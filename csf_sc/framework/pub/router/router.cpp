#include "alloca.h"
#include "framework.h"

/*
宏定义说明
SX_ROUTE_FUNC 涉及到山西特殊的路由服务, 涉及到2000个号码的问题, 需要特殊判断;
SX_ONLY_FOR_B: B区上线后,A区上线前, 路由服务的返回值如果是A1的话,就替换成B1,
               如果是A2的话,就替换成B2;
			   A1 --> B1
			   A2 --> B2
*/
/* 为朔州特殊处理，只要不是跨区号码，均返回B1
*/


/* #define SX_ROUTE_FUNC 1 liupengc 0324 A区割接,不再区分路由 */
#define SX_ONLY_FOR_B 1
/* 取消 B 区的路由方式 liupengc 
#ifdef SX_ONLY_FOR_B
#undef SX_ONLY_FOR_B
#endif
*/
#define SX_ONLY_ID_PHONE_NO_ROUTE 1
#define SX_ID_NO_ROUTE 11      /* 11 : 用户id路哟 */
#define SX_PHONE_NO_ROUTE 10   /* 10 : 号码路由 */
#define SX_GUOXX_CODE 399001999


/* 测试 报文 */
/*
<ROOT>
	<ROUTE_TYPE type="int">10</ROUTE_TYPE>
	<ROUTE_VALUE type="string">18234941234</ROUTE_VALUE>
</ROOT>

新服务的路由说明:

*/

utype* check_route_type(int iRouteCode)
{
	uAutoPtr pout(uInit(10));
}

/*
如果路由的号码在 2000 个号码中, 那么返回1, 否则返回 0
1: 路由号码是2000个号码;
0: 路由号码不是2000个号码;
*/
/**/
int check_2000_phone_and_id_ora(int i_route_code, const char * s_route_value, TCtrlInfo* errInfo)
{
	static char route_type_name[32];
    static char sql_str[256];

	/*
	i_route_code == SX_ID_NO_ROUTE ? strcpy(route_type_name,"ID_NO") : strcpy(route_type_name,"PHONE_NO");
	sprintf(sql_str, "select 1 from un_user_info where  %s = :v1<char[21]>", route_type_name);
    */
    if(i_route_code == SX_ID_NO_ROUTE)
    {
    	strcpy(sql_str, "select 1 from un_user_info where  ID_NO = :v1<long>");
    }
    else
    {
    	strcpy(sql_str, "select 1 from un_user_info where  PHONE_NO = :v1<char[21]>");
    }
	static int tmp = -9;
	otl_nocommit_stream qry_exist(1, sql_str, GETDB(errInfo));
	if(i_route_code == SX_ID_NO_ROUTE)
	{
		qry_exist << atol(s_route_value);
	}
	else
	{
		qry_exist << s_route_value;
	}

	if(qry_exist.eof()) return 0;  /* 在 un_user_info 表中无法查到 */
	qry_exist >> tmp;
	return 1;
}

/*  由于内存数据库断链后不能根据 static 变量进行初始化 直接在源代码中处理
int check_2000_phone_and_id_imdb(int i_route_code, char * s_route_value, TCtrlInfo* errInfo)
{
	static char route_type_name[32];
    static char sql_str[256];
    static DCI_SQL dsql4;
	static int pre_flag = 0;

	i_route_code == SX_ID_NO_ROUTE ? strcpy(route_type_name,"ID_NO") : strcpy(route_type_name,"PHONE_NO");
	sprintf(sql_str, "select 1 from un_user_info where  %s = ?", route_type_name);

	if(pre_flag == 0)
	{
		if(dci_prepare_sql(GETMDB(errInfo), &dsql4, sql_str)!=0) //预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		pre_flag = 1;
	}

	if(dci_bind_param(GETMDB(errInfo), &dsql4, 0, DCI_TYPE_CHAR, (void*)(s_route_value))!=0)//绑定变量，有几个问号就需要调用几次。
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if(dci_query_p(GETMDB(errInfo), &dsql4)!=0)//执行查询
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

	static DCI_ROW v_row;
	static int row_s = 0;
	while((v_row = dci_fetch_row_s(GETMDB(errInfo), &dsql4))){
		row_s++;
	}
	return row_s;
}
*/



