#include "smp.h"

int 	sockid;
char 	clibuf[2080];
jmp_buf env;
struct 	sockaddr_in srv_addr;
struct 	AppMsgData *mptr;
struct 	MulInfo *tmpinfo;

/***
�����ַ���ָ������֮��ĳ��� 
@inparam
				�ַ���
				λ��
@return ����
***/


extern void AlmMsg(int sig);



int axtoi(char *s,int len)
{
    int i,dest;

    dest=0;
    for(i=0;i<len;i++)
    {
        if(s[i]>='0' && s[i]<='9')
            dest=dest*10+s[i]-'0';
        else
            break;
    }

    return dest;
}


/**
ȡ�ź���Ϣ
@inparam  
	�źŴ���
@return void
***/

/*-----------------------------------
void AlmMsg(int sig)
{
    signal(sig,SIG_IGN);
    signal(sig,AlmMsg);
    longjmp(env,1);
	
	printf("receive the signal ALARM!\n");
    return ;
}
-------------------------------------*/

/*
ͨѶ��������
liyp mod for make
*/

int
readnet( int sockid,register char *ptr, short nbytes) 
{
    int nleft,nread;

    nleft=nbytes;
    while(nleft > 0) 
    {
        nread = read(sockid,ptr,nleft);
		printf("read:%s~\n",ptr);
        if (nread <= 0 ) 
        {
                printf("SMAP:read(%d,%x,%d)==%d,[errno=%d]\n",\
                        sockid,ptr,nleft,nread,errno);
                close(sockid);
                return (nread);
        }

        nleft -=nread;
        ptr +=nread;
    }

    return nbytes-nleft;
}
/******************************************************************
*
* �������ļ�sSmapDelay.cfg��ȡ��ָ��ҵ�����ʱʱ�䣬��û�и�ҵ���
* ������Ϣ������ʱʱ��Ĭ��ֵΪ20�룻
* ���ش�����䣺
* �����������-1�� ϵͳ����-2�� �����ɹ����أ�����0��ֵ
*
@inparam
		��������
@return
    �����������-1�� ϵͳ����-2�� �����ɹ����أ�����0��ֵ 
******************************************************************/



