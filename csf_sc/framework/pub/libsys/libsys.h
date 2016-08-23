#ifndef __libsys_h__
#define __libsys_h__
#include "libdbug.h"
#include <malloc.h>

/**
 *     得到结构体中成员在此结构体中的偏移量。
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
