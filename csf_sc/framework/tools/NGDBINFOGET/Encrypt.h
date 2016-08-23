/*加解密头文件
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
	/*封装了密钥的加密函数*/
	int encrypt2(char* srcbuf);
	/*封装了密钥的解密函数*/
	int decrypt2(char *encrychr);

	/*操作员口令加密函数*/
	//int encrypt( char *sstr);
	/*操作员口令解密函数*/
	//char * decrypt(char *tt);

	/*读配置文件*/
  int DcReadCfg(char* section, char* key, char* value);
#endif
