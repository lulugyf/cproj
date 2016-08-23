#include "publicsrv.h"
#include <errno.h>


/* 字符串处理类 */
/*****************************************************************************
name:     Srtrim							      
writer:   zhaohao           						      
modi:     zhaohao           						      
date:     2001.11.1       						      
function: 去掉字符串右边的空格					      
****************************************************************************/
#ifndef __SRTRIM__
#define __SRTRIM__
char *Srtrim(char *src)
{
	int i=0;

	for(i=strlen(src); i>0; i--) {
		if (*(src+i-1) != ' ') {
			*(src+i) = '\0';
			break;
		}
	}
	if (i == 0) {
		*src = '\0';
	}

	return src;
}

#endif

/* added 20020429 */

/**
字符串去空格
**/

char *rtrim(char *src)
{
	int i=0;

	for(i=strlen(src); i>0; i--) {
		if (*(src+i-1) != ' ') {
			*(src+i) = '\0';
			break;
		}
	}
	if (i == 0) {
		*src = '\0';
	}

	return src;
}


/*****************************************************************************
 name:     Sltrim							      
 writer:   zhaohao           						      
 modi:     zhaohao           						      
 date:     2001.11.1       						     
 function: 去掉字符串左边的空格					     
*****************************************************************************/
#ifndef __SLTRIM__
#define __SLTRIM__
char *Sltrim(char *src)
{
	int i=0;

	for(i=0; i<strlen(src); i++) {
		if (*(src+i) != ' ')
			return src+i;
	}

	if (i == strlen(src)) {
		*src = '\0';
	}

	return src;
}

#endif

/* added 20020429 */

#ifndef __LTRIM__
#define __LTRIM__
char *ltrim(char *src)
{
	int i=0;

	for(i=0; i<strlen(src); i++) {
		if (*(src+i) != ' ')
			return src+i;
	}

	if (i == strlen(src)) {
		*src = '\0';
	}

	return src;
}


#endif

/*****************************************************************************
name:     Strim							      
writer:   zhaohao           						      
modi:     zhaohao           						      
date:     2001.11.1       						      
function: 去掉字符串两边的空格					     
****************************************************************************/

#ifndef __STRIM__
#define __STRIM__

char *Strim(char *src)
{
	int i=0;

	for(i=strlen(src); i>0; i--) {
		if (*(src+i-1) != ' ') {
			*(src+i) = '\0';
			break;
		}
	}
	if (i == 0) {
		*src = '\0';
		return src;
	}

	for(i=0; i<strlen(src); i++) {
		if (*(src+i) != ' ')
			return src+i;
	}

	if (i == strlen(src)) {
		*src = '\0';
		return src;
	}
	return src;
}


#endif

/******************************************************************************
name:     Ssubstr							      
writer:   zhaohao           					
modi:     zhaohao           					
date:     2001.11.1       						
function: 截取src从begin开始截取length位的字符串返回(字符串的第一位为1)    
****************************************************************************/
char *Ssubstr(char *src, int begin, int length, char *dest)
{
        int tmplen=0;

        Sinitn(dest);

        tmplen = strlen(src);

        if (begin < 1 || length < 1 || begin > tmplen)
                return NULL;

        if(begin-1+length >= tmplen)
                strcpy(dest, src+begin-1);
        else
                strncpy(dest, src+begin-1, length);

        return dest;
}

/******************************************************************************
name:     Slower							     
writer:   zhaohao           				
modi:     zhaohao           				
date:     2001.11.1       					
function: 将大写字母转换为小写字母，其他字符不变			    
***************************************************************************/
char *Slower(char *src)
{
	int i=0;

	for(i=0; i<strlen(src); i++) {
		if (*(src+i) >= 'A' && *(src+i) <= 'Z')
			*(src+i) += 32;
	}

	return src;
}

/******************************************************************************
 name:     Supper							     
 writer:   zhaohao           			
 modi:     zhaohao           			
 date:     2001.11.1       					
 function: 将小写字母转换为大写字母，其他字符不变			    
*****************************************************************************/
char *Supper(char *src)
{
	int i=0;

	for(i=0; i<strlen(src); i++) {
		if (*(src+i) >= 'a' && *(src+i) <= 'z')
			*(src+i) -= 32;
	}

	return src;
}


/*****************************************************************************
name:     get_billfee						      
writer:   hanying           						     
date:     2002.05.22      						      
function: 帐单调整费用解析						      
****************************************************************************/
float get_billfee(char *in_str) 
{
	char *p,*q,str[20],str1[255];
	int i=0,j=0;
	p=in_str;
	q=strchr(in_str,'|');

	if(q!=NULL){
		for(i=0;i<q-p;i++)str[i]=in_str[i];
		str[i++]='\0';
		for(j=0;i<strlen(in_str);j++)str1[j]=in_str[i++];
		str1[j]='\0';
		strcpy(in_str,str1);
	}
	else 
		str[0]='\0';

	return atof(str);
}

