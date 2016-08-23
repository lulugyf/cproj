/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/* #ident	"@(#) samples/atmi/simpapp/simpcl.c	$Revision: 1.5 $" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "atmi.h"		/* TUXEDO  Header File */

int cal_tm(struct timeval *t1, struct timeval *t2){
	return (int)((t2->tv_sec - t1->tv_sec) * 1000 + (t2->tv_usec-t1->tv_usec) / 1000);
}

int callone(char *service_name, const char *param, int showout)
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

int main(int argc, char *argv[])
{
	char *rcvbuf;
	char service_name[32];
	long sendlen, rcvlen;
	int ret, callcount, i;
	struct timeval t1, t2;
	int showout = 1;
	TPINIT *tpinfo = NULL;
	char pass[64];


	if(argc < 3) {
		(void) fprintf(stderr, "Usage: clxml service_name xml_string\n");
		exit(1);
	}
	
	switch(tpchkauth()){
		case TPNOAUTH:
			break;
		case TPSYSAUTH:
			printf("need passwd:");
			memset(pass, 0, sizeof(pass));
			scanf("%s", pass);
			rcvbuf = strchr(pass, '\n'); if(rcvbuf != NULL) *rcvbuf = 0;
			rcvbuf = strchr(pass, '\r'); if(rcvbuf != NULL) *rcvbuf = 0;
			tpinfo = (TPINIT *)tpalloc("TPINIT", NULL, sizeof(TPINIT));
			strcpy(tpinfo->passwd, pass);
			break;
	}

	/* Attach to System/T as a Client Process */
	if (tpinit(tpinfo) == -1) {
		(void) fprintf(stderr, "Tpinit failed\n");
		if(tpinfo != NULL) tpfree((char *)tpinfo);
		exit(1);
	}
	if(tpinfo != NULL) tpfree((char *)tpinfo);

	sendlen = strlen(argv[2]);
	

	(void) strcpy(service_name, argv[1]);
	//(void) strcpy(sendbuf, argv[2]);
	callcount = 1;
	if(argc > 3){
		callcount = atoi(argv[3]);
	}

	if(callcount > 1) showout = 0;
	gettimeofday(&t1, NULL);
	printf("===call count=%d argc=%d\n", callcount, argc);
	for(i=0; i<callcount; i++){
		callone(service_name, argv[2], showout);
	}
	gettimeofday(&t2, NULL);
	printf("Time: %d (ms)\n", cal_tm(&t1, &t2));

	
	tpterm();
	return(0);
}
