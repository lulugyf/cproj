#pragma once

//#include "global.h"

/**
 *     对齐函数，返回的值以L对齐。一般来说L都是最小快的单位，如1024、8196等，
 * A的值一定要大于或等于L，否则返回的值没有意义。
 */
#define MY_ALIGN(A,L)	(((A) + (L) - 1) & ~((L) - 1))

/**
 *     以double对齐，即8字节对齐。
 */
#define ALIGN_SIZE(A)	MY_ALIGN((A),sizeof(double))

#define AllocRootInited(A) ((A)->minMalloc != 0)

#define SafeMalloc(A,B) NSPrime::CLMalloc::DebugMalloc((A),(B),__FILE__,__LINE__)
#define SafeFree(A,B) NSPrime::CLMalloc::DebugFree((A),(B),__FILE__,__LINE__)

namespace NSPrime
{
	/**
	 *     struct for once_alloc (block)，用于内存池。
	 */
	typedef struct tagUsedMem
	{
		struct tagUsedMem *next;	   /* Next block in use */
		unsigned long	left;		   /* memory left in block  */
		unsigned long	size;		   /* size of block */
	} TUsedMem;

	/**
	 *     内存池的头指针。
	 */
	typedef struct tagMemRoot
	{
		TUsedMem *free;                  /* blocks with free memory in it */
		TUsedMem *used;                  /* blocks almost without free memory */
		
		//块中可剩余的最小字节数，如果块中的字节数小于此值，则把可用块移到已用块中。
		unsigned int minMalloc;			

		// 指定为每一个块分配的字节数。
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
		 *     从free队列转移到used的最大容许的块大小，只有当前块的大小小于此值
		 * 才能够成为块转移的条件之一。
		 */
		static const int ALLOC_MAX_BLOCK_TO_DROP			=	4096;

		/**
		 *     从free队列转移到used的最大容许的测试次数，只有当测试的次数大于等
		 * 此值才能够成为块转移的条件之一。
		 */
		static const int ALLOC_MAX_BLOCK_USAGE_BEFORE_DROP	=	10;

	public:
		static const int MALLOC_OVERHEAD					=	8;

		static const int MY_KEEP_PREALLOC					=	1;
		static const int MY_MARK_BLOCKS_FREE				=	2;  /* move used to free list and reuse them */
		/**
		 *     用Malloc分配的内存信息体。
		 */
		typedef struct tagMallocInfo
		{
			gptr ptr;
			unsigned long size;
			HTHREAD hThread;
			unsigned long lSerialNo;	//分配的序列号。
			const char *psFile;
			unsigned int iLine;
		}TMallocInfo;

#ifndef DBUG_OFF

		/**
		 *     得到当前进程已经用Malloc分配的次数
		 */
		static unsigned long GetTotalMallocTimes();

		/**
		 *     得到当前线程已经用Malloc分配的字节数
		 */
		static unsigned long GetMallocSize(HTHREAD hThread);

		/**
		 *     得到当前线程Malloc的次数，是指还没有释放的内存分配次数。
		 */
		static unsigned long GetMallocTimes(HTHREAD hThread);

		/**
		 *     得到当前线程已经用Malloc分配的内存信息
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
		 *     malloc的封装函数，内部会记录调用malloc的调用次数。
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
		 *     free的封装函数
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
		 *     分配length+1个字节，并且拷贝from中的length个分符到返回值。
		 */
		static char* StrMemDup(const char *from, unsigned long length, myf myFlags);
		static char* StrMemDup(const char *from, myf myFlags);

		/**
		 *     初始化内存池的头节点。
		 */
		static void InitAllocRoot(TMemRoot *memRoot, unsigned int blockSize);

		/**
		*     从内存池中分配一段Size大小的空间并返回。如果内存池中的可用空间已经不
		* 足时，调用Malloc函数再分配一段内存到内存池中，同时把已经不再满足使用条件
		* 的可使用内存块转移到已用内存快中。
		*/
		static gptr AllocRoot(TMemRoot *memRoot,unsigned long Size);

		/**
		 *    标记内存池中的所有块为可使用状态。
		 */
		static void MarkBlocksFree(TMemRoot* root);

		/**
		 *     如果MyFlags标志中没有指定MY_MARK_BLOCKS_FREE标志，则释放内存池中的内
		 * 存到系统，否则就调用MarkBlocksFree函数标记内存池中的所有块为可使用状态。
		 */
		static void FreeRoot(TMemRoot *root, myf MyFlags);

		/**
		 *     从内存池中分配len+1字节长度的内存，并对这段内存拷贝长度为len长度的字
		 * 符串，然后在这段内存的后面加上一个空字符。
		 */
		static char *StrMakeRoot(TMemRoot *root,const char *str, unsigned long len);

		/**
		 *     内部调用StrMakeRoot函数，不同的是调用函数StrDupRoot不用传字符串的长
		 * 度，函数StrDupRoot内部会自动计算字符串str的长度。
		 */
		static char *StrDupRoot(TMemRoot *root,const char *str);

		/**
		 *     从内存池中分配len字节长度的内存，并对这段内存拷贝长度为len长度的字
		 * 符串，同函数StrMakeRoot不同，在这段内存的后面不会加上一个空字符。
		 */
		static char *MemDupRoot(TMemRoot *root,const char *str,unsigned long len);
	};
}

#ifndef DBUG_OFF
/**
 *   得到已经用Malloc分配的内存字节数。
 */
#define	GET_MALLOC_SIZE (NSPrime::CLMalloc::GetMallocSize(0))

/**
 *   得到分配链表中第一节点。
 */
#define	GET_MALLOC_LINK (NSPrime::CLMalloc::GetMallocLink(0))

/**
 *   得到分配链表中第一个内存地址的指针地址。
 */
#define	GET_MALLOC_PTR_ROOT (NSPrime::CLMalloc::GetMallocLink(0) != NULL)?((NSPrime::CLMalloc::TMallocInfo*)((NSPrime::CLMalloc::GetMallocLink(0))->ptr))->ptr:0
#else
#define	GET_MALLOC_SIZE (0)
#define	GET_MALLOC_LINK ((const NSPrime::TDbLink*)NULL)
#define	GET_MALLOC_PTR_ROOT 0
#endif
