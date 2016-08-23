#include "offon.h"
#include "db_func.h"

#define zero(a) memset(a, 0, sizeof(a))
#define init(a) memset(a, 0, sizeof(a))


char hlrcode[8];
char bakhlr[8];
FILE *logfp;

char *procname;

struct comm_data	tcpbuf;
struct op_data_req	*reqinfo;
struct op_data_ack	*ackinfo;

struct user_info	userhead,*userptr;
struct mcfg_info	mcfghead,*mcfgptr;

int					connid;
int					commport;
struct sockaddr_in	srvaddr;
struct
{
    char				hlr;
    int					flag;
    int					status;
    struct sockaddr_in	addr;
} hlraddr[256];


struct
{
    char rectype[20];
    char hlrcode[6];
    char db1[10];
    time_t rec_time;
    int rows;
    int tm4sel;
    int tm4fch;
    int tm4req;
    int tm4upd;
    int tm4ins;
    int tm4dul;
} yy_time;

extern int GenDaemon();
extern int testdir();
extern int db_login();
extern char *rlspace(char *);

void usage(char *s)
{
    printf("%s\n\nUsage:%s -Hhlrcode [-Dhlrcode] [-Udbuser -Pdbpswd -Sdbname] [-Llogdir] [-v]\n\n\n",s,procname);
    exit(1);
}

void LogOut(int sig)
{
    printf("LogOut signal==%d\n",sig);
    if(logfp)
    {
        fprintf(logfp,"LogOut signal==%d\n",sig);
        fclose(logfp);
    }

    exit(1);
}

int send_req(int id,int encrypt,int finished,int srvtype,int transid,int length)
{
    char chlen[16];

    length+=32;
    memcpy(tcpbuf.flag,MSGFLAG,4);
    sprintf(chlen,"%04d",length);
    memcpy(tcpbuf.msglen,chlen,4);
    sprintf(tcpbuf.srvtype,"%08d",srvtype);
    sprintf(tcpbuf.transid,"%08d",transid);
    tcpbuf.finished=finished;
    tcpbuf.msgtype=REQ_TYPE;
    tcpbuf.encrypt=encrypt;
    /*memcpy(tcpbuf.reserve,"     ",5); */

//printf("SND:%s[%d]\n",(char *)&tcpbuf,length);
    return writenet(id,(char *)&tcpbuf,length);
}

int recv_reply(int connid, char retn[8])
{
    int readlen, msglen;
    struct op_data_ack *ack;

    readlen = readnet(connid,(char *)&tcpbuf,8);
    if(readlen != 8)
    {
        fprintf(logfp,"readnet(%d,0,8)=%d failed\n",connid,readlen);
        fclose(logfp);
        exit(1);
    }

    if(strncmp(tcpbuf.flag,MSGFLAG,4))
    {
        tcpbuf.msglen[0]=0;
        fprintf(logfp,"MSGFLAG is incorrect [%s]!\n",tcpbuf.flag);
        fclose(logfp);
        exit(1);
    }

    msglen=get_length(tcpbuf.msglen, 4);
    if(msglen<32)
    {
        fprintf(logfp,"MSGLEN is incorrect[%04d]\n",msglen);
        fclose(logfp);
        exit(1);
    }

    readlen=readnet(connid,(char *)&tcpbuf+8,msglen-8);
    if(readlen!=msglen-8)
    {
        fprintf(logfp,"readnet(%d,8,%d)=%d failed!\n",
            connid,msglen-8,readlen);
        fclose(logfp);
        exit(1);
    }

    ack = (struct op_data_ack *)tcpbuf.data;
    memset(retn, 0x0, sizeof(retn));
    strncpy(retn,ack->retn, 4);
    return 0;
}

