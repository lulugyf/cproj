#include "publicsrv.h"

int main()
{
        if (spublicPutKeyShm() < 0) 
	{
                userlog("��ʼ�������ڴ�ʧ��!\n");
        }
	if (CreatMemAccept() != 0)
	{
                userlog("��ʼ���ڴ���ˮʧ��!\n");
	}
}
