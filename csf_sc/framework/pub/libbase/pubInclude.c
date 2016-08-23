#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>


#include <stdlib.h>
#include <string.h>

/**
 *去掉左右的空格、TAB和回车字段
 * @author lugz
 */
char* Trim(char *S)
{
	int I = 0, i = 0, L = 0;

	if (S == NULL)
	{
		return S;
	}

	L = strlen(S) - 1;
	I = 0;
	while ( (I <= L) && (S[I] <= ' ') && (S[I] > 0) )
	{
		I ++;
	}
	if (I > L)
	{
		S[0] = '\0';
	}
	else
	{
		while ( (S[L] <= ' ')  && (S[L] > 0 ) )
		{
			L --;
		}
		strncpy(S, S + I, L + 1);
		S[L + 1 - I] = '\0';
	}
	return S;
}
char * Ltrim(char *str)
{
	char *tmp_ptr;

	if(str[0]==0)
		return str;

	tmp_ptr=str;
	while(*tmp_ptr==' ' ||*tmp_ptr=='\t')
		tmp_ptr++;
	return strcpy(str,tmp_ptr);
}

char * Rtrim(char * str)
{
	int i;

	if(str[0]==0)
		return str;

	i=strlen(str)-1;

	while(str[i]==' ' || str[i]=='\t'){
		i--;
		if(i<0)
			break;
	}
	str[i+1]=0;
	return str;
}

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

long antol(const char* s, int bit)
{
	long resu=0;
	int i=0;
	for(i=0;i<bit&&s[i]!=0;++i){
		resu*=10;
		if(s[i]>'9'||s[i]<'0') continue;
		resu+=s[i]-'0';
	}
	return resu;
}

int IsDigital(char* InputChar)
{
    int i = 0;

    Trim(InputChar);
    for( i = 0; i < strlen(InputChar); i++ )
    {
        if ( (InputChar[i] < '0') || (InputChar[i] > '9') )
        {
            return -1;
        }
    }

    return 0;
}



/*取子串函数*/
int iStrGetPart(char *strWord,int nBegin,int nGip,char *strNewWord)
{
    int i=0,j=0,ret=0;

    if ( nGip < 1 )
    {
      
        return -1;
    }

    if ( nBegin < 0 || nBegin >= strlen(strWord) )
    {
      
        return -1;
    }

    strcpy(strNewWord,"");

    for(i=nBegin;i<(nBegin+nGip);i++)
    {
        if ( '\0'==strWord[i] )
        break;
        strNewWord[j]=strWord[i];
        j++;
    }

    strNewWord[j]='\0';
    return 0;
}

/**
 *     把字符串中的值按照指定的分隔符，分别存放到后面的动态变量中，这些变更的
 * 类型必须为“char*”。
 *     一般来说，源字符串中字段域的个数，应该与动态变量的个数相同。如果源字符
 * 串域的个数大于动态变量的个数，出错返回-1；如果源字符串域的个数小于动态变量
 * 的个数，后面的部分动态变更可能接收不到值，程序不认为出错，正常返回已得到值
 * 域的个数；如果源字符串域的个数等于动态变量，正常返回已得到值域的个数。
 * @author lugz
 * @inparam src	表示将要拆分的源串，源串中的字符串用指定的单个字符separateChar分
 *              隔。如下所示，用竖线分隔的串：
 *                  "field1|field2|field3| ... fieldn|"
 * @inparam separateChar
 * @outparam ...	变更的类型必须为“char*”，在函数中对这些变更的类型不做校检。
 * @return 返回一个整形值。如果源字符串域的个数大于动态变量的个数，出错返回-1；
 *         如果源字符串域的个数小于动态变量的个数，后面的部分动态变更可能接收
 *         不到值，程序不认为出错，正常返回已得到值域的个数；如果源字符串域的
 *         个数等于动态变量，正常返回已得到值域的个数。
 */
#ifndef __STRTOFIELDS__
#define __STRTOFIELDS__

