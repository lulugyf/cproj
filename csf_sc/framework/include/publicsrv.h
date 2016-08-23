#ifndef _PUBLICSRV_H
#define _PUBLICSRV_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/errno.h>
/*****#include <varargs.h>******/
#include <unistd.h>
#include <signal.h>

#ifdef _XOPEN_SOURCE_EXTENDED
#include <arpa/inet.h>
#else
#include <netinet/in.h>
#endif

#include <string.h>
#include <ctype.h>
#include <atmi.h>
#include <userlog.h>



/*
 * Sybase header files
 */

#ifndef SQLCA_STORAGE_CLASS
#define SQLCA_STORAGE_CLASS extern
#endif

#ifndef ORACA_STORAGE_CLASS
#define ORACA_STORAGE_CLASS extern
#endif

#include "des.h"

/*
#include "prodFuncDef.h"
*/
/*
#include "rtOweQry.h"
*/

#if USE_SCCSID
static char Sccsid[] = {"@(#) publicsrv.h 1.2 01/08/2004"};
#endif /* USE_SCCSID */

#define Sinitn(src) memset(src, 0, sizeof(src))
#define Sinit0(src) memset(src, '0', sizeof(src))
#define Sinits(src) memset(src, ' ', sizeof(src))


#define Strcpy(a,b) strncpy(a,b, sizeof(a)-1)

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif
/* added 20020423 */

#define LCONNTYPE	"0"
#define SCONNTYPE	"1"

#define ACCSHMKEYFILE   "acceptfile.shm"
#define ACCSEMKEYFILE   "acceptfile.sem"

#define REDOSHMKEYFILE   "redofile.shm"
#define REDOSEMKEYFILE   "redofile.sem"

#define SOPCODEFILE     "sCancelOpCode.cfg"
#define CFMACCEPTFILE   "cfmAcceptFile."
#define CANCELACCEPTFILE  "cancelAcceptFile."

#define SHMKDIR 	"sDBLogin.cfg"
#define SHMKEY		1
#define PERMS		0666
#define SHMKLOGDIR 	"sLogLevel.cfg"

#define MAX_BIND 	5
#define MAXCODE 	50
#define LINE 		80
#define COMMENT 	'#'

#define TRANSSDBLOGIN 	"sDBLogin.cfg"
#define TRANSSPRNFORMAT	"sPrnFormat.cfg"
#define TRANSSMAINTITLE	"sMainTitle.cfg"
#define TRANSSLOGLEVEL	"sLogLevel.cfg"

#define DEFTIME 	50

#define BIGCOUNT        200
#define MAXLABELLEN	12
#define MAXLOGIN	100
#define MAXLOGNUM	10000

#define MAXBUFLEN       1024
#define MAXENCRYPTLEN   16
#define MAXDECRYPTLEN   16
#define WORKDIR         "WORKDIR"
#define REDODIR         "REDODIR"
#define ORGPASSWDLEN	6

#define REDOPROCESSNUM	40
#define REDOCOUNT	4


#define DBPARTITION (cfgGetCurrentDBPatition())
#define DBPARTITIONINS (cfgGetCurrentDBInstance())
#define LABELBOSSCHANGE (cfgGetCurrentPatitionsLabel("bosschange", string("")).c_str())
#define LABELDBCHANGEALL (cfgGetAllPatitionsLabel("dbchange", string("")).c_str())
#define LABELDBCHANGE (cfgGetCurrentPatitionsLabel("dbchange", string("")).c_str())
#define LABELDBCEN      ((string("dbcen")+DBPARTITIONINS).c_str())
#define LABELDBLOGIN    ((string("dblogin")+DBPARTITIONINS).c_str())
#define LABELDBSETTLE    ((string("dbsettle")).c_str())
#define LABELBOTHERCHANGE (cfgGetCurrentPatitionsLabel("botherchange", string("")).c_str())


/* add by ZHAOQM  20100223*/
#define LABELDBSCORE  (cfgGetCurrentPatitionsLabel("dbscore", string("")).c_str())/* 积分域*/
#define LABELDBCNTT      ((string("dbcntt")+DBPARTITIONINS).c_str())	/* 接触域*/
#define LABELDBSCOREALL (cfgGetAllPatitionsLabel("dbscore", string("")).c_str())/*连接账务AB库*/

/* add by zhujg 20110714*/
#define LABELDBOBOSS    ((string("dboneboss")+DBPARTITIONINS).c_str())  /*一级BOSS全网库*/

/* 共享内存存储结构(数据库) */
struct spublicdblogin {
	char          label[MAXLABELLEN+1];
	char          server[MAXLABELLEN+1];
	char          database[MAXLABELLEN+1];
	char          username[MAXLABELLEN+1];
	char          password[MAXENDELEN+1];
	char          baklbl[MAXENDELEN+1];
};

struct comshm {
	unsigned int 		sdbloginno;
	struct spublicdblogin 	sdblogin[MAXLOGIN];
};

/* 内存流水使用的共享内存结构 */
struct acceptshm
{
	unsigned long count;
	char  sysdate[10];
};

/* 重做日志REDO使用的共享内存结构 */
struct redoShm
{
	char	memAccept[REDOPROCESSNUM*REDOCOUNT][100];
	unsigned long	redoPosition[REDOPROCESSNUM*REDOCOUNT];
	char	redoFile[REDOPROCESSNUM*REDOCOUNT][100];
	char	svcName[REDOPROCESSNUM*REDOCOUNT][20];
	char	phoneNo[REDOPROCESSNUM*REDOCOUNT][20];
	unsigned int	flag[REDOPROCESSNUM*REDOCOUNT];
	unsigned int	endFlag;
};

