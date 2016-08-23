#include <framework.h>

/*
 * ���մ��������ƽ̨�ӿڴ���
 * �������ִ������� ͨ�������л����ݶ�[ERRMANAGE]Interface=ws|db��
 * ws: ���ù���ƽ̨��webservice�ӿ�
 *   �ӿڴ�����liupengc���
 * db: ��ѯ���ؿ⣬ ��ṹ����
create table PI_DETAILMSG_DICT
(
  error_code VARCHAR2(20) not null,  --������
  channel    VARCHAR2(20) not null,  --����
  prompt_msg VARCHAR2(255) not null, --��ʾ��Ϣ
  bak        VARCHAR2(255),          --��ע
  usr_msg    VARCHAR2(255),          --�û���Ϣ�����CRM�Բ���ԭ����ȡֵ���������ֶ����ϣ�
  detail_msg VARCHAR2(255),       --��ϸ��Ϣ�����CRM�Բ���ԭ����ȡֵ���������ֶ����ϣ�
  valid_date DATE,			--��Чʱ��
  exp_date   DATE,			--ʧЧʱ��
  msg_id     NUMBER(14) primary key     --��ʾ��ϢID��������
);
SELECT PROMPT_MSG FROM PI_DETAILMSG_DICT
WHERE ERROR_CODE = :ERROR_CODE
AND CHANNEL=:CHANNEL
AND SYSDATE >= VALID_DATE AND SYSDATE<=EXP_DATE;

 �����滻����
 �ٶ���ҵ���׳��쳣
throw(123456789, "ҵ������쳣~15812345678|58.50|58.50")
�鵽����ϢΪ "����,���ĺ���%vǷ��%vԪ,�����ٽɷ�%vԪ,�ٽ��а���."
��ܸ���~�����ֵ,���ν�
"����,���ĺ���%vǷ��%vԪ,�����ٽɷ�%vԪ,�ٽ��а���."
�滻Ϊ: "����,���ĺ���15812345678Ƿ��58.50Ԫ,�����ٽɷ�58.50Ԫ,�ٽ��а���."
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
 * @desc  �Ӵ��������ƽ̨��ȡ��Ϣ
 * @param uin�������
 * @param ҵ������׳����쳣
 * @retmsg ���ڽ��շ��ص��ַ���
 *
 * @return 0-δ����  1-����ɹ� -1-����ʧ��
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
		L4C_DEBUG("��������������û��CHANNEL��������");
		return 0; //û��CHANNEL�����账�� ֱ�ӷ���0
	}
	sprintf(errcode, "%ld", retCode);

	const char *cmod = cfgGetStr("ERRMANAGE", "Interface");
	if(cmod[0] == 0){
		L4C_DEBUG("��������������ã�������");
		return 0; //δ���ã� �򲻴���
	}

	if(strcmp(cmod, "db") == 0){
		otl_nocommit_stream o;
		const char *sqlbuf = "SELECT PROMPT_MSG FROM PI_DETAILMSG_DICT WHERE ERROR_CODE = to_char(:ERROR_CODE<long>) AND CHANNEL=:CHANNEL<char[21]> AND SYSDATE between VALID_DATE AND EXP_DATE";
		try{
			o.open(1, sqlbuf, GETDB(errinfo));
			o << retCode << channel;
			if(o.eof()){
				L4C_ERROR("���������������Ϣ���޼�¼ %ld", retCode);
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
		//��ʼ�����滻
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
			L4C_ERROR("������������ô�����ӿ�[%s] ʧ�� %d", url, ret);
			if(outmsg != NULL)free(outmsg);
			return -1;
		}
		if(getXmlText(outmsg, "RspCode", rcode) != 0){
			L4C_ERROR("���������������ӿ� ������������Ӧ����[%s]", url);
			free(outmsg);
			return -1;
		}
		if(strcmp(rcode, "0000") != 0){
			prompt[0] = 0;
			getXmlText(outmsg, "PromptMsg", prompt);
			L4C_ERROR("���������������ӿ� Ӧ��ʧ��[%s]�� �������[%s][%s]", url, rcode, prompt);
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
