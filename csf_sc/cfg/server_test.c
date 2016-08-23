/**
 *  (c) 2007 BEA Systems, Inc. All Rights Reserved.
 *
 *  Copyright (c) 2007 BEA Systems, Inc.
 *  All rights reserved
 *  buildserver -o s10 -f s10.c -s sRoute
 *  THIS IS UNPUBLISHED PROPRIETARY
 *  SOURCE CODE OF BEA Systems, Inc.
 *  The copyright notice above does not
 *  evidence any actual or intended
 *  publication of such source code.
 */

/* #ident	"@(#) samples/atmi/simpapp/simpserv.c	$Revision: 1.2 $" */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include <ctype.h>
#include <atmi.h>
#include <userlog.h>
#include <fml.h>   
#include <Usysflds.h>
#include <fml32.h>   
#include <sys/timeb.h>
#include <limits.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>



#include <stdio.h>
#include <ctype.h>

#include <atmi.h>       /* TUXEDO Header File */
#include <userlog.h>    /* TUXEDO Header File */

/**
 *  tpsvrinit is executed when a server is booted,
 *  before it begins processing requests.
 *  It is not necessary to have this function.
 *  Also available is tpsvrdone (not used in this
 *  example), which is called at server shutdown time.
 */
#if defined(__STDC__) || defined(__cplusplus)
tpsvrinit( int argc, char *argv[] )
#else
tpsvrinit( argc, argv )
    int     argc;
    char  **argv;
#endif
{
    /* Some compilers warn if argc and argv aren't used. */
    argc = argc;
    argv = argv;

    /* userlog writes to the central TUXEDO message log. */
    userlog( "Welcome to the simple server" );
    return(0);
}

long get_str_from_file_mm(const char *file_name,char **content, long *ptr_len)
{
    FILE *fp = fopen(file_name, "r");
    time_t file_mtime;
    if(!fp)
    {
        printf("[%s][%s][%d]: open [%s] failed. errno=[%d],errmsg=[%s]\n",\
        __FILE__, __func__, __LINE__, file_name,errno,strerror( errno ));
        return -1; /* open file error */
    }

    struct stat f_stat;
    int fd = fileno(fp);
    long file_size = 0;

    fstat(fd,&f_stat);
    file_size = f_stat.st_size;    /* 文件的大小 */
    file_mtime = f_stat.st_mtime;  /* 文件的修改时间 */
    *ptr_len = file_size;
    (*content) = (char *)malloc(file_size+9);
    memset(*content,0,file_size+9);
    read(fd,*content,file_size);
    close(fd);
    fclose(fp);
    return file_mtime;
}


/**
 *  This function performs the actual service requested
 *  by the client.
 *  Its argument is a structure containing among other
 *  things a pointer to the data buffer, and the length
 *  of the data buffer.
 */
#ifdef __cplusplus
extern "C"
#endif
void
#if defined(__STDC__) || defined(__cplusplus)
TOUPPER(TPSVCINFO *rqst)
#else
TOUPPER(rqst)
    TPSVCINFO *rqst;
#endif
{
    /*
    int i;

    for( i=0; i<rqst->len-1; i++ )
    {
        rqst->data[i] = toupper(rqst->data[i]);
    }

   
    tpreturn( TPSUCCESS, 0, rqst->data, 0L, 0 );
    */
    long default_size = 512;
    static char file_name[64];
    int retcode = 0;
    char *result = NULL;
    memset(file_name, 0, sizeof(file_name));
    strcpy(file_name, "./data/");
    /*
    if(strcmp(rqst->data, "lpc") == 0)
    {
        strncpy(file_name + strlen(file_name), rqst->data, rqst->len);
    }
    else
    {
        strcat(file_name,"test.json");
    }
    */
    strcat(file_name,"lpc");
    
    long file_size = 0;
    char *ptr_content = NULL;
    retcode = get_str_from_file_mm(file_name, &ptr_content, &file_size);
    
	sleep(0);
    if(retcode == -1)
    {/* open file failed! */
        if( (result=tpalloc("STRING", "", default_size)) == (char *)NULL)
        {
            (void)userlog("%s: string tpalloc failed tperrno %d", "TOUPPER",tperrno);
            (void)tpreturn(TPFAIL,0,NULL,0,0);
        }
        sprintf(result, "the file:[%s] you wantted doesn't exists!\n",file_name);
        tpreturn(TPSUCCESS, 0, result, strlen(result), 0);
    }
    else
    {/* open file OK */
        if( (result=tpalloc("STRING", "", file_size+9)) == (char *)NULL)
        {
            (void)userlog("%s: string tpalloc failed tperrno %d", "tpalloc",tperrno);
            (void)tpreturn(TPFAIL,0,NULL,0,0);
        }
        strcpy(result, ptr_content);
        userlog(">>>>>>>>>>TOUPPER server ok!");
        tpreturn(TPSUCCESS, 0, result, file_size, 0);
    }
    
}