/* 共享内存存储结构(日志) */
struct spublicloglevel {
	char		codelevel[5+1];
	unsigned int	flag;
};
struct logshm {
	unsigned int		sloglevelno;
	struct spublicloglevel	sloglevel[MAXLOGNUM];
};


/* MAC校验结构 */
typedef struct MacStruc {
	int     use_int;
	int     srcint[10];
	int     use_float;
	float   srcfloat[10];
        int     use_char;
        char    srcchar[10][20];
} MACSTRUC;

typedef struct PrnFormat {
	char	line_no[4+1];
	char	col_width[4+1];
	char	order_type[2+1];
	char	format_type[2+1];
	char	all_var[36+1];
} PRNFORMAT;



#ifdef __cplusplus
extern "C" {
#endif
char * Ltrim(char * str);
char * Rtrim(char * str);
char *rtrim(char *src);
int IsDigital(char* InputChar);
int iStrGetPart(char *strWord,int nBegin,int nGip,char *strNewWord);
char* Trim(char *S);
int strToFields(const char* src, char separateChar, ...);
char *spublicGetEnvDir( char *env);
int  spublicGetCfgDir(const char *file, char rtn_path[LINE]);
int  spublicGetBinDir(const char *file, char rtn_path[LINE]);
int  spublicGetIncludeDir(const char *file, char rtn_path[LINE]);
int  spublicGetLibDir(const char *file, char rtn_path[LINE]);
int  spublicGetPublicDir(const char *file, char rtn_path[LINE]);
int  spublicGetTmpDir(const char *file, char rtn_path[LINE]);
int    spublicGetRedoDir(char file[18], char rtn_path[100]);
key_t  spublicGetShmKey();
struct comshm * spublicCreatShm();
struct comshm * spublicGetShm();
int    spublicDelShm();
int    spublicDtcShm(struct comshm *shmp);
struct spublicdblogin spublicGetDBP(char *connect_name);
int spublicPutKeyShm();

key_t  spublicLogGetShmKey();
struct logshm * spublicLogCreatShm();
struct logshm * spublicLogGetShm();
int    spublicLogPutKeyShm();
int    spublicLogDelShm();
int    spublicLogDtcShm(struct logshm *shmp);
int    spublicLogGetFlag(char *codelevel);
struct spublicloglevel spublicLogGetDBP(char *codelevel);
int spublicDBLogin(void *transIN,void *transOUT,char *srvName,char *connect_name);
int sChkDBLogin(void *transIN, void *transOUT, char *srvName,char *connect_name);
int spublicDBClose(char *connect_name);
int sGetDenPasswd(char *connect_name, char *login_no, char *login_passwd);
int spublicGenMAC(char *MAINKEY, struct MacStruc *macstruc, char *out_MAC);
int spublicRight(char *connect_name,char *login_no, char *login_passwd, char *function_code);
int sPayGetAccept(char *connect_name, int flag);
int spublicGetAccept(char *connect_name, int flag);
int spublicGetnAccept(char *connect_name,int flag, int n);
int spublicPrnFormat();


char *Srtrim(char *src);
char *Sltrim(char *src);
char *Strim(char *src);
char *Ssubstr(char *src, int begin, int length, char *dest);
char *Slower(char *src);
char *Supper(char *src);
char *Slower(char *src);
char *Supper(char *src);
char *ltrim(char *src);
char *rtrim(char *src);
char *Tchgformat(char *src, char *dest, char *type);
char *Tgetsysdatetime(int type);
char *Tgetssysdatetime(char s);
char *Tgetyear();
char *Tgetmonth();
char *Tgetday();
char *Tgethour();
char *Tgetminute();
char *Tgetsecond();

double roundN(double source, int num);

void bosslog();

int BcdToAsc_(unsigned char *dest, unsigned char *src, int length);
int NCreatOneSem(const key_t semkey);
int NSemDel(int semid);
int NOpenOneSem(const key_t semkey);
int Nsm_sem_lock(const int semid);
int Nsm_sem_unlock(const int semid);
int Nsem_lock_nowait(const int semid);
int Nsem_unlock_nowait(const int semid);
struct acceptshm * NCreatShm(key_t shmkey, int length,int *shmid);
struct acceptshm * NOpenShm(key_t shmkey);
int NCloseShm(const struct acceptshm *shmp);
int NDtcShm(const struct acceptshm *shmp);
int NDelShm(key_t shmkey);
int NOpenShmErr(key_t shmkey);
char *GetSysDatetime();
void Quit(int signo);
int CreatMemAccept();
char *GetMemAccept();
int DelMemAccept();
char *GetMemDate();

int  pubMarkUpdate(char *iPhoneNo,long iDeductPoint,int iFavourCount,char *iLoginNo,char *iFavourCode,char *iSystemNote,long iLoginAccept,char *iOpCode,char *oRetCode,char *oRetMsg);
int NMSWriteStartLog(char *,long,char *,char *,char *, char *, char *,char *, int ,char *, char *,char *,char *);
int NMSWriteEndLog(char *,long , char *,char *, char *);

char *Tntoe(char *src, char *dest);
void Pinitprintbright();
void Pendprintbright();
char *getSysTime(int type);
int spublicDelKeyShm();
struct redoShm * redoOpenShm(key_t shmkey);

#ifdef __cplusplus
}
#endif

#define ERR_HANDLER {goto ERR_LABEL;}

#endif /* _PUBLICSRV_H */

