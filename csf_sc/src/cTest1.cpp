///////////////// Input parameters ////////////////
// @	STRUCT
// -@0	INT	col1
////////////////////////////////////////////////////
///////////////// Output parameters ////////////////
// @	STRUCT
// -@0	COL1	LONG
// -@1	COL2	STRING
////////////////////////////////////////////////////
#include <allBCP.h>

using namespace std;

utype* cTest1(const utype * inParam,TCtrlInfo *errInfo)
{
	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(inParam);
	L4C_TRACE("------==INPUT END==-------");
	if(errInfo){
		memset(errInfo,0,sizeof(TCtrlInfo));
	}

	uAutoPtr uap(uInit(0));

	int rpcRows=0;
	otl_nocommit_stream sm_cTest1;


	sm_cTest1.set_flush(false);
	sm_cTest1.open(1,"select col1, col2 from csf1 where col1=:col1<int> ", GETDB(errInfo));


	if(utGetEmpty(inParam,"col1"))
		sm_cTest1<<otl_null();
	else
		sm_cTest1<<utGetInt(inParam,"col1");

	sm_cTest1.flush();

	while(!sm_cTest1.eof()){
		long f0;
		char f1[30+1];


		sm_cTest1>>f0;
		if(sm_cTest1.is_null())
			utAddEmpty(uap,"COL1");
		else
			utAddLong(uap,"COL1",f0);

		sm_cTest1>>f1;
		if(sm_cTest1.is_null())
			utAddStr(uap,"COL2","");
		else
			utAddStr(uap,"COL2",Rtrim(f1));

		rpcRows++;
		break;
	}
	if(errInfo){
		errInfo->iSqlRows = rpcRows;
	}
	L4C_TRACE("------==OUTPUT BEGIN==-------");
	LogUtype(uap);
	L4C_TRACE("------==OUTPUT END==-------");
	utAddStr(uap, "Extra", "new item");
	utAddStr(uap, "Extra 1", "new item11111");
	return(uap.release());
}
