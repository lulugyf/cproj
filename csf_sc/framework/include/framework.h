#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_


#include <alloca.h>
#include <utility>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utype.h>
#include <log4c.h>
#include <atmi.h>
#include <userlog.h>
#include <LogFunc.h>
#include <sys/time.h>
using namespace std;



#undef init

//////////////////// oracle occi head
#define OTL_ORA_MAP_STRINGS_TO_CHARZ
//#define OTL_ORA9I // Compile OTL 4/OCI8
#define OTL_ORA11G // Compile OTL 4/OCI8
#include <otlv4.h> // include the OTL 4 header file
#ifdef _USEDCI
#include "dci.h"
#else
typedef struct ___a{int eno;char error[128];} DCI ;
#define DCI_SQL void*
typedef const char** DCI_ROW;
#define dci_init(a) NULL
#define dci_real_connect(a,b,c,d,e,f) NULL
#define dci_set_Buffer_flag(a)
#define dci_set_auto_commit(a,b)
#define dci_prepare_sql(a,b,c) 0
#define dci_quit(a)
#define dci_query_p(a,b) 0
#define dci_fetch_row_s(a,b) NULL
#define dci_end_trans(a,b) 0
#define dci_free_sql(a)
#define dci_bind_param(a,b,c,d,e) 0
#define DCI_TYPE_CHAR 1
#define DCI_TYPE_INT 1

#endif

typedef utype* (*TDoMerge)(map<string, void*>* m, TCtrlInfo* errInfo);
#define GETDB(a) (*((TCtrlInfoEx*)a)->db)
#define GETMDB(a) (((TCtrlInfoEx*)a)->mdb)
#define GETRECONNFLAG(a) (((TCtrlInfoEx*)a)->bReconnFlag)
#define GETMDBLASTCONN(a) (((TCtrlInfoEx*)a)->mdbLastConn)
struct TCtrlInfoEx :TCtrlInfo{
	TCtrlInfoEx(){
		memset(this, 0, sizeof(TCtrlInfoEx));
	}
	otl_connect *db;
	DCI* mdb;
	bool bReconnFlag;
	const utype* input;
	TUtypeFuncPtr func;
	otl_connect *maindb;
	DCI* mainmdb;
	char cliWsnAddr[128];
	time_t mdbLastConn;
};



struct TCfgHandle
{
	map<string, string> cache;
	string sFileName;
	time_t tLastCheck;
	time_t tFilemtime;
	TCfgHandle(const char* file){
		tLastCheck=0;
		tFilemtime=0;
		sFileName=file;
	}
} ;

#ifdef _LVSETENABLE
#define SETLEVEL(a) l4c_lvset(a, NULL)
#else
#define SETLEVEL(a)
#endif



