#include <alloca.h>
#include <tpadm.h>
#include "framework.h"

#include "errlog.h"
#include "calltrace.h"

#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif 

//错误代码管理平台接口
int errMng(const utype *uin,
		const long retCode, char *retMsg,
		TCtrlInfo* errinfo, string *myret);

extern "C" void l4c_set_uniaccept(const char *accept);

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

bool checkChr(const char *s, const char c) {
	for (; *s != 0; s++) {
		if (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
			continue;
		return *s == c;
	}
	return false;
}

void* busiwork(void* v1, db_connect* pdb, bool isLong)
{
	 TCtrlInfoEx* ctrlInfo = (TCtrlInfoEx*) v1;

	if(strcmp(pdb->getCurType(), "MDB")==0){
		ctrlInfo->mdb=&pdb->getMDBHandle();
		ctrlInfo->db=ctrlInfo->maindb;
	}else{
		ctrlInfo->db=&pdb->getOtlHandle();
		ctrlInfo->mdb=ctrlInfo->mainmdb;	
	}
	
	ctrlInfo->retMsg[0] = 0;
  const char *bpname = NULL;
  if(((TCtrlInfoEx2*)ctrlInfo)->checkStruct()){
      bpname = ((TCtrlInfoEx2*)ctrlInfo)->getBPName();
  }

	return __CALLBP(ctrlInfo->func, bpname, ctrlInfo->input, ctrlInfo);
}
utype* doMerge(map<string, void*>* m, TCtrlInfo* errInfo)
{
	utype* dst=NULL;
	map<string, void*>::iterator iter;
	for(iter=m->begin();iter!=m->end();iter++){
		utype* src=(utype*)iter->second;
		if(src==NULL) continue;
		if(dst==NULL) {
			dst=src;
			continue;
		}else{
			int i;
			for(i=0;i<src->cnt;i++){
				switch(src->ppe[i]->type){
					case U_EMPTY:
						utAddEmpty(dst, utGetName(src,i));
						break;
					case U_CHAR:
						utAddChar(dst, utGetName(src,i), src->ppe[i]->value.v_char);
						break;
					case U_INT:
						utAddInt(dst, utGetName(src,i), src->ppe[i]->value.v_int);
						break;
					case U_LONG:
						utAddLong(dst, utGetName(src,i), src->ppe[i]->value.v_long);
						break;
					case U_DOUBLE:
						utAddDouble(dst, utGetName(src,i), src->ppe[i]->value.v_double);
						break;
					case U_STRING:
						utAddStr(dst, utGetName(src,i), src->ppe[i]->value.p_char);
						break;
					case U_ARRAY:
						utAddArray(dst, utGetName(src,i), utClone(src->ppe[i]->value.p_utype));
						break;
					case U_STRUCT:
						utAddStruct(dst, utGetName(src,i), utClone(src->ppe[i]->value.p_utype));
						break;
					default:
					{
						break;
					}
				}
			}
			uFree(src);
			(*m)[iter->first]=NULL;
		}
	}
	m->clear();
	return dst;
}

/*从入参中取统一流水并保存到日志全局变量中*/
//void l4c_set_uniaccept(const char *accept); 
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
		L4C_DEBUG("~~~~get accept by path[%s] failed, err[%s]\n",
				accept_path, err.errMsg);
		l4c_set_uniaccept(NULL);
		return; //入参中无统一流水, 则按将统一流水置空
	}
}

