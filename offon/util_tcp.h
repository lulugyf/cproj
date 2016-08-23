#ifndef _UTIL_TCP_H_
#define _UTIL_TCP_H_

#ifndef zero
#define zero(a) memset(a,0,sizeof(a))
#endif

typedef void (*tcp_call_back) (int sockid, char *clientip, int clientport,
			       void *parm, int servsockid);

const char *tcp_name2ip (const char *server_name);

int tcp_close (int sd);

int tcp_socket ();

/*��������*/
int tcp_accept (int sd, char *ip, int *port);

/*
 * �󶨱��ض˿�
 */
int tcp_bind (const char *local_ip, int port);

/*�󶨱��ض˿ڲ� ���� listen ״̬*/
int tcp_listen (const char *local_ip, int port);

int tcp_connect (const char *server_name, int port);

int tcp_connecta (const char *server_name, int port, int timeout);

int tcp_read (int fd, char *ptr, int len);

int tcp_reada (int fd, char *ptr, int len, int timeout);

int tcp_write (int fd, char *ptr, int len);

/* �� fd ��ȡ�̶������ֽ�, ����ʵ�ʶ�ȡ���ֽ��� */
int tcp_readn (int fd, char *ptr, int n);

/* �� fd ��ȡ�̶������ֽ�, ����ʵ�ʶ�ȡ���ֽ���, ��ʱ����timeout ���� */
int tcp_readna (int fd, char *ptr, int n, int timeout);

/* �� fd д��̶����ȵ��ֽ�, ����ʵ��д����ֽ��� */
int tcp_writen (int fd, char *ptr, int nbytes);

int tcp_check_read (int *socks, int count, int timeout);

/*��ȡһ�У� �� \r\n �ֽ�*/
int tcp_readline(int sockid, char* command_buf, const int BUFLEN);
int tcp_writeline(int sockid, char *buf);



/*************************************************/
/************************ for udp ****************/
/*************************************************/
int udp_socket();
int udp_bind (const char *local_ip, int port);
int udp_recvfrom (int sd, char *ip, int *port, char *buf, int maxlen);
int udp_sendto(int sd, char *ip, int port, char *buf, int len);


#endif /*_UTIL_TCP_H_*/
