#include <alloca.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "framework.h"



string cfgGetFullPath(string s)
{
	string path=getenv("HOME");
	if(s=="") return  s;	
	if(s.c_str()[0]!='/') 
		s=path+"/"+s;
	return s;
}



const char* cfgGetCurrentDBPatition()
{
	return (cfgGetStrSlient("MAIN", "DBPARTITION"));
}
const char* cfgGetCurrentDBInstance()
{
	const char* s=cfgGetCurrentDBPatition();
	if(s[0]==0)
		return "";
	else return s+1;
}
string cfgGetCurrentPatitionsLabel(const char* label, string s)
{
	s="";
	return (s=s+label+cfgGetCurrentDBPatition());
}
string cfgGetAllPatitionsLabel(const char* label, string s)
{
	s="";
	const char* sIns=cfgGetCurrentDBInstance();
	const char* sLin=cfgGetStrSlient("MAIN", "ALLDBPATITIONS");
	if(sLin[0]==0) return s=cfgGetCurrentPatitionsLabel(label,s);
	char* tar=(char*)alloca(strlen(sLin)+1);
	strcpy(tar, sLin);
	char* sDB=tar;
	while(1){
		char* st=strchr(sDB, ',');
		if(st!=NULL){
			char* sn=st+1;
			*st=0;
			s=s+label+sDB+sIns+",";
			sDB=sn;
		}else{
			s=s+label+sDB+sIns;
			break;
		}
	}
	return s;
}





TCfgHandle crmcfg(getenv("CRM_CFG")!=NULL?getenv("CRM_CFG"):(string(getenv("HOME"))+"/run/cfg/crm.cfg").c_str());
TCfgHandle pwdcfg(cfgGetFullPath(string(doGetCfgGetStrSlient("MAIN", "PWDCFG", crmcfg))).c_str());

extern "C" void desdec(const char *src, char* dst, size_t len);
extern "C" void desenc(const char *src, char* dst, size_t len);


const char* doGetCfgGetStr(const char* maintag, const char* subtag, TCfgHandle& handle)
{
	char sTag[1024]="";
	char sValue[1024];
	time_t now=time(NULL);
	if(now-handle.tLastCheck>=60){
		struct stat  buf;
		if(stat(handle.sFileName.c_str(), &buf)==0){
			if(buf.st_mtime!=handle.tFilemtime){
				//L4C_INFO("配置文件[%s]已更新，清空缓存", handle.sFileName.c_str());
				handle.cache.clear();
				handle.tFilemtime=buf.st_mtime;
			}
		}
		handle.tLastCheck=now;
	}
	sprintf(sTag, "%s=%s", maintag, subtag);//ini配置名字中必然不可能有等号
	
	map<string, string>::iterator iter;
	iter=handle.cache.find(sTag);
	if(iter==handle.cache.end()){
		//L4C_TRACE("配置文件[%s]缓存中未包含此配置[%s:%s]", handle.sFileName.c_str(), maintag, subtag);
		l4c_getcfgstr(handle.sFileName.c_str(), maintag, subtag, sValue, 1024, "");
		handle.cache.insert(map<string, string>::value_type(sTag, sValue));
		iter=handle.cache.find(sTag);
	}
	//L4C_TRACE("配置文件[%s]配置[%s:%s]=%s", handle.sFileName.c_str(), maintag, subtag, iter->second.c_str());
	return iter->second.c_str();
}


const char* doGetCfgGetStrSlient(const char* maintag, const char* subtag, TCfgHandle& handle)
{
	char sTag[1024]="";
	char sValue[1024];
	time_t now=time(NULL);
	if(now-handle.tLastCheck>=60){
		struct stat  buf;
		if(stat(handle.sFileName.c_str(), &buf)==0){
			if(buf.st_mtime!=handle.tFilemtime){
				handle.cache.clear();
				handle.tFilemtime=buf.st_mtime;
			}
		}
		handle.tLastCheck=now;
	}
	sprintf(sTag, "%s=%s", maintag, subtag);//ini配置名字中必然不可能有等号
	
	map<string, string>::iterator iter;
	iter=handle.cache.find(sTag);
	if(iter==handle.cache.end()){
		l4c_getcfgstr(handle.sFileName.c_str(), maintag, subtag, sValue, 1024, "");
		handle.cache.insert(map<string, string>::value_type(sTag, sValue));
		iter=handle.cache.find(sTag);
	}
	return iter->second.c_str();
}

const char* cfgGetStr(const char* maintag, const char* subtag)
{
	return doGetCfgGetStr(maintag, subtag, crmcfg);
}

const char* cfgGetStrSlient(const char* maintag, const char* subtag)
{
	return doGetCfgGetStrSlient(maintag, subtag, crmcfg);
}

