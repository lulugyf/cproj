//Xercesc 头文件
#include "CLTux.h"

#ifdef HAVE_DISPATCH

extern "C"
{
#include "pubdef.h"
#include "publicShmRoute.h"
}

#endif

/*
C:\bea\tuxedo8.1\bin\buildserver -s sUnifyView -o UnifyView.exe -f UnifyView.cpp -f "-DNOWHAT=1 -W3 -Od -DWIN32 -MDd -Zi /EHsc /D WIN32 /I
E:\4.program\VC\BossLib\include /I 
E:\4.program\VC\BossTuxLib\include /I D:\oracle\ora92\oci\include  
E:\4.program\VC\BossLib\lib\BossLib.lib 
E:\4.program\VC\BossTuxLib\lib\BossTuxLib.lib 
D:\oracle\ora92\oci\lib\msvc\oci.lib"
*/

//分配TUXEDO内存
inline FBFR32 *CLTux::TuxMemAlloc(FBFR32 **transOUT, ub4 memSize)
{
	*transOUT=(FBFR32 *)tpalloc((char*)FMLTYPE32,NULL,memSize);
	return *transOUT;
}

//处理默认连接
ETYPE CLTux::sChkDBLogin()
{
	ETYPE iRet=0;

	DBUG_ENTER("CLTux::sChkDBLogin");

	g_Command->CommondText = "select 1 from dual";
	g_Command->CommondType = adCmdText;
	if ((iRet=g_Command->Execute()) == 0)
	{
		g_Command->Close();
		DBUG_RETURN(0);
	}
	else
	{
		DBUG_PRINT("sChkDBLogin", ("Execute ErrCode[%ld]", iRet));
		CLConnection *ptActiveConnection = g_Command->ActiveConnection;
		ptActiveConnection->Close();
		DBUG_RETURN( ptActiveConnection->Open(ptActiveConnection->GetConnDbType(), ptActiveConnection->IsDefaultConn(),ptActiveConnection->GetConnName()));
	}
}


ETYPE CLTux::GetFuncName(const char*opCode, char* funcName) throw()
{
	ETYPE iRet=0;
	char opCodeTmp[5+1];
	char funcNameTmp[30+1];

	DBUG_ENTER("GetFuncName");

	memset(opCodeTmp, 0, sizeof(opCodeTmp));
	memset(funcNameTmp, 0, sizeof(funcNameTmp));
	strcpy(opCodeTmp, opCode);
	DBUG_PRINT("GetFuncName", ("opCodeTmp=[%s]", opCodeTmp));
	g_Command->CommondType = adCmdText;
	g_Command->CommondText = "SELECT function_name"
	                         "  FROM bs_function_dict"
							 " WHERE function_code = :function_code";
	try
	{
		g_Command->I(opCodeTmp, (ub4)strlen(opCodeTmp));
	}
	catch(CLException e)
	{
		DBUG_RETURN(e.GetErrorNo());
	}

	try
	{
		g_Command->O(funcNameTmp, sizeof(funcNameTmp));
	}
	catch(CLException e)
	{
		DBUG_RETURN(e.GetErrorNo());
	}
	if ((iRet=g_Command->Execute()) != 0)
	{
		DBUG_RETURN(iRet);
	}

	printf("__________________22222222____________________\n");
	if ( (iRet=g_Command->GetRecordSet()->FetchNext(1)) != 0)
	{
		DBUG_RETURN(iRet);
	}
	CLString::Trim(funcNameTmp);
	strcpy(funcName, funcNameTmp);
	g_Command->Close();
	DBUG_RETURN(iRet);
}

