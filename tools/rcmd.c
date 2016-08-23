#include <stdio.h>

extern char parm_workmode[20]; /* 工作模式 */
extern char parm_host[25];   /* ip地址 */
extern char parm_port[10];   /* 端口 */
extern char parm_workdir[100]; /*远程指令执行的目录s*/
extern char parm_cmd[500];   /* 指令 */
extern char parm_rfile[255]; /* 远端文件名 */
extern char parm_lfile[255]; /* 本地文件名 */

void new_connection(int sockid, char *clientip, int clientport,
               void *parm, int servsockid)
{
	printf("client: [%s:%d]\n", clientip, clientport);
    server(sockid);
    tcp_close(sockid);
}


int main(int argc, char **argv)
{
        int sd, psd;
        int port, ret, pid;
        char ip[50], buf[1024];
        char str[150];

        parsecmdline(argc, argv);

        if(strlen(parm_workmode) == 0)
        {
		printf("\n\n 服务端参数 -mserver -p<server_port>\n\n \
客户端参数格式\n \
rcmd: 远程指令命令，\n \
        -mrcmd -h<remote_host> -p<remote_port> -w\"workdir\" -c\"cmd\"\n \
sfil: 发送文件\n \
        -msfil -h<remote_host> -p<remote_port> -r<remote_file> -l<local_file>\n \
rfil: 从服务器端读取文件\n \
        -mrfil -h<remote_host> -p<remote_port> -r<remote_file> -l<local_file> \n\n");
                return -1;
        }

        if(strcasecmp(parm_workmode, "server") == 0){
#ifndef __WIN32__
                GenDaemon();
#endif                
                sd = tcp_listen(NULL, atoi(parm_port));
                if(sd <= 0){
                        printf("tcp_listen failed!\n");
                        return -2;
                }

                tcp_server_loop(sd, new_connection, NULL);

        }else{
            sd = tcp_connect(parm_host, atoi(parm_port));
            if(sd <= 0){
                printf("can not connect to remote server[%s:%s]\n",
                	parm_host, parm_port);
        	}else{
                client(sd);
            	tcp_close(sd);
         	}		  	        
        }


        return 0;
}


