#include "llayerStruct.h"

ETYPE CLError::m_errorNo=0;
#ifndef WIN32
//����������
const ETYPE CLError::MAX_ERROR_NUM;

const ETYPE CLError::E_SUCCESS;
const ETYPE CLError::E_MAX_ERROR_NO;

//���ݿ������
const ETYPE CLError::E_DATABASE;
const ETYPE CLError::E_DB_SQL_NOCONNECT;
const ETYPE CLError::E_DB_SQL_PREPARE;
const ETYPE CLError::E_DB_SQL_DATA_TYPE;
const ETYPE CLError::E_DB_DISCONNFLAG;
const ETYPE CLError::E_DB_SQLALD_BIND;
const ETYPE CLError::E_DB_SQL_EXECUTE_ITERS;
const ETYPE CLError::E_DB_BIND_MAXIMUM;
const ETYPE CLError::E_DB_SELECT_MAXIMUM;
const ETYPE CLError::E_DB_SQL_EXECUTE;
const ETYPE CLError::E_DB_SQL_UNKNOWN;
const ETYPE CLError::E_DB_OCI_INIT_ERROR;
const ETYPE CLError::E_DB_OCI_INIT_ENV;
const ETYPE CLError::E_DB_OCI_HDL_ALLOC_SVC;
const ETYPE CLError::E_DB_OCI_HDL_ALLOC_ERR;
const ETYPE CLError::E_DB_OCI_HDL_ALLOC_SRV;
const ETYPE CLError::E_DB_OCI_HDL_ALLOC_AUTH;
const ETYPE CLError::E_DB_OCI_HDL_ALLOC_STMT;
const ETYPE CLError::E_DB_OCI_SRV_ATTACH;
const ETYPE CLError::E_DB_OCI_ATTR_GET;
const ETYPE CLError::E_DB_OCI_ATTR_SET;
const ETYPE CLError::E_DB_OCI_LOG_ON;
const ETYPE CLError::E_DB_COMMIT;
const ETYPE CLError::E_DB_ROLLBACK;
const ETYPE CLError::E_DB_SQL_FETCH;
const ETYPE CLError::E_DB_SQL_FETCH_NODATA;
const ETYPE CLError::E_DB_GET_ROW_COUNT;
const ETYPE CLError::E_DB_GET_FETCHED_COUNT;
const ETYPE CLError::E_DB_SQL_DEFINE;
const ETYPE CLError::E_DB_GET_COL_ATTR;
const ETYPE CLError::E_DB_GET_LABEL;
const ETYPE CLError::E_DB_GET_BIND;

//�����ڴ������
const ETYPE CLError::E_SHM;
const ETYPE CLError::E_SHM_GETKEY;
const ETYPE CLError::E_SHM_GET_ID;
const ETYPE CLError::E_SHM_ASSOCIATED;
const ETYPE CLError::E_SHM_DETACH;

//�����ڴ������
const ETYPE CLError::E_FILE;
const ETYPE CLError::E_FILE_ENV;

//�ڴ���������
const ETYPE CLError::E_MEMORY;
const ETYPE CLError::E_MEMORY_LACK;

//TUXEDO���������
const ETYPE CLError::E_TUX;
const ETYPE CLError::E_TUX_FGET;
const ETYPE CLError::E_TUX_FADD;

//XML���������
const ETYPE CLError::E_XML;
const ETYPE CLError::E_XML_INIT;
const ETYPE CLError::E_XML_PARSE;
const ETYPE CLError::E_XML_TAG_ROOT;
const ETYPE CLError::E_XML_ELTAG_INPARAMS;
const ETYPE CLError::E_XML_ELTAG_PUBPARAMS;

//���������
const ETYPE CLError::E_PARAM;
const ETYPE CLError::E_PARAM_GET;

////////////////////////////////////////////////////////////
//    ����Ϊҵ�񼶱�Ĵ���
///////////////////////////////////////////////////////////

//ҵ��Ȩ�������
const ETYPE CLError::EB_RIGHT;
const ETYPE CLError::EB_RIGHT_LOGIN;
const ETYPE CLError::EB_RIGHT_FUNC;
const ETYPE CLError::EB_RIGHT_FUNCNAME;

