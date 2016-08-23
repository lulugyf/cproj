/**
 *     消息队列管理
 */
#include "libsys.h"

namespace NSPrime
{
#ifndef __WIN__
	const long int CLMsgQueue::m_iMsgType;
	const long int CLMsgQueue::MSGQUEUE_NOMSG;
#endif

	CLMsgQueue::CLMsgQueue(int iMsgSize)
	{
		m_iMsgSize = iMsgSize;
		m_bIsInitial = false;
		m_tRecvQueueHandle = (TMsgQueue)NULL;
		m_tSendQueueHandle = (TMsgQueue)NULL;
#ifdef __WIN__
		m_ptWinQueueBuff = NULL;
		m_iWinQueueBuffSize = 0;
#else
		m_ptUnixQueueBuff = NULL;
		m_iUnixQueueBuffSize = 0;
#endif
		m_bSuccRecv = false;
	}

	CLMsgQueue::~CLMsgQueue()
	{
		Destroy();
	}

#ifdef __WIN__
	//windows的消息回调函数
	LRESULT CALLBACK MsgQueueWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_COPYDATA)
		{
			CLMsgQueue *ptMsgQueue = (CLMsgQueue *)GetProp(hWnd, "this");
			memcpy(ptMsgQueue->m_ptWinQueueBuff, ((COPYDATASTRUCT*)lParam)->lpData, ptMsgQueue->m_iMsgSize);
			ptMsgQueue->m_bSuccRecv = true;
			PostQuitMessage(0);
		}
		else
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}
#endif

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
	 * <returns>
	 *     0:成功;
	 *     其他:创建服务器消息队列失败。
	 * </returns>
	 * <remarks>一个CLMsgQueue类只能创建消息队列一次，否则返回错误-1。</remarks>
	 */
	ETYPE CLMsgQueue::Create(const char *psLocalQueueName, unsigned long lProtectAttr, int iMsgProjectId, bool bNewMq)
	{
		ETYPE iRet = 0;

		if (m_bIsInitial)
		{
			return -1;
		}
#ifdef __WIN__
		m_iWinQueueBuffSize = sizeof(TWinQueueBuff) - 1 + m_iMsgSize;
		if (m_iMsgSize > 0)
		{
			if (m_ptWinQueueBuff == NULL)
			{
				m_ptWinQueueBuff = (TWinQueueBuff*)malloc(m_iWinQueueBuffSize);
			}
			memset(m_ptWinQueueBuff, 0, m_iWinQueueBuffSize);
		}
		else
		{
			if (m_ptWinQueueBuff)
			{
				free(m_ptWinQueueBuff);
				m_ptWinQueueBuff = NULL;
			}
			return 1;
		}

		//注册窗口类
		WNDCLASSEX wcex;
		memset(&wcex, 0, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.lpfnWndProc = (WNDPROC)MsgQueueWndProc;
		wcex.lpszClassName = psLocalQueueName;  //名字必须唯一
		RegisterClassEx(&wcex);

		//创建一个消息窗口
		if ((m_tRecvQueueHandle = CreateWindow(psLocalQueueName, NULL, 
			0, 0, 0, 0, 0, (HWND)HWND_MESSAGE, NULL, NULL, NULL)) == NULL)
		{
			return GetLastError();
		}
		SetProp(m_tRecvQueueHandle, "this", (HANDLE)this);
#else
		m_iUnixQueueBuffSize = sizeof(TUnixQueueBuff) - 1 + m_iMsgSize;
		if (m_iMsgSize > 0)
		{
			if (m_ptUnixQueueBuff == NULL)
			{
				m_ptUnixQueueBuff = (TUnixQueueBuff*)malloc(m_iUnixQueueBuffSize);
			}
			memset(m_ptUnixQueueBuff, 0, m_iUnixQueueBuffSize);
		}
		else
		{
			if (m_ptUnixQueueBuff)
			{
				free(m_ptUnixQueueBuff);
				m_ptUnixQueueBuff = NULL;
			}
			return 1;
		}

		key_t iKeyId;
		
		//调用CLShm类的静态成员函数GetKeyId，得到路径ID。
		if ((iRet = CLShm::GetKeyId(psLocalQueueName, iMsgProjectId, iKeyId)) != 0)
		{
			return iRet;
		}

		//判断是否重新建立一个全新的队列
		if (bNewMq)
		{
			if ((m_tRecvQueueHandle = msgget(iKeyId, 0)) != -1)
			{
				//    如果消息队列已经存在，则删除消息队列重新建立，主要目的是清空原
				//来上次进程启动中，没有处理完成的消息队列中的消息。
				msgctl(m_tRecvQueueHandle, IPC_RMID, 0);
				m_tRecvQueueHandle = (TMsgQueue)0;
			}

			if ((m_tRecvQueueHandle = msgget(iKeyId, lProtectAttr|IPC_CREAT|IPC_EXCL)) == -1)
			{
				return errno;
			}
		}
		else
		{
			if ((m_tRecvQueueHandle = msgget(iKeyId, lProtectAttr|IPC_CREAT)) == -1)
			{
				return errno;
			}
		}
#endif
		m_bIsInitial = true;

		return 0;
	}

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
	ETYPE CLMsgQueue::FindConn(const char *psServerQueueName, int iShmProjectId)
	{
		ETYPE iRet = 0;

#ifdef __WIN__
		if ( (m_tSendQueueHandle = (TMsgQueue)FindWindow(psServerQueueName, NULL)) == NULL)
		{
			return 1;
		}
#else
		key_t iKeyId;
		
		//调用CLShm类的静态成员函数GetKeyId，得到路径ID。
		if ((iRet = CLShm::GetKeyId(psServerQueueName, iShmProjectId, iKeyId)) != 0)
		{
			return iRet;
		}

		if ((m_tSendQueueHandle = msgget(iKeyId, 0)) == -1)
		{
			return errno;
		}
#endif
		return 0;
	}

	/**
	 * <summary>删除Create函数创建的消息队列</summary>
	 * <remarks>
	 *       保证多次调用Destroy函数不会出现问题。
	 *       windows调用DestroyWindow函数销毁此消息队列。
	 *       对于UNIX会调用msgctl函数清理此消息队列。
	 * </remarks>
	 */
	void CLMsgQueue::Destroy()
	{
#ifdef __WIN__
		if (m_tRecvQueueHandle)
		{
			DestroyWindow(m_tRecvQueueHandle);
		}
		if (m_ptWinQueueBuff)
		{
			free(m_ptWinQueueBuff);
			m_ptWinQueueBuff = NULL;
		}
#else
		if (m_tRecvQueueHandle)
		{
			msgctl(m_tRecvQueueHandle, IPC_RMID, 0);
			m_tRecvQueueHandle = (TMsgQueue)0;
		}

		if (m_ptUnixQueueBuff)
		{
			free(m_ptUnixQueueBuff);
			m_ptUnixQueueBuff = NULL;
		}
#endif
		m_tSendQueueHandle = NULL;
		m_bIsInitial = false;
	}

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
	ETYPE CLMsgQueue::Send(void *pvMsg, size_t iMsgLen, int iMsgFlag)
	{
		//消息人本的长度不能小于1
		if (iMsgLen < 1)
		{
			return 1;
		}

		if (m_tSendQueueHandle == (TMsgQueue)NULL)
		{
			return 2;
		}

		if (!m_bIsInitial)
		{
			return 3;
		}

		ETYPE iRet = 0;

		if (iMsgLen > m_iMsgSize)
		{
			iMsgLen = m_iMsgSize;
		}

#ifdef __WIN__
		memset(m_ptWinQueueBuff, 0, m_iWinQueueBuffSize);
		memcpy(m_ptWinQueueBuff->sMsgText, pvMsg, iMsgLen);

		COPYDATASTRUCT cs;
		cs.cbData = (DWORD)m_iMsgSize;
		cs.lpData = m_ptWinQueueBuff->sMsgText;
		SendMessage(m_tSendQueueHandle, WM_COPYDATA, reinterpret_cast<WPARAM>(m_tRecvQueueHandle), reinterpret_cast<LPARAM>(&cs));
#else
		memset(m_ptUnixQueueBuff, 0, m_iUnixQueueBuffSize);
		m_ptUnixQueueBuff->iMsgType = m_iMsgType;
		memcpy(m_ptUnixQueueBuff->sMsgText, pvMsg, iMsgLen);
		if (msgsnd(m_tSendQueueHandle, (const void*)m_ptUnixQueueBuff, m_iMsgSize, iMsgFlag) == -1)
		{
			iRet = errno;
		}
#endif
		return iRet;
	}

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
	ETYPE CLMsgQueue::Recv(void *pvMsg, size_t iMsgLen, int iMsgFlag)
	{
		if (!m_bIsInitial)
		{
			return 3;
		}

		ETYPE iRet = 0;

		m_bSuccRecv = false;
#ifdef __WIN__
		//处理消息循环
		MSG msg;
		while(GetMessage(&msg, NULL, 0, 0))
		{
			//WM_QUIT消息GetMessage函数返回0，会中断此循环，其他消息返回非0值。
			DispatchMessage(&msg);
		}
		if (!m_bSuccRecv)
		{
			iRet = MSGQUEUE_NOMSG;//表示没有消息
		}
#else
		memset(m_ptUnixQueueBuff, 0, m_iUnixQueueBuffSize);
		m_ptUnixQueueBuff->iMsgType = m_iMsgType;
		if ((msgrcv(m_tRecvQueueHandle, (void*)m_ptUnixQueueBuff, m_iMsgSize, m_iMsgType, iMsgFlag)) == -1)
		{
			iRet = errno;
		}
		m_bSuccRecv = true;
#endif

		if (m_bSuccRecv)
		{
			if (iMsgLen > m_iMsgSize)
			{
				iMsgLen = m_iMsgSize;
			}

			if (pvMsg != NULL)
			{
				memcpy(pvMsg, GetQueueBuff(), iMsgLen);
			}
		}
		return iRet;
	}
#ifndef __WIN__
	/**
	 * <summary>删除一个已经存在的消息队列，此函数只给UNIX使用。</summary>
	 * <inparam name="psMsgQueueName" type="const char*">
	 *       消息队列的名称。windows通过此变量此变量来标识此共享。UNIX通过此变量
	 *   来计算共享内存键值。
	 * </inparam>
	 * <inparam name="iShmProjectId" type="int">在UNIX版本下的ftok函数中会用到</inparam>
	 */
	ETYPE CLMsgQueue::RmMq(const char* psMsgQueueName, int iShmProjectId)
	{
		ETYPE iRet = 0; 
		key_t iKeyId;
		if ((iRet = CLShm::GetKeyId(psMsgQueueName, iShmProjectId, iKeyId)) != 0)
		{
			return iRet;
		}

		TMsgQueue tMqHandle;			//消息队列的句柄
		if ((tMqHandle = msgget(iKeyId, 0)) == -1)
		{
			return errno;
		}

		if (tMqHandle)
		{
			msgctl(tMqHandle, IPC_RMID, 0);
			tMqHandle = (TMsgQueue)0;
		}
		return 0;
	}
#endif
}
