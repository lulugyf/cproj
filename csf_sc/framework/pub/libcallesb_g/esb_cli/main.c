#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "esb_cli.h"


#ifndef LPNOWSEC
#define LPNOWSEC(a) \
    {\
        struct timeval  __ttt__;\
        gettimeofday(&__ttt__,NULL);\
        a=__ttt__.tv_sec+__ttt__.tv_usec/1000000.0;\
    }
#endif

char *g_inmsg = NULL;
void call_esb_rest_test()
{
    /*char *url = "http://172.21.1.95:51900/esbWS/rest/stest_1";*/
    //char *url = "http://192.168.0.111:8081/esbWS/rest/stest_1";//call sh rs.sh server;
    char *url = "http://192.168.0.111:58900/esbWS/rest/stest_1"; //call rest_server server;
    char *inmsg = "1234567890ÖÐ¹úabcdefg";
    char *outmsg = "";
    double d1,d2;
    LPNOWSEC(d1);
    if(g_inmsg) inmsg = g_inmsg;
    call_esb_rest(url,2,3,inmsg,&outmsg,0);
    LPNOWSEC(d2);
    printf("call rest costs %g s\n",d2-d1);
    puts(outmsg);
    free(outmsg);
}
void call_esb_ws_test()
{
    char *server = "http://192.168.0.111:8080/esbWS/services/sDynSvc/";
    char *instr = "<ROOT></ROOT>";
    int conn_timeout = 3;
    int recv_timeout = 3;
    char *test = NULL;
    double d1,d2;
    LPNOWSEC(d1);
    call_esb_ws(server, conn_timeout,recv_timeout,instr,&test,1);
    LPNOWSEC(d2);
    printf("call ws costs %g s\n",d2-d1);
    puts(test);
    free(test);
}

int main(int argc, char **argv)
{ 
    
    
    if(argc==2) g_inmsg = argv[1];
    call_esb_ws_test();
    call_esb_rest_test();
    return 0;
}

