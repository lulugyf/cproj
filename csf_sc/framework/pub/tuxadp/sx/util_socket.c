
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/poll.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



const char * tcp_name2ip(const char *server_name)
{
	struct hostent *ht;

	ht = gethostbyname(server_name);
	if(ht != NULL){
			return (char *)inet_ntoa(*(struct in_addr *)(ht->h_addr_list[0]));
	}
	return server_name;
}

/*socket close*/
int tcp_close(int sd){
        return close(sd);
}

/*接收连接*/
int tcp_accept(int sd, char *ip, int *port){
        int csd;
        struct sockaddr_in addr;
        unsigned int addrlen;

        memset(&addr, 0, sizeof(addr));
        addrlen = sizeof(addr);
        csd = accept(sd, (struct sockaddr *)&addr, &addrlen);

        if(csd > 0){
                strcpy(ip, (char *)inet_ntoa(addr.sin_addr));
                *port = ntohs(addr.sin_port);
        }

        return csd;
}

/*设置 recv 超时*/
void tcp_setrcvtimeo(int sd, int timeo)
{
        setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, &timeo, sizeof(timeo));
}
void tcp_keepalive(int sd, int alive)
{
        setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, &alive, sizeof(alive));
}

/*绑定本地端口并 进入 listen 状态*/
int tcp_listen(const char * local_ip, int port)
{
        int sd;
        struct sockaddr_in servaddr;
        int addrlen, opt = 1;

        int pid;

        sd = socket(AF_INET, SOCK_STREAM, 0);
        if(sd <= 0){
                return 0;
        }
        /* 端口重用
*********/
        setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
        memset(&servaddr, 0, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port   = htons(port);
        servaddr.sin_addr.s_addr =
                (local_ip==NULL) ? INADDR_ANY : inet_addr(local_ip);
        if( bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
                close(sd);
                return 0;
        }
        
        if( listen(sd, 10) < 0){
                close(sd);
                return 0;
        }
        return sd;
}

int tcp_connect(const char * server_name, int port)
{
        struct sockaddr_in servaddr;
        int addrlen;
        int sd = 0, ret;
        struct hostent *ht;

        sd = socket(AF_INET, SOCK_STREAM, 0);
        if(sd <= 0) {
                return -2;
        }

        ht = gethostbyname(server_name);
        if(ht == NULL){
                return -3;
        }

        memset(&servaddr, 0, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port   = htons(port);
        /*servaddr.sin_addr.s_addr = inet_addr(tcp_name2ip(server_name));*/
        servaddr.sin_addr.s_addr = ((struct in_addr *)ht->h_addr_list[0])->s_addr;
        
        ret=connect(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (ret!=0) {
                close(sd);
        return -4;
    }
        return sd;
}

/* 从 fd 读取固定长度字节, 返回实际读取的字节数 */
int tcp_readn(int fd, char *ptr, size_t n)
{
        int     nleft; 
        int     nread;
        char *pp, label[50];

        pp = ptr;
        nleft=n;
        while(nleft > 0)
        {
                if((nread = recv(fd, ptr, nleft, 0))<=0)
                {
                        printf("Err nread = %d\n",nread);
                        return -1;
                }
                else if(nread<=0)
                        break;

                nleft -=nread;
                ptr +=nread;
        }
        /*sprintf(label, "tcp_readn P(%d) S(%d)", getpid(), fd);
        printb(label, pp, n-nleft);
**********/
        return(n-nleft);        
}

int tcp_read (int sockid, char *buf, int len)
{
  return read (sockid, buf, len);
}


/* 向 fd 写入固定长度的字节, 返回实际写入的字节数 */
int tcp_writen(int fd, char *ptr, int nbytes)
{
    int nleft,nwritten;
        char *pp, label[50];
    nleft=nbytes;

        pp = ptr;

    while (nleft>0) 
        {
           nwritten=send(fd, ptr, nleft, 0);
           if(nwritten<=0)
                return(nwritten);
           nleft -= nwritten;
           ptr  += nwritten;
    }
        /*sprintf(label, "tcp_writen P(%d) S(%d)", getpid(), fd);
        printb(label, pp, nbytes-nleft);
**********/

    return(nbytes-nleft);
}


/****
下面 3 个函数采用异步IO方式控制socket操作的超时,
****/

/* 使用异步连接,
控制连接超时 timeout (milliseconds = 0.001 seconds)
*/
int tcp_connecta(const char * server_name, int port, int timeout)
{
        struct sockaddr_in servaddr;
        int addrlen;
        int sd = 0, ret;
        struct hostent *ht;

        const  int  fdcount = 1;
        struct pollfd pl[fdcount];

        sd = socket(AF_INET, SOCK_STREAM, 0);
        if(sd <= 0) {
                return 0;
        }

        pl[0].fd = sd;
        pl[0].events = POLLWRNORM | POLLRDNORM;
        pl[0].revents = 0;

        /* 修改为非阻塞工作方式
**********/
        fcntl(sd, F_SETFL, O_NONBLOCK);

        ht = gethostbyname(server_name);
        if(ht == NULL){
                return 0;
        }

        memset(&servaddr, 0, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port   = htons(port);
        /*servaddr.sin_addr.s_addr = inet_addr(tcp_name2ip(server_name));*/
        servaddr.sin_addr.s_addr = ((struct in_addr *)ht->h_addr_list[0])->s_addr;
        
        errno = 0;
        ret = connect(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        if(ret == -1 && errno == EINPROGRESS){
                /*printf("connect in progress...\n");
                等待检测是否连接成功, 超时 200 毫秒
*****************/
            errno = 0;
                poll(pl, fdcount, timeout);
                if ( pl[0].revents != POLLWRNORM && pl[0].revents != POLLRDNORM){
                        printf("timeout\n");
                        close(sd);
                        return 0;
                }
        }else if (ret != 0) {
                close(sd);
        return 0;
    }
        /*printf("connect OK\n");
**********/
        return sd;
}

/* 从 fd 读取固定长度字节, 返回实际读取的字节数
控制读超时 timeout (milliseconds = 0.001 seconds)
*/
int tcp_reada(int fd, char *ptr, int len, int timeout)
{
    int nread;
    const  int  fdcount = 1;
    struct pollfd pl[fdcount];

    pl[0].fd = fd;
    pl[0].events = POLLRDNORM;
    pl[0].revents = 0;

    errno = 0;
    poll(pl, fdcount, timeout);
    if ( pl[0].revents & POLLRDNORM ||  pl[0].revents & POLLIN ){
        nread = read(fd, ptr, len);
        printf("nread [%d] len[%d]\n", nread, len);
    }else{
        printf("read timeout.. errno[%d] pl[0].revents=[%d]\n", errno, pl[0].revents);
        return 0;
    }

    return nread;
}


/* 向 fd 写入固定长度的字节, 返回实际写入的字节数
控制写超时 timeout (milliseconds == 0.001 seconds)
*/
int tcp_writea(int fd, char *ptr, int nbytes, int timeout)
{
    int nwritten;
        const  int  fdcount = 1;
        struct pollfd pl[fdcount];

        pl[0].fd = fd;
        pl[0].events = POLLWRNORM;
        pl[0].revents = 0;

        poll(pl, fdcount, timeout);
        if ( pl[0].revents != POLLWRNORM ){
                printf("write timeout\n");
                return 0;
        }

    nwritten = write(fd, ptr, nbytes);
        printf("write return[%d]  nbytes[%d]\n", nwritten, nbytes);

    return nwritten;
}

int tcp_readline(int sockid, char* command_buf, const int BUFLEN)
{
        int i, length;

    length = -1;
        for(i = 0; i < BUFLEN; ++i)
        {
                recv(sockid, command_buf + i, 1, 0);
                if(i > 0 && command_buf[i - 1] == '\r' && command_buf[i] == '\n')
                {
                        /* Remove the CRLF. */
                        command_buf[i - 1] = 0;
                        break;
                }
        }

        /* If we read MAXLEN characters but never got a CRLF then
        / eat all the characters until we get a CRLF. */
        if(i == BUFLEN)
        {
                char cur = command_buf[BUFLEN - 1];
                char last = 0;
                
                while(last != '\r' || cur != '\n')
                {
                        last = cur;
                        recv(sockid, &cur, 1, 0);
                }

                command_buf[BUFLEN - 1] = 0;
        }

        if(i < BUFLEN && i > 0)
                length = (unsigned int)i - 1;

        return length;
}

int tcp_writeline(int sockid, char *buf){
    int i, r;
    i = strlen(buf);
    r = tcp_writen(sockid, buf, i);
    if(r != i)
        return -1;
    r = tcp_writen(sockid, "\r\n", 2);
    if(r != 2)
        return -2;
    return i+2;
}


/*
 * 绑定本地端口
 */
int udp_bind (const char *local_ip, int port)
{
  struct sockaddr_in servaddr;
  int opt;
  int sd;

  sd = udp_socket ();
  if (sd <= 0)
    {
      return -1;
    }

  opt = 1;
  setsockopt (sd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof (opt));
  memset (&servaddr, 0, sizeof (servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons (port);
  servaddr.sin_addr.s_addr =
    (local_ip == NULL) ? INADDR_ANY : inet_addr (local_ip);
  if (bind (sd, (struct sockaddr *) &servaddr, sizeof (servaddr)) < 0)
    {
      tcp_close (sd);
      return -2;
    }
  return sd;
}


/*接收报文*/
int udp_recvfrom (int sd, char *ip, int *port, char *buf, int maxlen)
{
  int n;
  struct sockaddr_in addr;
  unsigned int addrlen;

  memset (&addr, 0, sizeof (addr));
  addrlen = sizeof (addr);

  n = recvfrom(sd, buf, maxlen, 0, (struct sockaddr *) &addr, &addrlen);

  if (n > 0)
    {
      if(ip != NULL)
          strcpy (ip, (char *) inet_ntoa (addr.sin_addr));
      if(port != NULL)
          *port = ntohs (addr.sin_port);
    }
  return n;
}

/*发送报文*/
int udp_sendto(int sd, void *addr, char *buf, int len)
{
    struct sockaddr_in *servaddr;
    int l;
    servaddr = (struct sockaddr_in *)addr;
    l = sizeof(struct sockaddr_in);
    printf("====rzp udp_sendto send %s:", buf);
    return sendto(sd, buf, len, 0, (struct sockaddr *)servaddr, l);
}

void *udp_make_addr(const char *addr)
{
	char *p, *p1;
	if(memcmp(addr, "udp://", 6) != 0){
		return NULL;
	}
	p = strdup(addr+6);
	p1 = strchr(p, ':');
	if(p1 == NULL){
		free(p);
		return NULL;
	}
	*p1 = 0;
	p1 ++;

	struct hostent *ht = gethostbyname (p);
	struct sockaddr_in *servaddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
	memset(servaddr, 0, sizeof(struct sockaddr_in));
	servaddr->sin_family = AF_INET;
	servaddr->sin_port = htons (atoi(p1));
	/*servaddr.sin_addr.s_addr = inet_addr(tcp_name2ip(server_name)); */
	servaddr->sin_addr.s_addr = ((struct in_addr *) ht->h_addr_list[0])->s_addr;
	return servaddr;
}

int udp_socket()
{
    return socket (AF_INET, SOCK_DGRAM, 0);
}

static void __udp_getlocaladdr(int sd)
{
	struct sockaddr_in localAddress;
	socklen_t addressLength = sizeof(localAddress);
	getsockname(sd, (struct sockaddr*)&localAddress,
	                &addressLength);
	printf("local address: %s\n", inet_ntoa( localAddress.sin_addr));
	printf("local port: %d\n", (int) ntohs(localAddress.sin_port));
}

void udp_close(int s)
{
	close(s);
}


void udp_getlocaladdr(char addr[16])
{
	char hostname[64];
	int len, i;
	struct hostent *ht;
	const char *a;

	len = sizeof(hostname);
	gethostname(hostname, len);

	ht = gethostbyname(hostname);
	printf("len:%d in_addr:%d\n", ht->h_length, sizeof(struct in_addr));
	for(i=0; i<ht->h_length/sizeof(struct in_addr); i++){
		a = inet_ntoa(*(struct in_addr *)(ht->h_addr_list[i]));
		//printf("::%s\n", a);
		if(memcmp(a, "127.",4) != 0)
			strcpy(addr, a);
	}
}


#ifdef __TEST__
int main()
{
	int d;
	void *addr;
	addr = udp_make_addr("udp://10.10.10.10:1234");
	d = udp_socket();
	udp_sendto(d, addr, "hello", 4);
	udp_getlocaladdr(d);
	udp_close(d);

	test11();
	return 0;
}
#endif
