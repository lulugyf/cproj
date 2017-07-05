
#include "framework1.h"

void GetDBCfg(const char* lable, string& tns, string&  user, string& passwd, string& bak, string& type);


bool db_connect1::stuff(){
	string bakLable, bbl;
	mainName="";
	mainUser="";
	mainPass="";
	bakName="";
	bakUser="";
	bakPass="";
	GetDBCfg(lable.c_str(), mainName, mainUser, mainPass, bakLable, mainType);
	if(bakLable=="") return false;

	GetDBCfg(bakLable.c_str(), bakName, bakUser, bakPass, bbl, bakType);
	if(mainType!=bakType) throw(appException(306001003, "�����ļ��е����ݿ������������ͳ�ͻ"));
	return true;
}		



//class db_connect1{
void db_connect1::init(const char* lab){
	mainType="";
	isMainConn=true;
	hasInitPrepare=false;
	potl=&otl;
	isActive=false;
	this->lable=lab;
	stuff();
}
		
void db_connect1::setActive(bool is){
	isActive=is;
}
bool db_connect1::getActive(){
	return isActive;
}
time_t db_connect1::getLastConnectTime(){
	return 	lastConn;
}
db_connect1::db_connect1(const char* lab){
	init(lab);
}
db_connect1::db_connect1(){
}
const char* db_connect1::getCurType(){
	return mainType.c_str();
}
const char* db_connect1::getConnectLable(){
	return lable.c_str();
}
otl_connect& db_connect1::getOtlHandle(){
	return otl;
}
void db_connect1::doConnect(){
	bool hasBak=stuff();
	isMainConn=true;
	if(mainType=="ORACLE"){
		try{
			char sqlstr[1024];
			sprintf(sqlstr,"%s/%s@%s",mainUser.c_str(),mainPass.c_str(),mainName.c_str());
			L4C_TRACE("---- [%s]", sqlstr);
			potl->rlogon(sqlstr);
		}catch(otl_exception& p){
			if(p.code==32031) return;
			if(!hasBak) throw(p);
			L4C_WARN("ORACLE�����ݿ�����ʧ�ܣ��������ӱ������ݿ�");
			try{
				char sqlstr[1024];
				sprintf(sqlstr,"%s/%s@%s",bakUser.c_str(),bakPass.c_str(),bakName.c_str());
				potl->rlogon(sqlstr);
				isMainConn=false;
			}catch(otl_exception& p2){
				throw(p);	
			}	
		}
	}else
		throw(appException(306*1001000+2, "δ֪���ݿ�����"));
		
	lastConn=time(NULL);
}

void db_connect1::doClose(){
	if(mainType=="ORACLE"){
		try{
			potl->logoff();
		}catch(...){
			
		}
	}
}
bool db_connect1::tryConnect(){
	if(time(NULL)-lastConn>120&&!isMainConn){
		L4C_TRACE("Ŀǰ��ʹ�ñ������ݿ����ӣ����³��������ݿ�����");
		doClose();
		doConnect();
		return false;
	}else{
		time_t now=time(NULL);
		if(mainType=="ORACLE"){
			try
			{
				int val;
				otl_nocommit_stream getParam(1,"select 1 from dual",*potl);

				if(!getParam.eof())
				{
					L4C_TRACE("ORACLE���ݿ���������");
					getParam >> val;
					return true;
				}
				L4C_TRACE("ORACLE���ݿ��������쳣��dual��������");
				
			}catch (otl_exception& p)
			{
				L4C_TRACE("����ORACLE���ݿ�����ʧ�ܣ�%s : %s : %s",p.msg,p.stm_text,p.var_info);
			}
			lastTry=now;
			potl->logoff(); ////////by guanyf, 20130123 �Ĵ�crm5.7�����������⣬ ��⵽�����쳣�� û�йر�ֱ���������ӵ����쳣
			// by guanyf 20170705 ɽ�������ݿ��������ϵ�������ʧ��
			L4C_WARN("ORACLE���ݿ����ӶϿ����������ݿ�");
		}else
			throw(appException(306*1001000+2, "δ֪���ݿ�����"));

		
		doConnect();
		return false;
	}
}
void db_connect1::doCommit(){
	if(mainType=="ORACLE"){
		potl->commit();
	}
}
void db_connect1::doRollback(){
	if(mainType=="ORACLE"){
		potl->rollback();
	}
}
db_connect1::~db_connect1(){
	doClose();
}
//};



