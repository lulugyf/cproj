#include "publicsrv.h"


extern int errno;

#define SPRI	"/"

/* �ļ������� */
/******************************************
name:     spublicPrnFormat  						 
writer:   zhaohao           						 
modi:     zhaohao           						 
date:     2001.11.2        						 
function: ���������ļ���ӡ��Ʊ  					
****************************************************************************/
int spublicPrnFormat(char in_array[][60+1], char *formatfile)
{
	int  count, len;
	int  i, j, tmp_line;
	int  flag;
	char tmp[LINE+1];
	char tmp_dt[2+1];
	char prn_buf[1000+1];
	char prn_buf1[1000+1];
	char prn_buf2[1000+1];

	PRNFORMAT prnformat;

	char filename[LINE];
	FILE *fp;

	memset(tmp,0,LINE+1);
	memset(prn_buf,0,1000+1);
	memset(prn_buf1,0,1000+1);
	memset(prn_buf2,0,1000+1);

	spublicGetCfgDir( formatfile, filename );
	if ( filename == NULL ) {
		userlog("get pathname err!",__FILE__,__LINE__);
		return(-1);
	}

	if (( fp = fopen(filename,"r")) == NULL ) {
		userlog("open file err!",__FILE__,__LINE__);
		return(-1);
	}

	/* ����͸����ӡ��ʽ */

	Pinitprintbright(); 

	count = 1;
	tmp_line = 1;
	flag = 0;

	while (fgets(tmp,LINE,fp) != NULL)  
	{
        	memset(&prnformat, 0 ,sizeof(PRNFORMAT));
		strcpy(prnformat.line_no, "0");
		
		if (tmp[0] != COMMENT ) 
		{
			len=strlen(tmp);
			tmp[len-1] = '\0';

			strncpy(prnformat.line_no, tmp, 4);
			strncpy(prnformat.col_width, tmp+4, 4);
			strncpy(prnformat.order_type, tmp+8, 2);
			strncpy(prnformat.format_type, tmp+10, 2);
			strncpy(prnformat.all_var, tmp+12,36);
			
			if (tmp_line == atoi(prnformat.line_no)) {
				/* ����ͬһ�еĴ��� */
				memset(prn_buf, 0, sizeof(prn_buf));
				memset(prn_buf2,0,sizeof(prn_buf2));

				if (strcmp(Trim(prnformat.format_type), "s") == 0) {
					sprintf(prn_buf, "%%%c%ds", 
						prnformat.order_type[0],
						atoi(prnformat.col_width));
					sprintf(prn_buf2, prn_buf, Trim((char *)(in_array+atoi(prnformat.all_var))));
				}
				else if (strcmp(Trim(prnformat.format_type), "x") == 0) {
					sprintf(prn_buf, "%%%c%ds", 
						prnformat.order_type[0],
						atoi(prnformat.col_width));
					sprintf(prn_buf2, prn_buf, Trim(prnformat.all_var));
				}
				else if (strcmp(Trim(prnformat.format_type), "t") == 0) {
					sprintf(prn_buf, "%%%c%ds", 
						prnformat.order_type[0],
						atoi(prnformat.col_width));
					memset(tmp_dt, 0, sizeof(tmp_dt));
					strcpy(tmp_dt, Trim(prnformat.all_var));
					switch(tmp_dt[0]) {
						case 'y':
							sprintf(prn_buf2, prn_buf, Tgetyear());
							break;
						case 'm':
							sprintf(prn_buf2, prn_buf, Tgetmonth());
							break;
						case 'd':
							sprintf(prn_buf2, prn_buf, Tgetday());
							break;
						case 'h':
							sprintf(prn_buf2, prn_buf, Tgethour());
							break;
						case 'i':
							sprintf(prn_buf2, prn_buf, Tgetminute());
							break;
						case 's':
							sprintf(prn_buf2, prn_buf, Tgetsecond());
							break;
						default:
							break;
					}
				}
				else if (strcmp(Trim(prnformat.format_type), "n") == 0) {
					sprintf(prn_buf, "%%%c%ds", 
						prnformat.order_type[0],
						atoi(prnformat.col_width));
					if (prnformat.all_var[0] == 0) {
						printf("\n");
					}
					else {
						sprintf(prn_buf2, prn_buf, Trim(prnformat.all_var));
						printf("\n");
					}
				}

				strcat(prn_buf1, prn_buf2);
				flag = 0;
			}
			else {
			/* ���л��еĴ��� */
				printf("%s\n",prn_buf1);
				memset(prn_buf1, 0, sizeof(prn_buf1));

				memset(prn_buf, 0, sizeof(prn_buf));
				memset(prn_buf2,0,sizeof(prn_buf2));

				if (strcmp(Trim(prnformat.format_type), "s") == 0) {
					sprintf(prn_buf, "%%%c%ds", 
						prnformat.order_type[0],
						atoi(prnformat.col_width));
					sprintf(prn_buf2, prn_buf, Trim((char *)(in_array+atoi(prnformat.all_var))));
				}
				else if (strcmp(Trim(prnformat.format_type), "x") == 0) {
					sprintf(prn_buf, "%%%c%ds", 
						prnformat.order_type[0],
						atoi(prnformat.col_width));
					sprintf(prn_buf2, prn_buf, Trim(prnformat.all_var));
				}
				else if (strcmp(Trim(prnformat.format_type), "t") == 0) {
					sprintf(prn_buf, "%%%c%ds", 
						prnformat.order_type[0],
						atoi(prnformat.col_width));
					memset(tmp_dt, 0, sizeof(tmp_dt));
					strcpy(tmp_dt, Trim(prnformat.all_var));
					switch(tmp_dt[0]) {
						case 'y':
							sprintf(prn_buf2, prn_buf, Tgetyear());
							break;
						case 'm':
							sprintf(prn_buf2, prn_buf, Tgetmonth());
							break;
						case 'd':
							sprintf(prn_buf2, prn_buf, Tgetday());
							break;
						case 'h':
							sprintf(prn_buf2, prn_buf, Tgethour());
							break;
						case 'i':
							sprintf(prn_buf2, prn_buf, Tgetminute());
							break;
						case 's':
							sprintf(prn_buf2, prn_buf, Tgetsecond());
							break;
						default:
							break;
					}
				}
				else if (strcmp(Trim(prnformat.format_type), "n") == 0) {
					sprintf(prn_buf, "%%%c%ds", 
						prnformat.order_type[0],
						atoi(prnformat.col_width));
					if (prnformat.all_var[0] == 0) {
						printf("\n");
					}
					else {
						sprintf(prn_buf2, prn_buf, Trim(prnformat.all_var));
						printf("\n");
					}
				}

				strcpy(prn_buf1, prn_buf2);	

				flag = 1;

				tmp_line++;
			}

			memset(prn_buf, 0, sizeof(prn_buf));
			memset(prn_buf2, 0, sizeof(prn_buf2));
			memset(tmp,0,LINE+1);
			count++;
		}
	}
	fclose(fp);


	/* �˳�͸����ӡ��ʽ */

	Pendprintbright(); 


	return(0);
}



