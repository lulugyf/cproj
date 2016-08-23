#include <framework.h>

/*
 * 安徽错误码管理平台接口处理
 * 包括两种处理方案， 通过开关切换（暂定[ERRMANAGE]Interface=ws|db：
 * ws: 调用管理平台的webservice接口
 *   接口代码由liupengc完成
 * db: 查询本地库， 表结构如下
create table PI_DETAILMSG_DICT
(
  error_code VARCHAR2(20) not null,  --错误码
  channel    VARCHAR2(20) not null,  --渠道
  prompt_msg VARCHAR2(255) not null, --提示信息
  bak        VARCHAR2(255),          --备注
  usr_msg    VARCHAR2(255),          --用户信息（如果CRM仍采用原来的取值方法，此字段作废）
  detail_msg VARCHAR2(255),       --详细信息（如果CRM仍采用原来的取值方法，此字段作废）
  valid_date DATE,			--生效时间
  exp_date   DATE,			--失效时间
  msg_id     NUMBER(14) primary key     --提示信息ID（主键）
);
SELECT PROMPT_MSG FROM PI_DETAILMSG_DICT
WHERE ERROR_CODE = :ERROR_CODE
AND CHANNEL=:CHANNEL
AND SYSDATE >= VALID_DATE AND SYSDATE<=EXP_DATE;

 变量替换规则：
 假定行业部抛出异常
throw(123456789, "业务办理异常~15812345678|58.50|58.50")
查到的信息为 "您好,您的号码%v欠费%v元,请至少缴费%v元,再进行办理."
框架根据~后面的值,依次将
"您好,您的号码%v欠费%v元,请至少缴费%v元,再进行办理."
替换为: "您好,您的号码15812345678欠费58.50元,请至少缴费58.50元,再进行办理."
 */

static int strReplace(string *myret, char *msg, char *vars)
{
	char *p1, *p2, *p3, *p4;
	p1 = strchr(vars, '~');
	if(p1 == NULL){
		*myret = msg;
		return 1;
	}
	*p1 = 0;
	p1 ++;
	p3 = msg;
	while( (p4 = strstr(p3, "%v")) != NULL){
		p2 = strchr(p1, '`');
		if(p2 != NULL)
			*p2 = 0;
		*p4 = 0;
		myret->append(p3).append(p1);

		p3 = p4 + 2;
		if(p2 == NULL)
			break;
		p1 = p2 + 1;
	}
	if(p3 != NULL)
		myret->append(p3);
	return 1;
}

extern "C" int call_errno_ws(char *url, int conn_timeout, int recv_timeout,
                char *inmsg, int need2utf, char **outmsg, int need2gbk);

static int getXmlText(const char *xml, const char *tag, char *ret)
{
	char stag[64], etag[64], *ps, *pe;
	sprintf(stag, "<%s>", tag);
	sprintf(etag, "</%s>", tag);
	ps = strstr((char *)xml, stag);
	if(ps == NULL)
		return -1;
	ps += strlen(stag);
	pe = strstr(ps, etag);
	if(pe == NULL)
		return -2;
	int n = pe - ps;
	strncpy(ret, ps, n);
	ret[n] = 0;
	return 0;
}

/*
 * @desc  从错误码管理平台获取信息
 * @param uin服务入参
 * @param 业务代码抛出的异常
 * @retmsg 用于接收返回的字符串
 *
 * @return 0-未处理  1-处理成功 -1-处理失败
 */
int errMng(const utype *uin, const long retCode, char *retMsg,
		TCtrlInfo* errinfo, string *myret)
{
	const char *channel = NULL;
	char prompt[256];
	char errcode[32];

	try{
		channel = utGetStr(uin, "CHANNEL");
	}catch(...){
		L4C_DEBUG("错误码管理：入参中没有CHANNEL，不处理");
		return 0; //没有CHANNEL则无需处理， 直接返回0
	}
	sprintf(errcode, "%ld", retCode);

	const char *cmod = cfgGetStr("ERRMANAGE", "Interface");
	if(cmod[0] == 0){
		L4C_DEBUG("错误码管理：无配置，不处理");
		return 0; //未配置， 则不处理
	}

	if(strcmp(cmod, "db") == 0){
		otl_nocommit_stream o;
		const char *sqlbuf = "SELECT PROMPT_MSG FROM PI_DETAILMSG_DICT WHERE ERROR_CODE = to_char(:ERROR_CODE<long>) AND CHANNEL=:CHANNEL<char[21]> AND SYSDATE between VALID_DATE AND EXP_DATE";
		try{
			o.open(1, sqlbuf, GETDB(errinfo));
			o << retCode << channel;
			if(o.eof()){
				L4C_ERROR("错误码管理：错误信息表无记录 %ld", retCode);
				return -1;
			}
			memset(prompt, 0, sizeof(prompt));
			o >> prompt;
			o.close();
		}catch(otl_exception &ex){
			printf("select failed :%d  errmsg: %s\n %s %s\n\n",
					ex.code, ex.msg, ex.stm_text, ex.var_info);
			return -1;
		}
		//开始变量替换
		strReplace(myret, prompt, retMsg);
		return 1;
	}else if(strcmp(cmod, "ws") == 0){
		const char *url = cfgGetStr("ERRMANAGE", "ws.URL");
		char *p;
		string data;
		char rcode[10];
		char *outmsg = NULL;
		data.append("<ContractRoot><TcpCont><TransactionID/><ActionCode/><BusCode/><ServiceCode/><ServiceContractVer/><ServiceLevel/><SrcOrgID/><SrcSysID/><SrcSysSign/><DstOrgID/><DstSysID/><ReqTime/><Remarks/></TcpCont><SvcCont><ErrorDetail><OwnSystem/><OwnField/><FunctionCode/><ErrorCode>");
		data.append(errcode);
		data.append("</ErrorCode><Channel>");
		data.append(channel).append("</Channel><CallTime/><VARIABLES>");
		if((p = strchr(retMsg, '~')) != NULL){
			*p = 0;
			data.append(p+1);
		}
		data.append("</VARIABLES></ErrorDetail></SvcCont></ContractRoot>");
		L4C_INFO("call errno ws api:[%s]", url);
		//int ret = call_errno_ws((char *)url, 2, 3,  (char *)data.c_str(), 1, &outmsg, 1);
		int ret = -1; // call_errno_ws not implement yet.

		if(ret != 0){
			L4C_ERROR("错误码管理：调用错误码接口[%s] 失败 %d", url, ret);
			if(outmsg != NULL)free(outmsg);
			return -1;
		}
		if(getXmlText(outmsg, "RspCode", rcode) != 0){
			L4C_ERROR("错误码管理：错误码接口 返回数据中无应答码[%s]", url);
			free(outmsg);
			return -1;
		}
		if(strcmp(rcode, "0000") != 0){
			prompt[0] = 0;
			getXmlText(outmsg, "PromptMsg", prompt);
			L4C_ERROR("错误码管理：错误码接口 应答失败[%s]， 错误代码[%s][%s]", url, rcode, prompt);
			free(outmsg);
			return -1;
		}
		if(getXmlText(outmsg, "PromptMsg", prompt) != 0){
			free(outmsg);
			return -1;
		}
		myret->append(prompt);
		free(outmsg);
		return 1;
	}

	return 0;
}
