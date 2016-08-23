#include "alloca.h"
#include "framework.h"

/*
�궨��˵��
SX_ROUTE_FUNC �漰��ɽ�������·�ɷ���, �漰��2000�����������, ��Ҫ�����ж�;
SX_ONLY_FOR_B: B�����ߺ�,A������ǰ, ·�ɷ���ķ���ֵ�����A1�Ļ�,���滻��B1,
               �����A2�Ļ�,���滻��B2;
			   A1 --> B1
			   A2 --> B2
*/
/* Ϊ˷�����⴦��ֻҪ���ǿ������룬������B1
*/


/* #define SX_ROUTE_FUNC 1 liupengc 0324 A�����,��������·�� */
#define SX_ONLY_FOR_B 1
/* ȡ�� B ����·�ɷ�ʽ liupengc 
#ifdef SX_ONLY_FOR_B
#undef SX_ONLY_FOR_B
#endif
*/
#define SX_ONLY_ID_PHONE_NO_ROUTE 1
#define SX_ID_NO_ROUTE 11      /* 11 : �û�id·Ӵ */
#define SX_PHONE_NO_ROUTE 10   /* 10 : ����·�� */
#define SX_GUOXX_CODE 399001999


/* ���� ���� */
/*
<ROOT>
	<ROUTE_TYPE type="int">10</ROUTE_TYPE>
	<ROUTE_VALUE type="string">18234941234</ROUTE_VALUE>
</ROOT>

�·����·��˵��:

*/

utype* check_route_type(int iRouteCode)
{
	uAutoPtr pout(uInit(10));
}

/*
���·�ɵĺ����� 2000 ��������, ��ô����1, ���򷵻� 0
1: ·�ɺ�����2000������;
0: ·�ɺ��벻��2000������;
*/
/**/
int check_2000_phone_and_id_ora(int i_route_code, const char * s_route_value, TCtrlInfo* errInfo)
{
	static char route_type_name[32];
    static char sql_str[256];

	/*
	i_route_code == SX_ID_NO_ROUTE ? strcpy(route_type_name,"ID_NO") : strcpy(route_type_name,"PHONE_NO");
	sprintf(sql_str, "select 1 from un_user_info where  %s = :v1<char[21]>", route_type_name);
    */
    if(i_route_code == SX_ID_NO_ROUTE)
    {
    	strcpy(sql_str, "select 1 from un_user_info where  ID_NO = :v1<long>");
    }
    else
    {
    	strcpy(sql_str, "select 1 from un_user_info where  PHONE_NO = :v1<char[21]>");
    }
	static int tmp = -9;
	otl_nocommit_stream qry_exist(1, sql_str, GETDB(errInfo));
	if(i_route_code == SX_ID_NO_ROUTE)
	{
		qry_exist << atol(s_route_value);
	}
	else
	{
		qry_exist << s_route_value;
	}

	if(qry_exist.eof()) return 0;  /* �� un_user_info �����޷��鵽 */
	qry_exist >> tmp;
	return 1;
}

/*  �����ڴ����ݿ�������ܸ��� static �������г�ʼ�� ֱ����Դ�����д���
int check_2000_phone_and_id_imdb(int i_route_code, char * s_route_value, TCtrlInfo* errInfo)
{
	static char route_type_name[32];
    static char sql_str[256];
    static DCI_SQL dsql4;
	static int pre_flag = 0;

	i_route_code == SX_ID_NO_ROUTE ? strcpy(route_type_name,"ID_NO") : strcpy(route_type_name,"PHONE_NO");
	sprintf(sql_str, "select 1 from un_user_info where  %s = ?", route_type_name);

	if(pre_flag == 0)
	{
		if(dci_prepare_sql(GETMDB(errInfo), &dsql4, sql_str)!=0) //Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		pre_flag = 1;
	}

	if(dci_bind_param(GETMDB(errInfo), &dsql4, 0, DCI_TYPE_CHAR, (void*)(s_route_value))!=0)//�󶨱������м����ʺž���Ҫ���ü��Ρ�
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if(dci_query_p(GETMDB(errInfo), &dsql4)!=0)//ִ�в�ѯ
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

	static DCI_ROW v_row;
	static int row_s = 0;
	while((v_row = dci_fetch_row_s(GETMDB(errInfo), &dsql4))){
		row_s++;
	}
	return row_s;
}
*/



