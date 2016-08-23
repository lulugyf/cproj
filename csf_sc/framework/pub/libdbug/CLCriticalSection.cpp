#include "libdbug.h"

namespace NSPrime
{
	void CLCriticalSection::Lock() throw()
	{
#ifdef __WIN__
		EnterCriticalSection(&m_sec);
#else
		pthread_mutex_lock(&m_sec);
#endif
		m_iLockCount ++;
		m_tThreadId = CLThread::GetCurrThreadId();
	}

	void CLCriticalSection::Unlock() throw()
	{
		m_iLockCount --;
#ifdef __WIN__
		LeaveCriticalSection(&m_sec);
#else
		pthread_mutex_unlock(&m_sec);
#endif
	}

	bool CLCriticalSection::Init(long dwSpinCount) throw()
	{
		m_iInit = true;
#ifdef __WIN__
		return InitializeCriticalSectionAndSpinCount(&m_sec,(DWORD)dwSpinCount) == TRUE;
#else
		return pthread_mutex_init(&m_sec,NULL) == 0;
#endif
	}

	void CLCriticalSection::Term() throw()
	{
		m_iInit = false;
#ifdef __WIN__
		DeleteCriticalSection(&m_sec);
#else
		pthread_mutex_destroy(&m_sec);
#endif
	}	
	
	void CLCriticalSection::SafeMutexAssertOwner()
	{
		DBUG_ASSERT(m_iLockCount > 0 && ThreadEqual(CLThread::GetCurrThreadId(), m_tThreadId));
	}
}
