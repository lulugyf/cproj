#include <alloca.h>
#include <string.h>


int encrypt2(char* srcbuf);
int decrypt2(char *encrychr);

void desdec(const char *src, char* dst, size_t len)
{
        int rt;
        char* buf=(char*)alloca(strlen(src)+1);
        strcpy(buf, src);
        decrypt2(buf);
        strncpy(dst, buf, len-1);
        dst[len-1]=0;
}
void desenc(const char *src, char* dst, size_t len)
{
        int rt;
        char* buf=(char*)alloca(2*(strlen(src)+1));
        strcpy(buf, src);
        encrypt2(buf);
        strncpy(dst, buf, len-1);
        dst[len-1]=0;
}