#ifdef SX_ROUTE_FUNC
/* �漰���µ�·�ɷ��� */
utype* getRouteInfoOra(const utype* p, TCtrlInfo* errInfo)
{
	L4C_WARN("�ڴ����ݿ��޷�ʹ�ã�ʹ��oracle��ȡ·������");
	static bool isFirst=true;
	static const char* sSql0="select rule_code,route_data_type,group_length from bs_routerule_dict where  route_code=:ROUTE_TYPE<int> ";
	static const char* sSql2="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code and b.key_value = :ROUTE_VALUE<char[128]>";
	static const char* sSql3="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code AND TO_NUMBER (b.key_value)<:ROUTE_VALUE<long> and TO_NUMBER (b.key_value2)>:ROUTE_VALUE<long> ";
	static const char* sSql4="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code AND b.key_value<:ROUTE_VALUE<char[128]>  AND b.key_value2>:ROUTE_VALUE<char[128]>";
	const char* sSql=NULL;
	int pcode;
	char sWebSuffix[64]="";
	char sNote[60+1]="";
	uAutoPtr pout(uInit(10));
	int iRouteCode=utGetInt(p, "ROUTE_TYPE");
	const char* sRouteValue=utGetStr(p, "ROUTE_VALUE");
	int iRuleCode=0;
	int iRuleDataType=0;
	int iGroupLength=0;
    static char tmp_msg[128];
	/* liupengc ����ǲ����û�id ���� ����·��,��ô�ͷ��� B1*/
	if( !(iRouteCode == SX_ID_NO_ROUTE || iRouteCode == SX_PHONE_NO_ROUTE) )
	{
		/* B �������ߣ����ٷ��ع̶�ֵ 
		utAddStr(pout, "WEB_SUFFIX", "B1");
		utAddInt(pout, "PARTITION_CODE", 20); // added for dongxiao using 
		utAddStr(pout, "NOTE", "16"); // added for dongxiao using 
		return pout.release();
		*/
		goto RAW_DEAL;
		
	}
	/* liupengc �ж� ·�ɵ�ֵ�Ƿ���2000������  ��0 ��ʾ�ҵ�����*/
	if(check_2000_phone_and_id_ora(iRouteCode,sRouteValue,errInfo) != 0)
	{
		/* static char tmp_msg[128]; up to start!*/
		sprintf(tmp_msg,"·�ɵ�����[%s]��[UN_USER_INFO]����", sRouteValue);
		throw(appException(SX_GUOXX_CODE, tmp_msg));
	}
	/* 19:51 2012��2��24�� B�������ߺ�, ���ڲ��ڿ������е����� ����·�����ݱ�,��B1�ͷ���B1, ��B2�ͷ���B2 
	else // �̶�����B1  add by zl
	{
		utAddStr(pout, "WEB_SUFFIX", "B1");
		utAddInt(pout, "PARTITION_CODE", 20); // added for dongxiao using 
		utAddStr(pout, "NOTE", "16"); // added for dongxiao using 
		return pout.release();
	}
    */
RAW_DEAL:
	otl_nocommit_stream qRouteRule(1, sSql0, GETDB(errInfo));
	qRouteRule<<utGetInt(p, "ROUTE_TYPE");
	if(qRouteRule.eof()) throw(appException(399001000, "·�����Ͳ�����"));
	qRouteRule>>iRuleCode>>iRuleDataType>>iGroupLength;

	if(iRuleCode==11){
		sSql=sSql2;
	}else if(iRuleCode==10){
		if(iRuleDataType==11) sSql=sSql3;
		else if(iRuleDataType==10) sSql=sSql4;
		else throw(appException(399001001, "���õ�·���������ʹ���"));
	} else throw(appException(399001002, "���õ�·�ɹ������ʹ���"));
	otl_nocommit_stream qRouteInfo(1, sSql, GETDB(errInfo));
	qRouteInfo<<iRouteCode;

	if(iRuleCode==11){
		char* s=(char*) alloca(iGroupLength+1);
		memset(s,0,iGroupLength+1);
		strncpy(s,sRouteValue,iGroupLength);
		qRouteInfo<<s;
	}else{
		if(iRuleDataType==11){
			long lValue=atol(sRouteValue);
			qRouteInfo<<lValue;
		}else{
			qRouteInfo<<sRouteValue;
		}
	}
	if(qRouteInfo.eof()) throw(appException(399001003, "·�����ݲ�����"));
	/* if(qRouteInfo.eof()) throw(appException(SX_GUOXX_CODE, "·�����ݲ�����"));*/
	qRouteInfo>>pcode>>sWebSuffix>>sNote;
	utAddInt(pout, "PARTITION_CODE", pcode);
/* liupengc ����·��������ʵ�����÷�����Ϣ  ����Ҫȡ�� SX_ONLY_FOR_B
#ifdef SX_ONLY_FOR_B
    if(sWebSuffix[0]== 'A' || sWebSuffix[0]== 'a')
	{
		static char tmp_log_msg[128];
		sprintf(tmp_log_msg, "�����ݿ��в��ҵķ�������Ϊ[%s]:���Ǹ�ӵ���",sWebSuffix);
		throw(appException(SX_GUOXX_CODE, tmp_log_msg));
	}
#endif
*/
	utAddStr(pout, "WEB_SUFFIX", sWebSuffix);
	utAddStr(pout, "NOTE", sNote);

	return pout.release();

}

