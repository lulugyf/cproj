#include <alloca.h>
#include <tpadm.h>
#include "framework.h"
#include "LogFunc.h"

#include "errlog.h"
#include "calltrace.h"

#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

/*
错误代码基本分段：
303000000 ~ 303999999  utype exception
302000000 ~ 302999999  otlexception 数据库类异常
301000000 ~ 301999999  标准c++异常
300000000 ~ 300999999  未知异常类型
其它                   appException 业务逻辑使用的错误代码
*/

#define _OUTUDPLOG_ 1

void Powerfilter(utype* pu_out, TCtrlInfo* errinfo, const utype* pu_in, const char* svc_name);

//错误代码管理平台接口
int errMng(const utype *uin,
		const long retCode, char *retMsg,
		TCtrlInfo* errinfo, string *myret);


// for json-datatype support
utype * json2utype(const char *str);
char * utype2json(const utype *pu);
char * utype2json(const utype *pu, const char *arrPath);
bool checkChr(const char *s, const char c);
char *str_toupper(char *src, char *dst, int dst_size)
{
    memset(dst, 0, dst_size);
    int len = strlen(src);
    int i = 0;
    for(i;i<len&&i<(dst_size-1);i++)
    {
        dst[i] = tolower(src[i]);
    }
    return dst;
}

static const utype *inputHeader = NULL;
const utype *CSF_getInputHeader()
{
	return inputHeader;
}
/*
for Sichuan CRM5.7, tuxedo 实例不分区 2013-2
只修改单库连接的情况, 删除从配置中得到的 MAIN.DBPARTITION,
替换为从入参中得到的 HEADER.DB_ID
如果有含DBID的包头， 则puIn指向BODY, 否则puIn与inParam相同

*/
const char *useDBID(const utype *inParam, const char *psDbLabel,
		char *psLabelBuf, const utype **puIn)
{
	const char *dbid;
	const char *curdbid; //配置中的当前DBID
    char curdbid_insensitive[258];
	*puIn = inParam;
	inputHeader = NULL;

	try{
		const utype *h = utGetStruct(inParam, "HEADER");
		inputHeader = h;
	} catch (uException& err) {
		return psDbLabel; //入参中无对应的字段按原有规则处理
	}
	try{
		dbid = str_toupper(utGetStr(inputHeader, "DB_ID"), curdbid_insensitive, sizeof(curdbid_insensitive));
		*puIn = utGetStruct(inParam, "BODY");
	} catch (uException& err) {
		return psDbLabel; //入参中无对应的字段按原有规则处理
	}
	if(strchr(psDbLabel, ',') != NULL)
		return psDbLabel; //多库连接不处理
	curdbid = cfgGetCurrentDBPatition();
	int l0 = strlen(curdbid);
	int l1 = strlen(psDbLabel);
	if(memcmp(curdbid, psDbLabel+l1-l0, l0) == 0){
		strncpy(psLabelBuf, psDbLabel, l1-l0);
		psLabelBuf[l1-l0] = 0;
		strcat(psLabelBuf, dbid);
		return psLabelBuf;
	}else{
		return psDbLabel; //后缀不相同， 则不替换， 可能是中心库，只使用了实例号1/2
	}
}

/*从入参中取统一流水并保存到日志全局变量中*/
void l4c_set_uniaccept(const char *accept);
void getUniAccept(const utype *puin){

	const char *accept_path = getenv("UNIACCEPT_PATH");
	if(accept_path == NULL){
		l4c_set_uniaccept(NULL);
		return;
	}
	//printf("~~~~~~ accept path:%s\n", accept_path);
	try{
		const char *accept = utGetStrByPath(puin, accept_path);
		l4c_set_uniaccept(accept);
	}catch (uException& err) {
		printf("~~~~get accept by path[%s] failed, err[%s]\n",
				accept_path, err.errMsg);
		l4c_set_uniaccept(NULL);
		return; //入参中无统一流水, 则按将统一流水置空
	}
}

void* busiwork(void* v1, db_connect* pdb, bool isLong) {
	
	TCtrlInfoEx* ctrlInfo = (TCtrlInfoEx*) v1;

	if (strcmp(pdb->getCurType(), "MDB") == 0) {
		ctrlInfo->mdb = &pdb->getMDBHandle();
		ctrlInfo->db = ctrlInfo->maindb;
	} else {
		ctrlInfo->db = &pdb->getOtlHandle();
		ctrlInfo->mdb = ctrlInfo->mainmdb;
	}
	ctrlInfo->retMsg[0] = 0;
#if _OUTUDPLOG_
	const char *bpname = NULL;
	if(((TCtrlInfoEx2*)ctrlInfo)->checkStruct()){
		bpname = ((TCtrlInfoEx2*)ctrlInfo)->getBPName();
	}
	return __CALLBP(ctrlInfo->func, bpname, ctrlInfo->input, ctrlInfo);
#else
	return ctrlInfo->func(ctrlInfo->input, ctrlInfo);
#endif
}

