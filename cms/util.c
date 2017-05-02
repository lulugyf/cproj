#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include "cms.h"

#include <lua.h>			      /*Lua语言解析器*/
#include <lualib.h>			    /*Lua标准库*/
#include <lauxlib.h>			  /*Lua辅助工具*/

extern FILE *logfp;

int timeout;

char *rlspace(char *s)
{
	int len;

	if(s==NULL)
		return NULL;

	for(len=strlen(s)-1;len>=0;len--)
	{
		if(s[len]==' ' || s[len]=='\t' || s[len]==0x0a || s[len]==0x0d)
			s[len]=0x0;
		else
			break;
	}

	for(;;)
	{
		if(*s==' ' || *s=='\t' || *s==0x0a || *s==0x0d)
			s++;
		else
			return s;
	}
}

int get_length(char *s,int len)
{
	int ret,i;

	for(i=0,ret=0;i<len;i++)
	{
		if(s[i]>='0' && s[i]<='9')
			ret=ret*10+s[i]-'0';
		else
			break;
	}

	return ret;
}

void AddStr_new(char *str)
{
	
	char strsrc[10000];
	char strtemp[10000];
	char strtemp1[10000];
	char *ptemp = NULL;
	char *p     = NULL;
	
	memset(strsrc,0X00,sizeof(strsrc));
	memset(strtemp,0X00,sizeof(strtemp));
	memset(strtemp1,0X00,sizeof(strtemp1));
	
	sprintf(strsrc,"%s",str);
	ptemp = strsrc;
	while( (p = strstr(ptemp,"|")) != NULL)
	{
		memset(strtemp,0X00,sizeof(strtemp));
		memset(strtemp1,0X00,sizeof(strtemp1));
		snprintf(strtemp,p-ptemp+1,"%s",ptemp);
		sprintf(strtemp1,"%s",p+1);
		sprintf(ptemp,"%s#2@3##%s",strtemp,strtemp1);
		ptemp = p+6;
	}
	sprintf(str,"%s",strsrc);
}



void get_valstr(char *d,char *s,char *p1,char *p2,char *p3,char *p4,char *p5,char *p6)
{
	int beg,len;
	char *p;

	while(*s)
	{
		if(*s=='$')
		{
			if(!isdigit(s[1]) || !isdigit(s[2]) || !isdigit(s[3]) || !isdigit(s[4]) || !isdigit(s[5]))
				break;

			switch(s[1])
			{
			case '1':
				p=p1;
				break;
			case '2':
				p=p2;
				break;
			case '3':
				p=p3;
				break;
			case '4':
				p=p4;
				break;
			case '5':
				p=p5;
				break;
			case '6':
				p=p6;
				break;
			default:
				p=NULL;
				break;
			}

			if(p==NULL)
				break;

			beg=(s[2]-'0')*10+(s[3]-'0');
			len=(s[4]-'0')*10+(s[5]-'0');
			if(len==0)
				len=strlen(p+beg);

			memcpy(d,p+beg,len);

			s+=6;
			d+=len;
		}
		else
		{
			*d=*s;
			s++;
			d++;
		}
	}

	return;
}

char *cmsget_value(char *buf, char *key, char *value, int maxlen)
{
    char *ptr0, *ptr1, *ptr2, *ptre;
    int len, slen;

    value[0] = 0;
    ptre = (char *)(buf + strlen(buf));
    ptr0 = (char *)buf;
    while( (ptr1 = (char *)strstr(ptr0, key)) >= ptr0){
        ptr0 = ptr1 + strlen(key);
        if(ptr0 >= ptre)
            break;
        if(ptr0[0] != '=')
            continue;
        ptr0 ++;
        while(*ptr0 == ' ' || *ptr0 =='\t') ptr0 ++;
        if(*ptr0 == 0){
            value[0] = 0;
            return value;
        }
        if(*ptr0 == '\"'){
            ptr0 ++;
            ptr1 = strchr(ptr0, '\"');
            if(ptr1 == NULL){
                strncpy(value, ptr0, maxlen);
                return 0;
            }
            value[ptr1 - ptr0] = 0;
            memcpy(value, ptr0, ptr1-ptr0);
            return value;
        }
        ptr1 = strchr(ptr0, '|');
        if(ptr1 == NULL){
            strncpy(value, ptr0, maxlen);
            return value;
        }

        if(maxlen > ptr1-ptr0)
            maxlen = ptr1-ptr0;
        value[maxlen] = 0;
        memcpy(value, ptr0, maxlen);
        return value;
    }
    return 0;
}

