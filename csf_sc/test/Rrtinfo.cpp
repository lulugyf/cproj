#include <framework.h>
#include "alloca.h"

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
	L4C_TRACE("11111111");
	static time_t lastInit=-1;
	static DCI_SQL dsql1;
	static DCI_SQL dsql2;
	static DCI_SQL dsql3;
	static DCI_SQL dsql4;
	uAutoPtr pout(uInit(10));
	DCI_SQL* dsql=NULL;
	DCI_ROW v_row;
	L4C_TRACE("2222222222222");
	int iRouteCode=utGetInt(p, "ROUTE_TYPE");
	L4C_TRACE("%d",iRouteCode);
	const char* sRouteValue=utGetStr(p, "ROUTE_VALUE");
	L4C_TRACE("%s",sRouteValue);
	int iRuleCode=0;
	int iRuleDataType=0;
	int iGroupLength=0;
	L4C_TRACE("333333333333333");
	L4C_TRACE("%d",GETMDBLASTCONN(errInfo));
	
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
	L4C_TRACE("444444444444444444");
	if(!GETMDB(errInfo)) return getRouteInfoOra(p, errInfo);
		L4C_TRACE("5555555555555555555555555555");
	if(dci_bind_param(GETMDB(errInfo), &dsql1, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)//绑定变量，有几个问号就需要调用几次。注意第3个入参表示变量的位置
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if(dci_query_p(GETMDB(errInfo), &dsql1)!=0)//执行查询
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	while((v_row = dci_fetch_row_s(GETMDB(errInfo), &dsql1))){
		iRuleCode=atoi(v_row[0]);
		iRuleDataType=atoi(v_row[1]);
		iGroupLength=atoi(v_row[2]);
	}
	L4C_TRACE("%d",iRuleCode);
	L4C_TRACE("666666666666666666666666666666666");
	if(iRuleCode==11){
		dsql=&dsql2;
	}else if(iRuleCode==10){
		if(iRuleDataType==11) dsql=&dsql3;
		else if(iRuleDataType==10) dsql=&dsql4;
		else throw(appException(399001001, "配置的路由数据类型错误"));
	} else throw(appException(399001002, "配置的路由规则类型错误"));
	if(dci_bind_param(GETMDB(errInfo), dsql, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		
		L4C_TRACE("777777777777777777777777777777777777");
		L4C_TRACE("%s",dsql);
		L4C_TRACE("%d",iRuleCode);
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
	L4C_TRACE("8888888888888888888888888888888");
	if(dci_query_p(GETMDB(errInfo), dsql)!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		
		L4C_TRACE("9999999999999999999999999999999999");
	if((v_row = dci_fetch_row_s(GETMDB(errInfo), dsql))){
		utAddInt(pout, "PARTITION_CODE", atoi(v_row[0]));
		utAddStr(pout, "WEB_SUFFIX", v_row[1]);
		utAddStr(pout, "NOTE", v_row[2]);
	}else{
		L4C_TRACE("0000000000000000000000000000000000000000000");
		throw(appException(399001003, "路由数据不存在"));
	}
	return pout.release();
	
}


static void initLogEnv() {
	static bool isInit = false;
	char stmp[1024]; /* new add */
	if (isInit)
		return;
	bool lcnull = false, ccnull = false;
	string env = "";
	if (getenv("L4C_CFG") == NULL) {
		lcnull = true;
	} else if (getenv("L4C_CFG")[0] == 0)
		lcnull = true;
	if (getenv("CRM_CFG") == NULL) {
		ccnull = true;
	} else if (getenv("CRM_CFG")[0] == 0)
		ccnull = true;
	if (lcnull) {
		if (ccnull)
			env = env + getenv("HOME") + "/run/cfg/crm.cfg";
		else
			env = env + getenv("CRM_CFG");
		/* setenv("L4C_CFG", env.c_str(), 1); for mem leak */
		strcpy(stmp, "L4C_CFG="); /* new add */
		strcat(stmp, env.c_str());/* new add */
		putenv(stmp); /* new add */
	}
}

static utype* callBP(const utype* in, TUtypeFuncPtr ptUtypeFuncPtr)
{
	static db_factory dbFactory(1 != 0);
	TCtrlInfoEx CtrlInfo;

	static db_connect mdbc;
	static db_connect dbc;
	static char dblabel[60];

	static bool isInit=false;

	initLogEnv();

	if (!isInit) {
		memset(&CtrlInfo, 0, sizeof(TCtrlInfoEx));
		mdbc.init("imdb");
		mdbc.setActive(true);
		isInit = true;
		snprintf(dblabel, sizeof(dblabel)-1, "dbcen%s", cfgGetCurrentDBInstance());
		dbc.init(dblabel);
		dbc.setActive(true);
		
	}

	try {
		dbFactory.resetActive();
		CtrlInfo.maindb = NULL;
		CtrlInfo.db = NULL;
		CtrlInfo.bReconnFlag = false;
		//连接内存数据库
		try{
			mdbc.tryConnect(); //尝试连接内存数据库
			CtrlInfo.mainmdb=&mdbc.getMDBHandle();
			CtrlInfo.mdb=CtrlInfo.mainmdb;
			CtrlInfo.mdbLastConn=mdbc.getLastConnectTime();
		}catch(...){
			CtrlInfo.mainmdb=NULL;
			CtrlInfo.mdb=NULL;

			//连接失败， 则尝试连接物理库
			dbc.tryConnect();
			CtrlInfo.maindb = &dbc.getOtlHandle();
			CtrlInfo.db = CtrlInfo.maindb;
		}
		utype *ret = ptUtypeFuncPtr(in, &CtrlInfo);
		utAddLong(ret, "RETURN_CODE", 0);
		utAddStr(ret, "RETURN_MSG", "success");
		return ret;
	}catch(appException &e){
		utype *ret = uInit(1);
		utAddLong(ret, "RETURN_CODE", e.errCode);
		utAddStr(ret, "RETURN_MSG", e.errMsg);
		return ret;
	}catch (uException& err) {
		utype *ret = uInit(1);
		long retCode = 303 * 1000000 + err.errCode;
		utAddLong(ret, "RETURN_CODE", retCode);
		utAddStr(ret, "RETURN_MSG", err.errMsg);
		return ret;
	} catch (...) {
		//throw;
		utype *ret = uInit(1);
		utAddLong(ret, "RETURN_CODE", 11111111);
		utAddStr(ret, "RETURN_MSG", "query failed");
		return ret;
	}

	return NULL;
}

//extern utype* getRouteInfoMdb(const utype* p, TCtrlInfo* errInfo);

static int dotux(const char *svcname, char *input, char **output)
{
	uAutoPtr uin(uXml2Utype(input));
	uAutoPtr uout(callBP(uin, getRouteInfoMdb));
	*output = uUType2Xml(uout, "ROOT");
	return 0;
}

extern "C" void sRoute_info(TPSVCINFO *transb)
{
	char * output = NULL; 
	char * outbuf = NULL;
	int outlen = 0, ret = 0;

	ret = dotux(transb->name, transb->data, &output);

	if(output != NULL){
		outlen = strlen(output)+1;
		outbuf = (char *)tpalloc((char *)"STRING", NULL, outlen);
		memcpy(outbuf, output, outlen);
		free(output);
		tpreturn(TPSUCCESS, 0, outbuf, outlen, 0);
	}else{
		const char *err = "<r>error</r>";
		outlen = strlen(err)+1;
		outbuf = (char *)tpalloc((char *)"STRING", NULL, outlen);
		memcpy(outbuf, err, outlen);
		tpreturn(TPSUCCESS, 0, outbuf, outlen, 0);
	}
}


