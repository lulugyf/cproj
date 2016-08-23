#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define LOGFILE "rcmd.log"
#define TIMEOUT 10000

#ifndef GCC
#define strcasecmp strcmp
#endif /* GCC */

#define zero(a) memset(a, 0, sizeof(a))

/*
服务端参数 -mserver -p<server_port>

客户端参数格式
rcmd: 远程指令命令， 
        -mrcmd -h<remote_host> -p<remote_port> -w"workdir" -c"cmd"
sfil: 发送文件
        -msfil -h<remote_host> -p<remote_port> -r<remote_file> -l<local_file>
rfil: 从服务器端读取文件
        -mrfil -h<remote_host> -p<remote_port> -r<remote_file> -l<local_file>

通讯数据格式:
rcmd(其中000000nn 为十进制的长度表示, 包括之后的所有内容, 下同):  
  [rcmd000000nnworkdir;cmdstring]
  应答内容为指令指令的控制台输出内容
sfil(这里的000000nn 所包含的长度只到filesize, 后边的长度:
  [sfil000000nnremotefilename;localfilename;filesize]
  [sfil00000004retn]   应答(可以接受则retn=000, 其它值表示不接受)
  [filedata]]
rfil
  [rfil000000nnremotefilename;localfilename]
  [rfil000000nnretn[filedata]]  如果retn是0000时, 表示文件可以传送, nn表示文件的长度
*/


char parm_workmode[20]; /* 工作模式 */
char parm_host[25];   /* ip地址 */
char parm_port[10];   /* 端口 */
char parm_workdir[100]; /*远程指令执行的目录s*/
char parm_cmd[500];   /* 指令 */
char parm_rfile[255]; /* 远端文件名 */
char parm_lfile[255]; /* 本地文件名 */

int getfilesize(const char *filename){
    struct stat st;
    
    if(stat(filename, &st) != 0)
        return -1;
    return st.st_size; 
}    

void parsecmdline(int argc, char *argv[]){
        int i;
        char *str;
        
        zero(parm_workmode);
        zero(parm_host);
        zero(parm_port);
        zero(parm_cmd);
        zero(parm_rfile);
        zero(parm_lfile);
        
        for(i=0; i<argc; i++){
                str = argv[i];
                if(str[0] != '-')
                        continue;
                switch(str[1]){
                        case 'm':
                        case 'M':
                                strcpy(parm_workmode, str + 2); break;
                        case 'h':
                        case 'H':
                                strcpy(parm_host, str + 2); break;
                        case 'p':
                        case 'P':
                                strcpy(parm_port, str + 2); break;
                        case 'c':
                        case 'C':
                                strcpy(parm_cmd, str + 2); break;
                        case 'r':
                        case 'R':
                                strcpy(parm_rfile, str + 2); break;
                        case 'l':
                        case 'L':
                                strcpy(parm_lfile, str + 2); break;
                        case 'w':
                        case 'W':
                            strcpy(parm_workdir, str + 2); break;
                }
        }
}

int server(int sockid)
{
	char buf[1024], *ptr,  *ptr1;
	char mode[5];
	int ret, i, len;
	FILE *fp1, *fp2;

	zero(buf);
	ret = tcp_readn(sockid, buf, 12);
	if(ret != 12){
		printf("read command header failed[%d].\n", ret);
		return -1;
	}
	printf("read header[%s]\n", buf);
	memcpy(mode, buf, 4); mode[4] = 0;
	ptr = buf + 4;
	sscanf(ptr, "%08d", &len);
	printf("length [%d]\n", len);
	if(len <= 0 || len > 350)
	{/*invalid header length*/
		printf("read buf[%s]\n", buf);
		printf("length in header invalid[%d]\n", len);
		return -3;
	}
	zero(buf);
	ret = tcp_readn(sockid, buf, len);
	if(ret != len){
		printf("read length failed\n");
		return -4;
	}
	printf("read again[%s]\n", buf);
	if(strcmp(mode, "sfil") == 0){/*传送文件 client -> server*/
		char remotefile[100], localfile[100];
		int filesize;
		printf("send file[%s]\n", buf);
		ptr1 = buf;
		ptr = strchr(ptr1, ';');
		ptr[0] = 0;
		strcpy(remotefile, ptr1);
		ptr1 = ptr + 1;
		ptr = strchr(ptr1, ';');
		ptr[0] = 0;
		strcpy(localfile, ptr1);
		ptr1 = ptr + 1;
		sscanf(ptr1, "%x", &filesize);
		printf("get file local[%s] remote[%s] size[%d]\n", remotefile, localfile, filesize);
		fp1 = fopen(remotefile, "wb");
		if(fp1 == NULL){/* Can not create new file, refuse it*/
			strcpy(buf, "sfil000000041001");
			write(sockid, buf, strlen(buf));
			return -2;
			}
		strcpy(buf, "sfil000000040000");
		tcp_writen(sockid, buf, strlen(buf));
		while(filesize > 0){
		    len = sizeof(buf) < filesize ? sizeof(buf) : filesize;
			ret = tcp_readn(sockid, buf, len);
			if(ret <= 0){
				printf("read ret [%d], break\n", ret);
				break;
			}
			fwrite(buf, ret, 1, fp1);
			filesize -= ret;
			}
		fclose(fp1);
		return 0;		
	}
	else if(strcmp(mode, "rfil") == 0){/*传送文件 server -> client*/
		char remotefile[100], localfile[100];
		int filesize;
		ptr1 = buf;
		ptr = strchr(ptr1, ';');
		ptr[0] = 0;
		strcpy(remotefile, ptr1);
		strcpy(localfile, ptr+1);
		filesize = getfilesize(remotefile);
		printf("filesize: %d\n", filesize);
		if(filesize <= 0){
		    printf("get file size failed[%d]\n", filesize);
		    strcpy(buf, "rfil000000041001");
		    tcp_writen(sockid, buf, strlen(buf));
		    return -5;
		}else{
		    sprintf(buf, "rfil%08x0000", filesize);
		    tcp_writen(sockid, buf, strlen(buf));
		}    
		fp1 = fopen(remotefile, "rb");
		while(filesize > 0){
		    ret = fread(buf, 1, sizeof(buf), fp1);
		    if(ret <= 0){
		        printf("fread file failed[%d], break\n", ret);
		        break;
		    }
            len = tcp_writen(sockid, buf, ret);
            if(len != ret){
                printf("tcp_writen failed[%d]\n", len);
                break;
            }
            filesize -= len;    
		}
        fclose(fp1);
        return 0;
	}
#ifndef __WIN32__
	else if(strcmp(mode, "rcmd") == 0){/* 远程执行指令*/
		char workdir[100];
		char cmdstring[255];

		zero(workdir); zero(cmdstring);
		ptr = strchr(buf, ';');
		if(ptr == NULL){
			printf("string format invalid\n");
			return -4;
			}
		ptr[0] = 0; ptr ++;
		strcpy(workdir, buf);
		strcpy(cmdstring, ptr);
		chdir(workdir);
		fp1 = popen(cmdstring, "rb");
		while( 1 ){
			i = fread(buf, 1, sizeof(buf), fp1);
			if(i<=0)
				break;
			buf[i] = 0;
			printf("%s", buf);
			tcp_writen(sockid, buf, i);
		}
		pclose(fp1);
		return 0;
	}
#endif /* __WIN32__ */
}