#ifdef SX_ROUTE_FUNC
/* 涉及到新的路由服务 */
utype* getRouteInfoOra(const utype* p, TCtrlInfo* errInfo)
{
	L4C_WARN("内存数据库无法使用，使用oracle获取路由数据");
	static bool isFirst=true;
	static const char* sSql0="select rule_code,route_data_type,group_length from bs_routerule_dict where  route_code=:ROUTE_TYPE<int> ";
	static const char* sSql2="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code and b.key_value = :ROUTE_VALUE<char[128]>";
	static const char* sSql3="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code AND TO_NUMBER (b.key_value)<:ROUTE_VALUE<long> and TO_NUMBER (b.key_value2)>:ROUTE_VALUE<long> ";
	static const char* sSql4="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code AND b.key_value<:ROUTE_VALUE<char[128]>  AND b.key_value2>:ROUTE_VALUE<char[128]>";
	const char* sSql=NULL;
	int pcode;
	char sWebSuffix[64]="";
	char sNote[60+1]="";
	uAutoPtr pout(uInit(10));
	int iRouteCode=utGetInt(p, "ROUTE_TYPE");
	const char* sRouteValue=utGetStr(p, "ROUTE_VALUE");
	int iRuleCode=0;
	int iRuleDataType=0;
	int iGroupLength=0;
    static char tmp_msg[128];
	/* liupengc 如果是不是用户id 或者 号码路由,那么就返回 B1*/
	if( !(iRouteCode == SX_ID_NO_ROUTE || iRouteCode == SX_PHONE_NO_ROUTE) )
	{
		/* B 大区上线，不再返回固定值 
		utAddStr(pout, "WEB_SUFFIX", "B1");
		utAddInt(pout, "PARTITION_CODE", 20); // added for dongxiao using 
		utAddStr(pout, "NOTE", "16"); // added for dongxiao using 
		return pout.release();
		*/
		goto RAW_DEAL;
		
	}
	/* liupengc 判断 路由的值是否在2000个表中  非0 表示找到数据*/
	if(check_2000_phone_and_id_ora(iRouteCode,sRouteValue,errInfo) != 0)
	{
		/* static char tmp_msg[128]; up to start!*/
		sprintf(tmp_msg,"路由的数据[%s]在[UN_USER_INFO]表中", sRouteValue);
		throw(appException(SX_GUOXX_CODE, tmp_msg));
	}
	/* 19:51 2012年2月24日 B大区上线后, 对于不在跨区表中的数据 查找路由数据表,是B1就返回B1, 是B2就返回B2 
	else // 固定返回B1  add by zl
	{
		utAddStr(pout, "WEB_SUFFIX", "B1");
		utAddInt(pout, "PARTITION_CODE", 20); // added for dongxiao using 
		utAddStr(pout, "NOTE", "16"); // added for dongxiao using 
		return pout.release();
	}
    */
RAW_DEAL:
	otl_nocommit_stream qRouteRule(1, sSql0, GETDB(errInfo));
	qRouteRule<<utGetInt(p, "ROUTE_TYPE");
	if(qRouteRule.eof()) throw(appException(399001000, "路由类型不存在"));
	qRouteRule>>iRuleCode>>iRuleDataType>>iGroupLength;

	if(iRuleCode==11){
		sSql=sSql2;
	}else if(iRuleCode==10){
		if(iRuleDataType==11) sSql=sSql3;
		else if(iRuleDataType==10) sSql=sSql4;
		else throw(appException(399001001, "配置的路由数据类型错误"));
	} else throw(appException(399001002, "配置的路由规则类型错误"));
	otl_nocommit_stream qRouteInfo(1, sSql, GETDB(errInfo));
	qRouteInfo<<iRouteCode;

	if(iRuleCode==11){
		char* s=(char*) alloca(iGroupLength+1);
		memset(s,0,iGroupLength+1);
		strncpy(s,sRouteValue,iGroupLength);
		qRouteInfo<<s;
	}else{
		if(iRuleDataType==11){
			long lValue=atol(sRouteValue);
			qRouteInfo<<lValue;
		}else{
			qRouteInfo<<sRouteValue;
		}
	}
	if(qRouteInfo.eof()) throw(appException(399001003, "路由数据不存在"));
	/* if(qRouteInfo.eof()) throw(appException(SX_GUOXX_CODE, "路由数据不存在"));*/
	qRouteInfo>>pcode>>sWebSuffix>>sNote;
	utAddInt(pout, "PARTITION_CODE", pcode);
/* liupengc 按照路由数据真实的配置返回信息  所以要取消 SX_ONLY_FOR_B
#ifdef SX_ONLY_FOR_B
    if(sWebSuffix[0]== 'A' || sWebSuffix[0]== 'a')
	{
		static char tmp_log_msg[128];
		sprintf(tmp_log_msg, "在数据库中查找的分区类型为[%s]:不是割接地区",sWebSuffix);
		throw(appException(SX_GUOXX_CODE, tmp_log_msg));
	}
#endif
*/
	utAddStr(pout, "WEB_SUFFIX", sWebSuffix);
	utAddStr(pout, "NOTE", sNote);

	return pout.release();

}