utype* getRouteInfoMdb(const utype* p, TCtrlInfo* errInfo)
{
	static time_t lastInit=0;
	static DCI_SQL dsql1;
	static DCI_SQL dsql2;
	static DCI_SQL dsql3;
	static DCI_SQL dsql4;
	static DCI_SQL dsql5;// liupengc check 2000
    static DCI_SQL dsql6;// liupengc check 2000

	uAutoPtr pout(uInit(10));
	DCI_SQL* dsql=NULL;
	DCI_ROW v_row;
	int iRouteCode=utGetInt(p, "ROUTE_TYPE");
	const char* sRouteValue=utGetStr(p, "ROUTE_VALUE");
	int iRuleCode=0;
	int iRuleDataType=0;
	int iGroupLength=0;

	/* liupengc ����ǲ����û�id ���� ����·��,��ô�ͷ��� B1 #### ������� ������û�����·�ɣ���ô��Ĭ�Ϸ�ʽ
	if( !(iRouteCode == SX_ID_NO_ROUTE || iRouteCode == SX_PHONE_NO_ROUTE) )
	{
		utAddStr(pout, "WEB_SUFFIX", "B1");
		utAddInt(pout, "PARTITION_CODE", 20); 
		utAddStr(pout, "NOTE", "16"); 

		return pout.release();
	}
    */


	if(GETMDBLASTCONN(errInfo)!=lastInit){//�����ַ�ʽ��ֻ֤��Ԥ����һ��sql��䣬��ֹ���Ԥ����sql�����ɵ�ʱ���˷�

		L4C_TRACE("mdb init");
		if(!GETMDB(errInfo)) return getRouteInfoOra(p, errInfo);



		if(dci_prepare_sql(GETMDB(errInfo), &dsql1, "select rule_code,route_data_type,group_length from bs_routerule_dict where  route_code=? ")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql2, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														and b.key_value = ?")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql3, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														  AND TO_NUMBER (b.key_value)<? and TO_NUMBER (b.key_value2)>? ")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql4, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														AND b.key_value<?  AND b.key_value2>?")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}
		/* �� 2000 ��������й��� */
		if(dci_prepare_sql(GETMDB(errInfo), &dsql5, "select 1 from un_user_info where ID_NO=? ")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql6, "select 1 from un_user_info where PHONE_NO=? ")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}

		lastInit=GETMDBLASTCONN(errInfo);
	}
	if(!GETMDB(errInfo)) return getRouteInfoOra(p, errInfo);

	/************ �� UN_USER_INFO ���в������� *************/
    if(iRouteCode == SX_ID_NO_ROUTE)  /* ID_NO */
    {
    	long rv_value = atol(sRouteValue);
		if(dci_bind_param(GETMDB(errInfo), &dsql5, 0, DCI_TYPE_LONG, (void*)(&rv_value))!=0)//�󶨱������м����ʺž���Ҫ���ü��Ρ�
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		if(dci_query_p(GETMDB(errInfo), &dsql5)!=0)//ִ�в�ѯ
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

		int row_s_5 = 0;
		while( dci_fetch_row_s(GETMDB(errInfo), &dsql5) ){
			row_s_5++;
		}
		if(row_s_5 != 0)
		{
			static char tmp_msg[128];
			sprintf(tmp_msg,"·�ɵ�����ID_NO=[%s]��[UN_USER_INFO]����", sRouteValue);
			throw(appException(SX_GUOXX_CODE, tmp_msg));
		}
		/* ����ʵ���������ֵ liupengc 
		else // �̶�����B1  add by zl
		{
			utAddStr(pout, "WEB_SUFFIX", "B1");
			utAddInt(pout, "PARTITION_CODE", 20); // added for dongxiao using 
			utAddStr(pout, "NOTE", "16"); // added for dongxiao using 

			return pout.release();
		}
		*/
    }
    else if(iRouteCode == SX_PHONE_NO_ROUTE)/* PHONE_NO */
	{

		if(dci_bind_param(GETMDB(errInfo), &dsql6, 0, DCI_TYPE_CHAR, (void*)(sRouteValue))!=0)//�󶨱������м����ʺž���Ҫ���ü��Ρ�
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		if(dci_query_p(GETMDB(errInfo), &dsql6)!=0)//ִ�в�ѯ
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

		int row_s_6 = 0;
		while((dci_fetch_row_s(GETMDB(errInfo), &dsql6))){
			row_s_6++;
		}
		if(row_s_6 != 0)
		{
			static char tmp_msg[128];
			sprintf(tmp_msg,"·�ɵ�����PHONE_NO=[%s]��[UN_USER_INFO]����", sRouteValue);
			throw(appException(SX_GUOXX_CODE, tmp_msg));
		}
		/* ������ʵ��ֵ���� liupengc
		else // �̶�����B1  add by zl
		{
			utAddStr(pout, "WEB_SUFFIX", "B1");
			utAddInt(pout, "PARTITION_CODE", 20); // added for dongxiao using 
			utAddStr(pout, "NOTE", "16"); // added for dongxiao using 

			return pout.release();
		}
		*/
	}
    /************* ����������Խ����Ż� *********************/
	if(dci_bind_param(GETMDB(errInfo), &dsql1, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)//�󶨱������м����ʺž���Ҫ���ü��Ρ�ע���3����α�ʾ������λ��
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if(dci_query_p(GETMDB(errInfo), &dsql1)!=0)//ִ�в�ѯ
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	while((v_row = dci_fetch_row_s(GETMDB(errInfo), &dsql1))){
		iRuleCode=atoi(v_row[0]);
		iRuleDataType=atoi(v_row[1]);
		iGroupLength=atoi(v_row[2]);
	}
	if(iRuleCode==11){
		dsql=&dsql2;
	}else if(iRuleCode==10){
		if(iRuleDataType==11) dsql=&dsql3;
		else if(iRuleDataType==10) dsql=&dsql4;
		else throw(appException(399001001, "���õ�·���������ʹ���"));
	} else throw(appException(399001002, "���õ�·�ɹ������ʹ���"));
	if(dci_bind_param(GETMDB(errInfo), dsql, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

	if(iRuleCode==11){
		char* s=(char*) alloca(iGroupLength+1);
		memset(s,0,iGroupLength+1);
		strncpy(s,sRouteValue,iGroupLength);
		if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_CHAR, (void*)s)!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	}else{
		if(iRuleDataType==11){
			long lValue=atol(sRouteValue);
			if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_LONG, (void*)(&lValue))!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_bind_param(GETMDB(errInfo), dsql, 2, DCI_TYPE_LONG, (void*)(&lValue))!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		}else{
			if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_CHAR, (void*)sRouteValue)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_bind_param(GETMDB(errInfo), dsql, 2, DCI_TYPE_CHAR, (void*)sRouteValue)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		}

	}
	if(dci_query_p(GETMDB(errInfo), dsql)!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if((v_row = dci_fetch_row_s(GETMDB(errInfo), dsql))){
		utAddInt(pout, "PARTITION_CODE", atoi(v_row[0]));
/* ������ʵ��ֵ���� liupengc 
#ifdef SX_ONLY_FOR_B
    if(v_row[1][0]=='A' || v_row[1][0]=='a')
		throw(appException(SX_GUOXX_CODE, "�����ݿ��в��ҵ���A��:���Ǹ�ӵ���"));
#endif
*/

		utAddStr(pout, "WEB_SUFFIX", v_row[1]);
		utAddStr(pout, "NOTE", v_row[2]);
	}else{
		throw(appException(399001003, "·�����ݲ�����"));
	}
	return pout.release();

}


