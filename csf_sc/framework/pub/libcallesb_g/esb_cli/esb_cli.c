#include "esb_cli.h"
#include "soapH.h"
#include "sDynSvcSoap11Binding.nsmap"

#include "httppost.h" /*restful*/


#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <iconv.h>
#include <signal.h>




#define CALL_ESB_ERRCODE "999999"
#define __CSF_JSON_ERRMSG  "{"\
                                "\"ROOT\": {"\
                                    "\"RETURN_CODE\": %s,"\
                                    "\"RETURN_MSG\": \"%s\","\
                                    "\"USER_MSG\": \"%s\","\
                                    "\"DETAIL_MSG\": \"%s\","\
                                    "\"PROMPT_MSG\": \"\""\
                                "}"\
                            "}"

#define __CSF_XML_ERRMSG "<?xml version=\"1.0\" encoding=\"GBK\"?>"\
                          "<ROOT>"\
                            "<RETURN_CODE type=\"long\">%s</RETURN_CODE>"\
                            "<RETURN_MSG type=\"string\">%s</RETURN_MSG>"\
                            "<USER_MSG type=\"string\">%s</USER_MSG>"\
                            "<DETAIL_MSG type=\"string\">%s</DETAIL_MSG>"\
                            "<PROMPT_MSG type=\"string\"/>"\
                           "</ROOT>"
                           



