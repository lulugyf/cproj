#include <cstdlib>
#include <cstdio>
#include <cstring>

extern "C" void desenc(const char *src, char* dst, size_t len);
extern "C" void desdec(const char *src, char* dst, size_t len);
int main(int argc, char* argv[])
{
        char dest[1024];
        memset(dest, 0, sizeof(dest));
    if (argc != 3) {
        printf("usage:%s  flag passwd\n", argv[0]);
        printf(" flag =1 º”√‹\n");
        printf("      =0 Ω‚√‹\n");
        exit(0);
    }
        if (atoi(argv[1]) == 0 )
                desdec(argv[2], dest, 1024);
        else
                desenc(argv[2], dest, 1024);
         printf("[%s] [%s]\n", argv[2], dest);

        return 0;
}
