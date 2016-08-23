#ifndef __PUB_H__
#define __PUB_H__

#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utype.h>
#include <log4c.h>
using namespace std;

#undef init

//////////////////// oracle occi head
#define OTL_ORA_MAP_STRINGS_TO_CHARZ
#define OTL_ORA9I // Compile OTL 4/OCI8
#include <otlv4.h> // include the OTL 4 header file
#include "dci.h"

#define GETDB(a) (*((TCtrlInfoEx*)a)->db)
#define GETMDB(a) (((TCtrlInfoEx*)a)->mdb)
#define GETRECONNFLAG(a) (((TCtrlInfoEx*)a)->bReconnFlag)
struct TCtrlInfoEx :TCtrlInfo{
	otl_connect *db;
	DCI* mdb;
	bool bReconnFlag;
	const utype* input;
	TUtypeFuncPtr func;
	otl_connect *maindb;
	DCI* mainmdb;
};
const char* cfgGetStr(const char* maintag, const char* subtag);
class db_connect{
	private:
		DCI_SQL dsql;
		DCI* pdci;
		otl_connect* potl;
		DCI dci;
		otl_connect otl;
		time_t lastConn;
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
		void getcfg(string& n1, const char* n2, string&s){
			s=cfgGetStr(n1.c_str(), n2);
			if(s=="") throw(appException(306*1000000+111, "配置项为空"));
		}
		bool stuff(){
			string bakLable;
			mainName="";
			mainUser="";
			mainPass="";
			bakName="";
			bakUser="";
			bakPass="";
			getcfg(lable, "ConnectName", mainName);
			getcfg(lable, "UserName", mainUser);
			getcfg(lable, "UserPass", mainPass);
			getcfg(lable, "DatabaseType", mainType);
			try{
				getcfg(lable, "BackupConnect", bakLable);
			}
			catch(...){
				return false;
			}
			getcfg(bakLable, "ConnectName", bakName);
			getcfg(bakLable, "UserName", bakUser);
			getcfg(bakLable, "UserPass", bakPass);
			getcfg(bakLable, "DatabaseType", bakType);
			if(mainType!=bakType) throw(appException(306*1001000+3, "配置项冲突"));
			return true;
		}		
	public:
		db_connect(const char* lable){
			mainType="";
			isMainConn=true;
			hasInitPrepare=false;
			pdci=&dci;
			potl=&otl;
			this->lable=lable;
			stuff();
		}
		const char* getCurType(){
			return mainType.c_str();
		}
		const char* getConnectLable(){
			return lable.c_str();
		}
		otl_connect& getOtlHandle(){
			return otl;
		}
		DCI& getMDBHandle(){
			return dci;
		}
		void doConnect(){
			bool hasBak=stuff();
			isMainConn=true;
			if(mainType=="ORACLE"){
				try{
					char sqlstr[1024];
					sprintf(sqlstr,"%s/%s@%s",mainUser.c_str(),mainPass.c_str(),mainName.c_str());
					potl->rlogon(sqlstr);
				}catch(otl_exception& p){
					if(!hasBak) throw(p);
					try{
						char sqlstr[1024];
						sprintf(sqlstr,"%s/%s@%s",bakUser.c_str(),bakPass.c_str(),bakName.c_str());
						potl->rlogon(sqlstr);
						isMainConn=false;
					}catch(otl_exception& p2){
						throw(p);	
					}	
				}
			}else if (mainType=="MDB"){
				dci_init(pdci);
				if(dci_real_connect(pdci,NULL, mainUser.c_str(), mainPass.c_str(),mainName.c_str(), 0)!=NULL){
					dci_set_Buffer_flag(pdci);  
					dci_set_auto_commit(pdci, 0);
				}else{
					int ecode=pdci->eno;
					string errmsg=pdci->error;
					if(hasBak){
						if(dci_real_connect(pdci,NULL, bakUser.c_str(), bakPass.c_str(),bakName.c_str(), 0)!=NULL){
							dci_set_Buffer_flag(pdci);  
							dci_set_auto_commit(pdci, 0);
						}else
							throw(appException(305*1000000+100000+pdci->eno, pdci->error));
					}
					else
						throw(appException(305*1000000+100000+pdci->eno, pdci->error));
					if(!hasInitPrepare){
						if(dci_prepare_sql(pdci, &dsql, "select 1 from dual")!=0){
							throw(appException(305*1000000+100000+pdci->eno, pdci->error));
						}
					}
					hasInitPrepare=true;
				}
			}else
				throw(appException(306*1001000+2, "未知数据库类型"));
				
			lastConn=time(NULL);
		}

		void doClose(){
			if(mainType=="ORACLE"){
				try{
					potl->logoff();
				}catch(...){
					
				}
			}else if(mainType=="MDB"){
				hasInitPrepare=false;
				dci_quit(pdci);
			}
		}
		bool tryConnect(){
			if(time(NULL)-lastConn>60&&!isMainConn){
				doClose();
				doConnect();
				return false;
			}else{
				if(mainType=="ORACLE"){
					try
					{
						int val;
						otl_nocommit_stream getParam;
						getParam.set_flush(false);
						getParam.open(1,"select 1 from dual",*potl);
						getParam.flush();
						if(!getParam.eof())
						{
							getParam >> val;
							return true;
						}
					}catch (...)
					{
					}
				}else if(mainType=="MDB"){
					if(hasInitPrepare){
						if(dci_query_p(pdci, &dsql)==0){
							DCI_ROW v_row = dci_fetch_row_s(pdci, &dsql);
							return true;
						}		
					}
				}else
					throw(appException(306*1001000+2, "未知数据库类型"));

				doConnect();
				return false;
			}
		}
		void doCommit(){
			if(mainType=="ORACLE"){
				potl->commit();
			}else if(mainType=="MDB"){
				dci_end_trans(pdci, 1);
			}
		}
		void doRollback(){
			if(mainType=="ORACLE"){
				potl->rollback();
			}else if(mainType=="MDB"){
				dci_end_trans(pdci, 0);
			}
		}
		~db_connect(){
			doClose();
			dci_free_sql(&dsql);
		}
};


