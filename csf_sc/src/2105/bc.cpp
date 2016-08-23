///////////////// Input parameters ////////////////
// @	STRUCT
// -@0	LONG	CUST_ID
////////////////////////////////////////////////////
///////////////// Output parameters ////////////////
// @	STRUCT
// -@0	CUST_ID	LONG
// -@1	TYPE_CODE	INT
// -@2	CUST_NAME	STRING
// -@3	CUST_LEVEL	STRING
// -@4	ID_TYPE	STRING
// -@5	ID_ICCID	STRING
// -@6	ID_ADDRESS	STRING
// -@7	ID_VALIDDATE	STRING
// -@8	ADMIN_LEVEL	INT
// -@9	STATUS_CODE	INT
// -@10	STATUS_TIME	STRING
// -@11	ADDRESS_ID	INT
// -@12	EXTERN_ADDRESS	STRING
// -@13	CUST_ADDRESS	STRING
// -@14	CUST_POST	STRING
// -@15	CREATE_LOGIN	STRING
// -@16	CREATE_TIME	STRING
// -@17	GROUP_ID	STRING
// -@18	SERVICE_GROUP	STRING
// -@19	OWNED_CHNL_ID	STRING
// -@20	EMP_ID	STRING
// -@21	EMP_GROUP	STRING
// -@22	CUST_CD	STRING
// -@23	DEFAULT_LANG	STRING
// -@24	CARD_TYPE	INT
// -@25	VIP_FLAG	STRING
// -@26	VIP_CARD_NO	STRING
// -@27	VIP_CREATE_TYPE	INT
// -@28	SIGN_FLAG	STRING
// -@29	TRUE_FLAG	STRING
// -@30	FINISH_FLAG	STRING
// -@31	OP_TIME	STRING
// -@32	LOGIN_NO	STRING
// -@33	LOGIN_ACCEPT	LONG
// -@34	OP_CODE	STRING
// -@35	CREATE_NOTE	STRING
////////////////////////////////////////////////////
#include <allBCP.h>

using namespace std;