int getDelayTime(const char *InOpCode)
{
	FILE	*fp=NULL;
	char	cfgfilename[256];
	char	linebuf[100];
	char	vOpCode[10];
	char	vDelayTime[10];
	int		delay=20;
	
	if (InOpCode==NULL)
		return -1;
		
	memset(cfgfilename, 0, sizeof(cfgfilename));
	memset(linebuf, 0, sizeof(linebuf));
	memset(vOpCode, 0, sizeof(vOpCode));
	memset(vDelayTime, 0, sizeof(vDelayTime));
		
	sprintf(cfgfilename, "%s/cfg/sSmapDelay.cfg", getenv("WORKDIR"));
	fp = fopen(cfgfilename, "r");
	if (fp==NULL)
	{
		printf("fopen sSmapDelay.cfg failed, errno=[%d]!\n", errno);
		return -2;
	}
	
	while (fgets(linebuf, sizeof(linebuf), fp))
	{
		if (linebuf[0]=='#')
			continue;
		
		sscanf(linebuf, "%s%s", vOpCode, vDelayTime);
		if (strncmp(InOpCode, vOpCode, strlen(InOpCode))==0)
		{
			delay = atoi(vDelayTime);
			break;
		}
		
		memset(linebuf, 0, sizeof(linebuf));
		memset(vOpCode, 0, sizeof(vOpCode));
		memset(vDelayTime, 0, sizeof(vDelayTime));
	}
	fclose(fp);
	if (delay==0)
		delay = 20;
	
	printf("getDelayTime, delay = [%d]\n", delay);
	return delay;	
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
int pubSmapSend (char *IpAddr, int InPort, char *InOp_Code,char *InCmdText,struct MulInfo *InfoHead,char *Return_Message)
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
	printf("call pubSmapSend begin......\n");

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
        sprintf(Return_Message,"connect() failed[%d]!\0",errno);
        close(sockid);
        return 12;
    }

    msglen=strlen(InCmdText);
    mptr=(struct AppMsgData *)clibuf;
    memcpy(mptr->msgflag,"`AM`",4);
    sprintf(mptr->msglen,"%04d",msglen);
    memcpy(mptr->version,"100",3);
    mptr->msgtype=BASEPACKAGE;
	if(InfoHead != NULL)
    	mptr->finished='0';   /** ���к����� **/
    else
    	mptr->finished='1';   /** û�к����� **/
    memcpy(mptr->waitsend,"050",3);
    strcpy(mptr->opcode,InOp_Code);
    memcpy(mptr->retncode,"0000",4);
    memcpy(mptr->reserve,"        ",8);
    strcpy(mptr->sendmsg,InCmdText);

    msglen+=32;
    if(write(sockid,clibuf,msglen)!=msglen)
    {
        sprintf(Return_Message,"��SMAP��������ʧ��[%d]!",errno);
        close(sockid);
        return 13;
    }

	if(InfoHead != NULL)
    {
    	tmpinfo = InfoHead;
    	while(tmpinfo->next)
    	{
    		memset(clibuf, 0, sizeof(clibuf));
    		msglen=0;
    		msglen=strlen(tmpinfo->next->info);
    		mptr=(struct AppMsgData *)clibuf;
    		memcpy(mptr->msgflag,"`AM`",4);
    		sprintf(mptr->msglen,"%04d",msglen);
    		memcpy(mptr->version,"100",3);
    		mptr->msgtype=INFOPACKAGE;
    		if(tmpinfo->next->next != NULL)
    			mptr->finished='0';   /** ���к����� **/
    		else
    			mptr->finished='1';   /** û�к����� **/
    		memcpy(mptr->waitsend,"050",3);
    		strcpy(mptr->opcode,InOp_Code);
    		memcpy(mptr->retncode,"0000",4);
    		memcpy(mptr->reserve,"        ",8);
    		strcpy(mptr->sendmsg,tmpinfo->next->info);
    		
    		msglen+=32;
    		if(write(sockid,clibuf,msglen)!=msglen)
    		{
    		    sprintf(Return_Message,"��SMAP��������ʧ��[%d]!",errno);
    		    close(sockid);
    		    return 14;
    		}
    		
    		tmpinfo = tmpinfo->next;
    	}	
    }
    
    strcpy(Return_Message, "��SMAP��������ɹ�!");
    printf("sockid = %d, msglen= %d\n", sockid, msglen);
    printf("call pubSmapSend end......\n");
    return 0;    
}

/**
 * ��������������ԣ�����ָ�����ǰ��pubSmapSend_20060808�ָ�
 */
/*int pubSmapSend (char *IpAddr, int InPort, char *InOp_Code,char *InCmdText,struct MulInfo *InfoHead,char *Return_Message)
{
	printf("begin execute the function pubSmapSend\n");
    printf("call pubSmapSend end......\n");
    return 0;    
}*/

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

