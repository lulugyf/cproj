#include "framework.h"


#include <time.h>
#include <string>
#include <iostream>
#include <map>

using namespace std;

void* busiwork(void* v1, db_connect* pdb, bool isLong) ;
void sqlreplace(const char *sql, string &sql1, const utype *inparam);
utype* doMerge(map<string, void*>* m, TCtrlInfo* errInfo);
utype* pRuleCheck(const utype* puParamIn, TCtrlInfo* errInfo);

utype * json2utype(const char *str);

int test1()
{
	string s;
	const char *sql =
		"select 1 from table${ID_NO[-2:]}#{%Y%m} ${PHONE_NO[1:4]} ${PHONE_NO[1:-4]} ${PHONE_NO[:-2]} where rownum<2";
	uAutoPtr pp(uInit(1));
	//utype *p1 = uInit(1);
	//utAddStruct(pp, "IN_DATA", p1);
	utAddLong(pp, "ID_NO", 1234567L);
	utAddStr(pp, "PHONE_NO", "abcdefghijk");


	printf("ORG:[%s]\n", sql);
	LogUtype(pp);

	sqlreplace(sql, s, pp);
	printf("%s\n", s.c_str());
	return 0;
}


int testrule(const char *psDbLabel, const char* jsonin)
{
	db_factory dbFactory(false);

	uAutoPtr outParam;
	uAutoPtr in( json2utype(jsonin) );
	TCtrlInfoEx CtrlInfo;
	memset(&CtrlInfo, 0, sizeof(TCtrlInfoEx));
	map<string, void*> m;

	db_connect* dbcon = NULL;

	try {
		dbFactory.resetActive();
		dbcon = dbFactory.addConnect(psDbLabel);
		dbFactory.setActive(psDbLabel);
		CtrlInfo.maindb = &dbcon->getOtlHandle();
		CtrlInfo.db = CtrlInfo.maindb;
		CtrlInfo.bReconnFlag = false;
		CtrlInfo.mainmdb = NULL;
		CtrlInfo.mdb = NULL;
		CtrlInfo.func = NULL;
		CtrlInfo.input = in;

		dbFactory.doBegin();


		int iRuleId, iRuleOrder;
		string sPromptMsg;

		CtrlInfo.func = pRuleCheck;
		CtrlInfo.input = in;


		printf("====begin print INPUT:\n");
		LogUtype(in);
		printf("====end print INPUT\n");

		memset(&CtrlInfo, 0, sizeof(TCtrlInfo));
		L4C_TRACE("begin call busi func");
		dbFactory.doCall(m, busiwork, &CtrlInfo);

		printf("m.size: %d\n", m.size());
		if(m.size() > 0){
			outParam = doMerge(&m, &CtrlInfo);
		}

		if (CtrlInfo.infoMsg[0] != 0) {
			if (!sPromptMsg.empty())
				sPromptMsg += " ";
			sPromptMsg += CtrlInfo.infoMsg;
		}

		dbFactory.doEnd(false);

		printf("===OUT begin===\n");
		if(outParam != NULL)
			LogUtype(outParam);
		else
			printf("outParam: NULL!!!!!!\n");
		printf("===OUT end===\n");

	} catch (uException& err) {
		printf("uException: code:%d msg:%s\n",
				err.errCode, err.errMsg);
		return -1;
	} catch (otl_exception& otlErr) { // intercept OTL exceptions
		printf("otl_exception: code:%d DBERR 错误：%s : %s : %s\n",
				abs(otlErr.code), otlErr.msg, otlErr.stm_text, otlErr.var_info);
		return -1;
	} catch (appException& appErr) {
		printf("appException: code:%d msg:%s\n",
				appErr.errCode, appErr.errMsg);
		return -1;
	}  catch (...) {
		printf("failed!!!!\n");
		return -1;
	}




	return 0;
}

int main(int argc, char *argv[]){
	// return test1();
	int ret = 0;

	if(argc > 2)
		ret = testrule(argv[1], argv[2]);
	else
		printf("nothing todo!\n");

	return ret;
}


/*
 *
./ruleck dbchangea1 '{"ROOT":{"svc_name":"sruletest","REQUEST_INFO":{"BUSI_INFO_LIST":{"BUSI_INFO":{"ID_NO":16310001009523}}}}}'





insert into bs_servicerule_rel(service_name, rule_id, rule_order)
 values('s1158Query', 57330004, 0);
insert into bs_ruleinparam_rel(rule_id, param_code, utype_path, unit_id)
  values(57330004, 1005, 'REQUEST_INFO.BUSI_INFO_LIST.BUSI_INFO.ID_NO', '');
insert into bs_paramcode_dict(param_code, pram_name, value_type, value_length, param_desc)
 values(1005, 'ID_NO', 3, 14, '用户标识');
insert into bs_rulefactorgroup_rel(rule_id, group_id, group_order)
  values(57330004, 57330005, 0);
insert into bs_factorgroup_dict(group_id, group_desc, group_type)
  values(57330005, '骚扰停机不允许受理', 0);
insert into bs_groupfactor_rel(group_id, factor_id, factor_order)
  values(57330005, 57330005, 0);
insert into bs_rulefactor_dict(factor_id, param_code, operator_id, value1, value2, factor_desc, param_note)
 values(57330005, 1005, 10, 'select * from ur_User_info where  run_code = '''Q''' and id_no=:ID_NO<long>',
 0, '骚扰电话', '1005');


select * from ur_custuser_rel
select * from ur_user_info phone_no='13835013680' id_no=72050810160

create table test_usr_60(phone_no char(15) , b int)



 value_type:
    2: int
    3: long
    4: double
    5: string

operator_id:
    0: ==
    1: !=
    2: >
    3: <
    4: >=
    5: <=
    6: between
    7: like
    8: in
    9: not in
    10: sql  if has result then return false
*/
