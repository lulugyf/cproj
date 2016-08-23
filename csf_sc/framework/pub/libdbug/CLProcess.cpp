#include "libdbug.h"

namespace NSPrime
{
	/**
	 *     �õ���ǰ���̵�ID��
	 */
	TProcessId CLProcess::GetCurrProcessId()
	{
#ifdef __WIN__
		return ::GetCurrentProcessId();
#else
		return getpid();
#endif
	}
	
	
	/**
	 *     �жϽ���ID tProcessId��Ӧ�Ľ����Ƿ���ڡ�
	 */
	bool CLProcess::ProcessExists(TProcessId tProcessId)
	{
#ifdef __WIN__
		HANDLE hProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, tProcessId);
		if (hProcessHandle != NULL)
		{
			CloseHandle(hProcessHandle);
#else
		if (getpgid(tProcessId) != -1)	//ͨ������getpgid�����������Ƿ����
		{
#endif
			return true;
		}
		else
		{
			return false;
		}
	}

#ifdef __WIN__
	//�õ�������100����Ϊ��λ����ֵ���������һ���ʮ�ڷ�֮һ��
	static LONGLONG fileTimeToInt64 (const FILETIME * time)
	{
		ULARGE_INTEGER _time;
		_time.LowPart = time->dwLowDateTime;
		_time.HighPart = time->dwHighDateTime;
		return _time.QuadPart;
	}
#endif

	/**
	 *     �õ�ָ������ID�Ľ�����Ϣ�����ñ�����֮ǰ��Ҫ���Ȱ�TProcessInfo�ṹ�е�tProcessId���и�ֵ��
	 */
	ETYPE CLProcess::GetProcessInfo(TProcessInfo &tProcessInfo)
	{
		ETYPE iRet = 0;
#ifdef __WIN__
		HANDLE hProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, tProcessInfo.tProcessId);
		if (hProcessHandle != NULL)
		{
			HMODULE hMod;
			DWORD cbNeeded;

			//EnumProcessModules�������ܣ�ͨ���ƶ��Ľ���HANDLE�õ���Ӧ��ģ������
			if ( EnumProcessModules( hProcessHandle, &hMod, sizeof(hMod), &cbNeeded) )
			{
				int iRetLen = 0;
				if ((iRetLen = GetModuleBaseName(hProcessHandle, hMod, tProcessInfo.sExecFileName, sizeof(tProcessInfo.sExecFileName))) == 0)
				{
					iRet = GetLastError();
				}
			}
			else
			{
				iRet = GetLastError();
			}

			PROCESS_MEMORY_COUNTERS pmc;
			if ( GetProcessMemoryInfo( hProcessHandle, &pmc, sizeof(pmc)) )
			{
				tProcessInfo.iPhiMemSize = (unsigned long)pmc.WorkingSetSize;	//��ǰʹ�õ��ڴ棬��λ�ֽڡ�
				tProcessInfo.iPageMemSize = (unsigned long)pmc.PagefileUsage;	//��ǰʹ�õ��ڴ棬��λ�ֽڡ�
			}
			else
			{
				iRet = GetLastError();
			}

			FILETIME tCreationTime;
			FILETIME tExitTime;
			FILETIME tKernelTime;
			FILETIME tUserTime;
			if (GetProcessTimes(hProcessHandle, &tCreationTime, &tExitTime, &tKernelTime, &tUserTime))
			{
				tProcessInfo.tStartupTime = fileTimeToInt64(&tCreationTime) * 100;
				tProcessInfo.lUsedTime = (fileTimeToInt64(&tKernelTime) + fileTimeToInt64(&tUserTime)) * 100;
			}
			else
			{
				iRet = GetLastError();
			}
			CloseHandle(hProcessHandle);
		}
		else
		{
			iRet = GetLastError();
		}
#else
#if PLATFORM_TYPE == PLATFORM_TYPE_HP
		struct pst_static pstatic; 
		long lPageSize;
		if (pstat_getstatic(&pstatic, sizeof(pstatic), (size_t)1, 0) == -1)
		{ 
			iRet = errno;
			return iRet;
		}
		else
		{ 
			lPageSize = pstatic.page_size; 
		} 

		struct pst_status tProcStatus;
		(void)memset(&tProcStatus,0,sizeof(struct pst_status));
		if ((pstat_getproc (&tProcStatus, sizeof(tProcStatus), (size_t)0, tProcessInfo.tProcessId)) == -1)
		{
			iRet = errno;
			return iRet;
		}
		strcpy(tProcessInfo.sExecFileName, tProcStatus.pst_ucomm);
		tProcessInfo.lUsedTime = (tProcStatus.pst_utime+tProcStatus.pst_stime) * 1000000000;
		tProcessInfo.iPhiMemSize = (unsigned long)(( tProcStatus.pst_dsize +
													tProcStatus.pst_tsize +
													tProcStatus.pst_ssize +
													tProcStatus.pst_shmsize +
													tProcStatus.pst_mmsize +
													tProcStatus.pst_usize +
													tProcStatus.pst_iosize) * lPageSize);
		tProcessInfo.iPageMemSize = (unsigned long)((tProcStatus.pst_vdsize +
													 tProcStatus.pst_vtsize +
													 tProcStatus.pst_vssize +
													 tProcStatus.pst_vshmsize +
													 tProcStatus.pst_vmmsize +
													 tProcStatus.pst_vusize +
													 tProcStatus.pst_viosize) * lPageSize);
		tProcessInfo.tStartupTime = (tProcStatus.pst_start) * 1000000000;
#else
		psinfo_t currproc;
		int fd;
		char buf[30];
		snprintf(buf, sizeof(buf), "%s/%d/psinfo", PROCFS, tProcessInfo.tProcessId);
		if ((fd = open (buf, O_RDONLY)) < 0)
		{
			iRet = errno;
			return iRet;
		}
		if (read(fd, &currproc, sizeof(psinfo_t)) != sizeof(psinfo_t))
		{
			iRet = errno;
			return iRet;
		}
		(void)close(fd);
		strcpy(tProcessInfo.sExecFileName, currproc.pr_fname);
		tProcessInfo.lUsedTime = currproc.pr_time.tv_sec * 1000000000 + currproc.pr_time.tv_nsec;
		tProcessInfo.iPhiMemSize = (unsigned long)currproc.pr_rssize*1024;
		tProcessInfo.iPageMemSize = (unsigned long)currproc.pr_size*1024;
		tProcessInfo.tStartupTime = currproc.pr_start.tv_sec * 1000000000 + currproc.pr_start.tv_nsec;
#endif
#endif
		return iRet;
	}
}
