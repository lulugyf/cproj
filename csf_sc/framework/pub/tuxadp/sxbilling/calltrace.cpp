#include <framework.h>

#include <string>
#include <iostream>
#include <list>
#include <time.h>
#include <sstream>
#include <unistd.h>

#include "calltrace.h"

using namespace std;
#define CALLTRACEFLAG "!_@"

extern "C" {
	int udp_socket();
	void *udp_make_addr(const char *addr);
	int udp_sendto(int sd, void *addr, const char *buf, int len);
	void udp_close(int s);
	void udp_getlocaladdr(char addr[16]);
}


/*
<统一ID> <调用ID> <父调用ID> <服务编号> <服务名> <调用开始时间> <调用结束时间>
<主机IP> <端口号> <手机号> <工号> <模块代码> <结果编码> <结果信息>
 */
struct CallInfo{
    list<string> callstack;
    const char * servicename;      //服务名称
    const char * bpname;        // 入口BP名称
    char universe_accept[128]; //统一流水
    int  log_flag;             // 服务开关是否打开， 1-是； 0-否
    int  log_handle;          // fd of udp socket
    void *log_path;            // sockaddr_in *addr, generate by udp_make_addr, and must free outer
    int  callid_seed;
    char login_no[64];
    char op_code[8];
    char phone_no[64];
    char localaddr[16];
    const char * push(const char *callid);
    void pop();
};


TCtrlInfoEx2::TCtrlInfoEx2() {
	

    memset(this, 0, sizeof(TCtrlInfoEx2));
    CallInfo *c = new CallInfo();
    memcpy(__flag1, CALLTRACEFLAG, 4);
    c->log_path = NULL;
    c->log_handle = -1;
    reserve1 = c;
}

TCtrlInfoEx2::~TCtrlInfoEx2(){
	

    CallInfo *c = (CallInfo *)reserve1;
    
    
   	if( c == NULL  ) return ;
   		
    if(c->log_path != NULL)
    	free(c->log_path);
    if(c->log_handle != -1)
    	udp_close(c->log_handle);
    	 
    delete c;

}

const char *TCtrlInfoEx2::getServiceName(){
	CallInfo *c = (CallInfo *)reserve1;
	return c->servicename;
}

const char *TCtrlInfoEx2::getBPName(){
	CallInfo *c = (CallInfo *)reserve1;
	return c->bpname;
}

bool TCtrlInfoEx2::checkStruct(){
	if(memcmp(__flag1, CALLTRACEFLAG, sizeof(CALLTRACEFLAG)) == 0)
		return true;
	return false;
}


static char* uGetStrByName(const utype* pu, char* buf, int bufSize, const char* name)
{
    UPOS p;
    memset(buf, 0, bufSize);
    //查找当前utype下是否有名字为name的节点，如果有则返回节点值
    if(UPOS_END !=(p = utFind(pu, name)))
    {
				switch(pu->ppe[p]->type)
				{
					case U_INT:snprintf(buf, bufSize - 1, "%d", utGetInt(pu, name, p));break;
					case U_LONG:snprintf(buf, bufSize - 1, "%ld", utGetLong(pu, name, p));break;
					case U_DOUBLE:snprintf(buf, bufSize - 1, "%0.2f", utGetDouble(pu, name, p));break;
					case U_STRING:snprintf(buf, bufSize - 1, "%s", utGetStr(pu, name, p));break;
					default:strcpy(buf, "");break;
				}
		L4C_DEBUG("== e2e =buf is:%s", buf);
		return buf;
		}

    char sUtypeNodeName[127 + 1];
    uAutoPtr uTmp(uInit(0));
    uTmp = utClone(pu);
    int iLen = uTmp->cnt;

    for(int i = 0; i < iLen; i ++)
    {
        //首先按从上往下的顺序取utype当前目录下所有节点，
        //并判断节点是否为utype，为utype则进入utype，然后回调自身
        memset(sUtypeNodeName, 0, sizeof(sUtypeNodeName));
        strcpy(sUtypeNodeName, utGetName(pu, i));
        //printf("*****************sUtypeNodeName=[%s]***********************\n", sUtypeNodeName);
        int uTypeType = utGetType(pu, sUtypeNodeName);
        if(U_STRUCT == uTypeType)
        {
            uGetStrByName(utGetStruct(pu, sUtypeNodeName), buf, bufSize, name);
            if('\0' != buf[0])
            {
                return buf;
            }
        }
    }
    return buf;
}

