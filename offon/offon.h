/**********************************************************
 *  FileName:
 *      offon.h
 *
 *  Version:
 *      1.00 2004.11.08
 *
 *  tabstop = 4
 *
 **********************************************************/
#ifndef __INCLUDE_OFFON_H__
#define __INCLUDE_OFFON_H__

#include "h.h"

#define	VERSION "2.0"

#define DBLOGIN				"/gdblogin.cfg"
#define CUSTDB				"/custdb.cfg"

#define TERM_HLR			'1'
#define TERM_AUC			'2'
#define TERM_DATACENTER		'3'
#define	TERM_ENTRY			'4'
#define	TERM_QUERY			'5'

#define TERM_TAS            '7'
#define TERM_HSS            '8'
#define TERM_ENUM           '9'

#define	MSISDNLEN			15
#define	IMSILEN				20
#define	SSINFO1LEN			15
#define	SSINFO2LEN			20
#define	SSINFO3LEN			120
#define	QUERYINFOLEN		200

/* �û����Ϲ��� */
struct user_info
{
	char				user[12];			/* �û����� */
	char				pswd[12];			/* �û����� */
	char				hlrcode[4];			/* ���������� */
	char				hlrport;			/* �������˿� */
	char				type;				/* �ն����� */
	char				encrypt;			/* ���ܱ�־ */
	char				termid[12];			/* �ն˱�ʶ */
	struct user_info	*next;
};

/* define login status */
#define		LOGIN_INIT			'0'			/* ���ӽ�����δע�� */
#define		LOGIN_REGISTER		'1'			/* ע��ɹ� */

/* ͨ�����ӹ��� */
struct comm_info
{
	char				login;				/* �û�״̬��ʶ */
	char				termtype;			/* �ն����� */
	char				encrypt;			/* ���ܱ�־ */
	char				cipher[8];			/* ��Կ */
	int					sockid;				/* ͨ�������� */
	struct sockaddr_in	cliaddr;			/* �ͻ��˵�ַ */
	time_t				begintime;			/* ��½ʱ�� */
	time_t				reqtime;			/* ��������ʱ�� */
	time_t				sndtime;			/* ������ʱ�� */
	long				cmdid;				/* ��������ID */
	struct user_info	userinfo;			/* �û����� */
	struct comm_info	*next;
};

/* ҵ�������뽻����ָ�����ù�ϵ */
struct cmdtoorder
{
	char				hlrcode[4];			/* ���������� */
	int					cmdcode;			/* ҵ��������� */
	int					priority;			/* �������ȼ� */
	int					ordercode;			/* ������ָ����� */
	char				type;				/* ָ������ */
	int					serial;				/* ������ָ����� */
	struct cmdtoorder	*next;
};

#define		REDUCE_FIRST		'1'
#define		REDUCE_BACK			'2'
#define		REDUCE_ALL			'3'

/* ������ָ�����ع��� */
struct order_reduce
{
	char				hlrcode[4];			/* ���������� */
	int					old_order_code;		/* ��ָ����� */
	int					new_order_code;		/* ��ָ����� */
	char				operate;			/* �������� */
	struct order_reduce	*next;
};

/* �����쳣ָ������� */
struct order_resend
{
	char				hlrcode[4];			/* ���������� */
	int					order_code;			/* ָ����� */
	char				func_code[8];		/* ���ܴ��� */
	struct order_resend	*next;
};

/* ָ��Ӧ����Ϣ�������� */
struct reply_parse
{
	char				hlrcode[4];			/* ���������� */
	int					cmd_code;			/* ҵ��������� */
	int					order_code;			/* ԭʼָ�� */
	int					reply_code;			/* Ӧ���� */
	int					parse_result;		/* ������� */
	char				revise;				/* �Ƿ���ҪУ�� */
	int					dest_order;			/* Ŀ��ָ�� */
	char				order_type;			/* Ŀ��ָ������ */
	int					serial;				/* Ŀ��ָ����� */
	struct reply_parse	*next;
};

