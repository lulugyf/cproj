/**
 *     测试utype服务
 * @author	lugz
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fml32.h>             
#include <atmi.h>      
#include "general32.flds.h"
#include "ferror32.h"
#include "utype.h"

void PrintUtype(utype *pu, int iLevel);
#define ERR_HANDLER {goto ERR_LABEL;}

typedef struct tagParam
{
	int iLevel;
	int iType;
	char sValue[1024];
	char name[U_MAXNAMELEN+1];
}TParam;

#define MAX_LEVEL 50


char* LTrim(char *S)
{
	int I = 0, i = 0, L = 0;

	if (S == NULL)
	{
		return NULL;
	}
		
	L = (int)(strlen(S) - 1);
	I = 0;
	while ( (I <= L) && (S[I] <= ' ') && (S[I] > 0) )
	{
		I ++;
	}
	if (I > L)
	{
		S[0] = '\0';
	}
	else if (I > 0)
	{
		strcpy(S, S + I);
	}
	return S;
}

/*
-NAME	int	3
-NAME	long	4
-NAME	utype
--int 4
--int 5
--utype
---int 3
---long 4
---string abcd
--long 4
-double 4.4
*/
int ReadFile(char *psUtypeFileName, utype**uOutParam)
{
	FILE *fp;
	char sLine[1023+1], *psLine, *psComment;
	int i, iLen;
	long iRet=0;
	TParam tCurParam;
	utype *puTmp[MAX_LEVEL];
	
	if ((fp = fopen(psUtypeFileName, "r")) == NULL)
	{
		*uOutParam = NULL;
		return 1;
	}
	memset(&tCurParam, 0, sizeof(tCurParam));
	*uOutParam = uInit(0);

	puTmp[0] = *uOutParam;
	
	memset(sLine, 0, sizeof(sLine));
	while(fgets(sLine,1023,fp))
	{
		LTrim(sLine);
		if ((sLine[0] == '#') || (sLine[0] == '\0'))
		{
			continue;
		}
		psLine = sLine;
		memset(&tCurParam, 0, sizeof(tCurParam));
		/*得到等级*/
		tCurParam.iLevel=0;
		while(psLine[0] != '\0')
		{
			if (psLine[0] == '-')
			{
				tCurParam.iLevel ++;
			}
			else
			{
				break;
			}
			psLine ++;
		}

		/*得到名字*/
		psComment = strchr(psLine, '\t');
		strncpy(tCurParam.name, psLine, psComment - psLine);
		tCurParam.name[psComment - psLine] = '\0';

		/*跳过一个空格*/
		psLine = psComment + 1;
		
		/*得到类型*/
		if (strncmp(psLine, "char", 4) == 0)
		{
			psLine = psLine + 4;
			tCurParam.iType = U_CHAR;
		}
		else if (strncmp(psLine, "int", 3) == 0)
		{
			psLine = psLine + 3;
			tCurParam.iType = U_INT;
		}
		else if (strncmp(psLine, "long", 4) == 0)
		{
			psLine = psLine + 4;
			tCurParam.iType = U_LONG;
		}
		else if (strncmp(psLine, "double", 6) == 0)
		{
			psLine = psLine + 6;
			tCurParam.iType = U_DOUBLE;
		}
		else if (strncmp(psLine, "string", 6) == 0)
		{
			psLine = psLine + 6;
			tCurParam.iType = U_STRING;
		}
		else if (strncmp(psLine, "utype", 5) == 0)
		{
			psLine = psLine + 5;
			tCurParam.iType = U_ARRAY;
		}
		else if (strncmp(psLine, "empty", 5) == 0)
		{
			psLine = psLine + 5;
			tCurParam.iType = U_EMPTY;
		}
		else
		{
			return 1;
		}

		/*跳过一个空格*/
		psLine = psLine + 1;

		psComment = strchr(psLine, '#');
		if (psComment == NULL)
		{
			strcpy(tCurParam.sValue, psLine);
			iLen = strlen(tCurParam.sValue);
			for(i = iLen - 1; i >=0; i --)
			{
				if (tCurParam.sValue[i] == '\n')
				{
					tCurParam.sValue[i] = '\0';
					break;
				}
			}
		}
		else
		{
			strncpy(tCurParam.sValue, psLine, psComment - psLine);
			tCurParam.sValue[psComment - psLine] = '\0';
		}
		switch(tCurParam.iType)
		{
			case U_CHAR:
			{
				utSetChar(puTmp[tCurParam.iLevel-1], puTmp[tCurParam.iLevel-1]->cnt,  (char)(atoi(tCurParam.sValue)), tCurParam.name);
				break;
			}
			case U_INT:
			{
				utSetInt(puTmp[tCurParam.iLevel-1], puTmp[tCurParam.iLevel-1]->cnt,  atoi(tCurParam.sValue), tCurParam.name);
				break;
			}
			case U_LONG:
			{
				utSetLong(puTmp[tCurParam.iLevel-1], puTmp[tCurParam.iLevel-1]->cnt,  atol(tCurParam.sValue), tCurParam.name);
				break;
			}
			case U_DOUBLE:
			{
				utSetDouble(puTmp[tCurParam.iLevel-1], puTmp[tCurParam.iLevel-1]->cnt,  atof(tCurParam.sValue), tCurParam.name);
				break;
			}
			case U_STRING:
			{

				utSetStr(puTmp[tCurParam.iLevel-1], puTmp[tCurParam.iLevel-1]->cnt,  tCurParam.sValue, tCurParam.name);
				break;
			}
			case U_EMPTY:
			{
				utSetEmpty(puTmp[tCurParam.iLevel-1], puTmp[tCurParam.iLevel-1]->cnt,  tCurParam.name);
				break;
			}
			case U_ARRAY:
			case U_STRUCT:
			{
				UT_Init(puTmp[tCurParam.iLevel], 1, iRet, ERR_HANDLER, UT_ARG_FLAG_NULL);
				utSetStruct(puTmp[tCurParam.iLevel-1], puTmp[tCurParam.iLevel-1]->cnt,  puTmp[tCurParam.iLevel], tCurParam.name);
				break;
			}
			default:
			{
				break;
			}
		}
	}
ERR_LABEL:
	if (iRet != 0)
	{
		if (*uOutParam)
		{
			uFree(*uOutParam);
			*uOutParam = NULL;
		}
	}
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[])
{
	char *sendbuf=NULL, *rcvbuf=NULL;
	int ret,iSendLen;
	long reqlen=10240;
	char sServiceName[32],sUtypeFileName[PATH_MAX+1],buffer[1024];

	utype * sutype=NULL;
	utype * rutype=NULL;
	
	if(argc != 3)
	{
		(void) fprintf(stderr, "Usage: clutName <service name> <utype file>\n");
		return 1;
	}
	memset(sServiceName, 0, sizeof(sServiceName));
	memset(sUtypeFileName, 0, sizeof(sUtypeFileName));
	strcpy(sServiceName, argv[1]);
	strcpy(sUtypeFileName, argv[2]);

	/* Attach to System/T as a Client Process */
	if (tpinit((TPINIT *) NULL) == -1) {
		(void) fprintf(stderr, "Tpinit failed\n");
		exit(1);
	}
	ReadFile(sUtypeFileName, &sutype);
	iSendLen=uPackLen(sutype);
	
	if((sendbuf = (char *) tpalloc("CARRAY", NULL, iSendLen)) == NULL)
	{
		(void) fprintf(stderr,"Error allocating send buffer[%d]\n",iSendLen);
		tpterm();
		exit(1);
	}

	if((rcvbuf = (char *) tpalloc("CARRAY", NULL, reqlen)) == NULL)
	{
		(void) fprintf(stderr,"Error allocating receive buffer\n");
		tpfree((char *)sendbuf);
		tpterm();
		exit(1);
	}
	
	uPack(sutype,sendbuf);

	ret = tpcall(sServiceName, (char *)sendbuf, iSendLen, (char **)&rcvbuf, &reqlen, (long)0);
	if(ret == -1)
	{
		(void) fprintf(stderr, "Can't send request to service TOUPPER\n");
		(void) fprintf(stderr, "Tperrno = %d\n", tperrno);
		tpfree((char *)sendbuf);
		tpfree((char *)rcvbuf);
		tpterm();
		exit(1);
	}
	printf("++++ tpcall succ !!! ++++\n");

	uUnpack(rcvbuf,&rutype);

	PrintUtype(rutype,0);
	uFree(sutype);
	uFree(rutype);

	tpfree((char *)sendbuf);
	tpfree((char *)rcvbuf);
	tpterm();

	return(0);
}
