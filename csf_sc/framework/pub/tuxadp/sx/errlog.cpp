
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>



#include "errlog.h"
#include "framework.h"

const char* cfgGetStr(const char* maintag, const char* subtag);
//utype * json2utype(const char *str);
//char * utype2json(const utype *pu);

static const int ERR_HEADLEN = 8 + 64 + 17 + 14 + 14 + 10 + 10 + 14 + 14;
static const char *tagstr = "\n^ERRLG^";
static char hostname[128];

// ��¼���������־�� ��������������γ���
/*
��־���ݸ�ʽ�������£�
structlogdata{
	char tagstr[8];        //��ʶһ����־��ʼ���̶��ִ� \n^ERRLG^
	char servicename[64];  //�������ƣ����Ȳ���ǰ���ո�
    char begintime[17];    //������ÿ�ʼʱ�䣬 ��ʽ�� yyyymmddHHMMSSsss
    char timecost[14];     //�������ʹ��ʱ�䣬 ��������λ�� ms
	char processid[14];    //����id
    char errid[10];       // ������ɵĴ���id�� ��ֵ����뵽������Ϣ��ʹǰ̨���Կ�������������浥���ڿ��ٶ�λ������Ϣ
	char errcode[10];     // ҵ�񷵻ش�����룬 0Ϊ�ɹ�
	char inputlen[14];     //10�������뱨�ĳ��ȣ����Ȳ���ǰ���ո�
	char outputlen[14];    //10����������ĳ��ȣ����Ȳ���ǰ���ո�
	char indata[atoi(inputlen)];        // ���뱨������
	char outdata[atoi(outputlen)];      // �����������
};

��־�ļ���Сʱ��š�

�������ݶ������£� $CRM_CFG:
[ERRLOG]
STORE_PATH=/path/to/logfile   �洢��־�ļ���·��
STORE_SUCC_FLAG=0           �Ƿ��¼�ɹ����ã� 1-�� 0-��
DBLABEL=$label               ������ʹ�õ����ݿ����ӱ�ǩ

*/


int mylock(const char *f, int *pfd)
{
	struct flock fl;
	int fd;
	fl.l_type   = F_WRLCK;  /* F_RDLCK,F_WRLCK,F_UNLCK    */
	fl.l_whence = SEEK_SET; /* SEEK_SET,SEEK_CUR,SEEK_END */
	fl.l_start  = 0;        /* Offset from l_whence         */
	fl.l_len    = 0;        /* length,0 = to EOF           */
	fl.l_pid    = getpid(); /* our PID                      */
	fd = open(f, O_WRONLY | O_CREAT);
	if(fd < 0){
		return -1;
	}
	*pfd = fd;
	return fcntl(fd, F_SETLKW, &fl);  /* F_GETLK,F_SETLK,F_SETLKW */
}

int myunlock(int fd)
{
	struct flock fl;

	fl.l_type = F_UNLCK; /* F_RDLCK,F_WRLCK,F_UNLCK */
	fl.l_whence = SEEK_SET; /* SEEK_SET,SEEK_CUR,SEEK_END */
	fl.l_start = 0; /* Offset from l_whence */
	fl.l_len = 0; /* length,0 = to EOF */
	fl.l_pid = getpid(); /* our PID */

	fcntl(fd, F_SETLK, &fl);
	close(fd);
	return 0;
}

void mymkdirs(const char *m){
 char *p = strdup(m);
 char *p1 = p, *p2 = NULL;
 while( ( p2 = strchr(p1, '/')) != NULL){
    *p2 = 0;
    mkdir(p, 0775);
    *p2 = '/';
    p1 = p2 + 1;
 }
 free(p);
}

static struct _log_stru
{
	struct timeval tv_begin;
	char svc_name[68];
	int inlen;
	const char *inputstr;
} _log;

void errlog_begin(const char *svc_name, const char *inputstr)
{
	strncpy(_log.svc_name, svc_name, sizeof(_log.svc_name)-1);
	_log.svc_name[sizeof(_log.svc_name)-1] = 0;
	gettimeofday(&_log.tv_begin, NULL);
	_log.inputstr = inputstr;
	_log.inlen = strlen(inputstr);
	return;
}