utype* doMerge(map<string, void*>* m, TCtrlInfo* errInfo) {
	utype* dst = NULL;
	map<string, void*>::iterator iter;
	for (iter = m->begin(); iter != m->end(); iter++) {
		utype* src = (utype*) iter->second;
		if (src == NULL)
			continue;
		if (dst == NULL) {
			dst = src;
			continue;
		} else {
			int i;
			for (i = 0; i < src->cnt; i++) {
				switch (src->ppe[i]->type) {
				case U_EMPTY:
					utAddEmpty(dst, utGetName(src, i));
					break;
				case U_CHAR:
					utAddChar(dst, utGetName(src, i),
							src->ppe[i]->value.v_char);
					break;
				case U_INT:
					utAddInt(dst, utGetName(src, i), src->ppe[i]->value.v_int);
					break;
				case U_LONG:
					utAddLong(dst, utGetName(src, i),
							src->ppe[i]->value.v_long);
					break;
				case U_DOUBLE:
					utAddDouble(dst, utGetName(src, i),
							src->ppe[i]->value.v_double);
					break;
				case U_STRING:
					utAddStr(dst, utGetName(src, i), src->ppe[i]->value.p_char);
					break;
				case U_ARRAY:
					utAddArray(dst, utGetName(src, i),
							utClone(src->ppe[i]->value.p_utype));
					break;
				case U_STRUCT:
					utAddStruct(dst, utGetName(src, i),
							utClone(src->ppe[i]->value.p_utype));
					break;
				default: {
					break;
				}
				}
			}
			uFree(src);
			(*m)[iter->first] = NULL;
		}
	}
	m->clear();
	return dst;
}

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
	L4C_DEBUG("====label[%s]\n", psDbLabel);
	psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for 安徽应急
	L4C_DEBUG("+===label[%s]\n", psDbLabel);

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

static size_t errcodeExplain(TCtrlInfo* errInfo, long errcode, char* errmsg,
		char* urmsg, size_t len, int *flags)
{
	if (errcode == 0) {
		if(errInfo->retMsg[0] != 0){
			strncpy(errmsg, errInfo->retMsg, len-1);
			errmsg[len-1] = 0;
		}else{
			strcpy(errmsg, "ok!");
		}
		//strcpy(urmsg, errmsg);
		return strlen(errmsg);
	}
	switch (errcode / 1000000) {
	case 300:
		snprintf(errmsg, len, "未知错误，请联系系统管理员！");
		break;
	case 301:
		snprintf(errmsg, len, "程序标准错误，请联系系统管理员！");
		break;
	case 302:
		snprintf(errmsg, len, "数据库错误，请联系系统管理员！");
		break;
	case 303:
		snprintf(errmsg, len, "参数存取错误，请联系系统管理员！");
		break;
	case 304:
		snprintf(errmsg, len, "中间件调用错误，请联系系统管理员！");
		break;
	case 305:
		snprintf(errmsg, len, "内存数据库错误，请联系系统管理员！");
		break;
	case 306:
		snprintf(errmsg, len, "取配置信息失败，请联系系统管理员！");
		break;
	default: {
		try {
			// 2015-9-18 山西错误信息显示优化需求， 标记为1时 RETURN_MSG 和 DETAIL_MSG 互换
			otl_stream smRtMsg(1,
					"select return_msg, CUST_CLASS_TIPS, flags \
					from bs_returnmsg_dict a\
					where return_code = :RETURN_CODE<long>",
					GETDB(errInfo));
			smRtMsg << errcode;
			if (smRtMsg.eof()) {
				snprintf(errmsg, len, "无法获取该错误代码的错误信息，请直接查看明细信息");
			} else{
				int l_flags;
				smRtMsg >> errmsg >> urmsg >> l_flags;
				*flags = l_flags;
			}
		} catch (...) {
			snprintf(errmsg, len, "获取错误信息失败，请直接查看明细信息");
		}
	}
	}
	if (urmsg[0] == 0){
		strcpy(urmsg, errmsg);
	}
	return strlen(errmsg);
}

static int bindRetBuff(const char *psServiceName, const utype *inParam, int ruleErrFlag, TCtrlInfo* errInfo, utype *outParam,
		long retCode, char *retMsg, string& sPromptMsg, char **retBuff,
		int *retLen, char *outName = NULL, bool isXml = true) {
	int ul;
	int errid;
	char sRtMsg[4096];
	char sUrMsg[4096];
	uAutoPtr uRet(uInit(3));
	char *xmlstr;
	sUrMsg[0] = 0;
	
	checkDetailMsgWithSQL(psServiceName, retMsg);
	if (ruleErrFlag == 0) {
		int flags;
		errcodeExplain(errInfo, retCode, sRtMsg, sUrMsg, 4096, &flags);
		checkDetailMsgWithSQL(psServiceName, sRtMsg);
		utAddLong(uRet, "RETURN_CODE", retCode);
		utAddStr(uRet, "USER_MSG", sUrMsg);
		if(flags == 1){ // 2015-9-18 山西错误信息显示优化需求， 标记为1时 RETURN_MSG 和 DETAIL_MSG 互换
			utAddStr(uRet, "RETURN_MSG", retMsg);
			utAddStr(uRet, "DETAIL_MSG", sRtMsg);
		}else{
			utAddStr(uRet, "RETURN_MSG", sRtMsg);
			utAddStr(uRet, "DETAIL_MSG", retMsg);
		}
		if (!retCode)
			utAddStr(uRet, "PROMPT_MSG", sPromptMsg.c_str());
		else
			utAddStr(uRet, "PROMPT_MSG", "");
		if (outParam != NULL) {
			utAddStruct(uRet, outName, outParam);
		}
	} else {
		uRet = outParam;
	}
    if(retCode == 0 && errInfo->infoMsg[0] == 0)
         strcpy(errInfo->infoMsg, "处理成功!");
         
	if(errInfo->infoMsg[0] != 0){
		UPOS pos = utFind(uRet, "USER_MSG");
		if(pos != UPOS_END)
			utSetStr(uRet, pos, errInfo->infoMsg);
		else
			utAddStr(uRet, "USER_MSG", errInfo->infoMsg);
		L4C_DEBUG("set USER_MSG from errInfo->infoMsg");
	}
	// 20130620 by guanyf, 在失败的调用中加入errid, 便于日志入库后对应.
	if(retCode != 0){
		errid = errlog_generrid();
		strcpy(sRtMsg, utGetStr(uRet, "RETURN_MSG"));
		sprintf(sRtMsg+strlen(sRtMsg), " ERRID:%d", errid);
		UPOS pos = utFind(uRet, "RETURN_MSG");
		utSetStr(uRet, pos, sRtMsg);

		//错误码平台接口， 通过接口或者同步的本地表替换返回信息
		// guanyf 2013-10-30
		string myret;
		int r = errMng(inParam, retCode, retMsg,
				errInfo, &myret);
		if(r == 1)
		{
			utAddStr(uRet, "STANDARD_PROMPT_MSG", myret.c_str());
		}
		else
			L4C_ERROR("errMng failed, return %d", r);
	}else{
		errid = 0;
	}

	if (isXml){
		xmlstr = uUType2Xml(uRet, "ROOT");
	}else{
		const char *arrPath = cfgGetStr("ServiceJsonArr", psServiceName);
		L4C_DEBUG("jsonarr===== for svc[%s] return [%s]", psServiceName, arrPath);
		if(arrPath[0] == 0){
			xmlstr = utype2json(uRet);
		}else{
			xmlstr = utype2json(uRet, arrPath);
		}
	}
	ul = strlen((char *) xmlstr) + 1;
	*retBuff = (char *) tpalloc((char*) "STRING", NULL, ul);
	strcpy(*retBuff, (char *) xmlstr);
	*retLen = ul;

	free(xmlstr);
	return errid;
}

