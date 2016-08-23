#include "dbconn.h"

// private functions
bool multi_db_connect::stuff(){
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

// public functions
void multi_db_connect::setActive(bool is){
	isActive=is;
}
bool multi_db_connect::getActive(){
	return isActive;
}
time_t multi_db_connect::getLastConnectTime(){
	return 	lastConn;
}
multi_db_connect::multi_db_connect(const char* lab){
	init(lab);
}
multi_db_connect::multi_db_connect(){
}
const char* multi_db_connect::getCurType(){
	return mainType.c_str();
}
const char* multi_db_connect::getConnectLable(){
	return lable.c_str();
}
otl_connect& multi_db_connect::getOtlHandle(){
	return otl;
}
DCI& multi_db_connect::getMDBHandle(){
	return dci;
}

void multi_db_connect::init(const char* lab){
	mainType="";
	isMainConn=true;
	hasInitPrepare=false;
	pdci=&dci;
	potl=&otl;
	isActive=false;
	this->lable=lab;
	stuff();
	if(mainType=="MDB")
		dci_init(pdci);
}


void multi_db_connect::doConnect(){
	bool hasBak=stuff();
	isMainConn=true;
	if(mainType=="ORACLE"){
		try{
			char sqlstr[1024];
			sprintf(sqlstr,"%s/%s@%s",mainUser.c_str(),mainPass.c_str(),mainName.c_str());
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
	}else if (mainType=="MDB"){
		hasInitPrepare=false;

		if(dci_real_connect(pdci,NULL, mainUser.c_str(), mainPass.c_str(),mainName.c_str(), 0)!=NULL){
			dci_set_Buffer_flag(pdci);
			dci_set_auto_commit(pdci, 0);
		}else{
			int ecode=pdci->eno;
			string errmsg=pdci->error;
			if(hasBak){
				L4C_WARN("���ڴ����ݿ�����ʧ�ܣ��������ӱ������ݿ�");
				if(dci_real_connect(pdci,NULL, bakUser.c_str(), bakPass.c_str(),bakName.c_str(), 0)!=NULL){
					dci_set_Buffer_flag(pdci);
					dci_set_auto_commit(pdci, 0);
					isMainConn=false;
				}else
					throw(appException(305*1000000+100000+pdci->eno, pdci->error));
			}
			else
				throw(appException(305*1000000+100000+pdci->eno, pdci->error));

		}
		if(!hasInitPrepare){
			if(dci_prepare_sql(pdci, &dsql, "select 1 from dual")!=0){
				throw(appException(305*1000000+100000+pdci->eno, pdci->error));
			}
		}
		hasInitPrepare=true;
	}else
		throw(appException(306*1001000+2, "δ֪���ݿ�����"));

	lastConn=time(NULL);
}

void multi_db_connect::doClose(){
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
bool multi_db_connect::tryConnect(){
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
			L4C_WARN("ORACLE���ݿ����ӶϿ����������ݿ�");
		}else if(mainType=="MDB"){
			if(hasInitPrepare){
				if(dci_query_p(pdci, &dsql)==0){
					L4C_TRACE("�ڴ����ݿ���������");
					DCI_ROW v_row = dci_fetch_row_s(pdci, &dsql);
					return true;
				}else{
					L4C_TRACE("�����ڴ����ݿ�����ʧ�ܣ�%s",pdci->error);
				}
			}
			if(now-lastTry<120&&now-lastTry>=0){
				L4C_WARN("�ڴ����ݿ����ӶϿ�������δ�ﵽ��ʱʱ�䣬�ݲ������ڴ����ݿ�");
				throw(appException(306*1001000+3, "�ڴ����ݿ����ӶϿ�������δ�ﵽ��ʱʱ�䣬�ݲ������ڴ����ݿ�"));
			}
			lastTry=now;
			L4C_WARN("�ڴ����ݿ����ӶϿ��������ڴ����ݿ�");
		}else
			throw(appException(306*1001000+2, "δ֪���ݿ�����"));


		doConnect();
		return false;
	}
}
void multi_db_connect::doCommit(){
	if(mainType=="ORACLE"){
		potl->commit();
	}else if(mainType=="MDB"){
		if(hasInitPrepare)
			dci_end_trans(pdci, 1);
	}
}
void multi_db_connect::doRollback(){
	if(mainType=="ORACLE"){
		potl->rollback();
	}else if(mainType=="MDB"){
		if(hasInitPrepare)
			dci_end_trans(pdci, 0);
	}
}
multi_db_connect::~multi_db_connect(){
	doClose();
	dci_free_sql(&dsql);
}




multi_db_factory::multi_db_factory(bool is){
	this->isLong=is;
}
multi_db_factory::multi_db_factory(){
	multi_db_factory(false);
}
multi_db_connect* multi_db_factory::getConnect(const char* lable){
	return dbmap[lable];
}
void multi_db_factory::setShortLong(bool is){
	this->isLong=is;
}
void multi_db_factory::addConnect(const char* lable, bool isWork){
	multi_db_connect* dbconn=NULL;
	if(dbmap.find(lable)==dbmap.end()){
		dbconn=new multi_db_connect(lable);
		dbmap.insert(map<string, multi_db_connect*>::value_type(lable, dbconn));
		maskmap.insert(map<string, bool>::value_type(lable, !isWork));
	}
}
void multi_db_factory::setActive(const char* lablestr){
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
void multi_db_factory::resetActive(){
	map<string, multi_db_connect*>::iterator iter;
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		multi_db_connect* pdc=iter->second;
		pdc->setActive(false);
	}
}
multi_db_connect* multi_db_factory::addConnect(const char* lablestr){
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

#include <signal.h>
#include <unistd.h>
static int is_timeout;
void sig_func(int sig){
    is_timeout = 1;
}
bool multi_db_factory::doBegin(){
	map<string, multi_db_connect*>::iterator iter;
	bool isReconnect=false;
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		multi_db_connect* pdc=iter->second;
		if(!pdc->getActive()) continue;

        signal(SIGALRM, sig_func);
        is_timeout = 0;
        alarm(5); //5����Ϊ���ӳ�ʱʱ��
		if(isLong){
            try{
			    if(!pdc->tryConnect())
                    isReconnect=true;
            }catch(...){
                pdc->setActive(false);
            }
		}else{
            try{
			    pdc->doConnect();
            }catch(...){
                pdc->setActive(false);
            }
			isReconnect=true;
		}
        alarm(0);
        if(is_timeout == 1){
            // ���ӳ�ʱ���ж�, ���Ը�����
            pdc->setActive(false);
        }

	}
	return isReconnect;
}


void multi_db_factory::doCall(map<string, void*>& m, work_f func, void* v1) {
	map<string, multi_db_connect*>::iterator iter;
	m.empty();
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		multi_db_connect* pdc=iter->second;
		bool isReconnect=true;
		if(!pdc->getActive()) continue;
		if(maskmap[iter->first]) continue;
		void* p=func(v1, pdc, isLong);
		m.insert(map<string, void*>::value_type(iter->first, p));
	}
}
void multi_db_factory::doEnd(bool isCommit){
	map<string, multi_db_connect*>::iterator iter;
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		multi_db_connect* pdc=iter->second;
		if(!pdc->getActive()) continue;
		if(isCommit)
			pdc->doCommit();
		else
			pdc->doRollback();
		if(!isLong)
			pdc->doClose();
	}
}
multi_db_factory::~multi_db_factory(){
	map<string, multi_db_connect*>::iterator iter;
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		multi_db_connect* pdc=iter->second;
		delete pdc;
	}
	dbmap.empty();
}




