
#include <iostream>
#include <string>
#include <map>

using namespace std;

#include <utype.h>

utype* doMerge(map<string, void*>* m, TCtrlInfo* errInfo);

typedef utype* (*TDoMerge)(map<string, void*>* m, TCtrlInfo* errInfo);


/**
 * 适配器入口函数
 * @inparam    obuf             输出内容指针
 * @inparam    obufLen          输出内容长度
 * @inparam    psServiceName	服务名称
 * @inparam    inputstr			入参串，xml 或 json
 * @inparam    clientaddr       新增的参数，客户端地址, 可以为 NULL
 * @inparam    psDbLabel		数据库连接标签
 * @inparam    psUtypeFunc		utype函数名称
 * @inparam    ptUtypeFuncPtr	utype函数地址
 * @inparam    ptDoMerge	         结果合并回调函数， 可以为NULL， 则使用默认的 doMerge
 * @inparam    iConnType		数据库连接方式,1长连接,0短连接
 */
void adpt_entry(char **obuf,        //出参, 需要外部释放其内存空间
		int* obufLen,              //出参长度
		const char *psServiceName, //服务名称
		char *inputstr,    //入参串，xml 或 json
		char *clientaddr,  //新增的参数，客户端地址, 可以为 NULL
		const char *psDbLabel,     //数据库连接标签
		const char *psUtypeFunc,   // BP/BC 的名称
		TUtypeFuncPtr ptUtypeFuncPtr, // BP/BC 的函数指针
		TDoMerge ptDoMerge,   //结果合并回调函数， 可以为NULL， 则使用默认的 doMerge
		int iConnType         //数据库连接类型，  1-长连接  0-短连接
		);


//简化版本的函数,  与 dotuxadp 的差异如下：
//1. 无自定义合并结果集函数（使用自带的），少一个入参；
//2. 不调用业务规则doRule；
//3. 不调用结果集过滤Powerfilter
//4. 完全不使用内存数据库
void adpt_entry1(
		char **obuf,
		int* obufLen,
		const char *psServiceName,
		char *inputstr,
		char *clientaddr,
		const char *psDbLabel,
		const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr,
		int iConnType
		);
