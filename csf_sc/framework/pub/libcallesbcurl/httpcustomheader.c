#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <iconv.h>
#include <alloca.h>


//#define MSG_START_FLAG "<ns:return>"
//#define MSG_END_FLAG   "</ns:return>"
#define MSG_START_FLAG "return>"
#define MSG_END_FLAG   "</"

#define __SOAP__WRAPPER__  "<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">" \
                                "<SOAP-ENV:Body>" \
                                    "<m:callService xmlns:m=\"http://ws.sitech.com\">" \
                                        "<m:pin><![CDATA[%s]]></m:pin>" \
                                    "</m:callService>" \
                                "</SOAP-ENV:Body>" \
                            "</SOAP-ENV:Envelope>"

#define LPNOWSEC(a) \
{\
    struct timeval  __ttt__;\
    gettimeofday(&__ttt__,NULL);\
    a=__ttt__.tv_sec+__ttt__.tv_usec/1000000.0;\
}




/*
字符的映射规则
&apos;      '
&amp;       &
&gt;        >
&lt;        <
&quot;      "

flag:0 单词替换;
flag:非0 循环替换;
*/
static char * xml_escape(char *xmlstr, int flag)
{
	if(xmlstr == NULL) return NULL;
	size_t len = strlen(xmlstr);
	if(len == 0) return NULL;
	
	char *newstr = (char *)calloc(1, len+1);
	if(newstr == NULL) return NULL;

	
	char *ptrold = xmlstr;
	char *ptrnew = newstr;
	int i = 0;
    int j = 0;
    
    while(i<len)
    {
        if(ptrold[0]=='&')
        {
            if( (i+1<len && ptrold[1]=='g') 
              &&(i+2<len && ptrold[2]=='t')
              &&(i+3<len && ptrold[3]==';'))
            {
                ptrnew[j++] = '>';
                ptrold += 4;
                i += 4;
                continue;
            }
            
            if( (i+1<len && ptrold[1]=='l') 
              &&(i+2<len && ptrold[2]=='t')
              &&(i+3<len && ptrold[3]==';'))
            {
                ptrnew[j++] = '<';
                ptrold += 4;
                i += 4;
                continue;
            }
            
            if( (i+1<len && ptrold[1]=='a') 
              &&(i+2<len && ptrold[2]=='m')
              &&(i+3<len && ptrold[3]=='p')
              &&(i+4<len && ptrold[4]==';'))
            {
                /* &amp;lt; &amp;gt; */
                if(flag==0)
                {
                    ptrnew[j++] = '&';
                    ptrold += 5;
                    i += 5;
                }
                else
                {
                    ptrold[4] = '&';
                    ptrold += 4;
                    i += 4;
                }
                continue;
            }
            
            if( (i+1<len && ptrold[1]=='a') 
              &&(i+2<len && ptrold[2]=='p')
              &&(i+3<len && ptrold[3]=='o')
              &&(i+4<len && ptrold[4]=='s')
              &&(i+5<len && ptrold[5]==';'))
            {
                ptrnew[j++] = '\'';
                ptrold += 6;
                i += 6;
                continue;
            }
            
            if( (i+1<len && ptrold[1]=='q') 
              &&(i+2<len && ptrold[2]=='u')
              &&(i+3<len && ptrold[3]=='o')
              &&(i+4<len && ptrold[4]=='t')
              &&(i+5<len && ptrold[5]==';'))
            {
                ptrnew[j++] = '\"';
                ptrold += 6;
                i += 6;
                continue;
            }
            
        }
        
        ptrnew[j++] = ptrold[0];
        ptrold += 1;
	    i++;   
    }
    return ptrnew;
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
    /*  sun: iconv(_iconv_info*, const char**, unsigned long*, char**, unsigned long*) */
    if( iconv(cd, ( char**)pin, (size_t*)(&inlen), pout, (size_t*)(&outlen)) == -1 )
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


char * rf(char *fname)
{
    if(!fname) return NULL;
    int myfd = open( fname, O_RDONLY );
    if(myfd==-1) return NULL;
    char buf[4096];
    fd_set rfd;
    FD_ZERO( &rfd );
    FD_SET( myfd, &rfd );
    char *tmp = NULL;
    char *tmpnew = NULL;
    int ret = 0;
    int oldlen = 0;
    int newlen = 0;
    while(select(myfd+1,&rfd,NULL,NULL,NULL)>0)
    {
        ret = read(myfd,buf,sizeof(buf));
        if(ret==0) break;
        newlen += ret;
        tmp = (char *)realloc(tmp,newlen +1);
        strncpy(tmp+newlen-ret,buf,ret);
        FD_SET( myfd, &rfd );
        tmp[newlen]=0;
    }
    close(myfd);
    return tmp;
}


struct MemoryStruct {
  char *memory;
  size_t size;
};


static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


/*
int call_esb_rest(char *url,int conn_timeout, int recv_timeout,
                       char *inmsg, int need2utf,char **outmsg, int need2gbk)
*/
                      
/*
<faultcode>-2</faultcode>
<faultstring>入参不合法，缺少ROOT节点</faultstring>
要考虑到soap错误的情况;
*/
                      

int call_esb_ws(char *url, int conn_timeout, int recv_timeout,
                char *inmsg, int need2utf, char **outmsg, int need2gbk)
{
    CURL *curl = NULL;
    CURLcode res;
    char errmsg[1024] = {0};
    char *tmp = NULL;
    char *inutf8 = NULL;
    char *outgbk = NULL;
    size_t mylen = 0;
    int errcode = 0;
    char *urn_str = "urn:callService";
    struct curl_slist *chunk = NULL;
    struct MemoryStruct rspbuf;
    rspbuf.memory = (char *)malloc(1);
    rspbuf.memory[0] = 0;
    rspbuf.size = 0;
    struct MemoryStruct headbuf;
    headbuf.memory = (char *)malloc(1);
    headbuf.memory[0] = 0;
    headbuf.size = 0;
    char *p1 = NULL;
    char *p2 = NULL;
    char *rspxml = NULL;
    
    if(url==NULL || strlen(url)==0)
    {
        errcode = 1001;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws failed:url is null!",__FILE__,__LINE__);
        goto error_deal;
    }
    
    if(inmsg==NULL || strlen(inmsg)==0)
    {
        errcode = 1002;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:inmsg is null!",__FILE__,__LINE__,url);
        goto error_deal;
    }
    
    /* gen soap */
    tmp = (char *)alloca(strlen(inmsg) + 1024);
    if(tmp == NULL)
    {
        errcode = 10022;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:alloca return null!",__FILE__,__LINE__,url);
        goto error_deal;
    }
    sprintf(tmp, __SOAP__WRAPPER__, inmsg);
    inmsg = tmp;
    
    if(need2utf != 0)
    {
        inutf8 = g2u(inmsg);
        if(inutf8 == NULL)
        {
            errcode = 1003;
            snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:g2u failed!",__FILE__,__LINE__,url);
            goto error_deal;
        }
    }
    else
    {
        inutf8 = strdup(inmsg);
    }
    
    curl_global_init(CURL_GLOBAL_NOTHING);
    curl = curl_easy_init();
    if(curl == NULL)
    {
        errcode = 1004;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:curl_easy_init is null!",__FILE__,__LINE__,url);
        goto error_deal;
    }
    
    chunk = curl_slist_append(chunk, "Content-Type: text/xml");
    chunk = curl_slist_append(chunk, "SOAPAction: \"urn:callService\"");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, inutf8);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&rspbuf);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEHEADER, (void *)&headbuf);

    /* http://hi.baidu.com/a17509/item/34cc7eda461f165dfb57682d */
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1); 
    curl_easy_setopt( curl, CURLOPT_CONNECTTIMEOUT, conn_timeout );
    curl_easy_setopt( curl, CURLOPT_TIMEOUT, recv_timeout );
    
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        errcode = 1005;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:curl_easy_perform failed:%s!",__FILE__,__LINE__,url,curl_easy_strerror(res));
        goto error_deal;
    }

    if(strlen(rspbuf.memory)<1)
    {
        errcode = 10055;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s OK but esb return NULL!",__FILE__,__LINE__,url);
        goto error_deal;
    }
    
    p1 = strstr(rspbuf.memory, MSG_START_FLAG);
    if(p1 == NULL)
    {
        errcode = 1006;
        #ifdef CALL_ESB_DEBUG
        fprintf(stderr,"%s:%d  call_esb_ws %s failed:[%s]can't find %s!\n\n",__FILE__,__LINE__,url,MSG_START_FLAG, rspbuf.memory);
        #endif
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:can't find %s in retmsg %s!",__FILE__,__LINE__,url,MSG_START_FLAG, rspbuf.memory);
        goto error_deal;
    }

    p1 += strlen(MSG_START_FLAG);
    p2 = strstr(p1, MSG_END_FLAG);
    if(p2 == NULL)
    {
        errcode = 1007;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:can't find %s!",__FILE__,__LINE__,url,MSG_END_FLAG);
        goto error_deal;
    }
    *p2 = 0;
    rspxml = xml_escape(p1, 0);
    if(need2gbk)
    {
        outgbk =  u2g(rspxml);
        if(outgbk == NULL)
        {
            errcode = 1008;
            snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:u2g faield!",__FILE__,__LINE__,url);
            goto error_deal;
            
        }
    }
    else
    {
        outgbk = strdup(rspxml);
    }
 
