#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "des.h"

#if defined(__STDC__) || defined(VMS) || defined(M_XENIX) || defined(MSDOS)
#include <string.h>
#define bcopy(f,t,n)	memcpy(t,f,(size_t)(n))
#define bcmp(a,b,n)	memcmp(a, b,(size_t)(n))
#define index(s,c)	strchr(s,c)
#endif
#define MAXENDELEN 32
#define KEYSIZB 1024 /* should hit tty line limit first :-) */

#define MAINKEY	"bossboss"


int main1(int argc,char **argv)
{
	char src[MAXENDELEN+1],dest[MAXENDELEN+1];

	int eflag=0;
	memset(src,0, sizeof(src));
	memset(dest,0, sizeof(dest));

	strcpy(src, argv[1]);
	eflag=atoi(argv[2]);

	spublicEnDePasswd(src, dest, MAINKEY, eflag);
	printf("src=[%s], dest=[%s]\n", src, dest);
	return 0;
}

int main(int argc,char **argv)
{
	char *out;
	int outlen;
	if(argc < 4){
		printf("\nUsage: %s <en|de> <key> <src>\n\n", argv[0]);
		return 0;
	}
	
	if(strcmp(argv[1], "en") == 0){
		out = pubEncrypt(argv[3], strlen(argv[3]), &outlen, argv[2]);
		if(out == NULL){
			printf("Failed!!!\n");
		}else{
			printf("OUT:\n%s\n", out);
			free(out);
		}
	}else if(strcmp(argv[1], "de") == 0){
		out = pubDecrypt(argv[3], strlen(argv[3]), &outlen, argv[2]);
		if(out == NULL){
			printf("Failed!!!\n");
		}else{
			printf("OUT:\n%s\n", out);
			free(out);
		}
	}
	return 0;
}