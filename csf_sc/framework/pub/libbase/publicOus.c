#include "fee.h"
#include "amd_stop.h"
#include "boss_srv.h"
#include "publicsrv.h"
#include "boss_define.h"

/*定义数据表的同步方式*/
#define createAll  		"A"
#define createSend 		"S"
#define createLocal		"L"

/*定义接口表的更新方式*/
#define SEND_INSERT		"1"
#define SEND_UPDATE   "2"
#define SEND_DELETE		"3"

/*定义数据处理状态*/
#define UNDEAL  			"0"
#define DEALED 				"1"

#ifndef SQLCA
EXEC SQL INCLUDE SQLCA;
#endif

#ifndef SQLDA
EXEC SQL INCLUDE SQLDA;
#endif

/*
typedef struct CheckPrepay
{
    char 	vBankCode[5+1];
    char 	vCheckNo[20+1];
    float checkPrepay;
    char  vOpTime[17+1];
} tCheckPrepay;

typedef struct DcustStop
{
    long 	vIdNo;
    int 	iStopTimes;
    int	  iStopDurations;
    char  vStopTime[17+1];
    char  vOpenTime[17+1];
    float shouldPay;	
    int		vMonthStopTimes;
} tDcustStop;

typedef struct WbatchLog
{
    char 	vOpCode[4+1];
    long	loginAccept;
    char	vLoginNo[6+1];
    char  vBeginTime[17+1];
    char  vEndTime[17+1];
    int		vDealNum;	
    int		vSuccNum;	
    char	vErrNo[6+1];
    char	vErrMsg[60+1];
} tWbatchLog;

typedef struct WbatchOpr
{
    int 	vTotalDate;
    long	loginAccept;
    char	vOpCode[4+1];
    char  vPhoneNo[15+1];
    long  vIdNo;
    char	vSmCode[2+1];	
    char	vLoginNo[6+1];	
    char	vOrgCode[9+1];
    char	vOpTime[17+1];
    char	vOpFlag[1+1];
    char	vOpNote[60+1];
    int		vData1;
    char	vName1[60+1];
    int		vData2;
    char	vName2[60+1];
    int		vData3;
    char	vName3[60+1];
    int		vData4;
    char	vName4[60+1];    
    int		vData5;
    char	vName5[60+1];
} tWbatchOpr;

typedef struct WcheckOpr
{
    int 	vTotalDate;
    long	loginAccept;
    char	vOrgCode[9+1];
    char  vLoginNo[6+1];
    char  vOpCode[4+1];
    char	vBankCode[5+1];	
    char	vCheckNo[20+1];	
    float	vCheckPay;
    char	vOpTime[17+1];
    char	vOpNote[60+1];
    char	vOrgId[10+1];
} tWcheckOpr;

typedef struct wRelationFavChg
{
    char 	vMsisDn[12+1];
    char	vRelationCode[5+1];
    char	vOtherCode[20+1];
    char  vBeginTime[17+1];
    char  vEndDate[17+1];
    char	vFlag[1+1];	
    char	vDealDate[17+1];	
} tWrelationFavChg;

typedef struct wTotalFav
{
    char 	vPhoneNo[15+1];
    char	vOrderCode[5+1];
    long	vIdNo;
    char  vFavType[2+1];
    char  vOpCode[4+1];
    long	loginAccept;	
    char	vTotalDate[8+1];	
    char	vFeeCodes[1024+1];
    char	vSmFlag[1+1];
    float	vFavourFee;
    char	vBeginTime[17+1];
    char	vEndTime[17+1];
} twTotalFav;



typedef struct wTotalFavHis
{
    char 	vPhoneNo[15+1];
    char	vOrderCode[5+1];
    long	vIdNo;
    char  vFavType[2+1];
    char  vOpCode[4+1];
    long	loginAccept;	
    char	vTotalDate[8+1];	
    char	vFeeCodes[1024+1];
    char	vSmFlag[1+1];
    float	vFavourFee;
    char	vBeginTime[17+1];
    char	vEndTime[17+1];
} twTotalFavHis;

typedef struct billOweAdjOweDet
{
    char 	vPhoneNo[15+1];
    long	vIdNo;
		long	vContractNo;
    char  vFeeCode[3+1];
    char	vDetailCode[5+1];
    int  	vAdjSumShid;
    int		vAdjSumFav;	
    int		vAdjIncrShld;	
    int		vAdjINcrFav;
    int	  vAdjIncrTimes;
    int		vAdjIncrDuras;
} tbillOweAdjDet;
*/
int getInterAccept(char *accept)
{
        long lAcceptChg=0;                  

				#ifdef _DEBUG_
				        printf("getInterAccept: Starting Execute\n");
				#endif

        EXEC SQL SELECT sInterAccept.nextval	INTO :lAcceptChg FROM Dual;
        if (SQLCODE != 0)
        {
								#ifdef _DEBUG_
								                printf("getInterAccept: SQLCODE=[%d]\tSQLERRMSG=[%s]\n",SQLCODE,SQLERRMSG);
								#endif
                return 1;
        }

				#ifdef _DEBUG_
				        printf("getInterAccept: lAcceptChg=[%d]\n",lAcceptChg);
				#endif

        if (accept != NULL)
        {
                sprintf(accept, "%ld",lAcceptChg);
        }
        return 0;
}


