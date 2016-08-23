#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

#include <string>
#include "utype.h"

/*
功能描述：
    用于NG服务之间的调用，eg：tuxedo服务 SA 调用发布在ESB上的tuxedo服务 SB；
    pCallESBApi : SA 直接调用在ESB发布的服务SB的 rest 和 ws 服务；
入参：
    inParam ：被调用服务SB的入参utype的值；
    url : 调用esb的url地址;
    conn_timeout ： SA调用ESB的连接超时时间设置,0表示无超时时间；
    recv_timeout ： SA调用ESB的接受超时时间设置，如果在规定的时间内，ESB没有返回结果，则超时，0表示无超时时间
出参：
    正常情况下：被调用服务SB返回的utype结构指针；
    异常情况下：抛出异常 appException 和 uException；
                appException ： 表示和ESB交互的异常信息；
                uException ： 表示在存储utype结构，xml 和 utype 转换的异常;

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
        snprintf(err_msg, errmsg_len-1, "%s:%d pCallESBWS'sinParam 不能为NULL 请检查", __FILE__,__LINE__);
        throw( appException(555100002,  err_msg) );
    }
    
    if( NULL==url || strlen(url)==0 )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d pCallESBWS'url 不能为NULL 请检查", __FILE__,__LINE__);
        throw( appException(555100002,  err_msg) );
    }
    
    char *inmsg = NULL;
    inmsg = uUType2Xml(inParam,"ROOT");
    
    if(inmsg == NULL)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d 将 utype结构转换成 xml 失败 uUType2Xml 返回NULL", __FILE__,__LINE__);
        throw( appException(555100003,  err_msg) );
    }
    char *outmsg = NULL;
    ret_code = call_esb_ws(url, conn_timeout, recv_timeout, inmsg, 1, &outmsg, 1);
    free(inmsg);
    inmsg = NULL;
    if(ret_code !=0 )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d 调用[%s]失败 错误信息:%s", __FILE__,__LINE__, url, outmsg);
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
    //对服务批量压测 观察此程序的内存增长情况;
    while(1)
    {
        /* clxml sCustInfoValid "<ROOT><PHONE_NO type=\"string\">15799881753</PHONE_NO></ROOT>" */
        uAutoPtr uptr_1(uInit(0));
        utAddStr(uptr_1, "PHONE_NO", "15799881753");
        utAddStr(uptr_1, "TEST", "中文测试");
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
            printf("服务调用发生异常 appException : %s\n", appErr.what());
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
行业部再调用的时候,只需要传业务信息,不需要关注相应的包头结构;
"PHONE_NO":"15799881753"

带包头的测试:
{"ROOT":{"HEADER":{"POOL_ID":"11","DB_ID":"","ENV_ID":"","CHANNEL_ID":"02","ROUTING":{"ROUTE_KEY":"","ROUTE_VALUE":""}},"BODY":{"PHONE_NO":"15799881753","TEST":"#######json json 中文测试  #####"}}}
*/



/*

通过单元测试用例进行调用:
编译的方法:
单独测试的情况:

g++ -m64 -g -D__ESBAPITEST__ -I/tp/esb/csf/run/framework/pub/utype -o pCallESBWS pCallESBWS.cpp -lpthread -L./esb_cli -lesbgsoap -L/tp/esb/csf/run/solib  -lutype  


*/


