/**
 *     ��Ϣ���й���
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
	//Win����Ϣ�ṹ��
	typedef struct tagWinQueueBuff {
		char sMsgText[1];
	}TWinQueueBuff;
#else
	//UNIX����Ϣ�ṹ��
	typedef struct tagUnixQueueBuff {
		long   iMsgType;
		char   sMsgText[1];
	}TUnixQueueBuff;
#endif

	//�����ڴ����Ϣ
	class CLMsgQueue
	{
	public:
		CLMsgQueue(int iMsgSize);
		~CLMsgQueue();
	public:		
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
		 * <remarks>һ��CLMsgQueue��ֻ�ܴ�����Ϣ����һ�Σ����򷵻ش���-1��</remarks>
		 */
		ETYPE Create(const char *psLocalQueueName, unsigned long lProtectAttr, int iMsgProjectId, bool bNewMq = true);

		/**
		 * <summary>ɾ��Create������������Ϣ����</summary>
		 * <remarks>
		 *       ��֤��ε���Destroy��������������⡣
		 *       windows����DestroyWindow�������ٴ���Ϣ���С�
		 *       ����UNIX�����msgctl�����������Ϣ���С�
		 * </remarks>
		 */
		void Destroy();

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
		ETYPE FindConn(const char *psServerQueueName, int iShmProjectId);
		
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
		ETYPE Send(void *pvMsg, size_t iMsgLen, int iMsgFlag);

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
		 * <summary>ɾ��һ���Ѿ����ڵ���Ϣ���У��˺���ֻ��UNIXʹ�á�</summary>
		 * <inparam name="psMsgQueueName" type="const char*">
		 *       ��Ϣ���е����ơ�windowsͨ���˱����˱�������ʶ�˹���UNIXͨ���˱���
		 *   �����㹲���ڴ��ֵ��
		 * </inparam>
		 * <inparam name="iShmProjectId" type="int">��UNIX�汾�µ�ftok�����л��õ�</inparam>
		 */
		static ETYPE RmMq(const char* psMsgQueueName, int iShmProjectId);
#endif

	private:
		bool m_bIsInitial;				//������ǰ�Ĺ�����Ϣ�Ƿ�򿪻򴴽��ɹ���һ��CLMsgQueue��ֻ�ܴ򿪻򴴽�һ�Σ��������ظ���
		size_t m_iMsgSize;				//��Ϣ�ı��ĳ��ȡ�

		TMsgQueue m_tRecvQueueHandle;	//��ǰ���ڽ��յ���Ϣ���о��
		TMsgQueue m_tSendQueueHandle;	//��ǰ���ڷ��͵���Ϣ���о��
#ifdef __WIN__
		friend LRESULT CALLBACK MsgQueueWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		TWinQueueBuff *m_ptWinQueueBuff;
		size_t m_iWinQueueBuffSize;
#else
		//UNIX����Ϣ�ṹ��
		TUnixQueueBuff *m_ptUnixQueueBuff;
		size_t m_iUnixQueueBuffSize;
		static const long int m_iMsgType = 1;
#endif
		bool m_bSuccRecv;				//�Ƿ�ɹ����յ����ݡ�
	};
}
