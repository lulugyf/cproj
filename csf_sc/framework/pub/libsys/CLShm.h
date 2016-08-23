/**
 *     共享内存管理
 */

#pragma once

namespace NSPrime
{
#ifdef __WIN__
	typedef HANDLE TShm;
#else
	typedef int TShm;
#endif

	//共享内存的信息
	class CLShm
	{
	public:
		CLShm();
		~CLShm();
	public:
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
		ETYPE CreateShm(const char* psShmName, unsigned int iShmSize, unsigned long lProtectAttr, int iShmProjectId);

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
		ETYPE OpenShm(const char* psShmName, unsigned int iShmSize, int iShmProjectId);

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
		void CloseShm();

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
		void DestroyShm();

		void* GetShm()
		{
			return m_pvShm;
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
		static ETYPE GetKeyId(const char* psShmName, int iShmProjectId, key_t &iKeyId);

		/**
		 * <summary>删除一个已经存在的共享内存，此函数只给UNIX使用。</summary>
		 * <inparam name="psShmName" type="const char*">
		 *       共享内存的名称。windows通过此变量此变量来标识此共享。UNIX通过此变量
		 *   来计算共享内存键值。
		 * </inparam>
		 * <inparam name="iShmProjectId" type="int">在UNIX版本下的ftok函数中会用到，windows下可传入0，无意义</inparam>
		 */
		static ETYPE RmShm(const char* psShmName, int iShmProjectId);
#endif
	private:
		TShm m_tShm;			//共享内存的句柄
		void *m_pvShm;			//共享内存的内存指针
		bool m_bIsInitial;		//表明当前的共享内存是否打开或创建成功，一个CLShm类只能打开一次，不容许重复打开。
	};
}
