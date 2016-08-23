#pragma once
//#include "global.h"

namespace NSPrime
{
	typedef struct tagLibDbugGlobalVar
	{
		//���̵����ơ�
		const char *m_sProgramName;

		//����CLDbug��
		TDBugGlbalVar m_tDBugGlbalVar;

		//����CLGlobalErrors��
		TAbortHook AbortHook;
		TErrorHandlerHook ErrorHandlerHook;
		TFatalErrorHandlerHook FatalErrorHandlerHook;
		const char ** errMsg[CLGlobalErrors::MAX_MAP_NUM];
		const char *globErrs[CLGlobalErrors::GLOBERRS];
		char m_sErrBuff[CLGlobalErrors::NRERRBUFFS][CLGlobalErrors::ERR_MSG_SIZE];

#ifndef DBUG_OFF
		//����CLGlobalErrors��CLMalloc��
		/**
		 *     ��ǰ�ܵķ����������GlobalMalloc��һ����GlobalFree��һ��
		 */
		NSPrime::CLCriticalSection m_thrLockMalloc;
		unsigned long m_lTotalMallocTimes;
		unsigned long lTotalSerialNo;
		unsigned long m_lTotalMallocSize;
		TDbLink*  g_ptMallocLink;  //ȫ�ֵķ����ڴ��б���ֵ����CMalloc���еĺ��������޸ġ�
#endif

		//����CLThread��
		ub4 m_iThreadCount;
		/**
		 *     ���½��̻߳�ɾ���߳�ʱ��ʹ�ô�����
		 */
		CLCriticalSection m_gLockThread;

		/**
		 *     ���޸��̵߳�ȫ�ֱ���ʱ��ʹ�ô��߳���������
		 */
		CLCriticalSection m_gLockThreadInterVar;

		/**
		 *     ϵͳȫ���������ڶԱȽϼ򵥵ı����Ӽ��������м�����
		 */
		CLCriticalSection m_gLockSysGlobal;
#ifndef DBUG_OFF
		CLThread::TThreadList *g_ptThreadList;  //��ֵ����CMalloc���еĺ��������޸ġ�
#endif
		/**
		 *     �߳���������
		 */
		THREAD_KEY(TThreadVar, hThreadKeySystem);
	}TLibDbugGlobalVar;

	/**
	 *     ��ĳ�ʼ�������������
	 */
	class CLDbugLibInit
	{
	public:

		//libdbug�����õ�������ȫ�ֱ�������
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