//class db_factory1{

		db_factory1::db_factory1(bool is){
			this->isLong=is;
		}
		db_factory1::db_factory1(){
			db_factory1(false);
		}
		db_connect1* db_factory1::getConnect(const char* lable){
			return dbmap[lable];
		}
		void db_factory1::setShortLong(bool is){
			this->isLong=is;
		}
		void db_factory1::addConnect(const char* lable, bool isWork){		
			db_connect1* dbconn=NULL;	
			if(dbmap.find(lable)==dbmap.end()){
				dbconn=new db_connect1(lable);
				dbmap.insert(map<string, db_connect1*>::value_type(lable, dbconn));
				maskmap.insert(map<string, bool>::value_type(lable, !isWork));
			}
		}
		void db_factory1::setActive(const char* lablestr){
			char* tar=(char*)alloca(strlen(lablestr)+1);
			strcpy(tar, lablestr);
			char* slable=tar;
			while(1){
				char* st=strchr(slable, ',');
				if(st!=NULL){
					char* sn=st+1;
					*st=0;
					getConnect(slable)->setActive(true);
					slable=sn;
				}else{
					getConnect(slable)->setActive(true);
					break;
				}
			}
		}
		void db_factory1::resetActive(){
			map<string, db_connect1*>::iterator iter;
			for(iter=dbmap.begin();iter!=dbmap.end();iter++){
				db_connect1* pdc=iter->second;
				pdc->setActive(false);
			}
		}
		db_connect1* db_factory1::addConnect(const char* lablestr){		
			char* tar=(char*)alloca(strlen(lablestr)+1);
			strcpy(tar, lablestr);
			char* slable=tar;
			while(1){
				char* st=strchr(slable, ',');
				if(st!=NULL){
					char* sn=st+1;
					*st=0;
					addConnect(slable, true);
					slable=sn;
				}else{
					addConnect(slable, true);
					break;
				}
			}
			return dbmap[tar];
		}
		bool db_factory1::doBegin(){
			map<string, db_connect1*>::iterator iter;
			bool isReconnect=false;
			for(iter=dbmap.begin();iter!=dbmap.end();iter++){
				db_connect1* pdc=iter->second;
				if(!pdc->getActive()) continue;
				if(isLong){
					if(!pdc->tryConnect()) isReconnect=true;
				}else{
					pdc->doConnect();
					isReconnect=true;
				}
				
			}
			return isReconnect;
		}
		

		void db_factory1::doCall(map<string, void*>& m, work_f1 func, void* v1) {
			map<string, db_connect1*>::iterator iter;
			m.empty();
			for(iter=dbmap.begin();iter!=dbmap.end();iter++){
				db_connect1* pdc=iter->second;
				bool isReconnect=true;
				if(!pdc->getActive()) continue;
				if(maskmap[iter->first]) continue;
				void* p=func(v1, pdc, isLong);
				m.insert(map<string, void*>::value_type(iter->first, p));	
			}
		}
		void db_factory1::doEnd(bool isCommit){
			map<string, db_connect1*>::iterator iter;
			for(iter=dbmap.begin();iter!=dbmap.end();iter++){
				db_connect1* pdc=iter->second;
				if(!pdc->getActive()) continue;
				if(isCommit)
					pdc->doCommit();
				else
					pdc->doRollback();
				if(!isLong)
					pdc->doClose();
			}
		}
		db_factory1::~db_factory1(){
			map<string, db_connect1*>::iterator iter;
			for(iter=dbmap.begin();iter!=dbmap.end();iter++){
				db_connect1* pdc=iter->second;
				delete pdc;
			}
			dbmap.empty();
		}
//};