utype* doRule(const char* svc_name, const utype* puParamIn, TCtrlInfo* errInfo,
		string& sPromptMsg) {
	static map<string, time_t> tTry;
	time_t tCur = time(NULL);
	int iRuleId;
	/*
	 2014-1-21  by guanyf 关于减少 select BS_SERVICERULE_REL 的执行次数的策略：
	  	  如果检测到表中没有数据， 则2分钟内不再查表
	 */
	if(tTry.find(svc_name) == tTry.end()){
		tTry[svc_name] = 0;
	}
	if(tCur - tTry[svc_name] < 120){
		L4C_DEBUG("Timed rule check skipped....");
		return NULL;
	}
	otl_nocommit_stream qSvcRule(1,
			"select rule_id from BS_SERVICERULE_REL where service_name=:SVC_NAME<char[15+1]> order  by rule_order",
			GETDB(errInfo));
	qSvcRule << svc_name;
	tTry[svc_name] = qSvcRule.eof() ? tCur : 0;
	while (!qSvcRule.eof()) {
		qSvcRule >> iRuleId;
		utype* u = doBusiRule(iRuleId, puParamIn, errInfo);
		if (u != NULL)
			return u;
		if (errInfo->infoMsg[0] != 0) {
			if (!sPromptMsg.empty())
				sPromptMsg += " ";
			sPromptMsg += errInfo->infoMsg;
		}
	}
	snprintf(errInfo->infoMsg, 2048, "%s", sPromptMsg.c_str());
	return NULL;
}

/**
 * @inparam    psServiceName	tuxedo服务名称
 * @inparam    transb			tuxedo通用传入参数
 * @inparam    psDbLabel		数据库连接标签
 * @inparam    psUtypeFunc		utype函数名称
 * @inparam    ptUtypeFuncPtr	utype函数地址
 * @inparam    iConnType		数据库连接方式,1长连接,0短连接
 * @inparam    iExFlags			扩展接口
 */

void dumpcltid(TPSVCINFO *rqst, TCtrlInfoEx* errInfo) {
	char clientip[128];
	char wsc[128];
	char buf[128];
	FBFR32* ibuf;
	long blen = 0;
	long *cd = rqst->cltid.clientdata;

	errInfo->cliWsnAddr[0] = 0;
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
	strncpy(errInfo->cliWsnAddr, clientip, 127);
	errInfo->cliWsnAddr[127] = 0;
	tpfree((char*) ibuf);
}

static void initLogEnv() {
	static bool isInit = false;
	char stmp[1024]; /* new add */
	if (isInit)
		return;
	bool lcnull = false, ccnull = false;
	string env = "";
	if (getenv("L4C_CFG") == NULL) {
		lcnull = true;
	} else if (getenv("L4C_CFG")[0] == 0)
		lcnull = true;
	if (getenv("CRM_CFG") == NULL) {
		ccnull = true;
	} else if (getenv("CRM_CFG")[0] == 0)
		ccnull = true;
	if (lcnull) {
		if (ccnull)
			env = env + getenv("HOME") + "/run/cfg/crm.cfg";
		else
			env = env + getenv("CRM_CFG");
		/* setenv("L4C_CFG", env.c_str(), 1); for mem leak */
		strcpy(stmp, "L4C_CFG="); /* new add */
		strcat(stmp, env.c_str());/* new add */
		putenv(stmp); /* new add */
	}
}

