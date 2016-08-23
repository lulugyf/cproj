#pragma once

#ifdef __WIN__
struct timespec {		/* For pthread_cond_timedwait() */
    time_t tv_sec;
    long tv_nsec;
};
#endif

#define set_timespec(ABSTIME,SEC) { (ABSTIME).tv_sec=time((time_t*)0) + (time_t) (SEC); (ABSTIME).tv_nsec=0; }
#define pthread_detach_this_thread()
#define ThreadKill(A,B) NSPrime::CLThread::ThreadDummy(0)

#ifdef __WIN__
#define ETIMEDOUT 145		    /* Win32 doesn't have this */
#endif

#ifndef ETIME
#define ETIME ETIMEDOUT				/* For FreeBSD */
#endif

#define ThreadEqual(A,B) ((A) == (B))

#ifdef __WIN__
#define my_pthread_setprio(A,B)  SetThreadPriority(GetCurrentThread(), (B))
#else
#define my_pthread_setprio(A,B)  pthread_setprio((A), (B))
#endif

#define my_pthread_attr_setprio(A,B) NSPrime::CLThread::ThreadDummy(0)

namespace NSPrime
{
	class CLThreadCond;
	class CLThread
	{
	public:
		/*** 线程函数和变量开始***/
		/**
		 *     线程的句柄
		 */

		/**
		 *     当前库中所开线程的数量，此变量在ThreadCreate函数中增加一，在ThreadExit中减一。
		 */
		typedef struct tagThreadMap
		{
			HTHREAD hThread;
			TThreadId tThreadId;
			TThreadHandler ExecFunc;
			void *param;
		} TThreadMap;		
	private:
		static const int THREAD_NAME_SIZE	=	10;
	public:

#ifndef DBUG_OFF
		typedef struct tagThreadList
		{
			HTHREAD m_hThread;
			unsigned long  m_lMallocSize;		//此值会在CMalloc类中的函数进行修改。
			unsigned long  m_lMallocTimes;	//此值会在CMalloc类中的函数进行修改。
			struct tagThreadList*  m_ptThreadListNext;
			TDbLink*  m_ptMallocLink;  //此值会在CMalloc类中的函数进行修改。
		}TThreadList;
		
		static TThreadList *GetThreadListNode(HTHREAD hThread);
#endif

		/**
		 *     线程安全的变量加一操作。
		 */
		static void InterlockedIncrement ( sb8 *lpAddend);

		/**
		 *     线程安全的变量加一操作。
		 */
		static void InterlockedIncrement ( sb8 *lpAddend, CLCriticalSection *ptLock);

		/**
		 *     线程安全的变量加一和赋值操作。
		 */
		static void InterlockedIncrement2 ( sb8 *lpAddend, sb8* plRetValue);

		/**
		 *     线程安全的变量加上一个值操作。
		 */
		static void InterlockedAddition ( sb8 *lpAddend, sb8 lValue);

		/**
		 *     线程安全的变量减一操作。
		 */
		static void InterlockedDecrement ( sb8 *lpAddend);

		/**
		 *     线程安全的变量减一操作。
		 */
		static void InterlockedDecrement ( sb8 *lpAddend, CLCriticalSection *ptLock);

		/**
		 *     线程安全的变量减去一个值操作。
		 */
		static void InterlockedSubtract ( sb8 *lpAddend, sb8 lValue);

		/**
		 *     线程安全的变量赋值操作。
		 */
		static void InterlockedExchange  ( sb8 *lpAddend, sb8 lValue);

		/*** 线程函数和变量开始***/
		/**
		 *     线程属性
		 */
		typedef struct tagThreadAttr
		{
			sb8 dwStackSize;
			sb8 dwCreatingFlag;
			int priority;
		}TThreadAttr;

		typedef struct tagThreadVar
		{
			int thrErrno;				//当前线程的错误代码，此变量由各个应用程序维护赋值。
			char sThrErrMsg[2047+1];	//当前线程的错误信息，此变量由各个应用程序维护赋值。
			int iCurLineNo;				//当前线程错误所在的行信息，此变量由各个应用程序维护赋值。
			const char *psCurFuncName;	//当前线程错误所在的函数信息，此变量由各个应用程序维护赋值。
			const char *psCurFileName;	//当前线程错误所在的文件信息，此变量由各个应用程序维护赋值。

			TThreadCond suspend;
			CLCriticalSection lock;
			CLCriticalSection * volatile current_mutex;
			TThreadCond * volatile current_cond;
			HTHREAD hThreadSelf;		//当前线程的句柄
			TThreadId tThreadId;		//线程的ID。
			bool init;					//表示线程是否初始化了
			struct tagThreadVar *next,**prev;
			int volatile abort;
			void *opt_info;				//线程关联的可选信息
#ifndef DBUG_OFF
			gptr dbug;					//调试头指针。
			char name[THREAD_NAME_SIZE+1];	//线程的名称
#endif
		} TThreadVar;


		/**
		 *     得到线程指向的信息。
		 */
		static TThreadVar *GetThreadVar();

		/**
		 *     得到当前线程的ID。
		 */
		static inline TThreadId GetCurrThreadId()
		{
#ifdef __WIN__
			return ::GetCurrentThreadId();
#else
			return pthread_self();
#endif
		}

		/**
		 *     得到当前线程的句柄。
		 */
		static inline HTHREAD GetCurrThreadHandle()
		{
#ifdef __WIN__
			return ::GetCurrentThread();
#else
			return pthread_self();
#endif
		}