int comp_int(int val1,int val2)
{
	if(val1==val2 || val1==9999)
		return 1;
	else
		return 0;
}

void cal_time(char *s,struct timeval t1,struct timeval t2)
{
	if(t2.tv_usec<t1.tv_usec)
		fprintf(logfp,"CAL_TIME %s: %ld.%06ld  [%ld.%06ld - %ld.%06ld]\n",s,t2.tv_sec-t1.tv_sec-1,t2.tv_usec-t1.tv_usec+1000000,t1.tv_sec,t1.tv_usec,t2.tv_sec,t2.tv_usec);
	else
		fprintf(logfp,"CAL_TIME %s: %ld.%06ld  [%ld.%06ld - %ld.%06ld]\n",s,t2.tv_sec-t1.tv_sec,t2.tv_usec-t1.tv_usec,t1.tv_sec,t1.tv_usec,t2.tv_sec,t2.tv_usec);
	fflush(logfp);

	return;
}

void *copy_address(void *address)
{
        return address;
}

void free_address(void *address)
{
        return;
}

int pro_lua(char *inmmlbuf,char *incode,char *out)
{
	const char *result;
	char code[2048];
	char mmlbuf[4127];
	int flag;
	
	memset(mmlbuf,0,sizeof(mmlbuf));
	memset(code,0,sizeof(code));
	
	strcpy(mmlbuf,inmmlbuf);
	strcpy(code,incode);
	
	
	lua_State *s = luaL_newstate();  /*建立一个虚拟机*/
	
	luaopen_base(s); 
	luaL_openlibs(s);								/*打开Lua附加库*/
	
	
	luaL_dostring(s, code);		/*执行字符串中的源代码*/
	lua_getglobal(s, "show");		/*将Lua全局变量压栈*/
	lua_pushstring(s, mmlbuf);	/*属性串入栈*/
	
	flag = 0;
	
	lua_pcall(s, 1, 1, 0);				/*保护模式调用Lua函数*/
	
	
	result = lua_tostring(s, -1);		/*取得第一个返回值*/
	
	strcpy(out,result);
	lua_pop(s, 1);
	lua_close(s);

/*	//free(result);*/
	return flag;
}

/*把需要多值的参数截取出来，保留原来的参数*/
char *getOther_char(char *buf, char *key, char *value)
{
	char sel_key[100];
	char tem[1024];
	char *p,*p1;
	int stat,end; 
	if(buf == NULL)
		 return;
	
	memset(sel_key,0x00,sizeof(sel_key));
	memset(tem,0x00,sizeof(tem));
	sprintf(sel_key,"%s=",key);	
	
	p = strstr(buf,sel_key);
	if(p == NULL)
		 return;
	stat = strlen(buf)-strlen(p);
	strncpy(tem,buf,(strlen(buf)-strlen(p)));
	p1 = strstr(p,"|");
	if(p1 == NULL)
		 return;
	strcat(tem,p1+1);
	strcpy(value,tem);
	return;
}

char *getMul_str(char *string,char *ch,char *key,char *value)
{
	char sel_key[100];
	char *p,*p1;
	int stat,end; 
	if(string == NULL)
		 return;
	
	memset(sel_key,0x00,sizeof(sel_key));
	sprintf(sel_key,"%s=",key);	
	p = strstr(string,sel_key);
	if(p == NULL)
		 return;
	p = p+strlen(sel_key);
	stat = strlen(p);
	p1 = strstr(p,ch);
	if(p1 == NULL)
		 return;
	end = strlen(p1);
	strncpy(value,p,stat-end);
	return;
}