utype* cQCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo)
{

    LOG_FUNC("BC", inParam, errInfo, NULL);

	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(inParam);
	L4C_TRACE("------==INPUT END==-------");
	if(errInfo){
		memset(errInfo,0,sizeof(TCtrlInfo));
	}

	uAutoPtr uap(uInit(0));

	int rpcRows=0;
	otl_nocommit_stream sm_cQCustInfoByCustId;


	sm_cQCustInfoByCustId.set_flush(false);
  sm_cQCustInfoByCustId.open(1,"SELECT  CUST_ID,  TYPE_CODE,  CUST_NAME,  CUST_LEVEL,  ID_TYPE,  ID_ICCID,  ID_ADDRESS,  to_char(ID_VALIDDATE\
	,'YYYYMMDDHH24MISS') AS ID_VALIDDATE,  ADMIN_LEVEL,  STATUS_CODE,  to_char(STATUS_TIME,'YYYYMMDDHH24MISS'\
	) AS STATUS_TIME,  ADDRESS_ID,  EXTERN_ADDRESS,  CUST_ADDRESS,  CUST_POST,  CREATE_LOGIN,  to_char(CREATE_TIME\
	,'YYYYMMDDHH24MISS') AS CREATE_TIME,  GROUP_ID,  SERVICE_GROUP,  OWNED_CHNL_ID,  EMP_ID,  EMP_GROUP,\
	  CUST_CD,  DEFAULT_LANG,  CARD_TYPE,  VIP_FLAG,  VIP_CARD_NO,  VIP_CREATE_TYPE,  SIGN_FLAG,  TRUE_FLAG\
	,  FINISH_FLAG,  to_char(OP_TIME,'YYYYMMDDHH24MISS') AS OP_TIME,  LOGIN_NO,  LOGIN_ACCEPT,  OP_CODE,\
	  CREATE_NOTE, CUST_NAME_ENCRYPT FROM CT_CUST_INFO   WHERE CUST_ID=:CUST_ID<long> ",GETDB(errInfo));


	if(utGetEmpty(inParam,"CUST_ID"))
		sm_cQCustInfoByCustId<<otl_null();
	else
		sm_cQCustInfoByCustId<<utGetLong(inParam,"CUST_ID");

	sm_cQCustInfoByCustId.flush();

	while(!sm_cQCustInfoByCustId.eof()){
		long f0;
		int f1;
		char f2[100+1];
		char f3[3+1];
		char f4[2+1];
		char f5[50+1];
		char f6[128+1];
		char f7[14+1];
		int f8;
		int f9;
		char f10[14+1];
		int f11;
		char f12[128+1];
		char f13[128+1];
		char f14[6+1];
		char f15[20+1];
		char f16[14+1];
		char f17[10+1];
		char f18[10+1];
		char f19[10+1];
		char f20[14+1];
		char f21[10+1];
		char f22[30+1];
		char f23[3+1];
		int f24;
		char f25[1+1];
		char f26[30+1];
		int f27;
		char f28[1+1];
		char f29[1+1];
		char f30[1+1];
		char f31[14+1];
		char f32[20+1];
		long f33;
		char f34[5+1];
		char f35[128+1];
		char f36[400+1];		


		sm_cQCustInfoByCustId>>f0;
		if(sm_cQCustInfoByCustId.is_null())
			utAddEmpty(uap,"CUST_ID");
		else
			utAddLong(uap,"CUST_ID",f0);

		sm_cQCustInfoByCustId>>f1;
		if(sm_cQCustInfoByCustId.is_null())
			utAddEmpty(uap,"TYPE_CODE");
		else
			utAddInt(uap,"TYPE_CODE",f1);

		sm_cQCustInfoByCustId>>f2;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"CUST_NAME","");
		else
			utAddStr(uap,"CUST_NAME",Rtrim(f2));

		sm_cQCustInfoByCustId>>f3;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"CUST_LEVEL","");
		else
			utAddStr(uap,"CUST_LEVEL",Rtrim(f3));

		sm_cQCustInfoByCustId>>f4;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"ID_TYPE","");
		else
			utAddStr(uap,"ID_TYPE",Rtrim(f4));

		sm_cQCustInfoByCustId>>f5;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"ID_ICCID","");
		else
			utAddStr(uap,"ID_ICCID",Rtrim(f5));

		sm_cQCustInfoByCustId>>f6;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"ID_ADDRESS","");
		else
			utAddStr(uap,"ID_ADDRESS",Rtrim(f6));

		sm_cQCustInfoByCustId>>f7;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"ID_VALIDDATE","");
		else
			utAddStr(uap,"ID_VALIDDATE",Rtrim(f7));

		sm_cQCustInfoByCustId>>f8;
		if(sm_cQCustInfoByCustId.is_null())
			utAddEmpty(uap,"ADMIN_LEVEL");
		else
			utAddInt(uap,"ADMIN_LEVEL",f8);

		sm_cQCustInfoByCustId>>f9;
		if(sm_cQCustInfoByCustId.is_null())
			utAddEmpty(uap,"STATUS_CODE");
		else
			utAddInt(uap,"STATUS_CODE",f9);

		sm_cQCustInfoByCustId>>f10;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"STATUS_TIME","");
		else
			utAddStr(uap,"STATUS_TIME",Rtrim(f10));

		sm_cQCustInfoByCustId>>f11;
		if(sm_cQCustInfoByCustId.is_null())
			utAddEmpty(uap,"ADDRESS_ID");
		else
			utAddInt(uap,"ADDRESS_ID",f11);

		sm_cQCustInfoByCustId>>f12;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"EXTERN_ADDRESS","");
		else
			utAddStr(uap,"EXTERN_ADDRESS",Rtrim(f12));

		sm_cQCustInfoByCustId>>f13;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"CUST_ADDRESS","");
		else
			utAddStr(uap,"CUST_ADDRESS",Rtrim(f13));

		sm_cQCustInfoByCustId>>f14;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"CUST_POST","");
		else
			utAddStr(uap,"CUST_POST",Rtrim(f14));

		sm_cQCustInfoByCustId>>f15;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"CREATE_LOGIN","");
		else
			utAddStr(uap,"CREATE_LOGIN",Rtrim(f15));

		sm_cQCustInfoByCustId>>f16;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"CREATE_TIME","");
		else
			utAddStr(uap,"CREATE_TIME",Rtrim(f16));

		sm_cQCustInfoByCustId>>f17;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"GROUP_ID","");
		else
			utAddStr(uap,"GROUP_ID",Rtrim(f17));

		sm_cQCustInfoByCustId>>f18;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"SERVICE_GROUP","");
		else
			utAddStr(uap,"SERVICE_GROUP",Rtrim(f18));

		sm_cQCustInfoByCustId>>f19;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"OWNED_CHNL_ID","");
		else
			utAddStr(uap,"OWNED_CHNL_ID",Rtrim(f19));

		sm_cQCustInfoByCustId>>f20;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"EMP_ID","");
		else
			utAddStr(uap,"EMP_ID",Rtrim(f20));

		sm_cQCustInfoByCustId>>f21;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"EMP_GROUP","");
		else
			utAddStr(uap,"EMP_GROUP",Rtrim(f21));

		sm_cQCustInfoByCustId>>f22;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"CUST_CD","");
		else
			utAddStr(uap,"CUST_CD",Rtrim(f22));

		sm_cQCustInfoByCustId>>f23;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"DEFAULT_LANG","");
		else
			utAddStr(uap,"DEFAULT_LANG",Rtrim(f23));

		sm_cQCustInfoByCustId>>f24;
		if(sm_cQCustInfoByCustId.is_null())
			utAddEmpty(uap,"CARD_TYPE");
		else
			utAddInt(uap,"CARD_TYPE",f24);

		sm_cQCustInfoByCustId>>f25;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"VIP_FLAG","");
		else
			utAddStr(uap,"VIP_FLAG",Rtrim(f25));

		sm_cQCustInfoByCustId>>f26;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"VIP_CARD_NO","");
		else
			utAddStr(uap,"VIP_CARD_NO",Rtrim(f26));

		sm_cQCustInfoByCustId>>f27;
		if(sm_cQCustInfoByCustId.is_null())
			utAddEmpty(uap,"VIP_CREATE_TYPE");
		else
			utAddInt(uap,"VIP_CREATE_TYPE",f27);

		sm_cQCustInfoByCustId>>f28;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"SIGN_FLAG","");
		else
			utAddStr(uap,"SIGN_FLAG",Rtrim(f28));

		sm_cQCustInfoByCustId>>f29;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"TRUE_FLAG","");
		else
			utAddStr(uap,"TRUE_FLAG",Rtrim(f29));

		sm_cQCustInfoByCustId>>f30;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"FINISH_FLAG","");
		else
			utAddStr(uap,"FINISH_FLAG",Rtrim(f30));

		sm_cQCustInfoByCustId>>f31;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"OP_TIME","");
		else
			utAddStr(uap,"OP_TIME",Rtrim(f31));

		sm_cQCustInfoByCustId>>f32;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"LOGIN_NO","");
		else
			utAddStr(uap,"LOGIN_NO",Rtrim(f32));

		sm_cQCustInfoByCustId>>f33;
		if(sm_cQCustInfoByCustId.is_null())
			utAddEmpty(uap,"LOGIN_ACCEPT");
		else
			utAddLong(uap,"LOGIN_ACCEPT",f33);

		sm_cQCustInfoByCustId>>f34;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"OP_CODE","");
		else
			utAddStr(uap,"OP_CODE",Rtrim(f34));

		sm_cQCustInfoByCustId>>f35;
		if(sm_cQCustInfoByCustId.is_null())
			utAddStr(uap,"CREATE_NOTE","");
		else
			utAddStr(uap,"CREATE_NOTE",Rtrim(f35));		
		
/*        
		if(strcmp(province_group_in, "10017") == 0)
		{
			sm_cQCustInfoByCustId>>f36;
			if(sm_cQCustInfoByCustId.is_null())
				utAddStr(uap,"CUST_NAME_ENCRYPT","");
			else
				utAddStr(uap,"CUST_NAME_ENCRYPT",Rtrim(f36));
		}
*/
		rpcRows++;
		break;
	}
	if(errInfo){
		errInfo->iSqlRows = rpcRows;
	}
	L4C_TRACE("------==OUTPUT BEGIN==-------");
	LogUtype(uap);
	L4C_TRACE("------==OUTPUT END==-------");
	return(uap.release());
}