#else
/* liupengc ��֮ǰ�ϵ�·�ɷ��� */
utype* getRouteInfoOra(const utype* p, TCtrlInfo* errInfo)
{
	L4C_WARN("�ڴ����ݿ��޷�ʹ�ã�ʹ��oracle��ȡ·������");
	static bool isFirst=true;
	static const char* sSql0="select rule_code,route_data_type,group_length from bs_routerule_dict where  route_code=:ROUTE_TYPE<int> ";
	static const char* sSql2="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code and b.key_value = :ROUTE_VALUE<char[128]>";
	static const char* sSql3="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code AND TO_NUMBER (b.key_value)<:ROUTE_VALUE<long> and TO_NUMBER (b.key_value2)>:ROUTE_VALUE<long> ";
	static const char* sSql4="select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c where b.route_code = :ROUTE_TYPE<int>  AND c.partition_code = b.partition_code AND b.key_value<:ROUTE_VALUE<char[128]>  AND b.key_value2>:ROUTE_VALUE<char[128]>";
	const char* sSql=NULL;
	int pcode;
	char sWebSuffix[64]="";
	char sNote[60+1]="";
	uAutoPtr pout(uInit(10));
	int iRouteCode=utGetInt(p, "ROUTE_TYPE");
	const char* sRouteValue=utGetStr(p, "ROUTE_VALUE");
	int iRuleCode=0;
	int iRuleDataType=0;
	int iGroupLength=0;

	otl_nocommit_stream qRouteRule(1, sSql0, GETDB(errInfo));
	qRouteRule<<utGetInt(p, "ROUTE_TYPE");
	if(qRouteRule.eof()) throw(appException(399001000, "·�����Ͳ�����"));
	qRouteRule>>iRuleCode>>iRuleDataType>>iGroupLength;

	if(iRuleCode==11){
		sSql=sSql2;
	}else if(iRuleCode==10){
		if(iRuleDataType==11) sSql=sSql3;
		else if(iRuleDataType==10) sSql=sSql4;
		else throw(appException(399001001, "���õ�·���������ʹ���"));
	} else throw(appException(399001002, "���õ�·�ɹ������ʹ���"));
	otl_nocommit_stream qRouteInfo(1, sSql, GETDB(errInfo));
	qRouteInfo<<iRouteCode;

	if(iRuleCode==11){
		char* s=(char*) alloca(iGroupLength+1);
		memset(s,0,iGroupLength+1);
		strncpy(s,sRouteValue,iGroupLength);
		qRouteInfo<<s;
	}else{
		if(iRuleDataType==11){
			long lValue=atol(sRouteValue);
			qRouteInfo<<lValue;
		}else{
			qRouteInfo<<sRouteValue;
		}
	}
	if(qRouteInfo.eof()) throw(appException(399001003, "·�����ݲ�����"));
	qRouteInfo>>pcode>>sWebSuffix>>sNote;
	utAddInt(pout, "PARTITION_CODE", pcode);
	utAddStr(pout, "WEB_SUFFIX", sWebSuffix);
	utAddStr(pout, "NOTE", sNote);

	return pout.release();

}