utype* getRouteInfoMdb(const utype* p, TCtrlInfo* errInfo)
{
	static time_t lastInit=0;
	static DCI_SQL dsql1;
	static DCI_SQL dsql2;
	static DCI_SQL dsql3;
	static DCI_SQL dsql4;
	static DCI_SQL dsql5;// liupengc check 2000
    static DCI_SQL dsql6;// liupengc check 2000

	uAutoPtr pout(uInit(10));
	DCI_SQL* dsql=NULL;
	DCI_ROW v_row;
	int iRouteCode=utGetInt(p, "ROUTE_TYPE");
	const char* sRouteValue=utGetStr(p, "ROUTE_VALUE");
	int iRuleCode=0;
	int iRuleDataType=0;
	int iGroupLength=0;

	/* liupengc 如果是不是用户id 或者 号码路由,那么就返回 B1 #### 如果不是 号码和用户号码路由，那么走默认方式
	if( !(iRouteCode == SX_ID_NO_ROUTE || iRouteCode == SX_PHONE_NO_ROUTE) )
	{
		utAddStr(pout, "WEB_SUFFIX", "B1");
		utAddInt(pout, "PARTITION_CODE", 20); 
		utAddStr(pout, "NOTE", "16"); 

		return pout.release();
	}
    */


	if(GETMDBLASTCONN(errInfo)!=lastInit){//用这种方式保证只会预处理一次sql语句，防止多次预处理sql语句造成的时间浪费

		L4C_TRACE("mdb init");
		if(!GETMDB(errInfo)) return getRouteInfoOra(p, errInfo);



		if(dci_prepare_sql(GETMDB(errInfo), &dsql1, "select rule_code,route_data_type,group_length from bs_routerule_dict where  route_code=? ")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql2, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														and b.key_value = ?")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql3, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														  AND TO_NUMBER (b.key_value)<? and TO_NUMBER (b.key_value2)>? ")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql4, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														AND b.key_value<?  AND b.key_value2>?")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		/* 对 2000 个号码进行过滤 */
		if(dci_prepare_sql(GETMDB(errInfo), &dsql5, "select 1 from un_user_info where ID_NO=? ")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql6, "select 1 from un_user_info where PHONE_NO=? ")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}

		lastInit=GETMDBLASTCONN(errInfo);
	}
	if(!GETMDB(errInfo)) return getRouteInfoOra(p, errInfo);

	/************ 在 UN_USER_INFO 表中产看数据 *************/
    if(iRouteCode == SX_ID_NO_ROUTE)  /* ID_NO */
    {
    	long rv_value = atol(sRouteValue);
		if(dci_bind_param(GETMDB(errInfo), &dsql5, 0, DCI_TYPE_LONG, (void*)(&rv_value))!=0)//绑定变量，有几个问号就需要调用几次。
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		if(dci_query_p(GETMDB(errInfo), &dsql5)!=0)//执行查询
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

		int row_s_5 = 0;
		while( dci_fetch_row_s(GETMDB(errInfo), &dsql5) ){
			row_s_5++;
		}
		if(row_s_5 != 0)
		{
			static char tmp_msg[128];
			sprintf(tmp_msg,"路由的数据ID_NO=[%s]在[UN_USER_INFO]表中", sRouteValue);
			throw(appException(SX_GUOXX_CODE, tmp_msg));
		}
		/* 按照实际情况返回值 liupengc 
		else // 固定返回B1  add by zl
		{
			utAddStr(pout, "WEB_SUFFIX", "B1");
			utAddInt(pout, "PARTITION_CODE", 20); // added for dongxiao using 
			utAddStr(pout, "NOTE", "16"); // added for dongxiao using 

			return pout.release();
		}
		*/
    }
    else if(iRouteCode == SX_PHONE_NO_ROUTE)/* PHONE_NO */
	{

		if(dci_bind_param(GETMDB(errInfo), &dsql6, 0, DCI_TYPE_CHAR, (void*)(sRouteValue))!=0)//绑定变量，有几个问号就需要调用几次。
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		if(dci_query_p(GETMDB(errInfo), &dsql6)!=0)//执行查询
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

		int row_s_6 = 0;
		while((dci_fetch_row_s(GETMDB(errInfo), &dsql6))){
			row_s_6++;
		}
		if(row_s_6 != 0)
		{
			static char tmp_msg[128];
			sprintf(tmp_msg,"路由的数据PHONE_NO=[%s]在[UN_USER_INFO]表中", sRouteValue);
			throw(appException(SX_GUOXX_CODE, tmp_msg));
		}
		/* 按照真实的值返回 liupengc
		else // 固定返回B1  add by zl
		{
			utAddStr(pout, "WEB_SUFFIX", "B1");
			utAddInt(pout, "PARTITION_CODE", 20); // added for dongxiao using 
			utAddStr(pout, "NOTE", "16"); // added for dongxiao using 

			return pout.release();
		}
		*/
	}
    /************* 代码冗余可以进行优化 *********************/
	if(dci_bind_param(GETMDB(errInfo), &dsql1, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)//绑定变量，有几个问号就需要调用几次。注意第3个入参表示变量的位置
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if(dci_query_p(GETMDB(errInfo), &dsql1)!=0)//执行查询
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	while((v_row = dci_fetch_row_s(GETMDB(errInfo), &dsql1))){
		iRuleCode=atoi(v_row[0]);
		iRuleDataType=atoi(v_row[1]);
		iGroupLength=atoi(v_row[2]);
	}
	if(iRuleCode==11){
		dsql=&dsql2;
	}else if(iRuleCode==10){
		if(iRuleDataType==11) dsql=&dsql3;
		else if(iRuleDataType==10) dsql=&dsql4;
		else throw(appException(399001001, "配置的路由数据类型错误"));
	} else throw(appException(399001002, "配置的路由规则类型错误"));
	if(dci_bind_param(GETMDB(errInfo), dsql, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

	if(iRuleCode==11){
		char* s=(char*) alloca(iGroupLength+1);
		memset(s,0,iGroupLength+1);
		strncpy(s,sRouteValue,iGroupLength);
		if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_CHAR, (void*)s)!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	}else{
		if(iRuleDataType==11){
			long lValue=atol(sRouteValue);
			if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_LONG, (void*)(&lValue))!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_bind_param(GETMDB(errInfo), dsql, 2, DCI_TYPE_LONG, (void*)(&lValue))!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		}else{
			if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_CHAR, (void*)sRouteValue)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_bind_param(GETMDB(errInfo), dsql, 2, DCI_TYPE_CHAR, (void*)sRouteValue)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		}

	}
	if(dci_query_p(GETMDB(errInfo), dsql)!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if((v_row = dci_fetch_row_s(GETMDB(errInfo), dsql))){
		utAddInt(pout, "PARTITION_CODE", atoi(v_row[0]));
/* 按照真实的值返回 liupengc 
#ifdef SX_ONLY_FOR_B
    if(v_row[1][0]=='A' || v_row[1][0]=='a')
		throw(appException(SX_GUOXX_CODE, "在数据库中查找的是A区:不是割接地区"));
#endif
*/

		utAddStr(pout, "WEB_SUFFIX", v_row[1]);
		utAddStr(pout, "NOTE", v_row[2]);
	}else{
		throw(appException(399001003, "路由数据不存在"));
	}
	return pout.release();

}


