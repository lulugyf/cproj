#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#define LPNOWSEC(a) \
{\
struct timeval  __ttt__;\
gettimeofday(&__ttt__,NULL);\
a=__ttt__.tv_sec+__ttt__.tv_usec/1000000.0;\
}




extern char * rf(char *fname); /* defined in httpcustomheader.c */
extern int call_esb_ws(char *url, int conn_timeout, int recv_timeout,
                char *inmsg, int need2utf, char **outmsg, int need2gbk);
                
extern int call_esb_rest(char *url, int conn_timeout, int recv_timeout,
                char *inmsg, int need2utf, char **outmsg, int need2gbk);                

void call_ws()
{
    char *data = rf("./a.xml"); 
    char *url = "http://172.21.1.30:51900/esbWS/services/sCustInfoValid";
    char *outmsg;
    int ret = call_esb_ws(url,2,3,data,1,&outmsg,1);
    printf("call_esb_ws:ret=[%d],outmsg=[%s]\n",ret, outmsg);
    free(data);data = NULL;
    free(outmsg);outmsg = NULL;
}

void call_rest()
{
    char *data = rf("./a.json");
    char *url = "http://172.21.1.30:51900/esbWS/rest/sCustInfoValid";
    char *outmsg;
    int ret = call_esb_rest(url,2,3,data,0,&outmsg,0);
    printf("call_esb_rest:ret=[%d],outmsg=[%s]\n",ret, outmsg);
    free(data);data = NULL;
    free(outmsg);outmsg = NULL;
}

void call_esb_rest_test(char *myurl, char *msg_filename)
{
    char *data = rf(msg_filename);
    char *url = myurl;
    char *outmsg;
    double d1=0;
    double d2=0;
    LPNOWSEC(d1);
    int ret = call_esb_rest(url,2,3,data,0,&outmsg,0);
    LPNOWSEC(d2);
    printf("call_esb_rest:ret=[%d],outmsg=[%s],costs[%f]seconds\n",ret, outmsg, d2-d1);
    free(data);data = NULL;
    free(outmsg);outmsg = NULL;
}

void call_esb_ws_test(char *myurl, char *msg_filename)
{
    char *data = rf(msg_filename); 
    char *url = myurl;
    char *outmsg;
    double d1=0;
    double d2=0;
    LPNOWSEC(d1);
    int ret = call_esb_ws(url,2,3,data,1,&outmsg,1);
    LPNOWSEC(d2);
    printf("call_esb_ws:ret=[%d],outmsg=[%s],costs[%f]seconds\n",ret, outmsg,d2-d1);
    free(data);data = NULL;
    free(outmsg);outmsg = NULL;
}


int main(int argc, char **argv)
{
    /*call_ws();*/
    /*call_rest();*/
     if(argc!=4)
    {
        fprintf(stderr, "usage: %s 0|1 url msg_filename\n", argv[0]);
        fprintf(stderr, ">>>>>: %s 0|1 其中: 0为ws服务; 1为rest服务\n", argv[0]);
        fprintf(stderr, ">>>>>: %s url 其中: url为ws服务或者rest服务的地址\n", argv[0]);
        fprintf(stderr, ">>>>>: %s url 其中: msg_filename为一个文件名称,存放服务入参的报文\n", argv[0]);
        exit(10);
    }
    char *url = argv[2];
    char *msg_filename = argv[3];
    
    if(atoi(argv[1]))
    {
        call_esb_rest_test(url, msg_filename);
    }
    else
    {
        call_esb_ws_test(url, msg_filename);
    }
    
    return 0;
}