int client(int sockid){
    char buf[1024], *ptr, buf1[200];
    int ret, i, len;
    FILE *fp1;
    char remotefile[100], localfile[100];
    int filesize;
    
       if(strcasecmp(parm_workmode, "rcmd") == 0){
            sprintf(buf, "%s;%s", parm_workdir, parm_cmd);
            i = strlen(buf);
            sprintf(buf, "rcmd%08d%s;%s", i, parm_workdir, parm_cmd);
            ret = tcp_writen(sockid, buf, i+12);
	    while( 1 ){
			memset(buf, 0, sizeof(buf));
			i = tcp_read(sockid, buf, sizeof(buf)-1);
			if(i <= 0){
				printf("tcp_read return %d\n", i);
				break;
			}
			printf("%s", buf);
        }
            tcp_close(sockid);
    }else if(strcasecmp(parm_workmode, "sfil") == 0){
        filesize = getfilesize(parm_lfile);
        if(filesize <= 0){
			printf("local file[%s] size error[%d]\n", parm_lfile, filesize);
			return -2;
		}
		sprintf(buf1, "%s;%s;%x", parm_rfile, parm_lfile, filesize);
		sprintf(buf, "sfil%08d%s", strlen(buf1), buf1);
		ret = tcp_writen(sockid, buf, strlen(buf));
		printf("send head[%s]\n", buf);
		if(ret != strlen(buf)){
			printf("write failed %d [%s]\n", ret, buf);
			return -9;
		}
		zero(buf);
		ret = tcp_readn(sockid, buf, 16);
		if(ret != 16){
			printf("read reply failed\n");
			return -6;
		}
		if(memcmp(buf+12, "0000", 4) != 0){
			printf("server refused[%s]\n", buf+12 );
			return -7;
		}
		fp1 = fopen(parm_lfile, "rb");
		if(fp1 == NULL){
			printf("open local file [%s] failed\n", parm_lfile);
			return -10;
		}
		while(filesize > 0){
			ret = fread(buf, 1, sizeof(buf), fp1);
			if(ret <= 0){
				printf("read file faild[%d], break\n", ret);
				break;
			}
			fflush(stdout);
			len = tcp_writen(sockid, buf, ret);
			if(len != ret){
				printf("write sock failed[%d]\n", len);
				break;
			}
			filesize -= len;
		}
		fclose(fp1);
    }else if(strcasecmp(parm_workmode, "rfil") == 0){
        /*从服务器读取文件*/
        sprintf(buf1, "%s;%s", parm_rfile, parm_lfile);
        sprintf(buf, "rfil%08d%s", strlen(buf1), buf1);
        tcp_writen(sockid, buf, strlen(buf));
        zero(buf);
        ret = tcp_readn(sockid, buf, 16);
        if(ret != 16){
            printf("server back failed[%d]\n", ret);
            return -6;
        }
        if(memcmp(buf+12, "0000", 4) != 0){
            printf("server refused [%s]\n", buf);
            return -7;
        }
        buf[12] = 0;
        sscanf(buf+4, "%08x", &filesize);
printf("filesize [%d]\n", filesize);
        fp1 = fopen(parm_lfile, "wb");
        if(fp1 == NULL){
            printf("create local file[%s] failed.\n", parm_lfile);
            return -9;
        }     
        while(filesize > 0){
            len = sizeof(buf)<filesize ? sizeof(buf) : filesize;
            ret = tcp_read(sockid, buf, len);
            if(ret <= 0){
                printf("read file failed[%d]\n", ret);
                break;
            }
            len = fwrite(buf, 1, ret, fp1);
            filesize -= ret;
        }
        fclose(fp1);          
    }
	return 1;
}




