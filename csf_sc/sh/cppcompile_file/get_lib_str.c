#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>

long get_str_from_file(const char *file_name,char **content)
{
    FILE *fp = fopen(file_name, "r");
    time_t file_mtime;
    if(!fp)
    {
        printf("in [%s][%d]line: open [%s] failed. errno=[%d],errmsg=[%s]\n",\
        __FILE__,__LINE__,file_name,errno,strerror( errno ));
        return -1;
    }

    static struct stat f_stat;
    int fd = fileno(fp);
    int file_size = 0;

    fstat(fd,&f_stat);
    file_size = f_stat.st_size;
    file_mtime = f_stat.st_mtime;

    (*content) = (char *)malloc(file_size+1);
    memset(*content,0,file_size+1);
    read(fd,*content,file_size);

    close(fd);
    fclose(fp);

    return file_mtime;
}

void replace_char(char *str, int len, char old, char new)
{
    int i = 0;
    while(i < len)
    {
        if(str[i] == old) str[i] = new;
        i++;
    }
}

void replace_ch(char *str, int len, char newch)
{
	for(int i = 0; i < len; i ++)
	{
		str[i] = newch;
	}
}

int main(int argc, char ** argv)
{
    /*printf("argc=[%d], argv[0]=[%s]\n", argc, argv[0]);*/
    if(argc != 2)
    {
        printf("the get_lib_str_comm needs one para : file_name! ");
        return 0;
    }
    char *p1 = "DependSoList:";
    char *p2 = "Success";
    char *p3 = "ChangedDependSo:NO";
    char *p4 = "ChangedDependSo:YES";
    char *content = NULL;

    if( access( argv[1], F_OK ) != 0 )
    {
        printf("Don't allow to access the file:[%s] or the file:[%s] may not exist! ",argv[1], argv[1]);
        return 1;
    }

    get_str_from_file(argv[1], &content);
    replace_char(content, strlen(content), '\r', ' ');
    replace_char(content, strlen(content), '\n', ' ');
    char *pstart = strstr(content, p1);
    if(!pstart)
    {
        printf("run cppcompile.sh error, it doesn't output str:DependSoList: [%s]", content);
        return 2;
    }
    char *pend = strstr(content, p2);
    if(!pend)
    {
        printf("run cppcompile.sh error, it doesn't output str:Success! [%s]",content);
        return 3;
    }
	
	int iRet = 0;
	char *ps3 = strstr(content, p3);
	if(ps3)
	{
		replace_ch(ps3, strlen(p3), ' ');
		iRet = 100;
	}
	char *ps4 = strstr(content, p4);
	if(ps4)
	{
		replace_ch(ps4, strlen(p4), ' ');
		iRet = 101;
	}
	
    char *output_str = (char *)malloc(pend - pstart + 2);
    memset(output_str, 0, pend - pstart + 2);
    output_str[pend - pstart] = ' ';
    strncpy(output_str, pstart+strlen(p1),pend - pstart - strlen(p1));
    printf("%s",output_str);
    free(output_str);
    free(content);
    return iRet;
}
