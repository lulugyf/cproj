#pragma once

//#include "global.h"

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE -1
#endif

namespace NSPrime
{
	class CLTaskBase
	{
	public:
		virtual void DoTask(void *pvParam)=0;
	};

	/**
	 *    必须重新实现此类中的方法：Initialize、Terminate、。
	 */
	class CLWorker
	{
	private:
		static sb8 g_lCurrId;
	public:

		CLWorker() : m_dwExecs( 0 )
		{
			CLThread::InterlockedIncrement2(&g_lCurrId, &m_lId);
		}

		virtual bool Initialize(void *pvParam)
		{
			//printf("[%d]: CLWorker.Initialize(%d)\n", (DWORD_PTR)::GetCurrentThreadId(), (DWORD_PTR)pvParam );
			return true;
		}

		virtual void Terminate(void* /*pvParam*/)
		{
			//printf( "CLWorker #%d exec'd %d times.\n", m_lId, m_dwExecs );
		}

		void Execute(CLTaskBase *dw, void *pvParam) throw()
		{
			dw->DoTask(pvParam);

			m_dwExecs++;
		}

		virtual bool GetWorkerData(ub8 /*dwParam*/, void ** /*ppvData*/)
		{
			return false;
		}

	protected:
		ub8	m_dwExecs;
		sb8	m_lId;
	}; // CLWorker

	template <class CWorker, class ThreadTraits=CLThread>
	class CLThreadPool
	{
	protected:
		NSPrime::CLSimpleMap<TThreadId, NSPrime::HTHREAD> m_threadMap;

		TThreadId m_dwThreadEventId;

		CLCriticalSection m_critSec;
		CLCriticalSection m_lockTask;
		CLSemaphore m_lockThreadEvent;
		ub8 m_dwStackSize;
		sb8 m_dwMaxWait;

		void *m_pvWorkerParam;
		sb8 m_lShutdown;

		std::list<CLTaskBase*>  m_listRequestQueue;
		CLCriticalSectionWrapper<CLSemaphore> m_lockwThreadEvent;
		CLSemaphore m_semTask;
		bool m_bInit;
	public:
		CLThreadPool() throw() :
			m_pvWorkerParam(NULL),
			m_dwMaxWait(-1),
			m_lShutdown(FALSE),
			m_dwThreadEventId(0),
			m_dwStackSize(0),
			m_bInit(false)
		{
		}

		~CLThreadPool() throw()
		{
			if (m_bInit)
			{
				Shutdown();
			}
		}

		// Initialize the thread pool
		// if nNumThreads > 0, then it specifies the number of threads
		// if nNumThreads < 0, then it specifies the number of threads per proc (-)
		// if nNumThreads == 0, then it defaults to two threads per proc
		// lCompletion is a handle of a file to associate with the completion port
		// pvWorkerParam is a parameter that will be passed to CWorker::Execute
		//	dwStackSize:
		//		The stack size to use when creating the threads
		bool Initialize(void *pvWorkerParam=NULL, int nNumThreads=0, ub8 dwStackSize=0, ub8 lCompletion=INVALID_HANDLE_VALUE) throw()
		{
			if (!m_critSec.Init(0))
			{
				return false;
			}
			if (!m_lockTask.Init(0))
			{
				m_critSec.Term();
				return false;
			}
			if (m_lockThreadEvent.Init() != 0)
			{
				m_lockTask.Term();
				m_critSec.Term();
				return false;
			}

			m_lockwThreadEvent.Init(&m_lockThreadEvent, false);

			if (m_semTask.Init() != 0)
			{
				m_lockThreadEvent.Term();
				m_lockTask.Term();
				m_critSec.Term();
				return false;
			}

			m_pvWorkerParam = pvWorkerParam;
			m_dwStackSize = dwStackSize;

			if (SetSize(nNumThreads) != 0)
			{
				m_lockThreadEvent.Term();
				m_lockTask.Term();
				m_critSec.Term();
				m_semTask.Term();
			}
			m_bInit = true;
			return true;
		}

		// Shutdown the thread pool
		// This function posts the shutdown request to all the threads in the pool
		// It will wait for the threads to shutdown a maximum of dwMaxWait MS.
		// If the timeout expires it just returns without terminating the threads.
		void Shutdown(sb8 dwMaxWait=0) throw()
		{
			DBUG_ENTER("Shutdown");
			m_critSec.Lock();

			if (dwMaxWait == 0)
				dwMaxWait = m_dwMaxWait;

			ETYPE iRet = InternalResizePool(0, dwMaxWait);

			if (iRet != 0)
			{
				//DBUG_PRINT("CLThreadPool",("Thread pool not shutting down cleanly : %08x",hr));
			}
/*
			for (int i = m_threadMap.GetSize() - 1; i >= 0; i--)
			{
				HTHREAD hThread = m_threadMap.GetValueAt(i);

				CLThread::ThreadExit(hThread);
			}
*/
			m_listRequestQueue.clear();

			// Uninitialize the critical sections
			m_critSec.Unlock();
			m_critSec.Term();

			m_lockTask.Unlock();
			m_lockTask.Term();

			m_semTask.Term();
			m_lockThreadEvent.Term();
			m_bInit = false;
			DBUG_VOID_RETURN;
		}

		ETYPE SetSize(int nNumThreads) throw()
		{
			if (nNumThreads == 0)
			{
				return 0;
			}

			CLCriticalSectionWrapper<CLCriticalSection> lock(&m_critSec, false);
			lock.Lock();
			
			return InternalResizePool(nNumThreads, m_dwMaxWait);
		}

