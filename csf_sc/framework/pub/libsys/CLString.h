#pragma once

//#include "global.h"

namespace NSPrime
{
	class CLString
	{
	public:
		/**
		 * <summary>
		 *   ���ĸ��ƺ�����ĩβ�İ�����ֲ����ơ�
		 * </summary>
		 * <param name="psDest"></param>
		 * <param name="psSource"></param>
		 * <returns>
		 *   ���Ƶ��ַ�����
		 * </returns>
		 */
		static int StrCpyChina (unsigned char * psDest,const unsigned char * psSource, int iCount);

		/**
		 *     �ַ����İ��ֲ��Һ���������ҵ����������ַ����Ŀ�ʼλ�ã����򷵻�NULL��
		 */
		static char* StrWordFind(const char * str1, const char *str2);

		/**
		 *     �ַ����İ��ֲ��Һ���������ҵ����������ַ����Ŀ�ʼλ�ã����򷵻�NULL��
		 */
		static char* StrChrWordFind(const char * psStr, int ch);

		/**
		 *     ���ַ����е�ֵ����ָ���ķָ������ֱ��ŵ�����Ķ�̬�����У���Щ�����
		 * ���ͱ���Ϊ��char*����
		 *     һ����˵��Դ�ַ������ֶ���ĸ�����Ӧ���붯̬�����ĸ�����ͬ�����Դ�ַ�
		 * ����ĸ������ڶ�̬�����ĸ�����������-1�����Դ�ַ�����ĸ���С�ڶ�̬����
		 * �ĸ���������Ĳ��ֶ�̬������ܽ��ղ���ֵ��������Ϊ�������������ѵõ�ֵ
		 * ��ĸ��������Դ�ַ�����ĸ������ڶ�̬���������������ѵõ�ֵ��ĸ�����
		 * @author lugz
		 * @param src	��ʾ��Ҫ��ֵ�Դ����Դ���е��ַ�����ָ���ĵ����ַ�separateChar��
		 *              ����������ʾ�������߷ָ��Ĵ���
		 *                  "field1|field2|field3| ... fieldn|"
		 * @param separateChar
		 * @param ...	��������ͱ���Ϊ��char*�����ں����ж���Щ��������Ͳ���У�졣
		 * @return ����һ������ֵ�����Դ�ַ�����ĸ������ڶ�̬�����ĸ�����������-1��
		 *         ���Դ�ַ�����ĸ���С�ڶ�̬�����ĸ���������Ĳ��ֶ�̬������ܽ���
		 *         ����ֵ��������Ϊ�������������ѵõ�ֵ��ĸ��������Դ�ַ������
		 *         �������ڶ�̬���������������ѵõ�ֵ��ĸ�����
		 */
		static int StrToFields(const char* src, char separateChar, ...);

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
		static int StrToPtrs(char *src,const char *separateStr,char **ptrs);

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
		 * @param iFlags	0��ʾ������ѭ������separateChar������1����������separateChar���š�
		 * @param iArraySize	����ĳ��ȣ����Ϊ-1����ʾ����������ĳ��ȣ�����ֻ�Ƿ���ǰiArraySize������Ԫ�ء�
		 * @return ����һԴ��src�а������������
		 */
		static int StrToRows(const char *src,char separateChar,char **dest, int colLen, int iFlags=0, int iArraySize = -1);

		static char* Trim(char *S);
		static char* LTrim(char *S);
		static char* RTrim(char *S);

		/**
		 *     �ַ������Һ��������Դ�С�֣�����ҵ����������ַ����Ŀ�ʼλ�ã����򷵻�NULL��
		 */
		static char * StrFind (const char * str1, const char * str2);

		//�ַ����Ƚϣ������ִ�Сд��dst��src������ΪNULL��
		static int AsciiStrICmp (const char * dst,const char * src);

		//count���ַ����Ƚϣ������ִ�Сд��dst��src������ΪNULL��
		static int AsciiStrNICmp (const char * first,const char * last,size_t count);

		/**
		 *     ��ȡָ���������ֽ�����������ȡ�����һ���ַ��ǰ������ʱ�����ٽ�
		 * ȡһ���ַ���
		 * <param name="psSrc">ԭ�ַ���</param>
		 * <param name="psDesc">����ַ���</param>
		 * <param name="iCount">����ȡ������</param>
		 * <returns>��ȡ���ֽ�������</returns>
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
		
		//���ؽ���λ�á�
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
		 *  ���ļ��ж�ȡ���ݲ���ŵ�psData�����У�psData�������ڴ��ɴ˺����ڲ������䣬������Ҫʹ��SafeFree�����ͷ��ڴ档
		 * </summary>
		 */
		static int LoadStrFromFile(const char* psFileName, char **psData);
	};

}
