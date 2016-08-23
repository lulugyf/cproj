#define	REL_LIMIT_LOGIC	"1"
#define	REL_LIMIT_ABS	"2"
#define	REL_DEPEND_OR	"3"
#define	REL_DEPEND_AND	"4"
#define	REL_TRANS		"5"
#define	REL_OPT			"6"
#define	REL_BIND_ON		"7"
#define	REL_BIND_OFF	"8"
#define	REL_DERIV		"9"

#define GRPMBR_OBJTYPE_IDNO		"1"
#define GRPMBR_OBJTYPE_SVCNO	"2"
#define GRPMBR_OBJTYPE_GRP		"3"

/**--SP操作来源--**/
#define SP_OPSOURCE_WEB			"01"
#define SP_OPSOURCE_WT			"02"
#define SP_OPSOURCE_WAP			"03"
#define SP_OPSOURCE_SMS			"04"
#define SP_OPSOURCE_MMS			"05"
#define SP_OPSOURCE_KJAVA		"06"
#define SP_OPSOURCE_CRM			"07"
#define SP_OPSOURCE_BOSS		"08"
#define SP_OPSOURCE_SP			"09"

#define OUTTER_CHN_OPCODE 		"4000"

/**--主题服务类型--**/
#define MASTER_SERVID_01		"1001"		//G网
#define MASTER_SERVID_02		"1002"		//宽带
#define MASTER_SERVID_03		"1003"		//数据固定业务
#define MASTER_SERVID_04		"1004"		//固话
#define MASTER_SERVID_05		"1005"		//群业务
#define MASTER_SERVID_06		"1006"		//IMS业务

/**--群组类型--**/
#define GROUPTEAM_TYPE_11		"11"		//亲情号码组
#define GROUPTEAM_TYPE_B11              "B11"           //山西亲情号码组
#define GROUPTEAM_TYPE_B0		"B0"		//VPMN大集团群
#define GROUPTEAM_TYPE_C0		"C0"		//全球通家庭计划群
#define GROUPTEAM_TYPE_D1		"D1"		//家庭计划群
#define GROUPTEAM_TYPE_E0		"E0"		//INT_普通VPMN群
#define GROUPTEAM_TYPE_E1		"E1"		//INT_综合VPMN群
#define GROUPTEAM_TYPE_E2		"E2"		//INT_短号联合VPMN群
#define GROUPTEAM_TYPE_E3		"E3"
#define GROUPTEAM_TYPE_F0		"F0"
#define GROUPTEAM_TYPE_G1		"G1"
#define GROUPTEAM_TYPE_H0		"H0"
#define GROUPTEAM_TYPE_H1		"H1"
#define GROUPTEAM_TYPE_H2		"H2"
#define GROUPTEAM_TYPE_H3		"H3"
#define GROUPTEAM_TYPE_H4		"H4"
#define GROUPTEAM_TYPE_H5		"H5"
#define GROUPTEAM_TYPE_H6		"H6"
#define GROUPTEAM_TYPE_H7		"H7"
#define GROUPTEAM_TYPE_H8		"H8"
#define GROUPTEAM_TYPE_J0		"J0"
#define GROUPTEAM_TYPE_J1		"J1"
#define GROUPTEAM_TYPE_J2		"J2"
#define GROUPTEAM_TYPE_J3		"J3"
#define GROUPTEAM_TYPE_J4		"J4"
#define GROUPTEAM_TYPE_J5		"J5"
#define GROUPTEAM_TYPE_J6		"J6"
#define GROUPTEAM_TYPE_J7		"J7"
#define GROUPTEAM_TYPE_J8		"J8"
#define GROUPTEAM_TYPE_J9		"J9"
#define GROUPTEAM_TYPE_K0		"K0"
#define GROUPTEAM_TYPE_K1		"K1"
#define GROUPTEAM_TYPE_K3		"K3"
#define GROUPTEAM_TYPE_K4		"K4"
#define GROUPTEAM_TYPE_K5		"K5"
#define GROUPTEAM_TYPE_K6		"K6"
#define GROUPTEAM_TYPE_K7		"K7"
#define GROUPTEAM_TYPE_K8		"K8"
#define GROUPTEAM_TYPE_K9		"K9"
#define GROUPTEAM_TYPE_L0		"L0"
#define GROUPTEAM_TYPE_L1		"L1"
#define GROUPTEAM_TYPE_N0		"N0"

#define DATE_LENGTH		14
#define	SVCEXPIRETIME	"20200101000000"
#define DEFAULT_FLAG	F

#define Sinit(a) memset(a,0,sizeof(a))
