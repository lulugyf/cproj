#include "framework.h"


#include <dlfcn.h>
#include <iostream>
#include <string>
#include <time.h>




/*
����utype�����滻sql�ַ����еķ��Ų����� ����Ϊ���Դ��룺
	const char *sql =
		"select 1 from table${ID_NO[-2:]}#{%Y%m} ${PHONE_NO[1:4]} ${PHONE_NO[1:-4]} ${PHONE_NO[:-2]} where rownum<2";
	uAutoPtr pp(uInit(1));
	utAddLong(pp, "ID_NO", 1234567L);
	utAddStr(pp, "PHONE_NO", "abcdefghijk");
���н���� select 1 from table67201304 bcd bcdefg abcdefghi where rownum<2

 */
void sqlreplace(const char *sql,
		string &sql1, const utype *inparam);

utype* doQuerySqlFix(const char* sql, const utype *inparam, TCtrlInfo *errInfo);

utype* callOther(int modid, const utype* puParamIn, TCtrlInfo* errInfo);

utype* getAllParam(int iRuleId, const utype* puParamIn, TCtrlInfo* errInfo, map<int, pair<int, string> >& m);

utype* My_getAllParam(int iRuleId,
		const utype* puParamIn,
		TCtrlInfo* errInfo,
		map<int, pair<int, string> >& m);


size_t fGetRealValue(const utype* pu, TCtrlInfo* errInfo, const char* sParamName, char* buf, size_t len);

void rtmsgReplace(char* s, const utype* pu, TCtrlInfo* errInfo);


int op_in(const char *in, char *set);

bool logicJudge(int iOperateId, char* value1, char* value2, int iValueType, const char* sParamPath, const utype* puParamIn, TCtrlInfo *errInfo);


static void My_getRtMsg(
		int iRuleGroup, int iGroupType, const utype *uRuleInput,
		utype *uo, int &iUnitId, long &lRetCode, TCtrlInfo* errInfo)
{
	long lReturnCode;
	char sReturnMsg[256];
	//int  iUnitId;
	char sFileName[256];
	char sBPName[256];
	char sAdviceMsg[256];
	char sCustTips[256];
	otl_nocommit_stream qRuleRtMsg(1,
		"SELECT a.return_code, b.return_msg, nvl(unit_id, -1), \
		b.FILE_NAME, b.BP_NAME, b.ADVICE_MSG, b.CUST_CLASS_TIPS\
		  FROM bs_groupretmsg_info a, bs_returnmsg_dict b\
		 WHERE a.return_code = b.return_code  AND group_id = :RULE_GROUP<int>",
		  GETDB(errInfo));
	qRuleRtMsg<<iRuleGroup;
	if (qRuleRtMsg.eof())
		throw(appException(399000008, "ָ���Ĺ����޶�Ӧ�Ĵ�������������Ϣ"));
	qRuleRtMsg >>lReturnCode >>sReturnMsg >>iUnitId
		>>sFileName >> sBPName >> sAdviceMsg >> sCustTips;

	if(sReturnMsg[0] != 0){
		rtmsgReplace(sReturnMsg, uRuleInput, errInfo);
	}
	lRetCode = lReturnCode;
	if(iGroupType){
		// �� 0 ������ʾ����
		utAddLong(uo, "RETURN_CODE", 0L);
		utAddStr(uo, "RETURN_MSG", "Success");
		utAddStr(uo, "PROMPT_MSG", sReturnMsg);
	}else{
		utAddLong(uo, "RETURN_CODE", lReturnCode);
		utAddStr(uo, "RETURN_MSG", sReturnMsg);
		utAddStr(uo, "FILE_NAME", sFileName);
		utAddStr(uo, "BP_NAME", sBPName);
		utAddStr(uo, "ADVICE_MSG", sAdviceMsg);
		utAddStr(uo, "CUST_CLASS_TIPS", sCustTips);
	}
}