char *spublicGetEnvDir( char *env)
{
	char * envp;
    if ((envp = getenv(env)) == NULL) {
		userlog(" Get env err !!",__FILE__,__LINE__);
		return NULL;
	}
	return envp;
}


#define         CFGDIR  "/cfg"

/****
 �����ļ���ȡ��$WORKDIR/cfg�µ��ļ�ȫ·�� 
 *****/
int spublicGetCfgDir(const char *file, char *rtn_path)
{
	char *envp;

        envp = spublicGetEnvDir(WORKDIR);
  
        if ( envp == NULL )
                return -1;
        memset(rtn_path,0,LINE);

        strcpy(rtn_path,envp);
        strcat(rtn_path,CFGDIR);
        strcat(rtn_path,SPRI);
        strcat(rtn_path,file);
        return 0;
}

#define         BINDIR  "/bin"

/*****
 �����ļ���ȡ��$WORKDIR/bin�µ��ļ�ȫ·�� 
 *****/
int
spublicGetBinDir(const char *file, char *rtn_path)
{
	char *envp;

        envp = spublicGetEnvDir(WORKDIR);
        if ( envp == NULL )
                return -1;
        memset(rtn_path,0,LINE);

        strcpy(rtn_path,envp);
        strcat(rtn_path,BINDIR); 
	strcat(rtn_path,SPRI);
        strcat(rtn_path,file);

        return 0;
}


