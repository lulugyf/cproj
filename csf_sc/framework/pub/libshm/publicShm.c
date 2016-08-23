/******************************************
 *      Prg:  publicShm.cp
 *     Edit:  dangsl
 *     Date:  2002.12.26
 ******************************************/

#ifndef __PUBLICBACK_H
#define __PUBLICBACK_H

#include <sys/shm.h>
#include "publicsrv.h"

#include "atmi.h"

#define WORKDIR "WORKDIR"

extern int errno;

int    sig_semid;
struct acceptshm *sig_shmp;

static struct sembuf op_lock={ 0,-1,0};
static struct sembuf op_unlock={ 0,1,0};
static struct sembuf op_endcreat={ 1,-1,SEM_UNDO };
static struct sembuf op_open={ 1,-1,0  };
static struct sembuf op_close={ 1,1,0  };

/*** 
ȡ�ù����ڴ��ֵ 
@inparam 
@return  key_t 
***/
key_t
spublicGetShmKey()
{
	key_t kid;
	char filename[LINE];
	memset(filename, 0, sizeof(filename));
	userlog("[%s] SHMKDIR=[%s]\n",__FILE__,SHMKDIR);
	spublicGetCfgDir(SHMKDIR, filename);
	userlog("[%s] SHMKDIR_FILENAME=[%s]\n",__FILE__,filename);
	kid = ftok( filename, SHMKEY);
	return kid;
}

/****
���������ڴ� 
@inparam 
@return  comshm *
***/
struct comshm *
spublicCreatShm()
{
	int shmid;
	key_t shmkey,spublicGetShmKey();
	struct comshm *shmp;

	if (( shmkey = spublicGetShmKey()) < 0) {
		userlog(" [%s][%d]get share memory key err!",__FILE__,__LINE__);
		return NULL;
	}
	
	if (( shmid = shmget(shmkey,sizeof(struct comshm),
		PERMS|IPC_CREAT)) < 0 ) {
		userlog(" [%s][%s]get share memory id err!",__FILE__,__LINE__);
		return NULL;
	}
	
	if ((shmp = (struct comshm *) shmat (shmid, (char *) 0,0))
		== (struct comshm *) -1) {
		userlog(" share memory shmat err!",__FILE__,__LINE__);
		return NULL;
	}

	return shmp;
}

/***** 
�ӹ����ڴ���ȡ���� 
@inparam 
@return  comshm *
****/
struct comshm *
spublicGetShm()
{
	int shmid;
	key_t shmkey,spublicGetShmKey();
	struct comshm *shmp;

	if (( shmkey = spublicGetShmKey()) < 0) {
		userlog(" [%s][%d]get share memory key err!",__FILE__,__LINE__);
	        return NULL;
	}
	
	if (( shmid = shmget(shmkey,sizeof(struct comshm), 0)) < 0 ) {
		userlog(" [%s][%d]get share memory id err!",__FILE__,__LINE__);
		return NULL;
	}
	
	errno = 0;

	if ((shmp = (struct comshm *) shmat (shmid, 0,0)) == \
	(struct comshm *) -1) {
		userlog("shmat errno=%d\n",errno);
		userlog(" share memory shmat err!",__FILE__,__LINE__);
		return NULL;
	}

	return shmp;
}


/******************************
 name:     spublicDelKeyShm  
 writer:   zhaohao           
 date:     2001.02.10        
 function: ɾ�������ڴ���    
           ������            
@inparam 
@return  int
*******************************/
int spublicDelKeyShm()
{
	int  shmid;
	int  rtn_value;
	key_t shmkey,spublicGetShmKey();

	rtn_value = 0;

	if (( shmkey = spublicGetShmKey()) < 0) {
		userlog(" [%s][%d]get share memory key err!",__FILE__,__LINE__);
		userlog("ȡ�����ڴ��ֵʧ��!\n");
		rtn_value = -1;
		return rtn_value;
	}

	if ((shmid= shmget(shmkey,sizeof(struct comshm),PERMS|IPC_CREAT))< 0 ) {
		userlog(" get share memory id err!",__FILE__,__LINE__);
		userlog("ȡ�����ڴ�IDʧ��!\n");
		rtn_value = -1;
		return rtn_value;
        }

        if (( shmctl (shmid, IPC_RMID, 0)) < 0) {
                userlog(" delete share memory  err!",__FILE__,__LINE__);
		userlog("ɾ�������ڴ�ʧ��!\n");
		rtn_value = -1;
		return rtn_value;
        }

        return rtn_value;
}

/****
 �Ͽ������ڴ������ݽṹ������ 
 @inparam 
@return  int
 ****/