void errlog_end(long errid, long retcode, const char *outputstr)
{
	struct timeval tv_end;
	char logfile[128];
	struct tm *tm;
	pid_t pid;
	char *tmpbuf;
	char tm_begin[18];
	int fileid;
	const char *store_path;
	int outlen;
	int timecost;

	if(outputstr == NULL)
		return;

	store_path = cfgGetStr("ERRLOG", "STORE_PATH");
	if(store_path[0] == 0)
		return; //���û������, �����

	outlen = strlen(outputstr);

	if(cfgGetStr("ERRLOG", "STORE_SUCC_FLAG")[0] != '1' && retcode == 0L)
		return;

	gettimeofday(&tv_end, NULL);
	tm = localtime(&tv_end.tv_sec);
	pid = getpid();

	//filename: yyyymmddHH.PP.log
	sprintf(logfile, "%s/%04d%02d%02d%02d.%02d.log",
			store_path,
			tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour,
			pid % 100);
	tm = localtime(&_log.tv_begin.tv_sec);
	sprintf(tm_begin, "%04d%02d%02d%02d%02d%02d%03d",
			tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
			tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(_log.tv_begin.tv_usec/1000));

	timecost = (tv_end.tv_sec - _log.tv_begin.tv_sec)*1000
			+ (tv_end.tv_usec - _log.tv_begin.tv_usec)/1000;

	//const int hlen = 8 + 64 + 17 + 14 + 14 + 10 + 10 + 14 + 14;
	int buflen = ERR_HEADLEN + _log.inlen + outlen;
	tmpbuf = (char *)malloc( buflen );
	sprintf(tmpbuf, "% 8s% 64s% 17s% 14d% 14d% 10d% 10d% 14d% 14d",
	    		tagstr, _log.svc_name, tm_begin, timecost, pid, errid, retcode, _log.inlen, outlen);
	memcpy(tmpbuf+ERR_HEADLEN, _log.inputstr, _log.inlen);
	memcpy(tmpbuf+ERR_HEADLEN+_log.inlen, outputstr, outlen);

	/*printf("timecost: %d\n", timecost);
	printf("pid: %ld\n", pid);
	printf("errid: %d\n", errid);
	printf("retcode: %d\n", retcode);
	printf("inlen: %d\n", _log.inlen);
	printf("outlen: %d\n", outlen);
	*/

	fileid = open(logfile, O_WRONLY|O_CREAT|O_APPEND, 0666);
	if(fileid == -1){
		mymkdirs(store_path);
		fileid = open(logfile, O_WRONLY|O_CREAT|O_APPEND, 0666);
		if(fileid == -1){
			printf("open file failed[%s], errno:%d\n", logfile, errno);
			free(tmpbuf);
			return;
		}
	}
	int r = write(fileid, tmpbuf, buflen);
	printf("========write return %d, errno=%d\n", r, errno);
	close(fileid);
	free(tmpbuf);
}


int errlog_generrid()
{
	time_t t;
	pid_t pid;
	int ret;

	pid = getpid();
	t = time(NULL);

	ret = (pid % 10000) * 10000 + t % 10000;
	if(ret < 10000000){
		ret += 10000000;
	}

	return ret;
}


// ����ĺ������ػ�����ʹ�õģ� ���ڸ���־�����
/*
 * ʵ�ַ����ǣ� ��ʱɨ��Ŀ¼�е��ļ��� ÿ��ɨ��Ĺ������£�
 *    ����ϵ��ļ��� ��¼���ļ����� �ϴ��޸�ʱ�䣬 �ϴζ�ȡλ�ã�
 *    ɨ��Ŀ¼�ļ��� �����ļ������޸�ʱ�� ��С
 *    ������Ŀ¼�е��ļ��� ɾ������1hδ�޸��Ҷϵ�δ��ģ� �����ļ���Сû��ĺ���
 *      �����ļ��ʹ�С���ӵģ� ��ʼ��ȡ�ļ����ݣ� �����
 *       ��10�����ļ������� ����һ�ζϵ��ļ�����ǰ�Ķ�ȡλ�ü��ļ��޸�ʱ�䣩
 *    ���һ��ɨ���sleep 2��
 */
