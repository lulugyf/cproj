#ifndef __esb__cli__h__
#define __esb__cli__h__
#ifdef __cplusplus
extern "C" {
#endif





                           

int call_esb_ws(char *url, int conn_timeout, int recv_timeout,
                      char *inmsg, int need2utf,char **outmsg, int need2gbk);
int call_esb_rest(char *url,int conn_timeout, int recv_timeout,
                      char *inmsg, int need2utf, char **outmsg, int need2gbk);

#ifdef __cplusplus
    }
#endif

#endif

