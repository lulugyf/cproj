#include "allBCP.h"

#include <dlfcn.h>

#define _PRINT_MSG_ 1

extern int iUtypeMallocTimes;

void dotuxadp(char **obuf, int* obufLen, const char *psServiceName,
		TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType);

// typedef utype* (*TUtypeFuncPtr)(const utype *uInParam, TCtrlInfo *ctrlInfo);
static TUtypeFuncPtr _getFuncByName(const char *modpath, const char *funcname)
{
	void *handle;
	char cppfuncname[128], ostype[20];
	TUtypeFuncPtr func;
	char errmsg[200];


	handle = dlopen( modpath, RTLD_LAZY );
	if(handle == NULL)
	{
        printf("不能打开对应的模块[%s][%s] %s\n", funcname, modpath, dlerror());
        return NULL;
	}
    func = (TUtypeFuncPtr)dlsym(handle, funcname);
    if(func != NULL){
    	return func;
    }

#if (defined(__hpux))
	sprintf(cppfuncname, "_Z%d%sPK8tagutypeP11tagCtrlInfo", strlen(funcname), funcname);
    strcpy(ostype, "hpux");
#elif (defined(__sun))
	sprintf(cppfuncname, "__1cM%s6FpknItagutype_pnLtagCtrlInfo__p0_", funcname);
    strcpy(ostype, "sunos");
#elif (defined(__linux__))
	sprintf(cppfuncname, "_Z%ld%sPK8tagutypeP11tagCtrlInfo", strlen(funcname), funcname);
    strcpy(ostype, "linux");
#elif (defined(_AIX))
	sprintf(cppfuncname, "%s__FPC8tagutypeP11tagCtrlInfo",  funcname);
    strcpy(ostype, "aix");
#else
	sprintf(cppfuncname, "_Z%d%sPK8tagutypeP11tagCtrlInfo", strlen(funcname), funcname);
    strcpy(ostype, "other");
#endif

    //printf("ostype=[%s] cppfuncname=[%s]\n", ostype, cppfuncname);
	func = (TUtypeFuncPtr)dlsym( handle, cppfuncname );
	if(func == NULL){
		printf("can not dlsym for %s->[%s], errno=%d\n", modpath, funcname, errno);
		return NULL;
	}
	return func;
}

void crmCfgClose();

int main(int argc, const char *argv[])
{

	if(argc < 6){
		printf("Usage: %s <servicename> <modfile> <bpname> <dblabel> <param>\n\n");
		return 1;
	}
	const char *psServiceName = argv[1];
	const char *psUtypeFunc = argv[3];
	TUtypeFuncPtr ptUtypeFuncPtr = _getFuncByName(argv[2], argv[3]);
	if(ptUtypeFuncPtr == NULL)
		return 2;
	const char *psDbLabel = argv[4];
	TPSVCINFO _transb, *transb;
	_transb.data = (char *)argv[5];
	transb = &_transb;
	int iConnType = 0;


	char* outbuf = NULL;
	int outlen = 0, before = 0;
	before = iUtypeMallocTimes;
	SetDebugStatus(true);
	dotuxadp(&outbuf, &outlen, psServiceName, transb, psDbLabel, psUtypeFunc,
			ptUtypeFuncPtr, doMerge, iConnType);
	if (iUtypeMallocTimes - before != 0
			&& strcmp(cfgGetStr("MAIN", "UTYPELEAK"), "OFF") != 0)
		printf("服务[%s]未释放utype内存分配次数:%d\n\n", psServiceName,
				iUtypeMallocTimes - before);
	if(outbuf != NULL){
		printf("====OUT:%s\n", outbuf);
		tpfree(outbuf);
	}
	crmCfgClose();
	return 0;
}