/* ��ѯָ�������� */
struct query_parse
{
	char				hlrcode[4];			/* ���������� */
	int					cmd_code;			/* ҵ��������� */
	int					order_code;			/* ָ����� */
	int					src_beg;			/* Դ�ַ�����ʼλ */
	int					data_len;			/* ���ݳ��� */
	int					dest_station;		/* Ŀ���ַ���λ�� */
	int					dest_beg;			/* Ŀ���ַ�����ʼλ */
	struct query_parse	*next;
};

/* ��ѯͬ������ */
struct query_revise
{
	int					cmd_code;			/* ҵ��������� */
	int					order_code;			/* ָ����� */
	int					reply_code;			/* ָ����ɴ��� */
	char				func_code[8];		/* ���ܴ��� */
	char				status_flag;		/* ����״̬ͬ����־ */
	char				info_flag;			/* ������Ϣͬ����־ */
	int					status_addr;		/* ����״̬λ�� */
	char				status_null;		/* ����״̬��ֵ��ʶ */
	int					info_beg;			/* ������Ϣ��� */
	int					info_len;			/* ������Ϣ���� */
	struct query_revise	*next;
};

/* ������ָ��������Ϣ */
struct order_info
{
	int					ordercode;			/* ������ָ����� */
	char				orderinfo[1024];	/* ������ָ�������ʽ */
	struct order_info	*next;
};

/* ������Ӧ��������Ϣ */
struct reply_info
{
	int					replycode;			/* ������Ӧ����� */
	char				replyinfo[256];		/* ������Ӧ�������ʽ */
	struct reply_info	*next;
};

/* ������������Ϣ */
struct mcfg_info
{
	char				hlrcode[4];			/* ���������� */
	char				ipaddr[32];			/* IP��ַ */
	int					commport;			/* ͨ�Ŷ˿� */
	struct mcfg_info	*next;
};

/* �Ŷζ˿ڶ�����Ϣ */
struct phead_port
{
	int					phead;				/* ��Ŷ� */
	int					port;				/* ͨ�Ŷ˿� */
	char				hlrcode[4];			/* ���������� */
};

#define		MAX_PHEAD		8192

/* �Ŷ�HLR������Ϣ */
struct phead_hlr
{
	int					phead;				/* ��Ŷ� */
	char				hlrcode[4];			/* ���������� */
	struct phead_hlr	*next;
};

#define		MAXOPCODENUM	8192

/* ҵ��������ȼ����� */
struct opcode_pri
{
	char				op_code[8];			/* ҵ����� */
	int					priority;			/* ���ȼ� */
	struct opcode_pri	*next;
};

/* �û����Ϲ������ */
struct usrdata_mgr
{
	int					order_code;
	char				func_code[6];
	char				func_status;
	char				ss_info[128];
	struct usrdata_mgr	*next;
};

/* �����ͽ�����ָ����� */
#define		GENERAL_CMD			0
#define		REVISE_CMD			2
#define		REDUCE_CMD			1001

struct orderwait
{
	int					ordercode;			/* ָ����� */
	char				type;				/* ָ������ */
	int					serial;				/* ָ����� */
	int					status;				/* ָ��״̬ */
	struct orderwait	*next;
};

/* ������ҵ��������� */
#define		BOSS_CMD			0
#define		PARSE_CMD			1
struct cmdwait
{
	long				streamid;					/* ������ˮ�� */
	char				cmdid[20];					/* ҵ��������ˮ�� */
	char				opcode[8];					/* ҵ����� */
	int					cmdcode;					/* ҵ��������� */
	char				status;						/* ҵ������״̬ */
	int					priority;					/* �������ȼ� */
	char				msisdn[MSISDNLEN+1];		/* �ƶ����� */
	char				imsi[IMSILEN+1];			/* IMSI���� */
	char				ss_info1[SSINFO1LEN+1];		/* ������Ϣ1 */
	char				ss_info2[SSINFO2LEN+1];		/* ������Ϣ2 */
	char				ss_info3[SSINFO3LEN+1];		/* ������Ϣ3 */
	char				req_time[16];				/* ��������ʱ�� */
	char				queryinfo[QUERYINFOLEN+1];	/* ��ѯ��Ϣ */
	struct orderwait	orderhead;					/* ָ�����ͷ�ڵ� */
	struct cmdwait		*next;
};