static void timestr14(struct timeval *t, char *str)
{
	struct tm *tm;
	tm = localtime(&t->tv_sec);
	sprintf(str, "%04d%02d%02d%02d%02d%02d",
			tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
			tm->tm_hour, tm->tm_min, tm->tm_sec);
}

/*
 *
配置文件crm.cfg 新增内容,端到端监控
[E2E_LOG]
e2e_sendlog_flag=1
svc_${servicename}=1(服务开关),1(统一流水开关)
uni_accept_path=COMMON_INFO.TRACE_ID
log_path=udp://127.0.0.1:7788
 */
void TCtrlInfoEx2::init1(const char *servicename, const char *bpname, const utype *uin){
	CallInfo *c = (CallInfo *)reserve1;
	
	char temp[128];
	char kgvalue[20];

		
	memset(temp,0,sizeof(temp));
	memset(kgvalue,0,sizeof(kgvalue));
	
	c->servicename = servicename;
	c->bpname = bpname;
	
	//检查配置开关， 以及获取统一流水配置	
	
	//判断总开关是否打开
	L4C_DEBUG("== e2e =e2e_sendlog_flag:%s", cfgGetStr("E2E_LOG", "e2e_sendlog_flag"));
	if(strcmp(cfgGetStr("E2E_LOG", "e2e_sendlog_flag"), "1") != 0){
				c->log_flag = 0;
				return;
	}
	
	//总开关打开，继续检查分开关是否打开
	sprintf(temp, "svc_%s", servicename);
	strcpy(kgvalue,cfgGetStr("E2E_LOG", temp));
	
	//服务开关是否打开
	
	if( kgvalue[0] == '1' ){
		c->log_flag = 1;
	}else{
		c->log_flag = 0;
		return;
	}

	//获取统一流水，并保存到CallInfo 结构体中
	const char *uni_accept_path = cfgGetStr("E2E_LOG", "uni_accept_path");
	if(uni_accept_path[0] == 0){
		c->log_flag = 0;
		return;
	}
	try{
		 char *uniaccept = NULL;
		try{
			uniaccept = utGetStrByPath(uin, uni_accept_path);
			strcpy(c->universe_accept, uniaccept);
		}catch(uException &ue){
						printf("==errMsg=%s===",ue.errMsg);
		}
		
		//统一流水开关是否打开
		if( (uniaccept==0 || uniaccept[0] == 0 ) && kgvalue[2] != '1' )
			c->log_flag = 0;
		else if( (uniaccept==0 || uniaccept[0] == 0) && kgvalue[2] == '1' )
		{
			char _t11[15]={"\0"};
			struct timeval t11;
			
			gettimeofday(&t11, NULL);
			timestr14(&t11, _t11);		
			pid_t pid = getpid();
			pid = pid >999999?0:pid;//防超过6位，超过统一流水的长度
			srand( (unsigned int)(time(0)+pid) );	
			int irand = (rand()%900000)+ 100000;
			pid = pid==0?	irand:pid;
			 
			//重新生成统一流水
			sprintf(c->universe_accept,"900%stuxadp%d",_t11,irand);	
			c->universe_accept[40]='\0';
			
			strcpy(temp, "90000000991");
		}		
		else{
			//strcpy(temp, utGetStrByPath(uin, "COMMON_INFO.CALL_ID"));//父调用ID有问题
				try{
					strcpy(temp, utGetStrByPath(uin, "COMMON_INFO.CALL_ID"));
				}catch(uException &ue){
					L4C_DEBUG("== e2e  ===get COMMON_INFO.CALL_ID failed!!!");
				}
		}
		
	}catch(uException &ue){
		L4C_DEBUG("TCtrlInfoEx2 err or ");
		L4C_DEBUG("===e2e get path:%s failed code:%d msg:%s", uni_accept_path, ue.errCode, ue.errMsg);
		//strcpy(c->universe_accept, "<unknown>");
		c->log_flag = 0;
	}
	if( c->log_flag == 0 )
		 return;

	//建立UDP socket以及从配置中读取服务端地址
	const char *log_path = cfgGetStr("E2E_LOG", "log_path");
	c->log_handle = udp_socket();
	  L4C_DEBUG("== e2e =log_path:%s", log_path);
	c->log_path = udp_make_addr(log_path);

	udp_getlocaladdr(c->localaddr);
		
		try{
			uGetStrByName(uin, c->login_no, sizeof(c->login_no), "LOGIN_NO");
		}catch(uException &ue){
		}
		
		try{
			L4C_DEBUG("== e2e  ===get PHONE_NO  =====");
			uGetStrByName(uin, c->phone_no, sizeof(c->phone_no), "PHONE_NO");
			if(c->phone_no == NULL || strncmp(c->phone_no,"",1)==0 ){
				L4C_DEBUG("== e2e  ===get SERVICE_NO 111 =====");
				uGetStrByName(uin, c->phone_no, sizeof(c->phone_no), "SERVICE_NO");
			}
		}catch(uException &ue){
		}
		
		try{
			uGetStrByName(uin, c->op_code, sizeof(c->op_code), "OP_CODE");
		}catch(uException &ue){
			L4C_DEBUG("== e2e  ===get OP_CODE failed!!!");
		}

	/*
	uGetStrByName(uin, c->login_no, sizeof(c->login_no), "LOGIN_NO");
	uGetStrByName(uin, c->phone_no, sizeof(c->phone_no), "PHONE_NO");
	uGetStrByName(uin, c->op_code, sizeof(c->op_code), "OP_CODE");
	
	
	strcpy(c->login_no,"null");
	strcpy(c->phone_no,"null");
	strcpy(c->op_code,"null");
	*/
	
	c->push(temp);
}