/*
 *
/crmtux1/work/guanyf/testbc11/MyTest sDynSvc /crmtux1/run/solib/libBusi.so pDynSvc dbchangea1 '{"ROOT":{"HEADER":{"POOL_ID":"11","CONTACT_ID":"112014050515090125624340494","CHANNEL_ID":"11","ROUTING":{"ROUTE_KEY":"15","ROUTE_VALUE":"11"},"DB_ID":"A1"},"BODY":{"COMMON_INFO":{"CONTACT_ID":"","CHNN_ID":"11","PROVINCE_GROUP":"O","SESSION_ID":"O","SER_NAME":"O","ROUND_AUDIT":"O","DEST_IP":"O","DEST_PORT":"O","SRC_PORT":"O","APP_NAME":"O","APP_ID":"2000","FROM_SYS":"BOSS","BAK2":"O"},"SVC_NAME":"d39262"}}}'

====a.sh===== 生成makefile中的 lib列表， 连接全部的库， 有几个库连接的时候报错有找不到的符号，直接剔除了
cd $WORKDIR/solib
v=""
for f in lib*.so
do
v1=`echo $f|awk '{print substr($0,4,length($0)-6)}'`
v="$v -l$v1"
done
echo $v

====makefile=====
INC=-I/crmtux1/run/framework/pub/liblogutype  -I/crmtux1/run/framework/pub/tuxadp -I/crmtux1/run/framework/pub/router -I/crmtux1/run/framework/pub/publog -I/crmtux1/run/framework/pub/filter -I/crmtux1/run/framework/pub/rule -I/crmtux1/run/framework/pub/utype  -I/crmtux1/run/framework/pub/libdbug -I/crmtux1/run/framework/pub/libsys -I/crmtux1/run/framework/pub/BossLib/include -I/crmtux1/run/framework/pub/BossTuxLib/include -I/crmtux1/run/framework/src/border/include -I/crmtux1/run/framework/pub/zlib -I/crmtux1/run/imdb/dci/include/ -I/crmtux1/run/framework/src/zdb/libzdb -I/crmtux1/run/framework/src/zdb/libzdbclient -I/crmtux1/run/framework/src/zdb/libzdbserver -I/crmtux1/run/framework/include -I/crmtux1/run/public/include -I/crmtux1/run/xerces/include -I/tuxedo/tuxedo11gR1/include -I/oracle/app/oracle/product/11.2.0/client/precomp/public -I/oracle/app/oracle/product/11.2.0/client/rdbms/public -I/oracle/app/oracle/product/11.2.0/client/rdbms/demo -I/crmtux1/work/inc_all/ -I/crmtux1/run/framework/pub/liblogfunc -I/crmtux1/run/framework/pub/zlib -I/crmtux1/run/framework/src/custsvc/oop/src -I/crmtux1/libmemcached/include -I/usr/vacpp/include -I/usr/include

LIBS=-l1000Back -l1000Cfm -l1000Finish -l1050Cfm -l1050Finish -l1052 -l1052Finish -l1053 -l1053Back -l1053Finish -l1055 -l1055Finish -l1055RuleLimit -l1056Cfm -l1056Finish -l1087 -l1104 -l1108 -l1119Finish -l1119OrderCfm -l1147 -l1152 -l1158Cfm -l1160Cfm -l1178Cfm -l1182 -l1183 -l1184 -l1184Back -l1187 -l1213 -l1213Cfm -l1218Cfm -l1229 -l13512Cfm -l13513Cfm -l13514Cfm -l1351Cfm -l1351Finish -l1604 -l1615 -l1880Cfm -l1893Cfm -l1930Cfm -l1953 -l2076 -l2263 -l2304Cfm -l2310 -l2312 -l2313 -l3839 -l3966Cfm -l4124Cfm -l4125 -l4487 -l5000Finish -lAcctBillBC -lAcctBillBC1 -lAcctBillBP -lAcctGetinter -lAcctInvBC -lAcctInvBP -lAcctMarkBC -lAcctMarkBP -lAcctPayBC -lAcctPayBP -lAcctPubBC -lAcctPubBP -lAcctPubCon -lAcctQueryBC -lAcctQueryBP -lBalanceBC -lBalanceBP -lBaseTree -lBossPubService -lBossSys -lBossTux -lBusi -lCalAdp -lCallESBApi -lCallESBApi_test -lCancelInter -lChkBusiRule -lChkDeposit -lChkSonOfGroup -lChkUserSvc -lClsys -lCopyCard -lDBConn -lDataNetRePort -lDataShm -lDataWindow -lDesMac -lGoodPhone -lLG_bus -lMarketBP -lOverDict -lParam -lProdBP -lProdOrderCfm -lPubCheckLoginNo -lPubRuleChk1351 -lQryVpmnInfo -lQueryPubBP -lSendAlertSMS -lSmsParam -laccountBC -lahlocalBC -lbasementBC -lbasementBP -lbgcfg -lbillkt -lbillquery -lbodisp -lborder -lborderappfunc -lborderdisp -lbordererr -lborderexchange -lborderext -lborderfreebill -lborderoffon -lborderqry -lborderrule -lbordertransfer -lbp -lcfg -lcfg10 -lconfig -lcrm2spms -lcustmngBP -lcustomerBC -lcustsvcBP -lcustviewBC -lcustviewBP -ldatamodel -ldatasyn -ldbug -ldes4G -ldto -lentity -lfavquerypub -lfilter -linteractionBC -linterpubfun -llogfunc -llogutype -lmarketBC -lmobil800 -lobossBC -lobossBP -lorderBC -lordersvcBP -lp009Cfm -lp1010Cfm -lp1041Cfm -lp1041Finish -lp1045Cfm -lp1055OrdFinish -lp1100Cfm -lp1100Finish -lp1102Cfm -lp1105Cfm -lp1110Cfm -lp1112Cfm -lp1112Finish -lp1113Cfm -lp1114Cfm -lp1115Cfm -lp1116Cfm -lp1117Cfm -lp1120Bak -lp1120Cfm -lp1120Finish -lp1122Cfm -lp1124Cfm -lp1124Finish -lp1124InterL -lp1124Pub -lp1126Cfm -lp1127Cfm -lp1128Cfm -lp1130Cfm -lp1132Cfm -lp1133Cfm -lp1134Cfm -lp1136Cfm -lp1140Cfm -lp1144Cfm -lp1144Finish -lp1148Cfm -lp1150Cfm -lp1162Cfm -lp1164Cfm -lp1166Cfm -lp1174Cfm -lp1175Cfm -lp1184Finish -lp1212Cfm -lp1220Cfm -lp1220finish -lp1221Cfm -lp1225Cfm -lp1227Cfm -lp1228Cfm -lp1230Cfm -lp1246Cfm -lp1267Cfm -lp1269Cfm -lp1292Cfm -lp1295Cfm -lp1350Cfm -lp1355Cfm -lp1355Finish -lp1356Cfm -lp1356Finish -lp1357Cfm -lp1357Finish -lp1403Cfm -lp1506Cfm -lp1507Cfm -lp1514Cfm -lp1517Cfm -lp1526Cfm -lp1542Cfm -lp1559Cfm -lp1559CfmInter -lp1576Cfm -lp1577Cfm -lp1607Cfm -lp1617Cfm -lp1620Cfm -lp1628Cfm -lp1629Cfm -lp1640Cfm -lp1643Cfm -lp1644Cfm -lp1645Cfm -lp1646Cfm -lp1647Cfm -lp1872Cfm -lp1880CfmOrd -lp1884Cfm -lp1885Cfm -lp1886Cfm -lp1888Cfm -lp1893Cfm -lp1895Cfm -lp1895Finish -lp1898Cfm -lp1922Cfm -lp1932Cfm -lp1933Cfm -lp1935Cfm -lp1938Cfm -lp1940Cfm -lp1941Cfm -lp1943Cfm -lp1944Cfm -lp1949Cfm -lp1956Cfm -lp1959L -lp1971Cfm -lp1972Cfm -lp1973Cfm -lp1977Cfm -lp1978Cfm -lp1979Cfm -lp1981Cfm -lp1982Cfm -lp1984Cfm -lp1989Cfm -lp1995Cfm -lp1996Cfm -lp1997Cfm -lp1998Cfm -lp2003Cfm -lp2006Cfm -lp2022Cfm -lp2038Cfm -lp2062Cfm -lp2104Cfm -lp2105Cfm -lp2106Cfm -lp2107Cfm -lp2108Cfm -lp2109Cfm -lp2112Cfm -lp2113Cfm -lp2114Cfm -lp2120Cfm -lp2143Cfm -lp2205Cfm -lp2206Cfm -lp2207Cfm -lp2238Cfm -lp2276Cfm -lp2301Cfm -lp3708Cfm -lp3717Cfm -lp3718Cfm -lp3727Cfm -lp3792Cfm -lp3794Cfm -lp3825Cfm -lp3825Err -lp3844Cfm -lp3845Cfm -lp3846Cfm -lp3851Cfm -lp3852Cfm -lp3858Cfm -lp3859Cfm -lp3860Cfm -lp3861Cfm -lp3862Cfm -lp3863Cfm -lp3864Cfm -lp3865Cfm -lp3866Cfm -lp3867Cfm -lp3868Cfm -lp3870Cfm -lp3873Cfm -lp3874Cfm -lp3880Cfm -lp3885Cfm -lp3889Cfm -lp3890Cfm -lp3896Cfm -lp3897Cfm -lp3898Cfm -lp3900Cfm -lp3901Cfm -lp3903Cfm -lp3904Cfm -lp3907Cfm -lp3909Cfm -lp3914Cfm -lp3915Cfm -lp3916Cfm -lp3917Cfm -lp3924Cfm -lp3925Cfm -lp3937Cfm -lp3961Cfm -lp3966Fns -lp3969AccCfm -lp3971Cfm -lp3973Cfm -lp3974Cfm -lp3975Cfm -lp3977Cfm -lp3991Cfm -lp3992Cfm -lp3995Cfm -lp3996Cfm -lp3998Cfm -lp3999Cfm -lp4078Cfm -lp4079Cfm -lp4132Cfm -lpAddSlaveRelation -lpAssureProcess -lpChkOBackCfm -lpEsopSXInterAtten -lpEsopSXInterface -lpEsopViewInterFace2 -lpGrpScoreCfm -lpIMsgSend -lpJ605 -lpJ613 -lpJ616 -lpJ622Cfm -lpOrderSvcChkRule -lpPubFavCfm -lpUnSignRelationCfm -lpassutype -lprmmd5 -lproductBC -lpubInterBoss -lpubInterFunc -lpubInterRes -lpubInterWbqd -lpubInterWxwl -lpubShare -lpublog -lrPubFunc -lrouter -lrule -lscoreBP -lservice -lstorder -lsxacctBC -lsxacctBC1 -lsxacctBC2 -lsxacctBC3 -lsxacctBC4 -lsyncustview -ltestbc11 -ltuxadp -ltuxadp10 -luserBC -lutility -lutype -lutype10 -lzlib

CPP=g++ -m64 -g -fPIC
CFLAGS=-D_THREAD_SAFE  -DPLATFORM_TYPE=PLATFORM_TYPE_LINUX -D_USEDCI -D__BIGMSGQUEUE_ENABLED  -DMACHINE_WORD=64 -D_USE_MEMCACHED_
PUBLIB=-L/crmtux1/run/imdb/dci/lib -ldci  -L/crmtux1/run/xerces/lib -lxerces-c -L/tuxedo/tuxedo11gR1/lib -ltux -lbuft -lfml -lfml32 -lengine -L/oracle/app/oracle/product/11.2.0/client/lib -lclntsh

MyTest: MyTest.o
#	$(CPP) -o $@ $? -L/crmtux1/run/solib `./a.sh` $(PUBLIB)
	$(CPP) -o $@ $? -L/crmtux1/run/solib $(LIBS) $(PUBLIB)

MyTest.o: MyTest.cpp
	$(CPP) $(INC) -c -o $@ $?
 */
