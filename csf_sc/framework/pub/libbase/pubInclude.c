#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>


#include <stdlib.h>
#include <string.h>

/**
 *ȥ�����ҵĿո�TAB�ͻس��ֶ�
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



/*ȡ�Ӵ�����*/
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
 *     ���ַ����е�ֵ����ָ���ķָ������ֱ��ŵ�����Ķ�̬�����У���Щ�����
 * ���ͱ���Ϊ��char*����
 *     һ����˵��Դ�ַ������ֶ���ĸ�����Ӧ���붯̬�����ĸ�����ͬ�����Դ�ַ�
 * ����ĸ������ڶ�̬�����ĸ�����������-1�����Դ�ַ�����ĸ���С�ڶ�̬����
 * �ĸ���������Ĳ��ֶ�̬������ܽ��ղ���ֵ��������Ϊ�������������ѵõ�ֵ
 * ��ĸ��������Դ�ַ�����ĸ������ڶ�̬���������������ѵõ�ֵ��ĸ�����
 * @author lugz
 * @inparam src	��ʾ��Ҫ��ֵ�Դ����Դ���е��ַ�����ָ���ĵ����ַ�separateChar��
 *              ����������ʾ�������߷ָ��Ĵ���
 *                  "field1|field2|field3| ... fieldn|"
 * @inparam separateChar
 * @outparam ...	��������ͱ���Ϊ��char*�����ں����ж���Щ��������Ͳ���У�졣
 * @return ����һ������ֵ�����Դ�ַ�����ĸ������ڶ�̬�����ĸ�����������-1��
 *         ���Դ�ַ�����ĸ���С�ڶ�̬�����ĸ���������Ĳ��ֶ�̬������ܽ���
 *         ����ֵ��������Ϊ�������������ѵõ�ֵ��ĸ��������Դ�ַ������
 *         �������ڶ�̬���������������ѵõ�ֵ��ĸ�����
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
	while(q != NULL); /*����ѵ������һ����ͽ���*/
	va_end(marker);

	return count;
}

#endif



/**
 *ȥ�����ҵĿո�TAB�ͻس��ֶ�
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
 *     ���ַ����е�ֵ����ָ���ķָ������ֱ��ŵ�������ַ�����������У���Щ�����
 * ���ͱ���Ϊ��char*����
 * @author lugz
 * @param src	��ʾ��Ҫ��ֵ�Դ����Դ���е��ַ�����ָ���ĵ����ַ�separateChar��
 *              ����������ʾ�������߷ָ��Ĵ���
 *                  "field1|field2|field3| ... fieldn|"
 * @param separateChar
 * @param dest		��ŵ����顣
 * @param colLen	����ڶ�ά�ĳ���
 * @return ����һԴ��src�а������������
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
 * ����һ��ָ�����ȵ������
 *@inparam length �����32λ����,ȡֵ��ΧΪ:1��4λ֮��,
 *                �����64λ����,ȡֵ��ΧΪ:1��18֮��.
 *@outparam randNum ���ɵ������
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
 *     ���ַ����е�ֵ����ָ���ķָ������ֱ��ŵ�������ַ���ָ����������У���Щ�����
 * ���ͱ���Ϊ��char*����
 * @author lugz
 * @param src	��ʾ��Ҫ��ֵ�Դ����Դ���е��ַ�����ָ���ĵ����ַ�separateChar��
 *              ����������ʾ�������߷ָ��Ĵ���
 *                  "field1|field2|field3| ... fieldn|"
 * @param separateChar
 * @param ptrs		��ŵ����顣
 * @return ����һԴ��src�а���������������󷵻�-1��
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