/*********************************
Name: getSysTime(int type)     
Author:   lixg@sitech.com.cn   
Date:2003.10.24                
Desc: 根据给定的类型取系统时间 

 type 格式
 100 Oct 31 2001
 101 10/31/2001
 102 2001/10/31
 103 10.31.2001
 104 2001.10.31
 105 10-31-2001
 106 2001-10-31
 107 10312001
 108 20011031
 109 10:05:16
 110 10:05:16AM
 111 10:05AM                     
 112 20010110100606          
********************************/
char *getSysTime(int type)
{
        time_t tm;
        char hh[2+1];
        char ehh[3+1];
        static char sysdatetime[17+1];

        tm = time(NULL);

        Sinitn(sysdatetime);
        Sinitn(hh);
        Sinitn(ehh);
        switch(type) {
                case 100:
                        strftime(sysdatetime, 12, "%m  %d %Y", localtime(&tm));
                        strncpy(hh, sysdatetime, 2);
                        Tntoe(hh, ehh);
                        *sysdatetime = *ehh;
                        *(sysdatetime+1) = *(ehh+1);
                        *(sysdatetime+2) = *(ehh+2);
                        break;
                case 101:
                        strftime(sysdatetime, 11, "%m/%d/%Y", localtime(&tm));
                        break;
                case 102:
                        strftime(sysdatetime, 11, "%Y/%m/%d", localtime(&tm));
                        break;
                case 103:
                        strftime(sysdatetime, 11, "%m.%d.%Y", localtime(&tm));
                        break;
                case 104:
                        strftime(sysdatetime, 11, "%Y.%m.%d", localtime(&tm));
                        break;
                case 105:
                        strftime(sysdatetime, 11, "%m-%d-%Y", localtime(&tm));
                        break;
                case 106:
                        strftime(sysdatetime, 11, "%Y-%m-%d", localtime(&tm));
                        break;
                case 107:
                        strftime(sysdatetime, 9, "%m%d%Y", localtime(&tm));
                        break;
                case 108:
                        strftime(sysdatetime, 9, "%Y%m%d", localtime(&tm));
                        break;
                case 109:
                        strftime(sysdatetime, 9, "%H:%M:%S", localtime(&tm));
                        break;
                case 110:
                        strftime(sysdatetime, 9, "%H:%M:%S", localtime(&tm));
                        break;
                case 111:
                        strftime(sysdatetime, 6, "%H:%M", localtime(&tm));
                        break;
                case 112:
                        strftime(sysdatetime, 15, "%Y%m%d02/12/2004M%S", localtime(&tm));
                        break;
                default:
                        return NULL;
        }

        Sinitn(hh);
        if (type == 110 || type == 111) {
                strncpy(hh, sysdatetime, 2);
                if (atoi(hh) > 12 && atoi(hh) < 22) {
                        sprintf(hh, "0%d", atoi(hh) - 12);
                        strcat(sysdatetime, "PM");
                }
                else if (atoi(hh) >= 22) {
                        sprintf(hh, "%d", atoi(hh) - 12);
                        strcat(sysdatetime, "PM");
                }
                else
                        strcat(sysdatetime, "AM");

                *sysdatetime = *hh;
                *(sysdatetime+1) = *(hh+1);
        }

        return sysdatetime;
}

/*********************************
Name: itoaAH(int type)     
Date:2006.09.05                
Desc: i -> a 

Input parameter:
n           the i
BufEndAdr   end address of the char buffer.
base        base of char array returned.

**********************************/

#ifndef __ITOAAH__
#define __ITOAAH__
unsigned char * itoaAH(long n, unsigned char *BufEndAdr, int base)
{
 register unsigned char *p;
 char minus;
 p=BufEndAdr;
 *p = 0x00;
 if (n < 0) {
  minus = 1;
  n = -n;
 }
 else
  minus = 0;
 if (n == 0)
  *--p = '0';
 else
  while (n > 0) {
   *--p = "0123456789ABCDEF"[n % base];
   n /= base;
  }
 if (minus)
  *--p = '-';
 return p;
}

#endif


#ifndef __SUBSTR__
#define __SUBSTR__

char *substr(char *source,int begin,int num){
    int i;
    char dest[1024]="\0";
    if(begin<1 || num<1) return NULL;
    for(i=begin-1;i<begin+num-1;i++){
        dest[i-begin+1]=source[i];
    }
    dest[i-begin+1]='\0';
    return dest;
}

#endif

char* StrChrWordFind(const char * string, int ch)
{
        while (*string && *string != (char)ch)
        {
                if ( (*string < 0) || (*string > 127))
                {
                        /*JGR;8vK+WV=Z::WV#,Lx9}K+WV=Z::WV5DOBR;8vWV7{#!*/
                        string += 2;
                }
                else
                {
                        string ++;
                }
        }

        if (*string == (char)ch)
        {
                return((char *)string);
        }
        return(NULL);
}

int StrToRows(char *src,char separateChar,char **dest, int colLen)
{
        const char *p, *q;
        int i;
        char *s;

        if (src == NULL)
        {
                return 0;
        }

        s=(char*)dest;
        q = p = src;
        i=0;
        while ( (q=StrChrWordFind(p, (int)separateChar)) != (char *)NULL)
        {
                strncpy( s + i * colLen, p,  q - p);
                s[i * colLen + q - p] = '\0';
                p = q + 1;
                i++;
        }
        return i;
}