int strToFields(const char* src, char separateChar, ...)
{
	int count = 0;
	const char *p, *q;
	char *field=NULL;
	va_list marker;

	q = p = src;
	va_start( marker, separateChar);
	do
	{
		if ( (q=strchr(p, (int)separateChar)) != (char*)NULL)
		{
			field = va_arg( marker, char*);
			if (field != NULL)
			{
				if ( q - p != 0 )
				    strncpy(field, p, q - p);
				field[q - p] = '\0';
			}
			else
			    return -1;
			p = q + 1;
			count ++;
		}
	}
	while(q != NULL); /*如果已到达最后一个域就结束*/
	va_end(marker);

	return count;
}

#endif



/**
 *去掉左右的空格、TAB和回车字段
 * @author lugz
 */
char* trim(char *S)
{
	int I = 0, i = 0, L = 0;

	if (S == NULL)
	{
		return S;
	}

	L = strlen(S) - 1;
	I = 0;
	while ( (I <= L) && (S[I] <= ' ') && (S[I] > 0) )
	{
		I ++;
	}
	if (I > L)
	{
		S[0] = '\0';
	}
	else
	{
		while ( (S[L] <= ' ')  && (S[L] > 0 ) )
		{
			L --;
		}
		strncpy(S, S + I, L + 1);
		S[L + 1 - I] = '\0';
	}
	return S;
}


/**
 *     把字符串中的值按照指定的分隔符，分别存放到后面的字符串数组变量中，这些变更的
 * 类型必须为“char*”。
 * @author lugz
 * @param src	表示将要拆分的源串，源串中的字符串用指定的单个字符separateChar分
 *              隔。如下所示，用竖线分隔的串：
 *                  "field1|field2|field3| ... fieldn|"
 * @param separateChar
 * @param dest		存放的数组。
 * @param colLen	数组第二维的长度
 * @return 返回一源串src中包含域的数量。
 */
int strToRows(const char *src,char separateChar,char **dest, int colLen)
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
	while ( (q=strchr(p, (int)separateChar)) != (char *)NULL)
	{
		strncpy( s + i * colLen, p,  q - p);
		s[i * colLen + q - p] = '\0';
		p = q + 1;
		i++;
	}
	return i;
}

/**
 * 生成一个指定长度的随机数
 *@inparam length 如果是32位环境,取值范围为:1到4位之间,
 *                如果是64位环境,取值范围为:1到18之间.
 *@outparam randNum 生成的随机数
 */
 
#ifndef __GETRAND__
#define __GETRAND__
int getRand(int length, long *randNum)
{
	int i,cpuLen;
	*randNum=0;

	cpuLen=sizeof(long);

	if (cpuLen == 4)
	{
		if (length < 1 || length > 4)
		{
			return -1;
		}
	}
	else/*8*/
	{
		if (length < 1 || length > 18)
		{
			return -2;
		}
	}

	srand(time(NULL));
	while(!(*randNum=rand() % 10));
	for (i = 0; i < length-1; i ++)
	{
		*randNum=*randNum * 10 + rand() % 10;
	}
	return 0;
}

#endif

/**
 *     把字符串中的值按照指定的分隔符，分别存放到后面的字符串指针数组变量中，这些变更的
 * 类型必须为“char*”。
 * @author lugz
 * @param src	表示将要拆分的源串，源串中的字符串用指定的单个字符separateChar分
 *              隔。如下所示，用竖线分隔的串：
 *                  "field1|field2|field3| ... fieldn|"
 * @param separateChar
 * @param ptrs		存放的数组。
 * @return 返回一源串src中包含域的数量，错误返回-1。
 */
 
#ifndef __STRTOPTRS__
#define __STRTOPTRS__

int StrToPtrs(char *src,const char *separateStr,char **ptrs)
{
	int i=0, separateStrLen=0;
	char *p;

	if(separateStr==NULL)
	{
		return -1;
	}

	separateStrLen = strlen(separateStr);
	while(src)
	{
		ptrs[i++]=src;
		p=strstr(src,separateStr);
		if(p != (char*)NULL)
		{
			*p=0x0;
			src=p+separateStrLen;
		}
		else
		{
			break;
		}
	}
	ptrs[i]=NULL;
	return i;
}

