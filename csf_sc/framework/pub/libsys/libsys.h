#ifndef __libsys_h__
#define __libsys_h__
#include "libdbug.h"
#include <malloc.h>

/**
 *     �õ��ṹ���г�Ա�ڴ˽ṹ���е�ƫ������
 */
#ifndef OffsetOf
#define OffsetOf(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#include "CLQsort.h"
#include "CLList.h"
#include "CLRbtree.h"
#include "CLString.h"
#include "CLSemaphore.h"
#include "CLQuery.h"
#include "CLThreadPool.h"
#include "CLArray.h"
#include "CLMd5.h"
#include "CLSha1.h"
#include "CLAse.h"
#include "CLThreadRwLock.h"
#include "CLBitmap.h"
#include "CLBit.h"
#include "CLShm.h"
#include "CLMsgQueue.h"
#endif //__libsys_h__