error_deal:
    if(rspbuf.memory) free(rspbuf.memory),rspbuf.memory=NULL;
    /* 如果是调试模式 此处有bug if(headbuf.memory) free(headbuf.memory),headbuf.memory=NULL; */
    if(inutf8) free(inutf8),inutf8 = NULL;
    if(rspxml) free(rspxml),rspxml = NULL;
    if(curl) curl_easy_cleanup(curl);
    if(chunk) curl_slist_free_all(chunk),chunk = NULL;
    curl_global_cleanup();
    
    if(errcode == 0)
    {
        *outmsg = outgbk;
    }
    else
    {
        /* error; esb ruturn utf-8 need to gbk*/
        if(need2gbk !=0 )
        {
            *outmsg = u2g(errmsg);
            if (NULL == *outmsg)
            {
                *outmsg =(char *)calloc(1,strlen(errmsg)+sizeof(errmsg)+1);
                memcpy(*outmsg,errmsg,strlen(errmsg));
                tmp =  *outmsg + strlen(errmsg);
                snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call u2g failed! libiconv should install again!",__FILE__,__LINE__);
                memcpy(tmp,errmsg,strlen(errmsg));
            }
        }
        else
        {
            *outmsg = strdup(errmsg);
        }
        
    }
    #ifdef CALL_ESB_DEBUG
        fprintf(stderr,"%s:%d  call_esb_ws %s finished[retcode:%d]\n>>>>>>headmsg[%s]\n>>>>>>inmsg[%s]\n>>>>>>outmsg[%s]\n\n",__FILE__,__LINE__,url, errcode,headbuf.memory,inmsg, *outmsg);
    #endif
    if(headbuf.memory) free(headbuf.memory),headbuf.memory=NULL;
    return errcode;
}


