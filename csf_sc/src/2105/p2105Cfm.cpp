#include "allBCP.h"
//#include "libborder.h"
//ORDER_COMMLIB_INIT
//402012731-402012750
/*
���ܣ���Ӽ��ź�����
���룺
�����
���ڣ�
���ߣ�
�޸�:

{"BUSI_MODEL":{},
"OPR_INFO":{}
}


*/
utype* p2105AddCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo)
{
    LOG_FUNC("BP", puInParam, ptCtrlInfo, NULL);

	uAutoPtr outuap(uInit(0));
	uAutoPtr uOprInfo(uInit(0));//�����й�����OPR_INFO
	uAutoPtr uBusiInfo(uInit(0));//�����е�BUSI_MODEL
	uAutoPtr uOutSpeciallist(uInit(0));
	uAutoPtr outCustInfo(uInit(0));
	uAutoPtr outGrpCustInfo(uInit(0));
	
	uBusiInfo=utClone(utGetStructByDir(puInParam, "BUSI_MODEL"));
	uOprInfo=utClone(utGetStructByDir(puInParam, "OPR_INFO"));
	
	outCustInfo = cQCustInfoByCustId(uBusiInfo,ptCtrlInfo);
	if(ptCtrlInfo->iSqlRows == 0)
	{
		throw(appException(406100027, "�ÿͻ���Ϣ������!"));	
	}
	
	outGrpCustInfo = cQGrpCustInfoByCustId(uBusiInfo,ptCtrlInfo);
	if(ptCtrlInfo->iSqlRows == 0)
	{
		throw(appException(406107101, "���ſͻ���Ϣ������!!"));	
	}
	
	uOutSpeciallist = cQCustSpeciallistInfoById(uBusiInfo,ptCtrlInfo);
	
	if(ptCtrlInfo->iSqlRows != 0)
	{
		throw(appException(402011913, "���û�Ϊ�������û���������ӣ�"));	
	}
	
	utAddLong(uBusiInfo,"UPDATE_ACCEPT",utGetLong(uOprInfo,"LOGIN_ACCEPT"));
	utAddStr(uBusiInfo,"UPDATE_LOGIN",utGetStr(uOprInfo,"LOGIN_NO"));
	utAddStr(uBusiInfo,"UPDATE_CODE",utGetStr(uOprInfo,"OP_CODE"));
	utAddStr(uBusiInfo,"UPDATE_TIME",utGetStr(uOprInfo,"OP_TIME"));
	
	char sop_date[8+1];
	int op_date = 0;
	strncpy(sop_date, utGetStr(uOprInfo,"OP_TIME"), 8);
	/****************/
	sop_date[8] = '\0';
	/****************/
	op_date=atoi(sop_date);
	
	utAddInt(uBusiInfo,"UPDATE_DATE",op_date);
	utAddStr(uBusiInfo,"UPDATE_TYPE","I");
	
	
	utAddStr(uBusiInfo,"EFF_DATE",sop_date);
	utAddStr(uBusiInfo,"EXP_DATE","20991231");
	utAddStr(uBusiInfo,"FINISH_FLAG"," ");
	utAddStr(uBusiInfo,"REGISTOR_NAME"," ");
	utAddStr(uBusiInfo,"REMARK"," ");
	
	utAddLong(uBusiInfo,"LOGIN_ACCEPT",utGetLong(uOprInfo,"LOGIN_ACCEPT"));
	utAddStr(uBusiInfo,"OP_CODE",utGetStr(uOprInfo,"OP_CODE"));
	utAddStr(uBusiInfo,"LOGIN_NO",utGetStr(uOprInfo,"LOGIN_NO"));
	utAddStr(uBusiInfo,"OP_TIME",utGetStr(uOprInfo,"OP_TIME"));
	
	//����켣����
	cICustSpeciallistInfoHis(uBusiInfo,ptCtrlInfo);
	cICustSpeciallistInfo(uBusiInfo,ptCtrlInfo);
	
	return NULL;
}
/*
���ܣ�ɾ�����ź�����
���룺
�����
���ڣ�
���ߣ�
�޸�:
*/
utype* p2105DelCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo)
{
    LOG_FUNC("BP", puInParam, ptCtrlInfo, NULL);

  
  uAutoPtr outuap(uInit(0));
	uAutoPtr uOprInfo(uInit(0));//�����й�����OPR_INFO
	uAutoPtr uBusiInfo(uInit(0));//�����е�BUSI_MODEL
	
	uBusiInfo=utClone(utGetStructByDir(puInParam, "BUSI_MODEL"));
	uOprInfo=utClone(utGetStructByDir(puInParam, "OPR_INFO"));
	
	utAddLong(uBusiInfo,"UPDATE_ACCEPT",utGetLong(uOprInfo,"LOGIN_ACCEPT"));
	utAddStr(uBusiInfo,"UPDATE_LOGIN",utGetStr(uOprInfo,"LOGIN_NO"));
	utAddStr(uBusiInfo,"UPDATE_CODE",utGetStr(uOprInfo,"OP_CODE"));
	utAddStr(uBusiInfo,"UPDATE_TIME",utGetStr(uOprInfo,"OP_TIME"));
	
	char sop_date[8+1];
	int op_date = 0;
	strncpy(sop_date, utGetStr(uOprInfo,"OP_TIME"), 8);
	op_date=atoi(sop_date);
	
	utAddInt(uBusiInfo,"UPDATE_DATE",op_date);
	utAddStr(uBusiInfo,"UPDATE_TYPE","D");
	
	//����켣����
	cICustSpeciallistInfoHisbak(uBusiInfo,ptCtrlInfo);
	cDCustSpeciallistInfo(uBusiInfo,ptCtrlInfo);
    return NULL;
}

/*
���ܣ����ź��������
���룺
�����
���ڣ�
���ߣ�
�޸�:
*/ 
extern "C" utype* p2105Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo)
{
    LOG_FUNC("BP", puInParam, ptCtrlInfo, NULL);
	L4C_TRACE("------==p2105Cfm begin!==-------");
	if(strcmp(utGetStrByDir(puInParam, "BUSI_MODEL", "OPTR_MODE"), "1") == 0) 
		return p2105AddCfm(puInParam, ptCtrlInfo);
	else if(strcmp(utGetStrByDir(puInParam, "BUSI_MODEL", "OPTR_MODE"), "2") == 0) 
		return p2105DelCfm(puInParam, ptCtrlInfo);
	else
	{
		throw(appException(402012731, "�����������")); 
		return NULL;  
	}             
}
