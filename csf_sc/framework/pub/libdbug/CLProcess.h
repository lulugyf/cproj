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
	//���̽ṹ��
	//solaris�ο�psinfo�ṹ��
	typedef struct tagProcessInfo
	{
		//����ID��
		TProcessId tProcessId;

		//��ִ���ļ������ƣ�������·����Ϣ����������ϵͳ�Ĳ�ͬ��sExecFileName�����д�ŵĳ���Ҳ��ͬ����solaris�����16���ַ���
		char sExecFileName[PATH_MAX+1];

		//ʹ��CPU��ʱ�䳤�ȡ��õ�����������Ϊ��λ����ֵ���������һ���ʮ�ڷ�֮һ��
		ub8 lUsedTime;

		//ʹ�������ڴ�Ĵ�С����λ�ֽڡ�
		unsigned long iPhiMemSize;

		//ʹ�������ڴ�Ĵ�С����λ�ֽڡ�
		unsigned long iPageMemSize;

		//���̵�����ʱ�䡣�õ�����������Ϊ��λ����ֵ���������һ���ʮ�ڷ�֮һ��
		ub8	tStartupTime;
	}TProcessInfo;

	class CLProcess
	{
	public:
		/**
		 *     �õ���ǰ���̵�ID��
		 */
		static TProcessId GetCurrProcessId();
		
		/**
		 *     �жϽ���ID tProcessId��Ӧ�Ľ����Ƿ���ڡ�
		 */
		static bool ProcessExists(TProcessId tProcessId);

		/**
		 *     �õ�ָ������ID�Ľ�����Ϣ�����ñ�����֮ǰ��Ҫ���Ȱ�TProcessInfo�ṹ�е�tProcessId���и�ֵ��
		 */
		static ETYPE GetProcessInfo(TProcessInfo &tProcessInfo);
	};
}

