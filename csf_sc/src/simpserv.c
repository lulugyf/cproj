#include <stdio.h>
#include <ctype.h>
#include <atmi.h>       /* TUXEDO Header File */
#include <userlog.h>    /* TUXEDO Header File */


int tpsvrinit(int argc, char *argv[])
{
        /* Some compilers warn if argc and argv aren't used. */
        argc = argc;
        argv = argv;

        /* userlog writes to the central TUXEDO message log */
        userlog("Welcome to the simple server!");
        return(0);
}


int callone(const char *service_name, const char *param, int showout)
{
	char *sendbuf, *rcvbuf;
	int ret;
	int sendlen;
    sendlen = strlen(param);
   	if((sendbuf = (char *) tpalloc("STRING", NULL, sendlen+1)) == NULL) {
		(void) fprintf(stderr,"Error allocating send buffer\n");
		return 2;
	}
	strcpy(sendbuf, param);
  if((rcvbuf = (char *) tpalloc("STRING", NULL, 10240)) == NULL)
   {
	 fprintf(stderr,"Error allocating receive buffer, tperrno=%ld\n", tperrno);
	 tpfree(sendbuf);
	 return 1;
   }

	/* Request the service TOUPPER, waiting for a reply */
	ret = tpcall(service_name, (char *)sendbuf, sendlen, (char **)&rcvbuf, &sendlen, (long)0);

	if(ret == -1) {
		(void) fprintf(stderr, "Can't send request to service [%s]\n", service_name);
		(void) fprintf(stderr, "Tperrno = %d\n", tperrno);
		tpfree(rcvbuf);
		tpfree(sendbuf);
		return 2;
	}

	if(showout)
		fprintf(stdout, "Returned xml_string is: %s\n", rcvbuf);
	tpfree(rcvbuf);
	tpfree(sendbuf);
	return 0;
}


void TOUPPER(TPSVCINFO *rqst)
{

    int i;
	userlog("call %s with [%s]\n", rqst->name, rqst->data);
	for(i = 0; i < rqst->len-1; i++)
		rqst->data[i] = toupper(rqst->data[i]);
				
	callone("sQDual", "{}", 1);
 
	tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);
}