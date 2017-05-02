
#define	VERSION			"1.1.1"
#define DBLOGIN			"/gdblogin.cfg"
#define MAXLINE			1000

#define IS_SEND			'y'
#define NOT_SEND		'n'
#define IS_REDUCE		'y'
#define NOT_REDUCE		'n'

#define IS_HLR			"hlr"
#define MSISDN_ID		"SVCNUM"
#define IMSI_ID			"IMSI"
#define ONLY_ONE		"only"
#define DEF_TCODE		"err"
/*路由管理定义*/
/*#define ROUTEFLAG   0*/

struct PropertyID
{
	char			property_id[60];
	char			property_name[128];
	struct PropertyID	*next;
};

struct ImsiInHlr
{
	char			imsi_seg[16];
	char			hlr_code[16];
	struct ImsiInHlr	*next;
};

struct MsisdnInHlr
{
	char			msisdn_seg[16];
	char			hlr_code[16];
	struct MsisdnInHlr	*next;
};

struct MainActionGroup
{
	char			main_action_group[16];
	char			main_action_id[16];
	struct MainActionGroup	*next;
};

struct SubSvcGroup
{
	char			sub_svc_group[16];
	char			sub_svc_id[16];
	struct SubSvcGroup	*next;
};

struct HlrGroup
{
	char			hlr_group[16];
	char			hlr_code[16];
	struct HlrGroup	*next;
};

struct WorkOrderInfo
{
	char			wo_tablecode[16];
	char			cell_code[16];
	char			hlr_group[16];
	char			workorder_id[32];
	char			workorder_type;
	char			workorder_send;
	int				workorder_seq;
	char			issend_code[2048];
	char			is_value_map[2048];
	char 			is_mul_com[128];
	char			workorder_datas[2400];
	struct WorkOrderInfo	*next;
};

struct MainSvcConf
{
	char			main_svc_id[16];
	char			main_action_group[16];
	char			cell_code[16];
	char			hlr_group[16];
	char			workorder_id[32];
	char			workorder_type;
	int				workorder_seq;
	char 			issend_code[2048];
	char			is_value_map[2048];
	char			is_mul_com[128];
	struct MainSvcConf	*next;
};

struct SubSvcConf
{
	char			main_svc_id[16];
	char			main_action_group[16];
	char			sub_svc_group[16];
	char			sub_action_id[16];
	char			cell_code[16];
	char			hlr_group[16];
	char			workorder_id[32];
	char			workorder_type;
	int				workorder_seq;
	struct SubSvcConf	*next;
};

struct OrderProperty
{
	char			main_svc_id[16];
	char			main_action_group[16];
	char			svc_id[60];
	char			property_id[64];
	char			property_value[64];
	char			cell_code[16];
	char			hlr_group[16];
	char			workorder_id[32];
	char			workorder_type;
	int				workorder_seq;
	struct OrderProperty	*next;
};

struct WorkOrderSave
{
	char			cell_code[16];
	char			hlr_code[16];
	char			save_code[16];
	struct WorkOrderSave	*next;
};

struct SubSvcInfo
{
	char			sub_svc_id[16];
	char			sub_svc_group[16];
	char			sub_action_id[16];
	struct SubSvcInfo	*next;
};

struct PropertyInfo
{
	char			property_id[60];
	char			property_name[128];
	char			svc_id[60];
	char			property_value[512];
	char			property_mapvalue[512];
	char			property_mapid[60];
	struct PropertyInfo	*next;
};

struct OrderInfo
{
	char			crm_order_id[64];
	char			oss_order_id[32];
	char			work_order_id[32];
	char			service_no[64];
	int				order_priority;
	char			create_time[16];
	char			process_node_id[24];
	char 			cut_flag[10];
	char			cut_flag_wo[10];
	char			property_char[4127];

	char			hlr_code[16];
	char			hlr_group[16];
	char			login_no[20];
	struct OrderInfo	*next;
};

struct PropertyValueMapping
{

   char  cell_code[8+1];
   char  hlr_group[8+1];
   char  workorder_id[30+1];
   char  property_id[60+1];
   char  property_value[60+1];
   char  mapping_value[60+1];
   struct PropertyValueMapping  *next;
};
struct RelaPropGroup
{
   char main_svc_id[10+1];
   char main_action_group[8+1];
   char relaprop_id[60+1];
   char prop_id[60+1];
   char prop_val[60+1];
   char svc_id[60+1];
   struct RelaPropGroup *next;
};


struct RelaPropPty
{
 char prop_id[60+1];
 char prop_val[60+1];
 char svc_id[60+1];
 struct RelaPropPty *next;
};


struct RelaPropGroupMap
{
 char main_svc_id[10+1];
 char main_action_group[8+1];
 char relagroup_id[60+1];
 struct RelaPropPty RelaPropPtyHead;
 struct RelaPropGroupMap *next;
};


/*
struct RelaPropGroup
{
   char main_svc_id[10+1];
   char main_action_group[8+1];
   char svc_id[10+1];
   char relaprop_id[600+1];
   char prop_id[6][60+1];

   char prop_val[6][60+1];
   struct RelaPropGroup *next;
};*/
