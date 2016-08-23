/**
 *     �����ڴ����
 */
#include "libsys.h"

namespace NSPrime
{
	CLShm::CLShm()
	{
		m_tShm = (TShm)0;
		m_pvShm = NULL;
		m_bIsInitial = false;
	}

	CLShm::~CLShm()
	{
		
	}

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
	ETYPE CLShm::CreateShm(const char* psShmName, unsigned int iShmSize, unsigned long lProtectAttr, int iShmProjectId)
	{
		ETYPE iRet = 0; 

		if (m_bIsInitial)
		{
			return -1;
		}

#ifdef __WIN__
		m_tShm = CreateFileMapping(
                 INVALID_HANDLE_VALUE,	// use paging file
                 NULL,					// default security 
                 lProtectAttr,			// read/write access
                 0,						// max. object size 
                 iShmSize,				// buffer size  
                 psShmName);			// name of mapping object
		if (m_tShm == NULL) 
		{ 
			return GetLastError();
		}
		
		m_pvShm = MapViewOfFile(m_tShm,		// handle to map object
			FILE_MAP_ALL_ACCESS,			// read/write permission�����������PAGE_READWRITEѡ���
			0, 0, iShmSize);
		if (m_pvShm == NULL) 
		{ 
			return GetLastError();
		}
#else
		key_t iKeyId;
		if ((iRet = GetKeyId(psShmName, iShmProjectId, iKeyId)) != 0)
		{
			return iRet;
		}

		if ((m_tShm = shmget(iKeyId, iShmSize, lProtectAttr|IPC_CREAT)) == -1)
		{
			return errno;
		}
		if ((m_pvShm = shmat (m_tShm, (char *) 0,0)) == (void *) -1)
		{
			return errno;
		}
#endif
		//���ڿ����ǵõ�ԭ���Ѿ������Ĺ����ڴ棬�������ﲻ���������ڴ�ĳ�ʼ����memset��������
		//��ʼ���Ĺ��������ͻ�����ִ�С�
		//memset(m_pvShm, 0, iShmSize);
		m_bIsInitial = true;
		return iRet;
	}

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
	ETYPE CLShm::OpenShm(const char* psShmName, unsigned int iShmSize, int iShmProjectId)
	{
		ETYPE iRet = 0; 

		if (m_bIsInitial)
		{
			return -1;
		}
#ifdef __WIN__
		m_tShm = OpenFileMapping(
					FILE_MAP_ALL_ACCESS,   // read/write access
					FALSE,                 // do not inherit the name
					psShmName); 
		if (m_tShm == NULL) 
		{ 
			return GetLastError();
		}
		
		m_pvShm = MapViewOfFile(m_tShm,		// handle to map object
			FILE_MAP_ALL_ACCESS,					// read/write permission�����������PAGE_READWRITEѡ���
			0, 0, iShmSize);
		if (m_pvShm == NULL) 
		{ 
			return GetLastError();
		}
#else
		key_t iKeyId;
		if ((iRet = GetKeyId(psShmName, iShmProjectId, iKeyId)) != 0)
		{
			return iRet;
		}

		if ((m_tShm = shmget(iKeyId, iShmSize, 0)) == -1)
		{
			return errno;
		}
		
		if ((m_pvShm = shmat (m_tShm, (char *) 0,0)) == (void *) -1)
		{
			return errno;
		}
#endif
		m_bIsInitial = true;
		return 0;
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
	ETYPE CLShm::GetKeyId(const char* psShmName, int iShmProjectId, key_t &iKeyId)
	{
		iKeyId = ftok(psShmName, iShmProjectId);
		if (iKeyId == -1)
		{
			return errno;
		}
		return 0;
	}
#endif

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
	void CLShm::CloseShm()
	{
#ifdef __WIN__
		if (m_pvShm)
		{
			UnmapViewOfFile(m_pvShm);
			m_pvShm = NULL;
		}
		if (m_tShm != (TShm)0)
		{
			CloseHandle(m_tShm);
			m_tShm = (TShm)0;
		}
#else
		if (m_pvShm)
		{
			shmdt ((char *) m_pvShm);
			m_pvShm = (void*)0;
		}

		m_tShm = (TShm)0;
#endif
		m_bIsInitial = false;
		return;
	}

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
	void CLShm::DestroyShm()
	{
#ifdef __WIN__
		if (m_pvShm)
		{
			UnmapViewOfFile(m_pvShm);
			m_pvShm = NULL;
		}
		if (m_tShm != (TShm)0)
		{
			CloseHandle(m_tShm);
			m_tShm = (TShm)0;
		}
#else
		if (m_pvShm)
		{
			shmdt ((char *) m_pvShm);
			m_pvShm = (void*)0;
		}

		if (m_tShm)
		{
			shmctl(m_tShm, IPC_RMID, 0);
			m_tShm = (TShm)0;
		}
#endif
	}

#ifndef __WIN__
	/**
	 * <summary>ɾ��һ���Ѿ����ڵĹ����ڴ棬�˺���ֻ��UNIXʹ�á�</summary>
	 * <inparam name="psShmName" type="const char*">
	 *       �����ڴ�����ơ�windowsͨ���˱����˱�������ʶ�˹���UNIXͨ���˱���
	 *   �����㹲���ڴ��ֵ��
	 * </inparam>
	 * <inparam name="iShmProjectId" type="int">��UNIX�汾�µ�ftok�����л��õ���windows�¿ɴ���0��������</inparam>
	 */
	ETYPE CLShm::RmShm(const char* psShmName, int iShmProjectId)
	{
		ETYPE iRet = 0; 
		key_t iKeyId;
		if ((iRet = GetKeyId(psShmName, iShmProjectId, iKeyId)) != 0)
		{
			return iRet;
		}

		TShm tShm;			//�����ڴ�ľ��
		if ((tShm = shmget(iKeyId, 0, 0)) == -1)
		{
			return errno;
		}

		if (tShm)
		{
			shmctl(tShm, IPC_RMID, 0);
			tShm = (TShm)0;
		}
		return 0;
	}
#endif

}