#ifdef __cplusplus
extern "C" {
#endif

static void  sig_init()
{
    signal(SIGPIPE,SIG_IGN);
}

static int code_convert(char* from_charset, char* to_charset,
                        char* inbuf,  size_t inlen,
                        char* outbuf, size_t outlen)
{
    iconv_t cd;
    char** pin  = &inbuf;
    char** pout = &outbuf;

    cd = iconv_open(to_charset,from_charset);
    if(cd == (iconv_t)-1)
    {
        fprintf(stderr, "%s:%d "" iconv_open failed, errno=[%d],errmsg[%s]\n",
                        __FILE__,__LINE__,errno, strerror(errno));
        return -1;
    }
    memset(outbuf,0,outlen);
    if( iconv(cd, pin, (size_t*)(&inlen), pout, (size_t*)(&outlen)) == -1 )
    {
        fprintf(stderr, "%s:%d "" iconv failed, errno=[%d],errmsg[%s]\n",
                       __FILE__,__LINE__,errno, strerror(errno));
        iconv_close(cd);
        return -2;
    }
    iconv_close(cd);
    return 0;
}


static char* u2g(char *inbuf)
{
    size_t nOutLen = 3 * strlen(inbuf) + 512;
    char* szOut = (char*)calloc(1, nOutLen);
    if ( 0 != code_convert("UTF-8","GBK",inbuf,strlen(inbuf),szOut,nOutLen))
    {
        free(szOut);
        szOut = NULL;
    }
    return szOut;
}

static char* g2u(char *inbuf)
{
    size_t nOutLen = 3 * strlen(inbuf) + 512;
    char* szOut = (char*)calloc(1, nOutLen);
    if ( 0 != code_convert("GBK","UTF-8",inbuf,strlen(inbuf),szOut,nOutLen))
    {
        free(szOut);
        szOut = NULL;
    }
    return szOut;
}

static char *trans_code(char *from_code, char *to_code, char *from_code_str)
{
    if( (!from_code) || (!to_code) || (!from_code_str)) return NULL;
    size_t res_len = 3*strlen(from_code_str) + 512;
    char *result = (char *)calloc(1, res_len);
    if ( 0 != code_convert(from_code, to_code, 
                            from_code_str,strlen(from_code_str),
                            result,res_len) )
    {
        free(result); 
        result = NULL;
    }
    return result;
}

static void soap_get_errmsg(struct soap *soap,char *errmsg,size_t errmsg_len)
{
    if (soap_check_state(soap))
    {
        char *tmp = "Error: soap struct state not initialized";
        snprintf(errmsg,errmsg_len-1,"%s:%d call %s failed:soap struct state not initialized!", __FILE__,__LINE__,soap->endpoint);
    }
    else if (soap->error)
    { const char **c, *v = NULL, *s, *d;
        c = soap_faultcode(soap);
        if (!*c) soap_set_fault(soap);
        if (soap->version == 2) v = soap_check_faultsubcode(soap);
        s = *soap_faultstring(soap);
        d = soap_check_faultdetail(soap);
        snprintf(errmsg,errmsg_len-1,"%s:%d call %s failed:soap.error=%d %s,%s",
                  __FILE__,__LINE__,soap->endpoint, soap->error, s?s:"",*c);
    }
}

/* 将 url 作为参数输入 */
static void soap_get_errmsg_url(struct soap *soap,char *errmsg,size_t errmsg_len, char *url)
{
    if (soap_check_state(soap))
    {
        char *tmp = "Error: soap struct state not initialized";
        snprintf(errmsg,errmsg_len-1,"%s:%d call %s failed:soap struct state not initialized!", __FILE__,__LINE__,url);
    }
    else if (soap->error)
    { const char **c, *v = NULL, *s, *d;
        c = soap_faultcode(soap);
        if (!*c) soap_set_fault(soap);
        if (soap->version == 2) v = soap_check_faultsubcode(soap);
        s = *soap_faultstring(soap);
        d = soap_check_faultdetail(soap);
        snprintf(errmsg,errmsg_len-1,"%s:%d call %s failed:soap.error=%d %s,%s",
                  __FILE__,__LINE__,url, soap->error, s?s:"",*c);
    }
}



int call_esb_ws(char *url, int conn_timeout, int recv_timeout,
                      char *inmsg, int need2utf, char **outmsg, int need2gbk)
{
    sig_init();
    char errmsg[1024] = {0};
    char *tmp = NULL;
    char *inutf8 = NULL;
    size_t mylen = 0;
    int errcode = 0;
    char *urn_str = "urn:callService";
    struct soap soap;
    struct _ns1__callService req;
    struct _ns1__callServiceResponse rsp;
    soap_init1(&soap, SOAP_XML_INDENT);
    soap_set_mode(&soap,SOAP_C_UTFSTRING);
    soap.connect_timeout = conn_timeout;
    soap.recv_timeout = recv_timeout;
#ifdef MSG_NOSIGNAL
    soap.socket_flags = MSG_NOSIGNAL;  /* prevent sigpipe */
#endif
    if(inmsg == NULL || strlen(inmsg)==0)
    {
        errcode = -1; /* inmsg is null! -1*/
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call %s failed:inmsg is null!",__FILE__,__LINE__,url);
        goto error_deal;
    }
    /* convert immsg to utf-8 */
    if(need2utf)
    {
        inutf8 = g2u(inmsg);
        if(inutf8 == NULL)
        {
            errcode = -1001; 
            snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call %s failed: convert inmsg to utf8 failed",__FILE__,__LINE__,url);
            goto error_deal;
        }
    }
    else
    {
        inutf8 = strdup(inmsg);
    }
    
    req.pin = inutf8;
    soap_call___ns1__callService(&soap, url, urn_str, &req, &rsp);
    if (soap.error)
    {
        errcode = -2; /* call esb failed! -2*/
        soap_get_errmsg(&soap, errmsg, sizeof(errmsg));
        goto error_deal;
    }
    if(rsp.return_ == NULL)
    {
        errcode = -3; /* call esb ok, but esb return null! -3*/
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call %s failed:call ok but return NULL",__FILE__, __LINE__, soap.endpoint);
        goto error_deal;
    }
    if(need2gbk)
    {
        tmp = u2g(rsp.return_);
        if(tmp == NULL)
        {
            errcode = -4; /* uft-8 to gbk failed!*/
            snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call %s failed:uft-8 to gbk failed!",__FILE__, __LINE__,soap.endpoint);
            goto error_deal;
        }
        
    }
    else
    {
        tmp = strdup(rsp.return_);
    }
    *outmsg = tmp;
error_deal:
    if(errcode != 0)
    {
        *outmsg = u2g(errmsg);
        if(*outmsg == NULL)
        {
            *outmsg = (char *)calloc(1,2048);
            mylen = 2048;
            snprintf(*outmsg,mylen-1,"%s",errmsg);
        }
        
    }
    if(inutf8 !=NULL )
    {
        free(inutf8);
        inutf8 = NULL;
    }
    soap_destroy(&soap);
    soap_end(&soap);
    soap_done(&soap);
    return errcode;
}

int call_esb_rest(char *url,int conn_timeout, int recv_timeout,
                       char *inmsg, int need2utf,char **outmsg, int need2gbk)
{
  sig_init();
  char *buf = NULL;
  char *tmp = NULL;
  char *inutf8 = NULL;
  size_t len = 0;
  struct soap *soap = NULL;
  char content_type[128];
  /*char *content_type = "application/json";*/
  /* 根据need2utf的值判断是发送utf-8编码，还是发送gbk的编码  */
  printf(">>>>>> call [%s]:[%s] start.....\n", url?url:"",inmsg?inmsg:"");
  if(need2utf == 0)
  {
    strcpy(content_type, "application/json;charset=GBK");
  }
  else
  {
    strcpy(content_type, "application/json;charset=UTF-8");
  }
  
  int errcode = 0;
  char errmsg[1024] = {0};

  soap = (struct soap*)malloc(sizeof(struct soap));
  soap_init(soap);
  soap_set_omode(soap, SOAP_IO_CHUNK);
  soap->connect_timeout = conn_timeout;
  soap->recv_timeout = recv_timeout;
#ifdef MSG_NOSIGNAL
  soap->socket_flags = MSG_NOSIGNAL;  /* prevent sigpipe */
#endif
  if(inmsg == NULL || strlen(inmsg)==0 )
  {
    errcode = -1;
    snprintf(errmsg,sizeof(errmsg)-1,"call %s failed:inmsg is null!",soap->endpoint);
    goto error_deal;
  }
  if(need2utf)
  {
      inutf8 = g2u(inmsg);
      if(inutf8 == NULL)
      {
            errcode = -1001; 
            snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call %s failed: convert inmsg to utf8 failed",__FILE__,__LINE__,url);
            goto error_deal;
      }
  }
  else
  {
    inutf8 = strdup(inmsg);
  }
  
  /*if( soap_post_connect(&soap, url, NULL, content_type)
        || soap_send(&soap, inutf8)
        || soap_end_send(&soap))*/
  if(soap_post_connect(soap, url, NULL, content_type))
  {
        errcode = -201;/* conn and send failed */
        /* 使用 url 标识 地址 不再使用 soap.endpoint
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call %s failed:conn failed or send failed!",__FILE__,__LINE__,soap.endpoint);
        */
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call %s failed:conn failed or send failed!",__FILE__,__LINE__, url);
        goto error_deal;
  }
  if(soap_send(soap, inutf8))
  {
        errcode = -202;/* conn and send failed */
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call %s failed:soap_send failed!",__FILE__,__LINE__,url);
        goto error_deal;
  }
  if(soap_end_send(soap))
  {
        errcode = -203;/* conn and send failed */
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call %s failed:soap_end_send failed!",__FILE__,__LINE__,url);
        goto error_deal;
  }

  /* after sending POST content, receive body (note: POST handlers should not be set for client) */
  if (soap_begin_recv(soap)
        || soap_http_body(soap, &buf, &len)
        || soap_end_recv(soap))
  { 
        errcode = -22; /* recv failed */
        soap_get_errmsg_url(soap, errmsg, sizeof(errmsg),url);
        goto error_deal;
  }
  if(buf==NULL || strlen(buf)==0 || len==0)
  {
        errcode = -3; /* recv NULL */
        snprintf(errmsg,sizeof(errmsg)-1,"call %s failed:recv NULL!",url);
        goto error_deal;
  }
  if(200 == soap->status)
  {/* OK */
    if(need2gbk)
    {
        tmp = u2g(buf);
        if(tmp == NULL)
        {
            errcode = -4; /* uft-8 to gbk failed!*/
            snprintf(errmsg,sizeof(errmsg)-1,"call %s failed:uft-8 to gbk failed!",url);
            goto error_deal;
        }
    }
    else
    {
        tmp = buf;
    }
    *outmsg = strdup(tmp);
  }
  else
  {/* failed */
    errcode = -5; /* http status !200 */
    snprintf(errmsg,sizeof(errmsg)-1,"call %s failed:http status is [%d] expected 200 [%s]",url,soap->status,buf);
    goto error_deal;
  }
  
error_deal:
  if(errcode != 0)
  {
    *outmsg = (char *)calloc(1,2048);
    int mylen = 2048;
    /*
    snprintf(*outmsg,mylen-1,__CSF_JSON_ERRMSG,CALL_ESB_ERRCODE,errmsg,errmsg,errmsg);
    */
    snprintf(*outmsg,mylen-1,"%s",errmsg);
  }
  if(inutf8)
  {
     free(inutf8);
     inutf8 = NULL;
  }
  soap_closesock(soap); /* close only when not keep-alive */
  soap_end(soap);
  soap_done(soap);
  free(soap);
  printf("<<<<<< call [%s]:[%s] end.....\n", url?url:"", *outmsg);
  return errcode;
}







#ifdef __cplusplus
}
#endif


