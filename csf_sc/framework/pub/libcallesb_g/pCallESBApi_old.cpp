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
    service_name ：被调用服务SB的名称，需要和发布在ESB上的服务名称对应；
    route_key ：SA调用SB的路由类型，如果传 NULL，则采用CSF保存的路由类型；
    route_value ： SA调用SB的路由值，如果 route_key 不为NULL，那么SA调用SB将采用route_key和route_value进行路由
    call_type ：SA调用SB的方式，非0为rest调用；0表示soap调用；
    conn_timeout ： SA调用ESB的连接超时时间设置,0表示无超时时间；
    recv_timeout ： SA调用ESB的接受超时时间设置，如果在规定的时间内，ESB没有返回结果，则超时，0表示无超时时间
出参：
    正常情况下：被调用服务SB返回的utype结构指针；
    异常情况下：抛出异常 appException 和 uException；
                appException ： 表示和ESB交互的异常信息；
                uException ： 表示在存储utype结构，或者utype结构和xml，json转换的时候出现的异常

注意事项：
            需要在 crm.cfg 配置以下项,
            需要根据具体应用的情况，配置池ID对应的负载的IP地址和端口，用于在程序中自动生成调用服务的URL地址；
            CHANNEL_ID 为SA调用SB时,防止ESB进行校验 需要和ESB确认一个固定的  CHANNEL_ID 用于内部的服务调用;
            [CALL_ESB_API]
            CHANNEL_ID=12
            POOL_ID.10=172.21.1.30:51900
            POOL_ID.11=172.21.1.31:51900
            POOL_ID.12=172.21.1.32:51900
            
        例如： 营业池ID为10，对应的负载均衡地址为，172.21.1.30:51900，
        那么需要配置： POOL_ID.10=172.21.1.30:51900
        pCallESBApi 会根据 call_type 的值，来生成对应的url地址：
        比如，如果为rest调用模式，调用的服务名称为 sCustInfoValid （是发布在ESB上的服务名称），
        那么pCallESBApi会自动拼成：http://172.21.1.95:51900/esbWS/rest/sCustInfoValid  进行服务的调用；
              如果为soap调用模式，调用的服务名称为 sCustInfoValid （是发布在ESB上的服务名称），
        那么pCallESBApi会自动拼成：http://172.21.1.95:51900/esbWS/services/sCustInfoValid  进行服务的调用；
        
        目前 api 只支持REST的调用，SOAP调用平均会多出10毫秒的消耗，且SOAP调用需要进行字符集转换，
        soap的调用后期再支持
        
        
*/

extern "C" int call_esb_rest(char *url,int conn_timeout, int recv_timeout,
                      char *inmsg, int need2utf, char **outmsg, int need2gbk);


extern const char* cfgGetStr(const char* maintag, const char* subtag);                      
extern utype * json2utype(const char *str);
extern char * utype2json(const utype *pu);