///////////////// Input parameters ////////////////
// @	STRUCT
// -@0	LONG	CUST_ID
////////////////////////////////////////////////////
///////////////// Output parameters ////////////////
// @	STRUCT
// -@0	CUST_ID	LONG
// -@1	UNIT_ID	LONG
// -@2	GROUP_TYPE	INT
// -@3	SCOPE_CODE	INT
// -@4	TRADE_CODE	STRING
// -@5	TRADE_DETAIL	STRING
// -@6	ENT_TYPE	INT
// -@7	ENT_CODE	STRING
// -@8	AREA_TYPE	INT
// -@9	FAX	STRING
// -@10	UNIT_HOMEPAGE	STRING
// -@11	UNIT_LEADER	STRING
// -@12	MANAGE_AREA	STRING
// -@13	REGISTER_ADDRESS	STRING
// -@14	REGISTER_BANKROLL	STRING
// -@15	YEAR_TURNOVER	STRING
// -@16	YEAR_GAIN	STRING
// -@17	TOP_DEPUTY_NAME	STRING
// -@18	TOP_DEPUTY_PHONE	STRING
// -@19	UNIT_CREATE_DAY	STRING
// -@20	LICENSE_NUMBER	STRING
// -@21	SIGN_DATE	STRING
// -@22	LICENSE_VALIDATE	STRING
// -@23	INSTITUTION_TYPE	STRING
// -@24	BANK_NAME	STRING
// -@25	BANK_ACCOUNT_NO	STRING
// -@26	VALID_FLAG	STRING
// -@27	REVOKE_DATE	STRING
// -@28	INFORMATION_FLAG	STRING
// -@29	NATIONAL_UNIT_CODE	STRING
// -@30	UNIT_PAY_NO	STRING
// -@31	UNIT_PHOTO	STRING
// -@32	UNIT_SIGN	STRING
// -@33	STATUS_CODE	STRING
// -@34	FINISH_FLAG	STRING
// -@35	OP_TIME	STRING
// -@36	LOGIN_ACCEPT	LONG
// -@37	LOGIN_NO	STRING
// -@38	OP_CODE	STRING
// -@39	NOTE	STRING
// -@40	LEAVE_DATE	STRING
// -@41	CREDIT_GRADE	STRING
// -@42	EMAIL_ADDRESS	STRING
// -@43	OPERATOR_PHONE	STRING
// -@44	GROUP_HQ_NAME	STRING
////////////////////////////////////////////////////
#include <allBCP.h>

using namespace std;

