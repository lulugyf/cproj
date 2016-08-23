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

//数据库接标志
#define TUX_DEAL_FLAG_CONNECT	0x00000001

//权限验证标志
#define TUX_DEAL_FLAG_RIGHT		0x00000002

//通用函数接口
typedef struct tagBusiFuncParam
{
	CLTuxInParams *tuxInParams;
	CLTuxOutParams *tuxOutParams;

	//错误代码，错误信息
	char	retCode[20+1];
	char	retMsg[255+1];

	//信息代码，信息内容
	char	infoCode[20+1];
	char	infoMsg[256];

	//通用信息，从XML中取得
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
	const char* serviceName;	//TUXEDO服务名称
	const char* serverName;		//TUXEDO SERVER名称，即TUXEDO服务所在的文件名。
	TPSVCINFO *transb;			//TUXEDO服务的如口参数。
	const char* dbLabel;		//链接数据库的标签。
	TBusiFunc BusiFunc;			//回调的函数名，此函数处理具体的业务。

	bool  bIsDispatch;			//是否做路由分发操作

	//默认连接
	CLConnection *ptDefaultConn;
	ub4 iConnDbType;//连接的数据库类型

	//是否是默认连接
	bool bIsDefaultConn;

	//连接名。
	char sConnName[255+1];

	//控制定义
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
	//分配TUXEDO内存
	FBFR32 *TuxMemAlloc(FBFR32 **transOUT, ub4 memSize);

	//TUXEDO入口函数。
	void TuxedoDeal(TTuxedoDeal *tuxedoDeal) throw();
	
	//得到工号信息
	ETYPE GetLoginMsg(const char* psLoginNo, char* psOrgCode, char* psPowerCode) throw();

	//得到操作的名称
	ETYPE GetFuncName(const char*opCode, char* funcName) throw();
	ETYPE sChkDBLogin();
private:
};

#include "general32.flds.h"

#endif//__CLTux_h__