		/**
		 *     得到线程的名称
		 */
		static inline const char* ThreadName()
		{
#ifdef DBUG_OFF
			return "no name";
#else
			char name_buff[100];
			TThreadVar *tmp=GetThreadVar();
			if (tmp->name[0] == '\0')
			{
				sprintf(name_buff,"T@%d", tmp->tThreadId);
				//strncpy(tmp->name, name_buff, THREAD_NAME_SIZE);
				memcpy(tmp->name,name_buff, THREAD_NAME_SIZE);
				if (tmp->name[THREAD_NAME_SIZE] != 0)
				{
					tmp->name[THREAD_NAME_SIZE] = '\0';
				}
			}
			return tmp->name;
#endif
		}

		/**
		 *     线程索引的函数集。
		 */
#ifdef USE_TLS

#ifdef __WIN__
//#pragma message( "Compiling hThreadKeySystem with USE_TLS " __FILE__)
#endif

#ifdef __WIN__
#define TThreadKey sb8
#else
#define TThreadKey pthread_key_t
#endif
#define THREAD_KEY_STATIC(Type,Value)  static TThreadKey Value
#define THREAD_KEY(Type,Value)  TThreadKey Value
		static inline bool ThreadKeyCreate(TThreadKey *pThreadKey)
		{
#ifdef __WIN__
			return (*pThreadKey=TlsAlloc())!=TLS_OUT_OF_INDEXES;
#else
			return pthread_key_create(pThreadKey, NULL) == 0;
#endif
		}
		static inline bool ThreadKeyDelete(TThreadKey *pThreadKey)
		{
#ifdef __WIN__
			return TlsFree((DWORD)*pThreadKey) == TRUE;
#else
			return pthread_key_delete (*pThreadKey)== 0;
#endif
		}

		static inline gptr GetThreadSpecific(TThreadKey *pThreadKey)
		{
#ifdef __WIN__
			return TlsGetValue((DWORD)*pThreadKey);
#else
			return pthread_getspecific (*pThreadKey);
#endif
		}

		static inline bool ThreadSetSpecific(TThreadKey *pThreadKey, gptr pNewValue, size_t vlen)
		{
#ifdef __WIN__
			return TlsSetValue((DWORD)*pThreadKey, pNewValue)  == TRUE;
#else
			return pthread_setspecific (*pThreadKey, pNewValue) == 0;
#endif
		}

		static inline bool ThreadSetSpecificPtr(TThreadKey *pThreadKey, gptr pNewValue, size_t vlen)
		{
			return ThreadSetSpecific(pThreadKey, pNewValue, vlen);
		}
#else
//#pragma message( "Compiling hThreadKeySystem without USE_TLS " __FILE__)
#define TThreadKey void
#define THREAD_KEY_STATIC(Type,Value) __declspec(thread) static Type Value
#define THREAD_KEY(Type,Value) __declspec(thread) Type Value
		static inline bool ThreadKeyCreate(TThreadKey *pThreadKey)
		{
			return true;
		}
		static inline bool ThreadKeyDelete(TThreadKey *pThreadKey)
		{
			return true;
		}
		static inline gptr GetThreadSpecific(TThreadKey *pThreadKey)
		{
			return pThreadKey;
		}
		static inline bool ThreadSetSpecific(TThreadKey *pThreadKey, gptr *pNewValue, size_t vLen)
		{
			memcpy(pThreadKey,pNewValue,vLen);
			return true;
		}
		static inline bool ThreadSetSpecificPtr(TThreadKey **pThreadKey, gptr *pNewValue, size_t vLen)
		{
			*pThreadKey = pNewValue;
			return true;
		}
#endif /* USE_TLS */

		static inline gptr GetThreadSpecificPtr(TThreadKey *pThreadKey)
		{
			return GetThreadSpecific(pThreadKey);
		}

		/**
		 *     创建一个新的线程，通过ThreadExit来关闭线程句柄。
		 *@param stackSize	线程的堆栈，为零表示和主线程的堆栈大小相同。
		 *@param iInitFlag	只是对WINDOWS有效，UNIX直接传0。0:表示立即运行; CREATE_SUSPENDED表示挂起，需要使用ResumeThread函数执行这个线程。
		 *@param pThreadId	线程的ID， 如果传入的地址为空，表示不返回此值。
		 *@param attr	线程的属性，如果为空，则不设置线程的属性，此属性会初始化线
		 *              程的化先级。
		 */
		static HTHREAD ThreadCreate(void *security, ub4 stackSize,
			TThreadHandler ExecFunc, void *param,
			ub4 iInitFlag,TThreadId *pThreadId,const TThreadAttr *attr);

		/**
		 *     关闭指定的线程的句柄。
		 *@param hThread 指定线程的句柄。
		 */
		static void ThreadExit(HTHREAD hThread);

		/**
		 *     线程的初始化函数
		 */
		static bool ThreadInit(HTHREAD hThread, TThreadId tThreadId);

		/**
		 *     线程的初始化函数，内部调用ThreadInit(HTHREAD hThread, TThreadId tThreadId)函数
		 */
		static bool ThreadInit();

		/**
		 *     线程的执行结束后，对遗留数据进行清理。
		 */
		static void ThreadEnd(void);

		/**
		 *     得到当前库内线程的数量。
		 */
		static ub4 GetThreadCount();
		
		static int ThreadDummy(int ret)
		{
			return ret;
		}
	};
}
