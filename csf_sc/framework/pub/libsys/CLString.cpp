/**
*     内存分配
*/

#include "libsys.h"

namespace NSPrime
{
	/**
	 * <summary>
	 *   中文复制函数，末尾的半个汉字不复制。
	 * </summary>
	 * <param name="psDest"></param>
	 * <param name="psSource"></param>
	 * <returns>
	 *   复制的字符数量
	 * </returns>
	 */
	int CLString::StrCpyChina (unsigned char * psDest,const unsigned char * psSource, int iCount)
	{
		int iCopyNum = 0;
		
		while (iCopyNum < iCount)
		{
			*psDest = *psSource;
			iCopyNum ++;
			if ((*psSource) > 127)
			{
				//是汉字
				if (iCopyNum < iCount)
				{
					psDest ++;
					psSource ++;
					*psDest = *psSource;
					iCopyNum ++;
				}
				else
				{
					iCopyNum --;
					*psDest = '\0';
					return iCopyNum;
				}
			}
			psDest ++;
			psSource ++;
			if ((*psSource) == '\0')
			{
				break;
			}
		}
		return iCopyNum;
	}

	/**
	 *     字符串的按字查找函数，如果找到返回所查字符串的开始位置，否则返回NULL。
	 */
	char* CLString::StrWordFind(const char * str1, const char *str2)
	{
		char *cp = (char *) str1;
		char *s1, *s2;
	
		if (str2 == NULL)
		{
			return NULL;
		}
	
		if ( (*str2) == NULL)
		{
			return((char *)str1);
		}
	
		while (*cp)
		{
			s1 = cp;
			s2 = (char *) str2;
	
			while ( (*s1) && (*s2) && ( (*s1) == (*s2) ) )
			{
				s1++, s2++;
			}
	
			if ( ((*s2) == NULL))
			{
				return(cp);
			}
	
			if ( (*cp < 0) || (*cp > 127))
			{
				/*是一个双字节汉字，跳过双字节汉字的下一个字符！*/
				cp+=2;
			}
			else
			{
				cp++;
			}
		}
	
		return(NULL);
	}
	
	/**
	 *     字符串的按字查找函数，如果找到返回所查字符串的开始位置，否则返回NULL。
	 */
	char* CLString::StrChrWordFind(const char * psStr, int ch)
	{
		while (*psStr && *psStr != (char)ch)
		{
			if ( (psStr[0] < 0) || (psStr[0] > 127))
			{
				/*是一个双字节汉字，跳过双字节汉字的下一个字符！*/
				psStr += 2;
			}
			else
			{
				psStr ++;
			}
		}

		if (*psStr == (char)ch)
		{
			return((char *)psStr);
		}
		return(NULL);
	}