void dotuxadp(char **obuf, int* obufLen, const char *psServiceName,
		TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType)
{
	char stmp[128];
	struct timeval tm_begin;
	int errid;
	gettimeofday(&tm_begin, NULL);

	l4c_set_uniaccept(NULL);

	initLogEnv();
	l4c_idenset(NULL, psServiceName); //设置日志标识，即服务名
	L4C_BULLETIN("Service<%s> Begin",psServiceName);
	if(strcmp(cfgGetStr("MAIN", "OTLINFO"), "ON")==0) {
		putenv("OTL_INFO=on");
	} else {
		putenv("OTL_INFO=off");
	}
	static bool isInit=false;
	map<string, void*> m;
	static db_factory dbFactory(iConnType != 0);
#ifdef _USEDCI
	static db_connect mdbc;
#endif
	int iRuleErrFlag = 0;
	char *ibuf;
	const utype *inParam;
	uAutoPtr inParam_new;
	uAutoPtr outParam;
	long retCode;
	char retMsg[1024];
	char errNo[32 + 1];
	char outName[30];

	uAutoPtr tup(NULL);
#if _OUTUDPLOG_
	TCtrlInfoEx2 CtrlInfo;
	EntryRecord *_er = NULL;
#else
	TCtrlInfoEx CtrlInfo;
#endif
	memset(&CtrlInfo, 0, sizeof(TCtrlInfoEx));
	char sDBLabelBuf[100];
	string sPromptMsg;
	db_connect* dbcon = NULL;
	bool isXml = true;
	retCode = 0;
	strcpy(retMsg, "OK!");

	dbFactory.resetActive();
	try {
		ibuf = (char *) transb->data;
		errlog_begin(psServiceName, ibuf);
        #if 1
            L4C_BULLETIN("receive msg from client[%s]\n",ibuf);
        #endif
		if (checkChr(ibuf, '<'))
			inParam_new = uXml2Utype(ibuf);
		else {
			isXml = false;
			inParam_new = json2utype(ibuf);
			if (inParam_new.get() == NULL)
				throw(uException(U_ERR_MORE_TYPE,
						"input json string format invalid."));
		}

		if (!isInit) {
			otl_connect::otl_initialize();
#ifdef _USEDCI
			mdbc.init("imdb");
			mdbc.setActive(true);
#endif
			isInit = 1;
		}

		if (strcmp(cfgGetStr("MAIN", "TUXCLIID"), "OFF") != 0)
			dumpcltid(transb, &CtrlInfo);

		psDbLabel = useDBID(inParam_new.get(), psDbLabel, sDBLabelBuf, &inParam);// tux实例不分区改造2013-2

		char emergencyLabel[64];
		psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for 安徽应急

		getUniAccept(inParam); //入参中取统一流水
#if _OUTUDPLOG_
		if(CtrlInfo.init(transb->name, psUtypeFunc, inParam) ) {
			_er = new EntryRecord(transb->name, &CtrlInfo);
			_er->setIn(transb->data);
		}
#endif
		#if 1
            L4C_BULLETIN("conn db msg:[%s]\n",psDbLabel);
        #endif
        dbcon = dbFactory.addConnect(psDbLabel);
		dbFactory.setActive(psDbLabel);
		CtrlInfo.maindb = &dbcon->getOtlHandle();
		CtrlInfo.db = CtrlInfo.maindb;
		CtrlInfo.bReconnFlag = false;

		try {
#ifdef _USEDCI
			if(strcmp(cfgGetStr("MAIN", "DCISUPPORT"), "OFF")!=0) {
				CtrlInfo.mainmdb=&mdbc.getMDBHandle();
				CtrlInfo.mdb=CtrlInfo.mainmdb;
				CtrlInfo.bReconnFlag=!mdbc.tryConnect();
				CtrlInfo.mdbLastConn=mdbc.getLastConnectTime();
			} else {
				CtrlInfo.mainmdb=NULL;
				CtrlInfo.mdb=NULL;
			}
#else
			CtrlInfo.mainmdb = NULL;
			CtrlInfo.mdb = NULL;
#endif
		} catch (appException& appErr) {
			if (appErr.errCode < 305000000 || appErr.errCode >= 307000000)
				throw(appErr);
			CtrlInfo.mainmdb = NULL;
			CtrlInfo.mdb = NULL;
			L4C_ERROR("内存数据库连接失败");
		}
		CtrlInfo.func = ptUtypeFuncPtr;
		L4C_TRACE("connect db success");
		CtrlInfo.input = inParam;
		L4C_TRACE("parse input param over");
		L4C_DEBUG("------------inParam-------------");
		LogUtype(inParam, LVDEBUG);
		if (utFind(inParam, "OUTDATANAME") != UPOS_END) {
			strcpy(outName, utGetStr(inParam, "OUTDATANAME"));
		} else {
			strcpy(outName, "OUT_DATA");
		}

		GlobalBusiInit(psServiceName, psDbLabel, psUtypeFunc, inParam);
		for(int i=0; i<2; i++){
			//dbFactory.doBegin(); //连接主数据库
			// 通过循环重试一次， 避免每次进入服务都使用 select 1 from dual 来测试连接， 减少该语句的执行数量
			// 2014-1-21 by guanyf 关于该sql 语句top 1的应对
			try{
				L4C_TRACE("rule begin");
				tup = doRule(psServiceName, inParam, &CtrlInfo, sPromptMsg); //entry rule
				if (tup != NULL) {
					if (utFind(tup, "OUT_DATA") != -1)
						outParam = utClone(utGetStruct(tup, "OUT_DATA"));
					else
						outParam = NULL;
					retCode = utGetLong(tup, "RETURN_CODE");
					strcpy(retMsg, utGetStr(tup, "RETURN_MSG"));
					L4C_DEBUG("RULEERR"_LOG_FMT, retCode, retMsg);
					iRuleErrFlag = 1;
					goto END_LABEL;
				}
				L4C_TRACE("sPromptMsg:%s", sPromptMsg.c_str());
				L4C_TRACE("rule end");
				memset(&CtrlInfo, 0, sizeof(TCtrlInfo));
				L4C_TRACE("begin call busi func");
				dbFactory.doCall(m, busiwork, &CtrlInfo);
				if(ptDoMerge == NULL)
					outParam = doMerge(&m, &CtrlInfo);
				else
					outParam = ptDoMerge(&m, &CtrlInfo);
				if (CtrlInfo.infoMsg[0] != 0) {
					if (!sPromptMsg.empty())
						sPromptMsg += " ";
					sPromptMsg += CtrlInfo.infoMsg;
				}
				break;
			}catch(otl_exception &oerr){
				if(oerr.code == 3113 || oerr.code == 3114 || memcmp(oerr.msg, "123456789", 9) == 0
					|| oerr.code == 28 || oerr.code == 1012  //alter session kill 后报28的错, 再次访问就报1012
				){
					L4C_DEBUG("==DB Test loop, code:%d msg:%s", oerr.code, oerr.msg);
					dbFactory.doBegin(); //连接主数据库
					// 3113: end-of-file on communication channel
					// 3114: not connected to ORACLE
					// 0: not login yet
				}else{
					throw;
				}
			}catch(...){
				throw;
			}
		}
		/*if (outParam != NULL) {
			Powerfilter(outParam, &CtrlInfo, inParam, psServiceName);
		}*/
		END_LABEL1:
		L4C_DEBUG("------------outParam-------------");
		LogUtype(outParam, LVDEBUG);

		END_LABEL: CtrlInfo.db = CtrlInfo.maindb;
		CtrlInfo.mdb = CtrlInfo.mainmdb;
	} catch (uException& err) {
		retCode = 303 * 1000000 + err.errCode;
		strcpy(retMsg, err.errMsg);
	} catch (otl_exception& otlErr) { // intercept OTL exceptions
		retCode = 302 * 1000000 + abs(otlErr.code);
		memset(retMsg, 0, sizeof(retMsg));
		snprintf(retMsg, sizeof(retMsg) - 1, "DBERR 错误：%s : %s : %s",
				otlErr.msg, otlErr.stm_text, otlErr.var_info);
	} catch (appException& appErr) {
		retCode = appErr.errCode;
		memset(retMsg, 0, sizeof(retMsg));
		strncpy(retMsg, appErr.errMsg, sizeof(retMsg) - 1);
	} catch (std::exception& err) {
		retCode = 301 * 1000000;
		memset(retMsg, 0, sizeof(retMsg));
		strncpy(retMsg, err.what(), sizeof(retMsg) - 1);
	} catch (...) {
		retCode = 300 * 1000000;
		strcpy(retMsg, "未知错误请联系系统管理员!");
	}
	finally: {
		if (!retCode) {
			try {
				L4C_TRACE("bindRetBuff output begin");
				errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, outParam.release(),
						retCode, retMsg, sPromptMsg, obuf, obufLen, outName,
						isXml);
				if (sPromptMsg != "")
					L4C_WARN("%s", sPromptMsg.c_str());
				L4C_TRACE("bindRetBuff output end");
			} catch (...) {
				retCode = 303 * 1000000;
				strcpy(retMsg, "转换utype结构至XML失败，请检查是否节点名中包含不合法字符");
				L4C_ERROR(_LOG_FMT, retCode, retMsg);
				errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, NULL, retCode, retMsg,
						sPromptMsg, obuf, obufLen, NULL, isXml);
			}
		} else {
			L4C_ERROR("APPERR"_LOG_FMT, retCode, retMsg);
			errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, tup.release(), retCode, retMsg,
					sPromptMsg, obuf, obufLen, NULL, isXml);

		}

		errlog_end(errid, retCode, *obuf);
		if (retCode != 0) {
			CtrlInfo.lErrCode = retCode;
			strncpy(CtrlInfo.retMsg, retMsg, sizeof(CtrlInfo.retMsg) - 1);
		}
		try {
			//2011/10/28 17:58:28
			int nmret = NMLogCallBack(psServiceName, // 服务名称
					&CtrlInfo, // 传入错误代码及数据库链接
					psDbLabel, //数据库标签名称
					psUtypeFunc, //服务调用BP名称
					inParam, //输入参数Utype
					&tm_begin, //服务调用开始时间
					retCode,
					retMsg
					);
		} catch (uException& err) {
			L4C_TRACE("error error code = [%ld] error msg = [%s]", err.errCode,
					err.errMsg);
		} catch (otl_exception& otlErr) { // intercept OTL exceptions
			L4C_TRACE("error error code = [%ld] error msg = [%s]", otlErr.code,
					otlErr.msg);
		} catch (appException& appErr) {
			L4C_TRACE("error error code = [%ld] error msg = [%s]",
					appErr.errCode, appErr.errMsg);
		} catch (std::exception& err) {
			L4C_TRACE("error error msg = [%s]", err.what());
		} catch (...) {
			L4C_TRACE("error error msg = [未知错误请联系系统管理员]");
		}
        try{ //避免数据库连接异常时core掉 2014-4-25
            dbFactory.doEnd(retCode == 0);
        }catch(otl_exception& otlErr){
        }
