#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "des.h"

#define MAXENDELEN 32
#define KEYSIZB 1024 /* should hit tty line limit first :-) */

#define MAINKEY	"bossboss"

extern char * pubEncrypt(const char *src, const int inlen, int *outlen, char *key);
extern char * pubDecrypt(const char *src, int inlen, int *outlen, char *key);

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

int main3(int argc,char **argv)
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
void perf_test(int count) {
    char key[32], plain[64], cipher[128], *out;
    int i, outlen;
    time_t t1, t2;

    strcpy(key, "bossboss");
    strcpy(plain, "123321");

    t1 = time(NULL);
    for(i=0; i<count; i++) {
        out = pubEncrypt(plain, strlen(plain), &outlen, key);
        strcpy(cipher, out);
        free(out);

        out = pubDecrypt(cipher, strlen(cipher), &outlen, key);
        free(out);
    }
    t2 = time(NULL);
    printf("perf_test done %d sec\n", t2 -t1);
}

int main(int argc, char **argv) {
    char line[1024], tag[32], key[32], source[128], *out;
    int r, outlen;
    if(argc > 2 && strcmp(argv[1], "test")==0){
        perf_test(atoi(argv[2]));
        return 0;
    }
    while(1) {
        fgets(line, sizeof(line), stdin);
        if(strncmp(line, "quit", 4) == 0)
            break;
        r = sscanf(line, "%s %s %s", tag, key, source);
        if(r != 3){
            printf("ERROR: invalid input\n");
            fflush(stdout);
            continue;
        }
        if(strcmp(tag, "en") == 0){
            out = pubEncrypt(source, strlen(source), &outlen, key);
            if(out == NULL){
                printf("ERROR: encrypt failed\n");
            }else{
                printf("OUT: %s\n", out);
                free(out);
            }
            fflush(stdout);
        }else if(strcmp(tag, "de") == 0){
            out = pubDecrypt(source, strlen(source), &outlen, key);
            if(out == NULL){
                printf("ERROR: decrypt failed\n");
            }else{
                printf("OUT: %s\n", out);
                free(out);
            }
            fflush(stdout);
        }
    }
    return 0;
}
