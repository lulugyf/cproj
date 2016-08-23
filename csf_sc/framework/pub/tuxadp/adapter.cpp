#include <alloca.h>
#include "framework.h"
#include "LogFunc.h"

#include "errlog.h"

#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

void Powerfilter(utype* pu_out, TCtrlInfo* errinfo, const utype* pu_in, const char* svc_name);

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
	if(strchr(psDbLabel, ',') != NULL)
		return psDbLabel; //������Ӳ�����
	try{
		dbid = str_toupper(utGetStr(inputHeader, "DB_ID"), curdbid_insensitive, sizeof(curdbid_insensitive));
		*puIn = utGetStruct(inParam, "BODY");
	} catch (uException& err) {
		return psDbLabel; //������޶�Ӧ���ֶΰ�ԭ�й�����
	}
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
	return ctrlInfo->func(ctrlInfo->input, ctrlInfo);
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


#define _LOG_FMT " rt_code:%ld,rt_msg:%s"


static size_t errcodeExplain(TCtrlInfo* errInfo, long errcode, char* errmsg,
		char* urmsg, size_t len) {
	urmsg[0] = 0;
	if (errcode == 0) {
		if(errInfo->retMsg[0] != 0){
			strncpy(errmsg, errInfo->retMsg, len-1);
			errmsg[len-1] = 0;
		}else{
			strcpy(errmsg, "ok!");
		}

		if(errInfo->infoMsg[0] != 0){
			strncpy(urmsg, errInfo->infoMsg, len-1);
			urmsg[len-1] = 0;
		}else{
			strcpy(urmsg, errmsg);
		}
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
			otl_stream smRtMsg(1,
					"select return_msg,CUST_CLASS_TIPS \
					from bs_returnmsg_dict a\
					where return_code = :RETURN_CODE<long>",
					GETDB(errInfo));
			smRtMsg << errcode;
			if (smRtMsg.eof()) {
				snprintf(errmsg, len, "�޷���ȡ�ô������Ĵ�����Ϣ����ֱ�Ӳ鿴��ϸ��Ϣ");
			} else
				smRtMsg >> errmsg >> urmsg;
		} catch (...) {
			snprintf(errmsg, len, "��ȡ������Ϣʧ�ܣ���ֱ�Ӳ鿴��ϸ��Ϣ");
		}
	}
	}
	if (urmsg[0] == 0)
		strcpy(urmsg, errmsg);
	return strlen(errmsg);
}