#define         INCLUDEDIR  "/include"

/***** 
�����ļ���ȡ��$WORKDIR/include�µ��ļ�ȫ·�� 
*****/
int
spublicGetIncludeDir(const char *file, char *rtn_path)
{
	char *envp;

        envp = spublicGetEnvDir(WORKDIR);
        if ( envp == NULL )
                return -1;
        memset(rtn_path,0,LINE);

        strcpy(rtn_path,envp);
        strcat(rtn_path,INCLUDEDIR);
        strcat(rtn_path,SPRI);
        strcat(rtn_path,file);

        return 0;
}


#define         LIBDIR  "/lib"

/**** 
�����ļ���ȡ��$WORKDIR/lib�µ��ļ�ȫ·�� 
******/
int
spublicGetLibDir(const char *file, char *rtn_path)
{
	char *envp;

        envp = spublicGetEnvDir(WORKDIR);
        if ( envp == NULL )
                return -1;
        memset(rtn_path,0,LINE);

        strcpy(rtn_path,envp);
        strcat(rtn_path,LIBDIR);
        strcat(rtn_path,SPRI);
        strcat(rtn_path,file);

        return 0;
}


#define         PUBLICDIR  "/public"

/**** 
�����ļ���ȡ��$WORKDIR/public�µ��ļ�ȫ·�� 
*****/
int
spublicGetPublicDir(const char *file, char *rtn_path)
{
	char *envp;

        envp = spublicGetEnvDir(WORKDIR);
        if ( envp == NULL )
                return -1;
        memset(rtn_path,0,LINE);

        strcpy(rtn_path,envp);
        strcat(rtn_path,PUBLICDIR);
        strcat(rtn_path,SPRI);
        strcat(rtn_path,file);

        return 0;
}

#define         TMPDIR  "/tmp"

/**** 
�����ļ���ȡ��$WORKDIR/tmp�µ��ļ�ȫ·�� 
*******/
int spublicGetTmpDir(const char *file, char *rtn_path)
{
	char *envp;

    envp =spublicGetEnvDir(WORKDIR);
    if ( envp == NULL )
            return -1;
    memset(rtn_path,0,LINE);

    strcpy(rtn_path,envp);
    strcat(rtn_path,TMPDIR);
    strcat(rtn_path,SPRI);
    strcat(rtn_path,file);

    return 0;
}


#define		SHELLDIR  "/shell"

/****
�����ļ���ȡ��$WORKDIR/tmp�µ��ļ�ȫ·��
*******/
int
spublicGetShellDir(const char *file, char *rtn_path)
{
        char *envp;

        envp = spublicGetEnvDir(WORKDIR);
        if ( envp == NULL )
                return -1;
        memset(rtn_path,0,LINE);

        strcpy(rtn_path,envp);
        strcat(rtn_path,SHELLDIR);
        strcat(rtn_path,SPRI);
        strcat(rtn_path,file);

        return 0;
}
/****** 
�����ļ���ȡ��$REDOLOGDIR/log�µ��ļ�ȫ·�� 
****/
int spublicGetRedoDir(char *file, char *rtn_path)
{
	char *envp;
	
	/* memset(envp,0,sizeof(envp)); */
        memset(rtn_path,0,100);

	envp=getenv(REDODIR);
	if (strlen(envp) == 0) 
	{
		userlog(" Get env err !!",__FILE__,__LINE__);
		return -1;
	}

        strcpy(rtn_path,envp);
        strcat(rtn_path,SPRI);
        strcat(rtn_path,file);

        return 0;
}

