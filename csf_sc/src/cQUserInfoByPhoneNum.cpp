#include <allBCP.h>

using namespace std;

utype* cQUserInfoByPhoneNum(const utype * inParam,TCtrlInfo *errInfo)
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
        otl_nocommit_stream sm_cQUserInfoByPhoneNum;


        sm_cQUserInfoByPhoneNum.set_flush(false);
        sm_cQUserInfoByPhoneNum.open(1," SELECT  ID_NO,  PHONE_NO,  CONTRACT_NO,  CUST_ID,RUN_CODE,  to_char(RUN_TIME,'yyyymmddhh24miss') RUN_TIME\
                ,  OWNER_TYPE,  USER_GRADE_CODE,  STOP_FLAG,  OWED_FLAG,  BILLING_CYCLE_TYPE_ID,  BILL_TYPE,  GROUP_FLAG\
                ,  USER_PASSWD,  PASSWD_TYPE,  CREDIT_CODE,  LIMIT_OWE,  CMD_RIGHT,  ASSURE_FLAG,  to_char(CREATE_DATE\
                ,'yyyymmddhh24miss') CREATE_DATE,  CREATE_LOGIN,  GROUP_ID,  OWNED_CHNL_ID,  SERVICE_GROUP,  to_char\
                (COMPLETED_DATE,'yyyymmddhh24miss') COMPLETED_DATE,  to_char(OPEN_TIME,'yyyymmddhh24miss') OPEN_TIME\
                ,  to_char(BILL_START_TIME,'yyyymmddhh24miss') BILL_START_TIME,  to_char(BILL_END_TIME,'yyyymmddhh24miss'\
                ) BILL_END_TIME,  to_char(FIRST_USEDATE,'yyyymmddhh24miss') FIRST_USEDATE,  to_char(RENT_DATE,'yyyymmddhh24miss'\
                ) RENT_DATE,  to_char(STOP_RENT_DATE,'yyyymmddhh24miss') STOP_RENT_DATE,  PHOTO_FLAG,  CARD_TYPE,  VIP_CARD_NO\
                ,  VIP_CREATE_TYPE,  FINISH_FLAG,  OP_CODE,  to_char(OP_TIME,'yyyymmddhh24miss') OP_TIME,  LOGIN_NO,\
                  LOGIN_ACCEPT,  BAK_FIELD,  MASTER_SERV_ID,  OLD_RUN  FROM UR_USER_INFO  where PHONE_NO=:PHONE_NO<char[41]>\
                  and ROWNUM=1 ",GETDB(errInfo));


        if(utGetEmpty(inParam,"PHONE_NO"))
                sm_cQUserInfoByPhoneNum<<otl_null();
        else
                sm_cQUserInfoByPhoneNum<<utGetStr(inParam,"PHONE_NO");

        sm_cQUserInfoByPhoneNum.flush();

        while(!sm_cQUserInfoByPhoneNum.eof()){
                long f0;
                char f1[40+1];
                long f2;
                long f3;
                char f4[2+1];
                char f5[14+1];
                int f6;
                char f7[2+1];
                char f8[1+1];
                char f9[1+1];
                int f10;
                int f11;
                char f12[1+1];
                char f13[8+1];
                char f14[1+1];
                char f15[3+1];
                double f16;
                long f17;
                char f18[1+1];
                char f19[14+1];
                char f20[20+1];
                char f21[10+1];
                char f22[10+1];
                char f23[10+1];
                char f24[14+1];
                char f25[14+1];
                char f26[14+1];
                char f27[14+1];
                char f28[14+1];
                char f29[14+1];
                char f30[14+1];
                char f31[1+1];
                int f32;
                char f33[30+1];
                int f34;
                char f35[1+1];
                char f36[5+1];
                char f37[14+1];
                char f38[20+1];
                long f39;
                char f40[12+1];
                char f41[8+1];
                char f42[2+1];


                sm_cQUserInfoByPhoneNum>>f0;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"ID_NO");
                else
                        utAddLong(uap,"ID_NO",f0);

                sm_cQUserInfoByPhoneNum>>f1;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"PHONE_NO","");
                else
                        utAddStr(uap,"PHONE_NO",Rtrim(f1));

                sm_cQUserInfoByPhoneNum>>f2;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"CONTRACT_NO");
                else
                        utAddLong(uap,"CONTRACT_NO",f2);

                sm_cQUserInfoByPhoneNum>>f3;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"CUST_ID");
                else
                        utAddLong(uap,"CUST_ID",f3);

                sm_cQUserInfoByPhoneNum>>f4;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"RUN_CODE","");
                else
                        utAddStr(uap,"RUN_CODE",Rtrim(f4));

                sm_cQUserInfoByPhoneNum>>f5;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"RUN_TIME","");
                else
                        utAddStr(uap,"RUN_TIME",Rtrim(f5));

                sm_cQUserInfoByPhoneNum>>f6;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"OWNER_TYPE");
                else
                        utAddInt(uap,"OWNER_TYPE",f6);

                sm_cQUserInfoByPhoneNum>>f7;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"USER_GRADE_CODE","");
                else
                        utAddStr(uap,"USER_GRADE_CODE",Rtrim(f7));

                sm_cQUserInfoByPhoneNum>>f8;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"STOP_FLAG","");
                else
                        utAddStr(uap,"STOP_FLAG",Rtrim(f8));

                sm_cQUserInfoByPhoneNum>>f9;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"OWED_FLAG","");
                else
                        utAddStr(uap,"OWED_FLAG",Rtrim(f9));

                sm_cQUserInfoByPhoneNum>>f10;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"BILLING_CYCLE_TYPE_ID");
                else
                        utAddInt(uap,"BILLING_CYCLE_TYPE_ID",f10);

                sm_cQUserInfoByPhoneNum>>f11;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"BILL_TYPE");
                else
                        utAddInt(uap,"BILL_TYPE",f11);

                sm_cQUserInfoByPhoneNum>>f12;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"GROUP_FLAG","");
                else
                        utAddStr(uap,"GROUP_FLAG",Rtrim(f12));

                sm_cQUserInfoByPhoneNum>>f13;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"USER_PASSWD","");
                else
                        utAddStr(uap,"USER_PASSWD",Rtrim(f13));

                sm_cQUserInfoByPhoneNum>>f14;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"PASSWD_TYPE","");
                else
                        utAddStr(uap,"PASSWD_TYPE",Rtrim(f14));

                sm_cQUserInfoByPhoneNum>>f15;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"CREDIT_CODE","");
                else
                        utAddStr(uap,"CREDIT_CODE",Rtrim(f15));

                sm_cQUserInfoByPhoneNum>>f16;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"LIMIT_OWE");
                else
                        utAddDouble(uap,"LIMIT_OWE",f16);

                sm_cQUserInfoByPhoneNum>>f17;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"CMD_RIGHT");
                else
                        utAddLong(uap,"CMD_RIGHT",f17);

                sm_cQUserInfoByPhoneNum>>f18;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"ASSURE_FLAG","");
                else
                        utAddStr(uap,"ASSURE_FLAG",Rtrim(f18));

                sm_cQUserInfoByPhoneNum>>f19;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"CREATE_DATE","");
                else
                        utAddStr(uap,"CREATE_DATE",Rtrim(f19));

                sm_cQUserInfoByPhoneNum>>f20;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"CREATE_LOGIN","");
                else
                        utAddStr(uap,"CREATE_LOGIN",Rtrim(f20));

                sm_cQUserInfoByPhoneNum>>f21;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"GROUP_ID","");
                else
                        utAddStr(uap,"GROUP_ID",Rtrim(f21));

                sm_cQUserInfoByPhoneNum>>f22;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"OWNED_CHNL_ID","");
                else
                        utAddStr(uap,"OWNED_CHNL_ID",Rtrim(f22));

                sm_cQUserInfoByPhoneNum>>f23;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"SERVICE_GROUP","");
                else
                        utAddStr(uap,"SERVICE_GROUP",Rtrim(f23));

                sm_cQUserInfoByPhoneNum>>f24;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"COMPLETED_DATE","");
                else
                        utAddStr(uap,"COMPLETED_DATE",Rtrim(f24));

                sm_cQUserInfoByPhoneNum>>f25;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"OPEN_TIME","");
                else
                        utAddStr(uap,"OPEN_TIME",Rtrim(f25));

                sm_cQUserInfoByPhoneNum>>f26;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"BILL_START_TIME","");
                else
                        utAddStr(uap,"BILL_START_TIME",Rtrim(f26));

                sm_cQUserInfoByPhoneNum>>f27;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"BILL_END_TIME","");
                else
                        utAddStr(uap,"BILL_END_TIME",Rtrim(f27));

                sm_cQUserInfoByPhoneNum>>f28;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"FIRST_USEDATE","");
                else
                        utAddStr(uap,"FIRST_USEDATE",Rtrim(f28));

                sm_cQUserInfoByPhoneNum>>f29;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"RENT_DATE","");
                else
                        utAddStr(uap,"RENT_DATE",Rtrim(f29));

                sm_cQUserInfoByPhoneNum>>f30;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"STOP_RENT_DATE","");
                else
                        utAddStr(uap,"STOP_RENT_DATE",Rtrim(f30));

                sm_cQUserInfoByPhoneNum>>f31;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"PHOTO_FLAG","");
                else
                        utAddStr(uap,"PHOTO_FLAG",Rtrim(f31));

                sm_cQUserInfoByPhoneNum>>f32;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"CARD_TYPE");
                else
                        utAddInt(uap,"CARD_TYPE",f32);

                sm_cQUserInfoByPhoneNum>>f33;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"VIP_CARD_NO","");
                else
                        utAddStr(uap,"VIP_CARD_NO",Rtrim(f33));

                sm_cQUserInfoByPhoneNum>>f34;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"VIP_CREATE_TYPE");
                else
                        utAddInt(uap,"VIP_CREATE_TYPE",f34);

                sm_cQUserInfoByPhoneNum>>f35;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"FINISH_FLAG","");
                else
                        utAddStr(uap,"FINISH_FLAG",Rtrim(f35));

                sm_cQUserInfoByPhoneNum>>f36;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"OP_CODE","");
                else
                        utAddStr(uap,"OP_CODE",Rtrim(f36));

                sm_cQUserInfoByPhoneNum>>f37;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"OP_TIME","");
                else
                        utAddStr(uap,"OP_TIME",Rtrim(f37));

                sm_cQUserInfoByPhoneNum>>f38;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"LOGIN_NO","");
                else
                        utAddStr(uap,"LOGIN_NO",Rtrim(f38));

                sm_cQUserInfoByPhoneNum>>f39;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddEmpty(uap,"LOGIN_ACCEPT");
                else
                        utAddLong(uap,"LOGIN_ACCEPT",f39);

                sm_cQUserInfoByPhoneNum>>f40;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"BAK_FIELD","");
                else
                        utAddStr(uap,"BAK_FIELD",Rtrim(f40));

                sm_cQUserInfoByPhoneNum>>f41;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"MASTER_SERV_ID","");
                else
                        utAddStr(uap,"MASTER_SERV_ID",Rtrim(f41));

                sm_cQUserInfoByPhoneNum>>f42;
                if(sm_cQUserInfoByPhoneNum.is_null())
                        utAddStr(uap,"OLD_RUN","");
                else
                        utAddStr(uap,"OLD_RUN",Rtrim(f42));

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