utype* cQGrpCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo)
{
    LOG_FUNC("BC", inParam, errInfo, NULL);

	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(inParam);
	L4C_TRACE("------==INPUT END==-------");
	if(errInfo){
		memset(errInfo,0,sizeof(TCtrlInfo));
	}

	uAutoPtr uap(uInit(0));

	int rpcRows=0;
	otl_nocommit_stream sm_cQGrpCustInfoByCustId;


	sm_cQGrpCustInfoByCustId.set_flush(false);
	sm_cQGrpCustInfoByCustId.open(1,"SELECT  CUST_ID, UNIT_ID, GROUP_TYPE, SCOPE_CODE, TRADE_CODE, TRADE_DETAIL, ENT_TYPE, ENT_CODE, AREA_TYPE\
		, FAX, UNIT_HOMEPAGE, decrypt_data(UNIT_LEADER) UNIT_LEADER, MANAGE_AREA, REGISTER_ADDRESS, REGISTER_BANKROLL, YEAR_TURNOVER, YEAR_GAIN\
		, decrypt_data(TOP_DEPUTY_NAME) TOP_DEPUTY_NAME, TOP_DEPUTY_PHONE, to_char(UNIT_CREATE_DAY, 'YYYYMMDDHH24MISS') UNIT_CREATE_DAY, decrypt_data(LICENSE_NUMBER) LICENSE_NUMBER\
		, to_char(SIGN_DATE, 'YYYYMMDDHH24MISS') SIGN_DATE, LICENSE_VALIDATE, INSTITUTION_TYPE, BANK_NAME, BANK_ACCOUNT_NO\
		, VALID_FLAG, to_char(REVOKE_DATE, 'YYYYMMDDHH24MISS') REVOKE_DATE, INFORMATION_FLAG, NATIONAL_UNIT_CODE\
		, UNIT_PAY_NO, UNIT_PHOTO, UNIT_SIGN, STATUS_CODE, FINISH_FLAG, to_char(OP_TIME, 'YYYYMMDDHH24MISS')\
		 OP_TIME, LOGIN_ACCEPT, LOGIN_NO, OP_CODE, NOTE, to_char(LEAVE_DATE, 'YYYYMMDDHH24MISS') LEAVE_DATE,\
		 CREDIT_GRADE,EMAIL_ADDRESS,OPERATOR_PHONE,GROUP_HQ_NAME,PRODUCT_TYPE \  
		FROM    CT_GRPCUST_INFO WHERE   CUST_ID=:CUST_ID<LONG>\
		 ",GETDB(errInfo));


	if(utGetEmpty(inParam,"CUST_ID"))
		sm_cQGrpCustInfoByCustId<<otl_null();
	else
		sm_cQGrpCustInfoByCustId<<utGetLong(inParam,"CUST_ID");

	sm_cQGrpCustInfoByCustId.flush();

	while(!sm_cQGrpCustInfoByCustId.eof()){
		long f0;
		long f1;
		int f2;
		int f3;
		char f4[8+1];
		char f5[20+1];
		int f6;
		char f7[60+1];
		int f8;
		char f9[60+1];
		char f10[60+1];
		char f11[60+1];
		char f12[512+1];
		char f13[100+1];
		char f14[100+1];
		char f15[100+1];
		char f16[100+1];
		char f17[20+1];
		char f18[20+1];
		char f19[14+1];
		char f20[30+1];
		char f21[14+1];
		char f22[20+1];
		char f23[10+1];
		char f24[60+1];
		char f25[30+1];
		char f26[5+1];
		char f27[14+1];
		char f28[2+1];
		char f29[20+1];
		char f30[30+1];
		char f31[1+1];
		char f32[128+1];
		char f33[1+1];
		char f34[1+1];
		char f35[14+1];
		long f36;
		char f37[20+1];
		char f38[5+1];
		char f39[255+1];
		char f40[14+1];
		char f41[1+1];
		char f42[60+1];
		char f43[30+1];
		char f44[255+1];
		char f45[8+1];


		sm_cQGrpCustInfoByCustId>>f0;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddEmpty(uap,"CUST_ID");
		else
			utAddLong(uap,"CUST_ID",f0);

		sm_cQGrpCustInfoByCustId>>f1;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddEmpty(uap,"UNIT_ID");
		else
			utAddLong(uap,"UNIT_ID",f1);

		sm_cQGrpCustInfoByCustId>>f2;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddEmpty(uap,"GROUP_TYPE");
		else
			utAddInt(uap,"GROUP_TYPE",f2);

		sm_cQGrpCustInfoByCustId>>f3;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddEmpty(uap,"SCOPE_CODE");
		else
			utAddInt(uap,"SCOPE_CODE",f3);

		sm_cQGrpCustInfoByCustId>>f4;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"TRADE_CODE","");
		else
			utAddStr(uap,"TRADE_CODE",Rtrim(f4));

		sm_cQGrpCustInfoByCustId>>f5;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"TRADE_DETAIL","");
		else
			utAddStr(uap,"TRADE_DETAIL",Rtrim(f5));

		sm_cQGrpCustInfoByCustId>>f6;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddEmpty(uap,"ENT_TYPE");
		else
			utAddInt(uap,"ENT_TYPE",f6);

		sm_cQGrpCustInfoByCustId>>f7;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"ENT_CODE","");
		else
			utAddStr(uap,"ENT_CODE",Rtrim(f7));

		sm_cQGrpCustInfoByCustId>>f8;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddEmpty(uap,"AREA_TYPE");
		else
			utAddInt(uap,"AREA_TYPE",f8);

		sm_cQGrpCustInfoByCustId>>f9;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"FAX","");
		else
			utAddStr(uap,"FAX",Rtrim(f9));

		sm_cQGrpCustInfoByCustId>>f10;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"UNIT_HOMEPAGE","");
		else
			utAddStr(uap,"UNIT_HOMEPAGE",Rtrim(f10));

		sm_cQGrpCustInfoByCustId>>f11;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"UNIT_LEADER","");
		else
			utAddStr(uap,"UNIT_LEADER",Rtrim(f11));

		sm_cQGrpCustInfoByCustId>>f12;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"MANAGE_AREA","");
		else
			utAddStr(uap,"MANAGE_AREA",Rtrim(f12));

		sm_cQGrpCustInfoByCustId>>f13;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"REGISTER_ADDRESS","");
		else
			utAddStr(uap,"REGISTER_ADDRESS",Rtrim(f13));

		sm_cQGrpCustInfoByCustId>>f14;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"REGISTER_BANKROLL","");
		else
			utAddStr(uap,"REGISTER_BANKROLL",Rtrim(f14));

		sm_cQGrpCustInfoByCustId>>f15;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"YEAR_TURNOVER","");
		else
			utAddStr(uap,"YEAR_TURNOVER",Rtrim(f15));

		sm_cQGrpCustInfoByCustId>>f16;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"YEAR_GAIN","");
		else
			utAddStr(uap,"YEAR_GAIN",Rtrim(f16));

		sm_cQGrpCustInfoByCustId>>f17;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"TOP_DEPUTY_NAME","");
		else
			utAddStr(uap,"TOP_DEPUTY_NAME",Rtrim(f17));

		sm_cQGrpCustInfoByCustId>>f18;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"TOP_DEPUTY_PHONE","");
		else
			utAddStr(uap,"TOP_DEPUTY_PHONE",Rtrim(f18));

		sm_cQGrpCustInfoByCustId>>f19;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"UNIT_CREATE_DAY","");
		else
			utAddStr(uap,"UNIT_CREATE_DAY",Rtrim(f19));

		sm_cQGrpCustInfoByCustId>>f20;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"LICENSE_NUMBER","");
		else
			utAddStr(uap,"LICENSE_NUMBER",Rtrim(f20));

		sm_cQGrpCustInfoByCustId>>f21;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"SIGN_DATE","");
		else
			utAddStr(uap,"SIGN_DATE",Rtrim(f21));

		sm_cQGrpCustInfoByCustId>>f22;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"LICENSE_VALIDATE","");
		else
			utAddStr(uap,"LICENSE_VALIDATE",Rtrim(f22));

		sm_cQGrpCustInfoByCustId>>f23;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"INSTITUTION_TYPE","");
		else
			utAddStr(uap,"INSTITUTION_TYPE",Rtrim(f23));

		sm_cQGrpCustInfoByCustId>>f24;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"BANK_NAME","");
		else
			utAddStr(uap,"BANK_NAME",Rtrim(f24));

		sm_cQGrpCustInfoByCustId>>f25;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"BANK_ACCOUNT_NO","");
		else
			utAddStr(uap,"BANK_ACCOUNT_NO",Rtrim(f25));

		sm_cQGrpCustInfoByCustId>>f26;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"VALID_FLAG","");
		else
			utAddStr(uap,"VALID_FLAG",Rtrim(f26));

		sm_cQGrpCustInfoByCustId>>f27;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"REVOKE_DATE","");
		else
			utAddStr(uap,"REVOKE_DATE",Rtrim(f27));

		sm_cQGrpCustInfoByCustId>>f28;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"INFORMATION_FLAG","");
		else
			utAddStr(uap,"INFORMATION_FLAG",Rtrim(f28));

		sm_cQGrpCustInfoByCustId>>f29;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"NATIONAL_UNIT_CODE","");
		else
			utAddStr(uap,"NATIONAL_UNIT_CODE",Rtrim(f29));

		sm_cQGrpCustInfoByCustId>>f30;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"UNIT_PAY_NO","");
		else
			utAddStr(uap,"UNIT_PAY_NO",Rtrim(f30));

		sm_cQGrpCustInfoByCustId>>f31;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"UNIT_PHOTO","");
		else
			utAddStr(uap,"UNIT_PHOTO",Rtrim(f31));

		sm_cQGrpCustInfoByCustId>>f32;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"UNIT_SIGN","");
		else
			utAddStr(uap,"UNIT_SIGN",Rtrim(f32));

		sm_cQGrpCustInfoByCustId>>f33;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"STATUS_CODE","");
		else
			utAddStr(uap,"STATUS_CODE",Rtrim(f33));

		sm_cQGrpCustInfoByCustId>>f34;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"FINISH_FLAG","");
		else
			utAddStr(uap,"FINISH_FLAG",Rtrim(f34));

		sm_cQGrpCustInfoByCustId>>f35;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"OP_TIME","");
		else
			utAddStr(uap,"OP_TIME",Rtrim(f35));

		sm_cQGrpCustInfoByCustId>>f36;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddEmpty(uap,"LOGIN_ACCEPT");
		else
			utAddLong(uap,"LOGIN_ACCEPT",f36);

		sm_cQGrpCustInfoByCustId>>f37;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"LOGIN_NO","");
		else
			utAddStr(uap,"LOGIN_NO",Rtrim(f37));

		sm_cQGrpCustInfoByCustId>>f38;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"OP_CODE","");
		else
			utAddStr(uap,"OP_CODE",Rtrim(f38));

		sm_cQGrpCustInfoByCustId>>f39;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"NOTE","");
		else
			utAddStr(uap,"NOTE",Rtrim(f39));

		sm_cQGrpCustInfoByCustId>>f40;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"LEAVE_DATE","");
		else
			utAddStr(uap,"LEAVE_DATE",Rtrim(f40));

		sm_cQGrpCustInfoByCustId>>f41;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"CREDIT_GRADE","");
		else
			utAddStr(uap,"CREDIT_GRADE",Rtrim(f41));

		sm_cQGrpCustInfoByCustId>>f42;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"EMAIL_ADDRESS","");
		else
			utAddStr(uap,"EMAIL_ADDRESS",Rtrim(f42));

		sm_cQGrpCustInfoByCustId>>f43;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"OPERATOR_PHONE","");
		else
			utAddStr(uap,"OPERATOR_PHONE",Rtrim(f43));

		sm_cQGrpCustInfoByCustId>>f44;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"GROUP_HQ_NAME","");
		else
			utAddStr(uap,"GROUP_HQ_NAME",Rtrim(f44));
			
		sm_cQGrpCustInfoByCustId>>f45;
		if(sm_cQGrpCustInfoByCustId.is_null())
			utAddStr(uap,"PRODUCT_TYPE","");
		else
			utAddStr(uap,"PRODUCT_TYPE",Rtrim(f45));

		rpcRows++;
		break;
	}
	if(errInfo){
		errInfo->iSqlRows = rpcRows;
	}
	L4C_TRACE("------==OUTPUT BEGIN==-------");
	LogUtype(uap);
	L4C_TRACE("------==OUTPUT END==-------");
	return(uap.release());
}

