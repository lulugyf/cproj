#ifndef __CLDomain_h__
#define __CLDomain_h__

/**
 BOSS �����
 */

class CLDomain
{
public:
	static const ub4 DMI_LOGIN_NO					= 10087;	//dLoginMsg.login_no
	static const ub4 DMI_LOGIN_PASSWORD				= 10092;	//dLoginMsg.password
	static const ub4 DMI_FUNCTION_CODE				= 10114;	//sFuncCode.function_code
	static const ub4 DMI_CLASS_NO					= 10127;	//sClassStruct.class_no
	static const ub4 DMI_CLASS_CODE					= 10128;	//sClassStruct.class_code

	static const ub4 DMI_REGION_CODE				= 10055;	//sRegionCode.region_code
	static const ub4 DMI_DISTRICT_CODE				= 10056;	//sDisCode.district_code
	static const ub4 DMI_TOWN_CODE					= 10057;	//sTownCode.town_code

	static const ub4 DMI_USER_ID					= 10136;	//�û�ID����
	static const ub4 DMI_CON_ID						= 10170;	//�˻�ID����
	static const ub4 DMI_PHONE_NO					= 10190;	//�ֻ�����
	static const ub4 DMI_CUST_ID					= 10054;	//�ͻ�ID����

	static const ub4 DMI_GRAPH_TYPE					= 10803;	//CHARTͼ����
	static const ub4 DMI_CHART_DEPTH				= 10804;	//ͼ����ȱ�ֵ
	static const ub4 DMI_GRAPH_DIM_CATEGORIES		= 10805;	//������̶ȱ�ǩ
	static const ub4 DMI_GRAPH_DIM_VALUE			= 10806;	//����ͼ���ֵ
	static const ub4 DMI_GRAPH_DIM_VALUE_DIRECTION	= 10807;	//��ͼ��ֵ��ȡֵ����
	static const ub4 DMI_GRAPH_TITLE_CAPTION		= 10808;	//ͼ��ı�����Ϣ
	static const ub4 DMI_GRAPH_DATA_BEGIN_POS		= 10811;	//ͼ���������ʼλ��
	static const ub4 DMI_GRAPH_DATA_END_POS			= 10812;	//ͼ������ݽ���λ��
	static const ub4 DMI_GRAPH_STYLE				= 10813;	//ͼ���ͼ����ʽ��
};
#endif //__CLError_h__
