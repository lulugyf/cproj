#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <malloc.h>
#include <stdarg.h>
#include "Encrypt.h"

FILE	*F_Log;

	char	section_name[128];
	char	section_key[128];
	char	section_value[128];

void pubFun();

char *ltrim(char *in)
{
    int i;
    int iStrLen;

    iStrLen = strlen(in);

    for(i=0;i<iStrLen;i++)
    {
      if(in[i]==' ')
      {
         continue;
      }
      else
      {
         break;
      }
    }

    return in+i;
}

char *rtrim(char* in)
{
    int    i;

    for(i=strlen(in)-1;i>0;i--)
        if(in[i]==' ')
            continue;
        else
            break;

    in[i+1]=0;
    return in;
}
char* trim(char* in)
{
    return ltrim(rtrim(in));
}

int main(int argc,char **argv){

    memset(section_name,0,sizeof(section_name));
    memset(section_key,0,sizeof(section_key));
    memset(section_value,0,sizeof(section_value));

	if(argc!=3){
		printf("\nInput Error1!")	;
		printf("\nUsage: %s <SECTION> DBSERV/DBUSER/DBPASSWD\n",argv[0]);
		exit(0);
	}

	trim(argv[1]);
	trim(argv[2]);

	strcpy(section_name,argv[1]);
	strcpy(section_key,argv[2]);

	if(strcmp(section_name,"")==0){
		printf("\nInput Error2!");
		printf("\nUsage: %s <SECTION> DBSERV/DBUSER/DBPASSWD\n",argv[0]);
		exit(0);
	}

	if( (strcmp(section_key,"DBSERV")!=0) && (strcmp(section_key,"DBUSER")!=0) && (strcmp(section_key,"DBPASSWD")!=0)  && (strcmp(section_key,"HOSTIP")!=0) && (strcmp(section_key,"HOSTUSER")!=0)  && (strcmp(section_key,"HOSTPASSWD")!=0) ){
		printf("\nInput Error3!");
		printf("\nUsage: %s <SECTION> DBSERV/DBUSER/DBPASSWD\n",argv[0]);
		exit(0);
	}

	/*printf("-----.¶ÁÈ¡bossconfig¿ªÊ¼---section_name=[%s],section_key=[%s]-----\n",section_name,section_key);*/
	if((DcReadCfg(section_name,section_key,section_value)) <= 0){
		strcpy(section_value,"NULL");
		printf("%s\n",section_value);
		exit(0);
	}


	if( (strcmp(section_key,"DBUSER")==0) || (strcmp(section_key,"DBPASSWD")==0) || (strcmp(section_key,"HOSTUSER")==0)  || (strcmp(section_key,"HOSTPASSWD")==0) ){
		decrypt2(section_value);
	}

	printf("%s",section_value);
	return 0;
}