	/**
	 *     把字符串中的值按照指定的分隔符，分别存放到后面的动态变量中，这些变更的
	 * 类型必须为“char*”。
	 *     一般来说，源字符串中字段域的个数，应该与动态变量的个数相同。如果源字符
	 * 串域的个数大于动态变量的个数，出错返回-1；如果源字符串域的个数小于动态变量
	 * 的个数，后面的部分动态变更可能接收不到值，程序不认为出错，正常返回已得到值
	 * 域的个数；如果源字符串域的个数等于动态变量，正常返回已得到值域的个数。
	 * @author lugz
	 * @param src	表示将要拆分的源串，源串中的字符串用指定的单个字符separateChar分
	 *              隔。如下所示，用竖线分隔的串：
	 *                  "field1|field2|field3| ... fieldn|"
	 * @param separateChar
	 * @param ...	变更的类型必须为“char*”，在函数中对这些变更的类型不做校检。
	 * @return 返回一个整形值。如果源字符串域的个数大于动态变量的个数，出错返回-1；
	 *         如果源字符串域的个数小于动态变量的个数，后面的部分动态变更可能接收
	 *         不到值，程序不认为出错，正常返回已得到值域的个数；如果源字符串域的
	 *         个数等于动态变量，正常返回已得到值域的个数。
	 */
	int CLString::StrToFields(const char* src, char separateChar, ...)
	{
		int count = 0;
		const char *p, *q;
		char *field=NULL;	
		va_list marker;
		
		q = p = src;
		va_start( marker, separateChar);
		do
		{
			if ( (q=StrChrWordFind(p, (int)separateChar)) != (char*)NULL)
	
			{
				field = va_arg( marker, char*);
				if (field != NULL)
				{
					if ( q - p != 0 )
					{
						strncpy(field, p, q - p);
					}
					field[q - p] = '\0';
				}
				else
				{
					return -1;
				}
				
				p = q + 1;
				count ++;
			}
		}
		while(q != NULL); /*如果已到达最后一个域就结束*/
		va_end(marker);
	
		return count;
	}

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
	int CLString::StrToPtrs(char *src,const char *separateStr,char **ptrs)
	{
		int i=0;
		size_t separateStrLen=0;
		char *p;
		
		if(separateStr==NULL)
		{
			return -1;
		}
	
		separateStrLen = strlen(separateStr);
		while(src)
		{
			ptrs[i++]=src;
			p=StrWordFind(src,separateStr);
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
	 * @param iFlags	0表示，不做循环跳过separateChar操作，1跳过连续的separateChar符号。
	 * @return 返回一源串src中包含域的数量。
	 */
	int CLString::StrToRows(const char *src,char separateChar,char **dest, int colLen, int iFlags, int iArraySize)
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
		i = 0;
		while ( (q=StrChrWordFind(p, (int)separateChar)) != (char *)NULL)
		{
			if ((iArraySize != -1) && (i >= iArraySize))
			{
				break;
			}
			
			if (q != p)
			{
				strncpy( s + i * colLen, p,  q - p);
			}
			s[i * colLen + q - p] = '\0';
			//跳过多个指定的操作符。
			if (iFlags)
			{
				while (*q == (int)separateChar)
				{
					q ++;
				}
				p = q;
			}
			else
			{
				p = q + 1;
			}
			i++;
		}

		if ((iArraySize != -1) && (i >= iArraySize))
		{
			return i;
		}

		if (*p != '\0')
		{
			strcpy( s + i * colLen, p);
			s[i * colLen + strlen(p)] = '\0';
		}
		return i;
	}

	char* CLString::Trim(char *S)
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

	char* CLString::LTrim(char *S)
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


	char* CLString::RTrim(char *S)
	{
		int I = 0, i = 0, L = 0;
	
		if (S == NULL)
		{
			return NULL;
		}
			
		L = (int)(strlen(S) - 1);
		I = 0;
		while ( (S[L] <= ' ')  && (S[L] > 0 ) )
		{
			L --;
		}
		S[L + 1] = '\0';
		return S;
	}

	/**
	 *     字符串查找函数，忽略大小字，如果找到返回所查字符串的开始位置，否则返回NULL。
	 */
	char * CLString::StrFind (const char * str1, const char * str2)
	{
		char *cp = (char *) str1;
		char *s1, *s2;
		int caseMinus= 'a' - 'A';

		if ( !(*str2) )
		{
			return((char *)str1);
		}

		while (*cp)
		{
			s1 = cp;
			s2 = (char *) str2;

			while ( (*s1) && (*s2) && ( ((*s1) == (*s2)) || ((*s1) == ((*s2) +caseMinus)) || (((*s1)  + caseMinus) == (*s2)) ) )
			{
				s1++, s2++;
			}

			if ( !(*s2) )
			{
				return(cp);
			}

			cp++;
		}

		return(NULL);
	}

	int CLString::AsciiStrICmp (const char * dst,const char * src)
	{
		int f, l;

		do
		{
			if ( ((f = (unsigned char)(*(dst++))) >= 'A') && (f <= 'Z') )
				f -= 'A' - 'a';
			if ( ((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z') )
				l -= 'A' - 'a';
		}
		while ( f && (f == l) );

		return(f - l);
	}

	int CLString::AsciiStrNICmp (const char * first,const char * last,size_t count)
	{
		if(count)
		{
			int f=0;
			int l=0;

			do
			{

				if ( ((f = (unsigned char)(*(first++))) >= 'A') && (f <= 'Z') )
					f -= 'A' - 'a';

				if ( ((l = (unsigned char)(*(last++))) >= 'A') && (l <= 'Z') )
					l -= 'A' - 'a';
			}
			while ( --count && f && (f == l) );

			return ( f - l );
		}
		else
		{
			return 0;
		}
	}

	bool CLString::IsPrefix(register const char *s, register const char *t)
	{
		while (*t)
			if (*s++ != *t++) return false;
		return true;
	}

	char *CLString::StrXMov(char *dst,const char *src, ...)
	{
		va_list pvar;

		va_start(pvar,src);
		while (src != NULL) {
			while ((*dst++ = *src++)) ;
			dst--;
			src = va_arg(pvar, char *);
		}
		va_end(pvar);
		*dst = 0;			/* there might have been no sources! */
		return dst;
	}

	char *CLString::StrXNMov(char *dst,uint len, const char *src, ...)
	{
		va_list pvar;
		char *end_of_dst=dst+len;

		va_start(pvar,src);
		while (src != NULLS)
		{
			do
			{
				if (dst == end_of_dst)
					goto end;
			}
			while ((*dst++ = *src++));
			dst--;
			src = va_arg(pvar, char *);
		}
		*dst=0;
end:
		va_end(pvar);
		return dst;
	}

	/*
    StrFill(dest, len, fill) makes a string of fill-characters. The result
    string is of length == len. The des+len character is allways set to NULL.
    StrFill() returns pointer to dest+len;
	*/
	char* CLString::StrFill(char* s,uint len,char fill)
	{
		while (len--) *s++ = fill;
		*(s) = '\0';
		return(s);
	} /* StrFill */

	/*
	strip_sp(my_string str)
	Strips end-space from string and returns new length.
	*/
	size_t CLString::StripSpace(register char* str)
	{
		reg2 char* found;
		reg3 char* start;

		start=found=str;

		while (*str)
		{
			if (*str != ' ')
			{
				while (*++str && *str != ' ') {};
				if (!*str)
					return (size_t) (str-start);	/* Return stringlength */
			}
			found=str;
			while (*++str == ' ') {};
		}
		*found= '\0';				/* Stripp at first space */
		return (size_t) (found-start);
	} /* strip_sp */

	/*
	bmove512(dst, src, len) moves exactly "len" bytes from the source "src"
	to the destination "dst".  "src" and "dst" must be alligned on long
	boundory and len must be a mutliple of 512 byte. If len is not a
	multiple of 512 byte len/512*512+1 bytes is copyed.
	bmove512 is moustly used to copy IO_BLOCKS.  bmove512 should be the
	fastest way to move a mutiple of 512 byte.
	*/
	void CLString::bmove512(gptr to, const gptr from, register uint length)
	{
		reg1 ub8 *f,*t,*end= (ub8*) ((char*) from+length);

		f= (ub8*) from;
		t= (ub8*) to;

#if defined(m88k) || defined(sparc) || defined(HAVE_LONG_LONG)
		do {
			t[0]=f[0];	    t[1]=f[1];	    t[2]=f[2];	    t[3]=f[3];
			t[4]=f[4];	    t[5]=f[5];	    t[6]=f[6];	    t[7]=f[7];
			t[8]=f[8];	    t[9]=f[9];	    t[10]=f[10];    t[11]=f[11];
			t[12]=f[12];    t[13]=f[13];    t[14]=f[14];    t[15]=f[15];
			t[16]=f[16];    t[17]=f[17];    t[18]=f[18];    t[19]=f[19];
			t[20]=f[20];    t[21]=f[21];    t[22]=f[22];    t[23]=f[23];
			t[24]=f[24];    t[25]=f[25];    t[26]=f[26];    t[27]=f[27];
			t[28]=f[28];    t[29]=f[29];    t[30]=f[30];    t[31]=f[31];
			t[32]=f[32];    t[33]=f[33];    t[34]=f[34];    t[35]=f[35];
			t[36]=f[36];    t[37]=f[37];    t[38]=f[38];    t[39]=f[39];
			t[40]=f[40];    t[41]=f[41];    t[42]=f[42];    t[43]=f[43];
			t[44]=f[44];    t[45]=f[45];    t[46]=f[46];    t[47]=f[47];
			t[48]=f[48];    t[49]=f[49];    t[50]=f[50];    t[51]=f[51];
			t[52]=f[52];    t[53]=f[53];    t[54]=f[54];    t[55]=f[55];
			t[56]=f[56];    t[57]=f[57];    t[58]=f[58];    t[59]=f[59];
			t[60]=f[60];    t[61]=f[61];    t[62]=f[62];    t[63]=f[63];
#ifdef HAVE_LONG_LONG
			t+=64; f+=64;
#else
			t[64]=f[64];    t[65]=f[65];    t[66]=f[66];    t[67]=f[67];
			t[68]=f[68];    t[69]=f[69];    t[70]=f[70];    t[71]=f[71];
			t[72]=f[72];    t[73]=f[73];    t[74]=f[74];    t[75]=f[75];
			t[76]=f[76];    t[77]=f[77];    t[78]=f[78];    t[79]=f[79];
			t[80]=f[80];    t[81]=f[81];    t[82]=f[82];    t[83]=f[83];
			t[84]=f[84];    t[85]=f[85];    t[86]=f[86];    t[87]=f[87];
			t[88]=f[88];    t[89]=f[89];    t[90]=f[90];    t[91]=f[91];
			t[92]=f[92];    t[93]=f[93];    t[94]=f[94];    t[95]=f[95];
			t[96]=f[96];    t[97]=f[97];    t[98]=f[98];    t[99]=f[99];
			t[100]=f[100];  t[101]=f[101];  t[102]=f[102];  t[103]=f[103];
			t[104]=f[104];  t[105]=f[105];  t[106]=f[106];  t[107]=f[107];
			t[108]=f[108];  t[109]=f[109];  t[110]=f[110];  t[111]=f[111];
			t[112]=f[112];  t[113]=f[113];  t[114]=f[114];  t[115]=f[115];
			t[116]=f[116];  t[117]=f[117];  t[118]=f[118];  t[119]=f[119];
			t[120]=f[120];  t[121]=f[121];  t[122]=f[122];  t[123]=f[123];
			t[124]=f[124];  t[125]=f[125];  t[126]=f[126];  t[127]=f[127];
			t+=128; f+=128;
#endif
		} while (f < end);
#else
		do {
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
			*t++ = *f++;    *t++ = *f++;    *t++ = *f++;    *t++ = *f++;
		} while (f < end);
#endif
		return;
	} /* bmove512 */

	/**
	 * <summary>
	 *  从文件中读取内容并存放到psData变量中，psData变量的内存由此函数内部做分配，外面需要使用SafeFree函数释放内存。
	 * </summary>
	 */
	int CLString::LoadStrFromFile(const char* psFileName, char **psData)
	{
		FILE* fp = NULL;
		int err;
		
#ifdef __WIN__
		if ((err = fopen_s(&fp, psFileName, "rb")) != 0)
		{
			return err;
		}
#else
		if ((fp = fopen(psFileName, "r")) == NULL)
		{
			return errno;
		}
#endif
		if (fseek(fp, (long)0, SEEK_END) != 0)
		{
			fclose(fp);
			return errno;
		}

		long lFileSize = ftell(fp);
		if (lFileSize == -1L)
		{
			fclose(fp);
			return errno;
		}

		if (fseek(fp, (long)0, SEEK_SET) != 0)
		{
			fclose(fp);
			return errno;
		}

		*psData = (char*)SafeMalloc(lFileSize + 1, 0);
		if ((*psData) == NULL)
		{
			fclose(fp);
			return NSPrime::CLGlobalErrors::EE_OUTOFMEMORY;
		}

		size_t iReadCount = 0;
		if ( (iReadCount = fread(*psData, 1, lFileSize, fp)) != lFileSize)
		{
			SafeFree(*psData, 0);
			*psData = NULL;
			fclose(fp);
			return errno;
		}

		fclose(fp);
		return 0;
	}
}