const char * CallInfo::push(const char *callid){
	const char *p = NULL;

	if(callstack.size() > 0)
		p = callstack.back().c_str();
	callstack.push_back( callid );
	return p;
}

void CallInfo::pop(){
	callstack.pop_back();
}



static void timestr(struct timeval *t, char *str)
{
	struct tm *tm;
	tm = localtime(&t->tv_sec);
	sprintf(str, "%04d-%02d-%02d% 02d:%02d:%02d.%03d",
			tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
			tm->tm_hour, tm->tm_min, tm->tm_sec, t->tv_usec/1000);
}

void EntryRecord::setCode(long c){
	code = c;
}
void EntryRecord::setMsg(const char *m) {
	errmsg = m;
}

void EntryRecord::setIn(const utype *pin){ 	this->pin = pin; }
void EntryRecord::setIn(const char *pin){ 	this->s_pin = pin; }

void EntryRecord::setOut(const utype *pout){ this->pout = pout; }
void EntryRecord::setOut(const char *pout){ this->s_pout = pout; }

//#include <uuid/uuid.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
static void gencallid(char *callid, const int len){
	char hostname[64];
	static unsigned short seed = (unsigned short)time(NULL);
	
	// 生成 callid
    //uuid_t buf;
    //uuid_generate(buf);
    //uuid_unparse(buf, callid);
	
	gethostname(hostname, sizeof(hostname));
	snprintf(callid, len, "%s-%ld-%ld-%d", hostname, getpid(), time(NULL), ++seed);
}

EntryRecord::EntryRecord(const char *func, TCtrlInfo *tinfo){

	if(!((TCtrlInfoEx2 *)tinfo)->checkStruct())
		return;
		
	CallInfo *x = (CallInfo *)(((TCtrlInfoEx2 *)tinfo)->reserve1);
	
	CallInfo *ci = NULL;
	if( x == NULL ){ 
			ci = x;
			cii = x;
			return ;
	}

	ci = x;
	cii = ci;
	
	if (ci == NULL)
		return;
		
  if(ci->log_flag == 0)
        return;		
		
	funcname = func;
	gettimeofday(&t1, NULL);
	code = 0;

	gencallid(callid, sizeof(callid));
	//sprintf(callid, "%04d", ++ci->callid_seed);
	errmsg = NULL;
	pin = NULL;
	pout = NULL;
	s_pin = NULL;
	s_pout = NULL;
	callid_p = ci->push(callid);

}

