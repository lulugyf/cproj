SELECT ID_NO, PHONE_NO,CONTRACT_NO,CUST_ID,RUN_CODE,to_char(RUN_TIME,'yyyymmddhh24miss') RUN_TIME,OWNER_TYPE,USER_GRADE_CODE,
 STOP_FLAG,OWED_FLAG,BILLING_CYCLE_TYPE_ID,BILL_TYPE,
 GROUP_FLAG,USER_PASSWD,PASSWD_TYPE,CREDIT_CODE,LIMIT_OWE,CMD_RIGHT,
 ASSURE_FLAG,to_char(CREATE_DATE,'yyyymmddhh24miss') CREATE_DATE,CREATE_LOGIN,GROUP_ID,OWNED_CHNL_ID,SERVICE_GROUP,
 to_char(COMPLETED_DATE,'yyyymmddhh24miss') COMPLETED_DATE,to_char(OPEN_TIME,'yyyymmddhh24miss') OPEN_TIME,to_char(BILL_START_TIME,'yyyymmddhh24miss') BILL_START_TIME,to_char(BILL_END_TIME,'yyyymmddhh24miss') BILL_END_TIME,to_char(FIRST_USEDATE,'yyyymmddhh24miss') FIRST_USEDATE,
 to_char(RENT_DATE,'yyyymmddhh24miss') RENT_DATE,
 to_char(STOP_RENT_DATE,'yyyymmddhh24miss') STOP_RENT_DATE,PHOTO_FLAG, CARD_TYPE,VIP_CARD_NO,VIP_CREATE_TYPE,FINISH_FLAG,OP_CODE,to_char(OP_TIME,'yyyymmddhh24miss') OP_TIME,LOGIN_NO,LOGIN_ACCEPT,BAK_FIELD,MASTER_SERV_ID,OLD_RUN FROM UR_USER_INFO
 where PHONE_NO=:PHONE_NO<char[41]> and ROWNUM=1