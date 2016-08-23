#pragma once

namespace NSPrime
{
	class CLThreadCond
	{
	public:
		static void ThreadCondAttrInit(TThreadCondAttr *ptThreadCondAttr)
		{
#ifdef __WIN__
			memset(ptThreadCondAttr, 0, sizeof(TThreadCondAttr));
#else
			pthread_condattr_init(ptThreadCondAttr);
#endif
			return;
		}
		static void ThreadCondAttrDestroy(TThreadCondAttr *ptThreadCondAttr)
		{
#ifdef __WIN__
			memset(ptThreadCondAttr, 0, sizeof(TThreadCondAttr));
#else
			pthread_condattr_destroy(ptThreadCondAttr);
#endif
			return;
		}

		static inline int ThreadCondInit(TThreadCond *cond, const TThreadCondAttr *attr)
		{
#ifdef __WIN__
			cond->waiting=0;
			cond->semaphore=CreateSemaphore(NULL,0,0x7FFFFFFF,NULL);
			if (!cond->semaphore)
			{
				return ENOMEM;
			}
#else
			return pthread_cond_init(cond, attr);
#endif
			return 0;
		}

		static inline bool ThreadCondDestroy(TThreadCond *cond)
		{
#ifdef __WIN__
			return CloseHandle(cond->semaphore) == S_OK;
#else
			return pthread_cond_destroy((pthread_cond_t*)cond) == 0;
#endif
		}

		static int ThreadCondTimedwait(TThreadCond *cond, CLCriticalSection *pCriticalSection,
			struct timespec *abstime)
		{
#ifdef __WIN__
			struct _timeb curtime;
			int result;
			long timeout;
			_ftime(&curtime);
			timeout= ((long) (abstime->tv_sec - curtime.time)*1000L +
				(long)((abstime->tv_nsec/1000) - curtime.millitm)/1000L);
			if (timeout < 0)				/* Some safety */
				timeout = 0L;
			CLThread::InterlockedIncrement((sb8*)&cond->waiting);
			pCriticalSection->Unlock();
			result=WaitForSingleObject(cond->semaphore,timeout);
			CLThread::InterlockedDecrement((sb8*)&cond->waiting);
			pCriticalSection->Lock();
			return result == WAIT_TIMEOUT ? ETIMEDOUT : 0;
#else
			return pthread_cond_timedwait((pthread_cond_t*)cond, &pCriticalSection->m_sec, abstime);
#endif
		}

		static inline bool ThreadCondWait(TThreadCond *cond, CLCriticalSection *pCriticalSection,struct timespec *abstime)
		{
			return ThreadCondWait(cond, pCriticalSection);
		}
		static inline bool ThreadCondWait(TThreadCond *cond, CLCriticalSection *pCriticalSection)
		{
#ifdef __WIN__
			CLThread::InterlockedIncrement((sb8*)&cond->waiting);
			pCriticalSection->Unlock();
			WaitForSingleObject(cond->semaphore,INFINITE);
			CLThread::InterlockedDecrement((sb8*)&cond->waiting);
			pCriticalSection->Lock();
#else
			return pthread_cond_wait((pthread_cond_t*)cond, &pCriticalSection->m_sec);
#endif
			return true;
		}

		static inline bool ThreadCondSignal(TThreadCond *cond)
		{
#ifdef __WIN__
			long prev_count;
			if (cond->waiting)
				return ReleaseSemaphore(cond->semaphore,1,&prev_count) == TRUE;
#else
			return pthread_cond_signal((pthread_cond_t *)cond) == 0;
#endif
			return true;
		}

		static inline bool ThreadCondBroadcast(TThreadCond *cond)
		{
#ifdef __WIN__
			long prev_count;
			if (cond->waiting)
				return ReleaseSemaphore(cond->semaphore,cond->waiting,&prev_count) == TRUE;
#else
			return pthread_cond_broadcast((pthread_cond_t *)cond);
#endif
			return true;
		}
	};
}