//得到工号的编码
ETYPE CLTux::GetLoginMsg(const char* psLoginNo, char* psOrgCode, char* psPowerCode) throw()
{
	ETYPE iRet=0;
	char sLoginNoTmp[6+1];
	char sOrgCodeTmp[9+1];
	char sPowerCodeTmp[30+1];

	DBUG_ENTER("GetLoginOrgCode");

	memset(sLoginNoTmp, 0, sizeof(sLoginNoTmp));
	memset(sOrgCodeTmp, 0, sizeof(sOrgCodeTmp));
	strcpy(sLoginNoTmp, psLoginNo);
	DBUG_PRINT("GetLoginOrgCode", ("sLoginNoTmp=[%s]", sLoginNoTmp));
	g_Command->CommondType = adCmdText;
	g_Command->CommondText = "SELECT a.group_id, b.role_code"
	                         "  FROM bs_LoginMsg_dict a, bs_LoginRole_rel b"
							 " WHERE a.login_no = :login_no "
							 "   and a.login_no = b.login_no ";
	try
	{
		g_Command->I(psLoginNo, (ub4)strlen(psLoginNo));
	}
	catch(CLException e)
	{
		DBUG_RETURN(e.GetErrorNo());
	}

	try
	{
		g_Command->O(sOrgCodeTmp, sizeof(sOrgCodeTmp))
				->O(sPowerCodeTmp, sizeof(sPowerCodeTmp));
	}
	catch(CLException e)
	{
		DBUG_RETURN(e.GetErrorNo());
	}
	if ((iRet=g_Command->Execute()) != 0)
	{
		DBUG_RETURN(iRet);
	}

	if ( (iRet=g_Command->GetRecordSet()->FetchNext(1)) != 0)
	{
		DBUG_RETURN(iRet);
	}
	CLString::Trim(sOrgCodeTmp);
	strcpy(psOrgCode, sOrgCodeTmp);
	strcpy(psPowerCode, sPowerCodeTmp);
	g_Command->Close();
	DBUG_RETURN(iRet);
}

#ifdef HAVE_DISPATCH
typedef struct tagClearUpParam
{
#ifndef DBUG_OFF
	const char *_db_func_;
	const char *_db_file_;
	ub4 _db_level_;
#endif
	CLTuxInParams *ptTuxInParams;
}TClearUpParam;

/*
 *     内部函数，用于清空由于tpforwrad而需要释放的内存。
 */
static  void ClearUp(void*param)
{
	TClearUpParam *ptClearUpParam = (TClearUpParam *)param;

#ifndef DBUG_OFF
	CLDbug::_db_return_ (__LINE__,
				&(ptClearUpParam->_db_func_),
				&(ptClearUpParam->_db_file_),
				&(ptClearUpParam->_db_level_));
#endif
	
	delete ptClearUpParam->ptTuxInParams;
}
#endif

