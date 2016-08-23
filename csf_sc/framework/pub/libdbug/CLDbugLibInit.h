#pragma once
//#include "global.h"

namespace NSPrime
{
	typedef struct tagLibDbugGlobalVar
	{
		//进程的名称。
		const char *m_sProgramName;

		//用于CLDbug类
		TDBugGlbalVar m_tDBugGlbalVar;

		//用于CLGlobalErrors类
		TAbortHook AbortHook;
		TErrorHandlerHook ErrorHandlerHook;
		TFatalErrorHandlerHook FatalErrorHandlerHook;
		const char ** errMsg[CLGlobalErrors::MAX_MAP_NUM];
		const char *globErrs[CLGlobalErrors::GLOBERRS];
		char m_sErrBuff[CLGlobalErrors::NRERRBUFFS][CLGlobalErrors::ERR_MSG_SIZE];

#ifndef DBUG_OFF
		//用于CLGlobalErrors类CLMalloc类
		/**
		 *     当前总的分配次数，在GlobalMalloc加一，在GlobalFree减一。
		 */
		NSPrime::CLCriticalSection m_thrLockMalloc;
		unsigned long m_lTotalMallocTimes;
		unsigned long lTotalSerialNo;
		unsigned long m_lTotalMallocSize;
		TDbLink*  g_ptMallocLink;  //全局的分配内存列表，此值会在CMalloc类中的函数进行修改。
#endif

		//用于CLThread类
		ub4 m_iThreadCount;
		/**
		 *     当新建线程或删除线程时，使用此锁。
		 */
		CLCriticalSection m_gLockThread;

		/**
		 *     当修改线程的全局变量时，使用此线程数据锁。
		 */
		CLCriticalSection m_gLockThreadInterVar;

		/**
		 *     系统全局锁，用于对比较简单的变量加减操作进行加锁。
		 */
		CLCriticalSection m_gLockSysGlobal;
#ifndef DBUG_OFF
		CLThread::TThreadList *g_ptThreadList;  //此值会在CMalloc类中的函数进行修改。
#endif
		/**
		 *     线程索引定义
		 */
		THREAD_KEY(TThreadVar, hThreadKeySystem);
	}TLibDbugGlobalVar;

	/**
	 *     库的初始化和清除操作。
	 */
	class CLDbugLibInit
	{
	public:

		//libdbug库里用到的所有全局变量定义
		static TLibDbugGlobalVar *g_ptLibDbugGlobalVar;

		static inline void SetDbugInterEnv(TLibDbugGlobalVar *ptLibDbugGlobalVar)
		{
			g_ptLibDbugGlobalVar = ptLibDbugGlobalVar;
		}
		static inline TLibDbugGlobalVar *GetDbugInterEnv()
		{
			return g_ptLibDbugGlobalVar;
		}

		static int LibInit(const char* sProgramName);
		static int LibDestroy();
	};
}

