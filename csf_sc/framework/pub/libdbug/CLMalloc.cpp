/**
*     �ڴ����
*/

#include "libdbug.h"

namespace NSPrime
{
	gptr CLMalloc::DebugMalloc(unsigned long size, myf myFlags, const char *psFile, unsigned int iLine)
	{
		gptr point;
		DBUG_ENTER("DebugMalloc");
		//DBUG_PRINT("info",("size:%ld  myFlags:%d psFile:%s iLine:%d",(unsigned long)size, myFlags, CLDBug::BaseName(psFile), iLine));	--zhengwen modify at 20110427  ����CR62700 ע��
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

		//��¼��ǰ�̵߳ķ�����Ϣ��
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

		//��¼ȫ�ֵķ�����Ϣ��
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
		//DBUG_PRINT("DebugMalloc", ("Malloc[%ld][%ld]", (unsigned long)mallocInfo->lSerialNo, (unsigned long)NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocTimes));  --zhengwen modify at 20110427  ����CR62700 ע��
#endif
		//DBUG_PRINT("exit",("ptr: %lx",point));	--zhengwen modify at 20110427  ����CR62700 ע��
		DBUG_RETURN(point);
	} /* SafeMalloc */


	/* Free memory allocated with SafeMalloc */
	void CLMalloc::DebugFree(gptr ptr, myf myFlags, const char *psFile, unsigned int iLine)
	{
		DBUG_ENTER("Free");
		//DBUG_PRINT("info",("ptr: %lx psFile:%s iLine:%d,[%ld]",ptr, psFile, iLine, NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocTimes));	--zhengwen modify at 20110427  ����CR62700 ע��
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
					//DBUG_PRINT("info", ("Free[%ld]", ((TMallocInfo*)(ptGlobalCur->ptr))->lSerialNo));		--zhengwen modify at 20110427  ����CR62700 ע��
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
	 *     ����length+1���ֽڣ����ҿ���from�е�length���ַ�������ֵ��
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
	 *     ����length+1���ֽڣ����ҿ���from�е�length���ַ�������ֵ��
	 */
	char* CLMalloc::StrMemDup(const char *from, myf myFlags)
	{
		return StrMemDup(from, (unsigned int)strlen(from), myFlags);
	}
	/**
	 *     ��ʼ���ڴ�ص�ͷ�ڵ㡣
	 */
	void  CLMalloc::InitAllocRoot(TMemRoot *memRoot, unsigned int blockSize)
	{
		DBUG_ENTER("InitAllocRoot");
		//DBUG_PRINT("enter",("root: %lx", memRoot));		--zhengwen modify at 20110427  ����CR62700 ע��
		memRoot->free = memRoot->used = 0;
		memRoot->minMalloc= 32;
		//memRoot->blockSize= blockSize-MALLOC_OVERHEAD-sizeof(TUsedMem)-8;
		memRoot->blockSize= blockSize;
		memRoot->ErrorHandler= NULL;
		
		/**
		 *    ��ֵΪ�����AllocRoot�ĺ����л�����>>2���������Ե�����һ�����Ĵ�
		 * С��
		 */
		memRoot->blockNum= 4;
		
		memRoot->firstBlockUsage= 0;
		DBUG_VOID_RETURN;
	}

	/**
	 *     ���ڴ���з���һ��Size��С�Ŀռ䲢���ء�����ڴ���еĿ��ÿռ��Ѿ���
	 * ��ʱ������Malloc�����ٷ���һ���ڴ浽�ڴ���У�ͬʱ���Ѿ���������ʹ������
	 * �Ŀ�ʹ���ڴ��ת�Ƶ������ڴ���С�
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
			 *     ���Կ��ö����еĵ�һ����ʹ�ÿ飬����˿鲻�������ʹ�õ���
			 * ������Ѵ˿�ת�Ƶ���ʹ���б�
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
			 *     �ӿ��ö����в��ҵ�һ�����õĿ飬ע���ʱ�Ѿ������˿��ö��е�
			 * ͷָ�롣
			 */
			for (next= *prev ; next && next->left < Size ; next= next->next)
				prev= &next->next;
		}
		
