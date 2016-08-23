#pragma once
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include "utype.h"
/**
 * < summary>
 *     LOG_FUNC：为宏定义的名称，完成函数的统一日志打印。此宏定义内部会读取__FILE__、__FUNCTION__和__LINE__三个宏定义，
 * 得到函数的位置信息。此宏定义的使用方法举例如下：
 *        utype* ExampleFunc(const utype *puInParam, TCtrlInfo * pErrorInfo)
 *        {
 *                LOG_FUNC(puInParams, pErrorInfo, NULL);	//增加打函数信息。
 *                …… //函数体信息。
 *        }
 *</summary>
 *<param name=” psKeyWord” type=”const char*”>函数关键字，可以是"BP"、"BC"等。</param >
 *<param name=” puInParams” type=”utype*”>业务的输入参数，作为扩展参数使用</param >
 *<param name=” pErrorInfo” type=”TCtrlInfo*”>
 *    错误控制信息，作为以后的扩展参数使用。
 *</param >
 *<param name=” pLogFileHandle” type=”FILE*”>打印的函数句柄，默认填NULL。</param >
 */
#ifndef LOG_FUNC
#define LOG_FUNC(psKeyWord,puInParams, pErrorInfo, pLogFileHandle) \
	LogFunc __logFunc(psKeyWord, puInParams, pErrorInfo, pLogFileHandle, __FILE__, __FUNCTION__, __LINE__)
#define LOG_FUNC_BP() LOG_FUNC("BP", NULL, NULL, NULL)
#define LOG_FUNC_BC() LOG_FUNC("BC", NULL, NULL, NULL)
#endif

class LogFunc
{
public:
	/**
	 *<summary>日志构造函数</summary>
	 */
	LogFunc(const char *psKeyWord, const void *pInParam, const void * pErrorInfo, FILE *pLogFileHandle,
		const char *psFile, const char *psFunc, unsigned int iLine);

	/**
	 *<summary>日志析构函数</summary>
	 */
	~LogFunc();
public:
	const char *m_psKeyWord;//来自构造函数
	const void *m_pInParam;	//来自构造函数
	const void *m_pErrorInfo;	//来自构造函数
	FILE *m_pLogFileHandle;		//打印到的文件句柄,NULL到标准输出。
	const char *m_psFile;	//来自构造函数
	const char *m_psFunc;	//来自构造函数
	unsigned int m_iLine;	//来自构造函数

	unsigned int m_iCurrentDeep;	//当前深度。

	//扩展信息，可以在LogFunc中扩展使用此信息，以保证修改动态链接库，而不用修改此头文件。
	void* m_pvExternInfo;
private:
	/**
	 *<summary>阻止使用默认构造函数</summary>
	 */
	LogFunc()
	{
	}
};

typedef struct tagOprInfo
{
	char sServiceNo[100+1];	//服务号码
	char sLoginNo[20+1];	//工号
	char sOpCode[8+1];	//操作代码
	char sContactId[127+1];	//客户接触ID
	char sLoginAccept[127+1];	//交易流水
}TOprInfo;

/**
 *    初始化操作信息
 */
void GlobalInitOprInfo(TOprInfo &tOprInfo);

int NMLogCallBack(
	const char *psServiceName,		//服务名称
	TCtrlInfo *ptCtrlInfo,			//自有营业厅获取
	const char *psDbLabel,			//数据库标签名称
	const char *psUtypeFunc,		//服务调用BP名称
	const utype *pu_in,				//输入参数Utype
	struct timeval *tp_begin,		//服务调用开始时间
	const int retCode,              //服务返回代码
	const char *retMsg              //服务返回信息
	);
	
	
void GlobalBusiInit(const char *psServiceName,		//服务名称
	const char *psDbLabel,							//数据库标签名称
	const char *psUtypeFunc,						//服务调用BP名称
	const utype *pu_in								//输入参数Utype
	);
