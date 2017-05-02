#ifdef __WIN32__
#include <windows.h>
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/poll.h>
#endif /*__WIN32__*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

/*
 * 这是一个端口映射程序， 使用配置文件 conf/ports.conf, 格式如下：
 * listen_port remote_addr remote_port
 * 9191 172.21.3.187 22
 * 9192
 * */

#define SOCKTYPE_LISTEN   1
#define SOCKTYPE_CONNECT_LOCAL 2
#define SOCKTYPE_CONNECT_REMOTE 3

struct sockdata{
    int sock;
    int type; // SOCKTYPE_LISTEN  / SOCKTYPE_CONNECT_LOCAL / SOCKTYPE_CONNECT_REMOTE

    int    local_port;
    struct sockaddr_in remote_addr;
    struct sockdata *other;
    time_t last_active;                //最后活动时间， 用于检测超时

    struct sockdata *next;
};

//以空白字符切分字串， 连续的多个空白字符当作一个分割
int split_blank(char *string, char *fields[], int  nfields)
{
    char *p1;
    int i = 0, found = 0;

    fields[i++] = string;
    for(p1=string; *p1; p1++){
        if(*p1 == ' ' || *p1 == '\t'){
            *p1 = 0;
            found = 1;
        }else if(found == 1) {
            fields[i++] = p1;
            found = 0;
            if(i >= nfields)
                break;
        }
    }
    while(*(++p1)) if(*p1 =='\r' || *p1 == '\n') { *p1=0; break; } //删除行末的 \r \n
    return i;
}

typedef int (*fields_func) (char *flds[], int n, void *data);

static int read_file(const char *fname, fields_func callback, const int max_flds_per_line, void *data) {
    FILE *fp;
    char line[1024];
    char *fs[max_flds_per_line], *p;
    int fc, i = 0;

    fp = fopen(fname, "r");
    if(fp == NULL)
        return -1;
    while( fgets(line, sizeof(line)-1, fp) != NULL){
        if(line[0] == '#')
            continue;

        fc = split_blank(line, fs, max_flds_per_line);
        if(callback(fs, fc, data) != 0)
            break;
        i++;
    }
    fclose(fp);
    return i;
}

int tcp_close (int sd)
{
#ifdef __WIN32__
  return closesocket (sd);
#else
  return close (sd);
#endif
}

