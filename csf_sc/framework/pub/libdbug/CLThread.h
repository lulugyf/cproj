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
		/*** �̺߳����ͱ�����ʼ***/
		/**
		 *     �̵߳ľ��
		 */

		/**
		 *     ��ǰ���������̵߳��������˱�����ThreadCreate����������һ����ThreadExit�м�һ��
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
			unsigned long  m_lMallocSize;		//��ֵ����CMalloc���еĺ��������޸ġ�
			unsigned long  m_lMallocTimes;	//��ֵ����CMalloc���еĺ��������޸ġ�
			struct tagThreadList*  m_ptThreadListNext;
			TDbLink*  m_ptMallocLink;  //��ֵ����CMalloc���еĺ��������޸ġ�
		}TThreadList;
		
		static TThreadList *GetThreadListNode(HTHREAD hThread);
#endif

		/**
		 *     �̰߳�ȫ�ı�����һ������
		 */
		static void InterlockedIncrement ( sb8 *lpAddend);

		/**
		 *     �̰߳�ȫ�ı�����һ������
		 */
		static void InterlockedIncrement ( sb8 *lpAddend, CLCriticalSection *ptLock);

		/**
		 *     �̰߳�ȫ�ı�����һ�͸�ֵ������
		 */
		static void InterlockedIncrement2 ( sb8 *lpAddend, sb8* plRetValue);

		/**
		 *     �̰߳�ȫ�ı�������һ��ֵ������
		 */
		static void InterlockedAddition ( sb8 *lpAddend, sb8 lValue);

		/**
		 *     �̰߳�ȫ�ı�����һ������
		 */
		static void InterlockedDecrement ( sb8 *lpAddend);

		/**
		 *     �̰߳�ȫ�ı�����һ������
		 */
		static void InterlockedDecrement ( sb8 *lpAddend, CLCriticalSection *ptLock);

		/**
		 *     �̰߳�ȫ�ı�����ȥһ��ֵ������
		 */
		static void InterlockedSubtract ( sb8 *lpAddend, sb8 lValue);

		/**
		 *     �̰߳�ȫ�ı�����ֵ������
		 */
		static void InterlockedExchange  ( sb8 *lpAddend, sb8 lValue);

		/*** �̺߳����ͱ�����ʼ***/
		/**
		 *     �߳�����
		 */
		typedef struct tagThreadAttr
		{
			sb8 dwStackSize;
			sb8 dwCreatingFlag;
			int priority;
		}TThreadAttr;

		typedef struct tagThreadVar
		{
			int thrErrno;				//��ǰ�̵߳Ĵ�����룬�˱����ɸ���Ӧ�ó���ά����ֵ��
			char sThrErrMsg[2047+1];	//��ǰ�̵߳Ĵ�����Ϣ���˱����ɸ���Ӧ�ó���ά����ֵ��
			int iCurLineNo;				//��ǰ�̴߳������ڵ�����Ϣ���˱����ɸ���Ӧ�ó���ά����ֵ��
			const char *psCurFuncName;	//��ǰ�̴߳������ڵĺ�����Ϣ���˱����ɸ���Ӧ�ó���ά����ֵ��
			const char *psCurFileName;	//��ǰ�̴߳������ڵ��ļ���Ϣ���˱����ɸ���Ӧ�ó���ά����ֵ��

			TThreadCond suspend;
			CLCriticalSection lock;
			CLCriticalSection * volatile current_mutex;
			TThreadCond * volatile current_cond;
			HTHREAD hThreadSelf;		//��ǰ�̵߳ľ��
			TThreadId tThreadId;		//�̵߳�ID��
			bool init;					//��ʾ�߳��Ƿ��ʼ����
			struct tagThreadVar *next,**prev;
			int volatile abort;
			void *opt_info;				//�̹߳����Ŀ�ѡ��Ϣ
#ifndef DBUG_OFF
			gptr dbug;					//����ͷָ�롣
			char name[THREAD_NAME_SIZE+1];	//�̵߳�����
#endif
		} TThreadVar;


		/**
		 *     �õ��߳�ָ�����Ϣ��
		 */
		static TThreadVar *GetThreadVar();

		/**
		 *     �õ���ǰ�̵߳�ID��
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
		 *     �õ���ǰ�̵߳ľ����
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
		 *     �õ��̵߳�����
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
		 *     �߳������ĺ�������
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
		 *     ����һ���µ��̣߳�ͨ��ThreadExit���ر��߳̾����
		 *@param stackSize	�̵߳Ķ�ջ��Ϊ���ʾ�����̵߳Ķ�ջ��С��ͬ��
		 *@param iInitFlag	ֻ�Ƕ�WINDOWS��Ч��UNIXֱ�Ӵ�0��0:��ʾ��������; CREATE_SUSPENDED��ʾ������Ҫʹ��ResumeThread����ִ������̡߳�
		 *@param pThreadId	�̵߳�ID�� �������ĵ�ַΪ�գ���ʾ�����ش�ֵ��
		 *@param attr	�̵߳����ԣ����Ϊ�գ��������̵߳����ԣ������Ի��ʼ����
		 *              �̵Ļ��ȼ���
		 */
		static HTHREAD ThreadCreate(void *security, ub4 stackSize,
			TThreadHandler ExecFunc, void *param,
			ub4 iInitFlag,TThreadId *pThreadId,const TThreadAttr *attr);

		/**
		 *     �ر�ָ�����̵߳ľ����
		 *@param hThread ָ���̵߳ľ����
		 */
		static void ThreadExit(HTHREAD hThread);

		/**
		 *     �̵߳ĳ�ʼ������
		 */
		static bool ThreadInit(HTHREAD hThread, TThreadId tThreadId);

		/**
		 *     �̵߳ĳ�ʼ���������ڲ�����ThreadInit(HTHREAD hThread, TThreadId tThreadId)����
		 */
		static bool ThreadInit();

		/**
		 *     �̵߳�ִ�н����󣬶��������ݽ�������
		 */
		static void ThreadEnd(void);

		/**
		 *     �õ���ǰ�����̵߳�������
		 */
		static ub4 GetThreadCount();
		
		static int ThreadDummy(int ret)
		{
			return ret;
		}
	};
}