int
spublicDtcShm(struct comshm *shmp)
{
        if (shmdt ((char *) shmp) < 0 ) {
                userlog(" detach share memory err ! ",__FILE__,__LINE__);
                return FALSE;
        }
        return TRUE;
}


/* 2001.02.11 */
/***** 
�����ṩ�ı�ǩ������Ӧ�ķ������������ݿ������û�������
@inparam 
@return  struct spublicdblogin   
****/
struct spublicdblogin spublicGetDBP(char *connect_name) 
{
	struct comshm *shmp, *spublicGetShm();
	struct spublicdblogin sdblogin;
	int  count, i;

    userlog("----- [%s]spublicGetDBP is starting ......\n",__FILE__);
	shmp = spublicGetShm();
	if (shmp == NULL ) {
		userlog("get share memory err!\n");
		strcpy(sdblogin.label, NULL);
		strcpy(sdblogin.server, NULL);
		strcpy(sdblogin.database, NULL);
		strcpy(sdblogin.username, NULL);
		strcpy(sdblogin.password, NULL);
		return sdblogin;
	}

	count = shmp->sdbloginno;
	for ( i=0; i<count; i++)
        {
		if (strcmp(shmp->sdblogin[i].label, connect_name) == 0) {
			sdblogin = shmp->sdblogin[i];
/*			printf("test--sdblogin.label=[%s]\n",sdblogin.label);
			printf("test--sdblogin.server=[%s]\n",sdblogin.server);
			printf("test--sdblogin.database=[%s]\n",sdblogin.database);
			printf("test--sdblogin.username=[%s]\n",sdblogin.username);
			printf("test--sdblogin.password=[%s]\n",sdblogin.password);
*/
			break;	
		}
		
	}

	if (count == 0) {
		strcpy(sdblogin.label, NULL);
		strcpy(sdblogin.server, NULL);
		strcpy(sdblogin.database, NULL);
		strcpy(sdblogin.username, NULL);
		strcpy(sdblogin.password, NULL);
	}
	spublicDtcShm( shmp );	
	
	return sdblogin;
}

/*****************************
 name:     spublicPutKeyShm 
 writer:   zhaohao          
 date:     2001.02.10       
 function: �������ļ�����   
           �����ڴ�         
 @inparam 
@return  int
*******************************/
int spublicPutKeyShm()
{
	int  count;
	char tmp[LINE+1];
	char lbl[MAXLABELLEN+1];
	char srv[MAXLABELLEN+1];
	char db[MAXLABELLEN+1];
	char user[MAXLABELLEN+1];
	char passwd[MAXENDELEN+1];
	char baklbl[MAXLABELLEN+1];
	char temp_passwd[MAXENDELEN+1];
	char tmp_pass1[MAXENDELEN+1];
	char tmp_pass2[MAXENDELEN+1];

	char filename[LINE];
	FILE *fp;
	struct comshm *comshm;

	memset(tmp,0,LINE+1);
	memset(lbl,0,MAXLABELLEN+1);
	memset(srv,0,MAXLABELLEN+1);
	memset(db,0,MAXLABELLEN+1);
	memset(user,0,MAXLABELLEN+1);
	memset(passwd,0,MAXENDELEN+1);
	memset(temp_passwd,0,MAXENDELEN+1);
	memset(baklbl,0,MAXENDELEN+1);

	spublicGetCfgDir( TRANSSDBLOGIN, filename );
	if ( filename == NULL ) {
		userlog("get pathname err!",__FILE__,__LINE__);
		userlog("ȡ�����ļ�ʧ��!\n",__FILE__,__LINE__);
		return(-1);
	}

	if (( fp = fopen(filename,"r")) == NULL ) {
		userlog("open file err!",__FILE__,__LINE__);
		userlog("�������ļ�ʧ��!\n",__FILE__,__LINE__);
		return(-1);
	}

	/* ���������ڴ� */
	if (( comshm = spublicCreatShm()) == NULL ) {
		userlog("Creat share memory err!",__FILE__,__LINE__);
		userlog("���������ڴ�ʧ��!\n",__FILE__,__LINE__);
		return(-1);
	}

        memset(comshm,0,sizeof(struct comshm));

	count=0;
	while (fgets(tmp,LINE,fp) != NULL)  
	{
        	memset(tmp_pass1, 0, sizeof(tmp_pass1));
        	memset(tmp_pass2, 0, sizeof(tmp_pass2));

		if (tmp[0] != COMMENT ) 
		{
			sscanf (tmp,"%s%s%s%s%s%s",lbl,srv,db,user,passwd,baklbl);
			strcpy(comshm->sdblogin[count].label,lbl);
			strcpy(comshm->sdblogin[count].server,srv);
			strcpy(comshm->sdblogin[count].database,db);
			strcpy(comshm->sdblogin[count].username,user);
			strcpy(comshm->sdblogin[count].baklbl,baklbl);
	
			/* ��������ܺ���빲���ڴ� */
			spublicEnDePasswd(passwd, tmp_pass2, MASTERKEY, DECRYPT);
			strcpy(comshm->sdblogin[count].password, tmp_pass2);

			count++;
			memset(lbl,0,MAXLABELLEN+1);
			memset(srv,0,MAXLABELLEN+1);
			memset(db,0,MAXLABELLEN+1);
			memset(user,0,MAXLABELLEN+1);
			memset(passwd,0,MAXENDELEN+1);
			memset(baklbl,0,MAXENDELEN+1);
		}
		memset(tmp,0,LINE+1);
	}
	comshm->sdbloginno = count;
	fclose(fp);

	spublicDtcShm(comshm);

	userlog("д�빲���ڴ�ɹ�!");

	return(0);
}