int pubSmapBack(const char *InOpCode,struct MulInfo *InfoHead,struct MulInfo *BackInfoHead,char *return_msg )
{
    int mlen;
    int delay=0;
    char vBack_Code[8];
        
    printf("call publicSmapBack begin......\n");
    printf("sockid = %d\n", sockid);
    
    if (InOpCode==NULL)
    {
    	strcpy(return_msg, "�����������\n");
    	return -1;
    }
    printf("sockid = 111111111111111111111111\n");	
    delay = getDelayTime(InOpCode);    
    if (delay==-1)
    {
    	printf("getDelayTime�������������!\n");
    	strcpy(return_msg, "�����������");
    	return -2;
    }
     printf("sockid = 222222222222222222222222222\n");	
    if (delay==-2)
    {
    	printf("getDelayTime����ִ�д���!\n");
    	strcpy(return_msg, "getDelayTime����ִ�д���");
    	return -3;
    }
    
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
    mptr=(struct AppMsgData *)clibuf;
    mlen=readnet(sockid,clibuf,8);
    if(mlen<=0)
    {
        strcpy(return_msg,"ͨ��ʧ��");
        close(sockid);
        alarm(0);
        return -4;
    }      

    mlen=axtoi(clibuf+4,4);
    mlen=readnet(sockid,clibuf+8,mlen-8);
    if(mlen<=0)
    {
        strcpy(return_msg,"ͨ��ʧ��");
        close(sockid);
        alarm(0);
        return -5;
    }

	printf("recv: %s\n", clibuf);

    memset(vBack_Code, 0, sizeof(vBack_Code));
    memcpy(vBack_Code,mptr->retncode,4);   
    
    while (mptr->finished == '0') /* �к����� */
    {
    	if (InfoHead==NULL)  /** �������������ķ��� **/
    	{
    		tmpinfo = (struct MulInfo *)malloc(sizeof(struct MulInfo));
    		memset(tmpinfo, 0, sizeof(struct MulInfo));
    		strcpy(tmpinfo->retn, "0000");
    		    		
    		if ( strlen(mptr->sendmsg) > sizeof(tmpinfo->info))
    		{
    			strncpy(tmpinfo->info, mptr->sendmsg, sizeof(tmpinfo->info)-1);
    		}
    		else
    		{
    			strncpy(tmpinfo->info, mptr->sendmsg, strlen(mptr->sendmsg));
    		}
    		
    		tmpinfo->next = BackInfoHead->next;
    		BackInfoHead->next = tmpinfo;    		
    	}
    	else   /** �����������ķ��� **/
    	{
    		tmpinfo = InfoHead->next;
    		while( tmpinfo )
    		{
    			if (memcmp(tmpinfo->info, mptr->sendmsg, strlen(tmpinfo->info))==0)
    			{
    				strncpy(tmpinfo->retn, vBack_Code, sizeof(tmpinfo->retn));
    				break;
    			}
    			else
    				tmpinfo = tmpinfo->next;
    		}
    	}
    	    	
    	memset(clibuf, 0, sizeof(clibuf));
    	mptr=(struct AppMsgData *)clibuf;
    	mlen=readnet(sockid,clibuf,8);
    	if(mlen<=0)
    	{
    	    strcpy(return_msg,"ͨ��ʧ��");
    	    close(sockid);
    	    alarm(0);
    	    return -6;
    	}
    	    	
    	mlen=axtoi(clibuf+4,4);
    	mlen=readnet(sockid,clibuf+8,mlen-8);
    	if(mlen<=0)
    	{
    	    strcpy(return_msg,"ͨ��ʧ��");
    	    close(sockid);
    	    alarm(0);
    	    return -7;
    	}
    	
		printf("while recv: %s\n", clibuf);
    	
    	memset(vBack_Code, 0, sizeof(vBack_Code));
    	memcpy(vBack_Code,mptr->retncode,4);       
    		
    } /* ������������� */
        
    if (mptr->finished == '1')  /* û�к����� */
    {    	
        strcpy(return_msg, mptr->sendmsg); 
        memset(vBack_Code, 0, sizeof(vBack_Code));
    	memcpy(vBack_Code,mptr->retncode,4);            	    	
    }        
      
    printf("call publicSmapBack end, vBack_Code=[%s]\n", vBack_Code);
	close(sockid);
	alarm(0);

    return atoi(vBack_Code);
}

/*
main(int argc,char **argv)
{
    int 	ret;
    char 	Return_Message[2080];
    struct 	MulInfo BackInfoHead;
    struct 	MulInfo *tmpP, *ptr;

    if(argc!=3 || strlen(argv[1])!=4)
    {
        printf("\n\nUsage:%s op_code op_text\n\n\n",argv[0]);
        exit(1);
    }

	memset(Return_Message, 0, sizeof(Return_Message));
	
    ret=pubSmapSend("10.105.2.184", 9998, argv[1],argv[2], NULL,Return_Message);
    if(ret)
        printf("pubSmapSend() faield[%s]\n",Return_Message);


	memset(&BackInfoHead, 0, sizeof(struct MulInfo ));
    BackInfoHead.next = NULL;
    ret=pubSmapBack(argv[1],NULL,&BackInfoHead,Return_Message);
    if(ret)
        printf("publicSmapBack() failed, return_msg=[%s], ret=[%d]\n",Return_Message, ret);
    else
        printf("SUCCESS, ret=[%d]!\n", ret);
    printf("Return_Message=[%s]\n", Return_Message);
    
    tmpP = BackInfoHead.next;
    while(tmpP)
    {
    	printf("tmpP->info=[%s]\n", tmpP->info);
    	ptr = tmpP;
    	tmpP = tmpP->next;
    	free(ptr);
    }
}
*/

