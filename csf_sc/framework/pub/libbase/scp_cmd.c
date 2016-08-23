#include "smp.h"

extern int 	sockid;
extern char 	clibuf[2080];
extern jmp_buf env;
extern struct 	sockaddr_in srv_addr;
extern struct 	AppMsgData *mptr;
extern struct 	MulInfo *tmpinfo;

/***
�����ַ���ָ������֮��ĳ���
@inparam
				�ַ���
				λ��
@return ����
***/

/**
ȡ�ź���Ϣ
@inparam  
	�źŴ���
@return void
***/
void AlmMsg(int sig)
{
    signal(sig,SIG_IGN);
    signal(sig,AlmMsg);
    longjmp(env,1);
	
	printf("receive the signal ALARM!\n");
    return ;
}



/******************************************************************
*
* ����Return_Message�Ĵ洢�ռ���СΪ30���ֽڣ����ڴ洢���������Ϣ��
* ����InCmdText�ĳ��ȱ���С��2048���ֽڳ��ȣ�
* ���ش�����䣺
* �����������1��10�� socketͨ�Ŵ���11��20�� �����ɹ����أ�0
*
@inparam
		IP��ַ
		�˿�
		��������
		ָ�����
		����ͷ
@outparam
		������Ϣ
@return
    �����������1��10�� socketͨ�Ŵ���11��20�� �����ɹ����أ�0
******************************************************************/
int pubScpSend (char *IpAddr, int InPort, char *InOp_Code,char *InCmdText,char *Return_Message)
{
    int msglen;
    printf("********************IpAddr=[%s]\n",IpAddr) ;
    printf("********************InPort=[%d]\n",InPort) ;
    printf("********************InCmdText=[%s]\n",InCmdText) ;
    
    if (IpAddr==NULL || InOp_Code==NULL || InCmdText==NULL)
    	return 1;
    if (InPort<1024)
    	return 2;

	printf("InOp_code==%s[%s]\n",InOp_Code,InCmdText);
	printf("call pubScpSend begin......\n");

    sockid=socket(AF_INET,SOCK_STREAM,0);
    if(sockid<0)
    {
        sprintf(Return_Message,"socket() failed[%d]!\0",errno);
        return 11;
    }
   
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_family=AF_INET;
    srv_addr.sin_addr.s_addr=inet_addr(IpAddr);
    srv_addr.sin_port=htons(InPort);

    if(connect(sockid,(struct sockaddr *)&srv_addr,sizeof(srv_addr))<0)
    {
    	printf("+++++++++++++++++ֻ�ǵ���\n");
        sprintf(Return_Message,"connect() failed[%d]!\0",errno);
        close(sockid);
        return 12;
    }

    msglen=strlen(InCmdText);

    printf("��163�������͵��ַ���������:InCmdText=[%s]\n",InCmdText);
    if(write(sockid,InCmdText,msglen)!=msglen)
    {
        sprintf(Return_Message,"��SCP��������ʧ��[%d]!",errno);
        close(sockid);
        return 13;
    }
    
    strcpy(Return_Message, "��SCP��������ɹ�!");
    printf("sockid = %d, msglen= %d\n", sockid, msglen);
    printf("call pubScpSend end......\n");
    return 0;    
}


/******************************************************************
*
* �����β��������������������InfoHead��������������������ͷ�ڵ㣻
* �����β������������ݷ��ض����β����ֲ��������������������������
* ���Բ���BackInfoHeadΪͷ�ڵ�������У�����BackInfoHead����Ϊ�գ�
* ����ñ������ĳ�����Ҫ�����ͷŸ�����ռ�;
* ���ش�����䣺
@inparam
				��������
				�������ͷ
@outparam
				���ش���ͷ
				������Ϣ
@return  �����������С��0�� ��ʱ��-100������ִ�гɹ������ڵ���0
******************************************************************/
/*int pubSmapBack(const char *InOpCode,struct MulInfo *InfoHead,
struct MulInfo *BackInfoHead,char *return_msg )
{
return 0;
}*/

int pubScpBack(const char *InOpCode,char *BackInfo,char *return_msg )
{
    int mlen;
    int delay=0;
    char vBack_Code[8];
        
    printf("call publicScpBack begin......\n");
    printf("sockid = %d\n", sockid);
    if (InOpCode==NULL)
    {
    	strcpy(return_msg, "�����������\n");
    	return -1;
    }
   /* delay = getDelayTime(InOpCode);    
    if (delay==-1)
    {
    	printf("getDelayTime�������������!\n");
    	strcpy(return_msg, "�����������");
    	return -2;
    }
    if (delay==-2)
    {
    	printf("getDelayTime����ִ�д���!\n");
    	strcpy(return_msg, "getDelayTime����ִ�д���");
    	return -3;
    }*/
    
    alarm(0);
    signal(SIGALRM, AlmMsg);
    alarm(delay);
    if (setjmp(env)!=0)
    {
    	printf("����������������Ϣ��ʱ!\n");
    	strcpy(return_msg, "����������������Ϣ��ʱ");
    	alarm(0);
    	return -100;
    }
	
		memset(clibuf, 0, sizeof(clibuf));
    mlen=read(sockid,clibuf,1024);
    if(mlen<=0)
    {
        strcpy(return_msg,"ͨ��ʧ��");
        close(sockid);
        alarm(0);
        return -4;
    }  
		printf("recv: %s\n", clibuf);  
		strcpy(BackInfo,clibuf);  
    printf("call publicScpBack end, mlen=[%d]\n", mlen);
		close(sockid);
		alarm(0);
    return mlen;
}

