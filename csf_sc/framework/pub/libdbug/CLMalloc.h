#pragma once

//#include "global.h"

/**
 *     ���뺯�������ص�ֵ��L���롣һ����˵L������С��ĵ�λ����1024��8196�ȣ�
 * A��ֵһ��Ҫ���ڻ����L�����򷵻ص�ֵû�����塣
 */
#define MY_ALIGN(A,L)	(((A) + (L) - 1) & ~((L) - 1))

/**
 *     ��double���룬��8�ֽڶ��롣
 */
#define ALIGN_SIZE(A)	MY_ALIGN((A),sizeof(double))

#define AllocRootInited(A) ((A)->minMalloc != 0)

#define SafeMalloc(A,B) NSPrime::CLMalloc::DebugMalloc((A),(B),__FILE__,__LINE__)
#define SafeFree(A,B) NSPrime::CLMalloc::DebugFree((A),(B),__FILE__,__LINE__)

namespace NSPrime
{
	/**
	 *     struct for once_alloc (block)�������ڴ�ء�
	 */
	typedef struct tagUsedMem
	{
		struct tagUsedMem *next;	   /* Next block in use */
		unsigned long	left;		   /* memory left in block  */
		unsigned long	size;		   /* size of block */
	} TUsedMem;

	/**
	 *     �ڴ�ص�ͷָ�롣
	 */
	typedef struct tagMemRoot
	{
		TUsedMem *free;                  /* blocks with free memory in it */
		TUsedMem *used;                  /* blocks almost without free memory */
		
		//���п�ʣ�����С�ֽ�����������е��ֽ���С�ڴ�ֵ����ѿ��ÿ��Ƶ����ÿ��С�
		unsigned int minMalloc;			

		// ָ��Ϊÿһ���������ֽ�����
		unsigned int blockSize;         /* initial block size */
		unsigned int blockNum;          /* allocated blocks counter */
		/* 
		first free block in queue test counter (if it exceed 
		MAX_BLOCK_USAGE_BEFORE_DROP block will be droped in 'used' list)
		*/
		unsigned int firstBlockUsage;
		void (*ErrorHandler)(void);
	}TMemRoot;

	class CLMalloc
	{
	private:
		/**
		 *     ��free����ת�Ƶ�used���������Ŀ��С��ֻ�е�ǰ��Ĵ�СС�ڴ�ֵ
		 * ���ܹ���Ϊ��ת�Ƶ�����֮һ��
		 */
		static const int ALLOC_MAX_BLOCK_TO_DROP			=	4096;

		/**
		 *     ��free����ת�Ƶ�used���������Ĳ��Դ�����ֻ�е����ԵĴ������ڵ�
		 * ��ֵ���ܹ���Ϊ��ת�Ƶ�����֮һ��
		 */
		static const int ALLOC_MAX_BLOCK_USAGE_BEFORE_DROP	=	10;

	public:
		static const int MALLOC_OVERHEAD					=	8;

		static const int MY_KEEP_PREALLOC					=	1;
		static const int MY_MARK_BLOCKS_FREE				=	2;  /* move used to free list and reuse them */
		/**
		 *     ��Malloc������ڴ���Ϣ�塣
		 */
		typedef struct tagMallocInfo
		{
			gptr ptr;
			unsigned long size;
			HTHREAD hThread;
			unsigned long lSerialNo;	//��������кš�
			const char *psFile;
			unsigned int iLine;
		}TMallocInfo;

#ifndef DBUG_OFF

		/**
		 *     �õ���ǰ�����Ѿ���Malloc����Ĵ���
		 */
		static unsigned long GetTotalMallocTimes();

		/**
		 *     �õ���ǰ�߳��Ѿ���Malloc������ֽ���
		 */
		static unsigned long GetMallocSize(HTHREAD hThread);

		/**
		 *     �õ���ǰ�߳�Malloc�Ĵ�������ָ��û���ͷŵ��ڴ���������
		 */
		static unsigned long GetMallocTimes(HTHREAD hThread);

		/**
		 *     �õ���ǰ�߳��Ѿ���Malloc������ڴ���Ϣ
		 */
		static const TDbLink* GetMallocLink(HTHREAD hThread);
#endif
		static gptr DebugMalloc(unsigned long size, myf myFlags, const char *psFile, unsigned int iLine);
		
		/*
		Malloc many pointers at the same time
		Only ptr1 can be free'd, and doing this will free all
		the memory allocated. ptr2, etc all point inside big allocated
		memory area.

		SYNOPSIS
		MultiMalloc()
		myFlags              Flags
		ptr1, length1      Multiple arguments terminated by null ptr
		ptr2, length2      ...
		...
		NULL
		*/
		static gptr MultiMalloc(myf myFlags, ...);

