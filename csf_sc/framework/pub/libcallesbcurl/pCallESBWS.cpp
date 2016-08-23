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

extern const char* cfgGetStr(const char* maintag, const char* subtag);                      


extern "C" utype* pCallESBWS(const utype * inParam, char *url, int conn_timeout, int recv_timeout)
{
    int ret_code = 0;
    char err_msg[2048] = {0};
    size_t errmsg_len = sizeof(err_msg);
    
    //printf(">>>>>>>>test for boworker>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);    
    if( NULL==inParam )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d pCallESBWS'sinParam 不能为NULL 请检查", __FILE__,__LINE__);
        throw( appException(555100002,  err_msg) );
    }
    //printf(">>>>>>>>test for boworker>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);

    if( NULL==url || strlen(url)==0 )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d pCallESBWS'url 不能为NULL 请检查", __FILE__,__LINE__);
        throw( appException(555100002,  err_msg) );
    }
    //printf(">>>>>>>>test for boworker>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);    

	/// guanyf 2016-3-23 添加， ESB增加密码校验：
    printf(">>>>>>>>test for pCallESBWS>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);
    uAutoPtr   in(utClone(inParam));
	const char *username = cfgGetStr("CALL_ESB_API", "USERNAME");
    const char *password = cfgGetStr("CALL_ESB_API", "PASSWORD");
    const char *channelid = cfgGetStr("CALL_ESB_API", "CHANNEL_ID");
	if(username != NULL && username[0] != 0 && password != NULL && password[0] != 0){
        utype *header = NULL;
        if(utFind(in, "HEADER") != UPOS_END){
            header = (utype *)utGetStruct(in, "HEADER");
            UPOS pos_name = utFind(header, "USERNAME");
            if(pos_name == UPOS_END)
                utAddStr(header, "USERNAME", username);
            else
                utSetStr(header, pos_name, username); //已有则替换
            pos_name = utFind(header, "PASSWORD");
            if(pos_name == UPOS_END)
                utAddStr(header, "PASSWORD", password);
            else
                utSetStr(header, pos_name, password);
            pos_name = utFind(header, "CHANNEL_ID");
            if(pos_name == UPOS_END)
                utAddStr(header, "CHANNEL_ID", channelid);
            else
                utSetStr(header, pos_name, channelid);

            printf("===== add username in exists header [pCallESBWS]");
        }else{
            in = uInit(2);
            header = uInit(2);
            utAddStr(header, "USERNAME", username);
            utAddStr(header, "PASSWORD", password);
            utAddStr(header, "CHANNEL_ID", channelid);
            utAddStruct(in, "HEADER", header);
            utAddStruct(in, "BODY", utClone(inParam));  //!!! clone twice
            printf("===== add username in new header [pCallESBWS]");
        }
	}

    char *inmsg = NULL;
    inmsg = uUType2Xml(in,"ROOT");
    
    if(inmsg == NULL)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d 将 utype结构转换成 xml 失败 uUType2Xml 返回NULL", __FILE__,__LINE__);
        throw( appException(555100003,  err_msg) );
    }
    char *outmsg = NULL;
    //printf(">>>>>>>>test for boworker>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);    

    ret_code = call_esb_ws(url, conn_timeout, recv_timeout, inmsg, 1, &outmsg, 1);
    //printf(">>>>>>>>test for boworker>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);    

    free(inmsg);
    inmsg = NULL;
    //printf(">>>>>>>>test for boworker>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);    

    if(ret_code !=0 )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d 调用[%s]失败 错误信息:%s", __FILE__,__LINE__, url, outmsg);
        free(outmsg);
        outmsg = NULL;
        throw( appException(555100008,  err_msg) );
    }
    //printf(">>>>>>>>test for boworker>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);    

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
    //printf(">>>>>>>>test for boworker>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);    

    free(outmsg);
    outmsg = NULL;
    //printf(">>>>>>>>test for boworker>>>>>>>>[%s][%d]\n", __FILE__,__LINE__);    

    return u_outmsg.release();

}



extern "C" void hello()
{
    while(1)
    {
        /*
         ./demo 0 "http://172.21.1.30:51900/esbWS/services/sCustInfoValid" call_esb.txt
         <ROOT><PHONE_NO type=\"string\">15799881753</PHONE_NO></ROOT> 

        */
        /* clxml sCustInfoValid "<ROOT><PHONE_NO type=\"string\">15799881753</PHONE_NO></ROOT>" */
        uAutoPtr uptr_1(uInit(0));
        utAddStr(uptr_1, "PHONE_NO", "15799881753");
        utAddStr(uptr_1, "TEST", "中文测试");
        uAutoPtr uptr_2(uInit(0));
        char url[1024]={0};
        //strncpy(url,"http://10.204.96.24:51100/esbWS/services/WsRollbackSaleAction",sizeof(url)-1);        
        strncpy(url,"http://172.21.1.30:51900/esbWS/services/sCustInfoValid",sizeof(url)-1);
        int conn_timeout = 2;
        int recv_timeout = 3;
        try
		{
			uptr_2 = pCallESBWS(uptr_1, url, conn_timeout, recv_timeout);
		}
		catch(appException e)
		{
			printf("call esb failed: %s", e.what());
			exit(9);
		}
        char *outmsg = uUType2Xml(uptr_2, "ROOT");
        if(outmsg == NULL)
        {
            exit(1);
        }
        printf("call esb[%s] return[%s]\n", url, outmsg);
        free(outmsg);
        outmsg = NULL;
        //sleep(10000);
        break;
        usleep(100000);
    }
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
        utAddStr(uptr_1, "TEST", "TEST");
        uAutoPtr uptr_2(uInit(0));
        char url[1024]={0};
        // call lvhy new ws: strncpy(url,"http://172.21.1.30:51900/esbWS/services/sCustInfoValid",sizeof(url)-1);
        //strncpy(url,"http://10.204.96.24:51100/esbWS/services/WsRollbackSaleAction",sizeof(url)-1);
        strncpy(url,"http://172.21.1.30:51900/esbWS/services/sCustInfoValid",sizeof(url)-1);
        int conn_timeout = 2;
        int recv_timeout = 3;
		try
		{
			uptr_2 = pCallESBWS(uptr_1, url, conn_timeout, recv_timeout);
        }
		catch(appException e)
		{
			printf("call esb failed: %s", e.what());
			exit(9);
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
        usleep(100000);
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
山西测试环境编译的时候：
xlc++_r -q64 -g -D__ESBAPITEST__ -I/crmtux1/run/framework/pub/utype -o pCallESBWS pCallESBWS.cpp ./utype/utype.cpp ./utype/xs.cpp -lpthread   -L./esb_cli -lesbgsoap -liconv
                            
*/