int getTableOusCfg(char *tableName,char *synType,char *retMsg)
{
    char vSynType[1+1];
    memset(vSynType,	0,	sizeof(vSynType));
    strcpy(retMsg,"读取success");
		
		printf("tableName===[%s]\n",tableName);
		/*modi by yangjy 2009-1-19 19:44*/
    EXEC SQL select syn_Type into :vSynType
    		   from sTableSynCfg 
    		  where upper(table_name) = upper(:tableName);
    		  
	if(SQLCODE != OK || SQLROWS != 1)
	{
		printf("getTableSynCfg:读取数据表同步配置信息出错[%s],SQLCODE==[%d],SQLERRMSG==[%s]!\n", tableName,SQLCODE,SQLERRMSG);
		sprintf(retMsg,"读取sTableSynCfg中表[%s]出错",tableName);
		return 1;
	}
	
	printf("ceshi=====synType=[%s],vSynType=[%s] \n ",synType,vSynType);
	strcpy(synType,vSynType);
	printf("ceshi2=====synType=[%s],vSynType=[%s] \n ",synType,vSynType);	
	return 0;
}

int sendDcheckPrepay(tCheckPrepay *tCheckPre, char *chgType, char *loginAccept, char *retMsg)
{
printf("chgType=====[%s],loginAccept========[%s]\n",chgType,loginAccept);

	int  	ret_code=0;
	char 	chgSeq[14+1];
	char 	vSQL_Text[4096+1];
	char 	vTmp_String[4096+1]; 
	
	memset(chgSeq, 			0,	sizeof(chgSeq));
	memset(vSQL_Text, 	0,	sizeof(vSQL_Text));
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	
	
	ret_code=getInterAccept(chgSeq);
	if(ret_code!=0)
	{
		printf("获取接口流水失败\n");
		return 1;
	}	
	printf("接口流水===[%s]\n",chgSeq);

	strcpy(vSQL_Text,"INSERT INTO wCheckPrepaySend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Login_Accept,Send_Status,");	
	strcat(vSQL_Text,"Bank_Code,Check_No,Check_Prepay,Op_Time)");
	strcat(vSQL_Text,"VALUES (");
	
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s to_number('%s'),  '%s', to_number('%s'),'%s'",vTmp_String,chgSeq,chgType,loginAccept,UNDEAL);

	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s '%s',  '%s', '%lf',to_date('%s','YYYYMMDD HH24:MI:SS')",vTmp_String,tCheckPre->vBankCode,tCheckPre->vCheckNo,tCheckPre->checkPrepay,tCheckPre->vOpTime);
	
	printf("vSQL_Text====[%s]\n",vSQL_Text);

	strcpy(vSQL_Text,"INSERT INTO wCheckPrepaySend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Login_Accept,Send_Status,");	
	strcat(vSQL_Text,"Bank_Code,Check_No,Check_Prepay,Op_Time)");	
	strcat(vSQL_Text,"VALUES (");
	strcat(vSQL_Text,"to_number(:v1),:v2,to_number(:v3),'0',");
	strcat(vSQL_Text,":v4,:v5,:v6,to_date(:v7,'YYYYMMDD HH24:MI:SS'))");
	EXEC SQL PREPARE Exec_dCheckPre FROM :vSQL_Text;
	EXEC SQL EXECUTE Exec_dCheckPre using
	:chgSeq,	:chgType,	:loginAccept,
	:tCheckPre->vBankCode,	:tCheckPre->vCheckNo,
	:tCheckPre->checkPrepay,:tCheckPre->vOpTime;
		
	if(SQLCODE!=0)
	{
		printf("SQLCODE==[%d],SQLERRMSG==[%s]\n",SQLCODE,SQLERRMSG);
		strcpy(retMsg,"插入wCheckPrepaySend出错");
		return 2;
	}
	return 0;
}


