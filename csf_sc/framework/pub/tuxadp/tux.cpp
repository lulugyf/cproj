#include <alloca.h>
#include <tpadm.h>
#include "framework.h"

#include "adapter.h"

#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

/*
安徽应急系统改造（2013-3):
双库函数的应急处理： 配置 crm.cfg 中， [BASEENV]EMERGENCY_FILE=???
参数为可选， 参数指向应急标记文件的绝对路径， 判断方式为如果文件存在， 则为应急模式

双库函数的应急处理模式： 如果传入多库标签（以，分隔的多个库标签），则只保留本大区的标签, 如果没有发现本区的标签, 则不处理

在  AssiMutiConnWork 函数的第一行前加入下面的语句
	char emergencyLabel[64];
	psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for 安徽应急

*/
#include <sys/stat.h>
static const char *checkEmergency(const char *dblabels, char *newlabel){
	//printf("-------[%s]\n", dblabels);
	if(strchr(dblabels, ',') == NULL)
		return dblabels; //非多库标签，不处理

	const char *f = cfgGetStr("BASEENV", "EMERGENCY_FILE");
	if(f[0] == 0){
		//printf("-------have no BASEENV.EMERGENCY_FILE\n");
		return dblabels; // 未配置则认为无应急模式支持
	}

	struct stat st;
	if(stat(f, &st) != 0){
		//printf("------emergency file not exists\n");
		return dblabels; //应急文件不存在, 非应急模式
	}

	const char *curpt = cfgGetStr("MAIN", "DBPARTITION");
	if(curpt[0] == 0)
		return dblabels;
	int ptlen = strlen(curpt);
	const char *p1, *p2;
	p1 = dblabels;
	while(1){
		p2 = strchr(p1, ',');
		if(p2 == NULL){
			if(memcmp(curpt, p1+strlen(p1)-ptlen, ptlen) == 0){
				strcpy(newlabel, p1);
				//printf("----------1[%s]\n", newlabel);
				return newlabel;
			}
			break;
		}
		if(memcmp(curpt, p2-ptlen, ptlen) == 0){
			memcpy(newlabel, p1, p2-p1);
			newlabel[p2-p1] = 0;
			//printf("----------2[%s]\n", newlabel);
			return newlabel;
		}
		p1 = p2+1;
	}
	//printf("----------3[%s]\n", dblabels);
	return dblabels;
}

void* busiwork(void* v1, db_connect* pdb, bool isLong);
utype* AssiMutiConnWork_old(const utype* in, TCtrlInfo* errInfo,
		TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, const char *psDbLabel,
		int iConnType)
{
	static db_factory dbFactory(iConnType != 0);
	uAutoPtr outParam;
	map<string, void*> m;
	TCtrlInfoEx CtrlInfo;
	map<string, void*>::iterator iter;
	memset(&CtrlInfo, 0, sizeof(TCtrlInfoEx));

	char emergencyLabel[64];
	psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for 安徽应急

	db_connect* dbcon = NULL;
	if (ptDoMerge == NULL)
		ptDoMerge = doMerge;
	try {
		dbFactory.resetActive();
		dbcon = dbFactory.addConnect(psDbLabel);
		dbFactory.setActive(psDbLabel);

		CtrlInfo.maindb = &dbcon->getOtlHandle();
		CtrlInfo.db = CtrlInfo.maindb;
		CtrlInfo.bReconnFlag = false;
		CtrlInfo.mainmdb = NULL;
		CtrlInfo.mdb = NULL;
		CtrlInfo.func = ptUtypeFuncPtr;
		CtrlInfo.input = in;

		dbFactory.doBegin(); //连接主数据库
		dbFactory.doCall(m, busiwork, &CtrlInfo);
		outParam = ptDoMerge(&m, &CtrlInfo);
		dbFactory.doEnd(true);
	} catch (...) {
		for (iter = m.begin(); iter != m.end(); iter++) {
			if (iter->second != NULL)
				uFree((utype*) iter->second);
		}
		throw;
	}
	for (iter = m.begin(); iter != m.end(); iter++) {
		if (iter->second != NULL)
			uFree((utype*) iter->second);
	}
	return outParam.release();
}

#define _LOG_FMT " rt_code:%ld,rt_msg:%s"

int tuxinit(int argc, char *argv[], const char *psDbLabel,
		const char *psTuxServerName, int iFlags) {

	return 0;
}

void tuxdone(const char *psDbLabel, int iFlags) {
	//otl_connect::otl_terminate();
}


