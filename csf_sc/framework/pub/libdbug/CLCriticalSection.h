#pragma once

namespace NSPrime
{
#define thr_errno NSPrime::CLThread::GetThreadVar()->thrErrno

typedef unsigned int(*TThreadHandler)( void * );
#define pthread_handler_decl(A,B) unsigned int A(void *B)
#ifdef __WIN__
	typedef HANDLE		 HTHREAD;
	typedef unsigned int TThreadId;
#else
	typedef pthread_t		 HTHREAD;
	typedef pthread_t		 TThreadId;
#endif

	/**
	*     信号Semaphore部分函数和变量
	*/

#ifdef __WIN__
	typedef struct tagThreadCond
	{
		sb4 waiting;
		HANDLE semaphore;
	}TThreadCond;
#else
	typedef pthread_cond_t TThreadCond;
#endif

#ifdef __WIN__
	typedef struct tagThreadCondAttr
	{
		int dummy;
	} TThreadCondAttr;
#else
	typedef pthread_condattr_t TThreadCondAttr;
#endif
	/**
	*     对于单进程参数dwSpinCount没有意义，应该设为0。对于多进程系统，如
	* 果关键代码进入不合法，调用此函数的线程在进行系统等待之前，系统将最多
	* 尝试dwSpinCount多次初始化操作，如果还不成功就进入系统状态。
	* .
	*/
	class CLCriticalSection
	{
	public:
		CLCriticalSection() throw() :m_iLockCount(0),m_tThreadId(0),m_iInit(false)
		{
			memset(&m_sec, 0, sizeof(m_sec));
		}

		void Lock() throw();

		void Unlock() throw();

		bool Init(long dwSpinCount) throw();

		void Term() throw();

		void SafeMutexAssertOwner();
#ifdef __WIN__
		CRITICAL_SECTION m_sec;
#else
		pthread_mutex_t m_sec;
#endif
		bool IsInit()
		{
			return m_iInit;
		}
	private:
		TThreadId m_tThreadId;		//线程的ID。
		ub4 m_iLockCount;
		bool m_iInit;
	};

	/**
	* 对CCriticalSection类的封装
	*/
	template< class TLock =CLCriticalSection>
	class CLCriticalSectionWrapper
	{
	public:
		CLCriticalSectionWrapper()
		{
		}
		CLCriticalSectionWrapper( TLock* pcs, bool bInitialLock = true )
		{
			Init(pcs, bInitialLock);
		}
		~CLCriticalSectionWrapper() throw()
		{
			if( m_bLocked )
			{
				Unlock();
			}
		}

		void Init( TLock* pcs, bool bInitialLock = true )
		{
			m_pcs = pcs;
			if( bInitialLock )
			{
				m_pcs->Lock();
				m_bLocked = true;
			}
			else
			{
				m_bLocked = false;
			}
		}
		bool IsLock()
		{
			return m_bLocked;
		}
		void Lock() throw()
		{
			if (!m_bLocked)
			{
				m_bLocked = true;
				m_pcs->Lock();
			}
		}
		void Unlock() throw()
		{
			if (m_bLocked)
			{
				m_bLocked = false;
				m_pcs->Unlock();
			}
		}
	private:
		TLock* m_pcs;
		bool m_bLocked;
	};
}

