/**
*     内存分配
*/

#include "libdbug.h"

namespace NSPrime
{
	gptr CLMalloc::DebugMalloc(unsigned long size, myf myFlags, const char *psFile, unsigned int iLine)
	{
		gptr point;
		DBUG_ENTER("DebugMalloc");
		//DBUG_PRINT("info",("size:%ld  myFlags:%d psFile:%s iLine:%d",(unsigned long)size, myFlags, CLDBug::BaseName(psFile), iLine));	--zhengwen modify at 20110427  根据CR62700 注释
		//DBUG_PRINT("info",("size:%lu  myFlags:%d psFile:%s iLine:%d",size, myFlags, CLDBug::BaseName(psFile), iLine));
		if (!size)
			size=1;					/* Safety */
		if ((point = (gptr)CLMalloc::GlobalMalloc(size)) == NULL)
		{
			NSPrime::CLGlobalErrors::SetLastError(errno);
			if (myFlags & MY_FAE)
				NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->ErrorHandlerHook=NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->FatalErrorHandlerHook;
			if (myFlags & (MY_FAE+MY_WME))
			{
				NSPrime::CLGlobalErrors::GetErrMsg(NSPrime::CLGlobalErrors::EE_OUTOFMEMORY,
					myf(0),size);
			}
			if (myFlags & MY_FAE)
				exit(1);
		}
		else if (myFlags & MY_ZEROFILL)
			memset(point,0, sizeof(size));
#ifndef DBUG_OFF

		//记录当前线程的分配信息。
		TDbLink* dbLink = (TDbLink*)NSPrime::CLMalloc::GlobalMalloc(sizeof(TDbLink));
		TMallocInfo* mallocInfo = (TMallocInfo*)NSPrime::CLMalloc::GlobalMalloc(sizeof(TMallocInfo));

		CLThread::TThreadList *ptThreadListCur = CLThread::GetThreadListNode(0);

		mallocInfo->ptr = point;
		mallocInfo->size = size;
		mallocInfo->hThread = ptThreadListCur->m_hThread;
		mallocInfo->lSerialNo = NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->lTotalSerialNo;
		mallocInfo->psFile = psFile;
		mallocInfo->iLine = iLine;
		dbLink->ptr = mallocInfo;

		dbLink->next_link=ptThreadListCur->m_ptMallocLink;
		ptThreadListCur->m_ptMallocLink=dbLink;
		ptThreadListCur->m_lMallocSize += size;

		//记录全局的分配信息。
		dbLink = (TDbLink*)NSPrime::CLMalloc::GlobalMalloc(sizeof(TDbLink));
		mallocInfo = (TMallocInfo*)NSPrime::CLMalloc::GlobalMalloc(sizeof(TMallocInfo));

		mallocInfo->ptr = point;
		mallocInfo->size = size;
		mallocInfo->hThread = ptThreadListCur->m_hThread;
		mallocInfo->lSerialNo = NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->lTotalSerialNo;
		mallocInfo->psFile = psFile;
		mallocInfo->iLine = iLine;
		dbLink->ptr = mallocInfo;

		dbLink->next_link=NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptMallocLink;
		NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptMallocLink=dbLink;
		NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocSize += size;
		//DBUG_PRINT("DebugMalloc", ("Malloc[%ld][%ld]", (unsigned long)mallocInfo->lSerialNo, (unsigned long)NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocTimes));  --zhengwen modify at 20110427  根据CR62700 注释
#endif
		//DBUG_PRINT("exit",("ptr: %lx",point));	--zhengwen modify at 20110427  根据CR62700 注释
		DBUG_RETURN(point);
	} /* SafeMalloc */


