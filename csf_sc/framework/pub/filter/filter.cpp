#include "framework.h"

#include <string>
#include <iostream>
#include <map>

using namespace std;


void getDataObjItemOra(set<string>& st,
		const char* login_no, const char* svc_name,
		TCtrlInfo* errinfo, int validate_type)
{
	L4C_WARN("内存数据库无法使用，使用oracle处理数据权限过滤");
	multimap<int, string> mData;
	multimap<int, string> detected;
	multimap<int, string>::iterator iter;
	otl_nocommit_stream getAP(10,"select distinct b.ALIAS_NAME, c.POPEDOM_CODE \
									from bs_procedure_dict a, bs_FuncDataItem_rel b, bs_DataObjItem_dict c \
									where a.PROCEDURE_ID=b.PROCEDURE_ID and b.OBJECT_ID=c.OBJECT_ID \
									and c.OBJECT_CLASS=2 and a.PROCEDURE_NAME=:V1<char[255]>", GETDB(errinfo));

	printf("===========detected.size=%d\n", detected.size());
	getAP<<svc_name;
	while(!getAP.eof()){
		int iPowerCode;
		char sAliasName[30];
		getAP>>sAliasName>>iPowerCode;
		mData.insert(multimap<int, string>::value_type(iPowerCode, sAliasName));
	}
	if(!validate_type){
		// 如果没有验证， 则全部模糊化
		for(iter=mData.begin();iter!=mData.end();iter++){
			st.insert(iter->second);
		}
		return;
	}
	for(iter=mData.begin();iter!=mData.end();iter++)
	{
		
		//通过工号权限关系查找互斥权限
		otl_nocommit_stream getLRP1(1,"select a.POPEDOM_CODE from bs_LoginPopedom_rel a ,bs_Popedom_dict b \
										where ((a.RELA_TYPE='0' and a.SELECT_PRIVS=1) or (a.RELA_TYPE='1' and a.SELECT_PRIVS=0))\
										and sysdate between a.BEGIN_DATE  \
										and a.END_DATE and b.POPEDOM_CODE=:pc<int> \
										and b.POPEDOM_CODE=a.POPEDOM_CODE \
										and b.POPEDOM_TYPE='02' \
										and b.USE_FLAG='Y' \
										and a.LOGIN_NO=:ln<char[20+1]> ", GETDB(errinfo));
		getLRP1<<iter->first<<login_no;
		if(!getLRP1.eof()){//如果查到了互斥的权限，则认定该工号无此权限
			////st.insert(iter->second); // liupengc added
			//mData.erase(iter++);//mData.erase(iter->first);
			printf("found 1111\n");
			detected.insert(multimap<int, string>::value_type(iter->first, iter->second));
			continue;
		}
		//通过角色权限关系查找权限
		otl_nocommit_stream getLR(10,"select b.POPEDOM_CODE,b.SELECT_PRIVS from bs_LoginRole_rel a ,bs_RolePdom_rel b, bs_Popedom_dict c ,bs_ROLE_dict d \
										where a.ROLE_CODE=b.ROLE_CODE \
										and a.ROLE_CODE=d.ROLE_CODE  \
										and  d.USE_FLAG='Y' \
										and sysdate between a.BEGIN_DATE  \
										and a.END_DATE and b.POPEDOM_CODE=:pc<int>  \
										and b.POPEDOM_CODE=c.POPEDOM_CODE \
										and c.POPEDOM_TYPE='02' \
										and a.login_no=:ln<char[20+1]>  \
										and c.USE_FLAG='Y'", GETDB(errinfo));
		getLR<<iter->first<<login_no;
		int iPCode=0, iSePs=-255, isNULL=0; 
		if(!getLR.eof()){
			getLR>>iPCode>>iSePs;
		}else{
			isNULL=1;
		}
		if(isNULL){//如果查无结果
			//通过工号权限关系查找叠加权限
			otl_nocommit_stream getLRP1(1,"select a.POPEDOM_CODE from bs_LoginPopedom_rel a ,bs_Popedom_dict b \
											where ((a.RELA_TYPE='0' and a.SELECT_PRIVS=0) or (a.RELA_TYPE='1' and a.SELECT_PRIVS=1))\
											and sysdate between a.BEGIN_DATE  \
											and a.END_DATE and b.POPEDOM_CODE=:pc<int> \
											and b.POPEDOM_CODE=a.POPEDOM_CODE \
											and b.POPEDOM_TYPE='02' \
											and b.USE_FLAG='Y' \
											and a.LOGIN_NO=:ln<char[20+1]> ", GETDB(errinfo));
			getLRP1<<iter->first<<login_no;
			if(!getLRP1.eof()){//如果没查到权限，则认定该工号无此权限
				//mData.erase(iter++);// liupengc mData.erase(iter->first);
				printf("found 3333\n");
				detected.insert(multimap<int, string>::value_type(iter->first, iter->second));
				continue;
			}
		}else if(iSePs==1){//查到了可显示的角色权限
			//mData.erase(iter++);//liupengc mData.erase(iter->first);

			printf("found 2222\n");
			detected.insert(multimap<int, string>::value_type(iter->first, iter->second));
			continue;
		}

	}
	for(iter=mData.begin();iter!=mData.end();iter++){
		if(detected.find(iter->first) == detected.end()){
			printf("~~~~~filter add \n");
			st.insert(iter->second);
		}else{
			printf("~~~~~filter skiped, detected.size=%d\n", detected.size());
		}
	}
}