#endif


/*
 - split - divide a string into fields, like awk split()
 = int split(char *string, char *fields[], int nfields, char *sep);
 */
 
#ifndef __SPLIT__
#define __SPLIT__
/* number of fields, including overflow */

int split(char *string, char *fields[], int nfields, char *sep)
{
        register char *p = string;
        register char c;                        /* latest character */
        register char sepc = sep[0];
        register char sepc2;
        register int fn;
        register char **fp = fields;
        register char *sepp;
        register int trimtrail;

        /* white space */
        if (sepc == '\0') {
                while ((c = *p++) == ' ' || c == '\t')
                        continue;
                p--;
                trimtrail = 1;
                sep = " \t";    /* note, code below knows this is 2 long */
                sepc = ' ';
        } else
                trimtrail = 0;
        sepc2 = sep[1];         /* now we can safely pick this up */

        /* catch empties */
        if (*p == '\0')
                return(0);

        /* single separator */
        if (sepc2 == '\0') {
                fn = nfields;
                for (;;) {
                        *fp++ = p;
                        fn--;
                        if (fn == 0)
                                break;
                        while ((c = *p++) != sepc)
                                if (c == '\0')
                                        return(nfields - fn);
                        *(p-1) = '\0';
                }
                /* we have overflowed the fields vector -- just count them */
                fn = nfields;
                for (;;) {
                        while ((c = *p++) != sepc)
                                if (c == '\0')
                                        return(fn);
                        fn++;
                }
                /* not reached */
        }

        /* two separators */
        if (sep[2] == '\0') {
                fn = nfields;
                for (;;) {
                        *fp++ = p;
                        fn--;
                        while ((c = *p++) != sepc && c != sepc2)
                                if (c == '\0') {
                                        if (trimtrail && **(fp-1) == '\0')
                                                fn++;
                                        return(nfields - fn);
                                }
                        if (fn == 0)
                                break;
                        *(p-1) = '\0';
                        while ((c = *p++) == sepc || c == sepc2)
                                continue;
                        p--;
                }
                /* we have overflowed the fields vector -- just count them */
                fn = nfields;
                while (c != '\0') {
                        while ((c = *p++) == sepc || c == sepc2)
                                continue;
                        p--;
                        fn++;
                        while ((c = *p++) != '\0' && c != sepc && c != sepc2)
                                continue;
                }
                /* might have to trim trailing white space */
                if (trimtrail) {
                        p--;
                        while ((c = *--p) == sepc || c == sepc2)
                                continue;
                        p++;
                        if (*p != '\0') {
                                if (fn == nfields+1)
                                        *p = '\0';
                                fn--;
                        }
                }
                return(fn);
        }

        /* n separators */
        fn = 0;
        for (;;) {
                if (fn < nfields)
                        *fp++ = p;
                fn++;
                for (;;) {
                        c = *p++;
                        if (c == '\0')
                                return(fn);
                        sepp = sep;
                        while ((sepc = *sepp++) != '\0' && sepc != c)
                                continue;
                        if (sepc != '\0')       /* it was a separator */
                                break;
                }
                if (fn < nfields)
                        *(p-1) = '\0';
                for (;;) {
                        c = *p++;
                        sepp = sep;
                        while ((sepc = *sepp++) != '\0' && sepc != c)
                                continue;
                        if (sepc == '\0')       /* it wasn't a separator */
                                break;
                }
                p--;
        }

        /* not reached */
}

#endif

#if 0
void Trims(int i,char* src, ...)
{    	int j=0;	
	va_list marker;             	
	va_start(marker,src); 	
	
	char *field=src;            
	for(j=0;j<i;field=va_arg(marker,char *),j++)
	{
		Trim(field);
	}      
	va_end(marker);
}

#endif