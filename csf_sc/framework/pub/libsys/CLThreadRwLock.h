#pragma once

//#include "global.h"

namespace NSPrime
{
	/* Use our own version of read/write locks */
	typedef struct tagRwLock {
		CLCriticalSection lock;		/* lock for structure		*/
		TThreadCond	readers;	/* waiting readers		*/
		TThreadCond	writers;	/* waiting writers		*/
		int		state;		/* -1:writer,0:free,>0:readers	*/
		int		waiters;	/* number of waiting writers	*/
	} rw_lock_t;
	
	class CLThreadRwLock
	{
	public:
		CLThreadRwLock()
		{
			m_bIsInit = false;
		}
		~CLThreadRwLock()
		{
			if (m_bIsInit)
			{
				rwlock_destroy();
			}
		}
	public:
		int rwlock_init(void *);
		int rwlock_destroy();
		int rw_rdlock();
		int rw_wrlock();
		int rw_unlock();
		int rw_tryrdlock();
		int rw_trywrlock();
	private:
		rw_lock_t m_tRwp;
		bool m_bIsInit;
	};
}
