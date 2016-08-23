#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "des.h"

const char *pstr = "PLMOKNIJBUHYGVTFCRDXESZAQWqazwsxedcrfvtgbyhnujmikolp1234567890~`!@#$%^&*()-_+=|\\[]{}.,><?/;:";

/*@���ܺ���
 *@description				���Ȳ��ܳ���PASSWD_MAX_LENGTH���ַ�������ǰ��ĳ��Ȳ��䡣
 *@param		src			����ԭ�ִ�
 *@output		dest		���ܺ��ִ�
 *@return					0�ɹ�������ʧ��
*/
int cliEncrypt(const char* src, char *dest)
{
	int i, len;
	int tmp_int = 0;
	
	len = strlen(src);
	if (len > PASSWD_MAX_LENGTH)
	{
		return -1;
	}
	memset(dest, 0, PASSWD_MAX_LENGTH);
	
	for (i = 0; i < len; i++)
	{
		if (isdigit( (int)src[i] ) )
		{
			tmp_int = src[i] - '0';
			dest[i] =pstr[ (tmp_int + i + 1) *( len / 2 + 1)];
		}
		else
		{
			return -2;
		}
	}
	dest[i] = '\0';
	return 0;
}

/*@���ܺ���
 *@description				���Ȳ��ܳ���PASSWD_MAX_LENGTH���ַ�������ǰ��ĳ��Ȳ��䡣
 *@param		src			����ԭ�ִ�
 *@output		dest		���ܺ��ִ�
 *@return					0�ɹ�������ʧ��
*/
int cliUnencrypt(const char* src, char *dest)
{
	int i, j, len, len2;
	int tmp_int = 0;
	
	len = strlen(src);
	if (len > PASSWD_MAX_LENGTH)
	{
		return -1;
	}
	memset(dest, 0, PASSWD_MAX_LENGTH);
	len2= strlen(pstr);
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len2; j++)
		{
			if (src[i] == pstr[j])
			{
				dest[i] = j / (len / 2 + 1) - i - 1 + '0';
				break;
			}
		}
		
	}
	dest[i] = '\0';

	return 0;
}