//TUXEDO入口函数。
void CLTux::TuxedoDeal(TTuxedoDeal *tuxedoDeal) throw()
{
	ETYPE iRet;
	int i=0;
	FBFR32 *transIN = NULL, *transOUT = NULL;
	char	retCode[20+1];
	char	retMsg[256];

	const char * xmlBuf = NULL;
	CLTuxInParams *tuxInParams=NULL;
	CLTuxOutParams *tuxOutParams=NULL;

#ifdef HAVE_DISPATCH
	/*路由判断*/
	char sKeyValue[ROUTE_KEY_VALUE_LENGTH+1];	/*路由键值*/
	const XMLCh* psxFirstRouteValue;
	int iRouteCode=0;
	TClearUpParam tClearUpParam;
#endif

	DBUG_ENTER("CLTux::TuxedoDeal");
	DBUG_PRINT("TuxedoDeal",("开始执行服务[%s][%d]\n",
		tuxedoDeal->serviceName, tuxedoDeal->bIsDispatch));

	memset(retCode, 0, sizeof(retCode));
	memset(retMsg, 0, sizeof(retMsg));

	transIN = (FBFR32 *)tuxedoDeal->transb->data;

	tuxInParams = new CLTuxInParams(transIN);
	if (!tuxInParams)
	{
		sprintf(retCode, "%ld", CLError::E_MEMORY_LACK);
		strcpy(retMsg, CLError::GetErrorMsg(CLError::E_MEMORY_LACK));
		goto end_valid;
	}
	if (!tuxInParams->IsInitialize())
	{
		iRet = CLError::E_XML_ELTAG_INPARAMS;
		sprintf(retCode, "%ld", iRet);
		strcpy(retMsg, CLError::GetErrorMsg(iRet));
		goto end_valid;
	}
	
#ifdef HAVE_DISPATCH
	if (tuxedoDeal->bIsDispatch)
	{
		memset(sKeyValue, 0, sizeof(sKeyValue));
		if ((iRouteCode == 0) && ((psxFirstRouteValue = tuxInParams->GetFirstValueByCode(CLDomain::DMI_USER_ID)) != NULL))
		{
			StrX strX(psxFirstRouteValue);
			strcpy(sKeyValue, strX.localForm());
			CLString::Trim(sKeyValue);
			if (sKeyValue[0] != '\0')
			{
				iRouteCode = ROUTE_ROUTE_CODE_USERID;
			}
		}

		if ((iRouteCode == 0) && ((psxFirstRouteValue = tuxInParams->GetFirstValueByCode(CLDomain::DMI_CON_ID)) != NULL))
		{
			StrX strX(psxFirstRouteValue);
			strcpy(sKeyValue, strX.localForm());

			CLString::Trim(sKeyValue);
			if (sKeyValue[0] != '\0')
			{
				iRouteCode = ROUTE_ROUTE_CODE_CONID;
			}
		}

		if ((iRouteCode == 0) && ((psxFirstRouteValue = tuxInParams->GetFirstValueByCode(CLDomain::DMI_PHONE_NO)) != NULL))
		{
			StrX strX(psxFirstRouteValue);
			strcpy(sKeyValue, strX.localForm());

			CLString::Trim(sKeyValue);
			if (sKeyValue[0] != '\0')
			{
				iRouteCode = ROUTE_ROUTE_CODE_PHONE;
			}
		}

		if ((iRouteCode == 0) && ((psxFirstRouteValue = tuxInParams->GetFirstValueByCode(CLDomain::DMI_CUST_ID)) != NULL))
		{
			StrX strX(psxFirstRouteValue);
			strcpy(sKeyValue, strX.localForm());

			CLString::Trim(sKeyValue);
			if (sKeyValue[0] != '\0')
			{
				iRouteCode = ROUTE_ROUTE_CODE_CUSTID;
			}
		}

		if ((iRouteCode == 0) && ((psxFirstRouteValue = tuxInParams->GetFirstValueByCode(CLDomain::DMI_REGION_CODE)) != NULL))
		{
			StrX strX(psxFirstRouteValue);
			strcpy(sKeyValue, strX.localForm());

			CLString::Trim(sKeyValue);
			if (sKeyValue[0] != '\0')
			{
				iRouteCode = ROUTE_ROUTE_CODE_REGION;
			}
		}

		if ((iRouteCode == 0) && ((psxFirstRouteValue = tuxInParams->GetFirstValueByCode(CLDomain::DMI_LOGIN_NO)) != NULL))
		{
			StrX strX(psxF	irstRouteValue);
			strcpy(sKeyValue, strX.localForm());

			CLString::Trim(sKeyValue);
			if (sKeyValue[0] != '\0')
			{
				iRouteCode = ROUTE_ROUTE_CODE_LOGINNO;
			}
		}
		
		if (iRouteCode == 0)
		{
			if (tuxInParams->GetPubFirstValueByCode(CLDomain::DMI_LOGIN_NO, sKeyValue) == NULL)
			{
				sprintf(retCode, "%ld", CLError::EB_RIGHT_LOGIN);
				strcpy(retMsg, CLError::GetErrorMsg(CLError::EB_RIGHT_LOGIN));
				goto end_valid;
			}
			iRouteCode = ROUTE_ROUTE_CODE_REGION;
		}

#ifndef DBUG_OFF
		tClearUpParam._db_func_ = _db_func_;
		tClearUpParam._db_file_ = _db_file_;
		tClearUpParam._db_level_= _db_level_;
#endif
		tClearUpParam.ptTuxInParams = tuxInParams;

		DBUG_PRINT("TuxedoDeal",("iRouteCode[%d][%s]",iRouteCode, sKeyValue));

		if ((iRet = DispatchPartition(tuxedoDeal->serviceName, iRouteCode,
			sKeyValue, tuxedoDeal->transb, tuxedoDeal->dbLabel,
			ROUTE_DB_CONNECT_LONG, ROUTE_FLAGS_DYNAMIC_VALUE, ClearUp, &tClearUpParam)) != 0)
		{
			sprintf(retCode, "%ld", iRet);
			strcpy(retMsg, "没有有效的路由查询数据，请确认数据是否正确!");
			goto end_valid;
		}
	}
#endif

	strcpy(retCode,	"000000");
	strcpy(retMsg,	"调用成功");

	if ((tuxedoDeal->flags & TUX_DEAL_FLAG_CONNECT) != 0)
	{
		if (g_Command == NULL)
		{
			sprintf(retCode, "%ld", CLError::E_DB_SQL_NOCONNECT);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_DB_SQL_NOCONNECT));
			goto end_valid;
		}
		if ( (iRet = sChkDBLogin()) != 0)
		{
			sprintf(retCode, "%ld", iRet);
			strcpy(retMsg, CLError::GetErrorMsg(iRet));
			goto end_valid;
		}
	}
	else
	{
		if ( (iRet=tuxedoDeal->ptDefaultConn->Open(tuxedoDeal->dbLabel,tuxedoDeal->iConnDbType,tuxedoDeal->bIsDefaultConn, tuxedoDeal->sConnName)) != 0)
		{
			sprintf(retCode, "%ld", CLError::E_DB_SQL_NOCONNECT);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_DB_SQL_NOCONNECT));
			goto end_valid;
		}
	}

	/*主要程序处理开始*/
	TBusiFuncParam busiFuncParam;
	memset(&busiFuncParam, 0, sizeof(TBusiFuncParam));

	if (tuxInParams->GetPubFirstValueByCode(CLDomain::DMI_LOGIN_NO, busiFuncParam.sLoginNo) == NULL)
	{
		sprintf(retCode, "%ld", CLError::EB_RIGHT_LOGIN);
		strcpy(retMsg, CLError::GetErrorMsg(CLError::EB_RIGHT_LOGIN));
		goto end_valid;
	}

	if (tuxInParams->GetPubFirstValueByCode(CLDomain::DMI_LOGIN_PASSWORD, busiFuncParam.sLoginPasswd) == NULL)
	{
		sprintf(retCode, "%ld", CLError::EB_RIGHT_LOGIN);
		strcpy(retMsg, CLError::GetErrorMsg(CLError::EB_RIGHT_LOGIN));
		goto end_valid;
	}

	if (tuxInParams->GetPubFirstValueByCode(CLDomain::DMI_FUNCTION_CODE, busiFuncParam.sOpCode) == NULL)
	{
		sprintf(retCode, "%ld", CLError::EB_RIGHT_FUNC);
		strcpy(retMsg, CLError::GetErrorMsg(CLError::EB_RIGHT_FUNC));
		goto end_valid;
	}

	printf("________[%s][%s][%s]________\n", busiFuncParam.sOpCode, busiFuncParam.sLoginNo, busiFuncParam.sPowerCode);
