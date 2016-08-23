#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

#define PORT 12345
#define MAXSOCKFD 1024

void wf(char *file_name,char *buf, size_t len)
{
    int fd;
    fd = open( file_name,
        O_WRONLY | O_CREAT | O_TRUNC,
        S_IRUSR | S_IWUSR );
    write(fd,buf,len);
    close(fd);
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



main(int argc, char **argv)
{
    int sockfd,newsockfd,is_connected[MAXSOCKFD],fd;
    struct sockaddr_in addr;
    int addr_len = sizeof(struct sockaddr_in);
    fd_set readfds;
    char buffer[1024];
    //char msg[ ] ="Welcome to server!";
   /*
    char msg[10240];
    sprintf(msg, str_format,strlen(send_msg),send_msg);
    */
    if(argc !=3) fprintf(stderr,"usage:%s filename port\n",argv[0]),exit(10);
    char *sendmsg = rf(argv[1]);
    int port = atoi(argv[2]);
    if(!sendmsg) fprintf(stderr,"read file %s failed!\n",argv[1]),exit(10);
    char *msg = sendmsg;
    fprintf(stderr,"send client msg is:[%s]\n",msg);
    int ret = -9;
    if ((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
        perror("socket");
        exit(1);
    }
    bzero(&addr,sizeof(addr));
    addr.sin_family =AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuseaddr = 1;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
    printf("setsockopt SO_REUSEADDR ret:[%d]\n", ret);
    if(bind(sockfd,(const struct sockaddr *)&addr,sizeof(addr))<0)
    {
        perror("connect");
        exit(1);
    }
    if(listen(sockfd,15)<0){
        perror("listen:");
        exit(1);
    }
    for(fd=0;fd<MAXSOCKFD;fd++)
    {
        is_connected[fd]=0;
    }
    
    while(1)
    {
        FD_ZERO(&readfds);
        FD_SET(sockfd,&readfds); /* 每次都要将监听套接口放入监听集合中去 */
        for(fd=0;fd<MAXSOCKFD;fd++)
        {
            if(is_connected[fd]) FD_SET(fd,&readfds);
        }
        if(!select(MAXSOCKFD,&readfds,NULL,NULL,NULL)) 
            continue;
        for(fd=0;fd<MAXSOCKFD;fd++)
        {
            if(FD_ISSET(fd,&readfds))
            {
                if(sockfd == fd){
                    //sleep(5);
                    if((newsockfd = accept (sockfd,(struct sockaddr *)&addr,&addr_len))<0)
                    {
                        perror("accept:");
                    }
                    
                    printf(">>>>>>cnnect from %s\n",inet_ntoa(addr.sin_addr));
                    
                    sleep(100);
                    ret = write(newsockfd,msg,strlen(msg));
                    fprintf(stderr,"<<<<<<send to [%d] [%d]bytes,strlen(msg)=[%d]<<<%s\n",newsockfd,ret,strlen(msg),msg);
                    is_connected[newsockfd] =1;
                    
                }
                else
                {
                    bzero(buffer,sizeof(buffer));
                    if( (ret=read(fd,buffer,sizeof(buffer)-1))<=0)
                    {
                        printf(">>>>read(%d)return:%d connect closed.\n",fd,ret);
                        is_connected[fd]=0;
                        close(fd);
                    }
                    else
                    {
                        printf(">>recv [%d] bytes from [%d]>>%s\n",fd,strlen(buffer),buffer);
                    }
                }
            }
        }
        
        
    }
}


