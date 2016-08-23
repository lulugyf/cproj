#include "publicsrv.h"

main(int argc, char *argv[])
{
        char dest[32+1];
        memset(dest, 0, sizeof(dest));

	if (argc != 3) {
		printf("usage: get_pass flag passwd\n");
		printf(" flag =1 º”√‹\n");
		printf("      =0 Ω‚√‹\n");
		exit(0);
	}

	if (atoi(argv[1]) == 0 || atoi(argv[1]) == 1) {
		spublicEnDePasswd(argv[2], dest, MASTERKEY, atoi(argv[1]));
		printf("[%s] [%s]\n", argv[2], dest);
	}
	else {
		printf(" ‰»Î¥ÌŒÛ!\n");
	}
}
