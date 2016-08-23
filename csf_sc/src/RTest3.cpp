#include "allBCP.h"

/*
 * test case 20131030001:
 * 错误码管理平台接口
 修改了tuxadp.cpp 中的 bindRetBuff 函数，并增加了参数（服务入参）
 新增代码文件 pub/tuxadp/errmng.cpp,
 */
static utype* pMytest1(const utype *inparam, TCtrlInfo *errInfo)
{
	strcpy(errInfo->infoMsg, "infoMsg.....");
	if(utFind(inparam, "throw") != UPOS_END){
		long rcode = 210000;
		const char *m = utGetStr(inparam, "throw");
		if(utFind(inparam, "rcode") != UPOS_END){
			rcode = utGetLong(inparam, "rcode");
		}
		L4C_DEBUG("throw %ld[%s]", rcode, m);
		throw appException(rcode, m);
	}
	L4C_DEBUG("no throw, I'm fine.");

	long id;
	char sf3[20];
	int f1 = 123;
	otl_stream qry(1,
						"select f3, to_char(f3) sf3 from mytab1 where f1=:f1<int>",
						GETDB(errInfo));
	qry << f1;
	if(!qry.eof()){
		qry >> id >> sf3;
	}else{
		id = -1L;
	}
	qry.close();
	utype *uout = uInit(1);
	utAddStr(uout, "OUT", "hello");
	utAddLong(uout, "F3", id);
	utAddStr(uout, "SF3", sf3);
	return uout;
}

extern "C" void stest211(TPSVCINFO *transb)
{                                                                                     
	tuxadp(transb->name, transb, LABELDBCHANGE, "pMytest1", pMytest1, 1);
}       

/*
数据：
insert into PI_DETAILMSG_DICT values('210000', '12', '您好,您的号码%v欠费%v元,请至少缴费%v元,再进行办理.', '', '', '', sysdate-1, sysdate+1000, 21000);
配置：
[ERRMANAGE]
Interface=db
1.
clxml stest211 '{"ROOT":{"CHANNEL":"12"}}'
2.
clxml stest211 '{"ROOT":{"CHANNEL":"106", "rcode":17363110001, "throw":"fail~15812345678|58.50|58.50"}}'
clxml stest211 '{"ROOT":{"CHANNEL":"106", "rcode":17363110001, "throw":"fail"}}'
3.
clxml stest211 '{"ROOT":{"CHANNEL":"12", "throw":"fail~15812345678|58.50"}}'
4.
clxml stest211 '{"ROOT":{"CHANNEL":"12", "throw":"fail~15812345678|58.50|10|20"}}'


output:
1.
{ "ROOT": { "RETURN_CODE": 0, "RETURN_MSG": "ok!", "USER_MSG": "ok!", "DETAIL_MSG": "OK!", "PROMPT_MSG": "", "OUT_DATA": { "OUT": "hello" } } }
2.
{ "ROOT": { "RETURN_CODE": 210000, "RETURN_MSG": "无法获取该错误代码的错误信息，请直接查看明细信息 ERRID:24892606", "USER_MSG": "无法获取该错误代码的错误信息，请直接查看明细信息", "DETAIL_MSG": "fail~15812345678|58.50|58.50", "PROMPT_MSG": "", "STANDARD_PROMPT_MSG": "您好,您的号码15812345678欠费58.50元,请至少缴费58.50元,再进行办理." } }
3.
{ "ROOT": { "RETURN_CODE": 210000, "RETURN_MSG": "无法获取该错误代码的错误信息，请直接查看明细信息 ERRID:24892819", "USER_MSG": "无法获取该错误代码的错误信息，请直接查看明细信息", "DETAIL_MSG": "fail~15812345678|58.50", "PROMPT_MSG": "", "STANDARD_PROMPT_MSG": "您好,您的号码15812345678欠费58.50元,请至少缴费%v元,再进行办理." } }
4.
{ "ROOT": { "RETURN_CODE": 210000, "RETURN_MSG": "无法获取该错误代码的错误信息，请直接查看明细信息 ERRID:24892834", "USER_MSG": "无法获取该错误代码的错误信息，请直接查看明细信息", "DETAIL_MSG": "fail~15812345678|58.50|10|20", "PROMPT_MSG": "", "STANDARD_PROMPT_MSG": "您好,您的号码15812345678欠费58.50元,请至少缴费10元,再进行办理." } }
 */
