/**
 *     �����ڴ����
 */

#pragma once

namespace NSPrime
{
#ifdef __WIN__
	typedef HANDLE TShm;
#else
	typedef int TShm;
#endif

	//�����ڴ����Ϣ
	class CLShm
	{
	public:
		CLShm();
		~CLShm();
	public:
		/**
		 * <summary>
		 *     ����һ�������ڴ棬����Ѿ����ڣ��򷵻�ԭ���Ѿ������Ĺ����ڴ漰��С��
		 *  windows���Բο�CreateFileMapping������
		 * <inparam name="psShmName" type="const char*">
		 *       �����ڴ�����ơ�windowsͨ���˱����˱�������ʶ�˹���UNIXͨ���˱���
		 *   �����㹲���ڴ��ֵ��
		 * </inparam>
		 * <inparam name="iShmSize" type="unsigned int">�����Ĺ����ڴ��С</inparam>
		 * <inparam name="lProtectAttr" type="unsigned long">
		 *       ���ʴ˹����ڴ�ı������ԡ�
		 *   ��window��������ΪPAGE_READWRITE��UNIX��������Ϊ��0660��
		 * </inparam>
		 * <inparam name="iShmProjectId" type="int">��UNIX�汾�µ�ftok�����л��õ���windows�¿ɴ���0��������</inparam>
		 * <remarks>һ��CLShm��ֻ�ܴ��������ڴ�һ�Σ����򷵻ش���-1��</remarks>
		 */
		ETYPE CreateShm(const char* psShmName, unsigned int iShmSize, unsigned long lProtectAttr, int iShmProjectId);

		/**
		 * <summary>��һ�������ڴ棬windows���Բο�OpenFileMapping������</summary>
		 * <inparam name="psShmName" type="const char*">
		 *       �����ڴ�����ơ�windowsͨ���˱����˱�������ʶ�˹���UNIXͨ���˱���
		 *   �����㹲���ڴ��ֵ��
		 * </inparam>
		 * <inparam name="iShmSize" type="unsigned int">
		 *       iShmSize�Ǹù���洢�ε���Сֵ��������ڴ���һ���¶Σ�һ���ڷ�����
		 *   �У��������ָ����iShmSize��������ڴ��һ���ִ�ĶΣ�һ���ͻ���������
		 *   ��iShmSizeָ��Ϊ0����ʾ�������鹲���ڴ档
		 * </inparam>
		 * <inparam name="iShmProjectId" type="int">��UNIX�汾�µ�ftok�����л��õ���windows�¿ɴ���0��������</inparam>
		 * <remarks>һ��CLShm��ֻ�ܴ��������ڴ�һ�Σ����򷵻ش���-1��</remarks>
		 */
		ETYPE OpenShm(const char* psShmName, unsigned int iShmSize, int iShmProjectId);

		/**
		 * <summary>�ر�OpenShm�����򿪵Ĺ����ڴ档</summary>
		 * <remarks>
		 *       ��֤��ε���CloseShm��������������⡣
		 *       windows�Ų������ü����ĸ���ɾ���ں˶������Զ���windows��˵��
		 *   ����CloseShm�����͵���DestroyShm������������ͬ����û�н�����ʹ�ô�
		 *   �����ڴ�ʱ��windows���Զ�������˹����ڴ档
		 *       ����UNIX�����shmdt����������̺͹����ڴ�İ󶨹�ϵ��
		 * </remarks>
		 */
		void CloseShm();

		/**
		 * <summary>ɾ��CreateShm���������Ĺ����ڴ�</summary>
		 * <remarks>
		 *       ��֤��ε���DestroyShm��������������⡣
		 *       windows�Ų������ü����ĸ���ɾ���ں˶������Զ���windows��˵��
		 *   ����DestroyShm�����͵���CloseShm������������ͬ����û�н�����ʹ�ô�
		 *   �����ڴ�ʱ��windows���Զ�������˹����ڴ档
		 *       ����UNIX�����shmctl��������˹����ڴ档
		 * </remarks>
		 */
		void DestroyShm();

		void* GetShm()
		{
			return m_pvShm;
		}
#ifndef __WIN__
		/**
		 * <summary>�õ�UNIX��ֵID</summary>
		 * <inparam name="psShmName" type="const char*">
		 *       �����ڴ�����ơ�windowsͨ���˱����˱�������ʶ�˹���UNIXͨ���˱���
		 *   �����㹲���ڴ��ֵ��
		 * </inparam>
		 * <inparam name="iShmProjectId" type="int">��UNIX�汾�µ�ftok�����л��õ���windows�¿ɴ���0��������</inparam>
		 * <inparam name="iKeyId" type="key_t&">���ؼ�ֵID</inparam>
		 */
		static ETYPE GetKeyId(const char* psShmName, int iShmProjectId, key_t &iKeyId);

		/**
		 * <summary>ɾ��һ���Ѿ����ڵĹ����ڴ棬�˺���ֻ��UNIXʹ�á�</summary>
		 * <inparam name="psShmName" type="const char*">
		 *       �����ڴ�����ơ�windowsͨ���˱����˱�������ʶ�˹���UNIXͨ���˱���
		 *   �����㹲���ڴ��ֵ��
		 * </inparam>
		 * <inparam name="iShmProjectId" type="int">��UNIX�汾�µ�ftok�����л��õ���windows�¿ɴ���0��������</inparam>
		 */
		static ETYPE RmShm(const char* psShmName, int iShmProjectId);
#endif
	private:
		TShm m_tShm;			//�����ڴ�ľ��
		void *m_pvShm;			//�����ڴ���ڴ�ָ��
		bool m_bIsInitial;		//������ǰ�Ĺ����ڴ��Ƿ�򿪻򴴽��ɹ���һ��CLShm��ֻ�ܴ�һ�Σ��������ظ��򿪡�
	};
}