int call_esb_rest(char *url, int conn_timeout, int recv_timeout,
                char *inmsg, int need2utf, char **outmsg, int need2gbk)
{
    CURL *curl = NULL;
    CURLcode res;
    char errmsg[1024] = {0};
    char *tmp = NULL;
    char *inutf8 = NULL;
    char *outgbk = NULL;
    size_t mylen = 0;
    int errcode = 0;
    /* json don't need char *urn_str = "urn:callService"; */
    struct curl_slist *chunk = NULL;
    struct MemoryStruct rspbuf;
    rspbuf.memory = (char *)malloc(1);
    rspbuf.memory[0] = 0;
    rspbuf.size = 0;
    
    struct MemoryStruct headbuf;
    headbuf.memory = (char *)(char *)malloc(1);
    headbuf.memory[0] = 0;
    headbuf.size = 0;
    char *headmsg = NULL;
    
    char http_version[32] = {0};
    int http_statecode = 0;
    char http_sc_reason[128] = {0};
    
    char *p1 = NULL;
    char *p2 = NULL;
    char *rspxml = NULL;
    
    if(url==NULL || strlen(url)==0)
    {
        errcode = 1001;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_rest failed:url is null!",__FILE__,__LINE__);
        goto error_deal;
    }
    
    if(inmsg==NULL || strlen(inmsg)==0)
    {
        errcode = 1002;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_rest %s failed:inmsg is null!",__FILE__,__LINE__,url);
        goto error_deal;
    }
    
    /* gen soap */
    /* json no need
    tmp = alloca(strlen(inmsg) + 1024);
    if(tmp == NULL)
    {
        errcode = 10022;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:alloca return null!",__FILE__,__LINE__,url);
        goto error_deal;
    }
    sprintf(tmp, __SOAP__WRAPPER__, inmsg);
    inmsg = tmp;
    */
    if(need2utf != 0)
    {
        inutf8 = g2u(inmsg);
        if(inutf8 == NULL)
        {
            errcode = 1003;
            snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_rest %s failed:g2u failed!",__FILE__,__LINE__,url);
            goto error_deal;
        }
    }
    else
    {
        inutf8 = strdup(inmsg);
    }
    
    curl_global_init(CURL_GLOBAL_NOTHING);
    curl = curl_easy_init();
    if(curl == NULL)
    {
        errcode = 1004;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_rest %s failed:curl_easy_init is null!",__FILE__,__LINE__,url);
        goto error_deal;
    }
    if(need2utf)
        chunk = curl_slist_append(chunk, "Content-Type: application/json;charset=UTF-8");
    else
        chunk = curl_slist_append(chunk, "Content-Type: application/json;charset=GBK");
    /* json no use chunk = curl_slist_append(chunk, "SOAPAction: \"urn:callService\""); */
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, inutf8);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&rspbuf);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEHEADER, (void *)&headbuf);

    /* http://hi.baidu.com/a17509/item/34cc7eda461f165dfb57682d */
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1); 
    curl_easy_setopt( curl, CURLOPT_CONNECTTIMEOUT, conn_timeout );
    curl_easy_setopt( curl, CURLOPT_TIMEOUT, recv_timeout );
    
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        errcode = 1005;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_rest %s failed:curl_easy_perform failed:%s!",__FILE__,__LINE__,url,curl_easy_strerror(res));
        goto error_deal;
    }
    
    /* get headmsg */
    sscanf(headbuf.memory, "%s %d %s", http_version, &http_statecode, http_sc_reason);
    #ifdef CALL_ESB_DEBUG
    fprintf(stderr,"%s:%d  call_esb_rest %s : http_version=%s  http_statecode=%d http_sc_reason=[%s]\n\n",__FILE__,__LINE__,url, http_version,http_statecode,http_sc_reason);
    #endif
    if(strlen(rspbuf.memory)<1)
    {
        errcode = 10055;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_rest %s OK but esb return NULL!",__FILE__,__LINE__,url);
        goto error_deal;
    }
    
    /* don't deal json msg 
    p1 = strstr(rspbuf.memory, MSG_START_FLAG);
    if(p1 == NULL)
    {
        errcode = 1006;
        #ifdef CALL_ESB_DEBUG
        fprintf(stderr,"%s:%d  call_esb_ws %s failed:[%s]can't find %s!\n\n",__FILE__,__LINE__,url,MSG_START_FLAG, rspbuf.memory);
        #endif
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:can't find %s in retmsg %s!",__FILE__,__LINE__,url,MSG_START_FLAG, rspbuf.memory);
        goto error_deal;
    }

    p1 += strlen(MSG_START_FLAG);
    p2 = strstr(p1, MSG_END_FLAG);
    if(p2 == NULL)
    {
        errcode = 1007;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:can't find %s!",__FILE__,__LINE__,url,MSG_END_FLAG);
        goto error_deal;
    }
    *p2 = 0;
    rspxml = xml_escape(p1, 0);
    if(need2gbk)
    {
        outgbk =  u2g(rspxml);
        if(outgbk == NULL)
        {
            errcode = 1008;
            snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_ws %s failed:u2g faield!",__FILE__,__LINE__,url);
            goto error_deal;
            
        }
    }
    else
    {
        outgbk = strdup(rspxml);
    }
    */
    if(need2gbk)
    {
        outgbk =  u2g(rspbuf.memory);
        if(outgbk == NULL)
        {
            errcode = 1008;
            snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  call_esb_rest %s failed:u2g faield!",__FILE__,__LINE__,url);
            goto error_deal;
            
        }
    }
    else
    {
        outgbk = strdup(rspbuf.memory);
    }
    
