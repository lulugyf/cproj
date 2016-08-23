/**
 *     ��Ϣ���й���
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
	//windows����Ϣ�ص�����
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
	 *  <summary>����һ���������ڽ��յ���Ϣ���С�</summary>
	 * <inparam name="psLocalQueueName" type="const char*">
	 *      ������Ϣ���е����ơ�����windows���Ǵ���������֣�����UNIX������ʵ��·�����֡�
	 * <inparam name="lProtectAttr" type="unsigned long">
	 *       ���ʴ˹����ڴ�ı������ԡ�
	 *   ����windowsʹ�ô�����Ϣ�Ļ��ƣ����Բ���Ҫ�����ԣ��������ó�Ĭ��ֵ0��
	 *   UNIX��������Ϊ��0660��
	 * </inparam>
	 * <inparam name="iMsgProjectId" type="int">��UNIX�汾�µ�ftok�����л��õ���windows�¿ɴ���0��������</inparam>
	 * <inparam name="bNewMq" type="bool">
	 *      �Ƿ����½���һ��ȫ�µĶ��У�Ĭ��ֵΪtrue��
	 *      ��UNIX�汾�£���ɾ���Ѿ����ڵ���Ϣ�������½�����
	 *      ��windows�ɴ���true��������
	 * </inparam>
	 * <returns>
	 *     0:�ɹ�;
	 *     ����:������������Ϣ����ʧ�ܡ�
	 * </returns>
	 * <remarks>һ��CLMsgQueue��ֻ�ܴ�����Ϣ����һ�Σ����򷵻ش���-1��</remarks>
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

		//ע�ᴰ����
		WNDCLASSEX wcex;
		memset(&wcex, 0, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.lpfnWndProc = (WNDPROC)MsgQueueWndProc;
		wcex.lpszClassName = psLocalQueueName;  //���ֱ���Ψһ
		RegisterClassEx(&wcex);

		//����һ����Ϣ����
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
		
		//����CLShm��ľ�̬��Ա����GetKeyId���õ�·��ID��
		if ((iRet = CLShm::GetKeyId(psLocalQueueName, iMsgProjectId, iKeyId)) != 0)
		{
			return iRet;
		}

		//�ж��Ƿ����½���һ��ȫ�µĶ���
		if (bNewMq)
		{
			if ((m_tRecvQueueHandle = msgget(iKeyId, 0)) != -1)
			{
				//    �����Ϣ�����Ѿ����ڣ���ɾ����Ϣ�������½�������ҪĿ�������ԭ
				//���ϴν��������У�û�д�����ɵ���Ϣ�����е���Ϣ��
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
	 *  <summary>��ѯ���õ��������˵���Ϣ���С�</summary>
	 * <inparam name="psServerQueueName" type="const char*">
	 *      ����������Ϣ���е����ơ�����windows���Ǵ���������֣�����UNIX������ʵ��·�����֡�
	 * <inparam name="iShmProjectId" type="int">��UNIX�汾�µ�ftok�����л��õ���windows�¿ɴ���0��������</inparam>
	 * <returns>
	 *     0:�ɹ�;
	 *     ����:�򿪷�������Ϣ����ʧ�ܡ�
	 * </returns>
	 * <remarks>�ͻ���ʹ��FindConn�򿪵ķ�������Ϣ���У��ڿͻ��˲��ùرգ��ɷ������˹رա�</remarks>
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
		
		//����CLShm��ľ�̬��Ա����GetKeyId���õ�·��ID��
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
	 * <summary>ɾ��Create������������Ϣ����</summary>
	 * <remarks>
	 *       ��֤��ε���Destroy��������������⡣
	 *       windows����DestroyWindow�������ٴ���Ϣ���С�
	 *       ����UNIX�����msgctl�����������Ϣ���С�
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
	 * <summary>������Ϣ</summary>
	 * <inparam name="pvMsg" type="const void *">
	 *      ָ����Ϣ��������ָ�롣
	 * </inparam>
	 * <inparam name="iMsgLen" type="size_t">
	 *       ������Ϣ�ĳ��ȣ��˳��Ȳ��ܴ�����m_iMsgSize�ĳ��ȣ����򽫱��ضϡ�
	 * </inparam>
	 * <inparam name="iMsgFlag" type="int">
	 *      ��windows�汾�£���ʱ�����塣
	 *      ��UNIX�汾��msgsnd�����л��õ�����ο�msgsnd�����iMsgFlag�ͳ���IPC_NOWAIT���ã�����msgsnd()ִ��ʱ��
	 *  ����Ϣ������������msgsnd()������������������������-1�����ִ�е���
	 *  msgrcv()��������Ϣ���гʿ�ʱ�������ȴ����Ϸ���-1�����趨������Ϊ ENOMSG��
	 *  ��iMsgFlagΪ0ʱ��msgsnd()��msgrcv()�ڶ��г�����ʿյ�����ʱ����ȡ������
	 *  ���Ĵ���ģʽ��
	 * </inparam>
	 * <returns>
	 *     0:�ɹ�;
	 *     1:���Ȳ���С��1��
	 *     2:����������Ϣ����û�д򿪡�
	 *     3:�ͻ���û�д򿪡�
	 * </returns>
	 * <remarks>
	 *       
	 * </remarks>
	 */
	ETYPE CLMsgQueue::Send(void *pvMsg, size_t iMsgLen, int iMsgFlag)
	{
		//��Ϣ�˱��ĳ��Ȳ���С��1
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
	 * <summary>������Ϣ</summary>
	 * <inparam name="pvMsg" type="const void *">
	 *      ָ�򷵻���Ϣ��������ָ�롣
	 * </inparam>
	 * <inparam name="iMsgLen" type="size_t">
	 *       ������Ϣ�ĳ��ȣ��˳��Ȳ��ܴ�����m_iMsgSize�ĳ��ȣ�����ֻ�Ƿ���m_iMsgSize���ȵ��ڲ���
	 * </inparam>
	 * <inparam name="iMsgFlag" type="int">
	 *      ��windows�汾�£������塣
	 *      ��UNIX�汾��msgsnd�����л��õ�����ο�msgsnd�����iMsgFlag�ͳ���IPC_NOWAIT���ã�����msgsnd()ִ��ʱ��
	 *  ����Ϣ������������msgsnd()������������������������-1�����ִ�е���
	 *  msgrcv()��������Ϣ���гʿ�ʱ�������ȴ����Ϸ���-1�����趨������Ϊ ENOMSG��
	 *  ��iMsgFlagΪ0ʱ��msgsnd()��msgrcv()�ڶ��г�����ʿյ�����ʱ����ȡ������
	 *  ���Ĵ���ģʽ��
	 * </inparam>
	 * <returns>
	 *     0:�ɹ�;
	 *     3:�ͻ���û�д򿪡�
	 *     35:ENOMSG������Ϣ��
	 * </returns>
	 * <remarks>
	 *       ��
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
		//������Ϣѭ��
		MSG msg;
		while(GetMessage(&msg, NULL, 0, 0))
		{
			//WM_QUIT��ϢGetMessage��������0�����жϴ�ѭ����������Ϣ���ط�0ֵ��
			DispatchMessage(&msg);
		}
		if (!m_bSuccRecv)
		{
			iRet = MSGQUEUE_NOMSG;//��ʾû����Ϣ
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
	 * <summary>ɾ��һ���Ѿ����ڵ���Ϣ���У��˺���ֻ��UNIXʹ�á�</summary>
	 * <inparam name="psMsgQueueName" type="const char*">
	 *       ��Ϣ���е����ơ�windowsͨ���˱����˱�������ʶ�˹���UNIXͨ���˱���
	 *   �����㹲���ڴ��ֵ��
	 * </inparam>
	 * <inparam name="iShmProjectId" type="int">��UNIX�汾�µ�ftok�����л��õ�</inparam>
	 */
	ETYPE CLMsgQueue::RmMq(const char* psMsgQueueName, int iShmProjectId)
	{
		ETYPE iRet = 0; 
		key_t iKeyId;
		if ((iRet = CLShm::GetKeyId(psMsgQueueName, iShmProjectId, iKeyId)) != 0)
		{
			return iRet;
		}

		TMsgQueue tMqHandle;			//��Ϣ���еľ��
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