#include <string>
#include <iostream>
#include <map>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;


static char* uGetStrByName(const utype* pu, char* buf, int bufSize, const char* name)
{
    UPOS p;
    memset(buf, 0, bufSize);
    //���ҵ�ǰutype���Ƿ�������Ϊname�Ľڵ㣬������򷵻ؽڵ�ֵ
    if(UPOS_END !=(p = utFind(pu, name)))
    {
		switch(pu->ppe[p]->type)
		{
			case U_INT:snprintf(buf, bufSize - 1, "%d", utGetInt(pu, name, p));break;
			case U_LONG:snprintf(buf, bufSize - 1, "%ld", utGetLong(pu, name, p));break;
			case U_DOUBLE:snprintf(buf, bufSize - 1, "%0.2f", utGetDouble(pu, name, p));break;
			case U_STRING:snprintf(buf, bufSize - 1, "%s", utGetStr(pu, name, p));break;
			default:strcpy(buf, "");break;
		}
		return buf;
	}

    char sUtypeNodeName[127 + 1];
    uAutoPtr uTmp(uInit(0));
    uTmp = utClone(pu);
    int iLen = uTmp->cnt;

    for(int i = 0; i < iLen; i ++)
    {
        //���Ȱ��������µ�˳��ȡutype��ǰĿ¼�����нڵ㣬
        //���жϽڵ��Ƿ�Ϊutype��Ϊutype�����utype��Ȼ��ص�����
        memset(sUtypeNodeName, 0, sizeof(sUtypeNodeName));
        strcpy(sUtypeNodeName, utGetName(pu, i));
        //printf("*****************sUtypeNodeName=[%s]***********************\n", sUtypeNodeName);
        int uTypeType = utGetType(pu, sUtypeNodeName);
        if(U_STRUCT == uTypeType)
        {
            uGetStrByName(utGetStruct(pu, sUtypeNodeName), buf, bufSize, name);
            if('\0' != buf[0])
            {
                return buf;
            }
        }
    }
    return buf;
}

static void readBPFile(const char *path, map<string, pair<long, long> > *store)
{
	char fpath[128];
	FILE *fp;
	char line[1024];

	char fname[64];
	long fmod, fpos;

	sprintf(fpath, "%s/.breakpoints", path);
	fp = fopen(fpath, "r");
	if(fp == NULL)
		return;
	while(fgets(line, sizeof(line)-1, fp) != NULL){
		if(sscanf(line, "%s %ld %ld", fname, &fmod, &fpos) != 3)
			continue;
		store->insert(map<string, pair<long, long> >::value_type(fname, pair<long, long>(fmod, fpos)));
	}
	fclose(fp);
}

static void writeBPFile(const char *basedir,
		map<string, pair<long, long> > *store,
		map<string, int> *delfiles)
{
	char fpath[128];
	FILE *fp;
	char line[1024];

	char fname[64];

	sprintf(fpath, "%s/.breakpoints", basedir);
	fp = fopen(fpath, "w");
	if(fp == NULL)
		return;

	map<string, pair<long, long> >::iterator iter;

	for(iter = store->begin(); iter != store->end(); iter ++){
		if(delfiles->find(iter->first) != delfiles->end())
			continue; //if file delete, do not save it's breakpoint
		pair<long, long> *p = &iter->second;
		const char *fpath = iter->first.c_str();
		long fmod = p->first;
		long fpos = p->second;
		fprintf(fp, "%s %ld %ld\n", fpath,
				fmod, fpos);
		printf("!!SAVEBP: %s pos: %ld\n", fpath, fpos);
	}
	fclose(fp);
}

