#pragma once

//#include "global.h"

namespace NSPrime
{
	class CLString
	{
	public:
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
		static int StrCpyChina (unsigned char * psDest,const unsigned char * psSource, int iCount);

		/**
		 *     字符串的按字查找函数，如果找到返回所查字符串的开始位置，否则返回NULL。
		 */
		static char* StrWordFind(const char * str1, const char *str2);

		/**
		 *     字符串的按字查找函数，如果找到返回所查字符串的开始位置，否则返回NULL。
		 */
		static char* StrChrWordFind(const char * psStr, int ch);

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
		static int StrToFields(const char* src, char separateChar, ...);

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
		static int StrToPtrs(char *src,const char *separateStr,char **ptrs);

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
		 * @param iArraySize	数组的长度，如果为-1，表示不考虑数组的长度，否则，只是返回前iArraySize个数组元素。
		 * @return 返回一源串src中包含域的数量。
		 */
		static int StrToRows(const char *src,char separateChar,char **dest, int colLen, int iFlags=0, int iArraySize = -1);

		static char* Trim(char *S);
		static char* LTrim(char *S);
		static char* RTrim(char *S);

		/**
		 *     字符串查找函数，忽略大小字，如果找到返回所查字符串的开始位置，否则返回NULL。
		 */
		static char * StrFind (const char * str1, const char * str2);

		//字符串比较，不区分大小写，dst和src都不能为NULL。
		static int AsciiStrICmp (const char * dst,const char * src);

		//count个字符串比较，不区分大小写，dst和src都不能为NULL。
		static int AsciiStrNICmp (const char * first,const char * last,size_t count);

		/**
		 *     截取指定数量的字节数量。当截取的最后一个字符是半个汉字时，则少截
		 * 取一个字符。
		 * <param name="psSrc">原字符串</param>
		 * <param name="psDesc">输出字符串</param>
		 * <param name="iCount">最大截取的数量</param>
		 * <returns>截取的字节数量。</returns>
		 */
		static int SubStrChina(const char *psSrc,char *psDesc,int iCount)
		{
			int i = 0;

			while(i < iCount)
			{
				if (psSrc[i] < 0 || psSrc[i] > 127)
				{
					if (i == iCount - 1)
					{
						return i;
					}
					psDesc[i] = psSrc[i];
					i++;
					psDesc[i] = psSrc[i];
				}
				else
				{
					psDesc[i] = psSrc[i];
				}
				i++;
			}

			return i;
		}
		
		//返回结束位置。
		static char *StrMake(register char *dst, register const char *src, ub4 iLength)
		{
			while (iLength--)
			{
				if (! (*dst++ = *src++))
				{
					return dst-1;
				}
			}
			*dst=0;
			return dst;
		}

		/**
		 * StrEnd(s) returns a character pointer to the NUL which ends s.  That
		 * is,  NSPrime::CLString::StrEnd(s)-s  ==  strlen(s). This is useful for adding things at
		 * the end of strings.  It is redundant, because  strchr(s,'\0')  could
		 * be used instead, but this is clearer and faster.
		 * Beware: the asm version works only if strlen(s) < 65535.
		 */
		static char *StrEnd(register const char *s)
		{
			while (*s++);
			return (char*) (s-1);
		}
		static bool IsPrefix(register const char *s, register const char *t);
		static char *StrXMov(char *dst,const char *src, ...);
		static char *StrXNMov(char *dst,uint len, const char *src, ...);
		static char *StrCEnd(register const char *s, register char c)
		{
			for (;;)
			{
				if (*s == (char) c) return (char*) s;
				if (!*s++) return (char*) s-1;
			}
		}
		static char *StrMov(register char *dst, register const char *src)
		{
			while ((*dst++ = *src++)) ;
			return dst-1;
		}

		static char *StrNMov(register char *dst, register const char *src, uint n)
		{
			while (n-- != 0) {
				if (!(*dst++ = *src++)) {
					return (char*) dst-1;
				}
			}
			return dst;
		}
		static void MoveUpp(register char *dst, register const char *src, register uint len)
		{
			while (len-- != 0) *--dst = *--src;
		}

		/*
		StrFill(dest, len, fill) makes a string of fill-characters. The result
		string is of length == len. The des+len character is allways set to NULL.
		StrFill() returns pointer to dest+len;
		*/
		static char* StrFill(char* s,uint len,char fill);

		/*
		strip_sp(my_string str)
		Strips end-space from string and returns new length.
		*/
		static size_t StripSpace(register char* str);

		/*
		bmove512(dst, src, len) moves exactly "len" bytes from the source "src"
		to the destination "dst".  "src" and "dst" must be alligned on long
		boundory and len must be a mutliple of 512 byte. If len is not a
		multiple of 512 byte len/512*512+1 bytes is copyed.
		bmove512 is moustly used to copy IO_BLOCKS.  bmove512 should be the
		fastest way to move a mutiple of 512 byte.
		*/
		static void bmove512(gptr to, const gptr from, register uint length);

		/**
		 * <summary>
		 *  从文件中读取内容并存放到psData变量中，psData变量的内存由此函数内部做分配，外面需要使用SafeFree函数释放内存。
		 * </summary>
		 */
		static int LoadStrFromFile(const char* psFileName, char **psData);
	};

}