//ͳһ��ͼ�����
const ETYPE CLError::EB_UNIFY;
const ETYPE CLError::EB_UNIFY_RULE_TYPE;
const ETYPE CLError::EB_UNIFY_GET_FUNC_ADDR;
const ETYPE CLError::EB_UNIFY_UNSET_PARAM;
const ETYPE CLError::EB_UNIFY_NO_IN_PARAM;
const ETYPE CLError::EB_UNIFY_NOSUPPORT_INDATATYPE;
const ETYPE CLError::EB_UNIFY_NOSUPPORT_OUTDATATYPE;
const ETYPE CLError::EB_UNIFY_NOSUPPORT_OUTDATATYPE2;
const ETYPE CLError::EB_UNIFY_NO_FUNC_RULE;
const ETYPE CLError::EB_UNIFY_NO_RULE_INFO;
const ETYPE CLError::EB_UNIFY_NO_RULE_IN;
const ETYPE CLError::EB_UNIFY_NO_RULE_OUT;
const ETYPE CLError::EB_UNIFY_NO_MAIN_CONDITION;
const ETYPE CLError::EB_UNIFY_NOSUPPORT_DISPDATATYPE;
const ETYPE CLError::EB_UNIFY_NOSUPPORT_DISPLAYTYPE;
const ETYPE CLError::EB_UNIFY_ARRAY_STRUCT;
const ETYPE CLError::EB_UNIFY_SELECT_VALUE;
const ETYPE CLError::EB_UNIFY_SELECT_SQL;
const ETYPE CLError::EB_UNIFY_RULE_NO_DATA;
const ETYPE CLError::EB_UNIFY_RULE_MAX_DATA;
const ETYPE CLError::EB_UNIFY_DISCORDANT_ROWCOUNT;

#endif

