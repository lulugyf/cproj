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
�����������ֶΣ�
303000000 ~ 303999999  utype exception
302000000 ~ 302999999  otlexception ���ݿ����쳣
301000000 ~ 301999999  ��׼c++�쳣
300000000 ~ 300999999  δ֪�쳣����
����                   appException ҵ���߼�ʹ�õĴ������
*/

#define _OUTUDPLOG_ 1

void Powerfilter(utype* pu_out, TCtrlInfo* errinfo, const utype* pu_in, const char* svc_name);

//����������ƽ̨�ӿ�
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
for Sichuan CRM5.7, tuxedo ʵ�������� 2013-2
ֻ�޸ĵ������ӵ����, ɾ���������еõ��� MAIN.DBPARTITION,
�滻Ϊ������еõ��� HEADER.DB_ID
����к�DBID�İ�ͷ�� ��puInָ��BODY, ����puIn��inParam��ͬ

*/
const char *useDBID(const utype *inParam, const char *psDbLabel,
		char *psLabelBuf, const utype **puIn)
{
	const char *dbid;
	const char *curdbid; //�����еĵ�ǰDBID
    char curdbid_insensitive[258];
	*puIn = inParam;
	inputHeader = NULL;

	try{
		const utype *h = utGetStruct(inParam, "HEADER");
		inputHeader = h;
	} catch (uException& err) {
		return psDbLabel; //������޶�Ӧ���ֶΰ�ԭ�й�����
	}
	try{
		dbid = str_toupper(utGetStr(inputHeader, "DB_ID"), curdbid_insensitive, sizeof(curdbid_insensitive));
		*puIn = utGetStruct(inParam, "BODY");
	} catch (uException& err) {
		return psDbLabel; //������޶�Ӧ���ֶΰ�ԭ�й�����
	}
	if(strchr(psDbLabel, ',') != NULL)
		return psDbLabel; //������Ӳ�����
	curdbid = cfgGetCurrentDBPatition();
	int l0 = strlen(curdbid);
	int l1 = strlen(psDbLabel);
	if(memcmp(curdbid, psDbLabel+l1-l0, l0) == 0){
		strncpy(psLabelBuf, psDbLabel, l1-l0);
		psLabelBuf[l1-l0] = 0;
		strcat(psLabelBuf, dbid);
		return psLabelBuf;
	}else{
		return psDbLabel; //��׺����ͬ�� ���滻�� ���������Ŀ⣬ֻʹ����ʵ����1/2
	}
}

/*�������ȡͳһ��ˮ�����浽��־ȫ�ֱ�����*/
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
		return; //�������ͳһ��ˮ, �򰴽�ͳһ��ˮ�ÿ�
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
����Ӧ��ϵͳ���죨2013-3):
˫�⺯����Ӧ������ ���� crm.cfg �У� [BASEENV]EMERGENCY_FILE=???
����Ϊ��ѡ�� ����ָ��Ӧ������ļ��ľ���·���� �жϷ�ʽΪ����ļ����ڣ� ��ΪӦ��ģʽ

˫�⺯����Ӧ������ģʽ�� ����������ǩ���ԣ��ָ��Ķ�����ǩ������ֻ�����������ı�ǩ, ���û�з��ֱ����ı�ǩ, �򲻴���

��  AssiMutiConnWork �����ĵ�һ��ǰ������������
	char emergencyLabel[64];
	psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for ����Ӧ��

*/
#include <sys/stat.h>
static const char *checkEmergency(const char *dblabels, char *newlabel){
	//printf("-------[%s]\n", dblabels);
	if(strchr(dblabels, ',') == NULL)
		return dblabels; //�Ƕ���ǩ��������

	const char *f = cfgGetStr("BASEENV", "EMERGENCY_FILE");
	if(f[0] == 0){
		//printf("-------have no BASEENV.EMERGENCY_FILE\n");
		return dblabels; // δ��������Ϊ��Ӧ��ģʽ֧��
	}

	struct stat st;
	if(stat(f, &st) != 0){
		//printf("------emergency file not exists\n");
		return dblabels; //Ӧ���ļ�������, ��Ӧ��ģʽ
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
	psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for ����Ӧ��
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

		dbFactory.doBegin(); //���������ݿ�
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
		snprintf(errmsg, len, "δ֪��������ϵϵͳ����Ա��");
		break;
	case 301:
		snprintf(errmsg, len, "�����׼��������ϵϵͳ����Ա��");
		break;
	case 302:
		snprintf(errmsg, len, "���ݿ��������ϵϵͳ����Ա��");
		break;
	case 303:
		snprintf(errmsg, len, "������ȡ��������ϵϵͳ����Ա��");
		break;
	case 304:
		snprintf(errmsg, len, "�м�����ô�������ϵϵͳ����Ա��");
		break;
	case 305:
		snprintf(errmsg, len, "�ڴ����ݿ��������ϵϵͳ����Ա��");
		break;
	case 306:
		snprintf(errmsg, len, "ȡ������Ϣʧ�ܣ�����ϵϵͳ����Ա��");
		break;
	default: {
		try {
			// 2015-9-18 ɽ��������Ϣ��ʾ�Ż����� ���Ϊ1ʱ RETURN_MSG �� DETAIL_MSG ����
			otl_stream smRtMsg(1,
					"select return_msg, CUST_CLASS_TIPS, flags \
					from bs_returnmsg_dict a\
					where return_code = :RETURN_CODE<long>",
					GETDB(errInfo));
			smRtMsg << errcode;
			if (smRtMsg.eof()) {
				snprintf(errmsg, len, "�޷���ȡ�ô������Ĵ�����Ϣ����ֱ�Ӳ鿴��ϸ��Ϣ");
			} else{
				int l_flags;
				smRtMsg >> errmsg >> urmsg >> l_flags;
				*flags = l_flags;
			}
		} catch (...) {
			snprintf(errmsg, len, "��ȡ������Ϣʧ�ܣ���ֱ�Ӳ鿴��ϸ��Ϣ");
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
		if(flags == 1){ // 2015-9-18 ɽ��������Ϣ��ʾ�Ż����� ���Ϊ1ʱ RETURN_MSG �� DETAIL_MSG ����
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
         strcpy(errInfo->infoMsg, "����ɹ�!");
         
	if(errInfo->infoMsg[0] != 0){
		UPOS pos = utFind(uRet, "USER_MSG");
		if(pos != UPOS_END)
			utSetStr(uRet, pos, errInfo->infoMsg);
		else
			utAddStr(uRet, "USER_MSG", errInfo->infoMsg);
		L4C_DEBUG("set USER_MSG from errInfo->infoMsg");
	}
	// 20130620 by guanyf, ��ʧ�ܵĵ����м���errid, ������־�����Ӧ.
	if(retCode != 0){
		errid = errlog_generrid();
		strcpy(sRtMsg, utGetStr(uRet, "RETURN_MSG"));
		sprintf(sRtMsg+strlen(sRtMsg), " ERRID:%d", errid);
		UPOS pos = utFind(uRet, "RETURN_MSG");
		utSetStr(uRet, pos, sRtMsg);

		//������ƽ̨�ӿڣ� ͨ���ӿڻ���ͬ���ı��ر��滻������Ϣ
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
	 2014-1-21  by guanyf ���ڼ��� select BS_SERVICERULE_REL ��ִ�д����Ĳ��ԣ�
	  	  �����⵽����û�����ݣ� ��2�����ڲ��ٲ��
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
 * @inparam    psServiceName	tuxedo��������
 * @inparam    transb			tuxedoͨ�ô������
 * @inparam    psDbLabel		���ݿ����ӱ�ǩ
 * @inparam    psUtypeFunc		utype��������
 * @inparam    ptUtypeFuncPtr	utype������ַ
 * @inparam    iConnType		���ݿ����ӷ�ʽ,1������,0������
 * @inparam    iExFlags			��չ�ӿ�
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
	l4c_idenset(NULL, psServiceName); //������־��ʶ����������
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

		psDbLabel = useDBID(inParam_new.get(), psDbLabel, sDBLabelBuf, &inParam);// tuxʵ������������2013-2

		char emergencyLabel[64];
		psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for ����Ӧ��

		getUniAccept(inParam); //�����ȡͳһ��ˮ
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
			L4C_ERROR("�ڴ����ݿ�����ʧ��");
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
			//dbFactory.doBegin(); //���������ݿ�
			// ͨ��ѭ������һ�Σ� ����ÿ�ν������ʹ�� select 1 from dual ���������ӣ� ���ٸ�����ִ������
			// 2014-1-21 by guanyf ���ڸ�sql ���top 1��Ӧ��
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
					|| oerr.code == 28 || oerr.code == 1012  //alter session kill ��28�Ĵ�, �ٴη��ʾͱ�1012
				){
					L4C_DEBUG("==DB Test loop, code:%d msg:%s", oerr.code, oerr.msg);
					dbFactory.doBegin(); //���������ݿ�
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
		snprintf(retMsg, sizeof(retMsg) - 1, "DBERR ����%s : %s : %s",
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
		strcpy(retMsg, "δ֪��������ϵϵͳ����Ա!");
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
				strcpy(retMsg, "ת��utype�ṹ��XMLʧ�ܣ������Ƿ�ڵ����а������Ϸ��ַ�");
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
			int nmret = NMLogCallBack(psServiceName, // ��������
					&CtrlInfo, // ���������뼰���ݿ�����
					psDbLabel, //���ݿ��ǩ����
					psUtypeFunc, //�������BP����
					inParam, //�������Utype
					&tm_begin, //������ÿ�ʼʱ��
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
			L4C_TRACE("error error msg = [δ֪��������ϵϵͳ����Ա]");
		}
        try{ //�������ݿ������쳣ʱcore�� 2014-4-25
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
		throw(appException(304 * 1000000, "�ڴ����ʧ��"));
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
				"<?xml version=\"1.0\" encoding=\"GBK\" standalone=\"no\" ?><ROOT><RETURN_CODE type=\"long\">301000000</RETURN_CODE><RETURN_MSG type=\"string\">�޷��򿪲����������ļ�</RETURN_MSG></ROOT>");
	printf(all);
	tpreturn(TPSUCCESS, 0,
			strcpy((char*) tpalloc((char*) "STRING", NULL, strlen(all)), all),
			strlen(all), 0);
}

//�򻯰汾�ĺ���,  �� dotuxadp �Ĳ������£�
//1. ���Զ���ϲ������������ʹ���Դ��ģ�����һ����Σ�
//2. ������ҵ�����doRule��
//3. �����ý��������Powerfilter
//4. ��ȫ��ʹ���ڴ����ݿ�
void dotuxadp1(char **obuf, int* obufLen, const char *psServiceName,
		TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr, int iConnType) {

	struct timeval tm_begin;
	int errid;
	gettimeofday(&tm_begin, NULL);
	l4c_set_uniaccept(NULL);

	initLogEnv();
	l4c_idenset(NULL, psServiceName); //������־��ʶ����������
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

		psDbLabel = useDBID(inParam_new.get(), psDbLabel, sDBLabelBuf, &inParam);// tuxʵ������������2013-2
		char emergencyLabel[64];
		psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for ����Ӧ��

		getUniAccept(inParam); //�����ȡͳһ��ˮ
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

		dbFactory.doBegin(); //���������ݿ�
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
		snprintf(retMsg, sizeof(retMsg) - 1, "DBERR ����%s : %s : %s",
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
		strcpy(retMsg, "δ֪��������ϵϵͳ����Ա!");
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
				strcpy(retMsg, "ת��utype�ṹ��XMLʧ�ܣ������Ƿ�ڵ����а������Ϸ��ַ�");
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
			int nmret = NMLogCallBack(psServiceName, // ��������
					&CtrlInfo, // ���������뼰���ݿ�����
					psDbLabel, //���ݿ��ǩ����
					psUtypeFunc, //�������BP����
					inParam, //�������Utype
					&tm_begin, //������ÿ�ʼʱ��
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
			L4C_TRACE("error error msg = [δ֪��������ϵϵͳ����Ա]");
		}
        try{ //�������ݿ������쳣ʱcore�� 2014-4-25
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
		//��Ϊ����ֱ�ӿ�����ӵ�ģʽ
		return AssiMutiConnWork_old(in, errInfo, ptUtypeFuncPtr, ptDoMerge, psDbLabel, iConnType);
	}
	L4C_DEBUG("service_name[%s]", service_name);
	strcpy(svc_name, service_name);
	ptr = strchr(svc_name, ',');
	if(ptr != NULL){
		//�����д���·�ɵģ� ֱ�Ӵ�����ȡ
		if(CSF_getInputHeader() != NULL){
			//���ȫ�ֱ�������header�����ñ����е�
			*ptr = 0;
		}else{
			*ptr = 0;
			route_type = ptr+1;
			ptr = strchr((char *)route_type, ',');
			if(ptr == NULL){
				route_type = NULL; //��������
			}else{
				*ptr = 0;
				route_value = ptr+1;
			}
		}
	}else{
		//ʹ��Ĭ��·��ֵ
		route_type = cfgGetStr("AssiMutiConnWork", "_defRouteType");
		route_value = cfgGetStr("AssiMutiConnWork", "_defRouteValue");
	}

	// 2013-12-9 by guanyf ��Ϊֱ��tpcall
	uret = tuxcal(svc_name, in, 0, NULL, 0);
	//uret = pCallESBApi(in, svc_name, route_type, route_value, 1, 5, 10);

	// �����쳣
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
	//���ȥ����ͷ
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
	int flag_1;   //���ú���ѡ�� 0-dotuxadp  1-dotuxadp1
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
	// iConnType | 0x03 �ĺ�����Ҫͨ��iConnType �����ݵ��� dotuxadp1 �ı�ʶ
	TUXADPEX(psServiceName, transb, psDbLabel, psUtypeFunc, ptUtypeFuncPtr, doMerge, iConnType | 0x03);
}

/* avoid mem leak
 20111102 step 5 start :
 void tuxadpEx(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel,
 const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType)
 20111102 step 5 end :

2015-3-9: �����˼���ҵ�����ջʹ�����Ĵ��룬 �������ֻ���ڲ��ԣ��ڲ��Ի�����ֻ�ǻ������� STACK_SIZE=n ����λMB��Ϊ����
   �ⲿ�ֵ�ͳһ�����TUXADPEX �У� Ϊ�˼���dotuxadp1, ͨ�� iConnType�����ݱ�ʶ: iConnType & 0x03 > 0 �����dotuxadp1
2015-3-9�� �Ĵ����Ի���Ҫ��ǿ��ʹ�����ݿ�����ӵ����� ����ǽ�ж��������ӵ��·�����
     ����ʹ�û��������� CSF_FORCE_SHORT_DBCONN , ֻҪ�иû�����������Ϊ���ش�
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
		p->iConnType = iConnType & 0x01; //ֻȡ���λ
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
		L4C_WARN("����[%s]δ�ͷ�utype�ڴ�������:%d", psServiceName,
				iUtypeMallocTimes - before);
	tpreturn(TPSUCCESS, 0, outbuf, outlen, 0);
}
