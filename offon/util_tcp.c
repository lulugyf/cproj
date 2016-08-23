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
#include <errno.h>
#include <util_tcp.h>

#ifndef POLLWRNORM
#define POLLWRNORM 0x100
#define POLLRDNORM 0x040
#endif

const char * tcp_name2ip (const char *server_name)
{
  struct hostent *ht;

  ht = gethostbyname (server_name);
  if (ht > 0)
    {
      return (char *) inet_ntoa (*((struct in_addr *) ht->h_addr_list));
    }
  return server_name;
}

int tcp_close (int sd)
{
#ifdef __WIN32__
  return closesocket (sd);
#else
  return close (sd);
#endif
}

#ifdef __WIN32__
int WSA_init = 0;
int tcp_socket ()
{
    if (WSA_init == 0)
    {
        WSADATA wdata;
        WSAStartup (MAKEWORD (1, 1), &wdata);
        WSA_init = 1;
    }
    return socket (AF_INET, SOCK_STREAM, 0);
}
#else
int tcp_socket()
{
    return socket (AF_INET, SOCK_STREAM, 0);
}
#endif


/*��������*/
int tcp_accept (int sd, char *ip, int *port)
{
  int csd;
  struct sockaddr_in addr;
  unsigned int addrlen;

  memset (&addr, 0, sizeof (addr));
  addrlen = sizeof (addr);
  csd = accept (sd, (struct sockaddr *) &addr, &addrlen);

  if (csd > 0)
    {
      strcpy (ip, (char *) inet_ntoa (addr.sin_addr));
      *port = ntohs (addr.sin_port);
    }
  return csd;
}

/*
 * �󶨱��ض˿�
 */
