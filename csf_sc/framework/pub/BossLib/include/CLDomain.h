#ifndef __CLDomain_h__
#define __CLDomain_h__

/**
 BOSS 域定义表
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

	static const ub4 DMI_USER_ID					= 10136;	//用户ID编码
	static const ub4 DMI_CON_ID						= 10170;	//账户ID编码
	static const ub4 DMI_PHONE_NO					= 10190;	//手机号码
	static const ub4 DMI_CUST_ID					= 10054;	//客户ID编码

	static const ub4 DMI_GRAPH_TYPE					= 10803;	//CHART图类型
	static const ub4 DMI_CHART_DEPTH				= 10804;	//图像深度比值
	static const ub4 DMI_GRAPH_DIM_CATEGORIES		= 10805;	//坐标轴刻度标签
	static const ub4 DMI_GRAPH_DIM_VALUE			= 10806;	//绘制图表的值
	static const ub4 DMI_GRAPH_DIM_VALUE_DIRECTION	= 10807;	//制图表值的取值方向
	static const ub4 DMI_GRAPH_TITLE_CAPTION		= 10808;	//图表的标题信息
	static const ub4 DMI_GRAPH_DATA_BEGIN_POS		= 10811;	//图表的数据起始位置
	static const ub4 DMI_GRAPH_DATA_END_POS			= 10812;	//图表的数据结束位置
	static const ub4 DMI_GRAPH_STYLE				= 10813;	//图表的图形样式单
};
#endif //__CLError_h__
