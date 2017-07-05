#ifndef _FRAMEWORK1_H_
#define _FRAMEWORK1_H_


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

using namespace std;

//////////////////// oracle occi head
#ifndef OTL_ORA11G  // avoid dulplicated include otlv4.h
 #define OTL_ORA_MAP_STRINGS_TO_CHARZ
 //#define OTL_ORA9I // Compile OTL 4/OCI8
 #define OTL_ORA11G // Compile OTL 4/OCI8
 #include <otlv4.h> // include the OTL 4 header file
#endif

class db_connect1{
	private:
		otl_connect* potl;
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
		
		void init(const char* lab1);
		
		void setActive(bool is);
		bool getActive();
		time_t getLastConnectTime();
		db_connect1(const char* lab);
		db_connect1();
		const char* getCurType();
		const char* getConnectLable();
		otl_connect& getOtlHandle();
		void doConnect();

		void doClose();
		bool tryConnect();
		void doCommit();
		void doRollback();
		~db_connect1();
};

typedef void* (*work_f1)(void* v1, db_connect1* pdb, bool isLong);
class db_factory1{
	private:
		map<string, db_connect1*> dbmap;
		map<string, bool> maskmap;
		bool isLong;
	public:
		db_factory1(bool is);
		db_factory1();
		db_connect1* getConnect(const char* lable);
		void setShortLong(bool is);
		void addConnect(const char* lable, bool isWork);
		void setActive(const char* lablestr);
		void resetActive();
		db_connect1* addConnect(const char* lablestr);
		bool doBegin();
		

		void doCall(map<string, void*>& m, work_f1 func, void* v1) ;
		void doEnd(bool isCommit);
		~db_factory1();
};

#endif