int sendDcustStop(tDcustStop *tCustStop, char *chgType, char *loginAccept, char *retMsg)
{
	int  	ret_code=0;
	char 	chgSeq[14+1];
	char 	vSQL_Text[4096+1];
	char 	vTmp_String[4096+1]; 
	
	memset(chgSeq, 			0,	sizeof(chgSeq));
	memset(vSQL_Text, 	0,	sizeof(vSQL_Text));
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	
	
	ret_code=getInterAccept(chgSeq);
	if(ret_code!=0)
	{
		printf("获取接口流水失败\n");
		return 1;
	}	
	printf("接口流水===[%s]\n",chgSeq);

	strcpy(vSQL_Text,"INSERT INTO wCustStopSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Login_Accept,Send_Status,");	
	strcat(vSQL_Text,"Id_No,Stop_Times,Stop_Durations,Stop_Time,Open_Time,Should_Pay,Month_StopTimes)");
	strcat(vSQL_Text,"VALUES (");
	
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s to_number('%s'),  '%s', to_number('%s'),'%s'",vTmp_String,chgSeq,chgType,loginAccept,UNDEAL);

	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s '%ld',  '%d', '%d',to_date('%s','YYYYMMDD HH24:MI:SS'),to_date('%s','YYYYMMDD HH24:MI:SS'),%lf,%d",vTmp_String,tCustStop->vIdNo,tCustStop->iStopTimes,tCustStop->iStopDurations,tCustStop->vStopTime,tCustStop->vOpenTime,tCustStop->shouldPay,tCustStop->vMonthStopTimes);
	
	printf("vSQL_Text====[%s]\n",vSQL_Text);

	strcpy(vSQL_Text,"INSERT INTO wCustStopSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Login_Accept,Send_Status,");	
	strcat(vSQL_Text,"Id_No,Stop_Times,Stop_Durations,Stop_Time,Open_Time,Should_Pay,Month_StopTimes)");
	strcat(vSQL_Text,"VALUES (");
	strcat(vSQL_Text,"to_number(:v1),:v2,to_number(:v3),'0',");
	strcat(vSQL_Text,":v4,:v5,:v6,to_date(:v7,'YYYYMMDD HH24:MI:SS'),to_date(:v8,'YYYYMMDD HH24:MI:SS'),:v9,:v10)");
	EXEC SQL PREPARE Exec_dCheckPre FROM :vSQL_Text;
	EXEC SQL EXECUTE Exec_dCheckPre using
	:chgSeq,	:chgType,	:loginAccept,
	:tCustStop->vIdNo,:tCustStop->iStopTimes,
	:tCustStop->iStopDurations,:tCustStop->vStopTime,
	:tCustStop->vOpenTime,
	:tCustStop->shouldPay,:tCustStop->vMonthStopTimes;
		
	if(SQLCODE!=0)
	{
		printf("SQLCODE==[%d],SQLERRMSG==[%s]\n",SQLCODE,SQLERRMSG);
		strcpy(retMsg,"插入wCustStopSend出错");
		return 2;
	}
	return 0;
}

int sendBatchLog(tWbatchLog *tBatchLog, char *chgType, char *loginAccept, char *retMsg)
{
	int  	ret_code=0;
	char 	chgSeq[14+1];
	char 	vSQL_Text[4096+1];
	char 	vTmp_String[4096+1]; 
	
	memset(chgSeq, 			0,	sizeof(chgSeq));
	memset(vSQL_Text, 	0,	sizeof(vSQL_Text));
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	
	
	ret_code=getInterAccept(chgSeq);
	if(ret_code!=0)
	{
		printf("获取接口流水失败\n");
		return 1;
	}	
	printf("接口流水===[%s]\n",chgSeq);

	strcpy(vSQL_Text,"INSERT INTO wBatchLogSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Op_Code,Login_Accept,Login_No,Begin_Time,End_Time,Deal_Num,Succ_Num,Err_No,Err_Msg)");
	strcat(vSQL_Text,"VALUES (");
	
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s to_number('%s'),  '%s', to_number('%s'),'%s'",vTmp_String,chgSeq,chgType,loginAccept,UNDEAL);

	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s '%ld',  '%s', to_date('%s','YYYYMMDD HH24:MI:SS'),to_date('%s','YYYYMMDD HH24:MI:SS'),%d,%d,%s,%s",vTmp_String,tBatchLog->vOpCode,tBatchLog->loginAccept,tBatchLog->vLoginNo,tBatchLog->vBeginTime,tBatchLog->vEndTime,tBatchLog->vDealNum,tBatchLog->vSuccNum,tBatchLog->vErrNo,tBatchLog->vErrMsg);
	
	printf("vSQL_Text====[%s]\n",vSQL_Text);

	strcpy(vSQL_Text,"INSERT INTO wBatchLogSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Op_Code,Login_Accept,Login_No,Begin_Time,End_Time,Deal_Num,Succ_Num,Err_No,Err_Msg)");
	strcat(vSQL_Text,"VALUES (");
	strcat(vSQL_Text,"to_number(:v1),:v2,to_number(:v3),'0',");
	strcat(vSQL_Text,":v4,:v5,:v6,to_date(:v7,'YYYYMMDD HH24:MI:SS'),to_date(:v8,'YYYYMMDD HH24:MI:SS'),:v9,:v10,:v11,:v12)");
	EXEC SQL PREPARE Exec_dCheckPre FROM :vSQL_Text;
	EXEC SQL EXECUTE Exec_dCheckPre using
	:chgSeq,	:chgType,	:loginAccept,
	:tBatchLog->vOpCode,:tBatchLog->loginAccept,
	:tBatchLog->vLoginNo,:tBatchLog->vBeginTime,
	:tBatchLog->vEndTime,:tBatchLog->vDealNum,
	:tBatchLog->vSuccNum,
	:tBatchLog->vErrNo,:tBatchLog->vErrMsg;
		
	if(SQLCODE!=0)
	{
		printf("SQLCODE==[%d],SQLERRMSG==[%s]\n",SQLCODE,SQLERRMSG);
		strcpy(retMsg,"插入wBatchLogSend出错");
		return 2;
	}
	return 0;
}

