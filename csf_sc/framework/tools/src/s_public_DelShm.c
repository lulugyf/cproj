
/***************************
        kill shm, msg, sema 
 	Date: Jul 30,1999
**************************** */

#include "publicsrv.h"

void main()
{
	if((spublicDelKeyShm())<0)
		userlog("ɾ�������ڴ�ʧ��!",__FILE__,__LINE__);
	if(DelMemAccept() != 0)
		userlog("ɾ���ڴ���ˮʧ��!",__FILE__,__LINE__);
}
