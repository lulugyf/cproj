#ifndef __PUB_H__
#define __PUB_H__
#define CENTER_GROUP_ID "10017"
#define SEQ_UR_UNI_VPMNNO 63


#include "framework.h"
#define LONG_CONN_TYPE 1
#define SHORT_CONN_TYPE 0
#define SEQ_UNI_KAUTNO       61      /*宽带帐号序列*/
#define SEQ_UNI_AUTNO       62      /*vpmn集团帐号序列*/
#define CUST_QRY_MAXCNT 50 /* 根据证件查询客户最大限制数量 */


/*序列号类型定义*/
#define SEQ_CART_ID			1
#define SEQ_ORDER_ID		2
#define SEQ_ORDER_LINE_ID	3
#define SEQ_ORDER_CHG		4
#define SEQ_ORDER_LINE_CHG	5
#define SEQ_LOGIN_ACCEPT	6
#define SEQ_CUST_ID			7
#define SEQ_USER_ID			8
#define SEQ_CONTRACT_NO		9
#define SEQ_ORDER_LINE_SLA	10
#define SEQ_ORDER_LINE_BOOK	11
#define SEQ_ORDER_LINE_EXCP	12
#define SEQ_ORDER_LINE_EXEC	17
#define SEQ_UR_BILLMODE		28       /*13 付费模式序列*/
#define SEQ_UR_USERSTATE	29       /*14 用户状态序列*/
#define SEQ_CT_CONTACTID	6       /*15 客户联系信息*/
#define SEQ_UR_ADDNBRID		27       /*16 接入号标识  */
#define SEQ_IA_CONTACTID	20		/*20 统一接触序列类型 */
#define SEQ_CT_UNITID		1       /*18 集团编码  */
#define SEQ_CT_GRPDEPTID	6       /*19 集团部门标识  */
#define SEQ_CT_ADDRESSNO	6       /*20 集团通信录编码  */
#define SEQ_AC_ACCTID		30       /*21 账务标识序列*/
#define SEQ_CT_CUSTRELID	6       /*22 客户关系标识  */
#define SEQ_CT_CONTACTID	6       /*23 联系标识  */
#define SEQ_CT_SPCDAYNO	    6       /*24 关键日期标识  */
#define SEQ_CT_BLACKCUST   60       /*欠费销户  黑名单序列*/

#define SEQ_PD_PRODPRCINSID	13	/*产品资费实例序列*/
#define SEQ_PD_SVCINSID		18	/*服务实例序列*/
#define SEQ_UR_TEAMID  		14	/*组实例序列*/
#define SEQ_UR_GROUPID	 	15 	/*群实例序列*/
#define SEQ_UR_MEMBERID	 	16	/*成员实例序列*/
#define SEQ_UT_CUSTREL	 	6	/*客户关系序列*/
#define SEQ_UR_AGREEMENT	6	/*合同编码*/
#define SEQ_OR_PREORDER	  	6	  /*预订单流水-yangsong*/
#define SEQ_EVERY_PAGE	  	10	  /*每页显示的记录数*/
#define SEQ_UR_IMPI	  		31	  /*每页显示的记录数*/

#define SEQ_UR_TIETONGNO    65    /*铁通ADSL/LAN接入号自动生成序列*/
#define SEQ_UR_IAGW1065702601	  		66	  /*ADC手机邮箱接入号序列值*/
#define SEQ_UR_IDCGRPOUTNO	  		67	  /*通用的集团接入号序列值*/
#define SEQ_UR_GRPSX	  		68	  /*视讯通接入号序列值*/
#define SEQ_UR_GRPPRVVP	  		69	  /*vpmn接入号序列值*/
#define SEQ_UR_GRPVP	  		70	  /*省级vpmn接入号序列值*/
#define SEQ_UR_BBOSSACCEPT	  		71	  /*省级BBOSS一卡通接入号序列值*/