int sendBatchOpr(tWbatchOpr *tBatchOpr, char *chgType, char *loginAccept, char *retMsg)
{
	int  	ret_code=0;
	char 	chgSeq[14+1];
	char 	vSQL_Text[4096+1];
	char 	vTmp_String[4096+1]; 
	
	memset(chgSeq, 			0,	sizeof(chgSeq));
	memset(vSQL_Text, 	0,	sizeof(vSQL_Text));
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	
	
	ret_code=getInterAccept(chgSeq);
	if(ret_code!=0)
	{
		printf("获取接口流水失败\n");
		return 1;
	}	
	printf("接口流水===[%s]\n",chgSeq);

	strcpy(vSQL_Text,"INSERT INTO wBatchOprSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Total_Date,Login_Accept,Op_Code,Phone_No,Id_No,Sm_Code,Login_No,Org_Code,Op_Time,Op_Flag,Op_Note,Data1,Name1,Data2,Name2,Data3,Name3,Data4,Name4,Data5,Name5)");
	strcat(vSQL_Text,"VALUES (");
	
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s to_number('%s'),  '%s', to_number('%s'),'%s'",vTmp_String,chgSeq,chgType,loginAccept,UNDEAL);

	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s '%d','%ld', '%s','%s',%ld,%s,%s,%s,to_char('%s','YYYYMMDD HH24:MI:SS'),'%s','%s','%d','%s','%d','%s','%d','%s','%d','%s','%d','%s'",vTmp_String,tBatchOpr->vTotalDate,tBatchOpr->loginAccept,tBatchOpr->vOpCode,tBatchOpr->vPhoneNo,tBatchOpr->vIdNo,tBatchOpr->vSmCode,tBatchOpr->vLoginNo,tBatchOpr->vOrgCode,tBatchOpr->vOpTime,tBatchOpr->vOpFlag,tBatchOpr->vOpNote,tBatchOpr->vData1,tBatchOpr->vName1,tBatchOpr->vData2,tBatchOpr->vName2,tBatchOpr->vData3,tBatchOpr->vName3,tBatchOpr->vData4,tBatchOpr->vName4,tBatchOpr->vData5,tBatchOpr->vName5);
	
	printf("vSQL_Text====[%s]\n",vSQL_Text);

	strcpy(vSQL_Text,"INSERT INTO wBatchOprSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Total_Date,Login_Accept,Op_Code,Phone_No,Id_No,Sm_Code,Login_No,Org_Code,Op_Time,Op_Flag,Op_Note,Data1,Name1,Data2,Name2,Data3,Name3,Data4,Name4,Data5,Name5)");
	strcat(vSQL_Text,"VALUES (");
	strcat(vSQL_Text,"to_number(:v1),:v2,to_number(:v3),'0',");
	strcat(vSQL_Text,":v4,:v5,:v6,:v7,:v8,:v9,:v10,:v11,to_date(:v12,'YYYYMMDD HH24:MI:SS'),:v13,:v14,:v15,:v16,:v17,:v18,:v19,:v20,:v21,:v22,:v23,:v24)");
	EXEC SQL PREPARE Exec_dCheckPre FROM :vSQL_Text;
	EXEC SQL EXECUTE Exec_dCheckPre using
	:chgSeq,	:chgType,	:loginAccept,
	:tBatchOpr->vTotalDate,:tBatchOpr->loginAccept,
	:tBatchOpr->vOpCode,:tBatchOpr->vPhoneNo,
	:tBatchOpr->vIdNo,:tBatchOpr->vSmCode,
	:tBatchOpr->vLoginNo,:tBatchOpr->vOrgCode,
	:tBatchOpr->vOpTime,:tBatchOpr->vOpFlag,
	:tBatchOpr->vOpNote,:tBatchOpr->vData1,
	:tBatchOpr->vName1,:tBatchOpr->vData2,
	:tBatchOpr->vName2,:tBatchOpr->vData3,
	:tBatchOpr->vName3,:tBatchOpr->vData4,
	:tBatchOpr->vName4,
	:tBatchOpr->vData5,:tBatchOpr->vName5;
		
	if(SQLCODE!=0)
	{
		printf("SQLCODE==[%d],SQLERRMSG==[%s]\n",SQLCODE,SQLERRMSG);
		strcpy(retMsg,"插入wBatchOprSend出错");
		return 2;
	}
	return 0;
}