	/* Free memory allocated with SafeMalloc */
	void CLMalloc::DebugFree(gptr ptr, myf myFlags, const char *psFile, unsigned int iLine)
	{
		DBUG_ENTER("Free");
		//DBUG_PRINT("info",("ptr: %lx psFile:%s iLine:%d,[%ld]",ptr, psFile, iLine, NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocTimes));	--zhengwen modify at 20110427  根据CR62700 注释
		if (ptr)
		{
#ifndef DBUG_OFF
			REGISTER TDbLink *ptGlobalCur,*ptGlobalPre;
			for (ptGlobalPre = ptGlobalCur = NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptMallocLink; ptGlobalCur != NULL; ptGlobalCur = ptGlobalCur -> next_link)
			{
				if (((TMallocInfo*)(ptGlobalCur->ptr))->ptr==ptr)
				{
					REGISTER TDbLink *ptThrCur,*ptThrPre;
					CLThread::TThreadList *ptThreadListCur = CLThread::GetThreadListNode(((TMallocInfo*)(ptGlobalCur->ptr))->hThread);

					if (ptThreadListCur)
					{
						for (ptThrPre = ptThrCur = ptThreadListCur->m_ptMallocLink; ptThrCur != NULL; ptThrCur = ptThrCur -> next_link)
						{
							if (((TMallocInfo*)(ptThrCur->ptr))->ptr==ptr)
							{
								if (ptThrCur == ptThreadListCur->m_ptMallocLink)
								{
									ptThreadListCur->m_ptMallocLink = ptThreadListCur->m_ptMallocLink ->next_link;
								}
								ptThrPre->next_link = ptThrCur->next_link;
								ptThreadListCur->m_lMallocSize -= ((TMallocInfo*)ptThrCur->ptr)->size;
								CLMalloc::GlobalFree(ptThrCur->ptr);
								CLMalloc::GlobalFree(ptThrCur);
								break;
							}
							ptThrPre = ptThrCur;
						}
					}
					if (ptGlobalCur == NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptMallocLink)
					{
						NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptMallocLink = ptGlobalCur ->next_link;
					}
					ptGlobalPre->next_link = ptGlobalCur->next_link;
					NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocSize -= ((TMallocInfo*)ptGlobalCur->ptr)->size;
					//DBUG_PRINT("info", ("Free[%ld]", ((TMallocInfo*)(ptGlobalCur->ptr))->lSerialNo));		--zhengwen modify at 20110427  根据CR62700 注释
					CLMalloc::GlobalFree(ptGlobalCur->ptr);
					CLMalloc::GlobalFree(ptGlobalCur);
					break;
				}
				ptGlobalPre = ptGlobalCur;
			}
#endif
			CLMalloc::GlobalFree(ptr);
		}
		DBUG_VOID_RETURN;
	}

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
	gptr CLMalloc::MultiMalloc(myf myFlags, ...)
	{
		va_list args;
		char **ptr,*start,*res;
		unsigned int tot_length,length;
		DBUG_ENTER("MultiMalloc");

		va_start(args,myFlags);
		tot_length=0;
		while ((ptr=va_arg(args, char **)))
		{
			length=va_arg(args,uint);
			tot_length+=ALIGN_SIZE(length);
		}
		va_end(args);

		if (!(start=(char *) SafeMalloc(tot_length,myFlags)))
			DBUG_RETURN(0); /* purecov: inspected */

		va_start(args,myFlags);
		res=start;
		while ((ptr=va_arg(args, char **)))
		{
			*ptr=res;
			length=va_arg(args,uint);
			res+=ALIGN_SIZE(length);
		}
		va_end(args);
		DBUG_RETURN((gptr) start);
	}

	/* malloc and copy */
	gptr CLMalloc::MemDup(const char *from, unsigned int length, myf myFlags)
	{
		gptr ptr;
		DBUG_ENTER("MemDup");
		if ((ptr=SafeMalloc(length,myFlags)) != 0)
		{
			memcpy((char*) ptr, (char*) from,(size_t) length);
		}
		DBUG_RETURN(ptr);
	}

