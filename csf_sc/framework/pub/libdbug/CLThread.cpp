#include "libdbug.h"

namespace NSPrime
{
#ifdef __WIN__
	unsigned __stdcall ThreadStartAddress( void * param)
#else
#	if PLATFORM_TYPE == PLATFORM_TYPE_SOLARIS
	extern "C" void* ThreadStartAddress( void * param)
#	else
	void* ThreadStartAddress( void * param)
#	endif
#endif
	{
		if (!param)
		{
			return NULL;
		}
		TThreadHandler ExecFunc=((CLThread::TThreadMap *) param)->ExecFunc;
		void *funcParam=((CLThread::TThreadMap *) param)->param;
		
		/**
		 *     ��CLThread::ThreadCreate�������أ���ʱ�����param�����е���Ϣ��������
		 */
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockThread.Lock();
		CLThread::ThreadInit(((CLThread::TThreadMap *) param)->hThread, ((CLThread::TThreadMap *) param)->tThreadId);/* Will always succeed in windows */
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockThread.Unlock();
		CLMalloc::GlobalFree((char*) param);			  /* Free param from create */
		unsigned int iRet=(unsigned) (*ExecFunc)(funcParam);
		DBUG_PRINT("info", ("ExecFunc iRet[%d] begin ThreadEnd ...", iRet));
		CLThread::ThreadEnd();
#ifdef __WIN__
		_endthreadex(iRet);
		return 0;
#else
		pthread_exit(NULL);
		return NULL;
#endif
	}

	/**
	 *     ����һ���µ��̣߳�ͨ��ThreadExit���ر��߳̾����
	 *@param stackSize	�̵߳Ķ�ջ��Ϊ���ʾ�����̵߳Ķ�ջ��С��ͬ��
	 *@param iInitFlag	ֻ�Ƕ�WINDOWS��Ч��UNIXֱ�Ӵ�0��0:��ʾ��������; CREATE_SUSPENDED��ʾ������Ҫʹ��ResumeThread����ִ������̡߳�
	 *@param pThreadId	�̵߳�ID�� �������ĵ�ַΪ�գ���ʾ�����ش�ֵ��
	 *@param attr	�̵߳����ԣ����Ϊ�գ��������̵߳����ԣ������Ի��ʼ����
	 *              �̵Ļ��ȼ���
	 */
	HTHREAD CLThread::ThreadCreate(void *security, ub4 stackSize,
		TThreadHandler ExecFunc, void *param,
		ub4 iInitFlag,TThreadId *pThreadId,const TThreadAttr *attr)
	{
		HTHREAD hThread = 0;
		TThreadMap *threadMap=NULL;
		ub4 threadIdTmp=0;
		ub4 iRet = 0;
		DBUG_ENTER("ThreadCreate");

		if (!(threadMap=(TThreadMap*)CLMalloc::GlobalMalloc(sizeof(TThreadMap))))
		{
			DBUG_RETURN((HTHREAD)0);
		}

#ifndef DBUG_OFF
		TThreadList *ptThreadList;
		if (!(ptThreadList=(TThreadList*)CLMalloc::GlobalMalloc(sizeof(TThreadList))))
		{
			CLMalloc::GlobalFree(threadMap);
			DBUG_RETURN((HTHREAD)0);
		}
		ptThreadList->m_lMallocSize = 0;
		ptThreadList->m_lMallocTimes = 0;
		ptThreadList->m_ptMallocLink = NULL;
		ptThreadList->m_ptThreadListNext = CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList;
#endif

		threadMap->ExecFunc = ExecFunc;
		threadMap->param = param;

		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockThread.Lock();
#ifdef __WIN__
		hThread=(HTHREAD)_beginthreadex(security, stackSize, ThreadStartAddress,
			threadMap, iInitFlag, &threadIdTmp);
#else
		iRet = pthread_create(&hThread, NULL, ThreadStartAddress,threadMap);
#endif
		DBUG_PRINT("info", ("hThread=%lx",hThread));
		threadMap->hThread =hThread;
#ifdef __WIN__
		threadMap->tThreadId = threadIdTmp;

#ifndef DBUG_OFF
		ptThreadList->m_hThread = hThread;		
#endif
#else
		threadMap->tThreadId = hThread;
#ifndef DBUG_OFF
		ptThreadList->m_hThread = hThread;		
#endif
#endif
		if ((hThread) && (iRet == 0))
		{
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_iThreadCount ++;
			if (pThreadId)
			{
#ifdef __WIN__
				*pThreadId = threadIdTmp;
#else
				*pThreadId = hThread;
#endif
			}
		}
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockThread.Unlock();

		if ((hThread == (HTHREAD)0) || (iRet != 0))
		{
			int error=errno;
			DBUG_PRINT("error",("Can't create thread to handle request (error %d)",error));

#ifndef DBUG_OFF
			CLMalloc::GlobalFree(ptThreadList);
#endif
			CLMalloc::GlobalFree(threadMap);
			threadMap = NULL;
			DBUG_RETURN(hThread);
		}
		if (attr)
		{
#ifdef __WIN__
			VOID(SetThreadPriority(hThread, attr->priority)) ;
#else
#endif
		}
#ifndef DBUG_OFF
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
		CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList = ptThreadList;
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
#endif

		DBUG_RETURN(hThread);
	}