#ifdef _USEDCI
		mdbc.doRollback();
#endif
		map<string, void*>::iterator iter;
		for (iter = m.begin(); iter != m.end(); iter++) {
			if (iter->second != NULL)
				uFree((utype*) iter->second);
		}
#if _OUTUDPLOG_
		if(_er != NULL){
			_er->setCode(retCode);
			_er->setMsg(retMsg);
			_er->setOut(*obuf);
			delete _er;
		}
#endif
		L4C_BULLETIN("Service<%s> End", psServiceName);
	}

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
		TUtypeFuncPtr ptUtypeFuncPtr, int iConnType) {

	struct timeval tm_begin;
	int errid;
	gettimeofday(&tm_begin, NULL);
	l4c_set_uniaccept(NULL);

	initLogEnv();
	l4c_idenset(NULL, psServiceName); //设置日志标识，即服务名
	L4C_BULLETIN("Service<%s> Begin",psServiceName);
	if(strcmp(cfgGetStr("MAIN", "OTLINFO"), "ON")==0) {
		putenv("OTL_INFO=on");
	} else {
		putenv("OTL_INFO=off");
	}
	static bool isInit=false;
	map<string, void*> m;
	static db_factory dbFactory(iConnType != 0);

	int iRuleErrFlag = 0;
	char *ibuf;
	const utype *inParam;
	uAutoPtr inParam_new;
	uAutoPtr outParam;
	long retCode;
	char retMsg[1024];
	char errNo[32 + 1];
	char outName[30];
	uAutoPtr tup(NULL);
#if _OUTUDPLOG_
	TCtrlInfoEx2 CtrlInfo;
	EntryRecord *_er = NULL;
#else
	TCtrlInfoEx CtrlInfo;
#endif
	char sDBLabelBuf[100];
	string sPromptMsg;
	db_connect* dbcon = NULL;
	bool isXml = true;
	retCode = 0;
	strcpy(retMsg, "OK!");
	dbFactory.resetActive();

	memset(&CtrlInfo, 0, sizeof(TCtrlInfoEx));
	try {
		ibuf = (char *) transb->data;
		errlog_begin(psServiceName, ibuf);
		if (checkChr(ibuf, '<'))
			inParam_new = uXml2Utype(ibuf);
		else {
			inParam_new = json2utype(ibuf);
			if (inParam_new.get() == NULL)
				throw(uException(U_ERR_MORE_TYPE,
						"input json string format invalid."));
			isXml = false;
		}

		if (!isInit) {
			otl_connect::otl_initialize();
			isInit = 1;
		}

		if (strcmp(cfgGetStr("MAIN", "TUXCLIID"), "OFF") != 0)
			dumpcltid(transb, &CtrlInfo);

		psDbLabel = useDBID(inParam_new.get(), psDbLabel, sDBLabelBuf, &inParam);// tux实例不分区改造2013-2
		char emergencyLabel[64];
		psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for 安徽应急

		getUniAccept(inParam); //入参中取统一流水
#if _OUTUDPLOG_
		CtrlInfo.init(transb->name, psUtypeFunc, inParam);
		_er = new EntryRecord(transb->name, &CtrlInfo);
		_er->setIn(transb->data);
#endif
		dbcon = dbFactory.addConnect(psDbLabel);
		dbFactory.setActive(psDbLabel);
		CtrlInfo.maindb = &dbcon->getOtlHandle();
		CtrlInfo.db = CtrlInfo.maindb;
		CtrlInfo.bReconnFlag = false;
		CtrlInfo.mainmdb = NULL;
		CtrlInfo.mdb = NULL;

		dbFactory.doBegin(); //连接主数据库
		CtrlInfo.func = ptUtypeFuncPtr;
		L4C_TRACE("connect db success");
		CtrlInfo.input = inParam;
		L4C_TRACE("parse input param over");
		L4C_DEBUG("------------inParam-------------");
		LogUtype(inParam, LVDEBUG);
		if (utFind(inParam, "OUTDATANAME") != UPOS_END) {
			strcpy(outName, utGetStr(inParam, "OUTDATANAME"));
		} else {
			strcpy(outName, "OUT_DATA");
		}

		GlobalBusiInit(psServiceName, psDbLabel, psUtypeFunc, inParam);

		memset(&CtrlInfo, 0, sizeof(TCtrlInfo));
		L4C_TRACE("begin call busi func");
		dbFactory.doCall(m, busiwork, &CtrlInfo);
		outParam = doMerge(&m, &CtrlInfo);
		if (CtrlInfo.infoMsg[0] != 0) {
			if (!sPromptMsg.empty())
				sPromptMsg += " ";
			sPromptMsg += CtrlInfo.infoMsg;
		}
		L4C_DEBUG("------------outParam-------------");
		LogUtype(outParam, LVDEBUG);

		END_LABEL: CtrlInfo.db = CtrlInfo.maindb;
		CtrlInfo.mdb = CtrlInfo.mainmdb;
	} catch (uException& err) {
		retCode = 303 * 1000000 + err.errCode;
		strcpy(retMsg, err.errMsg);
	} catch (otl_exception& otlErr) { // intercept OTL exceptions
		retCode = 302 * 1000000 + abs(otlErr.code);
		memset(retMsg, 0, sizeof(retMsg));
		snprintf(retMsg, sizeof(retMsg) - 1, "DBERR 错误：%s : %s : %s",
				otlErr.msg, otlErr.stm_text, otlErr.var_info);
	} catch (appException& appErr) {
		retCode = appErr.errCode;
		memset(retMsg, 0, sizeof(retMsg));
		strncpy(retMsg, appErr.errMsg, sizeof(retMsg) - 1);
	} catch (std::exception& err) {
		retCode = 301 * 1000000;
		memset(retMsg, 0, sizeof(retMsg));
		strncpy(retMsg, err.what(), sizeof(retMsg) - 1);
	} catch (...) {
		retCode = 300 * 1000000;
		strcpy(retMsg, "未知错误请联系系统管理员!");
	}
	finally: {
		if (!retCode) {
			try {
				L4C_TRACE("bindRetBuff output begin");
				errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, outParam.release(),
						retCode, retMsg, sPromptMsg, obuf, obufLen, outName,
						isXml);
				if (sPromptMsg != "")
					L4C_WARN("%s", sPromptMsg.c_str());
				L4C_TRACE("bindRetBuff output end");
			} catch (...) {
				retCode = 303 * 1000000;
				strcpy(retMsg, "转换utype结构至XML失败，请检查是否节点名中包含不合法字符");
				L4C_ERROR(_LOG_FMT, retCode, retMsg);
				errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, NULL, retCode, retMsg,
						sPromptMsg, obuf, obufLen, NULL, isXml);
			}
		} else {
			L4C_ERROR("APPERR"_LOG_FMT, retCode, retMsg);
			errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, tup.release(), retCode, retMsg,
					sPromptMsg, obuf, obufLen, NULL, isXml);

		}
		if (retCode != 0) {
			CtrlInfo.lErrCode = retCode;
			strncpy(CtrlInfo.retMsg, retMsg, sizeof(CtrlInfo.retMsg) - 1);
		}
		errlog_end(errid, retCode, *obuf);
		try {
			//2011/10/28 17:58:28
			int nmret = NMLogCallBack(psServiceName, // 服务名称
					&CtrlInfo, // 传入错误代码及数据库链接
					psDbLabel, //数据库标签名称
					psUtypeFunc, //服务调用BP名称
					inParam, //输入参数Utype
					&tm_begin, //服务调用开始时间
					retCode,
					retMsg
					);
		} catch (uException& err) {
			L4C_TRACE("error error code = [%ld] error msg = [%s]", err.errCode,
					err.errMsg);
		} catch (otl_exception& otlErr) { // intercept OTL exceptions
			L4C_TRACE("error error code = [%ld] error msg = [%s]", otlErr.code,
					otlErr.msg);
		} catch (appException& appErr) {
			L4C_TRACE("error error code = [%ld] error msg = [%s]",
					appErr.errCode, appErr.errMsg);
		} catch (std::exception& err) {
			L4C_TRACE("error error msg = [%s]", err.what());
		} catch (...) {
			L4C_TRACE("error error msg = [未知错误请联系系统管理员]");
		}
        try{ //避免数据库连接异常时core掉 2014-4-25
            dbFactory.doEnd(retCode == 0);
        }catch(otl_exception& otlErr){
        }
		map<string, void*>::iterator iter;
		for (iter = m.begin(); iter != m.end(); iter++) {
			if (iter->second != NULL)
				uFree((utype*) iter->second);
		}
