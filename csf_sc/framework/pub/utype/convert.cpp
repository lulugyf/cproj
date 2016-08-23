#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <utype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <stdio.h>
#include <string.h>

#include "utype.h"

extern "C" {
#include "jsonc/json.h"
}


utype * json2utype(const char *str);
char * utype2json(const utype *pu);

void wf(char *file_name,char *buf, size_t len)
{
    int fd;
    fd = open( file_name,
        O_WRONLY | O_CREAT | O_TRUNC,
        S_IRUSR | S_IWUSR );
    write(fd,buf,len);
    close(fd);
}

char *rf(const char *fname)
{
    struct stat st;
    char *buf;
    if(stat(fname, &st) != 0)
    return NULL;
    buf = (char *)malloc(st.st_size+1);
    buf[st.st_size] = 0;
    FILE *fp = fopen(fname, "r");
    fread(buf, 1, st.st_size, fp);
    fclose(fp);
    return buf;
}



bool checkChr(const char *s, const char c) {
	for (; *s != 0; s++) {
		if (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
			continue;
		return *s == c;
	}
	return false;
}

int main(int argc, char** argv)
{
    if(argc < 2){
    	printf("Give me a file or string!!!\n");
    	return 1;
    }
    const char *arg1 = argv[1];
    const char *filename = NULL;
    char *filecontent = NULL;

    struct stat st;
    if(stat(arg1, &st) == 0){
    	filecontent = rf(arg1);
    	filename = arg1;
    	arg1 = filecontent;
    }
    
    char *output = NULL;
    if(checkChr(arg1, '<')){
    	// utype to json
    	uAutoPtr  inParam(uXml2Utype(arg1));
    	output = utype2json(inParam);
    }else{
    	// json to utype
    	uAutoPtr uptr1(json2utype(arg1));
		output = uUType2Xml(uptr1,"ROOT");
    }

    if(output == NULL){
    	printf("FAILED!!!\n");
    }
    if(filecontent == NULL){
    	// from args, print to stdout
    	printf("OUTPUT: \n%s\n", output);
    }else{
    	free(filecontent);
    	char f[128];
    	sprintf(f, "%s.out", filename);
    	wf(f, output, strlen(output));
    	printf("  output was writen to :%s\n", f);
    }
    free(output);

    return 0;
}

