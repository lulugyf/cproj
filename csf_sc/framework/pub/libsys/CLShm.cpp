/**
 *     共享内存管理
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
	 *     创建一个共享内存，如果已经存在，则返回原来已经创建的共享内存及大小，
	 *  windows可以参考CreateFileMapping函数。
	 * <inparam name="psShmName" type="const char*">
	 *       共享内存的名称。windows通过此变量此变量来标识此共享。UNIX通过此变量
	 *   来计算共享内存键值。
	 * </inparam>
	 * <inparam name="iShmSize" type="unsigned int">创建的共享内存大小</inparam>
	 * <inparam name="lProtectAttr" type="unsigned long">
	 *       访问此共享内存的保护属性。
	 *   如window可以设置为PAGE_READWRITE，UNIX可以设置为“0660”
	 * </inparam>
	 * <inparam name="iShmProjectId" type="int">在UNIX版本下的ftok函数中会用到，windows下可传入0，无意义</inparam>
	 * <remarks>一个CLShm类只能创建共享内存一次，否则返回错误-1。</remarks>
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
			FILE_MAP_ALL_ACCESS,			// read/write permission，对象必须由PAGE_READWRITE选项创建
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
		//由于可能是得到原来已经创建的共享内存，所以这里不能做共享内存的初始化（memset）操作，
		//初始化的工作交给客户端来执行。
		//memset(m_pvShm, 0, iShmSize);
		m_bIsInitial = true;
		return iRet;
	}

	/**
	 * <summary>打开一个共享内存，windows可以参考OpenFileMapping函数。</summary>
	 * <inparam name="psShmName" type="const char*">
	 *       共享内存的名称。windows通过此变量此变量来标识此共享。UNIX通过此变量
	 *   来计算共享内存键值。
	 * </inparam>
	 * <inparam name="iShmSize" type="unsigned int">
	 *       iShmSize是该共享存储段的最小值。如果正在创建一个新段（一般在服务器
	 *   中），则必须指定其iShmSize。如果正在存访一个现存的段（一个客户机），则
	 *   将iShmSize指定为0，表示访问整块共享内存。
	 * </inparam>
	 * <inparam name="iShmProjectId" type="int">在UNIX版本下的ftok函数中会用到，windows下可传入0，无意义</inparam>
	 * <remarks>一个CLShm类只能创建共享内存一次，否则返回错误-1。</remarks>
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
			FILE_MAP_ALL_ACCESS,					// read/write permission，对象必须由PAGE_READWRITE选项创建
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
	 * <summary>得到UNIX键值ID</summary>
	 * <inparam name="psShmName" type="const char*">
	 *       共享内存的名称。windows通过此变量此变量来标识此共享。UNIX通过此变量
	 *   来计算共享内存键值。
	 * </inparam>
	 * <inparam name="iShmProjectId" type="int">在UNIX版本下的ftok函数中会用到，windows下可传入0，无意义</inparam>
	 * <inparam name="iKeyId" type="key_t&">返回键值ID</inparam>
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
	 * <summary>关闭OpenShm函数打开的共享内存。</summary>
	 * <remarks>
	 *       保证多次调用CloseShm函数不会出现问题。
	 *       windows才采用引用计数的概念删除内核对象，所以对于windows来说，
	 *   调用CloseShm函数和调用DestroyShm函数的作用相同，当没有进程在使用此
	 *   共享内存时，windows会自动清理掉此共享内存。
	 *       对于UNIX会调用shmdt函数解除进程和共享内存的绑定关系。
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
	 * <summary>删除CreateShm函数创建的共享内存</summary>
	 * <remarks>
	 *       保证多次调用DestroyShm函数不会出现问题。
	 *       windows才采用引用计数的概念删除内核对象，所以对于windows来说，
	 *   调用DestroyShm函数和调用CloseShm函数的作用相同，当没有进程在使用此
	 *   共享内存时，windows会自动清理掉此共享内存。
	 *       对于UNIX会调用shmctl函数清理此共享内存。
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
	 * <summary>删除一个已经存在的共享内存，此函数只给UNIX使用。</summary>
	 * <inparam name="psShmName" type="const char*">
	 *       共享内存的名称。windows通过此变量此变量来标识此共享。UNIX通过此变量
	 *   来计算共享内存键值。
	 * </inparam>
	 * <inparam name="iShmProjectId" type="int">在UNIX版本下的ftok函数中会用到，windows下可传入0，无意义</inparam>
	 */
	ETYPE CLShm::RmShm(const char* psShmName, int iShmProjectId)
	{
		ETYPE iRet = 0; 
		key_t iKeyId;
		if ((iRet = GetKeyId(psShmName, iShmProjectId, iKeyId)) != 0)
		{
			return iRet;
		}

		TShm tShm;			//共享内存的句柄
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