/*
void spublicGetKeyShm(char *connect_name)
{
	int  rtn_value;

        if ( (rtn_value = spublicDBLogin(connect_name)) < 0 ) {
                userlog("The label name is wrong!\n");
                return NULL;
        }
        else {
                userlog("The label is right!\n");
        }
}
*/


/**** 
ȡ����־�����ڴ��ֵ 
 @inparam 
@return  key_t
****/
key_t
spublicLogGetShmKey()
{
	key_t kid;
	char filename[LINE];
	memset(filename, 0, sizeof(filename));
	userlog("---- before ShmKey file [%s]\n",filename);
	spublicGetCfgDir(SHMKLOGDIR, filename);
	userlog("---- ShmKey file [%s]\n",filename);
	kid = ftok( filename, SHMKEY);
	return kid;
}

/***** 
���������ڴ� 
 @inparam 
@return  struct logshm *
****/
struct logshm *
spublicLogCreatShm()
{
	int shmid;
	key_t shmkey,spublicLogGetShmKey();
	struct logshm *shmp;

	if (( shmkey = spublicLogGetShmKey()) < 0) {
		userlog(" [%s][%d]get share memory key err!",__FILE__,__LINE__);
		return NULL;
	}
	
	if (( shmid = shmget(shmkey,sizeof(struct logshm),
		PERMS|IPC_CREAT)) < 0 ) {
		userlog(" get share memory id err!",__FILE__,__LINE__);
		return NULL;
	}
	
	if ((shmp = (struct logshm *) shmat (shmid, (char *) 0,0))
		== (struct logshm *) -1) {
		userlog(" share memory shmat err!",__FILE__,__LINE__);
		return NULL;
	}

	return shmp;
}

/**** 
�ӹ����ڴ���ȡ���� 
 @inparam 
@return  struct logshm *
****/
struct logshm *
spublicLogGetShm()
{
	int shmid;
	key_t shmkey,spublicLogGetShmKey();
	struct logshm *shmp;

	if (( shmkey = spublicLogGetShmKey()) < 0) {
		userlog(" [%s][%d]get share memory key err!",__FILE__,__LINE__);
	        return NULL;
	}
	
	if (( shmid = shmget(shmkey,sizeof(struct logshm), 0)) < 0 ) {
		userlog(" get share memory id err!",__FILE__,__LINE__);
		return NULL;
	}
	
	errno = 0;

	if ((shmp = (struct logshm *) shmat (shmid, 0,0)) == \
	(struct logshm *) -1) {
		userlog("shmat errno=%d\n",errno);
		userlog(" share memory shmat err!",__FILE__,__LINE__);
		return NULL;
	}

	return shmp;
}


/*********************************
name:     spublicLogDelKeyShm  
writer:   zhaohao              
date:     2001.12.21           
function: ɾ�������ڴ���       
          ������               
 @inparam 
@return  int
**********************************/
int spublicLogDelKeyShm()
{
	int  shmid;
	int  rtn_value;
	key_t shmkey,spublicLogGetShmKey();

	rtn_value = 0;

	if (( shmkey = spublicLogGetShmKey()) < 0) {
		userlog(" [%s][%d]get share memory key err!",__FILE__,__LINE__);
		userlog("ȡ�����ڴ��ֵʧ��!\n");
		rtn_value = -1;
		return rtn_value;
	}

	if ((shmid= shmget(shmkey,sizeof(struct logshm),PERMS|IPC_CREAT))< 0 ) {
		userlog(" get share memory id err!",__FILE__,__LINE__);
		userlog("ȡ�����ڴ�IDʧ��!\n");
		rtn_value = -1;
		return rtn_value;
        }

        if (( shmctl (shmid, IPC_RMID, 0)) < 0) {
                userlog(" delete share memory  err!",__FILE__,__LINE__);
		userlog("ɾ�������ڴ�ʧ��!\n");
		rtn_value = -1;
		return rtn_value;
        }

        return rtn_value;
}