#define BS_CHN_CODE "11"  		/* 接触域渠道代码：营业前台 参考ia_chncode_dict 0开头是安徽老数据不便修改，建议不以0开头*/
#define INTERNET_CHN_CODE "02"  /* 接触域渠道代码：网上营业厅*/
#define WAP_CHN_CODE "03"  		/* 接触域渠道代码：掌上营业厅*/
#define SMS_CHN_CODE "04"  		/* 接触域渠道代码：短信营业厅*/
#define MACHINE_CHN_CODE "05"  	/* 接触域渠道代码：自助终端*/
#define IVR_CHN_CODE "06"  		/* 接触域渠道代码：IVR*/
#define CALLER_CHN_CODE "17"  	/* 接触域渠道代码：10086客服*/
#define BBOSS_CHN_CODE "18"		/* 接触域渠道代码：bboss */
#define RADIUS_CHN_CODE "07" 	/* 接触域渠道代码：省内RADIUS平台 */

#define PD_MASTER_QUN "1007"  		/* 群业务MASTER_SERV_ID*/
#define PD_MASTER_BRAND "1002"  	/* 宽带MASTER_SERV_ID*/

#define FINISH_FLAG         "N"        	/*生效状态*/
#define EXP_DATE            "20991231" 	/*失效时间*/
#define MAX_BILL_ORDER      99999999	/*默认账户销账优先级*/
#define FILE_PATH      "/run/file/ExtTxt/"	/*文件的存放路径*/
//A.B类集团必填字段
#define GRP_A_B "|.集团客户名称.CUST_NAME|.集团客户地址.CUST_ADDRESS|.行业类型.TRADE_CODE_NAME|.上年度通信费支出.COMMUNICATION_COSTS|.中层干部成员数.MID_LEADER_NUM|.领导班子成员数.LEADER_NUM|.企业员工数.WORKER_AMOUNT|.移动3G手机部数.MOBILE_NUM|.移动GSM手机部数.MOBILE_GSM_NUM|.报销话费人数.WRITE_OFF_NUM|.主要领导人姓名.LEAD_NAME|.主要领导人电话.LEAD_PHONE|.主要联系人姓名.CONTACT_NAME|.主要联系人电话.CONTACT_PHONE|.小灵通用户数.SPIRIT_NUM|.电信C网用户数.TEL_NETC_NUM|.电信3G用户数.TEL_3G_NUM|.联通G网用户数.UNION_NETG_NUM|.联通3G用户数.UNION_3G_NUM|.与电信合作内容.TEL_CONTENT|.与联通合作内容.UNION_CONTENT|.客户对信息化的需求程度.INFO_DEGREED|.客户选择该运营商的主要因素.CHOOSE_REASON|.是否签约电信.SIGN_TELECOM_FLAG|.是否签约联通.SIGN_UNICOM_FLAG|.已签约电信年限.SIGN_TELECOM_YEAR|.已签约联通年限.SIGN_UNICOM_YEAR|.客户经理姓名.MANAGER_NAME|.客户经理电话.MANAGER_PHONE"
//C.D类集团必填字段
#define GRP_C_D "|.集团客户名称.CUST_NAME|.集团客户地址.CUST_ADDRESS|.行业类型.TRADE_CODE_NAME|.企业员工数.WORKER_AMOUNT|.移动3G手机部数.MOBILE_NUM|.移动GSM手机部数.MOBILE_GSM_NUM|.主要领导人姓名.LEAD_NAME|.主要领导人电话.LEAD_PHONE|.主要联系人姓名.CONTACT_NAME|.主要联系人电话.CONTACT_PHONE|.小灵通用户数.SPIRIT_NUM|.电信C网用户数.TEL_NETC_NUM|.电信3G用户数.TEL_3G_NUM|.联通G网用户数.UNION_NETG_NUM|.联通3G用户数.UNION_3G_NUM|.固定电话（含网通）数.TELCOM_NUM"
#define BEGIN_CNTT_STATUS "N"     /* 接触开始状态*/
#define FINISH_CNTT_STATUS "E"  /* 接触完成状态*/
#endif

