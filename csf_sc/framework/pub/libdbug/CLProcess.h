#pragma once

#ifdef __WIN__
#define TProcessId DWORD
#else
#define TProcessId pid_t
#endif

#ifdef __WIN__
#include "Psapi.h"
#else
#if PLATFORM_TYPE == PLATFORM_TYPE_HP
#include <sys/pstat.h>
#else
#define PROCFS "/proc"
#define _STRUCTURED_PROC 1
#include <sys/procfs.h>
#endif
#endif

namespace NSPrime
{
	//进程结构。
	//solaris参考psinfo结构。
	typedef struct tagProcessInfo
	{
		//进程ID。
		TProcessId tProcessId;

		//可执行文件的名称，不包含路径信息。各个操作系统的不同，sExecFileName变量中存放的长度也不同，如solaris最多存放16个字符。
		char sExecFileName[PATH_MAX+1];

		//使用CPU的时间长度。得到的是以纳秒为单位的数值。纳秒等于一秒的十亿分之一。
		ub8 lUsedTime;

		//使用物理内存的大小，单位字节。
		unsigned long iPhiMemSize;

		//使用虚拟内存的大小，单位字节。
		unsigned long iPageMemSize;

		//进程的启动时间。得到的是以纳秒为单位的数值。纳秒等于一秒的十亿分之一。
		ub8	tStartupTime;
	}TProcessInfo;

	class CLProcess
	{
	public:
		/**
		 *     得到当前进程的ID。
		 */
		static TProcessId GetCurrProcessId();
		
		/**
		 *     判断进程ID tProcessId对应的进程是否存在。
		 */
		static bool ProcessExists(TProcessId tProcessId);

		/**
		 *     得到指定进程ID的进程信息。调用本函数之前，要求先把TProcessInfo结构中的tProcessId进行赋值。
		 */
		static ETYPE GetProcessInfo(TProcessInfo &tProcessInfo);
	};
}