#else
/* liupengc 走之前老的路由服务 */
utype* getRouteInfoOra(const utype* p, TCtrlInfo* errInfo)
{
	L4C_WARN("内存数据库无法使用，使用oracle获取路由数据");
	static bool isFirst=true;
	static const char* sSql0="select rule_code,route_data_type,group_length from bs_routerule_dict where  route_code=:ROUTE_TYPE<int> ";
	static const char* sSql2="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code and b.key_value = :ROUTE_VALUE<char[128]>";
	static const char* sSql3="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code AND TO_NUMBER (b.key_value)<:ROUTE_VALUE<long> and TO_NUMBER (b.key_value2)>:ROUTE_VALUE<long> ";
	static const char* sSql4="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code AND b.key_value<:ROUTE_VALUE<char[128]>  AND b.key_value2>:ROUTE_VALUE<char[128]>";
	const char* sSql=NULL;
	int pcode;
	char sWebSuffix[64]="";
	char sNote[60+1]="";
	uAutoPtr pout(uInit(10));
	int iRouteCode=utGetInt(p, "ROUTE_TYPE");
	const char* sRouteValue=utGetStr(p, "ROUTE_VALUE");
	int iRuleCode=0;
	int iRuleDataType=0;
	int iGroupLength=0;

	otl_nocommit_stream qRouteRule(1, sSql0, GETDB(errInfo));
	qRouteRule<<utGetInt(p, "ROUTE_TYPE");
	if(qRouteRule.eof()) throw(appException(399001000, "路由类型不存在"));
	qRouteRule>>iRuleCode>>iRuleDataType>>iGroupLength;

	if(iRuleCode==11){
		sSql=sSql2;
	}else if(iRuleCode==10){
		if(iRuleDataType==11) sSql=sSql3;
		else if(iRuleDataType==10) sSql=sSql4;
		else throw(appException(399001001, "配置的路由数据类型错误"));
	} else throw(appException(399001002, "配置的路由规则类型错误"));
	otl_nocommit_stream qRouteInfo(1, sSql, GETDB(errInfo));
	qRouteInfo<<iRouteCode;

	if(iRuleCode==11){
		char* s=(char*) alloca(iGroupLength+1);
		memset(s,0,iGroupLength+1);
		strncpy(s,sRouteValue,iGroupLength);
		qRouteInfo<<s;
	}else{
		if(iRuleDataType==11){
			long lValue=atol(sRouteValue);
			qRouteInfo<<lValue;
		}else{
			qRouteInfo<<sRouteValue;
		}
	}
	if(qRouteInfo.eof()) throw(appException(399001003, "路由数据不存在"));
	qRouteInfo>>pcode>>sWebSuffix>>sNote;
	utAddInt(pout, "PARTITION_CODE", pcode);
	utAddStr(pout, "WEB_SUFFIX", sWebSuffix);
	utAddStr(pout, "NOTE", sNote);

	return pout.release();

}

