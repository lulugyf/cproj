#include <framework.h>

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
			if(strcmp(cfgGetStr("MAIN", "DCISUPPORT"), "OFF")!=0){
				mdbc.tryConnect(); //尝试连接内存数据库
				CtrlInfo.mainmdb=&mdbc.getMDBHandle();
				CtrlInfo.mdb=CtrlInfo.mainmdb;
				CtrlInfo.mdbLastConn=mdbc.getLastConnectTime();
			}
			else{
				CtrlInfo.mainmdb=NULL;
				CtrlInfo.mdb=NULL;
				
				dbc.tryConnect();
				CtrlInfo.maindb = &dbc.getOtlHandle();
				CtrlInfo.db = CtrlInfo.maindb;
			}
		}catch(...){
			CtrlInfo.mainmdb=NULL;
			CtrlInfo.mdb=NULL;

			//连接失败， 则尝试连接物理库
			dbc.tryConnect();
			CtrlInfo.maindb = &dbc.getOtlHandle();
			CtrlInfo.db = CtrlInfo.maindb;
		}
		
		utype *ret0 = ptUtypeFuncPtr(in, &CtrlInfo);
		utype *ret = uInit(1);
		utAddLong(ret, "RETURN_CODE", 0);
		utAddStr(ret, "RETURN_MSG", "ok!");
		if (ret0 != NULL){
			utAddStruct(ret,"OUT_DATA",ret0);
		}
		
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

extern utype* getRouteInfoMdb(const utype* p, TCtrlInfo* errInfo);

static int dotux(const char *svcname, char *input, char **output)
{
	uAutoPtr uin(uXml2Utype(input));
	uAutoPtr uout(callBP(uin, getRouteInfoMdb));
	*output = uUType2Xml(uout, "ROOT");
	return 0;
}

extern "C" void sRouteInfo(TPSVCINFO *transb)
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