/******************************
name:     spublicEncrypt    
writer:   zhaohao           
date:     2001.04.26        
function: ���û�������м���
*****************************/

int spublicEncrypt( char *src, char *dest, int flag, int ende, int size )
{
        char    msg[21];
        int     i,j,len;
		int	tmp[21];	
        char    t[2];

	char ptsr[73]="PLMOKNIJBUHYGVTFCRDXESZAQWqazwsxedcrfvtgbyhnujmikolp1234567890-*&^$#@!;]";

	if (size > 20 )
		return(3);

	len=size;

        if(ende == 0) {
	/* ���� */
        for(i=0;i<=len;i++) {
         	if (src[i]==' ') src[i]='\0';
	}
	memset(msg, 0, sizeof(msg));

        msg[0]='\0';
        for(i=0;i<len;i++)
        {
          	t[0]=src[i];
          	t[1]='\0';
          	msg[i]=ptsr[((atoi(t)+i+1)*(len/2+1))];
        }

	if (flag == 0) {
	/* ֻ���� */
		strcpy(dest, msg);
		return(0);
	}
	else if (flag == 1) {
	/* �Ը�����Դ�����ܺ���������ܴ����жԱ� */
		if (strncmp(msg, dest, size) == 0) {
			return(0);
		}
		else {
			return(1);
		}
	}
	else
		return(2);
    }
    else if (ende == 1) {
	/* ���� */
	len = size;
        for(i=0;i<=len;i++) {
         	if (src[i]==' ') src[i]='\0';
	}

	memset(dest, 0, sizeof(dest));
	for(j=0; j<len; j++) {
		for (i=0; i<73; i++) {
			if (src[j] == ptsr[i]) {
				tmp[j]=i/(len/2+1)-1-j;
				break;
			}
		}
		sprintf(t,"%d",tmp[j]);
		if (j == 0) strcpy(dest,t);
		else strcat(dest,t);
	}
	return(0);
    }
    else
	return(2);
}

/*
void bosslog(codelevel, va_alist)
char *codelevel;
va_dcl
{
        va_list args;
        char    *fmt;
        FILE    *fp;
        char    *tempdir;
        char    tmpbuf[1024*10+1];

        memset(tmpbuf, 0, sizeof(tmpbuf));

        va_start(args);
        fmt=va_arg(args,char *);
        vsprintf(tmpbuf,fmt,args);

        tempdir=getenv("TEMPDIR");

        if (tempdir != NULL)
                chdir(tempdir);

        if (spublicLogGetFlag(codelevel) == TRUE)
                userlog("%s", tmpbuf);

        va_end(args);
}
*/

/***
 * name:     sEnDeDbPasswd  					     
 * flags: 0:����,1���� 
 * �����ܳ���64λ����
 ***/
void sEnDeDbPasswd(char *src, char *dest, int flags)
{
	char den_key[128+1];
	char tmp_src[128+1];
	char tmp_dest[128+1];
	int  i=0, length=0;
	
	memset(den_key, 0, sizeof(den_key));
	memset(tmp_src, 0, sizeof(tmp_src));
	memset(tmp_dest, 0, sizeof(tmp_dest));
	
	length = strlen(src);
	if (flags == ENCRYPT)
	{
	/*
		DES(flags, MASTERKEY, src, den_key, strlen(src));
		BcdToAsc_((unsigned char *)dest, (unsigned char *)den_key, 128);
	*/
		i = ((length / 8) * 16);
		if (length % 8 != 0)
		{
			i = i + 16;
		}
		dest[i] = '\0';
	}
	else if (flags == DECRYPT)
	{
	/*
		AscToBcd_ ((unsigned char *)den_key, (unsigned char *)src, 128);
		DES(flags, MASTERKEY, den_key, dest, strlen(src));
	*/
	}
}