/* ������Ϣ�ڵ� */
struct phonewait
{
	time_t				status;				/* ����״̬ */
	char				type;				/* ָ������ */
	struct cmdwait		cmdhead;			/* �������ͷ�ڵ� */
};

#define		MAXPHEADNUM	 1000

/* �Ŷι������ */
struct phonehead
{
	char				hlrcode[4];			/* ���������� */
	int					phead;				/* ��Ŷ� */
	struct phonewait	*ptail[10000];		/* ������Ϣ�ڵ� */
	struct phonehead	*next;
};

/* ������������ */
struct phoneidx
{
	char				msisdn[MSISDNLEN+1];	/* �ƶ����� */
	int					phead;					/* ��Ŷ� */
	int					ptail;					/* �������λ */
	struct phoneidx		*next;
};

/* ���ȼ��������� */
struct priorityidx
{
	int					priority;			/* ���ȼ� */
	int					num;				/* �������� */
	struct phoneidx		phonehead;			/* �����������нڵ� */
	struct phoneidx     phonetail;          /* ������������β��  2008-12�¼� */
	struct priorityidx	*next;
};


struct query_info
{
	char	msisdn[11];
	char	imsi[15];
	char	toll;
	char	roam;
	char	gprs;
	char	sms_snd;
	char	sms_rcv;
	char	cfu;
	char	cfbusy;
	char	cfnreply;
	char	cfnreach;
	char	cw;
	char	ch;
	char	mpty;
	char	cboc;
	char	cbic;
	char	fax;
	char	bs;
	char	clip;
	char	soclip;
	char	clir;
	char	soclir;
	char	odboc;
	char	odbic;
	char	bs31;
	char	mrbt;
	char	ici;
	char	tcsi;
	char	ocsi;
	char	ocamel_srvkey[2];
	char	ocamel_gsmid[12];
	char	tcamel_srvkey[2];
	char	tcamel_gsmid[12];
};

#define		MSGFLAG			"`CD'"

#define		VER100			"100"

#define		REQ_TYPE		'1'
#define		ACK_TYPE		'2'

#define		ENCRYPT			'1'
#define		DECRYPT			'2'

#define		TX_BEG			'1'
#define		TX_CON			'2'
#define		TX_END			'3'

/* ����ͨ����Ϣ��ʽ */
struct comm_data
{
	char				flag[4];			/* `CD' */
	char				msglen[4];			/* ��Ϣ�ܳ��ȣ�����Ϣͷ�� */
	char				srvtype[8];			/* ҵ������ */
	char				transid[8];			/* ����ID��Ψһ��ʶ�� */
	char				finished;			/* ���������־ */
	char				msgtype;			/* REQ & ACK */
	char				encrypt;			/* �������� */
	char				reserve[5];			/* ���� */
	char				data[10000];		/* ҵ������ */
};

#define		CONN_KEEP	00000010

#define		ACK0000		0000,"success"
#define		ACK0001		0001,"UNKNOW SRVTYPE"
#define		ACK0011		0011,"LOGIN FAILED"
#define		ACK0012		0012,"INCORRECT USERNAME"
#define		ACK0013		0013,"INCORRECT USERPSWD"
#define		ACK0021		0021,"UNREGISTERED"
#define		ACK0101		0101,"UNKNOW ERROR"
#define		ACK1001		1001,"UNKNOW PHONE_HEAD"
#define		ACK1002		1002,"UNKNOW COMMAND_CODE"
#define		ACK2001		2001,"UNKNOW QUERY_TYPE"
#define		ACK2002		2002,"PHONE_NO NOT EXIST"
#define		ACK2003		2003,"CAN'T OPEN QRY_FILE"
#define		ACK3001		3001,"NO DATAS"
#define		ACK3002		3002,"PHONE_NO NOT EXIST"
#define		ACK3003		3003,"STREAM_ID NOT EXIST"

/* ͨ��Ӧ����Ϣ��00000000�� */
#define		GENERAL_ACK		00000000
struct general_ack
{
	char				retn[4];			/* ������� */
	char				desc[60];			/* ������� */
};