	/**
	 *     分配length+1个字节，并且拷贝from中的length个分符到返回值。
	 */
	char* CLMalloc::StrMemDup(const char *from, unsigned long length, myf myFlags)
	{
		gptr ptr;

		DBUG_ENTER("StrDup");
		if ((ptr=SafeMalloc(length+1,myFlags)) != 0)
		{
			memcpy((char*) ptr, (char*) from,(size_t) length);
			((char*) ptr)[length]=0;
		}
		DBUG_RETURN((char*)ptr);
	}

	/**
	 *     分配length+1个字节，并且拷贝from中的length个分符到返回值。
	 */
	char* CLMalloc::StrMemDup(const char *from, myf myFlags)
	{
		return StrMemDup(from, (unsigned int)strlen(from), myFlags);
	}
	/**
	 *     初始化内存池的头节点。
	 */
	void  CLMalloc::InitAllocRoot(TMemRoot *memRoot, unsigned int blockSize)
	{
		DBUG_ENTER("InitAllocRoot");
		//DBUG_PRINT("enter",("root: %lx", memRoot));		--zhengwen modify at 20110427  根据CR62700 注释
		memRoot->free = memRoot->used = 0;
		memRoot->minMalloc= 32;
		//memRoot->blockSize= blockSize-MALLOC_OVERHEAD-sizeof(TUsedMem)-8;
		memRoot->blockSize= blockSize;
		memRoot->ErrorHandler= NULL;
		
		/**
		 *    此值为后面的AllocRoot的函数中会做“>>2”操作，以调节下一分配块的大
		 * 小。
		 */
		memRoot->blockNum= 4;
		
		memRoot->firstBlockUsage= 0;
		DBUG_VOID_RETURN;
	}

	/**
	 *     从内存池中分配一段Size大小的空间并返回。如果内存池中的可用空间已经不
	 * 足时，调用Malloc函数再分配一段内存到内存池中，同时把已经不再满足使用条件
	 * 的可使用内存块转移到已用内存快中。
	 */
	gptr CLMalloc::AllocRoot(TMemRoot *memRoot,unsigned long Size)
	{
		unsigned long getSize, blockSize;
		gptr point;
		reg1 TUsedMem *next= 0;
		reg2 TUsedMem **prev;

		DBUG_ENTER("AllocRoot");
		Size= ALIGN_SIZE(Size);
		if ((*(prev= &memRoot->free)) != NULL)
		{
			/**
			 *     测试可用队列中的第一个可使用块，如果此块不再满足可使用的条
			 * 件，则把此块转移到已使用列表。
			 */
			if ((*prev)->left < Size &&
				memRoot->firstBlockUsage++ >= ALLOC_MAX_BLOCK_USAGE_BEFORE_DROP &&
				(*prev)->left < ALLOC_MAX_BLOCK_TO_DROP)
			{
				next= *prev;
				*prev= next->next;
				next->next= memRoot->used;
				memRoot->used= next;
				memRoot->firstBlockUsage= 0;
			}
			
			/**
			 *     从可用队列中查找第一个可用的块，注意此时已经更新了可用队列的
			 * 头指针。
			 */
			for (next= *prev ; next && next->left < Size ; next= next->next)
				prev= &next->next;
		}
		
		if (next == NULL)
		{
			/**
			 *     如果可使用队列中已经不存在可使用块了，此时就分配新的可使用块
			 * 到可用队列中。
			 */
			blockSize= memRoot->blockSize * (memRoot->blockNum >> 2);
			getSize= Size+ALIGN_SIZE(sizeof(TUsedMem));
			getSize= NSPrime::CLNumber::Max(getSize, blockSize);

			if (!(next = (TUsedMem*) SafeMalloc(getSize,(myf)(MY_WME))))
			{
				if (memRoot->ErrorHandler)
					(*memRoot->ErrorHandler)();
				DBUG_RETURN((gptr)0);
			}
			memRoot->blockNum++;
			next->next= *prev;
			next->size= getSize;
			next->left= getSize-ALIGN_SIZE(sizeof(TUsedMem));
			*prev=next;
		}

		/**
		 *     从块next中分配一块内存给point，并检查next块中剩余的空间，如果剩
		 * 余的空间小于minMalloc时把此块放入已用块中。
		 */
		point = (gptr) ((char*) next + (next->size-next->left));
		if ((next->left-= Size) < memRoot->minMalloc)
		{						/* Full block */
			*prev= next->next;				/* Remove block from list */
			next->next= memRoot->used;
			memRoot->used= next;
			memRoot->firstBlockUsage= 0;
		}
		DBUG_RETURN(point);
	}

