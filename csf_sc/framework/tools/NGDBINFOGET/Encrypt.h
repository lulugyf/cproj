/*�ӽ���ͷ�ļ�
*/
#ifndef	__ENCRYPT_H__
	#define __ENCRYPT_H__
	#include <time.h>
	#include <sys/time.h>
	#include <stdarg.h>
	#include <fcntl.h>
	#include <errno.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <dirent.h>
	#include <malloc.h>
	#include <stdarg.h>
	/*��װ����Կ�ļ��ܺ���*/
	int encrypt2(char* srcbuf);
	/*��װ����Կ�Ľ��ܺ���*/
	int decrypt2(char *encrychr);

	/*����Ա������ܺ���*/
	//int encrypt( char *sstr);
	/*����Ա������ܺ���*/
	//char * decrypt(char *tt);

	/*�������ļ�*/
  int DcReadCfg(char* section, char* key, char* value);
#endif
