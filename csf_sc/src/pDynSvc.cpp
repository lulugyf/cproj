
#include "allBCP.h"

utype* cQDual(const utype * inParam,TCtrlInfo *errInfo);

utype* cD(const utype * inParam,TCtrlInfo *errInfo){
	return NULL;
}
utype* cC(const utype * inParam,TCtrlInfo *errInfo){
	return NULL;
}
utype* cB(const utype * inParam,TCtrlInfo *errInfo)
{
	CALLBP(cC, NULL, errInfo);
	CALLBP(cD, NULL, errInfo);
	return NULL;
}
utype* cA(const utype * inParam,TCtrlInfo *errInfo)
{
	CALLBP(cB, NULL, errInfo);
	return NULL;
}

utype* pMyTest1(const utype *inparam, TCtrlInfo *ptCtrlInfo)
{
	uAutoPtr p1(uInit(1));
	uAutoPtr p2(CALLBP(cQDual,inparam, ptCtrlInfo));

	char hello[64];
	sprintf(hello, "Hello %s", utGetStr(p2, "TODAY"));
	utAddStr(p1, "TODAY11", hello);
	CALLBP(cA, NULL, ptCtrlInfo);
	return p1.release();
}




utype* pubQuerySql(const utype *inparam, TCtrlInfo *errInfo);
utype* pDynSvc(const utype *inparam, TCtrlInfo *ptCtrlInfo)
{
    LOG_FUNC("BP", inparam, ptCtrlInfo, NULL);


	uAutoPtr pp(uInit(2)), pIn(utClone(inparam));
	char sDynStatement[1024];
	L4C_TRACE("fetch sql000000000000000000000");
	printf("SVC_NAME==%s", utGetStr(inparam,"SVC_NAME"));

	long lErrCode=0;
	char sErrMsg[4096];
	memset(sErrMsg,0,sizeof(sErrMsg));
try{
	L4C_TRACE("fetch sql");
	otl_nocommit_stream getStatement(10,"select dyn_statement from bs_DynSrv_dict where svc_name =:svc_name<char[40]> and qm_type='0'", GETDB(ptCtrlInfo));
	L4C_TRACE("fetch sql11111111111111111111111");

	//utGetStr(inparam,"SVC_NAME");

	getStatement << utGetStr(inparam,"SVC_NAME");
	/*if(getStatement.eof()){
		throw(appException(100001, "指定的sql语句不存在"));
	}
	*/
	getStatement>>sDynStatement;
}
catch(otl_exception& otlErr)
{

	lErrCode = 302*1000000 + abs(otlErr.code);
	snprintf(sErrMsg, sizeof(sErrMsg) - 1,"DBERR 错误：%s : %s : %s",otlErr.msg,otlErr.stm_text,otlErr.var_info);
	printf("#########%s", sErrMsg);
 }
 catch(uException& err)
{
	lErrCode = 303*1000000+err.errCode;
	strncpy(sErrMsg,err.errMsg, sizeof(sErrMsg) - 1);
	printf("####bbb#####%s", sErrMsg);
}
catch(appException& appErr)
{
	lErrCode = appErr.errCode;
	strncpy(sErrMsg,appErr.errMsg, sizeof(sErrMsg) - 1);
	printf("####ccc#####%s", sErrMsg);
}
	catch(std::exception& err)
{
	lErrCode = 101*1000000;
	strncpy(sErrMsg, err.what(), sizeof(sErrMsg) - 1);
	printf("####ddd#####%s", sErrMsg);
}
	catch(...)
{
	lErrCode = 201*1000000;
	strcpy(sErrMsg,"未知错误请联系系统管理员!");
	printf("####eee#####%s", sErrMsg);
}

L4C_TRACE("fetch sql4444444");

	L4C_TRACE("parse sql[%s]",sDynStatement);
	utAddStr(pp, "__SQL", sDynStatement);
	utAddStruct(pp, "IN_DATA", pIn.release());
	strcpy(ptCtrlInfo->retMsg, "success");  //修改RETURN_MSG试试
	return pubQuerySql(pp, ptCtrlInfo);
}

utype* cTest1(const utype * inParam,TCtrlInfo *errInfo);


extern utype * json2utype(const char *str);
extern char * utype2json(const utype *pu);

utype* pMulTest(const utype *inparam, TCtrlInfo *ptCtrlInfo)
{
	const char *psDB = "dbchangea1,dbchangeb1";
	utype *r = AssiMutiConnWork(inparam, ptCtrlInfo, cTest1, NULL, psDB, 1);

	char *jstr = utype2json(r);
	printf("[%s]\n", jstr);
	free(jstr);
	return r;
}
// clxml sMulTest '{"ROOT":{"col1":2} }'
/*
 create table CSF1
(
  col1 INTEGER,
  col2 VARCHAR2(30)
);
insert table csf1 values(2, 'hehe');
 */

