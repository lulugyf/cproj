#ifndef __CLTux_h__
#define __CLTux_h__

#include <atmi.h>
#include <fml32.h>
#include <fml.h>
#include "llayerStruct.h"
#include "utype.h"
#include "xml.h"
#include "CLTuxParam.h"
#include "CLBusiFuncMgr.h"

//���ݿ�ӱ�־
#define TUX_DEAL_FLAG_CONNECT	0x00000001

//Ȩ����֤��־
#define TUX_DEAL_FLAG_RIGHT		0x00000002

//ͨ�ú����ӿ�
typedef struct tagBusiFuncParam
{
	CLTuxInParams *tuxInParams;
	CLTuxOutParams *tuxOutParams;

	//������룬������Ϣ
	char	retCode[20+1];
	char	retMsg[255+1];

	//��Ϣ���룬��Ϣ����
	char	infoCode[20+1];
	char	infoMsg[256];

	//ͨ����Ϣ����XML��ȡ��
	char sLoginNo[20+1];
	char sOrgCode[10+1];
	char sPowerCode[30+1];
	char sOpCode[5+1];
	char sFuncName[30+1];
	char sLoginPasswd[32+1];
}TBusiFuncParam;

typedef ETYPE (*TBusiFunc)(TBusiFuncParam *busiFuncParam);

typedef struct tagTuxedoDeal
{
	const char* serviceName;	//TUXEDO��������
	const char* serverName;		//TUXEDO SERVER���ƣ���TUXEDO�������ڵ��ļ�����
	TPSVCINFO *transb;			//TUXEDO�������ڲ�����
	const char* dbLabel;		//�������ݿ�ı�ǩ��
	TBusiFunc BusiFunc;			//�ص��ĺ��������˺�����������ҵ��

	bool  bIsDispatch;			//�Ƿ���·�ɷַ�����

	//Ĭ������
	CLConnection *ptDefaultConn;
	ub4 iConnDbType;//���ӵ����ݿ�����

	//�Ƿ���Ĭ������
	bool bIsDefaultConn;

	//��������
	char sConnName[255+1];

	//���ƶ���
	//	TUX_DEAL_FLAG_CONNECT	0x00000001
	//	TUX_DEAL_FLAG_RIGHT		0x00000002
	int flags;
}TTuxedoDeal;

class CLTux
{
public:
	CLTux()
	{
	}
public:
	//����TUXEDO�ڴ�
	FBFR32 *TuxMemAlloc(FBFR32 **transOUT, ub4 memSize);

	//TUXEDO��ں�����
	void TuxedoDeal(TTuxedoDeal *tuxedoDeal) throw();
	
	//�õ�������Ϣ
	ETYPE GetLoginMsg(const char* psLoginNo, char* psOrgCode, char* psPowerCode) throw();

	//�õ�����������
	ETYPE GetFuncName(const char*opCode, char* funcName) throw();
	ETYPE sChkDBLogin();
private:
};

#include "general32.flds.h"

#endif//__CLTux_h__