//	if (GetFuncName(busiFuncParam.sOpCode, busiFuncParam.sFuncName) != 0)
//	{
//		sprintf(retCode, "%ld", CLError::EB_RIGHT_FUNCNAME);
//		strcpy(retMsg, CLError::GetErrorMsg(CLError::EB_RIGHT_FUNCNAME));
//		goto end_valid;
//	}

	strcpy(busiFuncParam.sFuncName, "MYTEST");
	printf("_______GetLoginMsg_________\n");

//	if (GetLoginMsg(busiFuncParam.sLoginNo, busiFuncParam.sOrgCode, busiFuncParam.sPowerCode) != 0)
//	{
//		sprintf(retCode, "%ld", CLError::EB_RIGHT_FUNCNAME);
//		strcpy(retMsg, CLError::GetErrorMsg(CLError::EB_RIGHT_FUNCNAME));
//		goto end_valid;
//	}

	strcpy(busiFuncParam.sOrgCode, "111000000");
	strcpy(busiFuncParam.sPowerCode, "100000");

	printf("_____[%d]_______\n", tuxedoDeal->flags & TUX_DEAL_FLAG_RIGHT);
	//权限处理
//	if ((tuxedoDeal->flags & TUX_DEAL_FLAG_RIGHT) != 0)
//	{
//		printf("______________[%s][%s][%s]_______________\n", busiFuncParam.sLoginNo, busiFuncParam.sLoginPasswd, busiFuncParam.sOpCode);
//		if ( (iRet = CLRight::CheckFuncPwdRight(busiFuncParam.sLoginNo, busiFuncParam.sLoginPasswd, busiFuncParam.sOpCode)) != 0)
//		{
//			sprintf(retCode, "%ld", iRet);
//			printf("____________[%s]__________\n", retCode);
//			strcpy(retMsg, CLError::GetErrorMsg(iRet));
//			goto end_valid;
//		}
//	}

	printf("_______________[%s][%s]_________\n", busiFuncParam.sOpCode, busiFuncParam.sFuncName);

	tuxOutParams = new CLTuxOutParams(busiFuncParam.sOpCode, busiFuncParam.sFuncName);
	if (!tuxOutParams)
	{
		sprintf(retCode, "%ld", CLError::E_MEMORY_LACK);
		strcpy(retMsg, CLError::GetErrorMsg(CLError::E_MEMORY_LACK));
		printf("_____________[%s]____[%s]___\n", retCode, retMsg);

		goto end_valid;
	}
	
	printf("\n\n\n--------[%s]--------\n\n\n", tuxOutParams->ParamToXml());
	if (!tuxOutParams->IsInitialize())
	{
		sprintf(retCode, "%ld", CLError::E_MEMORY_LACK);
		strcpy(retMsg, CLError::GetErrorMsg(CLError::E_MEMORY_LACK));
		goto end_valid;
	}

	printf("\n\n\n--------[%s]--------\n\n\n", tuxOutParams->ParamToXml());

	busiFuncParam.tuxInParams = tuxInParams;
	busiFuncParam.tuxOutParams = tuxOutParams;
	strcpy(busiFuncParam.retCode, "000000");
	strcpy(busiFuncParam.retMsg, "调用成功");
	strcpy(busiFuncParam.infoCode, "000000");
	strcpy(busiFuncParam.infoMsg, "调用成功");

	DBUG_PRINT("TuxedoDeal", ("BusiFunc begin"));
	if ((iRet = tuxedoDeal->BusiFunc(&busiFuncParam)) != 0)
	{
		strcpy(retCode, busiFuncParam.retCode);
		strcpy(retMsg, busiFuncParam.retMsg);
		goto end_valid;
	}
	DBUG_PRINT("TuxedoDeal", ("BusiFunc success"));
	xmlBuf = tuxOutParams->ParamToXml();
