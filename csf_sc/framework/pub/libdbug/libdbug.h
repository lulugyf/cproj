#pragma once

#include "global.h"

/**
 *     线程开关
 */
#define THREAD

/**
 *     在DLL中用到此宏
 */
#define USE_TLS
//#undef USE_TLS

typedef void* gptr;
typedef struct tagDbLink {
	gptr ptr;	      /* Pointer to link's contents */
	struct tagDbLink *next_link;   /* Pointer to the next link */
} TDbLink;

typedef int myf;

/* General bitmaps for my_func's */
static const int MY_FFNF			=	1;	/* Fatal if file not found */
static const int MY_FNABP			=	2;	/* Fatal if not all bytes read/writen */
static const int MY_NABP			=	4;	/* Error if not all bytes read/writen */
static const int MY_FAE				=	8;	/* Fatal if any error */
static const int MY_WME				=	16;	/* Write message on error */
static const int MY_ZEROFILL		=	32;	/* SafeMalloc(), fill array with zero */
static const int MY_RAID        	=	64; /* Support for RAID (not the "Johnson&Johnson"-s one ;) */
static const int MY_FULL_IO			=	512;/* For db_read_file - loop intil I/O is complete */

/* Internal error numbers (for StrToSB8_10 functions) */
#define MY_ERRNO_EDOM		33
#define MY_ERRNO_ERANGE		34

#include "CLMap.h"
#include "CLNumber.h"
#include "CLCriticalSection.h"
#include "CLThread.h"
#include "CLThreadCond.h"
#include "CLDbug.h"
#include "CLMalloc.h"
#include "CLGlobalErrors.h"
#include "CLDbugLibInit.h"
#include "CLProcess.h"