int sendCheckOpr(tWcheckOpr *tCheckOpr, char *chgType, char *loginAccept, char *retMsg)
{
	int  	ret_code=0;
	char 	chgSeq[14+1];
	char 	vSQL_Text[4096+1];
	char 	vTmp_String[4096+1]; 
	
	memset(chgSeq, 			0,	sizeof(chgSeq));
	memset(vSQL_Text, 	0,	sizeof(vSQL_Text));
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	
	
	ret_code=getInterAccept(chgSeq);
	if(ret_code!=0)
	{
		printf("获取接口流水失败\n");
		return 1;
	}	
	printf("接口流水===[%s]\n",chgSeq);

	strcpy(vSQL_Text,"INSERT INTO wCheckOprSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Total_Date,Login_Accept,Org_Code,Login_No,OP_Code,Bank_Code,Check_No,Check_Pay,Op_Time,Op_Note,Org_Id)");
	strcat(vSQL_Text,"VALUES (");
	
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s to_number('%s'),  '%s', to_number('%s'),'%s'",vTmp_String,chgSeq,chgType,loginAccept,UNDEAL);

	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s '%d','%ld','%s','%s',%s,%s,%s,%s,'%s','%s','%lf',to_date('%s','YYYYMMDD HH24:MI:SS'),'%s','%s','%s'",vTmp_String,tCheckOpr->vTotalDate,tCheckOpr->loginAccept,tCheckOpr->vOrgCode,tCheckOpr->vLoginNo,tCheckOpr->vOpCode,tCheckOpr->vBankCode,tCheckOpr->vCheckNo,tCheckOpr->vCheckPay,tCheckOpr->vOpTime,tCheckOpr->vOpNote,tCheckOpr->vOrgId);
	
	printf("vSQL_Text====[%s]\n",vSQL_Text);

	strcpy(vSQL_Text,"INSERT INTO wCheckOprSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Total_Date,Login_Accept,Org_Code,Login_No,OP_Code,Bank_Code,Check_No,Check_Pay,Op_Time,Op_Note,Org_Id)");
	strcat(vSQL_Text,"VALUES (");
	strcat(vSQL_Text,"to_number(:v1),:v2,to_number(:v3),'0',");
	strcat(vSQL_Text,":v4,:v5,:v6,:v7,:v8,,:v9,:v10,:v11,to_date(:v12,'YYYYMMDD HH24:MI:SS'),:v13,:v14)");
	EXEC SQL PREPARE Exec_dCheckPre FROM :vSQL_Text;
	EXEC SQL EXECUTE Exec_dCheckPre using
	:chgSeq,	:chgType,	:loginAccept,
	:tCheckOpr->vTotalDate,:tCheckOpr->loginAccept,
	:tCheckOpr->vOrgCode,:tCheckOpr->vLoginNo,
	:tCheckOpr->vOpCode,:tCheckOpr->vBankCode,
	:tCheckOpr->vCheckNo,:tCheckOpr->vCheckPay,
	:tCheckOpr->vOpTime,
	:tCheckOpr->vOpNote,:tCheckOpr->vOrgId;
		
	if(SQLCODE!=0)
	{
		printf("SQLCODE==[%d],SQLERRMSG==[%s]\n",SQLCODE,SQLERRMSG);
		strcpy(retMsg,"插入wCheckOprSend出错");
		return 2;
	}
	return 0;
}