		/**
		 *     malloc�ķ�װ�������ڲ����¼����malloc�ĵ��ô�����
		 */
		static void *GlobalMalloc (unsigned long size);
		static inline void *Realloc (void *buff, size_t size)
		{
			return realloc(buff, size);
		}

		static inline void *Realloc (void *buff, size_t size, myf myFlags)
		{
			return Realloc(buff, size);
		}

		/**
		 *     free�ķ�װ����
		 */
		static void GlobalFree (gptr ptr);
		
		static inline void* AAlloc(unsigned int iSize)
		{
#ifdef __WIN__
			return _malloca(iSize);
#else
			return SafeMalloc(iSize, (myf)0);
#endif
		}

		static inline void AFree(gptr ptr)
		{
#ifdef __WIN__
			;
#else
			return SafeFree(ptr, (myf)0);
#endif
		}


		/* Free memory allocated with SafeMalloc */
		static void DebugFree(gptr ptr, myf myFlags, const char *psFile, unsigned int iLine);

		/* malloc and copy */
		static gptr MemDup(const char *from, unsigned int length, myf myFlags);

		/**
		 *     ����length+1���ֽڣ����ҿ���from�е�length���ַ�������ֵ��
		 */
		static char* StrMemDup(const char *from, unsigned long length, myf myFlags);
		static char* StrMemDup(const char *from, myf myFlags);

		/**
		 *     ��ʼ���ڴ�ص�ͷ�ڵ㡣
		 */
		static void InitAllocRoot(TMemRoot *memRoot, unsigned int blockSize);

		/**
		*     ���ڴ���з���һ��Size��С�Ŀռ䲢���ء�����ڴ���еĿ��ÿռ��Ѿ���
		* ��ʱ������Malloc�����ٷ���һ���ڴ浽�ڴ���У�ͬʱ���Ѿ���������ʹ������
		* �Ŀ�ʹ���ڴ��ת�Ƶ������ڴ���С�
		*/
		static gptr AllocRoot(TMemRoot *memRoot,unsigned long Size);

		/**
		 *    ����ڴ���е����п�Ϊ��ʹ��״̬��
		 */
		static void MarkBlocksFree(TMemRoot* root);

		/**
		 *     ���MyFlags��־��û��ָ��MY_MARK_BLOCKS_FREE��־�����ͷ��ڴ���е���
		 * �浽ϵͳ������͵���MarkBlocksFree��������ڴ���е����п�Ϊ��ʹ��״̬��
		 */
		static void FreeRoot(TMemRoot *root, myf MyFlags);

		/**
		 *     ���ڴ���з���len+1�ֽڳ��ȵ��ڴ棬��������ڴ濽������Ϊlen���ȵ���
		 * ������Ȼ��������ڴ�ĺ������һ�����ַ���
		 */
		static char *StrMakeRoot(TMemRoot *root,const char *str, unsigned long len);

		/**
		 *     �ڲ�����StrMakeRoot��������ͬ���ǵ��ú���StrDupRoot���ô��ַ����ĳ�
		 * �ȣ�����StrDupRoot�ڲ����Զ������ַ���str�ĳ��ȡ�
		 */
		static char *StrDupRoot(TMemRoot *root,const char *str);

		/**
		 *     ���ڴ���з���len�ֽڳ��ȵ��ڴ棬��������ڴ濽������Ϊlen���ȵ���
		 * ������ͬ����StrMakeRoot��ͬ��������ڴ�ĺ��治�����һ�����ַ���
		 */
		static char *MemDupRoot(TMemRoot *root,const char *str,unsigned long len);
	};
}

#ifndef DBUG_OFF
/**
 *   �õ��Ѿ���Malloc������ڴ��ֽ�����
 */
#define	GET_MALLOC_SIZE (NSPrime::CLMalloc::GetMallocSize(0))

/**
 *   �õ����������е�һ�ڵ㡣
 */
#define	GET_MALLOC_LINK (NSPrime::CLMalloc::GetMallocLink(0))

/**
 *   �õ����������е�һ���ڴ��ַ��ָ���ַ��
 */
#define	GET_MALLOC_PTR_ROOT (NSPrime::CLMalloc::GetMallocLink(0) != NULL)?((NSPrime::CLMalloc::TMallocInfo*)((NSPrime::CLMalloc::GetMallocLink(0))->ptr))->ptr:0
#else
#define	GET_MALLOC_SIZE (0)
#define	GET_MALLOC_LINK ((const NSPrime::TDbLink*)NULL)
#define	GET_MALLOC_PTR_ROOT 0
#endif