void yy_time_log(time_t t)
{
    if(t-yy_time.rec_time >= 300){
        file_log("perf",
                "rectime=%ld,rectype=etr,hlrcode=%s,db1=%s,rows=%d,tm4sel=%d,"
                "tm4fch=%d,tm4req=%d,tm4upd=%d,tm4ins=%d,tm4dul=%d",
                t, yy_time.hlrcode, yy_time.db1, yy_time.rows, yy_time.tm4sel/1000,
                yy_time.tm4fch/1000, yy_time.tm4req/1000, yy_time.tm4upd/1000, yy_time.tm4ins/1000, yy_time.tm4dul/1000);
        yy_time.rows = 0;
        yy_time.tm4sel = 0;
        yy_time.tm4fch = 0;
        yy_time.tm4req = 0;
        yy_time.tm4upd = 0;
        yy_time.tm4ins = 0;
        yy_time.tm4dul = 0;
        yy_time.rec_time = t;
    }
}

FILE * open_logfp(time_t t, FILE *fp1, char *hlrcode)
{
    struct tm *tv;
    char fname[128];

    static int curt = 0;

    tv=localtime(&t);
    if(tv->tm_mday != curt)
    {
        sprintf(fname,"%s/etr%04d%02d%02d.%s",
                getenv("LOGDIR"), tv->tm_year+1900, tv->tm_mon+1,
                tv->tm_mday, hlrcode);
        if(fp1 != NULL)
            fclose(fp1);
        fp1 = fopen(fname,"a");
        if(fp1 == NULL)
        {
            printf("can't open %s for LOG[%d]\n", fname, errno);
            exit(1);
        }
        curt = tv->tm_mday;
    }
    return fp1;
}

int entry_callback_impl(struct cmd11 *c1, const int rec_count, const int connid)
{
    static int count = 0;
    int rec_idx;
    int x, y;
    struct cmd11 *c;
    char retn[8];
    struct op_data_req * req;
    const int SNDLINE = 40;

    if(rec_count == 0){
        fprintf(logfp,"*"); fflush(logfp);
        sleep(1);

        if(++count>9)
        {
            count = 0;
            if(send_req(connid,DECRYPT,TX_END,CONN_KEEP,1,0)<0)
            {
                fprintf(logfp,"send_req CONN_KEEP(%d) failed!\n",connid);
                fclose(logfp);
                exit(1);
            }
            recv_reply(connid, retn);
            fprintf(logfp,"#\n"); fflush(logfp);
        }
        return 0;
    }

    rec_idx = 0;
    while(rec_idx < rec_count)
    {
        /*批量向manager送指令, 一次最多 SNDLINE行*/
        y = SNDLINE;
        if(rec_count - rec_idx < SNDLINE)
            y = rec_count - rec_idx;

        if(y > 99) y = 99; //只够2个字符填写记录数
        sprintf(tcpbuf.reserve, "VV%02d", y); tcpbuf.reserve[4] = ' ';
        req = (struct op_data_req *)tcpbuf.data;
        for(x=0; x<y; x++, req++)
        {
            c = &c1[rec_idx+x];
            rlspace(c->group_id);

            sprintf(req->command_id,"%ld",c->command_id);
            strcpy(req->phone_no,rlspace(c->phone_no));
            strcpy(req->imsi_no,rlspace(c->imsi_no));
            strcpy(req->op_code,rlspace(c->op_code));
            strcpy(req->command_code,rlspace(c->command_code));
            if(atoi(c->command_code)>=60)
                req->cmd_status='0';
            else
                req->cmd_status=c->business_status[0];
            req->phone_priority='1';
            strcpy(req->ss_info1,rlspace(c->new_phone));
            strcpy(req->ss_info2,rlspace(c->new_imsi));
            strcpy(req->ss_info3,rlspace(c->otherinfo));
            strcpy(req->req_time,rlspace(c->request_time));
            strcpy(req->login_no,rlspace(c->login_no));
        }

        if(send_req(connid, DECRYPT, TX_END, SRVCODE0001, 1, sizeof(struct op_data_req)*y)<0)
        {
            fprintf(logfp,"send_req(%d) failed!\n",connid);
            fflush(logfp);
            return -1;
        }

        recv_reply(connid, retn);
        if(strcmp(retn, "0000") != 0){
            fprintf(logfp, "manager return error: [%s]\n", retn);
            fflush(logfp);
            return -2;
        }
        rec_idx += y;

    }
    return 0;
}

