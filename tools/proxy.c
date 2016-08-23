#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "util_tcp.h"

int  g_lport;
char g_tserv[20];
int  g_tport;
int  g_argtype;

/*
 * parse start
 * */
void parseArg(int argc, char *argv[])
{
	int i;
	char *p;
	FILE *fp;
	char buf[200];
	
	if(argc > 1 && argv[1][1] == 'f'){
		g_argtype = 1;
		fp = fopen(argv[1]+2, "r");
		i = 0;
		while(fgets(buf, sizeof(buf), fp) != NULL){
	        if(buf[0] == '#') continue;
        }
        fclose(fp);
	}else{
        g_lport = 8080;
        strcpy(g_tserv, "10.105.3.42");
		g_tport = 23;
	
		for(i=1; i<argc; i++){
			p = argv[i];
			switch(p[1]){
	        case 'l':
				g_lport = atoi(p+2);
				break;
			case 't':
				strcpy(g_tserv, p+2);
				break;
			case 'p':
	            g_tport = atoi(p+2);
	            break;
	        }
	    }
	}
}

/*
 * read from fd1 and write to fd2
 * */
int rw(int fd1, int fd2, int direct){
	char buf[4096];
	int rlen, wlen;
	
	rlen = tcp_read(fd1, buf, sizeof(buf));
	if(rlen <= 0)
		return -1;
    buf[rlen] = 0;
    if(direct == 1){
        printf("-->[%s]\n", buf);
    }else{
        printf("<--[%s]\n", buf);
    }

	wlen = tcp_writen(fd2, buf, rlen);
	if(wlen != rlen)
		return -2;
	return 0;
}

int data_tran(int sockid, char *client_ip, int client_port, void *parm, int servsockid){
	int psd, fds[2];
	int ret, i;
	int timeout;

#ifndef __WIN32__
	tcp_close(servsockid);
#endif
	printf("welcome data_tran\n");
	printf("sockid[%d], client_ip[%s], client_port[%d]\n",
		sockid, client_ip, client_port);
	printf("target server [%s:%d]\n", g_tserv, g_tport);
	psd = tcp_connect(g_tserv, g_tport);
	if(psd <= 0){
		tcp_close(sockid);
		return -2;
	}
	
	printf("target socket [%d], source socket[%d]\n", psd, sockid);
	
	timeout = 4*60*60*1000; /* 4 hours */
	while( 1 ){
		fds[0] = sockid;
		fds[1] = psd;
		ret = tcp_check_read(fds, 2, timeout);
		if(ret <= 0)
			break;
		for(i=0; i<ret; i++){
			/*printf("ready socket [%d]\n", fds[i]); */
			if(fds[i] == sockid)
				ret = rw(sockid, psd, 1);
			if(fds[i] == psd)
				ret = rw(psd, sockid, 0);
			if(ret != 0)
				break;
		}
		if(ret != 0)
			break;
	}
	tcp_close(sockid);
	tcp_close(psd);
	return 1;
}

/*
 * service port prepare and enter main loop.
 * */
int proxy_begin(int argc, char **argv ){
    int sd = 0;
	
	parseArg(argc, argv);
	sd = tcp_listen(NULL, g_lport);
	if(sd <= 0){
		printf("can not listen on[%d], return [%d]\n",
			g_lport, sd);
		return -1;
	}
	printf("listen sockid[%d], data_tran[%08X]\n",
		sd, data_tran);
	tcp_server_loop(sd, data_tran, NULL);
	
	return 0;
}

int main(int argc, char *argv[])
{
	GenDaemon();

	proxy_begin(argc, argv);
	return 0;
}

