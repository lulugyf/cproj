#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

#include <string>
#include "utype.h"

/*
����������
    ����NG����֮��ĵ��ã�eg��tuxedo���� SA ���÷�����ESB�ϵ�tuxedo���� SB��
    pCallESBApi : SA ֱ�ӵ�����ESB�����ķ���SB�� rest �� ws ����
��Σ�
    inParam �������÷���SB�����utype��ֵ��
    service_name �������÷���SB�����ƣ���Ҫ�ͷ�����ESB�ϵķ������ƶ�Ӧ��
    route_key ��SA����SB��·�����ͣ������ NULL�������CSF�����·�����ͣ�
    route_value �� SA����SB��·��ֵ����� route_key ��ΪNULL����ôSA����SB������route_key��route_value����·��
    call_type ��SA����SB�ķ�ʽ����0Ϊrest���ã�0��ʾsoap���ã�
    conn_timeout �� SA����ESB�����ӳ�ʱʱ������,0��ʾ�޳�ʱʱ�䣻
    recv_timeout �� SA����ESB�Ľ��ܳ�ʱʱ�����ã�����ڹ涨��ʱ���ڣ�ESBû�з��ؽ������ʱ��0��ʾ�޳�ʱʱ��
���Σ�
    ��������£������÷���SB���ص�utype�ṹָ�룻
    �쳣����£��׳��쳣 appException �� uException��
                appException �� ��ʾ��ESB�������쳣��Ϣ��
                uException �� ��ʾ�ڴ洢utype�ṹ������utype�ṹ��xml��jsonת����ʱ����ֵ��쳣

ע�����
            ��Ҫ�� crm.cfg ����������,
            ��Ҫ���ݾ���Ӧ�õ���������ó�ID��Ӧ�ĸ��ص�IP��ַ�Ͷ˿ڣ������ڳ������Զ����ɵ��÷����URL��ַ��
            CHANNEL_ID ΪSA����SBʱ,��ֹESB����У�� ��Ҫ��ESBȷ��һ���̶���  CHANNEL_ID �����ڲ��ķ������;
            [CALL_ESB_API]
            CHANNEL_ID=12
            POOL_ID.10=172.21.1.30:51900
            POOL_ID.11=172.21.1.31:51900
            POOL_ID.12=172.21.1.32:51900
            
        ���磺 Ӫҵ��IDΪ10����Ӧ�ĸ��ؾ����ַΪ��172.21.1.30:51900��
        ��ô��Ҫ���ã� POOL_ID.10=172.21.1.30:51900
        pCallESBApi ����� call_type ��ֵ�������ɶ�Ӧ��url��ַ��
        ���磬���Ϊrest����ģʽ�����õķ�������Ϊ sCustInfoValid ���Ƿ�����ESB�ϵķ������ƣ���
        ��ôpCallESBApi���Զ�ƴ�ɣ�http://172.21.1.95:51900/esbWS/rest/sCustInfoValid  ���з���ĵ��ã�
              ���Ϊsoap����ģʽ�����õķ�������Ϊ sCustInfoValid ���Ƿ�����ESB�ϵķ������ƣ���
        ��ôpCallESBApi���Զ�ƴ�ɣ�http://172.21.1.95:51900/esbWS/services/sCustInfoValid  ���з���ĵ��ã�
        
        Ŀǰ api ֻ֧��REST�ĵ��ã�SOAP����ƽ������10��������ģ���SOAP������Ҫ�����ַ���ת����
        soap�ĵ��ú�����֧��
        
        
*/

extern "C" int call_esb_rest(char *url,int conn_timeout, int recv_timeout,
                      char *inmsg, int need2utf, char **outmsg, int need2gbk);


extern const char* cfgGetStr(const char* maintag, const char* subtag);                      
extern utype * json2utype(const char *str);
extern char * utype2json(const utype *pu);


/*
��ܷ����ṩ���û���ȡSA�����б����HEADER��Ϣ ���а�����POOL_ID ROUTE_KEY ROUTE_VALUE ��ֵ;
*/

#ifdef __ESBAPITEST__

utype * CSF_getInputHeader()
{
    uAutoPtr uptr_1(uInit(0));
    utAddStr(uptr_1, "POOL_ID", "11");
    utAddStr(uptr_1, "DB_ID", "");
    utAddStr(uptr_1, "ENV_ID", "");
    utAddStr(uptr_1, "CHANNEL_ID", "02");
    
    uAutoPtr uptr_route(uInit(0));
    utAddStr(uptr_route, "ROUTE_KEY", "10");
    utAddStr(uptr_route, "ROUTE_VALUE", "15799881753");
    utAddStruct(uptr_1, "ROUTING", uptr_route.release());
    
    return uptr_1.release();    
}

#else

extern const utype *CSF_getInputHeader();

#endif


