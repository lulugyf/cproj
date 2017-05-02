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

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
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
int main(int argc, char *argv[]) {

    int r;
    if(argc < 3){
        printf("Usage: %s <url> <post content>\n", argv[0]);
        return 1;
    }
    r = curl_http_post(argv[1], 10, 10,
        argv[2], &output);
    printf("return %d
    return 0;
}
*/


/*
 * 做通用的post操作， 输入数据在content中， 返回数据在output中， 返回如果不为NULL, 必须在外部释放返回 free(*output)
 * 输入内容会进行 gbk->utf8的转换，  输出则进行 utf8->gbk 转换
 * 两个超时时间的单位为 s
 *
 * 返回值： 0 成功， 否则为失败， 失败描述信息在output中
*/
int curl_http_post(const char *url, int conn_timeout, int recv_timeout,
                char *content, char **output)
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

    inutf8 = g2u(content);
    if(inutf8 == NULL)
    {
        errcode = 1003;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  curl_http_post %s failed:g2u failed!",__FILE__,__LINE__,url);
        goto error_deal;
    }


    curl_global_init(CURL_GLOBAL_NOTHING);
    curl = curl_easy_init();
    if(curl == NULL)
    {
        errcode = 1004;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  curl_http_post %s failed:curl_easy_init is null!",__FILE__,__LINE__,url);
        goto error_deal;
    }

    chunk = curl_slist_append(chunk, "Content-Type: text/xml; charset=UTF-8");
    chunk = curl_slist_append(chunk, "SOAPAction: ");
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
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  curl_http_post %s failed:curl_easy_perform failed:%s!",__FILE__,__LINE__,url,curl_easy_strerror(res));
        goto error_deal;
    }

    if(strlen(rspbuf.memory)<1)
    {
        errcode = 10055;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  curl_http_post %s OK but esb return NULL!",__FILE__,__LINE__,url);
        goto error_deal;
    }

    outgbk = u2g(rspbuf.memory);

    if(outgbk == NULL)
    {
        errcode = 1008;
        snprintf(errmsg,sizeof(errmsg)-1,"%s:%d  curl_http_post %s failed:u2g faield!",__FILE__,__LINE__,url);
        goto error_deal;
    }


error_deal:
    if(rspbuf.memory) free(rspbuf.memory),rspbuf.memory=NULL;
    /* 如果是调试模式 此处有bug if(headbuf.memory) free(headbuf.memory),headbuf.memory=NULL; */
    if(inutf8) free(inutf8),inutf8 = NULL;
    if(curl) curl_easy_cleanup(curl);
    if(chunk) curl_slist_free_all(chunk),chunk = NULL;
    curl_global_cleanup();

    if(errcode == 0)
    {
        *output = outgbk;
    }
    else
    {
        *output = strdup(errmsg);
    }
    fprintf(stderr,"%s:%d  curl_http_post %s finished[retcode:%d]\n>>>>>>headmsg[%s]\n>>>>>>inmsg[%s]\n>>>>>>outmsg[%s]\n\n",
            __FILE__,__LINE__,url, errcode, headbuf.memory, content, *output);

    if(headbuf.memory) free(headbuf.memory),headbuf.memory=NULL;
    return errcode;
}


char *rf(const char *fname)
{
    struct stat st;
    char *buf;
    if(stat(fname, &st) != 0)
    return NULL;
    buf = (char *)malloc(st.st_size+1);
    buf[st.st_size] = 0;
    FILE *fp = fopen(fname, "r");
    fread(buf, 1, st.st_size, fp);
    fclose(fp);
    return buf;
}


int main(int argc, char *argv[]) {

    const char *url = "http://10.109.1.43:8600/mcpsec/services/BusinessService";
    char *output = NULL;
    char *content = NULL;
    char *p1, *p2;

    int ret;

    const char *tag_begin = "{\"ROOT\":{\"MESSAGE\":\"";
    const char *tag_end = "\"}}</ns:return>";

    content = rf("data.txt");
    ret = curl_http_post(url, 10, 10, content, &output);
    free(content);

    printf("ret=%d\n", ret);
    if(output != NULL){
        //printf("output:[%s]\n", output);
        p1 = strstr(output, tag_begin);
        if(p1 == NULL){
            printf("return failed:[%s]\n", output);
        }else{
            p1 += strlen(tag_begin);
            p2 = strstr(p1, tag_end);
            if(p2 != NULL){
                *p2 = 0;
                printf("message is [%s]\n", p1);
            }
        }
        free(output);
    }else{
        printf("output is NULL\n");
    }

    return 0;
}
