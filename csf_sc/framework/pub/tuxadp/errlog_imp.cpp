/*
 * errlog_imp.cpp

 *
 *  Created on: 2013-6-25
 *      Author: guanyf
 */
#include <stdio.h>
#include "errlog.h"



#include <atmi.h>
#include <pthread.h>



static int running = 1;
static pthread_t th_handle;

static void *th_loaderrlog(void *)
{
	//文件加锁的问题， 避免重复进程
	errlog_loadIntoDB(&running, 5);
	printf("exit!!\n");
	return NULL;
}

extern "C" int tpsvrinit(int argc, char *argv[])
{
	int ret;
	ret = pthread_create(&th_handle, NULL, th_loaderrlog, NULL);
	if(ret != 0)
		return -1;
	return 0;
}


extern void tpsvrdone()
{
	int *retv;

	running = 0;
	pthread_join(th_handle, (void **)&retv);
}


extern "C" void __svc__(TPSVCINFO *trans)
{
	tpreturn(TPSUCCESS, 0, trans->data, 0, 0);
}


#ifdef __TEST_MAIN__
int main(int argc, char *argv[])
{
	int t_running = 1;
	errlog_loadIntoDB(&t_running);
	return 0;
}
#endif