#if _OUTUDPLOG_
		if(_er != NULL){
			_er->setCode(retCode);
			_er->setMsg(retMsg);
			_er->setOut(*obuf);
			delete _er;
		}
#endif
		L4C_BULLETIN("Service<%s> End", psServiceName);
	}

}


bool checkChr(const char *s, const char c) {
	for (; *s != 0; s++) {
		if (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
			continue;
		return *s == c;
	}
	return false;
}


utype* pCallESBApi(const utype * inParam, const char *service_name, const char *route_key, const char * route_value, \
                         int call_type, int conn_timeout, int recv_timeout);

utype* AssiMutiConnWork_callesb(const char *bpname, const utype* in, TCtrlInfo* errInfo,
		TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, const char *psDbLabel,
		int iConnType)
{
	const char *service_name;
	long rcode;
	char *rmsg;
	char svc_name[128], *ptr;
	const char *route_type = NULL, *route_value = NULL;
	utype *uret = NULL;

	L4C_DEBUG("bpname[%s] dblabel[%s]", bpname, psDbLabel);
	service_name = cfgGetStr("AssiMutiConnWork", bpname);
	if(service_name[0] == 0){
		//throw(appException(304 * 1000000 + 9001, "AssiMutiConnWork config not found"));
		//改为调用直接跨库连接的模式
		return AssiMutiConnWork_old(in, errInfo, ptUtypeFuncPtr, ptDoMerge, psDbLabel, iConnType);
	}
	L4C_DEBUG("service_name[%s]", service_name);
	strcpy(svc_name, service_name);
	ptr = strchr(svc_name, ',');
	if(ptr != NULL){
		//配置中带有路由的， 直接从这里取
		if(CSF_getInputHeader() != NULL){
			//如果全局变量中有header，就用变量中的
			*ptr = 0;
		}else{
			*ptr = 0;
			route_type = ptr+1;
			ptr = strchr((char *)route_type, ',');
			if(ptr == NULL){
				route_type = NULL; //配置有误
			}else{
				*ptr = 0;
				route_value = ptr+1;
			}
		}
	}else{
		//使用默认路由值
		route_type = cfgGetStr("AssiMutiConnWork", "_defRouteType");
		route_value = cfgGetStr("AssiMutiConnWork", "_defRouteValue");
	}

	// 2013-12-9 by guanyf 改为直接tpcall
	uret = tuxcal(svc_name, in, 0, NULL, 0);
	//uret = pCallESBApi(in, svc_name, route_type, route_value, 1, 5, 10);

	// 处理异常
	if(uret == NULL){
		throw(appException(304 * 1000000 + 9002, "AssiMutiConnWork call service failed"));
	}
	L4C_DEBUG("pCallESBApi", service_name);

	try{
		rcode = utGetLong(uret, "RETURN_CODE");
		rmsg = utGetStr(uret, "RETURN_MSG");
	}catch(...){
		uFree(uret);
		throw(appException(304 * 1000000 + 9003, "AssiMutiConnWork can not find RETURN_CODE or RETURN_MSG"));
	}
	if(rcode != 0L)
	{
		uFree(uret);
		throw(appException(rcode, rmsg));
	}
	/////////////////////////////////
	//检查去掉包头
	//utype *u1 = utClone(utGetStruct(uret, "OUT_DATA"));
	utype *u1=NULL;
	if (UPOS_END == utFind(in, "OUTDATANAME"))
		u1 = utClone(utGetStruct(uret, "OUT_DATA"));
	else
		u1 = utClone(utGetStruct(uret, utGetStr(in, "OUTDATANAME")));

	uFree(uret);

	return u1;
}


#include <pthread.h>
struct ADPPARAM {
	const char *psServiceName;
	TPSVCINFO *transb;
	const char *psDbLabel;
	const char *psUtypeFunc;
	TUtypeFuncPtr ptUtypeFuncPtr;
	int iConnType;

	char **outbuf;
	int *outlen;
	TDoMerge merge_func;
	int flag_1;   //调用函数选择： 0-dotuxadp  1-dotuxadp1
};

void *ADP_Thread(void *param){
	ADPPARAM *p = (ADPPARAM *)param;
	if(p->flag_1 == 0)
	dotuxadp(p->outbuf, p->outlen, p->psServiceName, p->transb, p->psDbLabel, p->psUtypeFunc,
			p->ptUtypeFuncPtr, p->merge_func, p->iConnType);
	else if(p->flag_1 == 1){
		dotuxadp1(p->outbuf, p->outlen, p->psServiceName, p->transb, p->psDbLabel, p->psUtypeFunc,
			p->ptUtypeFuncPtr, p->iConnType);
	}

}


void TUXADP(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
		const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType) {
	TUXADPEX(psServiceName, transb, psDbLabel, psUtypeFunc, ptUtypeFuncPtr, doMerge, iConnType);
}

void TUXADP1(const char *psServiceName, TPSVCINFO *transb,
		const char *psDbLabel, const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr, int iConnType) {
	// iConnType | 0x03 的含义是要通过iConnType 来传递调用 dotuxadp1 的标识
	TUXADPEX(psServiceName, transb, psDbLabel, psUtypeFunc, ptUtypeFuncPtr, doMerge, iConnType | 0x03);
}

/* avoid mem leak
 20111102 step 5 start :
 void tuxadpEx(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
 const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType)
 20111102 step 5 end :

2015-3-9: 增加了计算业务代码栈使用量的代码， 这个计算只用于测试（在测试环境中只是环境变量 STACK_SIZE=n （单位MB）为开关
   这部分的统一入口在TUXADPEX 中， 为了兼容dotuxadp1, 通过 iConnType来传递标识: iConnType & 0x03 > 0 则调用dotuxadp1
2015-3-9： 四川测试环境要求强制使用数据库短连接的需求： 防火墙切断闲置连接导致服务僵死
     开关使用环境变量： CSF_FORCE_SHORT_DBCONN , 只要有该环境变量则认为开关打开
 */
extern int iUtypeMallocTimes;
void TUXADPEX(const char *psServiceName, TPSVCINFO *transb,
		const char *psDbLabel, const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType) {
	char* outbuf = NULL;
	int outlen = 0, before = 0;
	if(getenv("CSF_FORCE_SHORT_DBCONN") != NULL)
		iConnType &= 0x03;
	before = iUtypeMallocTimes;
	SetDebugStatus(true);
	
	printf("===== test stack size ENV[STACK_SIZE] exists: %d, if use force_short_dbconn: %d, iconnType:%d\n",
		getenv("STACK_SIZE") != NULL,
		getenv("CSF_FORCE_SHORT_DBCONN") != NULL,
		iConnType);
	
	if(getenv("STACK_SIZE") != NULL){
		ADPPARAM *p = new ADPPARAM();
		p->psServiceName = psServiceName;
		p->transb = transb;
		p->psDbLabel = psDbLabel;
		p->psUtypeFunc = psUtypeFunc;
		p->ptUtypeFuncPtr = ptUtypeFuncPtr;
		p->iConnType = iConnType & 0x01; //只取最低位
		p->outbuf = &outbuf;
		p->outlen = &outlen;
		p->merge_func = ptDoMerge;
		p->flag_1 = iConnType & 0x03 > 0 ? 1 : 0;

		int stacksize = atoi(getenv("STACK_SIZE"))*1024*1024;
		pthread_attr_t attr;
		pthread_t thread;
		void *stack;
		void *status;
		pthread_attr_init(&attr);

		stack = malloc(stacksize);
		if(stack == NULL){
			printf("malloc failed\n");
			return;
		}
		memset(stack, 0xEF, stacksize);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		pthread_attr_setstack(&attr, stack, stacksize);

		pthread_create(&thread, &attr, ADP_Thread, p);

		pthread_attr_destroy(&attr);

		pthread_join(thread, &status);
		free(p);
		int i;
		unsigned char *cc = (unsigned char *)stack;
		for(i=0; i<stacksize; i++){
			if(cc[i] != 0xef) break;
		}
		printf("===stack used: %d\n", stacksize-i);
		free(stack);
	}else{
		if(iConnType & 0x03 > 0){
			dotuxadp1(&outbuf, &outlen, psServiceName, transb, psDbLabel, psUtypeFunc,
				ptUtypeFuncPtr, iConnType & 0x01);
		}else{
			dotuxadp(&outbuf, &outlen, psServiceName, transb, psDbLabel, psUtypeFunc,
				ptUtypeFuncPtr, ptDoMerge, iConnType);
		}
	}
	//dotuxadp(&outbuf, &outlen, psServiceName, transb, psDbLabel, psUtypeFunc,
	//		ptUtypeFuncPtr, ptDoMerge, iConnType);

	if (iUtypeMallocTimes - before != 0
			&& strcmp(cfgGetStr("MAIN", "UTYPELEAK"), "OFF") != 0)
		L4C_WARN("服务[%s]未释放utype内存分配次数:%d", psServiceName,
				iUtypeMallocTimes - before);
	tpreturn(TPSUCCESS, 0, outbuf, outlen, 0);
}