///////////////// Input parameters ////////////////
// @	STRUCT
// -@0	LONG	CUST_ID
// -@1	STRING	LIST_TYPE
////////////////////////////////////////////////////
///////////////// Output parameters ////////////////
// @	STRUCT
// -@0	CUST_ID	LONG
// -@1	LIST_TYPE	STRING
// -@2	OP_CODE	STRING
// -@3	OP_TIME	STRING
// -@4	LOGIN_NO	STRING
// -@5	LOGIN_ACCEPT	LONG
// -@6	EFF_DATE	STRING
// -@7	EXP_DATE	STRING
// -@8	FINISH_FLAG	STRING
// -@9	REGISTOR_NAME	STRING
// -@10	REMARK	STRING
// -@11	GROUP_ID	STRING
////////////////////////////////////////////////////
#include <allBCP.h>

using namespace std;

utype* cQCustSpeciallistInfoById(const utype * inParam,TCtrlInfo *errInfo)
{
    LOG_FUNC_BC();
	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(inParam);
	L4C_TRACE("------==INPUT END==-------");
	if(errInfo){
		memset(errInfo,0,sizeof(TCtrlInfo));
	}

	uAutoPtr uap(uInit(0));

	int rpcRows=0;
	otl_nocommit_stream sm_cQCustSpeciallistInfoById;


	sm_cQCustSpeciallistInfoById.set_flush(false);
	sm_cQCustSpeciallistInfoById.open(1,"SELECT  CUST_ID, LIST_TYPE, OP_CODE, to_char(OP_TIME,'yyyymmddhh24miss') OP_TIME, LOGIN_NO, LOGIN_ACCEPT\
		, to_char(EFF_DATE,'yyyymmddhh24miss') EFF_DATE, to_char(EXP_DATE,'yyyymmddhh24miss') EXP_DATE, FINISH_FLAG\
		, REGISTOR_NAME, REMARK, GROUP_ID FROM CT_CUSTSPECIALLIST_INFO WHERE CUST_ID =:CUST_ID<LONG> AND\
		 LIST_TYPE = :LIST_TYPE<char[4]>",GETDB(errInfo));


	if(utGetEmpty(inParam,"CUST_ID"))
		sm_cQCustSpeciallistInfoById<<otl_null();
	else
		sm_cQCustSpeciallistInfoById<<utGetLong(inParam,"CUST_ID");

	if(utGetEmpty(inParam,"LIST_TYPE"))
		sm_cQCustSpeciallistInfoById<<otl_null();
	else
		sm_cQCustSpeciallistInfoById<<utGetStr(inParam,"LIST_TYPE");

	sm_cQCustSpeciallistInfoById.flush();

	while(!sm_cQCustSpeciallistInfoById.eof()){
		long f0;
		char f1[4+1];
		char f2[4+1];
		char f3[14+1];
		char f4[20+1];
		long f5;
		char f6[14+1];
		char f7[14+1];
		char f8[1+1];
		char f9[60+1];
		char f10[255+1];
		char f11[10+1];


		sm_cQCustSpeciallistInfoById>>f0;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddEmpty(uap,"CUST_ID");
		else
			utAddLong(uap,"CUST_ID",f0);

		sm_cQCustSpeciallistInfoById>>f1;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"LIST_TYPE","");
		else
			utAddStr(uap,"LIST_TYPE",Rtrim(f1));

		sm_cQCustSpeciallistInfoById>>f2;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"OP_CODE","");
		else
			utAddStr(uap,"OP_CODE",Rtrim(f2));

		sm_cQCustSpeciallistInfoById>>f3;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"OP_TIME","");
		else
			utAddStr(uap,"OP_TIME",Rtrim(f3));

		sm_cQCustSpeciallistInfoById>>f4;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"LOGIN_NO","");
		else
			utAddStr(uap,"LOGIN_NO",Rtrim(f4));

		sm_cQCustSpeciallistInfoById>>f5;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddEmpty(uap,"LOGIN_ACCEPT");
		else
			utAddLong(uap,"LOGIN_ACCEPT",f5);

		sm_cQCustSpeciallistInfoById>>f6;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"EFF_DATE","");
		else
			utAddStr(uap,"EFF_DATE",Rtrim(f6));

		sm_cQCustSpeciallistInfoById>>f7;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"EXP_DATE","");
		else
			utAddStr(uap,"EXP_DATE",Rtrim(f7));

		sm_cQCustSpeciallistInfoById>>f8;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"FINISH_FLAG","");
		else
			utAddStr(uap,"FINISH_FLAG",Rtrim(f8));

		sm_cQCustSpeciallistInfoById>>f9;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"REGISTOR_NAME","");
		else
			utAddStr(uap,"REGISTOR_NAME",Rtrim(f9));

		sm_cQCustSpeciallistInfoById>>f10;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"REMARK","");
		else
			utAddStr(uap,"REMARK",Rtrim(f10));

		sm_cQCustSpeciallistInfoById>>f11;
		if(sm_cQCustSpeciallistInfoById.is_null())
			utAddStr(uap,"GROUP_ID","");
		else
			utAddStr(uap,"GROUP_ID",Rtrim(f11));

		rpcRows++;
		break;
	}
	if(errInfo){
		errInfo->iSqlRows = rpcRows;
	}
	L4C_TRACE("------==OUTPUT BEGIN==-------");
	LogUtype(uap);
	L4C_TRACE("------==OUTPUT END==-------");
	return(uap.release());
}
///////////////// Input parameters ////////////////
// @	STRUCT
// -@0	LONG	CUST_ID
// -@1	STRING	LIST_TYPE
// -@2	STRING	OP_CODE
// -@3	STRING	OP_TIME
// -@4	STRING	LOGIN_NO
// -@5	LONG	LOGIN_ACCEPT
// -@6	STRING	EFF_DATE
// -@7	STRING	EXP_DATE
// -@8	STRING	FINISH_FLAG
// -@9	STRING	REGISTOR_NAME
// -@10	STRING	REMARK
// -@11	STRING	GROUP_ID
#include <allBCP.h>