const TErrorNoMsg CLError::errorNoMsg[MAX_ERROR_NUM]=
{
	{E_SUCCESS,					"��ȷ"},
	{E_MAX_ERROR_NO,			"�������"},

	{E_DATABASE,				"���ݿ������"},
	{E_DB_SQL_NOCONNECT,		"���ݿ�û������"},
	{E_DB_SQL_PREPARE,			"Ԥ����SQL������"},
	{E_DB_SQL_DATA_TYPE,		"����󶨵���������, �ο�EDbDataType"},
	{E_DB_DISCONNFLAG,			"���ݿ�Ͽ����ݿ����Ӳ�������"},
	{E_DB_SQLALD_BIND,			"����󶨱����ڴ�ʧ��"},
	{E_DB_SQL_EXECUTE_ITERS,	"ִ�еĵ�����������"},
	{E_DB_BIND_MAXIMUM,			"�󶨱���̫�࣬��������"},
	{E_DB_SELECT_MAXIMUM,		"ѡ�������̫�࣬��������"},
	{E_DB_SQL_EXECUTE,			"ִ��SQL������"},
	{E_DB_SQL_UNKNOWN,			"��֧�ֵ�SQL���"},
	{E_DB_OCI_INIT_ERROR,		"ORACLE ��ʼ��ʧ��"},
	{E_DB_OCI_INIT_ENV,			"ORACLE ������ʼ��ʧ��"},
	{E_DB_OCI_HDL_ALLOC_SVC,	"ORACLE ��ʼ��������ʧ��"},
	{E_DB_OCI_HDL_ALLOC_ERR,	"ORACLE ��ʼ��������ʧ��"},
	{E_DB_OCI_HDL_ALLOC_SRV,	"ORACLE ��ʼ�����������ʧ��"},
	{E_DB_OCI_HDL_ALLOC_AUTH,	"ORACLE ��ʼ����֤���ʧ��"},
	{E_DB_OCI_HDL_ALLOC_STMT,	"ORACLE ��ʼ�������ʧ��"},
	{E_DB_OCI_SRV_ATTACH,		"FAILED: OCIServerAttach()"},
	{E_DB_OCI_ATTR_GET,			"FAILED: OCIAttrGet() server attribute"},
	{E_DB_OCI_ATTR_SET,			"FAILED: OCIAttrSet() server attribute"},
	{E_DB_OCI_LOG_ON,			"��½ʧ��"},
	{E_DB_COMMIT,				"�����ύʧ��"},
	{E_DB_ROLLBACK,				"����ع�ʧ��"},
	{E_DB_SQL_FETCH,			"ȡ���α�����ݳ���"},
	{E_DB_SQL_FETCH_NODATA,		"�α���������"},
	{E_DB_GET_ROW_COUNT,		"�õ��α��еļ�¼������"},
	{E_DB_GET_FETCHED_COUNT,	"�õ����η��صļ�¼������"},
	{E_DB_SQL_DEFINE,			"��������󶨱�������"},
	{E_DB_GET_COL_ATTR,			"�õ�SELECT�������Գ���"},
	{E_DB_GET_LABEL,			"�õ����ݿ��ǩ����"},
	{E_DB_GET_BIND,				"�õ��󶨱�����Ϣ����"},

	{E_SHM,						"�����ڴ������"},
	{E_SHM_GETKEY,				"�õ������ڴ��ֵ����"},
	{E_SHM_GET_ID,				"�õ������ڴ��ʶ����"},
	{E_SHM_DETACH,				"�Ͽ������ڴ����"},

	{E_FILE,					"�ļ������"},
	{E_FILE_ENV,				"ȡ������������"},

	{E_MEMORY,					"�ڴ����"},
	{E_MEMORY_LACK,				"�ڴ治��"},

	{E_TUX,						"TUXEDO����"},
	{E_TUX_FGET,				"Fget��ȡ����ʧ��"},
	{E_TUX_FADD,				"Fadd��������ʧ��"},

	{E_XML,						"XML��������"},
	{E_XML_INIT,				"��ʼ��XML����ʧ��"},
	{E_XML_PARSE,				"����XML�ļ�����"},
	{E_XML_TAG_ROOT,			"�õ�XML����ǩ����"},
	{E_XML_ELTAG_INPARAMS,		"�õ�XML XML_ELTAG_INPARAMS��ǩ����"},
	{E_XML_ELTAG_PUBPARAMS,		"�õ�XML XML_ELTAG_PUBPARAMS��ǩ����"},

	{E_PARAM,					"�������������"},
	{E_PARAM_GET,				"��ȡ��������"},

	////////////////////////////////////////////////////////////
	//    ����Ϊҵ�񼶱�Ĵ���
	///////////////////////////////////////////////////////////

	//ҵ��Ȩ�������
	{EB_RIGHT,					"ҵ��Ȩ�������"},
	{EB_RIGHT_LOGIN,			"���빤�Ż��������"},
	{EB_RIGHT_FUNC,				"�޴˹���Ȩ��"},
	{EB_RIGHT_FUNCNAME,			"�޴˹��ܴ���"},

	//ͳһ��ͼ�����
	{EB_UNIFY,						"ͳһ��ͼ�����"},
	{EB_UNIFY_RULE_TYPE,			"��֧�ֵĹ�������[%d]��"},
	{EB_UNIFY_GET_FUNC_ADDR,		"�Ӷ�̬���ӿ��ж�ȡ����[%s]��ַ����"},
	{EB_UNIFY_UNSET_PARAM,			"����[%s]���صĲ���λ��[%d]���ڴ����û�����ã�"},
	{EB_UNIFY_NO_IN_PARAM,			"����[%s]�����������Ҳû��Ĭ��ֵ������λ��[%d]��"},
	{EB_UNIFY_NOSUPPORT_INDATATYPE,	"��֧�ֵ����뺯��[%s]�������ͣ�����λ��[%d]��"},
	{EB_UNIFY_NOSUPPORT_OUTDATATYPE,"��֧�ֵ��������[%s]�������ͣ�����λ��[%d]��"},
	{EB_UNIFY_NOSUPPORT_OUTDATATYPE2,"����[%s]Ƕ�׳���[%d]����"},
	{EB_UNIFY_NO_FUNC_RULE,			"���ܴ���[%s]û���κι������ã�"},
	{EB_UNIFY_NO_RULE_INFO,			"����[%d]�ڹ�����Ϣ����û��������Ϣ��"},
	{EB_UNIFY_NO_RULE_IN,			"���ܴ���[%s]�ڹ����������û�����ù���[%d]��"},
	{EB_UNIFY_NO_RULE_OUT,			"���ܴ���[%s]�ڹ����������û�����ù���[%d]��"},
	{EB_UNIFY_NO_MAIN_CONDITION,	"û����������ѯ���������ܴ���[%s], �������[%d]��"},
	{EB_UNIFY_NOSUPPORT_DISPDATATYPE,"��֧�ֵ���ʾ��������"},
	{EB_UNIFY_NOSUPPORT_DISPLAYTYPE,"��֧�ֵ���ʾ�ؼ�����"},
	{EB_UNIFY_ARRAY_STRUCT,			"�����Ԫ��ֻ���ǵ�ֵ�͵ģ�����[%s]����λ��[%d]��"},
	{EB_UNIFY_SELECT_VALUE,			"���ܴ���[%s], �������[%d], ��ѡֵ����������ô��󣬸�ʽ����¼֮���á�,���ŷֿ�����¼���á�~���ֿ���"},
	{EB_UNIFY_SELECT_SQL,			"��ȡ�������[%d]��SQL������"},
	{EB_UNIFY_RULE_NO_DATA,		"��ѯ�޷������������ݣ�����[%s]��"},
	{EB_UNIFY_RULE_MAX_DATA,		"����[%s]���ص������������������[%d]��ֻ��ʾ������Ƶ�������"},
	{EB_UNIFY_DISCORDANT_ROWCOUNT,	"ͬһ��table�У��ֶη��ز�һ�µļ�¼����������λ��[%d]��"}
};

ETYPE CLError::GetLastError() 
{
	return m_errorNo;
}

const char*  CLError::GetErrorMsg(ETYPE errNo) 
{
	register int i;
	for (i = 0; i < MAX_ERROR_NUM; i ++)
	{
		if (errorNoMsg[i].errorNo == errNo)
		{
			return errorNoMsg[i].errorMsg;
		}
	}
	return NULL;
}