utype* getRouteInfoMdb(const utype* p, TCtrlInfo* errInfo)
{
	static time_t lastInit=0;
	static DCI_SQL dsql1;
	static DCI_SQL dsql2;
	static DCI_SQL dsql3;
	static DCI_SQL dsql4;
	uAutoPtr pout(uInit(10));
	DCI_SQL* dsql=NULL;
	DCI_ROW v_row;
	int iRouteCode=utGetInt(p, "ROUTE_TYPE");
	const char* sRouteValue=utGetStr(p, "ROUTE_VALUE");
	int iRuleCode=0;
	int iRuleDataType=0;
	int iGroupLength=0;

	if(GETMDBLASTCONN(errInfo)!=lastInit){//用这种方式保证只会预处理一次sql语句，防止多次预处理sql语句造成的时间浪费

		L4C_TRACE("mdb init");
		if(!GETMDB(errInfo)) return getRouteInfoOra(p, errInfo);

		if(dci_prepare_sql(GETMDB(errInfo), &dsql1, "select rule_code,route_data_type,group_length from bs_routerule_dict where  route_code=? ")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql2, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														and b.key_value = ?")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql3, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														  AND TO_NUMBER (b.key_value)<? and TO_NUMBER (b.key_value2)>? ")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql4, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														AND b.key_value<?  AND b.key_value2>?")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		lastInit=GETMDBLASTCONN(errInfo);
	}
	if(!GETMDB(errInfo)) return getRouteInfoOra(p, errInfo);
	if(dci_bind_param(GETMDB(errInfo), &dsql1, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)//绑定变量，有几个问号就需要调用几次。注意第3个入参表示变量的位置
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if(dci_query_p(GETMDB(errInfo), &dsql1)!=0)//执行查询
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	while((v_row = dci_fetch_row_s(GETMDB(errInfo), &dsql1))){
		iRuleCode=atoi(v_row[0]);
		iRuleDataType=atoi(v_row[1]);
		iGroupLength=atoi(v_row[2]);
	}
	if(iRuleCode==11){
		dsql=&dsql2;
	}else if(iRuleCode==10){
		if(iRuleDataType==11) dsql=&dsql3;
		else if(iRuleDataType==10) dsql=&dsql4;
		else throw(appException(399001001, "配置的路由数据类型错误"));
	} else throw(appException(399001002, "配置的路由规则类型错误"));
	if(dci_bind_param(GETMDB(errInfo), dsql, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

	if(iRuleCode==11){
		char* s=(char*) alloca(iGroupLength+1);
		memset(s,0,iGroupLength+1);
		strncpy(s,sRouteValue,iGroupLength);
		if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_CHAR, (void*)s)!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	}else{
		if(iRuleDataType==11){
			long lValue=atol(sRouteValue);
			if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_LONG, (void*)(&lValue))!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_bind_param(GETMDB(errInfo), dsql, 2, DCI_TYPE_LONG, (void*)(&lValue))!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		}else{
			if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_CHAR, (void*)sRouteValue)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_bind_param(GETMDB(errInfo), dsql, 2, DCI_TYPE_CHAR, (void*)sRouteValue)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		}

	}
	if(dci_query_p(GETMDB(errInfo), dsql)!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if((v_row = dci_fetch_row_s(GETMDB(errInfo), dsql))){
		utAddInt(pout, "PARTITION_CODE", atoi(v_row[0]));
		utAddStr(pout, "WEB_SUFFIX", v_row[1]);
		utAddStr(pout, "NOTE", v_row[2]);
	}else{
		/*throw(appException(399001003, "路由数据不存在")); liupengc */
                return getRouteInfoOra(p, errInfo);
	}
	return pout.release();

}

#endif

utype* getRouteInfo(const utype* p, TCtrlInfo* errInfo)
{
	return getRouteInfoMdb(p, errInfo);
}


utype* getSysdateTest(const utype* p, TCtrlInfo* errInfo)
{
	/*char *sql_str = "select to_char(sysdate,'YYYYMMDDHH24MISS') DT  from dual;";*/
	char dt[32] = {0};
	/*otl_nocommit_stream qQry(1, sql_str, GETDB(errInfo));
	qQry>>dt;*/
	uAutoPtr pout(uInit(1));
	utAddStr(pout, "DT", "20121231010203");
	return pout.release();
}


