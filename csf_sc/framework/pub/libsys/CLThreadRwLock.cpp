#include "libsys.h"

namespace NSPrime
{
	int CLThreadRwLock::rwlock_init(void *arg __attribute__((unused)))
	{
		TThreadCondAttr	cond_attr;

		m_tRwp.lock.Init(0);
		CLThreadCond::ThreadCondAttrInit( &cond_attr );
		CLThreadCond::ThreadCondInit( &m_tRwp.readers, &cond_attr );
		CLThreadCond::ThreadCondInit( &m_tRwp.writers, &cond_attr );
		CLThreadCond::ThreadCondAttrDestroy(&cond_attr);

		m_tRwp.state	= 0;
		m_tRwp.waiters	= 0;
		m_bIsInit = true;

		return(0);
	}

	int CLThreadRwLock::rwlock_destroy()
	{
		m_tRwp.lock.Term();
		CLThreadCond::ThreadCondDestroy( &m_tRwp.readers );
		CLThreadCond::ThreadCondDestroy( &m_tRwp.writers );
		m_bIsInit = false;
		return(0);
	}


	int CLThreadRwLock::rw_rdlock()
	{
		m_tRwp.lock.Lock();

		/* active or queued writers */
		while (( m_tRwp.state < 0 ) || m_tRwp.waiters)
			CLThreadCond::ThreadCondWait( &m_tRwp.readers, &m_tRwp.lock);

		m_tRwp.state++;
		m_tRwp.lock.Unlock();
		return(0);
	}

	int CLThreadRwLock::rw_tryrdlock()
	{
		int res;
		m_tRwp.lock.Lock();
		if ((m_tRwp.state < 0 ) || m_tRwp.waiters)
			res= EBUSY;					/* Can't get lock */
		else
		{
			res=0;
			m_tRwp.state++;
		}
		m_tRwp.lock.Unlock();
		return(res);
	}


	int CLThreadRwLock::rw_wrlock()
	{
		m_tRwp.lock.Lock();
		m_tRwp.waiters++;				/* another writer queued */

		while (m_tRwp.state)
			CLThreadCond::ThreadCondWait(&m_tRwp.writers, &m_tRwp.lock);
		m_tRwp.state	= -1;
		m_tRwp.waiters--;
		m_tRwp.lock.Unlock();
		return(0);
	}


	int CLThreadRwLock::rw_trywrlock()
	{
		int res;
		m_tRwp.lock.Lock();
		if (m_tRwp.state)
			res= EBUSY;					/* Can't get lock */    
		else
		{
			res=0;
			m_tRwp.state	= -1;
		}
		m_tRwp.lock.Unlock();
		return(res);
	}


	int CLThreadRwLock::rw_unlock()
	{
		DBUG_PRINT("rw_unlock",
			("state: %d waiters: %d", m_tRwp.state, m_tRwp.waiters));
		m_tRwp.lock.Lock();

		if (m_tRwp.state == -1)		/* writer releasing */
		{
			m_tRwp.state= 0;		/* mark as available */

			if ( m_tRwp.waiters )		/* writers queued */
				CLThreadCond::ThreadCondSignal( &m_tRwp.writers );
			else
				CLThreadCond::ThreadCondBroadcast( &m_tRwp.readers );
		}
		else
		{
			if ( --m_tRwp.state == 0 )	/* no more readers */
				CLThreadCond::ThreadCondSignal( &m_tRwp.writers );
		}

		m_tRwp.lock.Unlock();
		return(0);
	}
}