/**** 
�Ͽ������ڴ������ݽṹ������ 
@inparam 
@return  int
***/
int
spublicLogDtcShm(struct logshm *shmp)
{
        if (shmdt ((char *) shmp) < 0 ) {
                userlog(" detach share memory err ! ",__FILE__,__LINE__);
                return FALSE;
        }
        return TRUE;
}

/* 2001.12.21 */

/**** 
�����ṩ�Ĳ����뷵���Ƿ������־ 
 @inparam 
@return  int
****/
int spublicLogGetFlag(char *codelevel) 
{
	struct logshm *shmp, *spublicLogGetShm();
	struct spublicloglevel sloglevel;
	int  count, i;

	shmp = spublicLogGetShm();
	if (shmp == NULL ) {
		userlog("get share memory err!\n");
		return(TRUE);
	}

	count = shmp->sloglevelno;
	for ( i=0; i<count; i++)
        {
		if (strcmp(shmp->sloglevel[i].codelevel, codelevel) == 0) {
			return(shmp->sloglevel[i].flag);
		}
	}

	if (i == count || count == 0) {
		return(TRUE);
	}

	spublicLogDtcShm( shmp );	
	
	return(TRUE);
}


/* 2001.12.21 */
/**** 
�����ṩ�Ĳ����뷵���Ƿ������־�ṹ 
 @inparam 
@return  struct spublicloglevel
***/
struct spublicloglevel spublicLogGetDBP(char *codelevel) 
{
	struct logshm *shmp, *spublicLogGetShm();
	struct spublicloglevel sloglevel;
	int  count, i;

	shmp = spublicLogGetShm();
	if (shmp == NULL ) {
		userlog("get share memory err!\n");
		strcpy(sloglevel.codelevel, "00000");
		sloglevel.flag  = 1;
		return sloglevel;
	}

	count = shmp->sloglevelno;
	for ( i=0; i<count; i++)
        {
		if (strcmp(shmp->sloglevel[i].codelevel, codelevel) == 0) {
			sloglevel = shmp->sloglevel[i];

			return sloglevel;
		}
	}

	if (i == count || i == 0) {
		strcpy(sloglevel.codelevel, "00000");
		sloglevel.flag = 1;
	}

	spublicLogDtcShm( shmp );	
	
	return sloglevel;
}

/*********************************
name:     spublicLogPutKeyShm  
writer:   zhaohao              
date:     2001.12.21           
function: �������ļ�����       
          �����ڴ�             
@inparam 
@return  struct spublicloglevel
**********************************/
int spublicLogPutKeyShm()
{
	int  count;
	char tmp[LINE+1];

	char filename[LINE];
	FILE *fp;
	struct logshm *logshm;

	memset(tmp,0,LINE+1);

	spublicGetCfgDir( TRANSSLOGLEVEL, filename );
	if ( filename == NULL ) {
		userlog("get pathname err!",__FILE__,__LINE__);
		userlog("ȡ�����ļ�ʧ��!\n",__FILE__,__LINE__);
		return(-1);
	}

	if (( fp = fopen(filename,"r")) == NULL ) {
		userlog("open file err!",__FILE__,__LINE__);
		userlog("�������ļ�ʧ��!\n",__FILE__,__LINE__);
		return(-1);
	}

	/* ���������ڴ� */
	if (( logshm = spublicLogCreatShm()) == NULL ) {
		userlog("Creat share memory err!",__FILE__,__LINE__);
		userlog("���������ڴ�ʧ��!\n",__FILE__,__LINE__);
		return(-1);
	}

        memset(logshm,0,sizeof(struct logshm));

	count=0;
	while (fgets(tmp,LINE,fp) != NULL)  
	{
		if (tmp[0] != COMMENT ) 
		{
			strncpy(logshm->sloglevel[count].codelevel, tmp, 5);
			logshm->sloglevel[count].flag = atoi(tmp+5);
printf("codelelve=[%s][%d]\n", logshm->sloglevel[count].codelevel,logshm->sloglevel[count].flag);
	
			count++;
		}
		memset(tmp,0,LINE+1);
	}
	logshm->sloglevelno = count;
	fclose(fp);

	spublicLogDtcShm(logshm);

	userlog("д�빲���ڴ�ɹ�!");

	return(0);
}