static int getFileList(const char *path,
		map<string, pair<long, long> > *flist)
{
	DIR *pDir = NULL;
	struct dirent *pDirent = NULL;
	char fpath[128];
	struct stat st;
	int i = 0;

	if((pDir = opendir(path)) == NULL)
		return -1;

	strcpy(fpath, path);
	strcat(fpath, "/");
	while(true)
	{
		pDirent = readdir(pDir) ; //��ȡ��һ�ļ�
		if(pDirent == NULL)
			break;

		if (pDirent->d_name[0] == '.')
			continue;

		strcpy(fpath, path);
		strcat(fpath, "/");
		strcat(fpath, pDirent->d_name);

		if(stat(fpath, &st) == -1) //��ȡ�ļ����Խṹ ���˴���Ҫʹ��lstat����ʹ��stat�������ж������ļ�����Ϣ
		{
			printf("ERR: can not stat file[%s], errno:%d\n", fpath, errno);
			continue;
		}
		if(S_ISDIR(st.st_mode)) //�ж��Ƿ���Ŀ¼
			continue;

		flist->insert(map<string, pair<long, long> >::value_type(fpath, pair<long, long>(st.st_mtime, st.st_size)));
		i ++;
	}
	closedir(pDir);
	return i;
}

void ltrim(char *s)
{
	char *s1 = s;
	while((*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') && *s != 0)
		s++;
	if(s != s1)
		strcpy(s1, s);
}

long toint(char *s, int len)
{
	char i[32];
	if(len > 31)
		len = 31;
	memcpy(i, s, len); i[len] = 0;
	return atol(i);
}

#ifdef __SICHUAN_FLAG
/*
 * @return
 *  >0: success and the value is read bytes
 * 	== 0: no data
 * 	<0: failed
 */
static int readOneRecord(int fid, otl_connect *db)
{
	char hbuf[ERR_HEADLEN+1];
	int readlen = 0; //���ζ������ֽ���

	int r = read(fid, hbuf, ERR_HEADLEN);
	if(r == 0){
		printf("==file end!");
		return 0;
	}
	if(r != ERR_HEADLEN){
		printf("ERR: read head failed, read[%d] headlen[%d]\n",
				r, ERR_HEADLEN);
		return -2;
	}
	hbuf[ERR_HEADLEN] = 0;
	readlen += r;

	char ntag[9], svc_name[64+1], tm_begin[18], *hh;
	int timecost, errid, retcode, inlen, outlen;
	long pid;

	//r = sscanf(hbuf, "% 8s% 64s% 17s% 14d% 14ld% 10d% 10d% 14d% 14d",
	//    		ntag, svc_name, tm_begin, &timecost, &pid, &errid, &retcode, &inlen, &outlen);
	strncpy(svc_name, hbuf+8, 64); svc_name[64] = 0; ltrim(svc_name);
	memcpy(tm_begin, hbuf+8+64, 17); tm_begin[17] = 0;
	hh = hbuf+8+64+17;
	timecost = (int)toint(hh, 14); hh+=14;
	pid = toint(hh, 14); hh+=14;
	errid = (int)toint(hh, 10); hh+=10;
	retcode = (int)toint(hh, 10); hh+=10;
	inlen = (int)toint(hh, 14); hh+=14;
	outlen = (int)toint(hh, 14); hh+=14;

	/*printf("timecost: %d\n", timecost);
	printf("pid: %ld\n", pid);
	printf("errid: %d\n", errid);
	printf("retcode: %d\n", retcode);
	printf("inlen: %d\n", inlen);
	printf("outlen: %d\n", outlen); */

	char *inbuf, *outbuf;
	inbuf = (char *)malloc(inlen + 1);
	outbuf = (char *)malloc(outlen + 1);
	if(inbuf == NULL || outbuf == NULL){
		if(inbuf != NULL) free(outbuf);
		if(outbuf != NULL) free(inbuf);
		printf("ERR: malloc failed, inlen[%d], outlen[%d]\n", inlen, outlen);
		return -4;
	}
	r = read(fid, inbuf, inlen);
	if(r != inlen){
		printf("ERR: read inbuf failed, need %d but %d\n", inlen, r);
		free(inbuf);
		free(outbuf);
		return -5;
	}
	readlen += r;
	inbuf[inlen] = 0;
	r = read(fid, outbuf, outlen);
	if(r != outlen){
		printf("ERR: read outbuf failed, need %d but %d\n", inlen, r);
		free(inbuf);
		free(outbuf);
		return -6;
	}
	readlen += r;

	char sqlbuf[1024], ymd[16];
	memcpy(ymd, tm_begin, 6); ymd[6] = 0;
	sprintf(sqlbuf,
			"insert into bs_csf_errlog_%s ("
			"service_name, op_time, begin_time, time_cost, errid,"
			"server_ip, client_ip, contact_id, phone_no, op_code,"
			"login_no, ret_code, ret_msg, detail_msg,"
			"input, output"
			")"
			 "values( :svc_name<char[65]>, to_date(:op_time<char[15]>, 'yyyymmddhh24miss') , :begin_time<char[18]>, :time_cost<int>, :errid<int>,"
			 ":server_ip<char[65]>, :client_ip<char[65]>, :contact_id<char[26]>, :phone_no<char[100]>, :op_code<char[9]>,"
			 ":login_no<char[9]>, :ret_code<int>, :ret_msg<char[129]>, :detail_msg<char[129]>,"
			 ":input<char[4001]>, :output<char[4001]>"
			 ")"
			,ymd);
	memcpy(ymd, tm_begin, 14); ymd[14] = 0; //op_time
	if(inlen > 4000)
		inbuf[4000-1] = 0;
	if(outlen > 4000)
		outbuf[4000-1] = 0;

	// parse: CONTACT_ID PHONE_NO OP_CODE LOGIN_NO RET_MSG DETAIL_MSG
	uAutoPtr uin(json2utype(inbuf));
	uAutoPtr uout(json2utype(outbuf));
	char contact_id[26], phone_no[101], op_code[9], login_no[10];
	char ret_msg[129], detail_msg[129];

#define MYGET(a, b, c) uGetStrByName(a, b, sizeof(b), c)
	MYGET(uin, contact_id, "CONTACT_ID");
	MYGET(uin, phone_no, "PHONE_NO");
	MYGET(uin, op_code, "OP_CODE");
	MYGET(uin, login_no, "LOGIN_NO");

	MYGET(uout, ret_msg, "RETURN_MSG");
	MYGET(uout, detail_msg, "DETAIL_MSG");

	otl_stream o;
	try{
		o.open(1, sqlbuf, *db);
		o << svc_name << ymd << tm_begin << timecost
		 << errid << hostname << "" << contact_id << phone_no << op_code
		 << login_no << retcode << ret_msg << detail_msg << inbuf << outbuf;
	}catch(otl_exception &ex){
		printf("insert failed :%d  errmsg: %s\n %s %s\n\n",
				ex.code, ex.msg, ex.stm_text, ex.var_info);
		return -1;
	}
	return readlen;
}
static int fileDbIn(const char *basedir, const char *fpath,
		long lastpos, time_t mod,
		map<string, pair<long, long> > *bp,
		map<string, int> *delfiles,
		otl_connect *db)
{
	int fid;

	printf("fileDbIn: %s lastpos: %ld\n", fpath, lastpos);
	fid = open(fpath, O_RDONLY);
	if(fid < 0){
		printf("ERR: err in open file[%s], errno:%d\n", fpath, errno);
		return -1;
	}
	if(lastpos > 0)
		lseek(fid, lastpos, SEEK_SET);

	int rcount = 0;
	while(true){
		int r = readOneRecord(fid, db);
		if(r <= 0)
			break;
		lastpos += r;
		(*bp)[fpath] = pair<long, long>(mod, lastpos);
		printf("new pos: %d\n", lastpos);
		rcount += 1;
		if(rcount >= 19){
			db->commit();
			rcount = 0;
			writeBPFile(basedir, bp, delfiles);
		}
	}
	db->commit();
	writeBPFile(basedir, bp, delfiles);

	return 0;
}

static int loopOnce(const char *basedir,
		const char *dblabel,
		map<string, pair<long, long> > &bp,
		map<string, pair<long, long> > &flist,
		map<string, int> &delfiles)
{
	time_t curtm;
	map<string, pair<long, long> >::iterator iter1, iter2;

	curtm = time(NULL);
	bp.clear();
	flist.clear();
	delfiles.clear();
	readBPFile(basedir, &bp);
	getFileList(basedir, &flist);

	db_connect db(dblabel);
	try{
		db.doConnect();
		printf("!! connect to db success.\n");
	}catch(...){
		printf("connect db failed...\n");
		return -1;
	}
	for(iter1=flist.begin(); iter1 != flist.end(); iter1++){
		iter2 = bp.find(iter1->first);
		printf("deal file[%s]\n", iter1->first.c_str());
		long lastpos = 0;
		if(iter2 != bp.end()){
			long tmcur = iter1->second.first, //�ļ��޸�ʱ��
				 tmbp = iter2->second.first;  //�ϵ����ļ��޸�ʱ��
			long fsize = iter1->second.second, //�ļ���С
				fpos = iter2->second.second;   //�ϵ��ж�ȡ�ļ�λ��
			if(curtm - tmcur >= 3600 && fpos >= fsize){
				//�ļ�����1hδ�޸�, �Ҵ�Сû��, ɾ��
				delfiles.insert(map<string, int>::value_type(iter1->first, 0));
				remove(iter1->first.c_str());
				continue;
			}
			if(fpos >= fsize){
				continue; //�ļ���Сδ��, ����
			}
			lastpos = fpos;
		}
		fileDbIn(basedir, iter1->first.c_str(), lastpos, iter1->second.first,
				&bp, &delfiles, &db.getOtlHandle());
	}
	db.doClose();
	return 0;
}

int errlog_loadIntoDB(int *running, int interval)
{
	const char *basedir;
	const char *dblabel;
	map<string, pair<long, long> > bp, flist;
	map<string, int> delfiles;

	time_t curtm;
	char lockfilename[128];
	int  lockfd;

	basedir = cfgGetStr("ERRLOG", "STORE_PATH");
	dblabel = cfgGetStr("ERRLOG", "DBLABEL");
	if(basedir == NULL || basedir[0] == '\0')
		return 0;
	if(dblabel == NULL || dblabel[0] == 0)
		return 0;
	printf("STORE_PATH[%s] DBLABEL[%s]\n", basedir, dblabel);
	FILE *fp = popen("hostname", "r");
	fgets(hostname, sizeof(hostname)-1, fp);
	fclose(fp);

	sprintf(lockfilename, "%s/.lock", basedir);
	while(*running){
		sleep(interval);
		//�����ļ������ظ�����
		if(mylock(lockfilename, &lockfd) != 0)
			continue;
		loopOnce(basedir, dblabel, bp, flist, delfiles);
		myunlock(lockfd);
	}

	return 0;
}


/**
 * @brief 
 * @param retMsg
 * ���DETAIL_MSG�������Ƿ���sql��䣬�еĻ����滻���� ���ڼ��Ű�ȫ���
 * 2015-6-24*/
void checkDetailMsgWithSQL(const char *serviceName, char *retMsg){
	if(strlen(retMsg) < 20)
		return;
	char *s = strdup(retMsg), *p;
	for(char *c = s; *c!=0; c++){
		*c = toupper(*c);
	}
	if( ( (strstr(s, "DELETE") != NULL 
		|| strstr(s, "SELECT") != NULL 
		|| strstr(s, "UPDATE") != NULL
		)
		 && strstr(s, "WHERE") != NULL  )
	  || (strstr(s, "INSERT") != NULL && strstr(s, "INTO") != NULL )
	){
		char logfile[128];
		time_t t;
		time(&t);
		struct tm *tt = localtime(&t);
		sprintf(logfile, "%s/log/detail.%d", getenv("WORKDIR"), tt->tm_wday);
		FILE *fp = fopen(logfile, "a");
		fprintf(fp, "==%ld  %s\n%s\n", t, serviceName, retMsg);
		fclose(fp);
		sprintf(retMsg, "DBERR of %s, %d errid: %ld", serviceName, tt->tm_wday, t);
	}
}

#endif // __SICHUAN_FLAG__