utype* pCallESBApi(const utype * inParam, const char *service_name, const char *route_key, const char * route_value, \
                         int call_type, int conn_timeout, int recv_timeout)
{
    int ret_code = 0;
    char err_msg[2048] = {0};
    size_t errmsg_len = sizeof(err_msg);
        
    if( NULL==inParam || NULL==service_name)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d inParam or service_name ����ΪNULL ����", __FILE__,__LINE__);
        throw( appException(555100002,  err_msg) );
    }
    
    const char * new_channel_id = cfgGetStr("CALL_ESB_API", "CHANNEL_ID");
    if( NULL == new_channel_id || strlen(new_channel_id)==0)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d ��ȡ crm.cfg �� sectionΪ[CALL_ESB_API]������:CHANNEL_ID ʧ��  ����", __FILE__,__LINE__);
        throw( appException(555100003,  err_msg) );
    }
    
    if( route_key!=NULL && NULL==route_value )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d ·�����ͷ�0����� ������·�ɵ�ֵ", __FILE__,__LINE__);
        throw( appException(555100004,  err_msg) );
    }
    
#ifndef __ESBAPITEST__ 
    const utype * ptr_src_header = CSF_getInputHeader();
    if( NULL==ptr_src_header)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d ��ȡԭʼ����İ�ͷ��ϢΪNULL ����", __FILE__,__LINE__);
        throw( appException(555100001,  err_msg) );
    }
    uAutoPtr uptr_header(utClone(ptr_src_header));
#else
    // ���Ե�ʱ��ʹ�� ʹ��ģ��ķ��ذ�ͷ��Ϣ
    uAutoPtr   uptr_header(CSF_getInputHeader());
#endif 

    
    UPOS pos_name;
    
    /* �����µ� ����ID */
    pos_name = utFind(uptr_header,"CHANNEL_ID");
    if(pos_name!=UPOS_END)
    {
        utSetStr(uptr_header,pos_name,new_channel_id);
    }
    else
    {
        utAddStr(uptr_header,"CHANNEL_ID",new_channel_id);
    }
    
    /* �����µ� ·������ */
    if(route_key != NULL)
    {
        utype *ptmp = NULL;
        try
        {
            ptmp = const_cast<utype*>(utGetStruct(uptr_header,"ROUTING"));
        }
        catch (appException& appErr)
        {
            printf("��ȡ��������е� HEADER.ROUTING ʧ��:%s\n", appErr.what());
            throw;
        }
        pos_name = utFind(ptmp,"ROUTE_KEY");
        if(pos_name != UPOS_END)
        {
            utSetStr(ptmp, pos_name, route_key);
        }
        else
        {
            utAddStr(ptmp,"ROUTE_KEY",route_key);
        }
        
        pos_name = utFind(ptmp,"ROUTE_VALUE");
        if(pos_name != UPOS_END)
        {
            utSetStr(ptmp, pos_name, route_value);
        }
        else
        {
            utAddStr(ptmp,"ROUTE_VALUE",route_value);
        }
        
    }
    
    /* ���� pool_id ƴ�� �����url */
    char *str_pool_id = utGetStr(uptr_header, "POOL_ID");
    if(str_pool_id == NULL)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d �����POOL_IDֵΪNULL ������POOL_ID��ֵ", __FILE__,__LINE__);
        throw( appException(555100005,  err_msg) );
    }
    
    char pool_find[128] = {0};
    sprintf(pool_find, "POOL_ID.%s", str_pool_id);
    pool_find[127] = 0;
    const char *ptr_tmp = cfgGetStr("CALL_ESB_API", pool_find);
    if(ptr_tmp == NULL || strlen(ptr_tmp)==0    )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d crm.cfg ��sectionΪ[CALL_ESB_API]��ֵ %s û����������", __FILE__,__LINE__, pool_find);
        throw( appException(555100006,  err_msg) );
    }
    char url[1024] = {0};
    // todo: ��Ҫ���϶� call_type ���ж� http://172.21.1.30:51900/esbWS/rest/sCustInfoValid  
    // Ŀǰ֧�� rest ���ĵĸ�ʽ;
    sprintf(url, "http://%s/esbWS/rest/%s", ptr_tmp, service_name);
    
    /* ���ɵ��� esb ��json���� */
    uAutoPtr   uptr_hb(uInit(1));
    uAutoPtr   uptr_body(utClone(inParam));
    utAddStruct(uptr_hb,"HEADER",uptr_header.release());
    utAddStruct(uptr_hb,"BODY",    uptr_body.release());
    
    char *inmsg = utype2json(uptr_hb);
    if(inmsg == NULL)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d �� utype�ṹת����jsonʧ�� utype2json ����NULL", __FILE__,__LINE__);
        throw( appException(555100007,  err_msg) );
    }
    char *outmsg = NULL;
    
    ret_code = call_esb_rest(url, conn_timeout, recv_timeout, inmsg, 0, &outmsg, 0);
    free(inmsg);
    inmsg = NULL;
    if(ret_code !=0 )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d ����[%s]ʧ�� ������Ϣ:%s", __FILE__,__LINE__, url, outmsg);
        
        free(outmsg);
        outmsg = NULL;
        throw( appException(555100008,  err_msg) );
    }
    
    uAutoPtr u_outmsg(json2utype(outmsg));
    free(outmsg);
    outmsg = NULL;
    return u_outmsg.release();
    
}