int sendRelationFavChg(tWrelationFavChg *tRelation, char *chgType, char *loginAccept, char *retMsg)
{
	int  	ret_code=0;
	char 	chgSeq[14+1];
	char 	vSQL_Text[4096+1];
	char 	vTmp_String[4096+1]; 
	
	memset(chgSeq, 			0,	sizeof(chgSeq));
	memset(vSQL_Text, 	0,	sizeof(vSQL_Text));
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	
	
	ret_code=getInterAccept(chgSeq);
	if(ret_code!=0)
	{
		printf("获取接口流水失败\n");
		return 1;
	}	
	printf("接口流水===[%s]\n",chgSeq);

	strcpy(vSQL_Text,"INSERT INTO wRelationFavChgSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Login_Accept,Send_Status,");	
	strcat(vSQL_Text,"MsisDn,Relation_Code,Other_Code,Begin_Date,End_Date,Flag,Deal_Date)");
	strcat(vSQL_Text,"VALUES (");
	
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s to_number('%s'),  '%s', to_number('%s'),'%s'",vTmp_String,chgSeq,chgType,loginAccept,UNDEAL);

	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s '%s','%s','%s',to_date('%s','YYYYMMDD HH24:MI:SS'),to_date('%s','YYYYMMDD HH24:MI:SS'),%s,to_date('%s','YYYYMMDD HH24:MI:SS')",vTmp_String,tRelation->vMsisDn,tRelation->vRelationCode,tRelation->vOtherCode,tRelation->vBeginTime,tRelation->vEndDate,tRelation->vFlag,tRelation->vDealDate);
	
	printf("vSQL_Text====[%s]\n",vSQL_Text);

	strcpy(vSQL_Text,"INSERT INTO wRelationFavChgSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Login_Accept,Send_Status,");	
	strcat(vSQL_Text,"MsisDn,Relation_Code,Other_Code,Begin_Date,End_Date,Flag,Deal_Date)");
	strcat(vSQL_Text,"VALUES (");
	strcat(vSQL_Text,"to_number(:v1),:v2,to_number(:v3),'0',");
	strcat(vSQL_Text,":v4,:v5,:v6,to_date(:v7,'YYYYMMDD HH24:MI:SS'),to_date(:v8,'YYYYMMDD HH24:MI:SS'),,:v9,to_date(:v10,'YYYYMMDD HH24:MI:SS'))");
	EXEC SQL PREPARE Exec_dCheckPre FROM :vSQL_Text;
	EXEC SQL EXECUTE Exec_dCheckPre using
	:chgSeq,	:chgType,	:loginAccept,
	:tRelation->vMsisDn,:tRelation->vRelationCode,
	:tRelation->vOtherCode,:tRelation->vBeginTime,
	:tRelation->vEndDate,
	:tRelation->vFlag,:tRelation->vDealDate;
		
	if(SQLCODE!=0)
	{
		printf("SQLCODE==[%d],SQLERRMSG==[%s]\n",SQLCODE,SQLERRMSG);
		strcpy(retMsg,"插入wRelationFavChgSend出错");
		return 2;
	}
	return 0;
}

int sendTotalFav(twTotalFav *tTotalFav, char *chgType, char *loginAccept, char *retMsg)
{
	int  	ret_code=0;
	char 	chgSeq[14+1];
	char 	vSQL_Text[4096+1];
	char 	vTmp_String[4096+1]; 
	
	memset(chgSeq, 			0,	sizeof(chgSeq));
	memset(vSQL_Text, 	0,	sizeof(vSQL_Text));
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	
	
	ret_code=getInterAccept(chgSeq);
	if(ret_code!=0)
	{
		printf("获取接口流水失败\n");
		return 1;
	}	
	printf("接口流水===[%s]\n",chgSeq);

	strcpy(vSQL_Text,"INSERT INTO wTotalFavSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Phone_No,Order_Code,Id_No,Fav_Type,Op_Code,Login_Accept,Total_Date,Fee_Codes,Sm_Flag,Favour_Fee,Begin_Time,End_Time)");
	strcat(vSQL_Text,"VALUES (");
	
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s to_number('%s'),  '%s', to_number('%s'),'%s'",vTmp_String,chgSeq,chgType,loginAccept,UNDEAL);

	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s '%s','%s','%ld','%s','%s','%ld','%s','%s','%s','%lf','%s','%s'",vTmp_String,tTotalFav->vPhoneNo,tTotalFav->vOrderCode,tTotalFav->vIdNo,tTotalFav->vFavType,tTotalFav->vOpCode,tTotalFav->loginAccept,tTotalFav->vTotalDate,tTotalFav->vFeeCodes,tTotalFav->vSmFlag,tTotalFav->vFavourFee,tTotalFav->vBeginTime,tTotalFav->vEndTime);
	
	printf("vSQL_Text====[%s]\n",vSQL_Text);

	strcpy(vSQL_Text,"INSERT INTO wTotalFavSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Phone_No,Order_Code,Id_No,Fav_Type,Op_Code,Login_Accept,Total_Date,Fee_Codes,Sm_Flag,Favour_Fee,Begin_Time,End_Time)");
	strcat(vSQL_Text,"VALUES (");
	strcat(vSQL_Text,"to_number(:v1),:v2,to_number(:v3),'0',");
	strcat(vSQL_Text,":v4,:v5,:v6,:v7,:v8,:v9,:v10,:v11,:v12,:v13,to_date(:v14,'YYYYMMDD HH24:MI:SS'),to_date(:v15,'YYYYMMDD HH24:MI:SS'))");
	EXEC SQL PREPARE Exec_dCheckPre FROM :vSQL_Text;
	EXEC SQL EXECUTE Exec_dCheckPre using
	:chgSeq,	:chgType,	:loginAccept,
	:tTotalFav->vPhoneNo,:tTotalFav->vOrderCode,
	:tTotalFav->vIdNo,:tTotalFav->vFavType,
	:tTotalFav->vOpCode,:tTotalFav->loginAccept,
	:tTotalFav->vTotalDate,:tTotalFav->vFeeCodes,
	:tTotalFav->vSmFlag,:tTotalFav->vFavourFee,
	:tTotalFav->vBeginTime,:tTotalFav->vEndTime;
		
	if(SQLCODE!=0)
	{
		printf("SQLCODE==[%d],SQLERRMSG==[%s]\n",SQLCODE,SQLERRMSG);
		strcpy(retMsg,"插入wTotalFavSend出错");
		return 2;
	}
	return 0;
}