#endif /* __PUBLICSHM_CP */



/**** 
�ӹ̶�λ��ȡ�ַ��� 
@inparam
		Դ�ַ�         
		��ʼλ��       
		����λ��       
@outparam         
		Ŀ�괮         
****/
substring(char * dest,const char * src,int start,int n)
{
    int i,j,n1,s1;
    j=strlen(src);
    if (start>j)
    {
             dest[0]=0;
        return -1;
    }
    if (start+n>j+1)
    {
             n1=j+1-start;
    }
    else
    {
             n1=n;
    }
    for (i=0;i<n1;i++)
    {
             dest[i]=src[start-1+i];
    }
    dest[i]=0;
}


/**********************************************
 ����: ʵ���ڴ���ˮ                          
 ʱ��: 2002.06.12/dangsl                     
 �汾: 1.0                                
***********************************************/

/**** 
������ֵ�źŵ� 
@inparam
		�ڴ��ֵ  
@return   int     
****/
int NCreatOneSem(const key_t semkey)
{
	int semid,semval;
        union semun {
        	int val;
                struct semid_ds *buf;
                unsigned short *array;
                } semctl_arg;


	semid=semget(semkey,1,IPC_CREAT|PERMS);  
        if(semid<0){
                userlog("semaphoreid get error!\n");
       		return -1;
	}

        if((semval=semctl(semid,0,GETVAL,0))<0)
                userlog("GETVAL error!\n");
        else
	        if(semval==0){
                	semctl_arg.val=1;
                        if(semctl(semid,0,SETVAL,semctl_arg)<0)
                      		userlog("SETVAL error\n");
                }   
          

       return semid;
}

/****
����semidɾ���źŵ� 
****/
int NSemDel(int semid)
{
 	if((semctl(semid,0,IPC_RMID,0))<0) {
 		userlog("delete semaphore error!\n");
 		return -1;
 	}

       	return 0;
}



/**** 
�򿪵�ֵ�źŵ� 
***/
int NOpenOneSem(const key_t semkey)
{
        int semid;

	semid=semget(semkey,1,0);  
        if(semid<0){
        	userlog("semaphoreid get error!\n");
                return -1;
        }
	return semid;
}


/****
�ӵ�ֵ�� 
****/
int Nsm_sem_lock(const int semid)
{
	while((semop(semid,&op_lock,1))<0){
        	if(errno==EINTR){
			usleep(1000);
			continue;
		}
		userlog("sem op_lock error!\n");
                return -1;
        }
        return 0;
}


/*** 
�ͷŵ�ֵ�� 
****/
int  Nsm_sem_unlock(const int semid)
{
 
        while((semop(semid,&op_unlock,1))<0){
        	if(errno==EINTR){
			usleep(1000);
			continue;
		}
		userlog("sem op_unlock error!\n");
                return -1;
        } 
        return 0;
}



/*** 
�Է������źŵƼӵ�ֵ�� 
***/
int Nsem_lock_nowait(const int semid)
{
struct sembuf op_no_lock={ 0,-1,IPC_NOWAIT};

        while(( semop(semid,&op_no_lock,1) ) < 0 ){
                if( errno==EINTR ) {
                        usleep(1000);
                        continue;
                }
                else if(errno== EAGAIN||errno==EFBIG){
                        userlog("sem_lock_nowait ret\n");
                        return -1;
                }
                userlog("sem op_lock error!\n");
                return -1;
        }
        return 0;
}


/*** 
�Է������źŵƽⵥֵ�� 
****/
int Nsem_unlock_nowait(const int semid)
{
struct sembuf op_no_unlock={ 0,1,IPC_NOWAIT};

 	while(( semop(semid,&op_no_unlock,1) ) < 0 ){
 		if( errno==EINTR ) {
 			usleep(1000);
 			continue;
 		}
 		else if(errno== EAGAIN||errno==EFBIG){
    			userlog("sem_unlock_nowait ret\n");
 			return -1;
 		}
 		userlog("sem op_unlock error!\n");
 		return -1;
 	}
 	return 0;
}

/****
���������ڴ�
***/
struct acceptshm * 
NCreatShm(key_t shmkey, int length, int *shmid)
{
	struct acceptshm *shmp;

	if((*shmid=shmget(shmkey,length, PERMS|IPC_CREAT)) < 0){
                userlog(" get share memory id err!\n");
                return NULL;
        }

	if((shmp = (struct acceptshm *)shmat(*shmid, (struct acceptshm  *)0, 0)) == (struct acceptshm  *) -1) {
                userlog(" share memory shmat err!\n");
                return NULL;
        }

        return shmp;
}