/* ��½�����Ự��00000001�� */
#define		SRV_LOGIN		00000001
struct login_req
{
	char				username[8];		/* �û����� */
	char				userpswd[8];		/* �û����� */
	char				hlrcode[4];			/* ���������� */
	char				hlrport;			/* ͨ�Ŷ˿� */
	char				termtype;			/* �ն����� */
	char				reserve[2];			/* ���� */
};
#define		LOGINREQLEN		sizeof(struct login_req)

struct login_ack
{
	char				retn[4];			/* ���ش��� */
	char				encrypt;			/* ���ܱ�־ */
	char				reserve[3];			/* ���� */
	char				cipher[8];			/* ��Կ */
};
#define		LOGINACKLEN		sizeof(struct login_ack)

/* ���ػ�ҵ���������ݸ�ʽ��10000001��
offon_entry �� manager���͵�ָ�����ݣ� ������¼��ʽ
*/
#define		SRVCODE0001		10000001
struct op_data_req
{
	char				command_id[16];		/* ������ˮ��ҵ�������Ψһ��ʶ */
	char				phone_no[MSISDNLEN+1];	/* �ƶ��绰���� */
	char				imsi_no[IMSILEN+1];		/* IMSI���� */
	char				op_code[6];				/* ҵ����� */
	char				command_code[6];		/* ����������� */
	char				cmd_status;				/* ҵ��״̬ */
	char				phone_priority;			/* �������ȼ� */
	char				ss_info1[SSINFO1LEN+1];	/* ������Ϣ1 */
	char				ss_info2[SSINFO2LEN+1];	/* ������Ϣ2 */
	char				ss_info3[SSINFO3LEN+1];	/* ������Ϣ3 */
	char				req_time[16];			/* ��������ʱ�� */
	char				login_no[8];			/* ���� */
};
#define		SRVLEN0001		sizeof(struct op_data_req)

struct op_data_ack
{
	char				retn[4];			/* ������� */
	char				desc[60];			/* ������� */
};

/* ���ػ�ָ�����ݸ�ʽ��10000002�� */
#define		GETORDER		10000002
#define		ONLY_GET		'1'
#define		REPLY_GET		'2'
struct cmd_data_req
{
	char				retn[4];				/* ���ش��� */
	char				type;					/* ָ������ */
	char				phone_no[MSISDNLEN+1];	/* �ƶ����� */
	char				stream_id[16];		/* ������ˮ��ҵ�������Ψһ��ʶ */
	char				ordercode[4];			/* ָ����� */
	char				info[QUERYINFOLEN+1];	/* ��ѯ��Ϣ */
};
#define		CMDREQLEN		sizeof(struct cmd_data_req)

struct cmd_data_ack
{
	char				retn[4];				/* ���ش��� */
	char				stream_id[16];		/* ������ˮ��ҵ�������Ψһ��ʶ */
	char				ordercode[4];			/* ָ����� */
	char				phone_no[MSISDNLEN+1];	/* �ƶ��绰���� */
	char				imsi_no[IMSILEN+1];		/* IMSI���� */
	char				ss_info1[SSINFO1LEN+1];	/* ������Ϣ1 */
	char				ss_info2[SSINFO2LEN+1];	/* ������Ϣ2 */
	char				ss_info3[SSINFO3LEN+1];	/* ������Ϣ3 */
	/*char				queryinfo[QUERYINFOLEN+1];	 ��ѯ��Ϣ */
};
#define		CMDACKLEN		sizeof(struct cmd_data_ack)

/* ����״̬��ѯ���ݸ�ʽ��20000001�� */
#define		QUERY0001		20000001
struct query0001_req
{
	char				type;				/* ��ѯ���� */
	char				datas[64];			/* ��ѯ���� */
};
#define		QRYLEN0001		sizeof(struct query0001_req)

struct query0001_ack
{
	char				retn[4];			/* ��ѯ������ */
	char				fname[60];			/* ��ѯ����ļ����� */
};

struct attr
{
    char        id[64];
    char        val[1024];
    struct attr *next;
};

struct RongZai
{
	char				tname[64];
	char				suff[32];
	char				tmpdir[256];
	char				snddir[256];
	char				bakdir[256];
	struct RongZai		*next;
};

#endif /*__INCLUDE_OFFON_H__ */