typedef void* (*work_f)(void* v1, db_connect* pdb, bool isLong);
class db_factory{
	private:
		map<string, db_connect*> dbmap;
		map<string, bool> maskmap;
		bool isLong;
	public:
		db_factory(bool isLong){
			this->isLong=isLong;
		}
		db_factory(){
			db_factory(false);
		}
		setShortLong(bool isLong){
			this->isLong=isLong;
		}
		bool addConnect(const char* lable, bool isWork=true){		
			db_connect* dbconn=NULL;	
			if(dbmap.find(lable)==dbmap.end()){
				dbconn=new db_connect(lable);
				dbmap.insert(map<string, db_connect*>::value_type(lable, dbconn));
				maskmap.insert(map<string, bool>::value_type(lable, !isWork));
			}
		}
		bool doBegin(){
			map<string, db_connect*>::iterator iter;
			bool isReconnect=false;
			for(iter=dbmap.begin();iter!=dbmap.end();iter++){
				db_connect* pdc=iter->second;
				if(isLong){
					if(!pdc->tryConnect()) isReconnect=true;
				}else{
					pdc->doConnect();
					isReconnect=true;
				}
				
			}
			return isReconnect;
		}
		
		db_connect* getConnect(const char* lable){
			return dbmap[lable];
		}
		void doCall(map<string, void*>& m, work_f func, void* v1) {
			map<string, db_connect*>::iterator iter;
			m.empty();
			for(iter=dbmap.begin();iter!=dbmap.end();iter++){
				bool isReconnect=true;
				if(maskmap[iter->first]) continue;
				db_connect* pdc=iter->second;
				void* p=func(v1, pdc, isLong);
				m.insert(map<string, void*>::value_type(iter->first, p));	
			}
		}
		void doEnd(bool isCommit){
			map<string, db_connect*>::iterator iter;
			for(iter=dbmap.begin();iter!=dbmap.end();iter++){
				db_connect* pdc=iter->second;
				if(isCommit)
					pdc->doCommit();
				else
					pdc->doRollback();
				if(!isLong)
					pdc->doClose();
			}
		}
		~db_factory(){
			map<string, db_connect*>::iterator iter;
			for(iter=dbmap.begin();iter!=dbmap.end();iter++){
				db_connect* pdc=iter->second;
				delete pdc;
			}
			dbmap.empty();
		}
};

#define LONG_CONN_TYPE 1
#define SHORT_CONN_TYPE 0

/*序列号类型定义*/
#define SEQ_CART_ID			1
#define SEQ_ORDER_ID		2
#define SEQ_ORDER_LINE_ID	3
#define SEQ_ORDER_CHG		4
#define SEQ_ORDER_LINE_CHG	5
#define SEQ_LOGIN_ACCEPT	6
#define SEQ_CUST_ID			7
#define SEQ_USER_ID			8
#define SEQ_CONTRACT_NO		9
#define SEQ_ORDER_LINE_SLA	10
#define SEQ_ORDER_LINE_BOOK	11
#define SEQ_ORDER_LINE_EXCP	12
#define SEQ_ORDER_LINE_EXEC	17
#define SEQ_UR_BILLMODE		6       /*13 付费模式序列*/
#define SEQ_UR_USERSTATE	6       /*14 用户状态序列*/
#define SEQ_CT_CONTACTID	6       /*15 客户联系信息*/
#define SEQ_UR_ADDNBRID		6       /*16 接入号标识  */

#define SEQ_CT_UNITID		1       /*18 集团编码  */
#define SEQ_CT_GRPDEPTID	6       /*19 集团部门标识  */
#define SEQ_CT_ADDRESSNO	6       /*20 集团通信录编码  */
#define SEQ_AC_ACCTID		6       /*21 账务标识序列*/
#define SEQ_CT_CUSTRELID	6       /*22 客户关系标识  */
#define SEQ_CT_CONTACTID	6       /*23 联系标识  */
#define SEQ_CT_SPCDAYNO	    6       /*24 关键日期标识  */

#define SEQ_PD_PRODPRCINSID	13	/*产品资费实例序列*/
#define SEQ_PD_SVCINSID		18	/*服务实例序列*/
#define SEQ_UR_TEAMID  		14	/*组实例序列*/
#define SEQ_UR_GROUPID	 	15 	/*群实例序列*/
#define SEQ_UR_MEMBERID	 	16	/*成员实例序列*/
#define SEQ_UT_CUSTREL	 	6	/*客户关系序列*/
#define SEQ_UR_AGREEMENT	6	/*合同编码*/
#define SEQ_OR_PREORDER	  6	  /*预订单流水-yangsong*/
#define SEQ_EVERY_PAGE	  10	  /*每页显示的记录数*/

#define FINISH_FLAG         "N"        	/*生效状态*/
#define EXP_DATE            "20991231" 	/*失效时间*/
#define MAX_BILL_ORDER      99999999	/*默认账户销账优先级*/
#define FILE_PATH      "/crmnga/run/framework/src/custmng/server/RGetExtFields/ExtTxt/"	/*文件的存放路径*/

#endif