error_deal:
    if(rspbuf.memory) free(rspbuf.memory),rspbuf.memory = NULL;
    
    if(inutf8) free(inutf8),inutf8 = NULL;
    if(rspxml) free(rspxml),rspxml = NULL;
    if(curl) curl_easy_cleanup(curl);
    if(chunk) curl_slist_free_all(chunk),chunk = NULL;
    curl_global_cleanup();
    
    if(errcode == 0)
    {
        *outmsg = outgbk;
    }
    else
    {
        /* error; esb ruturn utf-8 need to gbk*/
        if(need2gbk !=0 )
        {
            *outmsg = u2g(errmsg);
            if (NULL == *outmsg)
            {
                *outmsg =(char *)calloc(1,strlen(errmsg)+sizeof(errmsg)+1);
                memcpy(*outmsg,errmsg,strlen(errmsg));
                tmp =  *outmsg + strlen(errmsg);
                snprintf(errmsg,sizeof(errmsg)-1,"%s:%d call u2g failed! libiconv should install again!",__FILE__,__LINE__);
                memcpy(tmp,errmsg,strlen(errmsg));
            }
        }
        else
        {
            *outmsg = strdup(errmsg);
        }
        
    }
    #ifdef CALL_ESB_DEBUG
        fprintf(stderr,"%s:%d  call_esb_rest %s finished[retcode:%d]\n>>>>>>headmsg[%s]\n>>>>>>inmsg[%s]\n>>>>>>outmsg[%s]\n\n",__FILE__,__LINE__,url, errcode,headbuf.memory,inmsg, *outmsg);
    #endif
    if(headbuf.memory) free(headbuf.memory),headbuf.memory = NULL;
    return errcode;
}



void test_ws()
{
    char *data = rf("./a.xml");
    char *url = "http://172.21.1.30:51900/esbWS/services/sCustInfoValid";
    char *outmsg;
    int ret = call_esb_ws(url,2,3,data,1,&outmsg,1);
    printf("call_esb_ws:ret=[%d],outmsg=[%s]\n",ret, outmsg);
    free(data);data = NULL;
    free(outmsg);outmsg = NULL;
}


void test_rest()
{
    char *data = rf("./a.json");
    char *url = "http://127.0.0.1:51900/esbWS/services/sCustInfoValid";
    char *outmsg;
    int ret = call_esb_rest(url,2,3,data,0,&outmsg,0);
    printf("call_esb_rest:ret=[%d],outmsg=[%s]\n",ret, outmsg);
    free(data);data = NULL;
    free(outmsg);outmsg = NULL;
}




#ifdef __CURL_TEST__
int main()
{
    test_ws();
    //test_rest();
}
#endif













