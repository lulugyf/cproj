#include "llayerStruct.h"


extern "C" ETYPE CheckFuncRight(const char *loginNo, const char *opCode)
{
	ETYPE  iRet=0;

	ub4 iCount = 0;

	DBUG_ENTER("CLRight::CheckFuncRight");

	DBUG_PRINT("CheckFuncRight", ("loginNo=[%s][%s]",loginNo, opCode));

	g_Command->CommondText = "SELECT count(*) "
	                         "  FROM bs_LoginRole_rel a, bs_RolePdom_rel b, bs_Function_dict c "
							 " WHERE a.login_no= :loginNo "
							 "   AND c.function_code = :opCode "
							 "	 and a.role_code = b.role_code "
							"	 and b.popedom_code = c.popedom_code ";
	g_Command->CommondType = adCmdText;

	try
	{
		g_Command->I(loginNo, (ub4)strlen((const char*)loginNo))
			->I(opCode, (ub4)strlen((const char*)opCode));
	}
	catch(CLException e)
	{
		DBUG_RETURN(e.GetErrorNo());
	}
	try
	{
		g_Command->O(iCount, sizeof(iCount));
	}
	catch(CLException e)
	{
		DBUG_RETURN(e.GetErrorNo());
	}
	if ((iRet=g_Command->Execute()) != 0)
	{
		int oraErrorCode;
		char errMsg[512];
		g_Command->GetOraError(&oraErrorCode, errMsg);
		DBUG_PRINT("CheckFuncRight", ("oraErrorCode=[%d], errMsg=[%s][%d]\n", oraErrorCode, errMsg,iRet));
		DBUG_RETURN(iRet);
	}
	CLRecordSet* recordSet = g_Command->GetRecordSet();
	iRet = 0;
	if ( (iRet=recordSet->FetchNext(1)) != 0)
	{
		DBUG_PRINT("CheckFuncRight", ("iRet=recordSet->FetchNext[%d]", iRet));
		g_Command->Close();
		DBUG_RETURN(CLError::EB_RIGHT_LOGIN);
	}
	g_Command->Close();

	if (iCount <= 0)
	{
		DBUG_RETURN(CLError::EB_RIGHT_LOGIN);
	}

	DBUG_RETURN(0);
}

//检查列级权限
//有权限返回零，否则返回非零
extern "C" ETYPE CheckColumnRight(const char *loginNo, ub8 columnId)
{
	return 0;
}

//检查功能权限
//loginPasswd加密后的密码
ETYPE CLRight::CheckFuncPwdRight(const char *loginNo,
							  const char *loginPasswd, const char *opCode) throw()
{
	ETYPE  iRet=0;

	char loginPasswdDb[16+1];

	DBUG_ENTER("CLRight::CheckFuncPwdRight");

	memset(loginPasswdDb, 0, sizeof(loginPasswdDb));

	DBUG_PRINT("CheckFuncPwdRight", ("loginNo=[%s]",loginNo));
	DBUG_PRINT("CheckFuncPwdRight", ("loginPasswd=[%s]",loginPasswd));
	DBUG_PRINT("CheckFuncPwdRight", ("opCode=[%s]",opCode));

	g_Command->CommondText = "SELECT login_password "
		                "  FROM bs_LoginMsg_dict "
						" WHERE login_no = :loginNo";
	g_Command->CommondType = adCmdText;

	try
	{
		g_Command->I(loginNo, (ub4)strlen((const char*)loginNo));
	}
	catch(CLException e)
	{
		DBUG_RETURN(e.GetErrorNo());
	}
	try
	{
		g_Command->O(loginPasswdDb, sizeof(loginPasswdDb));
	}
	catch(CLException e)
	{
		DBUG_RETURN(e.GetErrorNo());
	}
	if ((iRet=g_Command->Execute()) != 0)
	{
		int oraErrorCode;
		char errMsg[512];
		g_Command->GetOraError(&oraErrorCode, errMsg);
		DBUG_PRINT("CheckFuncPwdRight", ("oraErrorCode=[%d], errMsg=[%s]\n", oraErrorCode, errMsg));
		DBUG_PRINT("CheckFuncPwdRight", ("Execute dLoginMsg ErrCode[%ld]", iRet));
		DBUG_RETURN(iRet);
	}
	CLRecordSet* recordSet = g_Command->GetRecordSet();
	iRet = 0;
	if ( (iRet=recordSet->FetchNext(1)) != 0)
	{
		DBUG_PRINT("CheckFuncPwdRight", ("iRet=recordSet->FetchNext[%ld]", iRet));
		g_Command->Close();
		DBUG_RETURN(CLError::EB_RIGHT_LOGIN);
	}
	g_Command->Close();

	if (strcmp( (const char*)loginPasswd, (const char*)loginPasswdDb ) != 0)
	{
		DBUG_RETURN(CLError::EB_RIGHT_LOGIN);
	}

	if ((iRet = CheckFuncRight((const char*)loginNo, (const char*)opCode)) != 0)
	{
		DBUG_RETURN(CLError::EB_RIGHT_FUNC);
	}
	DBUG_RETURN(0);
}