int sendTotalFavHis(twTotalFavHis *tTotalFavHis, char *chgType, char *loginAccept, char *retMsg)
{
	int  	ret_code=0;
	char 	chgSeq[14+1];
	char 	vSQL_Text[4096+1];
	char 	vTmp_String[4096+1]; 
	
	memset(chgSeq, 			0,	sizeof(chgSeq));
	memset(vSQL_Text, 	0,	sizeof(vSQL_Text));
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	
	
	ret_code=getInterAccept(chgSeq);
	if(ret_code!=0)
	{
		printf("获取接口流水失败\n");
		return 1;
	}	
	printf("接口流水===[%s]\n",chgSeq);

	strcpy(vSQL_Text,"INSERT INTO wTotalFavHisSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Phone_No,Order_Code,Id_No,Fav_Type,Op_Code,Login_Accept,Total_Date,Fee_Codes,Sm_Flag,Favour_Fee,Begin_Time,End_Time)");
	strcat(vSQL_Text,"VALUES (");
	
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s to_number('%s'),  '%s', to_number('%s'),'%s'",vTmp_String,chgSeq,chgType,loginAccept,UNDEAL);

	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s '%s','%s','%ld','%s','%s','%ld','%s','%s','%s','%lf','%s','%s'",vTmp_String,tTotalFavHis->vPhoneNo,tTotalFavHis->vOrderCode,tTotalFavHis->vIdNo,tTotalFavHis->vFavType,tTotalFavHis->vOpCode,tTotalFavHis->loginAccept,tTotalFavHis->vTotalDate,tTotalFavHis->vFeeCodes,tTotalFavHis->vSmFlag,tTotalFavHis->vFavourFee,tTotalFavHis->vBeginTime,tTotalFavHis->vEndTime);
	
	printf("vSQL_Text====[%s]\n",vSQL_Text);

	strcpy(vSQL_Text,"INSERT INTO wTotalFavHisSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Trans_Accept,Send_Status,");	
	strcat(vSQL_Text,"Phone_No,Order_Code,Id_No,Fav_Type,Op_Code,Login_Accept,Total_Date,Fee_Codes,Sm_Flag,Favour_Fee,Begin_Time,End_Time)");
	strcat(vSQL_Text,"VALUES (");
	strcat(vSQL_Text,"to_number(:v1),:v2,to_number(:v3),'0',");
	strcat(vSQL_Text,":v4,:v5,:v6,:v7,:v8,:v9,:v10,:v11,:v12,:v13,to_date(:v14,'YYYYMMDD HH24:MI:SS'),to_date(:v15,'YYYYMMDD HH24:MI:SS'))");
	EXEC SQL PREPARE Exec_dCheckPre FROM :vSQL_Text;
	EXEC SQL EXECUTE Exec_dCheckPre using
	:chgSeq,	:chgType,	:loginAccept,
	:tTotalFavHis->vPhoneNo,:tTotalFavHis->vOrderCode,
	:tTotalFavHis->vIdNo,:tTotalFavHis->vFavType,
	:tTotalFavHis->vOpCode,:tTotalFavHis->loginAccept,
	:tTotalFavHis->vTotalDate,:tTotalFavHis->vFeeCodes,
	:tTotalFavHis->vSmFlag,:tTotalFavHis->vFavourFee,
	:tTotalFavHis->vBeginTime,:tTotalFavHis->vEndTime;
		
	if(SQLCODE!=0)
	{
		printf("SQLCODE==[%d],SQLERRMSG==[%s]\n",SQLCODE,SQLERRMSG);
		strcpy(retMsg,"插入wTotalFavHisSend出错");
		return 2;
	}
	return 0;
}