/****
----------ʹ���Ѿ������Ĺ����ڴ�---------------
****/
struct acceptshm * 
NOpenShm(key_t shmkey)
{
	int	shmid;
	struct acceptshm *shmp;

	if((shmid=shmget(shmkey, 0, 0)) < 0){
                userlog(" open get share memory id err!\n");
                return NULL;
        }

	if((shmp = (struct acceptshm  *)shmat(shmid, (struct acceptshm  *)0, 0)) == (struct acceptshm  *) -1) {
                userlog(" open share memory shmat err!\n");
                return NULL;
        }

        return shmp;
}

/****
--------�ر��Ѿ��򿪵Ĺ����ڴ�-------------------
****/
int NCloseShm(const struct acceptshm *shmp){
	int	lret;
	lret=NDtcShm(shmp);
	return lret;
}
int 
NDtcShm(const struct acceptshm *shmp)
{
	if((shmdt((char *)shmp)) < 0 ) {
		userlog(" detach share memory err ! \n");
		return -1;
	}
	return 0;
}


/*****
----------ɾ���Ѿ������Ĺ����ڴ�------------
****/
int
NDelShm(key_t shmkey)
{
int 	shmid;

	if ((shmid= shmget(shmkey, 0, 0)) < 0 ) {
                userlog(" get share memory id err!\n");
                return -1;
        }

	if ((shmctl (shmid, IPC_RMID, (struct shmid_ds *)0)) < 0) {
		userlog(" delete share memory  err!\n");
		return -2;
	}

	return 0;
}


/****
--------�ɸ��ݷ���ֵ�ж�OpenShm Err��ԭ��--------
*****/
int
NOpenShmErr(key_t shmkey)
{
	int	shmid;
	struct acceptshm *shmp;

	if((shmid=shmget(shmkey, 0, 0)) < 0){
                userlog(" open get share memory id err!\n");
                return -1;
        }

	if((shmp = (struct acceptshm *)shmat(shmid, (struct acceptshm *)0, 0)) == (struct acceptshm *) -1) {
                userlog(" open share memory shmat err!\n");
                return -2;
        }

        return 0;
}

/****
ȡ��ϵͳʱ��
@return  �ַ���
***/
char *GetSysDatetime()
{
	struct tm *p;
        time_t t;
	char   tempsec[3],tempmin[3],temphour[3];
	char   tempday[3],tempmon[3],tempyear[5];
	char   temptime[30];

        t = time(NULL);
        p = localtime(&t);

	memset(tempsec,0,sizeof(tempsec));
	memset(tempmin,0,sizeof(tempmin));
	memset(temphour,0,sizeof(temphour));
	memset(tempday,0,sizeof(tempday));
	memset(tempmon,0,sizeof(tempmon));
	memset(tempyear,0,sizeof(tempyear));

	sprintf(tempsec,"%d",p->tm_sec);
	sprintf(tempmin,"%d",p->tm_min);
	sprintf(temphour,"%d",p->tm_hour);
	sprintf(tempday,"%d",p->tm_mday);
	sprintf(tempmon,"%d",p->tm_mon+1);
	sprintf(tempyear,"%d",p->tm_year+1900);
	if(p->tm_sec<10)
	{
		memset(tempsec,0,sizeof(tempsec));
		sprintf(tempsec,"0%d",p->tm_sec); 
	}
	if(p->tm_min<10)  
	{
		memset(tempmin,0,sizeof(tempmin));
		sprintf(tempmin,"0%d",p->tm_min); 
	}
	if(p->tm_hour<10)
	{
		memset(temphour,0,sizeof(temphour));
		sprintf(temphour,"0%d",p->tm_hour); 
	}
	if(p->tm_mday<10)
	{
		memset(tempday,0,sizeof(tempday));
		sprintf(tempday,"0%d",p->tm_mday); 
	}
	if(p->tm_mon+1<10)
	{ 
		memset(tempmon,0,sizeof(tempmon));
		sprintf(tempmon,"0%d",p->tm_mon+1);
	}
	memset(temptime,0,sizeof(temptime));
	strcat(temptime,tempyear);
	strcat(temptime,tempmon);
	strcat(temptime,tempday);
	strcat(temptime,temphour);
	strcat(temptime,tempmin);
	strcat(temptime,tempsec);

	return(temptime);
}