	/**
	 *    标记内存池中的所有块为可使用状态。
	 */
	void CLMalloc::MarkBlocksFree(TMemRoot* root)
	{
		reg1 TUsedMem *next;
		reg2 TUsedMem **last;

		/**
		 *     标记可用队列中的剩余空间为未用状态。
		 */
		last= &root->free;
		for (next= root->free; next; next= *(last= &next->next))
		{
			next->left= next->size - ALIGN_SIZE(sizeof(TUsedMem));
		}

		/**
		 *     合并可用队列到已使用队列的队尾。
		 */
		*last= next=root->used;

		/**
		 *      标记已使用队列中的剩余空间为未用状态。
		 */
		for (; next; next= next->next)
		{
			next->left= next->size - ALIGN_SIZE(sizeof(TUsedMem));
		}

		/**
		 *     设置已使用队列中的值为空。
		 */
		root->used= NULL;
		root->firstBlockUsage= 0;
	}

	/**
	 *     如果MyFlags标志中没有指定MY_MARK_BLOCKS_FREE标志，则释放内存池中的内
	 * 存到系统，否则就调用MarkBlocksFree函数标记内存池中的所有块为可使用状态。
	 */
	void CLMalloc::FreeRoot(TMemRoot *root, myf MyFlags)
	{
		reg1 TUsedMem *next,*old;
		DBUG_ENTER("FreeRoot");
		//DBUG_PRINT("enter",("root: %lx  flags: %u", root, (unsigned int) MyFlags));	--zhengwen modify at 20110427  根据CR62700 注释

		if (!root)					
			DBUG_VOID_RETURN;
		if (MyFlags & MY_MARK_BLOCKS_FREE)
		{
			MarkBlocksFree(root);
			DBUG_VOID_RETURN;
		}

		for (next=root->used; next ;)
		{
			old=next; next= next->next ;
			SafeFree((gptr) old, 0);
		}
		for (next=root->free ; next ;)
		{
			old=next; next= next->next;
			SafeFree((gptr) old, 0);
		}
		root->used=root->free=NULL;
		root->blockNum= 4;
		root->firstBlockUsage= 0;
		DBUG_VOID_RETURN;
	}

	/**
	 *     从内存池中分配len+1字节长度的内存，并对这段内存拷贝长度为len长度的字
	 * 符串，然后在这段内存的后面加上一个空字符。
	 */
	char *CLMalloc::StrMakeRoot(TMemRoot *root,const char *str, unsigned long len)
	{
		char *pos;
		if ((pos=(char*)NSPrime::CLMalloc::AllocRoot(root,(uint)(len+1))))
		{
			memcpy(pos,str,(size_t)len);
			pos[len] = '\0';
		}
		return pos;
	}

	/**
	 *     内部调用StrMakeRoot函数，不同的是调用函数StrDupRoot不用传字符串的长
	 * 度，函数StrDupRoot内部会自动计算字符串str的长度。
	 */
	char *CLMalloc::StrDupRoot(TMemRoot *root,const char *str)
	{
		return StrMakeRoot(root, str, (unsigned int)strlen(str));
	}

	/**
	 *     从内存池中分配len字节长度的内存，并对这段内存拷贝长度为len长度的字
	 * 符串，同函数StrMakeRoot不同，在这段内存的后面不会加上一个空字符。
	 */
	char *CLMalloc::MemDupRoot(TMemRoot *root,const char *str,unsigned long len)
	{
		char *pos;
		if ((pos=(char*)NSPrime::CLMalloc::AllocRoot(root,(uint)len)))
		{
			memcpy(pos,str,(size_t)len);
		}
		return pos;
	}

