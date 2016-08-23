#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <errno.h>
#include <assert.h>
#include <float.h>

#ifndef PLATFORM_TYPE_AIX
#define PLATFORM_TYPE_AIX		1001
#endif

#ifndef PLATFORM_TYPE_LINUX
#define PLATFORM_TYPE_LINUX	1002
#endif

#ifndef PLATFORM_TYPE_HP
#define PLATFORM_TYPE_HP		1003
#endif

#ifndef PLATFORM_TYPE_SOLARIS
#define PLATFORM_TYPE_SOLARIS		1004
#endif


#include "CLConfig.h"

#ifdef __WIN__
#define _WIN32_WINNT 0x0501

#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
#include <windows.h>
#include <sys/locking.h>
#endif

#ifdef __WIN__
#include <process.h>
#define snprintf _snprintf
#else
#include <sys/ipc.h>
#if PLATFORM_TYPE==PLATFORM_TYPE_LINUX
#include <pthread.h>
#else
#include <thread.h>
#endif
#if PLATFORM_TYPE==PLATFORM_TYPE_HP
#include <sys/semaphore.h>
#else
#include <semaphore.h>
#endif
#endif

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __WIN__
//忽略 C++ 异常规范，但指示函数不是 __declspec(nothrow)
#pragma warning( disable : 4290 )
#include "io.h"
#else
#include <sys/shm.h>
#include <unistd.h>
#endif

#include <stdarg.h>

#include <string>
#include <list>
#include <vector>
#include <map>

#ifdef __WIN__
#include <Winsock2.h>
#define SOCKET_SIZE_TYPE int
#else
#include <sys/socket.h>
#include <netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
typedef int SOCKET;
#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#define SD_RECEIVE      0x00
#define SD_SEND         0x01
#define SD_BOTH         0x02
#define VOID void
#define SOCKET_SIZE_TYPE socklen_t
#endif


#ifdef HAVE_mit_thread
#define size_socket socklen_t	/* Type of last arg to accept */
#else
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#endif

#ifndef PATH_MAX
#define PATH_MAX	1023
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#define REGISTER register	/* Names to be placed in registers */
#ifndef USING_X
#define reg1 register
#define reg2 register
#define reg3 register
#define reg4 register
#define reg5 register
#define reg6 register
#define reg7 register
#define reg8 register
#define reg9 register
#define reg10 register
#define reg11 register
#define reg12 register
#define reg13 register
#define reg14 register
#define reg15 register
#define reg16 register
#endif

/*
  Sometimes we want to make sure that the variable is not put into
  a register in debugging mode so we can see its value in the core
*/
#ifndef DBUG_OFF
#define dbug_volatile volatile
#else
#define dbug_volatile
#endif


#if SIZEOF_LONG_LONG > 4
#define HAVE_LONG_LONG 1
#endif


/*
  The macros below are borrowed from include/linux/compiler.h in the
  Linux kernel. Use them to indicate the likelyhood of the truthfulness
  of a condition. This serves two purposes - newer versions of gcc will be
  able to optimize for branch predication, which could yield siginficant
  performance gains in frequently executed sections of the code, and the
  other reason to use them is for documentation
*/
#if !defined(__GNUC__) || (__GNUC__ == 2 && __GNUC_MINOR__ < 96)
#define __builtin_expect(x, expected_value) (x)
#endif
#define likely(x)	__builtin_expect((x),1)
#define unlikely(x)	__builtin_expect((x),0)

#ifndef FN_LIBCHAR
#ifdef __WIN__
#define FN_LIBCHAR	'\\'
#else
#define FN_LIBCHAR	'/'
#endif
#endif

#define FN_ROOTDIR	"\\"

#define NULLS		(char *) 0

#if !defined(__attribute__)
#define __attribute__(A)
#endif

#define CMP_NUM(a,b)    (((a) < (b)) ? -1 : ((a) == (b)) ? 0 : 1)
#define test(a)		((a) != 0 ? true : false)
#define SetMaxValue(src,dst)  { if ((src) < (dst)) (src)=(dst); }
#define SetMinValue(src,dst) { if ((src) > (dst)) (src)=(dst); }
#define test_all_bits(a,b) (((a) & (b)) == (b))

//得到数组元素的个数
#define GetArrayElementCount(A) ((ub4) (sizeof(A)/sizeof(A[0])))

//交换变量a，和b，其中t是类型。
#define SWAP(t,a,b)	{ register t dummy; dummy = a; a = b; b = dummy; }

/* sprintf does not always return the number of bytes :- */
#ifdef SPRINTF_RETURNS_INT
#define my_sprintf(buff,args) sprintf args
#else
#ifdef SPRINTF_RETURNS_PTR
#define my_sprintf(buff,args) ((int)(sprintf args - buff))
#else
#define my_sprintf(buff,args) ((ulong) sprintf args, (ulong) strlen(buff))
#endif
#endif

#define PTR_BYTE_DIFF(A,B) (my_ptrdiff_t) ((ub1*) (A) - (byte*) (B))
#define ADD_TO_PTR(ptr,size,type) (type) ((byte*) (ptr)+size)

	/* defines when allocating data */
#ifdef SAFEMALLOC
#else
#define my_checkmalloc()
#undef TERMINATE
#define TERMINATE(A) {}
#define QUICK_SAFEMALLOC
#define NORMAL_SAFEMALLOC
#define CALLER_INFO_PROTO   /* nothing */
#define CALLER_INFO         /* nothing */
#define ORIG_CALLER_INFO    /* nothing */
#endif

