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
    url : ����esb��url��ַ;
    conn_timeout �� SA����ESB�����ӳ�ʱʱ������,0��ʾ�޳�ʱʱ�䣻
    recv_timeout �� SA����ESB�Ľ��ܳ�ʱʱ�����ã�����ڹ涨��ʱ���ڣ�ESBû�з��ؽ������ʱ��0��ʾ�޳�ʱʱ��
���Σ�
    ��������£������÷���SB���ص�utype�ṹָ�룻
    �쳣����£��׳��쳣 appException �� uException��
                appException �� ��ʾ��ESB�������쳣��Ϣ��
                uException �� ��ʾ�ڴ洢utype�ṹ��xml �� utype ת�����쳣;

*/

extern "C" int call_esb_ws(char *url, int conn_timeout, int recv_timeout,
                      char *inmsg, int need2utf, char **outmsg, int need2gbk);


utype* pCallESBWS(const utype * inParam, char *url, int conn_timeout, int recv_timeout)
{
    int ret_code = 0;
    char err_msg[2048] = {0};
    size_t errmsg_len = sizeof(err_msg);
    
        
    if( NULL==inParam )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d pCallESBWS'sinParam ����ΪNULL ����", __FILE__,__LINE__);
        throw( appException(555100002,  err_msg) );
    }
    
    if( NULL==url || strlen(url)==0 )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d pCallESBWS'url ����ΪNULL ����", __FILE__,__LINE__);
        throw( appException(555100002,  err_msg) );
    }
    
    char *inmsg = NULL;
    inmsg = uUType2Xml(inParam,"ROOT");
    
    if(inmsg == NULL)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d �� utype�ṹת���� xml ʧ�� uUType2Xml ����NULL", __FILE__,__LINE__);
        throw( appException(555100003,  err_msg) );
    }
    char *outmsg = NULL;
    ret_code = call_esb_ws(url, conn_timeout, recv_timeout, inmsg, 1, &outmsg, 1);
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
    uAutoPtr u_outmsg(uInit(0));
    try
    {
        u_outmsg = uXml2Utype(outmsg);
    }
    catch(...)
    {
        free(outmsg);
        outmsg = NULL;
        throw;
    }
    
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
        /* clxml sCustInfoValid "<ROOT><PHONE_NO type=\"string\">15799881753</PHONE_NO></ROOT>" */
        uAutoPtr uptr_1(uInit(0));
        utAddStr(uptr_1, "PHONE_NO", "15799881753");
        utAddStr(uptr_1, "TEST", "���Ĳ���");
        uAutoPtr uptr_2(uInit(0));
        char url[1024]={0};
        strncpy(url,"http://172.21.1.30:51900/esbWS/services/sCustInfoValid",sizeof(url)-1);
        
        int conn_timeout = 2;
        int recv_timeout = 3;
        
        try{
            uptr_2 = pCallESBWS(uptr_1, url, conn_timeout, recv_timeout);
        }
        catch (appException& appErr)
        {
            printf("������÷����쳣 appException : %s\n", appErr.what());
        }
        
        char *outmsg = uUType2Xml(uptr_2, "ROOT");
        if(outmsg == NULL)
        {
            exit(1);
        }
        printf("call esb[%s] return[%s]\n", url, outmsg);
        free(outmsg);
        outmsg = NULL;
        break;
        usleep(100);
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

g++ -m64 -g -D__ESBAPITEST__ -I/tp/esb/csf/run/framework/pub/utype -o pCallESBWS pCallESBWS.cpp -lpthread -L./esb_cli -lesbgsoap -L/tp/esb/csf/run/solib  -lutype  


*/