		if (next == NULL)
		{
			/**
			 *     �����ʹ�ö������Ѿ������ڿ�ʹ�ÿ��ˣ���ʱ�ͷ����µĿ�ʹ�ÿ�
			 * �����ö����С�
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
		 *     �ӿ�next�з���һ���ڴ��point�������next����ʣ��Ŀռ䣬���ʣ
		 * ��Ŀռ�С��minMallocʱ�Ѵ˿�������ÿ��С�
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
	 *    ����ڴ���е����п�Ϊ��ʹ��״̬��
	 */
	void CLMalloc::MarkBlocksFree(TMemRoot* root)
	{
		reg1 TUsedMem *next;
		reg2 TUsedMem **last;

		/**
		 *     ��ǿ��ö����е�ʣ��ռ�Ϊδ��״̬��
		 */
		last= &root->free;
		for (next= root->free; next; next= *(last= &next->next))
		{
			next->left= next->size - ALIGN_SIZE(sizeof(TUsedMem));
		}

		/**
		 *     �ϲ����ö��е���ʹ�ö��еĶ�β��
		 */
		*last= next=root->used;

		/**
		 *      �����ʹ�ö����е�ʣ��ռ�Ϊδ��״̬��
		 */
		for (; next; next= next->next)
		{
			next->left= next->size - ALIGN_SIZE(sizeof(TUsedMem));
		}

		/**
		 *     ������ʹ�ö����е�ֵΪ�ա�
		 */
		root->used= NULL;
		root->firstBlockUsage= 0;
	}

	/**
	 *     ���MyFlags��־��û��ָ��MY_MARK_BLOCKS_FREE��־�����ͷ��ڴ���е���
	 * �浽ϵͳ������͵���MarkBlocksFree��������ڴ���е����п�Ϊ��ʹ��״̬��
	 */
	void CLMalloc::FreeRoot(TMemRoot *root, myf MyFlags)
	{
		reg1 TUsedMem *next,*old;
		DBUG_ENTER("FreeRoot");
		//DBUG_PRINT("enter",("root: %lx  flags: %u", root, (unsigned int) MyFlags));	--zhengwen modify at 20110427  ����CR62700 ע��

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
	 *     ���ڴ���з���len+1�ֽڳ��ȵ��ڴ棬��������ڴ濽������Ϊlen���ȵ���
	 * ������Ȼ��������ڴ�ĺ������һ�����ַ���
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
	 *     �ڲ�����StrMakeRoot��������ͬ���ǵ��ú���StrDupRoot���ô��ַ����ĳ�
	 * �ȣ�����StrDupRoot�ڲ����Զ������ַ���str�ĳ��ȡ�
	 */
	char *CLMalloc::StrDupRoot(TMemRoot *root,const char *str)
	{
		return StrMakeRoot(root, str, (unsigned int)strlen(str));
	}

	/**
	 *     ���ڴ���з���len�ֽڳ��ȵ��ڴ棬��������ڴ濽������Ϊlen���ȵ���
	 * ������ͬ����StrMakeRoot��ͬ��������ڴ�ĺ��治�����һ�����ַ���
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
	 *     free�ķ�װ����
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
		 *     �õ���ǰ�����Ѿ���Malloc����Ĵ���
		 */
		unsigned long CLMalloc::GetTotalMallocTimes()
		{
			return NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_lTotalMallocTimes;
		}

		/**
		 *     �õ���ǰ�߳��Ѿ���Malloc������ֽ���
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
		 *     �õ���ǰ�߳�Malloc�Ĵ�������ָ��û���ͷŵ��ڴ���������
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
		 *     �õ���ǰ�߳��Ѿ���Malloc������ڴ���Ϣ
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