static int bindRetBuff(const char *psServiceName, int ruleErrFlag, TCtrlInfo* errInfo, utype *outParam,
		long retCode, char *retMsg, string& sPromptMsg, char **retBuff,
		int *retLen, char *outName = NULL, bool isXml = true) {
	int ul;
	int errid;
	char sRtMsg[4096];
	char sUrMsg[4096];
	uAutoPtr uRet(uInit(3));
	char *xmlstr;
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

	// 20130620 by guanyf, ��ʧ�ܵĵ����м���errid, ������־�����Ӧ.
	if(retCode != 0){
		errid = errlog_generrid();
		strcpy(sRtMsg, utGetStr(uRet, "RETURN_MSG"));
		sprintf(sRtMsg+strlen(sRtMsg), " ERRID:%d", errid);
		UPOS pos = utFind(uRet, "RETURN_MSG");
		utSetStr(uRet, pos, sRtMsg);
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
	//const XMLByte *xmlstr = uUType2Xml(uRet, 0, (char*)"ROOT");
	ul = strlen((char *) xmlstr) + 1;
	/*
    *retBuff = (char *) tpalloc((char*) "STRING", NULL, ul);
	strcpy(*retBuff, (char *) xmlstr);
	free(xmlstr);
	 */

	*retBuff = xmlstr;
	*retLen = ul;

	return errid;
}

utype* doRule(const char* svc_name, const utype* puParamIn, TCtrlInfo* errInfo,
		string& sPromptMsg) {
	int iRuleId;

	otl_nocommit_stream qSvcRule(1,
			"select rule_id from BS_SERVICERULE_REL where service_name=:SVC_NAME<char[15+1]> order  by rule_order",
			GETDB(errInfo));
	qSvcRule << svc_name;
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

utype* AssiMutiConnWork_callesb(const utype* in, const char *bpname)
{
	const char *service_name;
	long rcode;
	char *rmsg;
	utype *uret = NULL;

	L4C_DEBUG("bpname[%s]", bpname);
	service_name = cfgGetStr("AssiMutiConnWork", bpname);
	if(service_name[0] == 0){
		throw(appException(304 * 1000000 + 9001, "AssiMutiConnWork config not found"));
	}
	L4C_DEBUG("service_name[%s]", service_name);

	uret = pCallESBApi(in, service_name, NULL, NULL, 1, 5, 10);

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


/**
 * ��������ں���
 * @inparam    obuf             �������ָ��
 * @inparam    obufLen          ������ݳ���
 * @inparam    psServiceName	��������
 * @inparam    inputstr			��δ���xml �� json
 * @inparam    clientaddr       �����Ĳ������ͻ��˵�ַ, ����Ϊ NULL
 * @inparam    psDbLabel		���ݿ����ӱ�ǩ
 * @inparam    psUtypeFunc		utype��������
 * @inparam    ptUtypeFuncPtr	utype������ַ
 * @inparam    ptDoMerge	         ����ϲ��ص������� ����ΪNULL�� ��ʹ��Ĭ�ϵ� doMerge
 * @inparam    iConnType		���ݿ����ӷ�ʽ,1������,0������
 */
void adpt_entry(char **obuf,        //����, ��Ҫ�ⲿ�ͷ����ڴ�ռ�
		int* obufLen,              //���γ���
		const char *psServiceName, //��������
		char *inputstr,    //��δ���xml �� json
		char *clientaddr,  //�����Ĳ������ͻ��˵�ַ, ����Ϊ NULL
		const char *psDbLabel,     //���ݿ����ӱ�ǩ
		const char *psUtypeFunc,   // BP/BC ������
		TUtypeFuncPtr ptUtypeFuncPtr, // BP/BC �ĺ���ָ��
		TDoMerge ptDoMerge,   //����ϲ��ص������� ����ΪNULL�� ��ʹ��Ĭ�ϵ� doMerge
		int iConnType         //���ݿ��������ͣ�  1-������  0-������
		)
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
	TCtrlInfoEx CtrlInfo;
	char sDBLabelBuf[100];
	string sPromptMsg;
	db_connect* dbcon = NULL;
	bool isXml = true;
	retCode = 0;
	strcpy(retMsg, "OK!");

	dbFactory.resetActive();
	memset(&CtrlInfo, 0, sizeof(TCtrlInfoEx));
	try {
		ibuf = (char *) inputstr;
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

		if (clientaddr != NULL)
		{
			int _adlen = sizeof(CtrlInfo.cliWsnAddr);
			strncpy(CtrlInfo.cliWsnAddr, clientaddr, _adlen-1);
			CtrlInfo.cliWsnAddr[_adlen-1] = 0;
		}

		psDbLabel = useDBID(inParam_new.get(), psDbLabel, sDBLabelBuf, &inParam);// tuxʵ������������2013-2

		char emergencyLabel[64];
		psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for ����Ӧ��

		getUniAccept(inParam); //�����ȡͳһ��ˮ
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
		if (outParam != NULL) {
			Powerfilter(outParam, &CtrlInfo, inParam, psServiceName);
		}
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
				errid = bindRetBuff(psServiceName, iRuleErrFlag, &CtrlInfo, outParam.release(),
						retCode, retMsg, sPromptMsg, obuf, obufLen, outName,
						isXml);
				if (sPromptMsg != "")
					L4C_WARN("%s", sPromptMsg.c_str());
				L4C_TRACE("bindRetBuff output end");
			} catch (...) {
				retCode = 303 * 1000000;
				strcpy(retMsg, "ת��utype�ṹ��XMLʧ�ܣ������Ƿ�ڵ����а������Ϸ��ַ�");
				L4C_ERROR(_LOG_FMT, retCode, retMsg);
				errid = bindRetBuff(psServiceName, iRuleErrFlag, &CtrlInfo, NULL, retCode, retMsg,
						sPromptMsg, obuf, obufLen, NULL, isXml);
			}
		} else {
			L4C_ERROR("APPERR"_LOG_FMT, retCode, retMsg);
			errid = bindRetBuff(psServiceName, iRuleErrFlag, &CtrlInfo, tup.release(), retCode, retMsg,
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
					&tm_begin //������ÿ�ʼʱ��
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
		dbFactory.doEnd(retCode == 0);
#ifdef _USEDCI
		mdbc.doRollback();
#endif
		map<string, void*>::iterator iter;
		for (iter = m.begin(); iter != m.end(); iter++) {
			if (iter->second != NULL)
				uFree((utype*) iter->second);
		}
		L4C_BULLETIN("Service<%s> End", psServiceName);
	}

}


//�򻯰汾�ĺ���,  �� dotuxadp �Ĳ������£�
//1. ���Զ���ϲ������������ʹ���Դ��ģ�����һ����Σ�
//2. ������ҵ�����doRule��
//3. �����ý��������Powerfilter
//4. ��ȫ��ʹ���ڴ����ݿ�
void adpt_entry1(
		char **obuf,
		int* obufLen,
		const char *psServiceName,
		char *inputstr,
		char *clientaddr,
		const char *psDbLabel,
		const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr,
		int iConnType
		)
{
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
	TCtrlInfoEx CtrlInfo;
	char sDBLabelBuf[100];
	string sPromptMsg;
	db_connect* dbcon = NULL;
	bool isXml = true;
	retCode = 0;
	strcpy(retMsg, "OK!");
	dbFactory.resetActive();

	memset(&CtrlInfo, 0, sizeof(TCtrlInfoEx));
	try {
		ibuf = (char *) inputstr;
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

		if (clientaddr != NULL)
		{
			int _adlen = sizeof(CtrlInfo.cliWsnAddr);
			strncpy(CtrlInfo.cliWsnAddr, clientaddr, _adlen-1);
			CtrlInfo.cliWsnAddr[_adlen-1] = 0;
		}

		psDbLabel = useDBID(inParam_new.get(), psDbLabel, sDBLabelBuf, &inParam);// tuxʵ������������2013-2
		char emergencyLabel[64];
		psDbLabel = checkEmergency(psDbLabel, emergencyLabel); //add for ����Ӧ��

		getUniAccept(inParam); //�����ȡͳһ��ˮ
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
				errid = bindRetBuff(psServiceName, iRuleErrFlag, &CtrlInfo, outParam.release(),
						retCode, retMsg, sPromptMsg, obuf, obufLen, outName,
						isXml);
				if (sPromptMsg != "")
					L4C_WARN("%s", sPromptMsg.c_str());
				L4C_TRACE("bindRetBuff output end");
			} catch (...) {
				retCode = 303 * 1000000;
				strcpy(retMsg, "ת��utype�ṹ��XMLʧ�ܣ������Ƿ�ڵ����а������Ϸ��ַ�");
				L4C_ERROR(_LOG_FMT, retCode, retMsg);
				errid = bindRetBuff(psServiceName, iRuleErrFlag, &CtrlInfo, NULL, retCode, retMsg,
						sPromptMsg, obuf, obufLen, NULL, isXml);
			}
		} else {
			L4C_ERROR("APPERR"_LOG_FMT, retCode, retMsg);
			errid = bindRetBuff(psServiceName, iRuleErrFlag, &CtrlInfo, tup.release(), retCode, retMsg,
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
					&tm_begin //������ÿ�ʼʱ��
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
		dbFactory.doEnd(retCode == 0);
		map<string, void*>::iterator iter;
		for (iter = m.begin(); iter != m.end(); iter++) {
			if (iter->second != NULL)
				uFree((utype*) iter->second);
		}
		L4C_BULLETIN("Service<%s> End", psServiceName);
	}

}


