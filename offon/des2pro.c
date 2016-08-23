#include <stdio.h>
#include "des2.h"


int main(int argc, char *argv[])
{
    char buf[100], buf1[100];
    int l;

    if(argc < 3){
//        printf("Usage: %s <de|en> <string>\n\n", argv[0]);
        return -1;
    }
    if(strcmp(argv[1], "en") == 0){
        mydes(1, argv[2], buf);
        printf("encode output %s\n", buf);
    }else{
        mydes(0, argv[2], buf);
        printf("decode output %s\n", buf);
    }
    return 0;
}