// ����ֵ: true ������, false ������
static long doBusiRuleAll(int iRuleId,
		const utype* puParamIn, utype *uOut, TCtrlInfo* errInfo)
{
	string sPromptMsg;
	char sRuleName[64];
	char sGroupDesc[256];
	map<int, pair<int, string> > mParamTxt;
	memset(errInfo, 0, sizeof(TCtrlInfo));
	long lRet = 0L;
	
	otl_nocommit_stream qRuleID(1,
		"SELECT   rule_id, rule_name\
	     FROM bs_busirule_dict \
	     WHERE  rule_id =:RULE_ID<int>", GETDB(errInfo));
									   
	qRuleID<<iRuleId;
	if(qRuleID.eof())
		throw(appException(399000006, "RULE_ID������"));
	qRuleID >> iRuleId >> sRuleName;
	
	uAutoPtr uRuleInput(My_getAllParam(iRuleId, puParamIn, errInfo, mParamTxt));
	int iRuleGroup, iGroupType;
	
	otl_nocommit_stream qRule(10,
			"SELECT  b.group_id, c.group_type, c.group_desc\
		FROM  bs_rulefactorgroup_rel b, bs_factorgroup_dict c \
	   WHERE  b.group_id = c.group_id\
			 AND b.rule_id =:RULE_ID<int>\
	         ORDER BY b.group_order",
	         GETDB(errInfo));
	qRule << iRuleId;

	while (!qRule.eof()){
		qRule >> iRuleGroup >> iGroupType >> sGroupDesc;
		bool bCurGroup=true;
		otl_nocommit_stream qRuleSerial(10, 
		"SELECT   operator_id, value1, value2, NVL(param_code, -1)\
		    FROM bs_rulefactor_dict a,\
		         bs_factorgroup_dict c,\
		         bs_groupfactor_rel d\
		   WHERE c.group_id = :RULE_GROUP<int>\
		     AND d.group_id = c.group_id\
		     AND a.factor_id = d.factor_id\
		ORDER BY d.factor_order", GETDB(errInfo));
		qRuleSerial<<iRuleGroup;
		printf("\n===iRuleId:%d sRuleName:%s iRuleGroup:%d sGroupDesc:%s\n",
				iRuleId, sRuleName, iRuleGroup, sGroupDesc);

		uAutoPtr uo(uInit(3));
		utAddInt(uo, "RULEID", iRuleId);
		utAddStr(uo, "RULENAME", sRuleName);
		utAddInt(uo, "GROUPID", iRuleGroup);
		utAddStr(uo, "GROUPNAME", sGroupDesc);

		while(!qRuleSerial.eof()){
			int iOperateId, iParamCode;
			char value1[1024+1];
			char value2[1024+1];
			qRuleSerial >>iOperateId >>value1 >>value2 >>iParamCode;
			map<int, pair<int, string> >::iterator fi
				= mParamTxt.find(iParamCode);
			if(fi==mParamTxt.end() && iOperateId!=10){
				char sParamCode[10];
				sprintf(sParamCode, "%d", iParamCode);
				throw(appException(399000007, "��������[%s]δ����", sParamCode, NULL));
			}
			if(!logicJudge(iOperateId, value1, value2, fi->second.first, fi->second.second.c_str(), uRuleInput, errInfo)){
				bCurGroup=false;
				break;
			}
		}
		if(bCurGroup){
			long lReturnCode;
			int iUnitId;


			My_getRtMsg(iRuleGroup, iGroupType, uRuleInput,
					uo, iUnitId, lReturnCode, errInfo);
			if(iUnitId != -1){
				utAddStruct(uRuleInput, "IN_DATA", utClone(puParamIn));
				utAddStruct(uo, "OUT_DATA",  callOther(iUnitId, uRuleInput, errInfo));
			}
			if(!iGroupType)
				lRet = lReturnCode;
		}else{
			utAddLong(uo, "RETURN_CODE", 0L);
			utAddStr(uo, "RETURN_MSG", "Success");
		}
		utAddStruct(uOut, "CheckResult", uo.release());
	}

	return lRet;
}

utype* pRuleCheck(const utype* puParamIn, TCtrlInfo* errInfo)
{
	int iRuleId;

	char *svc_name;
	long retCode = 0;
	char retMsg[1024];
	bool iRuleErrFlag = true;

	strcpy(retMsg, "Success");
	svc_name = utGetStr(puParamIn, "svc_name");
	uAutoPtr uOut(uInit(1));

	otl_nocommit_stream qSvcRule(1,
			"select rule_id from BS_SERVICERULE_REL "
			" where service_name=:SVC_NAME<char[15+1]>"
			" order  by rule_order",
			GETDB(errInfo));
	qSvcRule << svc_name;
	long lLastRestrictCode = 0L;
	while (!qSvcRule.eof()) {
		qSvcRule >> iRuleId;
		lLastRestrictCode =
				doBusiRuleAll(iRuleId, puParamIn, uOut, errInfo);
	}
	utAddLong(uOut, "RETURN_CODE", lLastRestrictCode);
	utAddStr(uOut, "RETURN_MSG", retMsg);

	return uOut.release();
}

/*
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
�����ʽ˵����
err:
֮���Ǳ��
{"RETURN_CODE": n,    # 0 Ϊ��ҵ������  ;  ��0, ��ҵ������,����һ�����Ƶ�ҵ�����
 "RETURN_MSG" : "",   # ������Ϣ
 "CheckResult":[
 	 {
 	 	 "RULEID":n,
 	 	 "RULENAME":"",
 	 	 "GROUPID":n,
 	 	 "GROUPNAME":"",
 	 	 "RETURN_CODE":n,
 	 	 "RETURN_MSG": "",
 	 	 "FILE_NAME":"",
 	 	 "BP_NAME":"",
 	 	 "ADVICE_MSG":"",
 	 	 "CUST_CLASS_TIPS":""
 	 },
 	 {}
 	 ...
 	 ]
}


 */