int sendBillOweAdj(tbillOweAdjDet *tbillOweDet, char *chgType, char *loginAccept, char *retMsg)
{
	int  	ret_code=0;
	char 	chgSeq[14+1];
	char 	vSQL_Text[4096+1];
	char 	vTmp_String[4096+1]; 
	
	memset(chgSeq, 			0,	sizeof(chgSeq));
	memset(vSQL_Text, 	0,	sizeof(vSQL_Text));
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	
	
	ret_code=getInterAccept(chgSeq);
	if(ret_code!=0)
	{
		printf("获取接口流水失败\n");
		return 1;
	}	
	printf("接口流水===[%s]\n",chgSeq);

	strcpy(vSQL_Text,"INSERT INTO wBillOwe_adjOweDetSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Login_Accept,Send_Status,");	
	strcat(vSQL_Text,"Phone_No,Id_No,Contract_No,Fee_Code,Detail_Code,Adj_SumShld,Adj_SumFav,Adj_IncrShld,Adj_IncrFav,Adj_IncrTimes,Adj_IncrDuras)");
	strcat(vSQL_Text,"VALUES (");
	
	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s to_number('%s'),  '%s', to_number('%s'),'%s'",vTmp_String,chgSeq,chgType,loginAccept,UNDEAL);

	memset(vTmp_String, 0,	sizeof(vTmp_String));
	strcpy(vTmp_String,vSQL_Text);
	sprintf(vSQL_Text,"%s '%s','%ld','%ld','%s','%s','%s','%s','%s','%s','%s','%s'",vTmp_String,tbillOweDet->vPhoneNo,tbillOweDet->vIdNo,tbillOweDet->vContractNo,tbillOweDet->vFeeCode,tbillOweDet->vDetailCode,tbillOweDet->vAdjSumShid,tbillOweDet->vAdjSumFav,tbillOweDet->vAdjIncrShld,tbillOweDet->vAdjINcrFav,tbillOweDet->vAdjIncrTimes,tbillOweDet->vAdjIncrDuras);
	
	printf("vSQL_Text====[%s]\n",vSQL_Text);

	strcpy(vSQL_Text,"INSERT INTO wTotalFavHisSend ");
	strcat(vSQL_Text,"(Chg_Seq,	Chg_Type,Login_Accept,Send_Status,");	
	strcat(vSQL_Text,"Phone_No,Id_No,Contract_No,Fee_Code,Detail_Code,Adj_SumShld,Adj_SumFav,Adj_IncrShld,Adj_IncrFav,Adj_IncrTimes,Adj_IncrDuras)");
	strcat(vSQL_Text,"VALUES (");
	strcat(vSQL_Text,"to_number(:v1),:v2,to_number(:v3),'0',");
	strcat(vSQL_Text,":v4,:v5,:v6,:v7,:v8,:v9,:v10,:v11,:v12,:v13,:v14)");
	EXEC SQL PREPARE Exec_dCheckPre FROM :vSQL_Text;
	EXEC SQL EXECUTE Exec_dCheckPre using
	:chgSeq,	:chgType,	:loginAccept,
	:tbillOweDet->vPhoneNo,:tbillOweDet->vIdNo,
	:tbillOweDet->vContractNo,:tbillOweDet->vFeeCode,
	:tbillOweDet->vDetailCode,:tbillOweDet->vAdjSumShid,
	:tbillOweDet->vAdjSumFav,:tbillOweDet->vAdjIncrShld,
	:tbillOweDet->vAdjINcrFav,
	:tbillOweDet->vAdjIncrTimes,:tbillOweDet->vAdjIncrDuras;
		
	if(SQLCODE!=0)
	{
		printf("SQLCODE==[%d],SQLERRMSG==[%s]\n",SQLCODE,SQLERRMSG);
		strcpy(retMsg,"插入wTotalFavHisSend出错");
		return 2;
	}
	return 0;
}


int sendMsg(char *tableName, char *sqlStr1, char *sqlStr2, char *retMsg)
{
	char  synType[1+1];
	
	memset(synType,0,sizeof(synType));

	if(getTableOusCfg(tableName,synType,retMsg) != 0)
	{
		return 1;
	}
	
	if(strcmp(synType,"S")==0)
	{
		EXEC SQL PREPARE sql1 from :sqlStr1;
		EXEC SQL EXECUTE sql1;
		if(SQLCODE!=0)
		{
			return 2;
		}
	}else if(strcmp(synType,"L")==0)
	{
		EXEC SQL PREPARE sql2 from :sqlStr2;
		EXEC SQL EXECUTE sql2;
		if(SQLCODE!=0)
		{
			return 3;
		}		
	}

	return 0;
}

/**
 *
 */
char *getTableSynCfg(char *tableName,char *retCode,char *retMsg)
{
    char 	sqlBuf[1024+1];                         /* SQL语句                  */
    char	synType[1+1];
    strcpy(retCode,"000000");

    memset(sqlBuf,	0, 	sizeof(sqlBuf));
    memset(synType,	0,	sizeof(synType));

    if ( tableName == NULL )
    {
    	printf("getTableSynCfg:输入参数不能为空(NULL)!\n");
		strcpy(retCode,"000002");
		sprintf(retMsg,"getTableSynCfg:输入参数不能为空(NULL)!\n");
		return NULL;
    }

    EXEC SQL select Syn_Type into :synType
    		   from sTableSynCfg
    		  where table_name = :tableName;
	if(SQLCODE != OK || SQLROWS != 1)
	{
		printf("getTableSynCfg:读取数据表同步配置信息出错[%s]!\n", tableName);
		strcpy(retCode,"000002");
		sprintf(retMsg,"getTableSynCfg:读取数据表同步配置信息出错[%s]!\n", tableName);
		return NULL;
	}

	return &synType[0];
}