	/**
	 *     �˳���ǰ���̡߳�
	 *@param retVal ���߳��˳�ʱ�ķ���ֵ��
	 */
	void CLThread::ThreadExit(HTHREAD hThread)
	{
#ifndef DBUG_OFF
		TThreadList *ptThreadListPre, *ptThreadListCur;

		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
		ptThreadListPre = ptThreadListCur = CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList;
		while(ptThreadListCur)
		{
			if (ptThreadListCur->m_hThread == hThread)
			{
				ptThreadListPre->m_ptThreadListNext = ptThreadListCur->m_ptThreadListNext;
				if (CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList == ptThreadListCur)
				{
					CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList = CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList->m_ptThreadListNext;
				}
				CLMalloc::GlobalFree(ptThreadListCur);
				break;
			}
			ptThreadListPre = ptThreadListCur;
			ptThreadListCur = ptThreadListCur->m_ptThreadListNext;
		}
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
#endif
#ifdef __WIN__
		//windows��_endthreadex�������ر��̵߳ľ������Ҫ�ֹ��رա�
		CloseHandle(hThread);
#else
#endif
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockThread.Lock();
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_iThreadCount --;
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockThread.Unlock();
	}

	/**
	 *     �̵߳ĳ�ʼ������
	 */
	bool CLThread::ThreadInit(HTHREAD hThread, TThreadId tThreadId)
	{
		TThreadVar *pThreadVarTmp=NULL;
		bool retVal=TRUE;

		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockThreadInterVar.Lock();

#ifdef USE_TLS
		if (GetThreadSpecific(&CLDbugLibInit::g_ptLibDbugGlobalVar->hThreadKeySystem))
		{
#ifdef EXTRA_DEBUG_THREADS
			fprintf(stderr,"CLThread::ThreadInit() called more than once in thread %ld\n",GetThreadVar()->hThreadSelf);
#endif
			goto END;
		}
		if (!(pThreadVarTmp= (TThreadVar *) CLMalloc::GlobalMalloc(sizeof(TThreadVar))))
		{
			retVal= FALSE;
			goto END;
		}
		memset(pThreadVarTmp, 0, sizeof(TThreadVar));
		if (!ThreadSetSpecific(&CLDbugLibInit::g_ptLibDbugGlobalVar->hThreadKeySystem,(gptr*)pThreadVarTmp,sizeof(TThreadVar)))
		{
#ifdef EXTRA_DEBUG_THREADS
			fprintf(stderr,"CLThread::ThreadInit() ThreadSetSpecific %ld\n",GetThreadVar()->hThreadSelf);
#endif
			retVal= FALSE;
			goto END;
		}

#else
		/**
		 *     Skip initialization if the thread specific variable is already initialized
		 */
		if (hThreadKeySystem.id)
		{
			goto END;
		}
		pThreadVarTmp= &hThreadKeySystem;
#endif
		pThreadVarTmp->abort = 0;
		pThreadVarTmp->thrErrno = 0;
		pThreadVarTmp->tThreadId = tThreadId;
		pThreadVarTmp->hThreadSelf = hThread;
#ifndef DBUG_OFF
		pThreadVarTmp->dbug = NULL;
		memset(pThreadVarTmp->name, 0, sizeof(THREAD_NAME_SIZE+1));
#endif
		pThreadVarTmp->lock.Init(0);
		CLThreadCond::ThreadCondInit(&pThreadVarTmp->suspend, NULL);
		pThreadVarTmp->init= TRUE;
		pThreadVarTmp->current_mutex = NULL;
		pThreadVarTmp->current_cond = NULL;
END:
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockThreadInterVar.Unlock();
		return retVal;
	}


	/**
	 *     �̵߳ĳ�ʼ���������ڲ�����ThreadInit(HTHREAD hThread, TThreadId tThreadId)����
	 */
	bool CLThread::ThreadInit()
	{
#ifdef __WIN__
		return ThreadInit(::GetCurrentThread(),GetCurrThreadId());
#else
		return ThreadInit(GetCurrThreadId(),GetCurrThreadId());
#endif
	}