int tcp_bind (const char *local_ip, int port)
{
  struct sockaddr_in servaddr;
  int opt;
  int sd;

  sd = tcp_socket ();
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

int tcp_readline(int sockid, char* command_buf, const int BUFLEN)
{
	int i, length;

    length = -1;
	for(i = 0; i < BUFLEN; ++i)
	{
		if(recv(sockid, command_buf + i, 1, 0) < 1){
            if(i == 0)
                return -1;
            break;
        }
		if(i > 0 && command_buf[i - 1] == '\r' && command_buf[i] == '\n')
		{
			/* Remove the CRLF. */
			command_buf[i - 1] = 0;
			break;
		}
        if(i > 0 && command_buf[i] == '\n'){
			command_buf[i] = 0;
			break;
        }
	}

	/* If we read MAXLEN characters but never got a CRLF then
	// eat all the characters until we get a CRLF. */
	if(i == BUFLEN)
	{
		char cur = command_buf[BUFLEN - 1];
		char last = 0;
		
		while(last != '\r' || cur != '\n')
		{
			last = cur;
			if(recv(sockid, &cur, 1, 0) < 1)
                break;
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


/*�󶨱��ض˿ڲ� ���� listen ״̬*/
int tcp_listen (const char *local_ip, int port)
{
  int sd;
  sd = tcp_bind (local_ip, port);
  if (sd <= 0)
    return sd;

  if (listen (sd, 50) < 0)
    {
      tcp_close (sd);
      return -3;
    }
  return sd;
}

int tcp_connect (const char *server_name, int port)
{
  struct sockaddr_in servaddr;
  int sd = 0, ret;
  struct hostent *ht;

  sd = tcp_socket ();
  if (sd <= 0)
    {
      return 0;
    }

  ht = gethostbyname (server_name);
  if (ht == NULL)
    {
      return 0;
    }

  memset (&servaddr, 0, sizeof (servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons (port);
  /*servaddr.sin_addr.s_addr = inet_addr(tcp_name2ip(server_name)); */
  servaddr.sin_addr.s_addr = ((struct in_addr *) ht->h_addr_list[0])->s_addr;

  ret = connect (sd, (struct sockaddr *) &servaddr, sizeof (servaddr));
  if (ret != 0)
    {
      tcp_close (sd);
      return 0;
    }
  return sd;
}

#ifndef __WIN32__
int tcp_connecta (const char *server_name, int port, int timeout)
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
    return sd;
}
#endif /* __WIN32__ */

int tcp_read (int sockid, char *buf, int len)
{
  return read (sockid, buf, len);
}

int tcp_reada (int sockid, char *buf, int len, int timeout)
{
	int ret;
	ret = tcp_check_read(&sockid, 1, timeout);
	if(ret <= 0)
			return ret;
  return recv (sockid, buf, len, 0);
}

int tcp_write (int sockid, char *buf, int len)
{
  return send (sockid, buf, len, 0);
}

/* �� fd ��ȡ�̶������ֽ�, ����ʵ�ʶ�ȡ���ֽ��� */
int tcp_readn (int fd, char *ptr, int n)
{
  int nleft;
  int nread;
  char *pp;

  pp = ptr;
  nleft = n;
  while (nleft > 0)
    {
      if ((nread = tcp_read (fd, ptr, nleft)) <= 0)
	{
	  printf ("Err nread = %d\n", nread);
	  return -1;
	}
      else if (nread <= 0)
	break;

      nleft -= nread;
      ptr += nread;
    }
  return (n - nleft);
}

/* �� fd ��ȡ�̶������ֽ�, ����ʵ�ʶ�ȡ���ֽ���, ��ʱ timeout ���� */
int tcp_readna (int fd, char *ptr, int n, int timeout)
{
  int nleft;
  int nread;
  char *pp;

  pp = ptr;
  nleft = n;
  while (nleft > 0)
    {
      if ((nread = tcp_reada (fd, ptr, nleft, timeout)) <= 0)
	{
	  printf ("Err nread = %d\n", nread);
	  return -1;
	}
      else if (nread <= 0)
	break;

      nleft -= nread;
      ptr += nread;
    }
  return (n - nleft);
}

/* �� fd д��̶����ȵ��ֽ�, ����ʵ��д����ֽ��� */
int tcp_writen (int fd, char *ptr, int nbytes)
{
  int nleft, nwritten;
  char *pp;
  nleft = nbytes;
  pp = ptr;
  while (nleft > 0)
    {
      nwritten = tcp_write (fd, ptr, nleft);
      if (nwritten <= 0)
	return (nwritten);
      nleft -= nwritten;
      ptr += nwritten;
    }
  return (nbytes - nleft);
}

/**
 * �����sock״̬�Ƿ�ɶ�, �������õ�״̬����, 
 * @socks: array of socket handle
 * @count: in, count of sockets handle
 * @timeout: max wait time, in 1/1000 seconds
 */
int tcp_check_read (int *socks, int count, int timeout)
{
  fd_set rfd;
  int i, ret, fds, j;
  struct timeval tvl;

  fds = 0;
  FD_ZERO (&rfd);
  for (i = 0; i < count; i++)
    {
      FD_SET (socks[i], &rfd);
      fds = (socks[i] > fds) ? socks[i] : fds;
    }
  fds++;
  tvl.tv_sec = timeout / 1000;
  tvl.tv_usec = (timeout % 1000) * 1000;

  ret = select (fds, &rfd, NULL, NULL, &tvl);
  if (ret <= 0)
    {
      return ret;
    }
  j = 0;
  for (i = 0; i < count; i++)
    {
      if (FD_ISSET (socks[i], &rfd))
	{
	  socks[j++] = socks[i];
	}
    }
  return ret;
}


#ifdef __WIN32__
int udp_socket ()
{
    if (WSA_init == 0)
    {
        WSADATA wdata;
        WSAStartup (MAKEWORD (1, 1), &wdata);
        WSA_init = 1;
    }
    return socket (AF_INET, SOCK_DGRAM, 0);
}
#else
int udp_socket()
{
    return socket (AF_INET, SOCK_DGRAM, 0);
}
#endif

/*
 * �󶨱��ض˿�
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


/*���ձ���*/
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

/*���ͱ���*/
int udp_sendto(int sd, char *ip, int port, char *buf, int len)
{
    struct sockaddr_in servaddr;
    int l;
    struct hostent *ht;

    ht = gethostbyname (ip);
    if (ht == NULL)
    {
        return 0;
    }

    memset (&servaddr, 0, sizeof (servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons (port);
    /*servaddr.sin_addr.s_addr = inet_addr(tcp_name2ip(server_name)); */
    servaddr.sin_addr.s_addr = ((struct in_addr *) ht->h_addr_list[0])->s_addr;
    l = sizeof(servaddr);
    return sendto(sd, buf, len, 0, (struct sockaddr *)&servaddr, l);
}