/**�ر��ź��˳�*/
void Quit(int signo)
{
	Nsm_sem_unlock(sig_semid);
	NCloseShm(sig_shmp);
	exit(0);
}

/**
�����ڴ���ˮ
@return int
**/
int CreatMemAccept()
{
        int semid,shmid;
        struct acceptshm *shmp;
	char semfile[LINE],shmfile[LINE],destdate[10],srcdate[20],tempdate[30];
	char tempcmd[LINE+LINE],tempstr[LINE];

	memset(tempdate, 0, sizeof(tempdate));
	memset(shmfile, 0, sizeof(shmfile));
	memset(semfile, 0, sizeof(semfile));
	memset(destdate, 0, sizeof(destdate));
	memset(srcdate, 0, sizeof(srcdate));
	memset(tempcmd, 0, sizeof(tempcmd));
	memset(tempstr, 0, sizeof(tempstr));

	spublicGetCfgDir(ACCSHMKEYFILE, tempstr);
	strcpy(shmfile,tempstr);

	spublicGetCfgDir(ACCSEMKEYFILE, tempstr);
	strcpy(semfile,tempstr);

	memset(tempcmd, 0, sizeof(tempcmd));
	strcpy(tempcmd,"touch ");
	strcat(tempcmd,shmfile);
	system(tempcmd);

	memset(tempcmd, 0, sizeof(tempcmd));
	strcpy(tempcmd,"touch ");
	strcat(tempcmd,semfile);
	system(tempcmd);


        if((semid = NCreatOneSem(ftok(semfile,1)))==NULL)
	{
		userlog("Create Accept Semaphore Error!\n");
		return -1;
	}
	printf("Create Accept Semaphore:\n");
	memset(tempcmd, 0, sizeof(tempcmd));
	memset(tempstr, 0, sizeof(tempstr));
	strcpy(tempcmd,"ipcs -s|grep ");
	sprintf(tempstr,"%d",semid);
	strcat(tempcmd,tempstr);
	system(tempcmd);

        if((shmp = NCreatShm(ftok(shmfile,1),sizeof(struct acceptshm),&shmid))==NULL)
	{
		userlog("Create Accept Shared Memory Error!\n");
		return -2;
	}

	memset(srcdate, 0, sizeof(srcdate));
	memset(destdate, 0, sizeof(destdate));

	strcpy(tempdate,GetSysDatetime());
	strcpy(srcdate,tempdate);
	substring(destdate,srcdate,1,8);
	strcpy(shmp->sysdate,destdate);

	printf("Create Accept Shared Memory:\n");
	memset(tempcmd, 0, sizeof(tempcmd));
	memset(tempstr, 0, sizeof(tempstr));
	strcpy(tempcmd,"ipcs -m|grep ");
	sprintf(tempstr,"%d",shmid);
	strcat(tempcmd,tempstr);
	system(tempcmd);
	
	return 0;
}	

/***
ȡ�ڴ���ˮ
@return  char
***/
char *GetMemAccept()
{
	int semid;
	struct acceptshm *shmp;
	char accept[LINE+LINE],temp[70],temptime[30];
	char semfile[LINE],shmfile[LINE];
	char tempcmd[LINE+LINE],tempstr[LINE];

	memset(temp, 0, sizeof(temp));
	memset(temptime, 0, sizeof(temptime));
	memset(accept, 0, sizeof(accept));
	memset(shmfile, 0, sizeof(shmfile));
	memset(semfile, 0, sizeof(semfile));
	memset(tempcmd, 0, sizeof(tempcmd));
	memset(tempstr, 0, sizeof(tempstr));

	spublicGetCfgDir(ACCSHMKEYFILE, tempstr);
	strcpy(shmfile,tempstr);

	spublicGetCfgDir(ACCSEMKEYFILE, tempstr);
	strcpy(semfile,tempstr);

	/* ���źŵ� */
	if((semid = NOpenOneSem(ftok(semfile,1)))<0)return "";
	/* �򿪹����ڴ� */
	if((shmp = NOpenShm(ftok(shmfile,1)))==NULL)return "";

	/* ȫ�ֱ�������QUIT�����ͷ���Դ */
	sig_semid=semid;
	sig_shmp=shmp;

	/* ���ý����ж��ź� */
	signal(SIGTERM,Quit);

	/* �źŵƼ��� */
	if(Nsm_sem_lock(semid)!=0)return "";

	/* �����ڴ���� */
	shmp->count++;
	sprintf(temp,"%d",shmp->count);

	/* �źŵƽ��� */
	if(Nsm_sem_unlock(semid)!=0)return "";

	/* �����ڴ�ر� */
	if(NCloseShm(shmp)!=0)return "";


	strcpy(temptime,GetSysDatetime());

	strcpy(accept,temptime);
	strcat(accept,temp);


	return accept;
}