	/**
	 *     �̵߳�ִ�н����󣬶��������ݽ�������
	 */
	void CLThread::ThreadEnd(void)
	{
		TThreadVar *pThreadVarTmp;

		pThreadVarTmp= (TThreadVar *)GetThreadSpecific(&CLDbugLibInit::g_ptLibDbugGlobalVar->hThreadKeySystem);

		//printf("ThreadEnd pThreadVarTmp[%lx] ThreadEnding ...",
		//	pThreadVarTmp);

#ifdef EXTRA_DEBUG_THREADS
		fprintf(stderr,"CLThread::ThreadEnd(): pThreadVarTmp=%p,thread_id=%ld\n",pThreadVarTmp,GetThreadVar()->hThreadSelf);
#endif  
		if (pThreadVarTmp && pThreadVarTmp->init)
		{
#ifndef DBUG_OFF
			/* tmp->dbug is allocated inside DBUG library */
			if (pThreadVarTmp->dbug)
			{
				CLMalloc::GlobalFree(pThreadVarTmp->dbug);
				pThreadVarTmp->dbug=NULL;
			}
#endif
			CLThreadCond::ThreadCondDestroy(&pThreadVarTmp->suspend);
			pThreadVarTmp->lock.Term();
#ifdef USE_TLS
			ThreadSetSpecific(&CLDbugLibInit::g_ptLibDbugGlobalVar->hThreadKeySystem,NULL,0);
			CLMalloc::GlobalFree(pThreadVarTmp);
#else
#endif
		}
	}

#ifndef DBUG_OFF

		CLThread::TThreadList *CLThread::GetThreadListNode(HTHREAD hThread = (HTHREAD)0)
		{
			CLThread::TThreadList *ptThreadListCur;

			if (hThread ==  (HTHREAD)0)
			{
				hThread = CLThread::GetCurrThreadHandle();
			}

			CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
			ptThreadListCur = CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList;
			while(ptThreadListCur)
			{
				if (ptThreadListCur->m_hThread == hThread)
				{
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
					return ptThreadListCur;
				}
				ptThreadListCur = ptThreadListCur->m_ptThreadListNext;
			}
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();

			return NULL;
		}

#endif

	/**
	 *     �̰߳�ȫ�ı�����һ������
	 */
	void CLThread::InterlockedIncrement ( sb8 *lpAddend)
	{
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
		(*lpAddend) ++;
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
	}

	/**
	 *     �̰߳�ȫ�ı�����һ������
	 */
	void CLThread::InterlockedIncrement ( sb8 *lpAddend, CLCriticalSection *ptLock)
	{
		ptLock->Lock();
		(*lpAddend) ++;
		ptLock->Unlock();
	}

	/**
	 *     �̰߳�ȫ�ı�����һ�͸�ֵ������
	 */
	void CLThread::InterlockedIncrement2 ( sb8 *lpAddend, sb8* plRetValue)
	{
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
		(*lpAddend) ++;
		*plRetValue = (*lpAddend);
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
	}

	/**
	 *     �̰߳�ȫ�ı�������һ��ֵ������
	 */
	void CLThread::InterlockedAddition ( sb8 *lpAddend, sb8 lValue)
	{
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
		(*lpAddend) = (*lpAddend) + lValue;
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
	}

	/**
	 *     �̰߳�ȫ�ı�����һ������
	 */
	void CLThread::InterlockedDecrement ( sb8 *lpAddend)
	{
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
		(*lpAddend) --;
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
	}

	/**
	 *     �̰߳�ȫ�ı�����һ������
	 */
	void CLThread::InterlockedDecrement ( sb8 *lpAddend, CLCriticalSection *ptLock)
	{
		ptLock->Lock();
		(*lpAddend) --;
		ptLock->Unlock();
	}

	/**
	 *     �̰߳�ȫ�ı�����ȥһ��ֵ������
	 */
	void CLThread::InterlockedSubtract ( sb8 *lpAddend, sb8 lValue)
	{
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
		(*lpAddend) = (*lpAddend) - lValue;
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
	}

	/**
	 *     �̰߳�ȫ�ı�����ֵ������
	 */
	void CLThread::InterlockedExchange  ( sb8 *lpAddend, sb8 lValue)
	{
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
		(*lpAddend) = lValue;
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
	}

	CLThread::TThreadVar *CLThread::GetThreadVar()
	{
		return (NSPrime::CLThread::TThreadVar *)CLThread::GetThreadSpecific(&CLDbugLibInit::g_ptLibDbugGlobalVar->hThreadKeySystem);
	}

	/**
	 *     �õ���ǰ�����̵߳�������
	 */
	ub4 CLThread::GetThreadCount()
	{
		return CLDbugLibInit::g_ptLibDbugGlobalVar->m_iThreadCount;
	}
}
