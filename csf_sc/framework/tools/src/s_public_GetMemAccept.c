#include "publicsrv.h"

int main()
{
	char accept[30];

	memset(accept,0,sizeof(accept));

	strcpy(accept,GetMemAccept());
	if (strlen(accept) == 0)
	{
                printf("ȡ�ڴ���ˮʧ��!\n");
	}
	printf("��ǰ�ڴ���ˮΪ:%s\n",accept);
}
