/**
 *     消息队列管理
 */

#pragma once

#ifdef __WIN__
#else
#include <sys/msg.h>
#endif

namespace NSPrime
{
#ifdef __WIN__
	typedef HWND TMsgQueue;
#else
	typedef int TMsgQueue;
#endif

#ifdef __WIN__
	//Win的消息结构体
	typedef struct tagWinQueueBuff {
		char sMsgText[1];
	}TWinQueueBuff;
#else
	//UNIX的消息结构体
	typedef struct tagUnixQueueBuff {
		long   iMsgType;
		char   sMsgText[1];
	}TUnixQueueBuff;
#endif

	//共享内存的信息
	class CLMsgQueue
	{
	public:
		CLMsgQueue(int iMsgSize);
		~CLMsgQueue();
	public:		
		/**
		 *  <summary>创建一个本地用于接收的消息队列。</summary>
		 * <inparam name="psLocalQueueName" type="const char*">
		 *      本地消息队列的名称。对于windows就是窗口类的名字；对于UNIX就是真实的路径名字。
		 * <inparam name="lProtectAttr" type="unsigned long">
		 *       访问此共享内存的保护属性。
		 *   由于windows使用窗口消息的机制，所以不需要此属性，可以设置成默认值0；
		 *   UNIX可以设置为“0660”
		 * </inparam>
		 * <inparam name="iMsgProjectId" type="int">在UNIX版本下的ftok函数中会用到，windows下可传入0，无意义</inparam>
		 * <inparam name="bNewMq" type="bool">
		 *      是否重新建立一个全新的队列，默认值为true。
		 *      在UNIX版本下，会删除已经存在的消息队列重新建立。
		 *      在windows可传入true，无意义
		 * </inparam>
		 * <remarks>一个CLMsgQueue类只能创建消息队列一次，否则返回错误-1。</remarks>
		 */
		ETYPE Create(const char *psLocalQueueName, unsigned long lProtectAttr, int iMsgProjectId, bool bNewMq = true);

		/**
		 * <summary>删除Create函数创建的消息队列</summary>
		 * <remarks>
		 *       保证多次调用Destroy函数不会出现问题。
		 *       windows调用DestroyWindow函数销毁此消息队列。
		 *       对于UNIX会调用msgctl函数清理此消息队列。
		 * </remarks>
		 */
		void Destroy();

		/**
		 *  <summary>查询并得到服务器端的消息队列。</summary>
		 * <inparam name="psServerQueueName" type="const char*">
		 *      服务器端消息队列的名称。对于windows就是窗口类的名字；对于UNIX就是真实的路径名字。
		 * <inparam name="iShmProjectId" type="int">在UNIX版本下的ftok函数中会用到，windows下可传入0，无意义</inparam>
		 * <returns>
		 *     0:成功;
		 *     其他:打开服务器消息队列失败。
		 * </returns>
		 * <remarks>客户端使用FindConn打开的服务器消息队列，在客户端不用关闭，由服务器端关闭。</remarks>
		 */
		ETYPE FindConn(const char *psServerQueueName, int iShmProjectId);
		
		/**
		 * <summary>发送消息</summary>
		 * <inparam name="pvMsg" type="const void *">
		 *      指向消息缓冲区的指针。
		 * </inparam>
		 * <inparam name="iMsgLen" type="size_t">
		 *       发送消息的长度，此长度不能大于在m_iMsgSize的长度，否则将被截断。
		 * </inparam>
		 * <inparam name="iMsgFlag" type="int">
		 *      在windows版本下，暂时无意义。
		 *      在UNIX版本下msgsnd函数中会用到，请参考msgsnd，如果iMsgFlag和常数IPC_NOWAIT合用，则在msgsnd()执行时若
		 *  是消息队列已满，则msgsnd()将不会阻塞，而会立即返回-1，如果执行的是
		 *  msgrcv()，则在消息队列呈空时，不做等待马上返回-1，并设定错误码为 ENOMSG。
		 *  当iMsgFlag为0时，msgsnd()及msgrcv()在队列呈满或呈空的情形时，采取阻塞等
		 *  待的处理模式。
		 * </inparam>
		 * <returns>
		 *     0:成功;
		 *     1:长度不能小于1。
		 *     2:服务器端消息队列没有打开。
		 *     3:客户端没有打开。
		 * </returns>
		 * <remarks>
		 *       
		 * </remarks>
		 */
		ETYPE Send(void *pvMsg, size_t iMsgLen, int iMsgFlag);