using namespace std;

utype* cICustSpeciallistInfo(const utype * inParam,TCtrlInfo *errInfo)
{
    LOG_FUNC_BC();
	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(inParam);
	L4C_TRACE("------==INPUT END==-------");
	if(errInfo){
		memset(errInfo,0,sizeof(TCtrlInfo));
	}
	int rpcRows=0;
	otl_nocommit_stream sm_cICustSpeciallistInfo;


	sm_cICustSpeciallistInfo.set_flush(false);
	sm_cICustSpeciallistInfo.open(1,"insert into CT_CUSTSPECIALLIST_INFO ( CUST_ID, LIST_TYPE, OP_CODE, OP_TIME, LOGIN_NO, LOGIN_ACCEPT, EFF_DATE\
		, EXP_DATE, FINISH_FLAG, REGISTOR_NAME, REMARK, GROUP_ID )  values ( :CUST_ID<long>, :LIST_TYPE<char[5]>\
		, :OP_CODE<char[5]>, to_date(:OP_TIME<char[15]>,'yyyymmddhh24miss'), :LOGIN_NO<char[21]>, :LOGIN_ACCEPT<long>\
		, to_date(:EFF_DATE<char[15]>,'yyyymmddhh24miss'), to_date(:EXP_DATE<char[15]>,'yyyymmddhh24miss'), :FINISH_FLAG<char[2]>\
		, :REGISTOR_NAME<char[61]>, :REMARK<char[256]>, :GROUP_ID<char[11]> )",GETDB(errInfo));


	if(utGetEmpty(inParam,"CUST_ID"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetLong(inParam,"CUST_ID");

	if(utGetEmpty(inParam,"LIST_TYPE"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"LIST_TYPE");

	if(utGetEmpty(inParam,"OP_CODE"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"OP_CODE");

	if(utGetEmpty(inParam,"OP_TIME"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"OP_TIME");

	if(utGetEmpty(inParam,"LOGIN_NO"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"LOGIN_NO");

	if(utGetEmpty(inParam,"LOGIN_ACCEPT"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetLong(inParam,"LOGIN_ACCEPT");

	if(utGetEmpty(inParam,"EFF_DATE"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"EFF_DATE");

	if(utGetEmpty(inParam,"EXP_DATE"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"EXP_DATE");

	if(utGetEmpty(inParam,"FINISH_FLAG"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"FINISH_FLAG");

	if(utGetEmpty(inParam,"REGISTOR_NAME"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"REGISTOR_NAME");

	if(utGetEmpty(inParam,"REMARK"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"REMARK");

	if(utGetEmpty(inParam,"GROUP_ID"))
		sm_cICustSpeciallistInfo<<otl_null();
	else
		sm_cICustSpeciallistInfo<<utGetStr(inParam,"GROUP_ID");

	sm_cICustSpeciallistInfo.flush();

	rpcRows+=sm_cICustSpeciallistInfo.get_rpc();
	if(errInfo){
		errInfo->iSqlRows = rpcRows;
	}
	L4C_TRACE("------==OUTPUT BEGIN==-------");
	L4C_TRACE("此构件无输出");
	L4C_TRACE("------==OUTPUT END==-------");
	return NULL;
}
///////////////// Input parameters ////////////////
// @	STRUCT
// -@0	LONG	CUST_ID
// -@1	STRING	LIST_TYPE
#include <allBCP.h>

using namespace std;

utype* cDCustSpeciallistInfo(const utype * inParam,TCtrlInfo *errInfo)
{
    LOG_FUNC_BC();
	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(inParam);
	L4C_TRACE("------==INPUT END==-------");
	if(errInfo){
		memset(errInfo,0,sizeof(TCtrlInfo));
	}
	int rpcRows=0;
	otl_nocommit_stream sm_cDCustSpeciallistInfo;


	sm_cDCustSpeciallistInfo.set_flush(false);
	sm_cDCustSpeciallistInfo.open(1,"delete FROM CT_CUSTSPECIALLIST_INFO WHERE CUST_ID =:CUST_ID<LONG> AND LIST_TYPE = :LIST_TYPE<char[4]>",GETDB(errInfo));


	if(utGetEmpty(inParam,"CUST_ID"))
		sm_cDCustSpeciallistInfo<<otl_null();
	else
		sm_cDCustSpeciallistInfo<<utGetLong(inParam,"CUST_ID");

	if(utGetEmpty(inParam,"LIST_TYPE"))
		sm_cDCustSpeciallistInfo<<otl_null();
	else
		sm_cDCustSpeciallistInfo<<utGetStr(inParam,"LIST_TYPE");

	sm_cDCustSpeciallistInfo.flush();

	rpcRows+=sm_cDCustSpeciallistInfo.get_rpc();
	if(errInfo){
		errInfo->iSqlRows = rpcRows;
	}
	L4C_TRACE("------==OUTPUT BEGIN==-------");
	L4C_TRACE("此构件无输出");
	L4C_TRACE("------==OUTPUT END==-------");
	return NULL;
}


///////////////// Input parameters ////////////////
// @	STRUCT
// -@0	LONG	CUST_ID
// -@1	STRING	LIST_TYPE
// -@2	STRING	OP_CODE
// -@3	STRING	OP_TIME
// -@4	STRING	LOGIN_NO
// -@5	LONG	LOGIN_ACCEPT
// -@6	STRING	EFF_DATE
// -@7	STRING	EXP_DATE
// -@8	STRING	FINISH_FLAG
// -@9	STRING	REGISTOR_NAME
// -@10	STRING	REMARK
// -@11	STRING	GROUP_ID
// -@12	LONG	UPDATE_ACCEPT
// -@13	STRING	UPDATE_TIME
// -@14	INT	UPDATE_DATE
// -@15	STRING	UPDATE_LOGIN
// -@16	STRING	UPDATE_TYPE
// -@17	STRING	UPDATE_CODE
#include <allBCP.h>

using namespace std;

utype* cICustSpeciallistInfoHis(const utype * inParam,TCtrlInfo *errInfo)
{
    LOG_FUNC_BC();
	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(inParam);
	L4C_TRACE("------==INPUT END==-------");
	if(errInfo){
		memset(errInfo,0,sizeof(TCtrlInfo));
	}
	int rpcRows=0;
	otl_nocommit_stream sm_cICustSpeciallistInfoHis;


	sm_cICustSpeciallistInfoHis.set_flush(false);
	sm_cICustSpeciallistInfoHis.open(1,"insert into CT_CUSTSPECIALLIST_INFO_HIS ( CUST_ID, LIST_TYPE, OP_CODE, OP_TIME, LOGIN_NO, LOGIN_ACCEPT\
		, EFF_DATE, EXP_DATE, FINISH_FLAG, REGISTOR_NAME, REMARK, GROUP_ID, UPDATE_ACCEPT, UPDATE_TIME, UPDATE_DATE\
		, UPDATE_LOGIN, UPDATE_TYPE, UPDATE_CODE )  values ( :CUST_ID<long>, :LIST_TYPE<char[5]>, :OP_CODE<char[5]>\
		, to_date(:OP_TIME<char[15]>,'yyyymmddhh24miss'), :LOGIN_NO<char[21]>, :LOGIN_ACCEPT<long>, to_date(:EFF_DATE<char[15]>\
		,'yyyymmddhh24miss'), to_date(:EXP_DATE<char[15]>,'yyyymmddhh24miss'), :FINISH_FLAG<char[2]>, :REGISTOR_NAME<char[61]>\
		, :REMARK<char[256]>, :GROUP_ID<char[11]>, :UPDATE_ACCEPT<long>, to_date(:UPDATE_TIME<char[15]>,'YYYYMMDDHH24MISS'\
		), :UPDATE_DATE<int>, :UPDATE_LOGIN<char[21]>, :UPDATE_TYPE<char[2]>, :UPDATE_CODE<char[6]> )",GETDB(errInfo));


	if(utGetEmpty(inParam,"CUST_ID"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetLong(inParam,"CUST_ID");

	if(utGetEmpty(inParam,"LIST_TYPE"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"LIST_TYPE");

	if(utGetEmpty(inParam,"OP_CODE"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"OP_CODE");

	if(utGetEmpty(inParam,"OP_TIME"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"OP_TIME");

	if(utGetEmpty(inParam,"LOGIN_NO"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"LOGIN_NO");

	if(utGetEmpty(inParam,"LOGIN_ACCEPT"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetLong(inParam,"LOGIN_ACCEPT");

	if(utGetEmpty(inParam,"EFF_DATE"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"EFF_DATE");

	if(utGetEmpty(inParam,"EXP_DATE"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"EXP_DATE");

	if(utGetEmpty(inParam,"FINISH_FLAG"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"FINISH_FLAG");

	if(utGetEmpty(inParam,"REGISTOR_NAME"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"REGISTOR_NAME");

	if(utGetEmpty(inParam,"REMARK"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"REMARK");

	if(utGetEmpty(inParam,"GROUP_ID"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"GROUP_ID");

	if(utGetEmpty(inParam,"UPDATE_ACCEPT"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetLong(inParam,"UPDATE_ACCEPT");

	if(utGetEmpty(inParam,"UPDATE_TIME"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"UPDATE_TIME");

	if(utGetEmpty(inParam,"UPDATE_DATE"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetInt(inParam,"UPDATE_DATE");

	if(utGetEmpty(inParam,"UPDATE_LOGIN"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"UPDATE_LOGIN");

	if(utGetEmpty(inParam,"UPDATE_TYPE"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"UPDATE_TYPE");

	if(utGetEmpty(inParam,"UPDATE_CODE"))
		sm_cICustSpeciallistInfoHis<<otl_null();
	else
		sm_cICustSpeciallistInfoHis<<utGetStr(inParam,"UPDATE_CODE");

	sm_cICustSpeciallistInfoHis.flush();

	rpcRows+=sm_cICustSpeciallistInfoHis.get_rpc();
	if(errInfo){
		errInfo->iSqlRows = rpcRows;
	}
	L4C_TRACE("------==OUTPUT BEGIN==-------");
	L4C_TRACE("此构件无输出");
	L4C_TRACE("------==OUTPUT END==-------");
	return NULL;
}
///////////////// Input parameters ////////////////
// @	STRUCT
// -@0	LONG	UPDATE_ACCEPT
// -@1	STRING	UPDATE_TIME
// -@2	INT	UPDATE_DATE
// -@3	STRING	UPDATE_LOGIN
// -@4	STRING	UPDATE_TYPE
// -@5	STRING	UPDATE_CODE
// -@6	LONG	CUST_ID
// -@7	STRING	LIST_TYPE
#include <allBCP.h>

using namespace std;

utype* cICustSpeciallistInfoHisbak(const utype * inParam,TCtrlInfo *errInfo)
{
    LOG_FUNC_BC();
	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(inParam);
	L4C_TRACE("------==INPUT END==-------");
	if(errInfo){
		memset(errInfo,0,sizeof(TCtrlInfo));
	}
	int rpcRows=0;
	otl_nocommit_stream sm_cICustSpeciallistInfoHisbak;


	sm_cICustSpeciallistInfoHisbak.set_flush(false);
	sm_cICustSpeciallistInfoHisbak.open(1,"INSERT INTO CT_CUSTSPECIALLIST_INFO_HIS ( CUST_ID, LIST_TYPE, OP_CODE, OP_TIME, LOGIN_NO, LOGIN_ACCEPT\
		, EFF_DATE, EXP_DATE, FINISH_FLAG, REGISTOR_NAME, REMARK, GROUP_ID, UPDATE_ACCEPT, UPDATE_TIME, UPDATE_DATE\
		, UPDATE_LOGIN, UPDATE_TYPE, UPDATE_CODE ) SELECT CUST_ID, LIST_TYPE, OP_CODE, OP_TIME, LOGIN_NO, LOGIN_ACCEPT\
		, EFF_DATE, EXP_DATE, FINISH_FLAG, REGISTOR_NAME, REMARK, GROUP_ID, :UPDATE_ACCEPT<long>, to_date(:UPDATE_TIME<char[15]>\
		,'YYYYMMDDHH24MISS'), :UPDATE_DATE<int>, :UPDATE_LOGIN<char[21]>, :UPDATE_TYPE<char[2]>, :UPDATE_CODE<char[6]>\
		 FROM CT_CUSTSPECIALLIST_INFO WHERE CUST_ID =:CUST_ID<LONG> AND LIST_TYPE = :LIST_TYPE<char[4]>",GETDB(errInfo));


	if(utGetEmpty(inParam,"UPDATE_ACCEPT"))
		sm_cICustSpeciallistInfoHisbak<<otl_null();
	else
		sm_cICustSpeciallistInfoHisbak<<utGetLong(inParam,"UPDATE_ACCEPT");

	if(utGetEmpty(inParam,"UPDATE_TIME"))
		sm_cICustSpeciallistInfoHisbak<<otl_null();
	else
		sm_cICustSpeciallistInfoHisbak<<utGetStr(inParam,"UPDATE_TIME");

	if(utGetEmpty(inParam,"UPDATE_DATE"))
		sm_cICustSpeciallistInfoHisbak<<otl_null();
	else
		sm_cICustSpeciallistInfoHisbak<<utGetInt(inParam,"UPDATE_DATE");

	if(utGetEmpty(inParam,"UPDATE_LOGIN"))
		sm_cICustSpeciallistInfoHisbak<<otl_null();
	else
		sm_cICustSpeciallistInfoHisbak<<utGetStr(inParam,"UPDATE_LOGIN");

	if(utGetEmpty(inParam,"UPDATE_TYPE"))
		sm_cICustSpeciallistInfoHisbak<<otl_null();
	else
		sm_cICustSpeciallistInfoHisbak<<utGetStr(inParam,"UPDATE_TYPE");

	if(utGetEmpty(inParam,"UPDATE_CODE"))
		sm_cICustSpeciallistInfoHisbak<<otl_null();
	else
		sm_cICustSpeciallistInfoHisbak<<utGetStr(inParam,"UPDATE_CODE");

	if(utGetEmpty(inParam,"CUST_ID"))
		sm_cICustSpeciallistInfoHisbak<<otl_null();
	else
		sm_cICustSpeciallistInfoHisbak<<utGetLong(inParam,"CUST_ID");

	if(utGetEmpty(inParam,"LIST_TYPE"))
		sm_cICustSpeciallistInfoHisbak<<otl_null();
	else
		sm_cICustSpeciallistInfoHisbak<<utGetStr(inParam,"LIST_TYPE");

	sm_cICustSpeciallistInfoHisbak.flush();

	rpcRows+=sm_cICustSpeciallistInfoHisbak.get_rpc();
	if(errInfo){
		errInfo->iSqlRows = rpcRows;
	}
	L4C_TRACE("------==OUTPUT BEGIN==-------");
	L4C_TRACE("此构件无输出");
	L4C_TRACE("------==OUTPUT END==-------");
	return NULL;
}