EntryRecord::~EntryRecord(){

	
	if(cii == NULL)
		return;

		
	CallInfo * ci = (CallInfo *)cii;
	
  if(ci->log_flag == 0)
        return;		
     	
		ci->pop(); 

  			      	
	gettimeofday(&t2, NULL);
	char _t1[32], _t2[32];
	timestr(&t1, _t1);
	timestr(&t2, _t2);
	stringstream ss;
	
	ss <<ci->universe_accept<<"~!~"<<callid<<"~!~";
	L4C_DEBUG("== e2e = callid_p %s",callid_p);
	if( callid_p!=NULL )
		ss << callid_p ;
	else
		ss << "" ;
		
		ss<<"~!~xxx~!~" <<ci->servicename <<"~!~";
		 
		ss <<"B001~!~null~!~" <<funcname<<"~!~";
	
	
	ss << _t1 << "~!~" << _t2 << "~!~" << ci->localaddr << "~!~" << 0<<"~!~"<<"null"<< "~!~";
	//ss <<"null"<< "~!~"<<ci->phone_no<<"~!~"<<ci->login_no<<"~!~";
	ss <<ci->phone_no<< "~!~"<<ci->phone_no<<"~!~"<<ci->login_no<<"~!~";
	ss << "null~!~" << ci->op_code<<"~!~"<<code<<"~!~";
		
	if( errmsg!=NULL && errmsg[0]!='\0' ){
		ss<<errmsg << "~!~";
	}else{
		ss<<"null" << "~!~";
	}
	uAutoPtr uapOutMsg(uInit(0));
	uAutoPtr poutMsg(uInit(0));	
	if(s_pout != NULL)
	{
		char *tmp = NULL;
		tmp = strstr(s_pout, "<ROOT>");
		string str = tmp;
		string ruleDetailInfo = str.substr(0,strlen(tmp));
		L4C_TRACE("=====ruleDetailInfo===[%s]=======\n",ruleDetailInfo.c_str());
		uapOutMsg = uXml2Utype(ruleDetailInfo.c_str());
		LogUtype(uapOutMsg);
		printf("11111111222222222\n");
		if(utFind(uapOutMsg, "OUT_DATA") != UPOS_END)
		{
			poutMsg = utClone(utGetStruct(uapOutMsg, "OUT_DATA"));
		}
		else
		{
			poutMsg = NULL;
		}
	}
	if(pout != NULL)
	{
		poutMsg = utClone(pout);
	}
	
	char *prod_prcid = NULL;
	char *rule_detail = const_cast<char*>(errmsg);
	char *rule_type = NULL;
	try{
		if(utFind(poutMsg, "PROD_PRCID") != UPOS_END)
		{
			prod_prcid = utGetStr(poutMsg, "PROD_PRCID");
		}else
		{
			prod_prcid = utGetStrByPath(poutMsg, "DATA.PROD_PRCID");
		}
	}catch(uException &ue){
	}
	if(prod_prcid == NULL)
	{
		prod_prcid = "null";
	}
	ss << prod_prcid << "~!~";

	try{
		if(utFind(poutMsg, "NOTES") != UPOS_END)
		{
			rule_detail = utGetStr(poutMsg, "NOTES");
		}else
		{
			rule_detail = utGetStrByPath(poutMsg, "DATA.NOTES");
		}
	}catch(uException &ue){
	}
	if( rule_detail!=NULL && rule_detail[0]!='\0' ){
	   ss << rule_detail << "~!~";
	}else{
	   ss<<errmsg<< "~!~";
	}
	
	try{
		if(utFind(poutMsg, "RELATION_TYPE") != UPOS_END)
		{
			rule_type = utGetStr(poutMsg, "RELATION_TYPE");
		}
		else
		{
			rule_type = utGetStrByPath(poutMsg, "DATA.RELATION_TYPE");
		}
	}catch(uException &ue){
	}
	if( rule_type!=NULL && rule_type[0]!='\0' ){
	   ss << rule_type << "~!~";
	}else{
	   ss<<code<< "~!~";
	}
		
		
	//只输出服务入口的输入参数
	L4C_DEBUG("== e2e = ci->servicename is %s",ci->servicename);
	L4C_DEBUG("== e2e = funcname is %s",funcname);
	L4C_DEBUG("== e2e = ci->servicename[0] is %s",ci->servicename[0]);
	//test code 
	if(s_pin != NULL){
				L4C_DEBUG("== e2e = 11test s_pin is not NULL: %s",s_pin);
	}else if(pin != NULL){
				L4C_DEBUG("== e2e = 11pin is not NULL");
	}else if(s_pout !=NULL){
				L4C_DEBUG("== e2e = 11test s_pout is not NULL: %s",s_pout);
	}else if(pout !=NULL){
				L4C_DEBUG("== e2e = 11pout is not NULL");
	}
	
	//test code 
/*	
	if( ci->servicename != NULL && funcname!=NULL && ci->servicename[0] == 's' 
		&& strcmp(ci->servicename,funcname) == 0 ){
			// ){
			if(s_pin != NULL){
				L4C_DEBUG("== e2e = s_pin is not NULL: %s",s_pin);
				ss << s_pin << "~!~";
				//ss << "null" << "~!~";
			}else if(pin == NULL){
				L4C_DEBUG("== e2e = pin is  NULL");
				ss << "NULL~!~";
			}else{
				L4C_DEBUG("== e2e = pin is  not NULL");
				char *xmlstr = uUType2Xml(pin, "ROOT");
				if(xmlstr != NULL){
					ss << xmlstr << "~!~";
					free(xmlstr);
				}
			}			
			
		}else{
				ss<<"in xml is NULL"<<"~!~";
			}

*/
	
 /*
	if(s_pin != NULL){
		ss << s_pin << "~!~";
	}else if(pin == NULL){
		ss << "null~!~";
	}else{
		char *xmlstr = uUType2Xml(pin, "ROOT");
		if(xmlstr != NULL){
			ss << xmlstr << "~!~";
			free(xmlstr);
		}
	}
 
 ss<<"null"<<"~!~";
 
 	*/
 	/*
	if( ci->servicename != NULL && funcname!=NULL && ci->servicename[0] == 's' 
		 		&& strcmp(ci->servicename,funcname) == 0 ){
		 //){
		if(s_pout != NULL){
			L4C_DEBUG("== e2e = s_pout is not NULL: %s",s_pout);
			ss << s_pout << "~!~";
		}else if(pout == NULL){
			L4C_DEBUG("== e2e = pout is  NULL");
			ss << "null~!~";
		}else{
			L4C_DEBUG("== e2e = pout is not NULL");
			char *xmlstr = uUType2Xml(pout, "ROOT");
			if(xmlstr != NULL){
				ss << xmlstr << "~!~";
				free(xmlstr);
			}
		}		
}else{
	ss<<"out xml is NULL"<<"~!~";
	}

*/

ss<<"in xml is NULL"<<"~!~";
ss<<"out xml is NULL"<<"~!~";
		 
	L4C_DEBUG("e2e send flume: %s",	ss.str().c_str());
	
	udp_sendto(ci->log_handle, ci->log_path, ss.str().c_str(), ss.str().length());
	/*snprintf(temp, sizeof(temp)-1, "%s\t%s\t%s\t%s\t[5]%s\t%s\t%s\t%s\t[9]%d\t%s\t%s\t%s\t[13]%d\t%s",
			ci->universe_accept, callid, callid_p, "xxx" ci->servicename, _t1, _t2,
			ci->localaddr, 0, ci->phone_no, ci->login_no, ci->op_code, code, errmsg==NULL?"":errmsg);
	udp_sendto(ci->log_handle, ci->log_path, temp, strlen(temp)); 
	printf("--func[%s] callid[%s] parentcallid[%s] time[%ld] code[%d]\n",
		funcname, callid, callid_p==NULL?"<nil>":callid_p,
		(t2.tv_sec-t1.tv_sec)*1000 + (t2.tv_usec-t1.tv_usec)/1000, code);
*/
}