#ifdef __ESBAPITEST__
int main()
{
    //�Է�������ѹ�� �۲�˳�����ڴ��������;
    while(1)
    {
        uAutoPtr uptr_1(uInit(0));
        utAddStr(uptr_1, "PHONE_NO", "15799881753");
        utAddStr(uptr_1, "TEST", "���Ĳ���");
        uAutoPtr uptr_2(uInit(0));
        try
        {
            /* ��Ҫ��·��ֵ������ */
            uptr_2 = pCallESBApi(uptr_1, "sCustInfoValid", "10", "15799881753", 0, 2, 3);
            char *xmlstr = uUType2Xml(uptr_2,"ROOT");
            printf("���÷���ķ��ؽ��Ϊ:%s\n", xmlstr);
            free(xmlstr);
            xmlstr = NULL;
            
            /* ����Ҫ��·��ֵ����� 
            uptr_2 = pCallESBApi(uptr_1, "sCustInfoValid", NULL, "", 0, 5 3);
            char *xmlstr = uUType2Xml(uptr_2,"ROOT");
            printf("���÷���ķ��ؽ��Ϊ:%s\n", xmlstr);
            free(xmlstr);
            xmlstr = NULL;
            */
        }
        catch (appException& appErr)
        {
            printf("������÷����쳣 appException : %s\n", appErr.what());
        }
        catch (std::exception& err)
        {
            printf("������÷����쳣 exception : %s\n", err.what());
        }
        catch(...)
        {
            printf("������÷����쳣\n");
        }
        break;
        usleep(100000);
    }
    
    
    
    return 0;
}
#endif



/*
��ҵ���ٵ��õ�ʱ��,ֻ��Ҫ��ҵ����Ϣ,����Ҫ��ע��Ӧ�İ�ͷ�ṹ;
"PHONE_NO":"15799881753"

����ͷ�Ĳ���:
{"ROOT":{"HEADER":{"POOL_ID":"11","DB_ID":"","ENV_ID":"","CHANNEL_ID":"02","ROUTING":{"ROUTE_KEY":"","ROUTE_VALUE":""}},"BODY":{"PHONE_NO":"15799881753","TEST":"#######json json ���Ĳ���  #####"}}}
*/



/*

ͨ����Ԫ�����������е���:
����ķ���:
�������Ե����:
g++ -m64 -g -D__ESBAPITEST__ -I/tp/esb/csf/run/framework/pub/publog -I/tp/esb/csf/run/framework/pub/utype -o pCallESBApi pCallESBApi.cpp -lpthread -L./esb_cli -lesbgsoap -L/tp/esb/csf/run/solib -lcfg -lutype -lpublog -lDesMac

ִ��ִ�п��Ե��÷���;

ͨ��������е��õ�ʵ��:

�� sTime �н���

time clxml sQTime '{"ROOT":{"HEADER":{"POOL_ID":"11","DB_ID":"","ENV_ID":"","CHANNEL_ID":"02","ROUTING":{"ROUTE_KEY":"","ROUTE_VALUE":""}},"BODY":{"PHONE_NO":"15799881753","TEST":"#######json json ���Ĳ���  #####"}}}'

*/





/*
{"ROOT":
    {"HEADER":{ "POOL_ID":{2λ},//���ֵ��Ϊ�գ��ر��� �ַ�������
                "DB_ID":{2λ},//�Ǳ��ֵ��Ϊ�գ����ݿ�ʵ������ �ַ�������
                "ENV_ID":{8λ}, //���ֵ��Ϊ�գ��������� �ַ�������
                "CHANNEL_ID":{2λ}, //���ֵ��Ϊ�գ�������ʶ �ַ�������
                "CONTACT_ID" :{25λ}, //���ֵ��Ϊ�գ����������ˮ�� �ַ�������
                "USERNAME":{?λ}, //�û����ȫ��֤ʱ���ֵ��Ϊ�գ��û��� �ַ�������
                "PASSWORD":{?λ}, //�û����ȫ��֤ʱ���ֵ��Ϊ�գ����� �ַ�������
                "ENDUSRLOGINID":{32λ}, //session��֤ʱ���ֵ��Ϊ�գ�32λ����� �ַ�������
                "ENDUSRIP":{?λ}, //�ն��û�IP��¼ʱ���ֵ�ɲ�Ϊ�գ��ն��û���IP��ַ �ַ�������
                "ROUTING":{
                   "ROUTE_KEY":{},//���ֵ��Ϊ�գ�//·������  �ַ���
                   "ROUTE_VALUE":{}//���ֵ��Ϊ�գ�//·��ֵ  �ַ�������
                 }
              },
     "BODY":{"REQUEST_INFO": {
			  "OPR_INFO": {
				"REGION_ID": 11,
				"CHANNEL_TYPE": "0001",
				"LOGIN_NO": "Y18600IVR",
				"LOGIN_PWD": "123",
				"IP_ADDRESS": "127.0.0.1",
				"GROUP_ID": 100000,
				"CONTACT_ID": 100000,
				"OP_CODE": "1234"
			},
			"BUSI_INFO_LIST": {
				"BUSI_INFO": {
					"PROD_ID": "CPX004"
				}
		  }
		  }
     }
  }
}

*/