/***
ȡ�ڴ�����
@return �ַ���
***/
char *GetMemDate()
{
	int semid;
	struct acceptshm *shmp;
	char accept[LINE],temp[LINE];
	char semfile[LINE],shmfile[LINE],destdate[10],srcdate[20],olddate[10],tempdate[30];
	char tempcmd[LINE+LINE],tempstr[LINE];

	memset(accept, 0, sizeof(accept));
	memset(temp, 0, sizeof(temp));
	memset(shmfile, 0, sizeof(shmfile));
	memset(semfile, 0, sizeof(semfile));
	memset(destdate, 0, sizeof(destdate));
	memset(srcdate, 0, sizeof(srcdate));
	memset(olddate, 0, sizeof(olddate));
	memset(tempcmd, 0, sizeof(tempcmd));
	memset(tempstr, 0, sizeof(tempstr));

	spublicGetCfgDir(ACCSHMKEYFILE, tempstr);
	strcpy(shmfile,tempstr);

	spublicGetCfgDir(ACCSEMKEYFILE, tempstr);
	strcpy(semfile,tempstr);

	/* ���źŵ� */
	if((semid = NOpenOneSem(ftok(semfile,1)))<0)return "";
	/* �򿪹����ڴ� */
	if((shmp = NOpenShm(ftok(shmfile,1)))==NULL)return "";

	/* ȫ�ֱ�������QUIT�����ͷ���Դ */
	sig_semid=semid;
	sig_shmp=shmp;

	memset(srcdate, 0, sizeof(srcdate));
	memset(destdate, 0, sizeof(destdate));

	strcpy(tempdate,GetSysDatetime());
	strcpy(srcdate,tempdate);
	substring(destdate,srcdate,1,8);

	if(strcmp(shmp->sysdate,destdate)==0) 
	{
		return "";
	}
	else
	{
		/* ���ý����ж��ź� */
		signal(SIGTERM,Quit);

		memset(olddate,0,sizeof(olddate));
		strcpy(olddate,shmp->sysdate);

		/* �źŵƼ��� */
		if(Nsm_sem_lock(semid)!=0)return "";

		strcpy(shmp->sysdate,destdate);

		/* �źŵƽ��� */
		if(Nsm_sem_unlock(semid)!=0)return "";

		/* �����ڴ�ر� */
		if(NCloseShm(shmp)!=0)return "";

		return olddate;
	}
}

/***
ɾ���ڴ���ˮ
@return int
***/
int DelMemAccept()
{
	int semid;
	struct acceptshm *shmp;
	char accept[LINE];
	char semfile[LINE],shmfile[LINE];

	memset(shmfile, 0, sizeof(shmfile));
	spublicGetCfgDir(ACCSHMKEYFILE, shmfile);
	if(NDelShm(ftok(shmfile,1))!=0)return -1;

	memset(semfile, 0, sizeof(semfile));
	spublicGetCfgDir(ACCSEMKEYFILE, semfile);
	if((semid = NOpenOneSem(ftok(semfile,1)))<0)return -2;
	if(NSemDel(semid)!=0)return -3;

	userlog("Accept Shared Memory and Semaphore was removed!\n");
	printf("Accept Shared Memory and Semaphore was removed!\n");

	return 0;
}




/**
 �ѵ�����־д����ˮ
**/
int changeFile(char *strStdout)
{
	char strDate[10],tempDate[30]; /* �������� */
	char strNewStdout[60];
	char strCmd[100];

	memset(strDate,0,sizeof(strDate));
	memset(tempDate,0,sizeof(tempDate));
	memset(strNewStdout,0,sizeof(strNewStdout));
	memset(strCmd,0,sizeof(strCmd));

	strcpy(tempDate,GetMemDate());
	
	if(strlen(tempDate)!=0)
    	{
		/* �л��ļ� */
		strcpy(strDate,tempDate);

		sprintf(strNewStdout,"%s.%s", strStdout, strDate);
		fprintf(stderr,"%s\n", strNewStdout);
		sprintf(strCmd, "cp %s %s", strStdout, strNewStdout);
		fprintf(stderr,"%s\n",strCmd);
		system(strCmd);
	
		userlog("strCmd:%s\n",strCmd);
		
		/* ���stdout�ļ� */
		if (-1 == truncate(strStdout,0))
		{
			fprintf(stderr,"changeFile error\n");
			return -1;
		}
    	}
    	return 0;
}