int main(int argc,char **argv)
{

        char	selsql[1024];
        char	updsql[1024];
        char	inssql[1024];

        char	retn[8];
        int		rec_count;
        int		total_count;


    int ret,count,endflag;
    char inputstr[2048];
    int num,i,status,today;
    char srvip[32];
    int srvport;
    FILE *cfgfp;
    char cfgstr[256];
    char dbuser[32],dbpswd[32],dbname[32],bossdb[32],tname[64];
    char logfilename[256],logdir[256];
    time_t t;
    struct tm *tv;
    int x, y;

    char chhlr;
    int msglen,readlen,headlen,tcplen,bodylen;
    int transid;
    struct timeval t1, t2;
    int SNDLINE = 40;
    long cmdids[40];

    procname=argv[0];
    logfp=NULL;

    memset(inputstr,0x0,sizeof(inputstr));
    for(i=0;i<argc;i++)
    {
        strcat(inputstr,argv[i]);
        strcat(inputstr," ");
    }

    if(argc<2)
        usage("Incorrect Parameter!");

    if(GenDaemon()<0)
    {
        printf("GenDaemon() failed!\n");
        exit(1);
    }

    signal(SIGTERM,LogOut);
    signal(SIGPIPE,SIG_IGN);
    signal(SIGCLD,SIG_IGN);
    signal(SIGINT,SIG_IGN);

    memset(hlrcode,0x0,sizeof(hlrcode));
    memset(bakhlr,0x0,sizeof(bakhlr));
    memset(dbuser,0x0,sizeof(dbuser));
    memset(dbpswd,0x0,sizeof(dbpswd));
    memset(dbname,0x0,sizeof(dbname));
    memset(bossdb,0x0,sizeof(bossdb));
    memset(logdir,0x0,sizeof(logdir));

    while(--argc>0)
    {
        if(argv[argc][0]!='-')
            usage("Incorrect Parameter!");

        switch(argv[argc][1])
        {
        case 'H':
            strncpy(hlrcode,argv[argc]+2,4);
            break;
        case 'U':
            strncpy(dbuser,argv[argc]+2,30);
            break;
        case 'P':
            strncpy(dbpswd,argv[argc]+2,30);
            break;
        case 'S':
            strncpy(dbname,argv[argc]+2,30);
            break;
        case 'L':
            strncpy(logdir,argv[argc]+2,240);
            break;
        /*case 'D':
            strncpy(bakhlr, argv[argc]+2,4);
            break;*/
        case 'N':
            SNDLINE = atoi(argv[argc]+2);
            if(SNDLINE > 40 || SNDLINE < 1)
                SNDLINE = 40;
            break;
        case 'V':
        case 'v':
            printf("\n\nversion : %s\n\n",VERSION);
            exit(0);
        default:
            usage("Unknow Parameter!");
            break;
        }
    }

printf("hlrcode===%s~\n",hlrcode);
    if(strlen(hlrcode)!=3)
        usage("Incorrect parameter [hlrcode]!\n");

    if(strlen(logdir)<1)
        strcpy(logdir,getenv("LOGDIR"));

    if(testdir(logdir))
        usage("Incorrect parameter [logdir]!");

    time(&t);
    tv=localtime(&t);
    memset(logfilename,0x0,sizeof(logfilename));
    sprintf(logfilename,"%s/etr%04d%02d%02d.%s",logdir,
        tv->tm_year+1900,tv->tm_mon+1,tv->tm_mday,hlrcode);
    logfp = open_logfp(t, NULL, hlrcode);

    memset(&yy_time, 0, sizeof(yy_time));
    strcpy(yy_time.hlrcode, hlrcode);
    strcpy(yy_time.rectype, "etr");
    strcpy(yy_time.db1, "offdb");
    yy_time.rec_time = time(NULL);

    fprintf(logfp,"INIT %04d/%02d/%02d %02d:%02d:%02d\n",
        tv->tm_year+1900,tv->tm_mon+1,tv->tm_mday,
        tv->tm_hour,tv->tm_min,tv->tm_sec);
    fprintf(logfp,"%s[%d]\n",inputstr,argc);
    fflush(logfp);
    today=tv->tm_mday;

    if(strlen(dbuser)<1 || strlen(dbpswd)<1 || strlen(dbname)<1)
    {
        memset(cfgstr,0x0,sizeof(cfgstr));
        strcpy(cfgstr,getenv("ETCDIR"));
        strcat(cfgstr,DBLOGIN);

        cfgfp=fopen(cfgstr,"r");
        if(cfgfp==NULL)
        {
            fprintf(logfp,"can't open %s for read[%d]\n",cfgstr,errno);
            fclose(logfp);
            exit(1);
        }

        memset(dbuser,0x0,sizeof(dbuser));
        memset(dbpswd,0x0,sizeof(dbpswd));
        memset(dbname,0x0,sizeof(dbname));
        fscanf(cfgfp,"%s%s%s",dbuser,dbpswd,dbname);
        fclose(cfgfp);
    }

    if(db_login(dbuser,dbpswd,dbname))
    {
        fprintf(logfp,"db_login(%s,%s,%s) failed!\n",dbuser,dbpswd,dbname);
        fclose(logfp);
        exit(1);
    }
    fprintf(logfp,"db_login(%s) success!\n",dbname);
    fflush(logfp);

    commport=get_commport(hlrcode,srvip, NULL);
    if(commport<1024 || commport>65535)
    {
        fprintf(logfp,"get_commport(%s) == %d failed[%d]\n",commport,errno);
        fclose(logfp);
        exit(1);
    }

    memset(&srvaddr,0x0,sizeof(srvaddr));
    srvaddr.sin_family=AF_INET;
    srvaddr.sin_addr.s_addr=inet_addr(srvip);
    srvaddr.sin_port=htons(commport);

    if(srvaddr.sin_addr.s_addr==-1)
    {
        fprintf(logfp,"Incorrect IPADDR in mcfghead[%s]\n",srvip);
        fclose(logfp);
        exit(1);
    }

    memset(dbuser,0x0,sizeof(dbuser));
    memset(dbpswd,0x0,sizeof(dbpswd));
    memset(tname,0x0,sizeof(tname));

    if(get_bossinfo(hlrcode,bossdb,dbuser,dbpswd,tname))
    {
        fprintf(logfp,"get_boss_db(%s) failed!\n",hlrcode);
        fclose(logfp);
        exit(1);
    }
    else
    {
        fprintf(logfp,"BOSSDB:%s[%d]	%d		%s		%s[%d]\n",
            dbuser,strlen(dbuser), strlen(dbpswd),bossdb, tname,strlen(tname));
        fflush(logfp);
    }
printf("tname====%s~%s~%s~%s\n",tname, dbuser, dbpswd, bossdb);

    db_logout();

    if(db_login(dbuser,dbpswd,bossdb))
    {
        fprintf(logfp,"db_login(%s) failed!\n",bossdb);
        fclose(logfp);
        exit(1);
    }
    fprintf(logfp,"db_login(%s) success!\n",bossdb);
    fflush(logfp);

    connid=socket(AF_INET,SOCK_STREAM,0);
    if(connid<0)
    {
        fprintf(logfp,"socket() failed[%d]\n",errno);
        fclose(logfp);
        exit(1);
    }

    if(connect(connid,(struct sockaddr *)&srvaddr,sizeof(srvaddr))<0)
    {
        fprintf(logfp,"connect(%d) failed[%d]!\n",connid,errno);
        fclose(logfp);
        exit(1);
    }

    memset(selsql,0x0,sizeof(selsql));
    memset(updsql,0x0,sizeof(updsql));
    memset(inssql, 0, sizeof(inssql));

    entry_loop(hlrcode, tname, entry_callback_impl, connid);
    close(connid);

    db_logout();

    fclose(logfp);

    return 0;
}