		ub4 GetSize(ub4 *pnNumThreads) throw()
		{
			if (!pnNumThreads)
				return 0;

			*pnNumThreads = m_threadMap.GetSize();
			return *pnNumThreads;
		}

		bool SetTimeout(sb8 dwMaxWait) throw()
		{
			m_dwMaxWait = dwMaxWait;

			return true;
		}

		sb8 GetTimeout(ub8 *pdwMaxWait) throw()
		{
			if (!pdwMaxWait)
				return m_dwMaxWait;

			*pdwMaxWait = m_dwMaxWait;

			return *pdwMaxWait;
		}

		//追加一个任务请求到线程池。
		bool QueueRequest(CLTaskBase *request) throw()
		{
			if (!request)
			{
				return false;
			}
			return InternalQueueRequest(request, true);
		}
	protected:
		//内部增加一个任务请求到线程池。
		bool InternalQueueRequest(CLTaskBase *request, bool bIsAppend) throw()
		{
			m_lockTask.Lock();
			if (bIsAppend)
			{
				m_listRequestQueue.push_back(request);
			}
			else
			{
				m_listRequestQueue.push_front(request);
			}
			m_lockTask.Unlock();
			m_semTask.Unlock();
			return true;
		}

		ub4 ThreadProc() throw()
		{
			ub4 iCount  = 0;

			// this block is to ensure theWorker gets destructed before the 
			// thread handle is closed
			{
				// We instantiate an instance of the worker class on the stack
				// for the life time of the thread.
				CWorker theWorker;
				
				if (theWorker.Initialize(m_pvWorkerParam) == FALSE)
				{
					return 1;
				}

				while (1)
				{
					m_semTask.Lock();

					m_lockTask.Lock();
					CLTaskBase *request = m_listRequestQueue.front();
					iCount = (ub4)m_listRequestQueue.size();
					m_listRequestQueue.pop_front();
					m_lockTask.Unlock();

					if ((request == NULL) && (iCount > 0)) // Shut down
					{
						CLThread::InterlockedExchange(&m_lShutdown, FALSE);
						
						//等待创建线程池的线程进行加锁操作，以便当前子线程释放锁。
						while(1)
						{
							if (m_lockwThreadEvent.IsLock())
							{
								break;
							}
							else
							{
#ifdef __WIN__
								Sleep(1000);
#else
								sleep(1);
#endif
							}
						}
#ifdef __WIN__
						m_dwThreadEventId = GetCurrentThreadId();
#else
						m_dwThreadEventId = pthread_self();
#endif
						m_lockwThreadEvent.Unlock();

						break;
					}
					else										// Do work
					{
						theWorker.Execute(request, m_pvWorkerParam);
					}
				}

				theWorker.Terminate(m_pvWorkerParam);
			}
			
			return 0; 
		}

		pthread_handler_decl(WorkerThreadProc,pv)
		{
			CLThreadPool* pThis = 
				reinterpret_cast< CLThreadPool* >(pv); 

			return pThis->ThreadProc();
		} 

		ETYPE InternalResizePool(int nNumThreads, sb8 dwMaxWait) throw()
		{
			DBUG_ENTER("InternalResizePool");
			int nCurThreads = m_threadMap.GetSize();
			if (nNumThreads == nCurThreads)
			{
				DBUG_RETURN(0);
			}
			else if (nNumThreads < nCurThreads)
			{
				int nNumShutdownThreads = nCurThreads - nNumThreads;
				for (int nThreadIndex = 0; nThreadIndex < nNumShutdownThreads; nThreadIndex++)
				{
					CLThread::InterlockedExchange(&m_lShutdown, TRUE);
					InternalQueueRequest(NULL, false);
					m_lockwThreadEvent.Lock();

					int nIndex = m_threadMap.FindKey(m_dwThreadEventId);
					if (nIndex != -1)
					{
						HTHREAD hThread = m_threadMap.GetValueAt(nIndex);

						//等待将要结束的线程结束。
#ifdef __WIN__
						WaitForSingleObject(hThread, INFINITE);
#else
						pthread_join(hThread, NULL);
#endif

						//
						CLThread::ThreadExit(m_threadMap.GetValueAt(nIndex));
						m_threadMap.RemoveAt(nIndex);
					}
					else
					{
						//不可能到这里！！！
						//DBUG_PRINT("InternalResizePool", ("m_threadMap.RemoveAt Error![%ld]", m_dwThreadEventId));
					}
				}
			}
			else
			{
				int nNumNewThreads = nNumThreads - nCurThreads;
				// Create and initialize worker threads

				for (int nThreadIndex = 0; nThreadIndex < nNumNewThreads; nThreadIndex++)
				{
					ub4 wThreadID;
					HTHREAD hThread= ThreadTraits::ThreadCreate(NULL, (ub4)m_dwStackSize, WorkerThreadProc,
						(gptr)this,0, &wThreadID, NULL);
					if (!hThread)
					{
						DBUG_RETURN(CLGlobalErrors::EE_OUTOFMEMORY);
					}

					if (!m_threadMap.Add(wThreadID, hThread))
					{
						DBUG_RETURN(CLGlobalErrors::EE_OUTOFMEMORY);
					}
				}
			}
			DBUG_RETURN(0);
		}
	};
}

