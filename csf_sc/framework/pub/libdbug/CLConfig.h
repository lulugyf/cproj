#pragma once

#ifndef PLATFORM_TYPE
#if defined(_WIN64) || defined(WIN64)
#define MACHINE_TYPE	"ia64"		/* Define to machine type name */
#else
#define MACHINE_TYPE	"i32"		/* Define to machine type name */
#ifndef _WIN32
#define _WIN32				/* Compatible with old source */
#endif
#ifndef __WIN32__
#define __WIN32__
#endif
#endif /* _WIN64 */
#ifndef __WIN__
#define __WIN__			      /* To make it easier in VC++ */
#endif
#endif

#ifndef __WIN__
#define HAVE_SYS_UN_H 1
#define HAVE_FCNTL 1
#endif

/**
 机器类型定义
 PLATFORM_TYPE
	HP
 */

#if PLATFORM_TYPE == PLATFORM_TYPE_HP
#include <iostream.h>
#else
#include <iostream>
#endif

#if PLATFORM_TYPE == PLATFORM_TYPE_AIX
#	include <extension.h>
#endif

#ifndef ORATYPES
#ifndef ub1
typedef unsigned char	ub1;
typedef signed char		sb1;
#endif

#ifndef ub2
typedef unsigned short	ub2;
typedef signed short	sb2;
#endif

#define SB3_MIN	((long) 0xff800000L)
#define SB3_MAX	0x007fffffL
#define SB2_MIN	((short int) 0x8000)
#define SB2_MAX	0x7FFF
#define SB1_MIN	((char) 0x80)
#define SB1_MAX	((char) 0x7F)

#ifndef ub4
typedef unsigned int	ub4;
typedef signed int	sb4;
#endif
#ifndef ub8
#ifdef __WIN__
typedef unsigned __int64	ub8;
typedef signed __int64	sb8;
#else
#if MACHINE_WORD == 64
typedef unsigned long	ub8;
typedef signed long	sb8;
#else
typedef unsigned long long	ub8;
typedef signed long long	sb8;
#endif
#endif
#endif//ub8
#endif /*ORATYPES*/

#define SB4_MIN	 (0x80000000L)
#define SB4_MAX	 (0x7FFFFFFF)
#define UB4_MAX	 (0xFFFFFFFF)
#define UB2_MAX	0xFFFF
#define UB3_MAX	  0xffffff

#define SB8_MIN	((sb8) 0x8000000000000000LL)
#define SB8_MAX	((sb8) 0x7FFFFFFFFFFFFFFFLL)
#define UB8_MAX	((ub8) 0xFFFFFFFFFFFFFFFFULL)


typedef ub2	ushort;
typedef ub4	uint;
#ifdef __WIN__
typedef ub4	ulong;
#endif

#if PLATFORM_TYPE == PLATFORM_TYPE_HP
typedef unsigned long ulong;
#endif

typedef ub8 ulonglong;
typedef sb8 longlong;
#ifdef __WIN__
typedef sb4 sigset_t;
#endif
#define longlong_defined

#ifdef OS64
#define SIZEOF_LONG		8
#else
#define SIZEOF_LONG		4
#endif

/*
  Max size that must be added to a so that we know Size to make
  adressable obj.
*/
#if SIZEOF_LONG == 4
typedef long		my_ptrdiff_t;
#else
typedef long long	my_ptrdiff_t;
#endif

#define SIZEOF_LONG_LONG	8

#define SIZEOF_OFF_T		8

#define HAVE_INNOBASE_DB 1
#undef HAVE_MYISAM_DB
#undef HAVE_MRG_MYISAM_DB
#define HAVE_GETCWD 1
#define HAVE_RENAME	1	/* Have rename() as function */
#define HAVE_ALLOCA 1
#define HAVE_QUERY_CACHE 1
#define HAVE_VIO 1
#ifdef __WIN__
#define HAVE_SMEM 1
#endif
//#define NO_FCNTL_NONBLOCK	/* No FCNTL */
#define HAVE_COMPRESS 1

//sprintf函数返回字节数
#define SPRINTF_RETURNS_INT

#ifdef __WIN__
#define key_t	ub8
#else
#endif

#define ETYPE   int

#ifdef __WIN__
#define F_RDLCK		_LK_NBLCK	/* read lock */
#define F_WRLCK		_LK_NBRLCK	/* write lock */
#define F_UNLCK		_LK_UNLCK	/* remove lock(s) */
#endif

#ifdef _WIN64
#define ulonglong2double(A) ((double) (ulonglong) (A))
#define my_off_t2double(A)  ((double) (my_off_t) (A))

#else
inline double ulonglong2double(ulonglong value)
{
  longlong nr=(longlong) value;
  if (nr >= 0)
    return (double) nr;
  return (18446744073709551616.0 + (double) nr);
}
#define my_off_t2double(A) ulonglong2double(A)
#endif /* _WIN64 */