end_valid:
	printf("_____________________________________________________\n");
	printf("--[%s]--\n", xmlBuf);
	if (xmlBuf)
	{
		DBUG_PRINT("TuxedoDeal",("xmlBuf[%s]\n",xmlBuf));
		if (TuxMemAlloc(&transOUT, (ub4)(strlen(xmlBuf) * 3)) == NULL)
		{
			sprintf(retCode, "%ld", CLError::E_MEMORY_LACK);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_MEMORY_LACK));
			goto end_valid;
		}
		if(Fadd32(transOUT,GPARM32_0,(char*)xmlBuf,(FLDLEN32)0) == -1)
		{
			sprintf(retCode, "%ld", CLError::E_TUX_FADD);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_TUX_FADD));
		}
		if(Fadd32(transOUT,GPARM32_1,(char*)busiFuncParam.infoCode,(FLDLEN32)0) == -1)
		{
			sprintf(retCode, "%ld", CLError::E_TUX_FADD);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_TUX_FADD));
		}
		if(Fadd32(transOUT,GPARM32_2,(char*)busiFuncParam.infoMsg,(FLDLEN32)0) == -1)
		{
			sprintf(retCode, "%ld", CLError::E_TUX_FADD);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_TUX_FADD));
		}
	}
	else
	{
		DBUG_PRINT("TuxedoDeal",("xmlBuf[NULL]\n"));
		if (TuxMemAlloc(&transOUT, (ub4)(4096)) == NULL)
		{
			sprintf(retCode, "%ld", CLError::E_MEMORY_LACK);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_MEMORY_LACK));
			goto end_valid;
		}
		if(Fadd32(transOUT,GPARM32_0,(char*)"",(FLDLEN32)0) == -1)
		{
			sprintf(retCode, "%ld", CLError::E_TUX_FADD);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_TUX_FADD));
		}
		if(Fadd32(transOUT,GPARM32_1,(char*)"0",(FLDLEN32)0) == -1)
		{
			sprintf(retCode, "%ld", CLError::E_TUX_FADD);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_TUX_FADD));
		}
		if(Fadd32(transOUT,GPARM32_2,(char*)"",(FLDLEN32)0) == -1)
		{
			sprintf(retCode, "%ld", CLError::E_TUX_FADD);
			strcpy(retMsg, CLError::GetErrorMsg(CLError::E_TUX_FADD));
		}
	}

	DBUG_PRINT("TuxedoDeal", ("BusiFunc flags begin"));
	if ((tuxedoDeal->flags & TUX_DEAL_FLAG_CONNECT) == 0)
	{
		tuxedoDeal->ptDefaultConn->Close();
	}
	Fchg32(transOUT,SVC_ERR_NO32,0,retCode,(FLDLEN32)0);
	Fchg32(transOUT,SVC_ERR_MSG32,0,retMsg,(FLDLEN32)0);

	DBUG_PRINT("TuxedoDeal", ("delete tuxInParams"));
	if (tuxInParams)
	{
		delete tuxInParams;
	}

	DBUG_PRINT("TuxedoDeal", ("delete tuxOutParams"));
	if (tuxOutParams)
	{
		delete tuxOutParams;
	}

	DBUG_PRINT("TuxedoDeal", ("DBUG_LEAVE"));
	printf("----------[%d]------1----\n", __LINE__);
//	DBUG_LEAVE;
	printf("----------[%d]------2----\n", __LINE__);

	DBUG_PRINT("TuxedoDeal", ("tpreturn"));
	tpreturn(TPSUCCESS,0,(char *)transOUT,0L,0);
}