static int bind_port(char *flds[], int n, void *data) {
    struct sockdata *s, *s1;
    struct hostent *ht;
    int sd;
    int opt = 1;
    struct sockaddr_in servaddr;

    if(n < 3){
        printf("not enough fields %d\n", n);
        return 0;
    }

    s = (struct sockdata *)malloc(sizeof(struct sockdata));
    memset(s, 0, sizeof(struct sockdata));
    s->local_port = atoi(flds[0]);

    ht = gethostbyname (flds[1]);
    if (ht == NULL) {free(s); return -2; }


    memset (&servaddr, 0, sizeof (servaddr));

    s->remote_addr.sin_family = AF_INET;
    s->remote_addr.sin_port = htons (atoi(flds[2]) );
    s->remote_addr.sin_addr.s_addr = ((struct in_addr *) ht->h_addr_list[0])->s_addr;
    sd = socket (AF_INET, SOCK_STREAM, 0);

    if (sd < 0){ free(s); return -1; }

    // bind local port
    setsockopt (sd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof (opt));
    memset (&servaddr, 0, sizeof (servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons (s->local_port);
    servaddr.sin_addr.s_addr = INADDR_ANY; // inet_addr (local_ip);
    if (bind (sd, (struct sockaddr *) &servaddr, sizeof (servaddr)) < 0)
    {
        tcp_close (sd);
        free(s);
        return -3;
    }

    if (listen (sd, 5) < 0)
    {
        tcp_close (sd);
        free(s);
        return -4;
    }

    s->sock = sd;
    s->type = SOCKTYPE_LISTEN;
    s1 = (struct sockdata *)data;
    s->next = s1->next;
    s1->next = s;

    printf("listen on %s for %s:%s\n", flds[0], flds[1], flds[2]);

    return 0;
}

static void socket_init()
{
#ifdef __WIN32__
    WSADATA wdata;
    WSAStartup (MAKEWORD (1, 1), &wdata);
#endif
}


static inline int accept_connection(struct sockdata *s, struct sockdata *head){
    struct sockdata *s2, *s3;
    unsigned int addrlen;

    s2 = (struct sockdata*)malloc(sizeof(struct sockdata));
    memset(s2, 0, sizeof(struct sockdata));
    addrlen = sizeof(s2->remote_addr);
    s2->sock = accept(s->sock, (struct sockaddr *)&s2->remote_addr, &addrlen);
    if(s2->sock < 0){
        printf("accept failed\n");
        free(s2);
        return -1;
    }
    printf("connected from %s:%d on local-port: %d\n",
           inet_ntoa(s2->remote_addr.sin_addr), ntohs(s2->remote_addr.sin_port),
           s->local_port);
    s2->type = SOCKTYPE_CONNECT_LOCAL;
    s2->local_port = s->local_port;

    s3 = (struct sockdata*)malloc(sizeof(struct sockdata));
    memset(s3, 0, sizeof(struct sockdata));
    s3->sock = socket (AF_INET, SOCK_STREAM, 0);
    memcpy(&s3->remote_addr, &s->remote_addr, sizeof(s->remote_addr));
    if( connect (s3->sock, (struct sockaddr *) &s3->remote_addr, sizeof (s3->remote_addr)) != 0)
    {
        printf("connect to remote [%s:%d] failed\n",
               inet_ntoa(s3->remote_addr.sin_addr), ntohs(s3->remote_addr.sin_port));
        tcp_close (s2->sock);
        free(s2);
        tcp_close(s3->sock);
        free(s3);
        return -2;
    }
    s3->type = SOCKTYPE_CONNECT_REMOTE;
    printf("connected to: %s:%d, pair: %d-%d\n",
           inet_ntoa(s3->remote_addr.sin_addr), ntohs(s3->remote_addr.sin_port),
           s2->sock, s3->sock);

    s2->other = s3;
    s3->other = s2;

    // 挂上连接链表
    s2->next = s3;
    s3->next = head->next;
    head->next = s2;

    return 0;
}

static inline int recv_data(struct sockdata *s) {
    static char buf[4096];
    int ret, i;

    ret = recv(s->sock, buf, sizeof(buf), 0);
    if(ret == 0){
        // remote reset connection
        return 0;
    }else if(ret < 0) {
        printf("read data failed\n");
        return -1;
    }
    while(ret > 0) {
        i = send(s->other->sock, buf, ret, 0);
        if(i < 0){
            printf("write to remote failed\n");
            return 0;
        }
        ret -= i;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    struct sockdata sockhead, *s, *s1, *s2;
    const char *conf = "conf/ports.conf";
    int timeout = 5000; // ms

    fd_set rfd;
    int i, ret, maxfd, j;
    struct timeval tvl;
    int need_exit = 0;

    if(argc > 1)
        conf = argv[1];
    socket_init(); // for win32, invoke WSAStartup
    sockhead.next = NULL;
    read_file(conf, bind_port, 3, &sockhead);


    while(1){
        maxfd = 0;
        FD_ZERO (&rfd);
        tvl.tv_sec = timeout / 1000;
        tvl.tv_usec = (timeout % 1000) * 1000;

        //printf("begin select...\n");
        for (s1=&sockhead,s = sockhead.next; s; s1=s,s=s->next)
        {
            if(s->sock < 0) {
                /* marked closed */
                printf("remove paired sock\n");
                s1->next = s->next;
                free(s);
                s = s1;
            }else{
                FD_SET (s->sock, &rfd);
                maxfd = (s->sock > maxfd) ? s->sock : maxfd;
            }
        }
        maxfd += 1;

        ret = select (maxfd, &rfd, NULL, NULL, &tvl);
        if (ret < 0)
        {
            printf("select failed, break\n");
            break;
        }
        if(ret == 0){
            // timeout
            continue;
        }

        for(s=sockhead.next;s;s=s->next){
            if(s->sock < 0) continue;
            if (FD_ISSET (s->sock, &rfd) ){
                if(s->type == SOCKTYPE_CONNECT_LOCAL || s->type == SOCKTYPE_CONNECT_REMOTE){
                    //read data
                    ret = recv_data(s);
                    if(ret == 0){
                        // remote reset connection
                        printf("close pair: %d-%d s1: %x s: %x\n",
                               s->sock, s->other->sock, s1, s);
                        tcp_close(s->sock);
                        tcp_close(s->other->sock);
                        s->sock = -1;
                        s->other->sock = -1;
                        /*s1->next = s->next;
                        s->other->sock = -1; //mark to close other connection
                        free(s);
                        s = s1;
                        printf("done\n"); */

                    }else if(ret < 0) {
                        printf("read data failed\n");
                        need_exit = 1;
                        break;
                    }
                }else if(s->type == SOCKTYPE_LISTEN){
                    //accept
                    accept_connection(s, &sockhead);
                }
            }

        } // for
        if(need_exit == 1)
            break;
    }

    // close all
    s = sockhead.next;
    while(s) {
        printf("close local_port [%d]\n", s->local_port);
        tcp_close(s->sock);
        s1 = s->next;
        free(s);
        s = s1;
    }
    printf("sizeof long=%d\n", sizeof(long));

    return 0;
}