void dumpcltid(TPSVCINFO *rqst, char *addr) {
	char clientip[128];
	char wsc[128];
	char buf[128];
	FBFR32* ibuf;
	long blen = 0;
	long *cd = rqst->cltid.clientdata;

	addr[0] = 0;
	if (cd[0] == 0 && cd[1] == 0xFFFFFFFFFFFFFFFE && cd[2] == 0xFFFFFFFFFFFFFFFF
			&& cd[3] == 0) {
		L4C_TRACE("domain call");
		return;
	} else
		L4C_TRACE("wsc data:0x%lX 0x%lX 0x%lX 0x%lX", cd[0], cd[1], cd[2],
				cd[3]);

	memset(buf, 0, 128);
	sprintf(buf, "0x%x 0x%x 0x%x 0x%x", rqst->cltid.clientdata[0],
			rqst->cltid.clientdata[1], rqst->cltid.clientdata[2],
			rqst->cltid.clientdata[3]);
	ibuf = (FBFR32 *) tpalloc(FMLTYPE32, NULL, 0);
	Fchg32(ibuf, TA_OPERATION, 0, "GET", 0);
	Fchg32(ibuf, TA_CLASS, 0, "T_CLIENT", 0);
	Fchg32(ibuf, TA_CLIENTID, 0, buf, 0);

	L4C_TRACE("Begin call tuxedo system svc [.TMIB] get clientdata ");

	if (tpcall(".TMIB", (char *) ibuf, 0, (char **) &ibuf, &blen, 0) == -1)
		tpreturn(TPSUCCESS, 0, rqst->data, 0, 0);

	Fget32(ibuf, TA_NADDR, (FLDOCC32) 0, clientip, 0);
	Fget32(ibuf, TA_WSC, (FLDOCC32) 0, wsc, 0);

	L4C_INFO("WSC-CALL=%s", clientip);
	strncpy(addr, clientip, 127);
	addr[127] = 0;
	tpfree((char*) ibuf);
}

void dotuxadp(char **obuf, int* obufLen, const char *psServiceName,
		TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType)
{
	char clientaddr[128], *addr = NULL;
	char *output = NULL;
	int  outlen = 0;

	if (strcmp(cfgGetStr("MAIN", "TUXCLIID"), "OFF") != 0){
		dumpcltid(transb, clientaddr);
		addr = clientaddr;
	}

	adpt_entry(&output, &outlen, psServiceName,
			(char *)transb->data, addr,
			psDbLabel, psUtypeFunc,
			ptUtypeFuncPtr, ptDoMerge, iConnType);
	if(outlen > 0){
		*obuf = (char *) tpalloc((char*) "STRING", NULL, outlen);
		printf("========outlen:%d  tpalloc return is NULL[%d], output is NULL[%d]\n",
				outlen, *obuf==NULL,  output == NULL);
		if(*obuf == NULL){
			printf("tpalloc failed tperrno:%d\n", tperrno);
			free(output);
		}else if(*output != NULL){
			memcpy(*obuf, output, outlen);
			*obufLen = outlen;
			free(output);
		}
	}else{
		*obuf = NULL;
		*obufLen = 0;
	}
}
/* avoid mem leak
 20111102 step 4 start :
 void tuxadp(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
 const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType)
 20111102 step 4 end
 */
void TUXADP(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
		const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType) {
	char* outbuf = NULL;
	int outlen = 0, before = 0;
	before = iUtypeMallocTimes;
	SetDebugStatus(true);
	dotuxadp(&outbuf, &outlen, psServiceName, transb, psDbLabel, psUtypeFunc,
			ptUtypeFuncPtr, doMerge, iConnType);
	if (iUtypeMallocTimes - before != 0
			&& strcmp(cfgGetStr("MAIN", "UTYPELEAK"), "OFF") != 0)
		L4C_WARN("服务[%s]未释放utype内存分配次数:%d", psServiceName,
				iUtypeMallocTimes - before);
	tpreturn(TPSUCCESS, 0, outbuf, outlen, 0);
}

/* avoid mem leak
 20111102 step 5 start :
 void tuxadpEx(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
 const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType)
 20111102 step 5 end :
 */
void TUXADPEX(const char *psServiceName, TPSVCINFO *transb,
		const char *psDbLabel, const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType) {
	char* outbuf = NULL;
	int outlen = 0, before = 0;
	before = iUtypeMallocTimes;
	SetDebugStatus(true);
	dotuxadp(&outbuf, &outlen, psServiceName, transb, psDbLabel, psUtypeFunc,
			ptUtypeFuncPtr, ptDoMerge, iConnType);
	if (iUtypeMallocTimes - before != 0
			&& strcmp(cfgGetStr("MAIN", "UTYPELEAK"), "OFF") != 0)
		L4C_WARN("服务[%s]未释放utype内存分配次数:%d", psServiceName,
				iUtypeMallocTimes - before);
	tpreturn(TPSUCCESS, 0, outbuf, outlen, 0);
}

int tuxacal(char* psServiceName, const utype *pu, long flag) {
	int han;
	char *xmlstr = uUType2Xml(pu, "ROOT");
	int ul = strlen((char *) xmlstr) + 1;
	char* reqbuf = (char *) tpalloc((char*) "STRING", NULL, ul);
	strcpy(reqbuf, xmlstr);
	free(xmlstr);
	han = tpacall(psServiceName, reqbuf, ul, flag);
	if (han < 0) {
		throw(appException(304 * 1000000 + tperrno, tpstrerror(tperrno)));
	}
	tpfree(reqbuf);
	return han;
}