/*
安徽应急系统改造（2013-3):
双库函数的应急处理： 配置 crm.cfg 中， [BASEENV]EMERGENCY_FILE=???
参数为可选， 参数指向应急标记文件的绝对路径， 判断方式为如果文件存在， 则为
应急模式

双库函数的应急处理模式： 如果传入多库标签（以，分隔的多个库标签），则只保留
本大区的标签, 如果没有发现本区的标签, 则不处理

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
				L4C_ERROR("-----1当前系统处于应急模式，目前读库为：newlabel=%s-----",newlabel);
				return newlabel;
			}
			break;
		}
		if(memcmp(curpt, p2-ptlen, ptlen) == 0){
		memcpy(newlabel, p1, p2-p1);
		newlabel[p2-p1] = 0;
		//printf("----------2[%s]\n", newlabel);
		L4C_ERROR("-----2当前系统处于应急模式，目前读库为：newlabel=%s-----",newlabel);
		return newlabel;
		}
		p1 = p2+1;
	}
	//printf("----------3[%s]\n", dblabels);
	L4C_ERROR("-----3当前系统处于应急模式，目前读库为：newlabel=%s-----",newlabel);
	return dblabels;
}

utype* AssiMutiConnWork(const utype* in, TCtrlInfo* errInfo, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, const char *psDbLabel, int iConnType)
{
	char emergencyLabel[64];
	psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for 安徽应急
	
	static db_factory dbFactory(iConnType!=0);
	uAutoPtr outParam;
	map<string, void*> m;
	TCtrlInfoEx CtrlInfo;
	map<string, void*>::iterator iter;
	memset(&CtrlInfo,0,sizeof(TCtrlInfoEx));
	db_connect* dbcon=NULL;
	if(ptDoMerge==NULL) ptDoMerge=doMerge;
	try{
		dbFactory.resetActive();
		dbcon=dbFactory.addConnect(psDbLabel);
		dbFactory.setActive(psDbLabel);
		
		dbcon=dbFactory.addConnect(psDbLabel);
		dbFactory.setActive(psDbLabel);
		CtrlInfo.maindb=&dbcon->getOtlHandle();
		CtrlInfo.db=CtrlInfo.maindb;
		CtrlInfo.bReconnFlag=false;
		CtrlInfo.mainmdb=NULL;
		CtrlInfo.mdb=NULL;
		CtrlInfo.func=ptUtypeFuncPtr;
		CtrlInfo.input=in;
		dbFactory.doBegin();//连接主数据库
		dbFactory.doCall(m, busiwork, &CtrlInfo);
		outParam=ptDoMerge(&m, &CtrlInfo);
		dbFactory.doEnd(true);
	}
	catch (...){
		for(iter=m.begin();iter!=m.end();iter++){
			if(iter->second!=NULL)
				uFree((utype*)iter->second);
		}
		throw;
	}
	for(iter=m.begin();iter!=m.end();iter++){
		if(iter->second!=NULL)
			uFree((utype*)iter->second);
	}
	return outParam.release();
}
#define _LOG_FMT " rt_code:%ld,rt_msg:%s"
int tuxinit(int argc, char *argv[], const char *psDbLabel, const char *psTuxServerName, int iFlags)
{
	return 0;
}
void tuxdone(const char *psDbLabel, int iFlags)
{
	//otl_connect::otl_terminate();
}
static size_t errcodeExplain(TCtrlInfo* errInfo, long errcode, char* errmsg,char* urmsg, size_t len)
{
	urmsg[0]=0;
	if(errcode==0){
		snprintf(errmsg, len, "ok!");
		strcpy(urmsg, errmsg);
		return strlen(errmsg);
	}
	switch(errcode/1000000)	{
		case 300: snprintf(errmsg, len, "未知错误，请联系系统管理员！");break;
		case 301: snprintf(errmsg, len, "程序标准错误，请联系系统管理员！");break;
		case 302: snprintf(errmsg, len, "数据库错误，请联系系统管理员！");break;
		case 303: snprintf(errmsg, len, "参数存取错误，请联系系统管理员！");break;
		case 304: snprintf(errmsg, len, "中间件调用错误，请联系系统管理员！");break;
		case 305: snprintf(errmsg, len, "内存数据库错误，请联系系统管理员！");break;
		case 306: snprintf(errmsg, len, "取配置信息失败，请联系系统管理员！");break;
		default:{
			try{
				otl_stream smRtMsg(1,"select return_msg,CUST_CLASS_TIPS \
					from bs_returnmsg_dict a\
					where return_code = :RETURN_CODE<long>",GETDB(errInfo));
				smRtMsg<<errcode;
				if(smRtMsg.eof()){
					snprintf(errmsg, len, "无法获取该错误代码的错误信息，请直接查看明细信息");
				}else
					smRtMsg>>errmsg>>urmsg;
			}catch(...){
				snprintf(errmsg, len, "获取错误信息失败，请直接查看明细信息");
			}
		}
	}
	if(urmsg[0]==0)
		strcpy(urmsg, errmsg);
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
	if (ruleErrFlag == 0) {
		errcodeExplain(errInfo, retCode, sRtMsg, sUrMsg, 4096);
		utAddLong(uRet, "RETURN_CODE", retCode);
		utAddStr(uRet, "RETURN_MSG", sRtMsg);
		utAddStr(uRet, "USER_MSG", sUrMsg);
		utAddStr(uRet, "DETAIL_MSG", retMsg);
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

utype* doRule(const char* svc_name, const utype* puParamIn, TCtrlInfo* errInfo, string& sPromptMsg)
{
	int iRuleId;
	otl_nocommit_stream qSvcRule(1, "select rule_id from BS_SERVICERULE_REL where service_name=:SVC_NAME<char[15+1]> order  by rule_order",  GETDB(errInfo));
	qSvcRule<<svc_name;
	while(!qSvcRule.eof()){
		qSvcRule>>iRuleId;
		utype* u=doBusiRule(iRuleId, puParamIn,  errInfo);
		if(u!=NULL) return u;
		if(errInfo->infoMsg[0]!=0){
			if(!sPromptMsg.empty()) sPromptMsg+=" ";
			sPromptMsg+=errInfo->infoMsg;
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
 
void dumpcltid(TPSVCINFO *rqst,TCtrlInfoEx* errInfo)
{
	char clientip[128];
	char wsc[128];
	char buf[128];
	FBFR32* ibuf;
	long blen=0;
	long *cd=rqst->cltid.clientdata;
	
	errInfo->cliWsnAddr[0]=0;
	if(cd[0]==0&&cd[1]==0xFFFFFFFFFFFFFFFE&&cd[2]==0xFFFFFFFFFFFFFFFF&&cd[3]==0){
		L4C_TRACE("domain call");
		return;
	}
	else
		L4C_TRACE("wsc data:0x%lX 0x%lX 0x%lX 0x%lX", cd[0], cd[1], cd[2], cd[3]);
	memset(buf,0,128);
	sprintf(buf,"0x%x 0x%x 0x%x 0x%x",rqst->cltid.clientdata[0],rqst->cltid.clientdata[1],rqst->cltid.clientdata[2],rqst->cltid.clientdata[3]);	  
	ibuf = (FBFR32 *)tpalloc(FMLTYPE32, NULL, 0);
	Fchg32(ibuf, TA_OPERATION, 0, "GET",       0);
	Fchg32(ibuf, TA_CLASS,     0, "T_CLIENT", 0); 
	Fchg32(ibuf, TA_CLIENTID,     0, buf, 0);	  
	
	L4C_TRACE("Begin call tuxedo system svc [.TMIB] get clientdata ");
	
	if(tpcall(".TMIB", (char *)ibuf, 0, (char **)&ibuf, &blen, 0) == -1)
		tpreturn(TPSUCCESS, 0, rqst->data, 0, 0 );
	Fget32(ibuf,TA_NADDR,(FLDOCC32)0,clientip,0);
	Fget32(ibuf,TA_WSC,(FLDOCC32)0,wsc,0);
	L4C_INFO("WSC-CALL=%s",clientip);
	strncpy(errInfo->cliWsnAddr, clientip,127);
	errInfo->cliWsnAddr[127]=0;
	tpfree((char*)ibuf);
}
static void initLogEnv()
{
	static bool isInit=false;
	char stmp[1024];
	if(isInit) return;
	bool lcnull=false,ccnull=false;
	string env="";
	if(getenv("L4C_CFG")==NULL){
		lcnull=true;
	}else if(getenv("L4C_CFG")[0]==0) lcnull=true;
	if(getenv("CRM_CFG")==NULL){
		ccnull=true;
	}else if(getenv("CRM_CFG")[0]==0) ccnull=true;
	if(lcnull){
		if(ccnull)
			env=env+getenv("HOME")+"/run/cfg/crm.cfg";
		else
			env=env+getenv("CRM_CFG");
		strcpy(stmp, "L4C_CFG=");
		strcat(stmp, env.c_str());
		putenv(stmp);
	}
}
void dotuxadp(char **obuf, int* obufLen, const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
	const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType)
{
	char emergencyLabel[64];
	psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for 安徽应急
	
	char stmp[60];
		//2011/10/28 17:49:29
	int errid;
	struct timeval tm_begin;
  gettimeofday(&tm_begin, NULL);
  
  l4c_set_uniaccept(NULL);
  
  //2011/10/28 17:49:40
	initLogEnv();
	l4c_idenset(NULL, psServiceName); //设置日志标识，即服务名
	L4C_BULLETIN("Service<%s> Begin",psServiceName);
	if(strcmp(cfgGetStr("MAIN", "OTLINFO"), "ON")==0){
		putenv("OTL_INFO=on");
	}else{
		putenv("OTL_INFO=off");
	}
	static bool isInit=false;
	map<string, void*> m;
	static db_factory dbFactory(iConnType!=0);
#ifdef _USEDCI
	static db_connect mdbc;
#endif
	int iRuleErrFlag=0;
	char *ibuf;
	const utype *inParam;
	uAutoPtr inParam_new;
	uAutoPtr outParam;
	long retCode;
	char sIden[1024];
	char retMsg[1024];
	char errNo[32+1];
	char outName[30];
	uAutoPtr tup(NULL);
	
	//TCtrlInfoEx CtrlInfo;
	
	//端到端日志监控
	TCtrlInfoEx2 CtrlInfo;
	EntryRecord *_er = NULL;	
	int iRouteCode, iRouteType;
	char sRoutePath[100];
	char sRouteValue[30];
	string sPromptMsg;
	db_connect* dbcon=NULL;
	bool isXml = true;
	retCode=0;
	strcpy(retMsg,"OK!");
	
	dbFactory.resetActive();
	memset(&CtrlInfo,0,sizeof(TCtrlInfoEx));
	char sDBLabelBuf[100];
	try
	{
		ibuf=(char *)transb->data;
		//inParam = uXml2Utype(ibuf);
		if (checkChr(ibuf, '<'))
			inParam_new = uXml2Utype(ibuf);
		else {
			isXml = false;
			inParam_new = json2utype(ibuf);
			if (inParam_new.get() == NULL)
				throw(uException(U_ERR_MORE_TYPE,
						"input json string format invalid."));
		}
				
		if(!isInit){
			otl_connect::otl_initialize();
#ifdef _USEDCI
			mdbc.init("imdb");
			mdbc.setActive(true);
#endif
			isInit=1;
		}
				
		if(strcmp(cfgGetStr("MAIN", "TUXCLIID"), "OFF")!=0)
			dumpcltid(transb, &CtrlInfo);
			
		psDbLabel = useDBID(inParam_new.get(), psDbLabel, sDBLabelBuf, &inParam);// tux实例不分区改造2013-2
			
		//端到端监控
		getUniAccept(inParam); //入参中取统一流水
		CtrlInfo.init(transb->name, psUtypeFunc, inParam);
		_er = new EntryRecord(transb->name, &CtrlInfo);
		_er->setIn(transb->data);
		
		dbcon=dbFactory.addConnect(psDbLabel);
		dbFactory.setActive(psDbLabel);
		CtrlInfo.maindb=&dbcon->getOtlHandle();
		CtrlInfo.db=CtrlInfo.maindb;
		CtrlInfo.bReconnFlag=false;	
		try{
#ifdef _USEDCI
		if(strcmp(cfgGetStr("MAIN", "DCISUPPORT"), "OFF")!=0){
			CtrlInfo.mainmdb=&mdbc.getMDBHandle();
			CtrlInfo.mdb=CtrlInfo.mainmdb;
			CtrlInfo.bReconnFlag=!mdbc.tryConnect();
			CtrlInfo.mdbLastConn=mdbc.getLastConnectTime();
		}else{
			CtrlInfo.mainmdb=NULL;
			CtrlInfo.mdb=NULL;
		}
#else
		CtrlInfo.mainmdb=NULL;
		CtrlInfo.mdb=NULL;
#endif
		}catch(appException& appErr){
			if(appErr.errCode<305000000||appErr.errCode>=307000000) throw(appErr);
			CtrlInfo.mainmdb=NULL;
			CtrlInfo.mdb=NULL;
			L4C_ERROR("内存数据库连接失败");
		}
		dbFactory.doBegin();//连接主数据库
		CtrlInfo.func=ptUtypeFuncPtr;
		CtrlInfo.input=inParam;	
		L4C_TRACE("connect db success[%s]", psDbLabel);

		 

		L4C_DEBUG("------------inParam-------------");
		LogUtype(inParam, LVDEBUG);
		if (utFind(inParam, "OUTDATANAME") != UPOS_END){
			strcpy(outName, utGetStr(inParam, "OUTDATANAME"));
		} else {
			strcpy(outName, "OUT_DATA");
		}
		GlobalBusiInit(psServiceName, psDbLabel, psUtypeFunc, inParam);
		LOG_SERV("Service", inParam, &CtrlInfo, NULL,psServiceName);
		L4C_TRACE("rule begin");
		tup = doRule(psServiceName, inParam, &CtrlInfo, sPromptMsg);//entry rule
		if (tup != NULL){
			if(utFind(tup, "OUT_DATA")!=-1)
				outParam=utClone(utGetStruct(tup, "OUT_DATA"));
			else
				outParam=NULL;
			retCode=utGetLong(tup, "RETURN_CODE");
			strcpy(retMsg, utGetStr(tup, "RETURN_MSG"));
			L4C_DEBUG("RULEERR"_LOG_FMT, retCode, retMsg);
			iRuleErrFlag=1;
			goto END_LABEL;
		}
		L4C_TRACE("sPromptMsg:%s", sPromptMsg.c_str());
		L4C_TRACE("rule end");
		memset(&CtrlInfo,0,sizeof(TCtrlInfo));
		L4C_TRACE("begin call busi func");
		

		dbFactory.doCall(m, busiwork, &CtrlInfo);
		outParam=ptDoMerge(&m, &CtrlInfo);
		if(CtrlInfo.infoMsg[0]!=0){
			if(!sPromptMsg.empty()) sPromptMsg+=" ";
			sPromptMsg+=CtrlInfo.infoMsg;
		}
		if(outParam!=NULL){
			const char* sLoginNo;
			try{
				sLoginNo=utGetStrByDir(inParam, "REQUEST_INFO", "OPR_INFO", "LOGIN_NO");
			}
			catch(uException& err){
				goto END_LABEL1;
			}
			Powerfilter(outParam, &CtrlInfo, sLoginNo, psServiceName);
		}
END_LABEL1:
		L4C_DEBUG("------------outParam-------------");
		LogUtype(outParam, LVDEBUG);
END_LABEL:
		CtrlInfo.db=CtrlInfo.maindb;
		CtrlInfo.mdb=CtrlInfo.mainmdb;
	}
	catch(uException& err){
		retCode=303*1000000+err.errCode;
		strcpy(retMsg,err.errMsg);
	}
	catch(otl_exception& otlErr){// intercept OTL exceptions
		retCode=302*1000000+abs(otlErr.code);
		memset(retMsg,0,sizeof(retMsg));
		snprintf(retMsg,sizeof(retMsg)-1,"DBERR 错误：%s : %s : %s",otlErr.msg,otlErr.stm_text,otlErr.var_info);
	}
	catch(appException& appErr){
		retCode=appErr.errCode;
		memset(retMsg,0,sizeof(retMsg));
		strncpy(retMsg,appErr.errMsg,sizeof(retMsg)-1);
	}
	catch(std::exception& err){
		retCode=301*1000000;
		memset(retMsg,0,sizeof(retMsg));
		strncpy(retMsg,err.what(),sizeof(retMsg)-1);
	}
	catch(...){
		retCode=300*1000000;
		strcpy(retMsg,"未知错误请联系系统管理员!");
	}
finally:
	{
		if(!retCode){
			try{
				L4C_TRACE("bindRetBuff output begin");
				errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, outParam.release(),
						retCode, retMsg, sPromptMsg, obuf, obufLen, outName,
						isXml);
				if(sPromptMsg!="")
					L4C_WARN("%s", sPromptMsg.c_str());
				L4C_TRACE("bindRetBuff output end");
			}catch(...){
				retCode=303*1000000;
				strcpy(retMsg,"转换utype结构至XML失败，请检查是否节点名中包含不合法字符");
				L4C_ERROR(_LOG_FMT,retCode,retMsg);
				errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, NULL, retCode, retMsg,
						sPromptMsg, obuf, obufLen, NULL, isXml);
			}
		}
		else{
			L4C_ERROR("APPERR"_LOG_FMT,retCode,retMsg);
			errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, tup.release(), retCode, retMsg,
					sPromptMsg, obuf, obufLen, NULL, isXml);
		}
		dbFactory.doEnd(retCode==0);
#ifdef _USEDCI
		mdbc.doRollback();
#endif
		map<string, void*>::iterator iter;
		for(iter=m.begin();iter!=m.end();iter++){
			if(iter->second!=NULL)
				uFree((utype*)iter->second);
		}
		
		if(_er != NULL){
			_er->setCode(retCode);
			_er->setMsg(retMsg);
			_er->setOut(*obuf);
			delete _er;
		}		
		L4C_BULLETIN("Service<%s> End",psServiceName);
	}
}
extern int iUtypeMallocTimes;
void tuxadp(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
	const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType)
{
	char* outbuf=NULL;
	int outlen=0,before=0;
	before=iUtypeMallocTimes;
	SetDebugStatus(true);
	dotuxadp(&outbuf,&outlen,psServiceName, transb, psDbLabel,psUtypeFunc, ptUtypeFuncPtr, doMerge,iConnType);
	if(iUtypeMallocTimes-before!=0&&strcmp(cfgGetStr("MAIN", "UTYPELEAK"), "OFF")!=0) L4C_WARN("服务[%s]未释放utype内存分配次数:%d", psServiceName, iUtypeMallocTimes-before);
	tpreturn(TPSUCCESS,0,outbuf,outlen,0);
}
void tuxadpEx(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
	const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType)
{
	char* outbuf=NULL;
	int outlen=0,before=0;
	before=iUtypeMallocTimes;
	SetDebugStatus(true);
	dotuxadp(&outbuf,&outlen,psServiceName, transb, psDbLabel,psUtypeFunc, ptUtypeFuncPtr, ptDoMerge, iConnType);
	if(iUtypeMallocTimes-before!=0&&strcmp(cfgGetStr("MAIN", "UTYPELEAK"), "OFF")!=0) L4C_WARN("服务[%s]未释放utype内存分配次数:%d", psServiceName, iUtypeMallocTimes-before);
	tpreturn(TPSUCCESS,0,outbuf,outlen,0);
}
int tuxacal(char* psServiceName, const utype *pu, long flag)
{
	int han;
	char *xmlstr = uUType2Xml(pu,"ROOT");
	int ul = strlen((char *)xmlstr) + 1;
	char* reqbuf = (char *)tpalloc((char*)"STRING", NULL, ul);
	strcpy(reqbuf, xmlstr);
	free(xmlstr);
	han=tpacall(psServiceName, reqbuf, ul, flag);
	if(han<0){
		throw(appException(304*1000000+tperrno, tpstrerror(tperrno)));	
	}
	tpfree(reqbuf);
	return han;
}
utype * tuxcal(char* psServiceName, const utype *pu, long flag, const char* ip, unsigned short port)
{
	long rcvlen=0;
	utype* op;
	int han;
	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(pu);
	L4C_TRACE("------==INPUT END==-------");
	char *xmlstr = uUType2Xml(pu,"ROOT");
	int ul = strlen((char *)xmlstr) ;
	char* reqbuf = (char *)tpalloc((char*)"STRING", NULL, ul+1), *rcvbuf = (char *) tpalloc("STRING", NULL, 10240);
	if(reqbuf==NULL||rcvbuf==NULL)
		throw(appException(304*1000000, "内存分配失败"));	
	strcpy(reqbuf, xmlstr);
	free(xmlstr);
	if(ip!=NULL&&port!=0){
		char sWSNADDR[128];
		snprintf(sWSNADDR, 128, "//%s:%i", ip, (int)port);
		L4C_TRACE("new wsnaddr is:%s", sWSNADDR);
		strcpy(sWSNADDR+8, sWSNADDR);
		memcpy(sWSNADDR, "WSNADDR=", 8);
		putenv(sWSNADDR);
	}
	L4C_TRACE("call svc[%s] input :%s",psServiceName, reqbuf);
	han = tpcall(psServiceName, (char *)reqbuf, ul, (char **)&rcvbuf, &rcvlen, flag);
	if(han<0){
		throw(appException(304*1000000+tperrno, tpstrerror(tperrno)));	
	}
	L4C_TRACE("call svc[%s] output :%s",psServiceName, rcvbuf);
	op=uXml2Utype(rcvbuf);
	tpfree(reqbuf);
	tpfree(rcvbuf);
	return op;
}
void tuxtst(const char* psServiceName, TPSVCINFO *transb, TUtypeFuncPtr ptUtypeFuncPtr)
{
	char fn[MAXPATHLEN];
	char all[50*1024]="";
	char line[10*1024];
	snprintf(fn,MAXPATHLEN,"/%s/run/cfg/tstop/%s.cfg",getenv("HOME"), psServiceName);
	FILE* fp=fopen(fn, "r");
	if(fp){
		while(fgets(line,sizeof(line),fp)!=NULL){
			strcat(all,line);
		}
		fclose(fp);
	}
	if(all[0]==0) strcpy(all, "<?xml version=\"1.0\" encoding=\"GBK\" standalone=\"no\" ?><ROOT><RETURN_CODE type=\"long\">301000000</RETURN_CODE><RETURN_MSG type=\"string\">无法打开测试用配置文件</RETURN_MSG></ROOT>");
	printf(all);
	tpreturn(TPSUCCESS,0,strcpy((char*)tpalloc((char*)"STRING", NULL, strlen(all)),all),strlen(all),0);
}
//简化版本的函数
void dotuxadp1(char **obuf, int* obufLen, const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
	const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType)
{
	char emergencyLabel[64];
	int errid;
	psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for 安徽应急
	
	initLogEnv();
	l4c_set_uniaccept(NULL);
	l4c_idenset(NULL, psServiceName);//设置日志标识，即服务名
	
	
	L4C_BULLETIN("Service<%s> Begin",psServiceName);
	if(strcmp(cfgGetStr("MAIN", "OTLINFO"), "ON")==0){
	}else{
		putenv("OTL_INFO=off");
	}
	static bool isInit=false;
	map<string, void*> m;
	static db_factory dbFactory(iConnType!=0);
	int iRuleErrFlag=0;
	char *ibuf;
	const utype *inParam;
	uAutoPtr inParam_new;
	uAutoPtr outParam;
	long retCode;
	char sIden[1024];
	char retMsg[1024];
	char errNo[32+1];
	char outName[30];
	uAutoPtr tup(NULL);
  	//TCtrlInfoEx CtrlInfo;
	
	//端到端日志监控
	TCtrlInfoEx2 CtrlInfo;
	EntryRecord *_er = NULL;
	int iRouteCode, iRouteType;
	char sRoutePath[100];
	char sRouteValue[30];
	string sPromptMsg;
	db_connect* dbcon=NULL;
	bool isXml = true;
	retCode=0;
	strcpy(retMsg,"OK!");
	dbFactory.resetActive();
//2bad
	memset(&CtrlInfo,0,sizeof(TCtrlInfoEx));
	char sDBLabelBuf[100];
	
	try
	{
		ibuf=(char *)transb->data;
		if (checkChr(ibuf, '<'))
			inParam_new = uXml2Utype(ibuf);
		else {
			inParam_new = json2utype(ibuf);
			if (inParam_new.get() == NULL)
				throw(uException(U_ERR_MORE_TYPE,
						"input json string format invalid."));
			isXml = false;
		}
		
		psDbLabel = useDBID(inParam_new.get(), psDbLabel, sDBLabelBuf, &inParam);// tux实例不分区改造2013-2

		CtrlInfo.input=inParam;
		
			//端到端监控
		getUniAccept(inParam); //入参中取统一流水
		CtrlInfo.init(transb->name, psUtypeFunc, inParam);
		_er = new EntryRecord(transb->name, &CtrlInfo);
		_er->setIn(transb->data);		
		
		L4C_TRACE("parse input param over");
		
		if(!isInit){
			otl_connect::otl_initialize();
			isInit=1;
		}
		if(strcmp(cfgGetStr("MAIN", "TUXCLIID"), "OFF")!=0)
			dumpcltid(transb, &CtrlInfo);
		dbcon=dbFactory.addConnect(psDbLabel);
		dbFactory.setActive(psDbLabel);
		CtrlInfo.maindb=&dbcon->getOtlHandle();
		CtrlInfo.db=CtrlInfo.maindb;
		CtrlInfo.bReconnFlag=false;
		CtrlInfo.mainmdb=NULL;
		CtrlInfo.mdb=NULL;
		
			
		dbFactory.doBegin();//连接主数据库
		CtrlInfo.func=ptUtypeFuncPtr;
		L4C_TRACE("connect db success");

				
		
		L4C_DEBUG("------------inParam-------------");
		LogUtype(inParam, LVDEBUG);
		if (utFind(inParam, "OUTDATANAME") != UPOS_END){
			strcpy(outName, utGetStr(inParam, "OUTDATANAME"));
		} else {
			strcpy(outName, "OUT_DATA");
		}
		
		memset(&CtrlInfo,0,sizeof(TCtrlInfo));
		L4C_TRACE("begin call busi func");
		dbFactory.doCall(m, busiwork, &CtrlInfo);
		outParam=doMerge(&m, &CtrlInfo);
		if(CtrlInfo.infoMsg[0]!=0){
			if(!sPromptMsg.empty()) sPromptMsg+=" ";
			sPromptMsg+=CtrlInfo.infoMsg;
		}
		L4C_DEBUG("------------outParam-------------");
		LogUtype(outParam, LVDEBUG);
END_LABEL:
		CtrlInfo.db=CtrlInfo.maindb;
		CtrlInfo.mdb=CtrlInfo.mainmdb;
	}
	catch(uException& err){
		retCode=303*1000000+err.errCode;
		strcpy(retMsg,err.errMsg);
	}
	catch(otl_exception& otlErr){// intercept OTL exceptions
		retCode=302*1000000+abs(otlErr.code);
		memset(retMsg,0,sizeof(retMsg));
		snprintf(retMsg,sizeof(retMsg)-1,"DBERR 错误：%s : %s : %s",otlErr.msg,otlErr.stm_text,otlErr.var_info);
	}
	catch(appException& appErr){
		retCode=appErr.errCode;
		memset(retMsg,0,sizeof(retMsg));
		strncpy(retMsg,appErr.errMsg,sizeof(retMsg)-1);
	}
	catch(std::exception& err){
		retCode=301*1000000;
		memset(retMsg,0,sizeof(retMsg));
		strncpy(retMsg,err.what(),sizeof(retMsg)-1);
	}
	catch(...){
		retCode=300*1000000;
		strcpy(retMsg,"未知错误请联系系统管理员!");
	}
finally:
	{
		if(!retCode){
			try{
				L4C_TRACE("bindRetBuff output begin");
				errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, outParam.release(),
						retCode, retMsg, sPromptMsg, obuf, obufLen, outName,
						isXml);
				if(sPromptMsg!="")
					L4C_WARN("%s", sPromptMsg.c_str());
				L4C_TRACE("bindRetBuff output end");
			}catch(...){
				retCode=303*1000000;
				strcpy(retMsg,"转换utype结构至XML失败，请检查是否节点名中包含不合法字符");
				L4C_ERROR(_LOG_FMT,retCode,retMsg);
				errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, NULL, retCode, retMsg,
						sPromptMsg, obuf, obufLen, NULL, isXml);
			}
		}
		else{
			L4C_ERROR("APPERR"_LOG_FMT,retCode,retMsg);
			errid = bindRetBuff(psServiceName, inParam, iRuleErrFlag, &CtrlInfo, tup.release(), retCode, retMsg,
					sPromptMsg, obuf, obufLen, NULL, isXml);
			
		}
		dbFactory.doEnd(retCode==0);
		map<string, void*>::iterator iter;
		for(iter=m.begin();iter!=m.end();iter++){
			if(iter->second!=NULL)
				uFree((utype*)iter->second);
		}
		
		if(_er != NULL){
			_er->setCode(retCode);
			_er->setMsg(retMsg);
			_er->setOut(*obuf);
			delete _er;
		}		
		L4C_BULLETIN("Service<%s> End",psServiceName);
	}
}
void tuxadp1(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
	const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType)
{
	char* outbuf=NULL;
	int outlen=0,before=0;
	before=iUtypeMallocTimes;
	SetDebugStatus(true);
	dotuxadp1(&outbuf,&outlen,psServiceName, transb, psDbLabel,psUtypeFunc, ptUtypeFuncPtr, iConnType);
	if(iUtypeMallocTimes-before!=0&&strcmp(cfgGetStr("MAIN", "UTYPELEAK"), "OFF")!=0) L4C_WARN("服务[%s]未释放utype内存分配次数:%d", psServiceName, iUtypeMallocTimes-before);
	tpreturn(TPSUCCESS,0,outbuf,outlen,0);
}
