#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/** Ĭ�����봮����<=8��*/
#define PASSWD_MAX_LENGTH	8
#define DES_ENCRYPT     1
#define DES_DECRYPT     0

const char *pstr = "PLMOKNIJBUHYGVTFCRDXESZAQWqazwsxedcrfvtgbyhnujmikolp1234567890~`!@#$%^&*()-_+=|\\[]{}.,><?/;:";

int main(int argc, char ** argv)
{
	char pwd[PASSWD_MAX_LENGTH+1];
	if (argc != 3)
	{
		fprintf(stdout, "usage: encrypt	     <option> cryptchar\n"
						"       option:      0 DES_DECRYPT\n"
						"                    1 DES_ENCRYPT\n"
						"       cryptchar:   encrypt char or decrypt.\n"
						"       description: max length 8\n"
				);
		return -1;
	}
	if (strlen(argv[2]) > PASSWD_MAX_LENGTH)
	{
		fprintf(stdout, "�������󳤶Ȳ��ܴ���%dλ��\n",PASSWD_MAX_LENGTH);
		return -1;
	}
	if (argv[1][0] == '0')
	{
		unencrypt(argv[2], pwd);
		fprintf(stdout, "unencrypt src:[%s]\t\tdest[%s]\n", argv[2], pwd);
	}
	else
	{
		encrypt(argv[2], pwd);
		fprintf(stdout, "encrypt src:[%s]\t\tdest[%s]\n", argv[2], pwd);
	}
	return 0;
}

/*@���ܺ���
 *@description				���Ȳ��ܳ���PASSWD_MAX_LENGTH���ַ�������ǰ��ĳ��Ȳ��䡣
 *@param		src			����ԭ�ִ�
 *@output		dest		���ܺ��ִ�
 *@return					0�ɹ�������ʧ��
*/
int encrypt(const char* src, char *dest)
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
int unencrypt(const char* src, char *dest)
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