utype * tuxcal(char* psServiceName, const utype *pu, long flag, const char* ip,
		unsigned short port) {
	long rcvlen = 0;
	utype* op;
	int han;
	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(pu);
	L4C_TRACE("------==INPUT END==-------");
	char *xmlstr = uUType2Xml(pu,"ROOT");
	int ul = strlen((char *)xmlstr);
	char* reqbuf = (char *)tpalloc((char*)"STRING", NULL, ul+1), *
rcvbuf	= (char
	*) tpalloc("STRING", NULL, 10240);
	if (reqbuf == NULL || rcvbuf == NULL)
		throw(appException(304 * 1000000, "内存分配失败"));
	strcpy(reqbuf, xmlstr);
	free(xmlstr);
	if (ip != NULL && port != 0) {
		char sWSNADDR[128];
		snprintf(sWSNADDR, 128, "//%s:%i", ip, (int) port);
		L4C_TRACE("new wsnaddr is:%s", sWSNADDR);
		/* setenv("WSNADDR", sWSNADDR, 1); for mm leak */
		strcpy(sWSNADDR + 8, sWSNADDR);
		memcpy(sWSNADDR, "WSNADDR=", 8);
		putenv(sWSNADDR);
	}
	L4C_TRACE("call svc[%s] input :%s", psServiceName, reqbuf);
	han = tpcall(psServiceName, (char *) reqbuf, ul, (char **) &rcvbuf, &rcvlen,
			flag);
	if (han < 0) {
		throw(appException(304 * 1000000 + tperrno, tpstrerror(tperrno)));
	}
	L4C_TRACE("call svc[%s] output :%s", psServiceName, rcvbuf);
	op = uXml2Utype(rcvbuf);
	tpfree(reqbuf);
	tpfree(rcvbuf);
	return op;
}

void tuxtst(const char* psServiceName, TPSVCINFO *transb,
		TUtypeFuncPtr ptUtypeFuncPtr) {
	char fn[MAXPATHLEN];
	char all[50 * 1024] = "";
	char line[10 * 1024];

	snprintf(fn, MAXPATHLEN, "/%s/run/cfg/tstop/%s.cfg", getenv("HOME"),
			psServiceName);
	FILE* fp = fopen(fn, "r");
	if (fp) {
		while (fgets(line, sizeof(line), fp) != NULL) {
			strcat(all, line);
		}
		fclose(fp);
	}
	if (all[0] == 0)
		strcpy(all,
				"<?xml version=\"1.0\" encoding=\"GBK\" standalone=\"no\" ?><ROOT><RETURN_CODE type=\"long\">301000000</RETURN_CODE><RETURN_MSG type=\"string\">无法打开测试用配置文件</RETURN_MSG></ROOT>");
	printf(all);
	tpreturn(TPSUCCESS, 0,
			strcpy((char*) tpalloc((char*) "STRING", NULL, strlen(all)), all),
			strlen(all), 0);
}



//简化版本的函数,  与 dotuxadp 的差异如下：
//1. 无自定义合并结果集函数（使用自带的），少一个入参；
//2. 不调用业务规则doRule；
//3. 不调用结果集过滤Powerfilter
//4. 完全不使用内存数据库
void dotuxadp1(char **obuf, int* obufLen, const char *psServiceName,
		TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr, int iConnType)
{
	char clientaddr[128], *addr = NULL;
	char *output = NULL;
	int  outlen = 0;

	if (strcmp(cfgGetStr("MAIN", "TUXCLIID"), "OFF") != 0){
		dumpcltid(transb, clientaddr);
		addr = clientaddr;
	}

	adpt_entry1(&output, &outlen, psServiceName,
			(char *)transb->data, addr,
			psDbLabel, psUtypeFunc,
			ptUtypeFuncPtr, iConnType);
	if(outlen > 0){
		*obuf = (char *) tpalloc((char*) "STRING", NULL, outlen);
		memcpy(*obuf, output, outlen);
		*obufLen = outlen;
		free(output);
	}else{
		*obuf = NULL;
		*obufLen = 0;
	}
}

/* avoid mem leak
 20111102 step 6 start :
 void tuxadp1(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
 const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType)
 20111102 step 6 end :
 */
void TUXADP1(const char *psServiceName, TPSVCINFO *transb,
		const char *psDbLabel, const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr, int iConnType) {
	char* outbuf = NULL;
	int outlen = 0, before = 0;
	before = iUtypeMallocTimes;
	SetDebugStatus(true);
	dotuxadp1(&outbuf, &outlen, psServiceName, transb, psDbLabel, psUtypeFunc,
			ptUtypeFuncPtr, iConnType);
	if (iUtypeMallocTimes - before != 0
			&& strcmp(cfgGetStr("MAIN", "UTYPELEAK"), "OFF") != 0)
		L4C_WARN("服务[%s]未释放utype内存分配次数:%d", psServiceName,
				iUtypeMallocTimes - before);
	tpreturn(TPSUCCESS, 0, outbuf, outlen, 0);
}


