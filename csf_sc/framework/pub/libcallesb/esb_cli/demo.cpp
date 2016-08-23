#include "esb_cli.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <time.h>
#include <sys/time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/select.h>
#include <signal.h>
#include <string.h>

#include <map>
using namespace std;



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



#ifndef LPNOWSEC
#define LPNOWSEC(a) \
    {\
        struct timeval  __ttt__;\
        gettimeofday(&__ttt__,NULL);\
        a=__ttt__.tv_sec+__ttt__.tv_usec/1000000.0;\
    }
#endif


void call_esb_rest_test(char *url, char *msg_filename)
{
    char *inmsg = rf(msg_filename);
    if(inmsg == NULL)
    {
        fprintf(stderr, "读取文件[%s]失败,请检查\n", msg_filename);
        exit(10);
    }
    fprintf(stderr, ">>>>>>>>>>>>>调用rest服务开始\n地址:[%s],输入报文:[%s]\n", url,inmsg);
    char *outmsg = NULL;
    int ret = 0;
    double d1,d2;
    LPNOWSEC(d1);

    ret = call_esb_rest(url,5,5,inmsg,0,&outmsg,0);


    LPNOWSEC(d2);
    if(ret == 0)
    {
        fprintf(stderr, "<<<<<<<<<<<调用rest服务成功\n地址:[%s],输出报文:[%s]\n", url,outmsg);
    }
    else
    {
        fprintf(stderr, "<<<<<<<<<<<调用rest服务失败\n地址:[%s],错误信息:[%s]\n", url,outmsg);
    }
    printf("##################call rest costs %g s\n\n\n",d2-d1);
    free(outmsg);
    outmsg = NULL; /* 无论成功失败,都需要将outmsg指针free */
}


void call_esb_ws_test(char *url, char *msg_filename)
{
    char *inmsg = rf(msg_filename);
    if(inmsg == NULL)
    {
        fprintf(stderr, "读取文件[%s]失败,请检查\n", msg_filename);
        exit(10);
    }
    fprintf(stderr, ">>>>>>>>>>>调用Webservice服务开始\n地址:[%s],输入报文:[%s]\n", url,inmsg);
    char *outmsg = NULL;
    int ret = 0;
    double d1,d2;
    LPNOWSEC(d1);
    int conn_timeout = 3;
    int recv_timeout = 3;
    char *outstr = NULL;
    LPNOWSEC(d1);
    ret = call_esb_ws(url, conn_timeout,recv_timeout,inmsg,1,&outmsg,1);
    LPNOWSEC(d2);
	if (ret == 0)
	{
		fprintf(stderr, "<<<<<<<<<<<调用ws服务成功\n地址:[%s],输出报文:[%s]\n", url,outmsg);
	}
	else
	{

		fprintf(stderr, "<<<<<<<<<<<调用ws服务失败\n地址:[%s],错误信息:[%s]\n", url,outmsg);
	}
    printf("##################call ws costs %g s\n\n\n",d2-d1);
    free(outmsg);
	outmsg = NULL;  /* 无论成功失败都需要释放空间 */
}

int main(int argc, char **argv)
{ 
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

	