utype* getRouteInfoMdb(const utype* p, TCtrlInfo* errInfo)
{
	static time_t lastInit=0;
	static DCI_SQL dsql1;
	static DCI_SQL dsql2;
	static DCI_SQL dsql3;
	static DCI_SQL dsql4;
	uAutoPtr pout(uInit(10));
	DCI_SQL* dsql=NULL;
	DCI_ROW v_row;
	int iRouteCode=utGetInt(p, "ROUTE_TYPE");
	const char* sRouteValue=utGetStr(p, "ROUTE_VALUE");
	int iRuleCode=0;
	int iRuleDataType=0;
	int iGroupLength=0;

	if(GETMDBLASTCONN(errInfo)!=lastInit){//�����ַ�ʽ��ֻ֤��Ԥ����һ��sql��䣬��ֹ���Ԥ����sql�����ɵ�ʱ���˷�

		L4C_TRACE("mdb init");
		if(!GETMDB(errInfo)) return getRouteInfoOra(p, errInfo);

		if(dci_prepare_sql(GETMDB(errInfo), &dsql1, "select rule_code,route_data_type,group_length from bs_routerule_dict where  route_code=? ")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql2, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														and b.key_value = ?")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql3, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														  AND TO_NUMBER (b.key_value)<? and TO_NUMBER (b.key_value2)>? ")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}
		if(dci_prepare_sql(GETMDB(errInfo), &dsql4, "select c.partition_code, c.web_suffix,b.note from   bs_routedata_dict b, bs_partitioncode_dict c \
														where b.route_code = ?  AND c.partition_code = b.partition_code \
														AND b.key_value<?  AND b.key_value2>?")!=0){//Ԥ����sql��䡣�󶨱������ʺŴ���
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));//�ڴ����ݿ�Ĵ��������305��ʼ
		}
		lastInit=GETMDBLASTCONN(errInfo);
	}
	if(!GETMDB(errInfo)) return getRouteInfoOra(p, errInfo);
	if(dci_bind_param(GETMDB(errInfo), &dsql1, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)//�󶨱������м����ʺž���Ҫ���ü��Ρ�ע���3����α�ʾ������λ��
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if(dci_query_p(GETMDB(errInfo), &dsql1)!=0)//ִ�в�ѯ
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	while((v_row = dci_fetch_row_s(GETMDB(errInfo), &dsql1))){
		iRuleCode=atoi(v_row[0]);
		iRuleDataType=atoi(v_row[1]);
		iGroupLength=atoi(v_row[2]);
	}
	if(iRuleCode==11){
		dsql=&dsql2;
	}else if(iRuleCode==10){
		if(iRuleDataType==11) dsql=&dsql3;
		else if(iRuleDataType==10) dsql=&dsql4;
		else throw(appException(399001001, "���õ�·���������ʹ���"));
	} else throw(appException(399001002, "���õ�·�ɹ������ʹ���"));
	if(dci_bind_param(GETMDB(errInfo), dsql, 0, DCI_TYPE_INT, (void*)(&iRouteCode))!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));

	if(iRuleCode==11){
		char* s=(char*) alloca(iGroupLength+1);
		memset(s,0,iGroupLength+1);
		strncpy(s,sRouteValue,iGroupLength);
		if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_CHAR, (void*)s)!=0)
			throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	}else{
		if(iRuleDataType==11){
			long lValue=atol(sRouteValue);
			if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_LONG, (void*)(&lValue))!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_bind_param(GETMDB(errInfo), dsql, 2, DCI_TYPE_LONG, (void*)(&lValue))!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		}else{
			if(dci_bind_param(GETMDB(errInfo), dsql, 1, DCI_TYPE_CHAR, (void*)sRouteValue)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
			if(dci_bind_param(GETMDB(errInfo), dsql, 2, DCI_TYPE_CHAR, (void*)sRouteValue)!=0)
				throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
		}

	}
	if(dci_query_p(GETMDB(errInfo), dsql)!=0)
		throw(appException(305*1000000+100000+GETMDB(errInfo)->eno, GETMDB(errInfo)->error));
	if((v_row = dci_fetch_row_s(GETMDB(errInfo), dsql))){
		utAddInt(pout, "PARTITION_CODE", atoi(v_row[0]));
		utAddStr(pout, "WEB_SUFFIX", v_row[1]);
		utAddStr(pout, "NOTE", v_row[2]);
	}else{
		/*throw(appException(399001003, "·�����ݲ�����")); liupengc */
                return getRouteInfoOra(p, errInfo);
	}
	return pout.release();

}

#endif

utype* getRouteInfo(const utype* p, TCtrlInfo* errInfo)
{
	return getRouteInfoMdb(p, errInfo);
}


utype* getSysdateTest(const utype* p, TCtrlInfo* errInfo)
{
	/*char *sql_str = "select to_char(sysdate,'YYYYMMDDHH24MISS') DT  from dual;";*/
	char dt[32] = {0};
	/*otl_nocommit_stream qQry(1, sql_str, GETDB(errInfo));
	qQry>>dt;*/
	uAutoPtr pout(uInit(1));
	utAddStr(pout, "DT", "20121231010203");
	return pout.release();
}


