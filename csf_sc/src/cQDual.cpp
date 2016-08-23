///////////////// Input parameters ////////////////
////////////////////////////////////////////////////
///////////////// Output parameters ////////////////
// @	STRUCT
// -@0	TODAY	STRING
////////////////////////////////////////////////////
#include <allBCP.h>

using namespace std;

utype* cQDual(const utype * inParam,TCtrlInfo *errInfo)
{
	L4C_TRACE("------==INPUT BEGIN==-------");
	LogUtype(inParam);
	L4C_TRACE("------==INPUT END==-------");
	if(errInfo){
		memset(errInfo,0,sizeof(TCtrlInfo));
	}

	try{
		utGetStr(inParam, "throw");
		throw appException(9999, "sorry about that!!");
	}catch(uException &ex){
	}

	uAutoPtr uap(uInit(0));

	int rpcRows=0;
	otl_nocommit_stream sm_cQDual;


	sm_cQDual.set_flush(false);
	sm_cQDual.open(1,"select to_char(sysdate, 'yyyymmdd') today from dual ",GETDB(errInfo));


	sm_cQDual.flush();

	while(!sm_cQDual.eof()){
		char f0[8+1];


		sm_cQDual>>f0;
		if(sm_cQDual.is_null())
			utAddStr(uap,"TODAY","");
		else
			utAddStr(uap,"TODAY",Rtrim(f0));

		rpcRows++;
		break;
	}
	if(errInfo){
		errInfo->iSqlRows = rpcRows;
	}
	L4C_TRACE("------==OUTPUT BEGIN==-------");
	LogUtype(uap);
	L4C_TRACE("------==OUTPUT END==-------");
	return(uap.release());
}
