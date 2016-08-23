#include "smp.h"

extern int 	sockid;
extern char 	clibuf[2080];
extern jmp_buf env;
extern struct 	sockaddr_in srv_addr;
extern struct 	AppMsgData *mptr;
extern struct 	MulInfo *tmpinfo;

/***
计算字符串指定长度之后的长度
@inparam
				字符串
				位数
@return 长度
***/

/**
取信号信息
@inparam  
	信号代码
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
* 参数Return_Message的存储空间最小为30个字节，用于存储操作结果信息；
* 参数InCmdText的长度必须小于2048个字节长度；
* 返回代码分配：
* 输入参数错误：1－10； socket通信错误：11－20； 函数成功返回：0
*
@inparam
		IP地址
		端口
		操作代码
		指令代码
		代码头
@outparam
		返回信息
@return
    输入参数错误：1－10； socket通信错误：11－20； 函数成功返回：0
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
    	printf("+++++++++++++++++只是调试\n");
        sprintf(Return_Message,"connect() failed[%d]!\0",errno);
        close(sockid);
        return 12;
    }

    msglen=strlen(InCmdText);

    printf("向163主机发送的字符串内容是:InCmdText=[%s]\n",InCmdText);
    if(write(sockid,InCmdText,msglen)!=msglen)
    {
        sprintf(Return_Message,"向SCP发送命令失败[%d]!",errno);
        close(sockid);
        return 13;
    }
    
    strcpy(Return_Message, "向SCP发送命令成功!");
    printf("sockid = %d, msglen= %d\n", sockid, msglen);
    printf("call pubScpSend end......\n");
    return 0;    
}


/******************************************************************
*
* 若本次操作是批量操作，则参数InfoHead是批量操作的数据链表头节点；
* 若本次操作有批量数据返回而本次操作又不是批量操作，则批量结果保存
* 在以参数BackInfoHead为头节点的链表中，参数BackInfoHead若不为空，
* 则调用本函数的程序需要负责释放该链表空间;
* 返回代码分配：
@inparam
				操作代码
				输入代码头
@outparam
				返回代码头
				返回信息
@return  函数本身错误：小于0； 超时：-100；函数执行成功：大于等于0
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
    	strcpy(return_msg, "输入参数错误\n");
    	return -1;
    }
   /* delay = getDelayTime(InOpCode);    
    if (delay==-1)
    {
    	printf("getDelayTime，输入参数错误!\n");
    	strcpy(return_msg, "输入参数错误");
    	return -2;
    }
    if (delay==-2)
    {
    	printf("getDelayTime函数执行错误!\n");
    	strcpy(return_msg, "getDelayTime函数执行错误");
    	return -3;
    }*/
    
    alarm(0);
    signal(SIGALRM, AlmMsg);
    alarm(delay);
    if (setjmp(env)!=0)
    {
    	printf("接收智能网返回信息超时!\n");
    	strcpy(return_msg, "接收智能网返回信息超时");
    	alarm(0);
    	return -100;
    }
	
		memset(clibuf, 0, sizeof(clibuf));
    mlen=read(sockid,clibuf,1024);
    if(mlen<=0)
    {
        strcpy(return_msg,"通信失败");
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