		/**
		 * <summary>接收消息</summary>
		 * <inparam name="pvMsg" type="const void *">
		 *      指向返回消息缓冲区的指针。
		 * </inparam>
		 * <inparam name="iMsgLen" type="size_t">
		 *       返回消息的长度，此长度不能大于在m_iMsgSize的长度，否则只是返回m_iMsgSize长度的内部。
		 * </inparam>
		 * <inparam name="iMsgFlag" type="int">
		 *      在windows版本下，无意义。
		 *      在UNIX版本下msgsnd函数中会用到，请参考msgsnd，如果iMsgFlag和常数IPC_NOWAIT合用，则在msgsnd()执行时若
		 *  是消息队列已满，则msgsnd()将不会阻塞，而会立即返回-1，如果执行的是
		 *  msgrcv()，则在消息队列呈空时，不做等待马上返回-1，并设定错误码为 ENOMSG。
		 *  当iMsgFlag为0时，msgsnd()及msgrcv()在队列呈满或呈空的情形时，采取阻塞等
		 *  待的处理模式。
		 * </inparam>
		 * <returns>
		 *     0:成功;
		 *     3:客户端没有打开。
		 *     35:ENOMSG，无消息。
		 * </returns>
		 * <remarks>
		 *       无
		 * </remarks>
		 */
		ETYPE Recv(void *pvMsg, size_t iMsgLen, int iMsgFlag);

		const char *GetQueueBuff()
		{
			if (m_bSuccRecv)
			{
#ifdef __WIN__
			return m_ptWinQueueBuff->sMsgText;
#else
			return m_ptUnixQueueBuff->sMsgText;
#endif
			}
			else
			{
				return NULL;
			}
		}
#ifdef __WIN__
		static const long int MSGQUEUE_NOMSG = 35;
#else
		static const long int MSGQUEUE_NOMSG = ENOMSG;
#endif

#ifndef __WIN__
		/**
		 * <summary>删除一个已经存在的消息队列，此函数只给UNIX使用。</summary>
		 * <inparam name="psMsgQueueName" type="const char*">
		 *       消息队列的名称。windows通过此变量此变量来标识此共享。UNIX通过此变量
		 *   来计算共享内存键值。
		 * </inparam>
		 * <inparam name="iShmProjectId" type="int">在UNIX版本下的ftok函数中会用到</inparam>
		 */
		static ETYPE RmMq(const char* psMsgQueueName, int iShmProjectId);
#endif

	private:
		bool m_bIsInitial;				//表明当前的共享消息是否打开或创建成功，一个CLMsgQueue类只能打开或创建一次，不容许重复。
		size_t m_iMsgSize;				//消息文本的长度。

		TMsgQueue m_tRecvQueueHandle;	//当前用于接收的消息队列句柄
		TMsgQueue m_tSendQueueHandle;	//当前用于发送的消息队列句柄
#ifdef __WIN__
		friend LRESULT CALLBACK MsgQueueWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		TWinQueueBuff *m_ptWinQueueBuff;
		size_t m_iWinQueueBuffSize;
#else
		//UNIX的消息结构体
		TUnixQueueBuff *m_ptUnixQueueBuff;
		size_t m_iUnixQueueBuffSize;
		static const long int m_iMsgType = 1;
#endif
		bool m_bSuccRecv;				//是否成功接收到数据。
	};
}