void getDataObjItemMdb(set<string>& st, const char* login_no, const char* svc_name, TCtrlInfo* errInfo)
{
	static time_t lastInit=0;
	multimap<int, string> mData;
	multimap<int, string>::iterator iter;
	static DCI_SQL dsql1;
	static DCI_SQL dsql2;
	static DCI_SQL dsql3;
	static DCI_SQL dsql4;
	DCI_ROW v_row;


	if(GETMDBLASTCONN(errInfo)!=lastInit){//用这种方式保证只会预处理一次sql语句，防止多次预处理sql语句造成的时间浪费
		
		L4C_TRACE("mdb init");
		if(!GETMDB(errInfo)) return getDataObjItemOra(st, login_no, svc_name, errInfo, 1);

		if(dci_prepare_sql(GETMDB(errInfo), &dsql1, "select distinct b.ALIAS_NAME, c.POPEDOM_CODE \
													from bs_procedure_dict a, bs_FuncDataItem_rel b, bs_DataObjItem_dict c \
													where b.PROCEDURE_ID=a.PROCEDURE_ID and c.OBJECT_ID=b.OBJECT_ID and a.PROCEDURE_NAME=? and c.OBJECT_CLASS=2 ")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql2, "select a.POPEDOM_CODE from bs_LoginPopedom_rel a ,bs_Popedom_dict b \
														where  ((a.RELA_TYPE='0' and a.SELECT_PRIVS=1) or (a.RELA_TYPE='1' and a.SELECT_PRIVS=0))\
														and a.LOGIN_NO=? and a.POPEDOM_CODE=? \
														and sysdate >= a.BEGIN_DATE  and sysdate <=a.END_DATE\
														and b.POPEDOM_CODE=a.POPEDOM_CODE \
														and b.POPEDOM_TYPE='02' \
														and b.USE_FLAG='Y'")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql3, "select b.SELECT_PRIVS from bs_LoginRole_rel a ,bs_RolePdom_rel b, bs_Popedom_dict c ,bs_ROLE_dict d \
														where a.login_no=? and b.ROLE_CODE=a.ROLE_CODE and  b.POPEDOM_CODE=? \
														and c.POPEDOM_CODE=b.POPEDOM_CODE \
														and d.ROLE_CODE=a.ROLE_CODE\
														and d.USE_FLAG='Y' \
														and sysdate >= a.BEGIN_DATE  \
														and sysdate <= a.END_DATE \
														and c.POPEDOM_TYPE='02' \
														and c.USE_FLAG='Y'")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql4, "select a.POPEDOM_CODE from bs_LoginPopedom_rel a ,bs_Popedom_dict b \
														where  ((a.RELA_TYPE='0' and a.SELECT_PRIVS=0) or (a.RELA_TYPE='0' and a.SELECT_PRIVS=0))\
														and a.LOGIN_NO=? and a.POPEDOM_CODE=? \
														and sysdate >= a.BEGIN_DATE  and sysdate <=a.END_DATE\
														and b.POPEDOM_CODE=a.POPEDOM_CODE \
														and b.POPEDOM_TYPE='02' \
														and b.USE_FLAG='Y'")!=0){//预处理sql语句。绑定变量用问号代替
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//内存数据库的错误代码以305开始
		}
		lastInit=GETMDBLASTCONN(errInfo);
	}
	if(!GETMDB(errInfo)) return getDataObjItemOra(st, login_no, svc_name, errInfo, 1);
	if(dci_bind_param(GETMDB(errInfo), &dsql1, 0, DCI_TYPE_CHAR, (void*)svc_name)!=0)//绑定变量，有几个问号就需要调用几次。注意第3个入参表示变量的位置
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if(dci_query_p(GETMDB(errInfo), &dsql1)!=0)//执行查询
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	while( (v_row = dci_fetch_row_s(GETMDB(errInfo), &dsql1))){
		mData.insert(multimap<int, string>::value_type(atoi(v_row[1]), (char*)v_row[0]));
		L4C_TRACE("popedom_code:%s, zn:%s",(char*)v_row[1], (char*)v_row[0]);
	}
	for(iter=mData.begin();iter!=mData.end();iter++)
	{
		if(dci_bind_param(GETMDB(errInfo), &dsql2, 0, DCI_TYPE_CHAR, (void*)login_no)!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		if(dci_bind_param(GETMDB(errInfo), &dsql2, 1, DCI_TYPE_INT, (void*)(&(iter->first)))!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		if(dci_query_p(GETMDB(errInfo), &dsql2)!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		while( (v_row = dci_fetch_row_s(GETMDB(errInfo), &dsql2))){
			mData.erase(iter++);// liupengc mData.erase(iter->first);
			continue;
		}
		if(dci_bind_param(GETMDB(errInfo), &dsql3, 0, DCI_TYPE_CHAR, (void*)login_no)!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		if(dci_bind_param(GETMDB(errInfo), &dsql3, 1, DCI_TYPE_INT, (void*)(&(iter->first)))!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		if(dci_query_p(GETMDB(errInfo), &dsql3)!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		
		int iSePs=-255, isNULL=0;
		DCI_ROW dr=dci_fetch_row_s(GETMDB(errInfo), &dsql3);
		if(dr){
			iSePs=atoi(dr[0]);
		}else{
			isNULL=1;
		}
		
		if(isNULL){
			if(dci_bind_param(GETMDB(errInfo), &dsql4, 0, DCI_TYPE_CHAR, (void*)login_no)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_bind_param(GETMDB(errInfo), &dsql4, 1, DCI_TYPE_INT, (void*)(&(iter->first)))!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_query_p(GETMDB(errInfo), &dsql4)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_fetch_row_s(GETMDB(errInfo), &dsql4)==NULL){
				mData.erase(iter++);//liupengc mData.erase(iter->first);
				continue;
			}
		}else if(iSePs==1){//查到了可显示的角色权限
			mData.erase(iter++);// liupengc mData.erase(iter->first);
			continue;
		}
	}
	for(iter=mData.begin();iter!=mData.end();iter++){
		st.insert(iter->second);
	}
}

char *confusion(const char *str){
	char *s = strdup(str);
	int l = strlen(s);
	for(int i=2; i<l-2; i+=2){
		s[i] = '*';
		s[i+1] = '*';
	}
	return s;
}

void FilterUtype(utype* pu, set<string>& st)
{
	int i;

	u_errno=0;
	for(i=0;i<pu->cnt;i++){
		int n=st.count(utGetName(pu,i));
		if((pu->ppe[i]->type==U_ARRAY||pu->ppe[i]->type==U_STRUCT)){
			FilterUtype(pu->ppe[i]->value.p_utype, st);
			continue;
		}

		if(n==0) continue;
		switch(pu->ppe[i]->type){
			case U_CHAR:{
				utSetChar(pu,i,0);
				break;
			}
			case U_INT:{
				utSetInt(pu,i,0);
				break;
			}
			case U_LONG:
			{
				utSetLong(pu,i,0);
				break;
			}
			case U_DOUBLE:
			{
				utSetDouble(pu,i,0);
				break;
			}
			case U_STRING:
			{
				char *s = utGetStr(pu, i);
				s = confusion(s);
				utSetStr(pu, i, s);
				free(s);
				break;
			}
			default:
			{
				break;
			}
		}
	}

}


void Powerfilter(utype* pu_out, TCtrlInfo* errinfo, const utype* pu_in, const char* svc_name)
{
	set<string> st;
	const char* login_no;
	int validate_type = 1; // 默认为已验证， 为了向后兼容

	try {
		login_no = utGetStrByDir(pu_in,
				"REQUEST_INFO", "OPR_INFO", "LOGIN_NO");
	} catch (uException& err) {
		return;
	}

	const char *validate_path = getenv("VALIDATE_PATH");
	if(validate_path != NULL){
		try{
			validate_type = utGetIntByPath(pu_in, validate_path);
		}catch (uException& err) {
			//没有输入值的话， 就按默认原则处理（已验证）
			printf("not found path:[%s]\n", validate_path);
		}
	} //没有配置也按原有原则处理（已验证）
	//getDataObjItemMdb(st, login_no, svc_name,errinfo);
	getDataObjItemOra(st, login_no, svc_name, errinfo, validate_type);
	FilterUtype(pu_out, st);
}