extern "C" char * Ltrim(char * str);
extern "C" char * Rtrim(char * str);
extern "C" char *rtrim(char *src);
extern "C" char* Trim(char *S);
utype* pubEncryptPasswd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubGetLoginAccept(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubGetRandPass(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubGetSysTime(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubModifySql(const utype *inparam, TCtrlInfo *errInfo);
utype* pubQuerySql(const utype *inparam, TCtrlInfo *errInfo);
utype* pubBusiReversal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubRegexExec(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubReadTxtFile(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubTxtSplit(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQryChgDetail(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubBusiRule(const utype* puParamIn, TCtrlInfo* errInfo);
utype* pubServiceNoInfo(const utype* p, TCtrlInfo* errInfo);
int pubServiceNoInfoHashCode(const char* sServAddNum);
utype* pubServAddNum(const utype* p, TCtrlInfo* errInfo);
utype* getRouteInfo(const utype* p, TCtrlInfo* errInfo);
const char* doGetCfgGetStrSlient(const char* maintag, const char* subtag, TCfgHandle& handle);
const char* doGetCfgGetStr(const char* maintag, const char* subtag, TCfgHandle& handle);
const char* cfgGetStr(const char* maintag, const char* subtag);
const char* cfgGetStrSlient(const char* maintag, const char* subtag);
const char* cfgGetCurrentDBPatition();
const char* cfgGetCurrentDBInstance();
string cfgGetCurrentPatitionsLabel(const char* label, string s);
string cfgGetAllPatitionsLabel(const char* label, string s);
string cfgGetFullPath(string s);
void GetFtpCfg(const char* label, string& ip, string&  user, string& passwd, string& path);
void GetDBCfg(const char* lable, string& tns, string&  user, string& passwd, string& bak, string& type);
void desEncrypt(const char *src, char* dst, size_t len);
void desDecrypt(const char *src, char* dst, size_t len);
void LogUtype(const utype *pu, int a);
void LogUtype(const utype *pu);
void LogUtype(const utype *pu, const t_logparam& lp);
utype* doBusiRule(int iRuleId, const utype* puParamIn, TCtrlInfo* errInfo);
utype* doMerge(map<string, void*>* m, TCtrlInfo* errInfo);

//utype* AssiMutiConnWork_old(const utype* in, TCtrlInfo* errInfo, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, const char *psDbLabel, int iConnType);
utype* AssiMutiConnWork_callesb(const char *bpname, const utype* in, TCtrlInfo* errInfo, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, const char *psDbLabel, int iConnType);
#define AssiMutiConnWork(uin, errinfo, bpfunc, mergfunc, dblabel, conntype) \
		AssiMutiConnWork_callesb(#bpfunc, uin, errinfo, bpfunc, mergfunc, dblabel, conntype)

int tuxinit(int argc, char *argv[], const char *psDbLabel, const char *psTuxServerName, int iFlags);
void tuxdone(const char *psDbLabel, int iFlags);
int tuxacal(char* psServiceName, const utype *pu, long flag=TPNOREPLY);
utype * tuxcal(char* psServiceName, const utype *pu, long flag=0, const char* ip=NULL, unsigned short port=0);
void tuxtst(const char* psServiceName, TPSVCINFO *transb, TUtypeFuncPtr ptUtypeFuncPtr=NULL);
/* void tuxadp(  const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType); */
/* void tuxadpEx(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType); */
/* void tuxadp1( const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType); */


/********************added by LPC for stop mem leak**********************/

void TUXADP(  const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType);
void TUXADPEX(const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, int iConnType);
void TUXADP1( const char *psServiceName, TPSVCINFO *transb, const char *psDbLabel, const char *psUtypeFunc, TUtypeFuncPtr ptUtypeFuncPtr, int iConnType);

#define tuxadp(psServiceName, transb, psDbLabel, psUtypeFunc, ptUtypeFuncPtr, iConnType)	\
	{ \
		char ssss[128];	\
		memset(ssss, 0, sizeof(ssss)); \
		strcpy(ssss, psDbLabel);  \
		TUXADP(psServiceName, transb, ssss, psUtypeFunc, ptUtypeFuncPtr, iConnType); \
	}

#define tuxadpEx(psServiceName, transb, psDbLabel, psUtypeFunc,  ptUtypeFuncPtr,  ptDoMerge,  iConnType)	\
	{ \
		char ssss[128];	\
		memset(ssss, 0, sizeof(ssss)); \
		strcpy(ssss, psDbLabel);  \
		TUXADPEX(psServiceName, transb, psDbLabel, psUtypeFunc,  ptUtypeFuncPtr,  ptDoMerge,  iConnType); \
	}

#define tuxadp1(psServiceName, transb, psDbLabel, psUtypeFunc, ptUtypeFuncPtr, iConnType)	\
	{ \
		char ssss[128];	\
		memset(ssss, 0, sizeof(ssss)); \
		strcpy(ssss, psDbLabel);  \
		TUXADP1(psServiceName, transb, ssss, psUtypeFunc, ptUtypeFuncPtr, iConnType); \
	}


/********************added by LPC for stop mem leak**********************/






class db_connect{
	private:
		DCI_SQL dsql;
		DCI* pdci;
		otl_connect* potl;
		DCI dci;
		otl_connect otl;
		time_t lastConn;
		time_t lastTry;
		bool isMainConn;
		string mainName;
		string mainUser;
		string mainPass;
		string mainType;
		string bakName;
		string bakUser;
		string bakPass;
		string bakType;
		string lable;
		bool hasInitPrepare;
		bool isActive;
		bool stuff();
	public:
		void init(const char* lab);

		void setActive(bool is);
		bool getActive();
		time_t getLastConnectTime();
		db_connect(const char* lab);
		db_connect();
		const char* getCurType();
		const char* getConnectLable();
		otl_connect& getOtlHandle();
		DCI& getMDBHandle();
		void doConnect();

		void doClose();
		bool tryConnect();
		void doCommit();
		void doRollback();
		~db_connect();
};


typedef void* (*work_f)(void* v1, db_connect* pdb, bool isLong);
class db_factory{
	private:
		map<string, db_connect*> dbmap;
		map<string, bool> maskmap;
		bool isLong;
	public:
		db_factory(bool is);
		db_factory();
		db_connect* getConnect(const char* lable);
		void setShortLong(bool is);
		void addConnect(const char* lable, bool isWork);
		void setActive(const char* lablestr);
		void resetActive();
		db_connect* addConnect(const char* lablestr);
		bool doBegin();


		void doCall(map<string, void*>& m, work_f func, void* v1);
		void doEnd(bool isCommit);
		~db_factory();
};


utype* __CALLBP(TUtypeFuncPtr bpfunc, const char *bpname, const utype *uInParam, TCtrlInfo *ctrlInfo);
#define CALLBP(bpname, uInParam, ctrlInfo) __CALLBP(bpname, #bpname, uInParam, ctrlInfo)


#endif