// need a macro to use it
//#define CALLBP(bpname, uInParam, ctrlInfo) __CALLBP(bpname, #bpname, uInParam, ctrlInfo)
utype* __CALLBP(TUtypeFuncPtr bpfunc, const char *bpname, const utype *uInParam, TCtrlInfo *ctrlInfo){
  cout<<"__CALLBP begin..."<<endl;
	if(!((TCtrlInfoEx2 *)ctrlInfo)->checkStruct()){
		return bpfunc(uInParam, ctrlInfo); //兼容未使用 TCtrlInfoEx2 结构的原有代码（后台进程）
	}
	CallInfo *x = (CallInfo *)(((TCtrlInfoEx2 *)ctrlInfo)->reserve1);
	if(x->log_flag != 1)
		return bpfunc(uInParam, ctrlInfo); //日志关，直接调用，不走后边的代码了

    if(bpname == NULL)
        bpname = ((TCtrlInfoEx2 *)ctrlInfo)->getServiceName();

	
    EntryRecord __e(bpname, ctrlInfo );
    
    
    __e.setIn(uInParam);
    try{
    	utype *ret = bpfunc(uInParam, ctrlInfo);
    	__e.setOut(ret);
		return ret;
    } catch (uException& err) {
		__e.setCode(303 * 1000000 + err.errCode);
		__e.setMsg(err.errMsg);
		throw err;
	} catch (otl_exception& otlErr) { // intercept OTL exceptions
		__e.setCode(302 * 1000000 + abs(otlErr.code));
		//snprintf(retMsg, sizeof(retMsg) - 1, "DBERR 错误：%s : %s : %s",
		//		otlErr.msg, otlErr.stm_text, otlErr.var_info);
		__e.setMsg((const char *)otlErr.msg);
		throw otlErr;
	} catch (appException& appErr) {
		__e.setCode(appErr.errCode);
		__e.setMsg(appErr.errMsg);
		throw appErr;
	} catch (std::exception& err) {
		__e.setCode(301 * 1000000);
		__e.setMsg(err.what());
		throw err;
	} catch (...) {
		__e.setCode(300 * 1000000);
		__e.setMsg("未知错误请联系系统管理员!");
		throw;
	}
	return NULL;
}