#ifdef __cplusplus
extern "C"
#endif
void
#if defined(__STDC__) || defined(__cplusplus)
stest(TPSVCINFO *rqst)
#else
stest(rqst)
    TPSVCINFO *rqst;
#endif
{
    /*
    int i;

    for( i=0; i<rqst->len-1; i++ )
    {
        rqst->data[i] = toupper(rqst->data[i]);
    }

   
    tpreturn( TPSUCCESS, 0, rqst->data, 0L, 0 );
    */
    long default_size = 512;
    static char file_name[64];
    int retcode = 0;
    char *result = NULL;
    memset(file_name, 0, sizeof(file_name));
    strcpy(file_name, "./data/");
    /*
    if(strcmp(rqst->data, "lpc") == 0)
    {
        strncpy(file_name + strlen(file_name), rqst->data, rqst->len);
    }
    else
    {
        strcat(file_name,"test.json");
    }
    */
    strcat(file_name,"json");
    
    long file_size = 0;
    char *ptr_content = NULL;
    retcode = 0;
    file_size = 1000;
    ptr_content = (char *)malloc(1000);
    strcpy(ptr_content, "hello,liupengc,XXXXXXXXXXX");
    
	sleep(0);
    if(retcode == -1)
    {/* open file failed! */
        if( (result=tpalloc("STRING", "", default_size)) == (char *)NULL)
        {
            (void)userlog("%s: string tpalloc failed tperrno %d", "TOUPPER",tperrno);
            (void)tpreturn(TPFAIL,0,NULL,0,0);
        }
        sprintf(result, "the file:[%s] you wantted doesn't exists!\n",file_name);
        tpreturn(TPSUCCESS, 0, result, strlen(result), 0);
    }
    else
    {/* open file OK */
        if( (result=tpalloc("STRING", "", file_size+9)) == (char *)NULL)
        {
            (void)userlog("%s: string tpalloc failed tperrno %d", "tpalloc",tperrno);
            (void)tpreturn(TPFAIL,0,NULL,0,0);
        }
        strcpy(result, ptr_content);
        userlog(">>>>>>>>>>stest server ok!");
        tpreturn(TPSUCCESS, 0, result, file_size, 0);
    }
    
}




#ifdef __cplusplus
extern "C"
#endif
void
#if defined(__STDC__) || defined(__cplusplus)
sRoute(TPSVCINFO *rqst)
#else
sRoute(rqst)
    TPSVCINFO *rqst;
#endif
{
    /*
    int i;

    for( i=0; i<rqst->len-1; i++ )
    {
        rqst->data[i] = toupper(rqst->data[i]);
    }

   
    tpreturn( TPSUCCESS, 0, rqst->data, 0L, 0 );
    */
    long default_size = 512;
    static char file_name[64];
    int retcode = 0;
    char *result = NULL;
    memset(file_name, 0, sizeof(file_name));
    strcpy(file_name, "./data/");
    /*
    if(strcmp(rqst->data, "lpc") == 0)
    {
        strncpy(file_name + strlen(file_name), rqst->data, rqst->len);
    }
    else
    {
        strcat(file_name,"test.json");
    }
    */
    strcat(file_name,"route");
    
    long file_size = 0;
    char *ptr_content = NULL;
    retcode = get_str_from_file_mm(file_name, &ptr_content, &file_size);
    
	sleep(0);
    if(retcode == -1)
    {/* open file failed! */
        if( (result=tpalloc("STRING", "", default_size)) == (char *)NULL)
        {
            (void)userlog("%s: string tpalloc failed tperrno %d", "TOUPPER",tperrno);
            (void)tpreturn(TPFAIL,0,NULL,0,0);
        }
        sprintf(result, "the file:[%s] you wantted doesn't exists!\n",file_name);
        tpreturn(TPSUCCESS, 0, result, strlen(result), 0);
    }
    else
    {/* open file OK */
        if( (result=tpalloc("STRING", "", file_size+9)) == (char *)NULL)
        {
            (void)userlog("%s: string tpalloc failed tperrno %d", "tpalloc",tperrno);
            (void)tpreturn(TPFAIL,0,NULL,0,0);
        }
        strcpy(result, ptr_content);
        userlog(">>>>>>>>>>sRoute server ok!");
        tpreturn(TPSUCCESS, 0, result, file_size, 0);
    }
    
}