/*
框架服务提供的用户获取SA服务中保存的HEADER信息 其中包含了POOL_ID ROUTE_KEY ROUTE_VALUE 等值;
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
        snprintf(err_msg, errmsg_len-1, "%s:%d inParam or service_name 不能为NULL 请检查", __FILE__,__LINE__);
        throw( appException(555100002,  err_msg) );
    }
    
    const char * new_channel_id = cfgGetStr("CALL_ESB_API", "CHANNEL_ID");
    if( NULL == new_channel_id || strlen(new_channel_id)==0)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d 获取 crm.cfg 中 section为[CALL_ESB_API]的配置:CHANNEL_ID 失败  请检查", __FILE__,__LINE__);
        throw( appException(555100003,  err_msg) );
    }
    
    if( route_key!=NULL && NULL==route_value )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d 路由类型非0情况下 请输入路由的值", __FILE__,__LINE__);
        throw( appException(555100004,  err_msg) );
    }
    
#ifndef __ESBAPITEST__ 
    const utype * ptr_src_header = CSF_getInputHeader();
    if( NULL==ptr_src_header)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d 获取原始服务的包头信息为NULL 请检查", __FILE__,__LINE__);
        throw( appException(555100001,  err_msg) );
    }
    uAutoPtr uptr_header(utClone(ptr_src_header));
#else
    // 测试的时候使用 使用模拟的返回包头信息
    uAutoPtr   uptr_header(CSF_getInputHeader());
#endif 

    
    UPOS pos_name;
    
    /* 设置新的 渠道ID */
    pos_name = utFind(uptr_header,"CHANNEL_ID");
    if(pos_name!=UPOS_END)
    {
        utSetStr(uptr_header,pos_name,new_channel_id);
    }
    else
    {
        utAddStr(uptr_header,"CHANNEL_ID",new_channel_id);
    }
    
    /* 设置新的 路由类型 */
    if(route_key != NULL)
    {
        utype *ptmp = NULL;
        try
        {
            ptmp = const_cast<utype*>(utGetStruct(uptr_header,"ROUTING"));
        }
        catch (appException& appErr)
        {
            printf("获取服务入参中的 HEADER.ROUTING 失败:%s\n", appErr.what());
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
    
    /* 根据 pool_id 拼接 服务的url */
    char *str_pool_id = utGetStr(uptr_header, "POOL_ID");
    if(str_pool_id == NULL)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d 服务的POOL_ID值为NULL 请设置POOL_ID的值", __FILE__,__LINE__);
        throw( appException(555100005,  err_msg) );
    }
    
    char pool_find[128] = {0};
    sprintf(pool_find, "POOL_ID.%s", str_pool_id);
    pool_find[127] = 0;
    const char *ptr_tmp = cfgGetStr("CALL_ESB_API", pool_find);
    if(ptr_tmp == NULL || strlen(ptr_tmp)==0    )
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d crm.cfg 中section为[CALL_ESB_API]的值 %s 没有配置请检查", __FILE__,__LINE__, pool_find);
        throw( appException(555100006,  err_msg) );
    }
    char url[1024] = {0};
    // todo: 需要加上对 call_type 的判断 http://172.21.1.30:51900/esbWS/rest/sCustInfoValid  
    // 目前支持 rest 报文的格式;
    sprintf(url, "http://%s/esbWS/rest/%s", ptr_tmp, service_name);
    
    /* 生成调用 esb 的json报文 */
    uAutoPtr   uptr_hb(uInit(1));
    uAutoPtr   uptr_body(utClone(inParam));
    utAddStruct(uptr_hb,"HEADER",uptr_header.release());
    utAddStruct(uptr_hb,"BODY",    uptr_body.release());
    
    char *inmsg = utype2json(uptr_hb);
    if(inmsg == NULL)
    {
        memset(err_msg, 0, sizeof(errmsg_len));
        snprintf(err_msg, errmsg_len-1, "%s:%d 将 utype结构转换成json失败 utype2json 返回NULL", __FILE__,__LINE__);
        throw( appException(555100007,  err_msg) );
    }
    char *outmsg = NULL;
    
    ret_code = call_esb_rest(url, conn_timeout, recv_timeout, inmsg, 0, &outmsg, 0);
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
    
    uAutoPtr u_outmsg(json2utype(outmsg));
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
        uAutoPtr uptr_1(uInit(0));
        utAddStr(uptr_1, "PHONE_NO", "15799881753");
        utAddStr(uptr_1, "TEST", "中文测试");
        uAutoPtr uptr_2(uInit(0));
        try
        {
            /* 需要传路由值的类型 */
            uptr_2 = pCallESBApi(uptr_1, "sCustInfoValid", "10", "15799881753", 0, 2, 3);
            char *xmlstr = uUType2Xml(uptr_2,"ROOT");
            printf("调用服务的返回结果为:%s\n", xmlstr);
            free(xmlstr);
            xmlstr = NULL;
            
            /* 不需要传路由值的情况 
            uptr_2 = pCallESBApi(uptr_1, "sCustInfoValid", NULL, "", 0, 5 3);
            char *xmlstr = uUType2Xml(uptr_2,"ROOT");
            printf("调用服务的返回结果为:%s\n", xmlstr);
            free(xmlstr);
            xmlstr = NULL;
            */
        }
        catch (appException& appErr)
        {
            printf("服务调用发生异常 appException : %s\n", appErr.what());
        }
        catch (std::exception& err)
        {
            printf("服务调用发生异常 exception : %s\n", err.what());
        }
        catch(...)
        {
            printf("服务调用发生异常\n");
        }
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
g++ -m64 -g -D__ESBAPITEST__ -I/tp/esb/csf/run/framework/pub/publog -I/tp/esb/csf/run/framework/pub/utype -o pCallESBApi pCallESBApi.cpp -lpthread -L./esb_cli -lesbgsoap -L/tp/esb/csf/run/solib -lcfg -lutype -lpublog -lDesMac

执行执行可以调用服务;

通过服务进行调用的实例:

在 sTime 中进行

time clxml sQTime '{"ROOT":{"HEADER":{"POOL_ID":"11","DB_ID":"","ENV_ID":"","CHANNEL_ID":"02","ROUTING":{"ROUTE_KEY":"","ROUTE_VALUE":""}},"BODY":{"PHONE_NO":"15799881753","TEST":"#######json json 中文测试  #####"}}}'

*/





/*
{"ROOT":
    {"HEADER":{ "POOL_ID":{2位},//必填，值可为空；池编码 字符串类型
                "DB_ID":{2位},//非必填，值可为空；数据库实例编码 字符串类型
                "ENV_ID":{8位}, //必填，值可为空；环境编码 字符串类型
                "CHANNEL_ID":{2位}, //必填，值不为空；渠道标识 字符串类型
                "CONTACT_ID" :{25位}, //必填，值不为空；服务访问流水号 字符串类型
                "USERNAME":{?位}, //用户口令安全验证时必填，值不为空；用户名 字符串类型
                "PASSWORD":{?位}, //用户口令安全验证时必填，值不为空；口令 字符串类型
                "ENDUSRLOGINID":{32位}, //session验证时必填，值不为空；32位随机码 字符串类型
                "ENDUSRIP":{?位}, //终端用户IP记录时必填，值可不为空；终端用户的IP地址 字符串类型
                "ROUTING":{
                   "ROUTE_KEY":{},//必填，值不为空；//路由类型  字符串
                   "ROUTE_VALUE":{}//必填，值不为空；//路由值  字符串类型
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