#define THROW_EXEPTION_NULL_CFG(a,b,c) if(a=="")  {string serr="";serr=serr+"["+b+":"+c+"]配置项为空";throw(appException(306*1000000+111, serr.c_str()));}
void GetDBCfg(const char* lable, string& tns, string&  user, string& passwd, string& bak, string& type)
{
	char dst[1024];
	string sDBSrvOpt, sDBUsrOpt, sDBPasswdOpt;
	string sDBLable=doGetCfgGetStr(lable, "DBLABEL", crmcfg);
	THROW_EXEPTION_NULL_CFG(sDBLable, lable, "DBLABEL");
	type=doGetCfgGetStr(lable, "DBTYPE", crmcfg);
	THROW_EXEPTION_NULL_CFG(type, lable, "DBTYPE");
	bak=doGetCfgGetStr(lable, "DBBAK", crmcfg);
	sDBSrvOpt=doGetCfgGetStr(lable, "DBSERVOPT", crmcfg);
	if(sDBSrvOpt=="") sDBSrvOpt="DBSERV";
	sDBUsrOpt=doGetCfgGetStr(lable, "DBUSEROPT", crmcfg);
	if(sDBUsrOpt=="") sDBUsrOpt="DBUSER";
	sDBPasswdOpt=doGetCfgGetStr(lable, "DBPASSWDOPT", crmcfg);
	if(sDBPasswdOpt=="") sDBPasswdOpt="DBPASSWD";

	tns=doGetCfgGetStr(sDBLable.c_str(), sDBSrvOpt.c_str(), pwdcfg);
	THROW_EXEPTION_NULL_CFG(tns, sDBLable.c_str(), sDBSrvOpt.c_str());
	user=doGetCfgGetStr(sDBLable.c_str(), sDBUsrOpt.c_str(), pwdcfg);
	THROW_EXEPTION_NULL_CFG(user, sDBLable.c_str(), sDBUsrOpt.c_str());
	passwd=doGetCfgGetStr(sDBLable.c_str(), sDBPasswdOpt.c_str(), pwdcfg);
	THROW_EXEPTION_NULL_CFG(passwd, sDBLable.c_str(), sDBPasswdOpt.c_str());
	desdec(user.c_str(), dst, 1024);
	user=dst;
	desdec(passwd.c_str(), dst, 1024);
	passwd=dst;
}
void GetFtpCfg(const char* label, string& ip, string&  user, string& passwd, string& path)
{
	char dst[1024];
	string sDBSrvOpt, sDBUsrOpt, sDBPasswdOpt;
	string sDBLable=doGetCfgGetStr(label, "FTPLABEL", crmcfg);
	THROW_EXEPTION_NULL_CFG(sDBLable, label, "FTPLABEL");
	path=doGetCfgGetStr(label, "FTPPATH", crmcfg);
	THROW_EXEPTION_NULL_CFG(path, label, "FTPPATH");
	sDBSrvOpt=doGetCfgGetStr(label, "FTPIPOPT", crmcfg);
	if(sDBSrvOpt=="") sDBSrvOpt="HOSTIP";
	sDBUsrOpt=doGetCfgGetStr(label, "FTPUSEROPT", crmcfg);
	if(sDBUsrOpt=="") sDBUsrOpt="HOSTUSER";
	sDBPasswdOpt=doGetCfgGetStr(label, "FTPPASSWDOPT", crmcfg);
	if(sDBPasswdOpt=="") sDBPasswdOpt="HOSTPASSWD";

	ip=doGetCfgGetStr(sDBLable.c_str(), sDBSrvOpt.c_str(), pwdcfg);
	THROW_EXEPTION_NULL_CFG(ip, sDBLable.c_str(), sDBSrvOpt.c_str());
	user=doGetCfgGetStr(sDBLable.c_str(), sDBUsrOpt.c_str(), pwdcfg);
	THROW_EXEPTION_NULL_CFG(user, sDBLable.c_str(), sDBUsrOpt.c_str());
	passwd=doGetCfgGetStr(sDBLable.c_str(), sDBPasswdOpt.c_str(), pwdcfg);
	THROW_EXEPTION_NULL_CFG(passwd, sDBLable.c_str(), sDBPasswdOpt.c_str());
	desdec(user.c_str(), dst, 1024);
	user=dst;
	desdec(passwd.c_str(), dst, 1024);
	passwd=dst;
}

void GetFtpCfg2(const char* label,string sDBSrvOpt, string sDBUsrOpt, string sDBPasswdOpt, string& ip, string&  user, string& passwd, string& path)
{
	char dst[1024];
	string sDBLable=label;

	ip=doGetCfgGetStr(sDBLable.c_str(), sDBSrvOpt.c_str(), pwdcfg);
	THROW_EXEPTION_NULL_CFG(ip, sDBLable.c_str(), sDBSrvOpt.c_str());
	user=doGetCfgGetStr(sDBLable.c_str(), sDBUsrOpt.c_str(), pwdcfg);
	THROW_EXEPTION_NULL_CFG(user, sDBLable.c_str(), sDBUsrOpt.c_str());
	passwd=doGetCfgGetStr(sDBLable.c_str(), sDBPasswdOpt.c_str(), pwdcfg);
	THROW_EXEPTION_NULL_CFG(passwd, sDBLable.c_str(), sDBPasswdOpt.c_str());
	desdec(user.c_str(), dst, 1024);
	user=dst;
	desdec(passwd.c_str(), dst, 1024);
	passwd=dst;
}