	void *CLMalloc::GlobalMalloc (unsigned long size)
	{
		register char *new_malloc;

		if (!(new_malloc = (char*) malloc((size_t) size)))
			NSPrime::CLDBug::DbugExit ("out of memory");
#ifndef DBUG_OFF
		NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_thrLockMalloc.Lock();
		//printf("CLMalloc.GlobalMalloc: mallocAddressId=[%ld], m_lTotalMallocTimes=%d\n", new_malloc,m_lTotalMallocTimes);
		NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->lTotalSerialNo ++;
		NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocTimes ++;
		NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_thrLockMalloc.Unlock();
#endif
		return (new_malloc);
	}

	/**
	 *     free的封装函数
	 */
	void CLMalloc::GlobalFree (gptr ptr)
	{
#ifndef DBUG_OFF
		NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_thrLockMalloc.Lock();
		NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocTimes--;
		//printf("CLMalloc.GlobalMalloc: freeAddressId=[%ld],m_lTotalMallocTimes=%d\n", ptr,m_lTotalMallocTimes);
		NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_thrLockMalloc.Unlock();
#endif
		free(ptr);
	}

#ifndef DBUG_OFF

		/**
		 *     得到当前进程已经用Malloc分配的次数
		 */
		unsigned long CLMalloc::GetTotalMallocTimes()
		{
			return NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocTimes;
		}

		/**
		 *     得到当前线程已经用Malloc分配的字节数
		 */
		unsigned long CLMalloc::GetMallocSize(HTHREAD hThread=(HTHREAD)NULL)
		{
			CLThread::TThreadList *ptThreadListCur;

			if (hThread == (HTHREAD)NULL)
			{
				hThread = CLThread::GetCurrThreadHandle();
			}

			CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
			ptThreadListCur = CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList;
			while(ptThreadListCur)
			{
				if (ptThreadListCur->m_hThread == hThread)
				{
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
					return ptThreadListCur->m_lMallocSize;
				}
				ptThreadListCur = ptThreadListCur->m_ptThreadListNext;
			}
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();

			return 0;
		}

		/**
		 *     得到当前线程Malloc的次数，是指还没有释放的内存分配次数。
		 */
		unsigned long CLMalloc::GetMallocTimes(HTHREAD hThread=(HTHREAD)NULL)
		{
			CLThread::TThreadList *ptThreadListCur;

			if (hThread == (HTHREAD)NULL)
			{
				hThread = CLThread::GetCurrThreadHandle();
			}

			CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
			ptThreadListCur = CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList;
			while(ptThreadListCur)
			{
				if (ptThreadListCur->m_hThread == hThread)
				{
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
					return ptThreadListCur->m_lMallocTimes;
				}
				ptThreadListCur = ptThreadListCur->m_ptThreadListNext;
			}
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();

			return 0;
		}

		/**
		 *     得到当前线程已经用Malloc分配的内存信息
		 */
		const TDbLink* CLMalloc::GetMallocLink(HTHREAD hThread=(HTHREAD)NULL)
		{
			CLThread::TThreadList *ptThreadListCur;

			if (hThread == (HTHREAD)NULL)
			{
				hThread = CLThread::GetCurrThreadHandle();
			}

			CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Lock();
			ptThreadListCur = CLDbugLibInit::g_ptLibDbugGlobalVar->g_ptThreadList;
			while(ptThreadListCur)
			{
				if (ptThreadListCur->m_hThread == hThread)
				{
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();
					return ptThreadListCur->m_ptMallocLink;
				}
				ptThreadListCur = ptThreadListCur->m_ptThreadListNext;
			}
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_gLockSysGlobal.Unlock();

			return NULL;
		}
#endif
}

