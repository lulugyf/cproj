#include <framework.h>

// private functions
bool db_connect::stuff(){
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
void db_connect::setActive(bool is){
	isActive=is;
}
bool db_connect::getActive(){
	return isActive;
}
time_t db_connect::getLastConnectTime(){
	return 	lastConn;
}
db_connect::db_connect(const char* lab){
	init(lab);
}
db_connect::db_connect(){
}
const char* db_connect::getCurType(){
	return mainType.c_str();
}
const char* db_connect::getConnectLable(){
	return lable.c_str();
}
otl_connect& db_connect::getOtlHandle(){
	return otl;
}
DCI& db_connect::getMDBHandle(){
	return dci;
}

void db_connect::init(const char* lab){
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


void db_connect::doConnect(){
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

void db_connect::doClose(){
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
bool db_connect::tryConnect(){
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
void db_connect::doCommit(){
	if(mainType=="ORACLE"){
		potl->commit();
	}else if(mainType=="MDB"){
		if(hasInitPrepare)
			dci_end_trans(pdci, 1);
	}
}
void db_connect::doRollback(){
	if(mainType=="ORACLE"){
		potl->rollback();
	}else if(mainType=="MDB"){
		if(hasInitPrepare)
			dci_end_trans(pdci, 0);
	}
}
db_connect::~db_connect(){
	doClose();
	dci_free_sql(&dsql);
}




db_factory::db_factory(bool is){
	this->isLong=is;
}
db_factory::db_factory(){
	db_factory(false);
}
db_connect* db_factory::getConnect(const char* lable){
	return dbmap[lable];
}
void db_factory::setShortLong(bool is){
	this->isLong=is;
}
void db_factory::addConnect(const char* lable, bool isWork){
	db_connect* dbconn=NULL;
	if(dbmap.find(lable)==dbmap.end()){
		dbconn=new db_connect(lable);
		dbmap.insert(map<string, db_connect*>::value_type(lable, dbconn));
		maskmap.insert(map<string, bool>::value_type(lable, !isWork));
	}
}
void db_factory::setActive(const char* lablestr){
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
void db_factory::resetActive(){
	map<string, db_connect*>::iterator iter;
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		db_connect* pdc=iter->second;
		pdc->setActive(false);
	}
}
db_connect* db_factory::addConnect(const char* lablestr){
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
bool db_factory::doBegin(){
	map<string, db_connect*>::iterator iter;
	bool isReconnect=false;
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		db_connect* pdc=iter->second;
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


void db_factory::doCall(map<string, void*>& m, work_f func, void* v1) {
	map<string, db_connect*>::iterator iter;
	m.empty();
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		db_connect* pdc=iter->second;
		bool isReconnect=true;
		if(!pdc->getActive()) continue;
		if(maskmap[iter->first]) continue;
		void* p=func(v1, pdc, isLong);
		m.insert(map<string, void*>::value_type(iter->first, p));
	}
}
void db_factory::doEnd(bool isCommit){
	map<string, db_connect*>::iterator iter;
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		db_connect* pdc=iter->second;
		if(!pdc->getActive()) continue;
		if(isCommit)
			pdc->doCommit();
		else
			pdc->doRollback();
		if(!isLong || getenv("CSF_FORCE_SHORT_DBCONN") != NULL)  //����������������� ��ǿ��ȫ��ʹ�ö����� 2015-9-10
			pdc->doClose();
	}
}
db_factory::~db_factory(){
	map<string, db_connect*>::iterator iter;
	for(iter=dbmap.begin();iter!=dbmap.end();iter++){
		db_connect* pdc=iter->second;
		delete pdc;
	}
	dbmap.empty();
}





