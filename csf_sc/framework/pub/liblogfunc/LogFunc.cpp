#include <string.h>
#include <stdlib.h>
#include "LogFunc.h"


#ifndef _PROCPATH
#define _PROCPATH ""
#endif
#ifdef WIN32
#include <windows.h>
#define GETPID GetCurrentProcessId
#else
#include <sys/time.h>
#include <unistd.h>
#define GETPID getpid
#endif

static TOprInfo g_tOprInfo;	//������Ϣ

void GlobalInitOprInfo(TOprInfo &tOprInfo)
{
	memcpy(&g_tOprInfo, &tOprInfo, sizeof(tOprInfo));
}

#ifdef WIN32
/**
* UnicodeToAnsi converts the Unicode string pszW to an ANSI string
* and returns the ANSI string through ppszA. Space for the 
* the converted string is allocated by UnicodeToAnsi.
*/ 
HRESULT __fastcall UnicodeToAnsi(LPCOLESTR pszW, LPSTR ppszA)
{  
	ULONG cbAnsi, cCharacters;    DWORD dwError;    
	// If input is null then just return the same.   
	if (pszW == NULL) 
	{      
		*ppszA = NULL;
		return NOERROR;   
	}   
	cCharacters = wcslen(pszW)+1;   
	// Determine number of bytes to be allocated for ANSI string. An    
	// ANSI string can have at most 2 bytes per character (for Double   
	// Byte Character Strings.)   
	cbAnsi = cCharacters*2;   
	// Convert to ANSI. 
	if (0 == WideCharToMultiByte(CP_ACP, 0, pszW, cCharacters, ppszA,                  cbAnsi, NULL, NULL))   
	{   
		dwError = GetLastError(); 
		return HRESULT_FROM_WIN32(dwError);   
	}
	return NOERROR;
}
#endif

static bool GetGlobalProgramName(char* psCurrProgramName)
{
	char sCurrProgramName[1023+1];	//��ǰ��������ơ�
	memset(sCurrProgramName, 0, sizeof(sCurrProgramName));
#ifdef WIN32
     LPWSTR *szArglist;
     int nArgs;

	 szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
     if( NULL == szArglist )
     {
        return false;
     }
	 UnicodeToAnsi(szArglist[0], sCurrProgramName);
	 sCurrProgramName[1023]=0;
	 LocalFree(szArglist);
#else
	if(strlen(_PROCPATH)!=0)
	{
		char procpath[1024];
		sprintf(procpath, "/proc/%d/%s", GETPID(), _PROCPATH);
		if(readlink(procpath, sCurrProgramName, 1024)<0)
		{
			if (getenv("_")==NULL)
			{
				psCurrProgramName[0] = '\0';
				return false;
			}
			strncpy(sCurrProgramName, getenv("_"), 1023);
			sCurrProgramName[1023]=0;
		}
	}
	else
	{
		if (getenv("_")==NULL)
		{
			psCurrProgramName[0] = '\0';
			return false;
		}
		strncpy(sCurrProgramName, getenv("_"), 1023);
		sCurrProgramName[1023]=0;
	}
#endif
	const char *s1=NULL, *s2=NULL;
	s1=strrchr(sCurrProgramName, '\\');
	s2=strrchr(sCurrProgramName, '/');

	if(s1<s2) s1=s2;
	if(s1==NULL)
		s1=sCurrProgramName;
	else
		++s1;
	strcpy(psCurrProgramName, s1);
	return true;
}

/**
 *    ��־�Ŀ����ຯ���������ڲ��࣬����ͷ�ļ������֡�
 */
class LogCtrl
{
public:
	LogCtrl()
	{
		memset(&m_tBeginTime, 0, sizeof(m_tBeginTime));
		m_iRefreshSecond = 3600;	//Ĭ��һ��Сʱˢ��һ�Ρ�
		m_bPrintLog = true;	//Ĭ�ϴ�ӡ��־
		m_iLogDeep = 0;	//��ӡ��־����ȣ�0��ʾ��������ȣ���ӡ������ȵ���־��
		memset(m_sTimeFormat, 0, sizeof(m_sTimeFormat));	//ʱ���ʽ�Ķ���
		memset(m_sInFormat, 0, sizeof(m_sInFormat));	//���뺯����ӡ��־�ĸ�ʽ
		memset(m_sOutFormat, 0, sizeof(m_sOutFormat));	//�˳�������ӡ��־�ĸ�ʽ
		m_bPrintProgram = false;	//����ֻ���ض��ĳ���Ŵ�ӡ��ֻ�е�m_bPrintLogΪfalse������£��˱�������Ч��
		memset(m_sCurrProgramName, 0, sizeof(m_sCurrProgramName));
		memset(m_sPrintBuffer, 0, sizeof(m_sPrintBuffer));
		m_iErrorStatus = 0;
		m_iNextDeep = 0;
		m_bIsLoad = false;
	}
	~LogCtrl()
	{
	}
public:
	enum
	{
		ERR_PROGRAM_NAME = 1,	//������ļ�����
		ERR_ENV_LOG_FUNC_CFG = 2,		//����������ļ���������
		ERR_OPEN_LOG_FUNC_CFG = 3,		//�������ļ�����
	};
public:
	/**
	 *    ������־�����ļ�
	 */
	bool LoadCfg()
	{
		memset(m_sCurrProgramName, 0, sizeof(m_sCurrProgramName));
		if (!GetGlobalProgramName(m_sCurrProgramName))
		{
			m_iErrorStatus = ERR_PROGRAM_NAME;
			return false;
		}

		//TODO:���������ļ�
		if (getenv("LOG_FUNC_CFG") == NULL)
		{
			m_iErrorStatus = ERR_ENV_LOG_FUNC_CFG;
			return false;
		}
		FILE *fp = NULL;
		if ((fp=fopen(getenv("LOG_FUNC_CFG"), "r")) == NULL)
		{
			m_iErrorStatus = ERR_OPEN_LOG_FUNC_CFG;
			return false;
		}
		
		m_bPrintProgram = false;	//Ĭ�Ϲر�
		char sLine[1023+1];
		memset(sLine, 0, sizeof(sLine));
		while(fgets(sLine, 1023, fp))
		{
			char *ps = NULL;
			if (sLine[0] == '#')
			{
				continue;
			}
			else if (strncmp(sLine, "REFRESH_SECOND", strlen("REFRESH_SECOND")) == 0)
			{
				ps = sLine + strlen("REFRESH_SECOND") + 1;
				m_iRefreshSecond = atoi(ps);
			}
			else if (strncmp(sLine, "PRINT_LOG", strlen("PRINT_LOG")) == 0)
			{
				ps = sLine + strlen("PRINT_LOG") + 1;
				if (strncmp(ps, "OFF", 3) == 0)
				{
					m_bPrintLog = false;
				}
				else
				{
					m_bPrintLog = true;
				}
			}
			else if (strncmp(sLine, "LOG_DEEP", strlen("LOG_DEEP")) == 0)
			{
				ps = sLine + strlen("LOG_DEEP") + 1;
				m_iLogDeep = atoi(ps);
			}
			else if (strncmp(sLine, "TIME_FORMAT", strlen("TIME_FORMAT")) == 0)
			{
				ps = sLine + strlen("TIME_FORMAT") + 1 + 1; //��������
				char *psEnd = strchr(ps, '"');
				if (psEnd)
				{
					strncpy(m_sTimeFormat, ps, psEnd - ps);
				}
			}
			else if (strncmp(sLine, "IN_FORMAT", strlen("IN_FORMAT")) == 0)
			{
				ps = sLine + strlen("IN_FORMAT") + 1 + 1;
				char *psEnd = strchr(ps, '"');
				if (psEnd)
				{
					strncpy(m_sInFormat, ps, psEnd - ps);
				}
			}
			else if (strncmp(sLine, "OUT_FORMAT", strlen("OUT_FORMAT")) == 0)
			{
				ps = sLine + strlen("OUT_FORMAT") + 1 + 1;
				char *psEnd = strchr(ps, '"');
				if (psEnd)
				{
					strncpy(m_sOutFormat, ps, psEnd - ps);
				}
			}
			else if (strncmp(sLine, "PRINT_PROGRAM", strlen("PRINT_PROGRAM")) == 0)
			{
				ps = sLine + strlen("PRINT_PROGRAM") + 1;
				if (strncmp(ps, m_sCurrProgramName, strlen(m_sCurrProgramName)) == 0)
				{
					m_bPrintProgram = true;
				}
			}
		}
		
		fclose(fp);
		return true;
	}

	/**
	 *    ������־�����ļ�
	 */
	bool ReLoadCfg()
	{
		return LoadCfg();
	}

	bool IsPrintLog(LogFunc *pLogFunc)
	{
		if (!m_bPrintLog)
		{
			if (!m_bPrintProgram)
			{
				return false;	//�������ӡ��־������
			}
		}
		if (m_iLogDeep != 0)
		{
			if (pLogFunc->m_iCurrentDeep > m_iLogDeep)
			{
				return false;
			}
		}
		return true;
	}

	/**
	 *    ���������ļ���ӡ����������־��Ϣ��
	 */
	void PrintBeginLog(LogFunc *pLogFunc)
	{
		PrintLog(pLogFunc, m_sInFormat);
	}

	/**
	 *    ���������ļ���ӡ�����˳���־��Ϣ��
	 */
	void PrintEndLog(LogFunc *pLogFunc)
	{
		PrintLog(pLogFunc, m_sOutFormat);
	}

	/**
	 *    �õ�ˢ�µ�ʱ�������������
	 */
	inline unsigned int GetRefreshSecond()
	{
		return m_iRefreshSecond;
	}

	/**
	 *    �õ���ǰ��������ơ�
	 */
	inline const char*  GetCurrProgramName()
	{
		return m_sCurrProgramName;
	}

	/**
	 *    ���õ�ǰ��������ƣ��˺����ڽ������ʱ���á�
	 */
	inline void SetCurrProgramName(const char* psCurrProgramName)
	{
		memset(m_sCurrProgramName, 0, sizeof(m_sCurrProgramName));
		strncpy(m_sCurrProgramName, psCurrProgramName, 255);
	}

	inline unsigned int GetErrorStatus()
	{
		return m_iErrorStatus;
	}

	inline void SetErrorStatus(unsigned int iErrorStatus)
	{
		m_iErrorStatus = iErrorStatus;
	}

	inline unsigned int GetNextLevel()
	{
		return m_iNextDeep ++;
	}

	inline void SetNextLevel(unsigned int iNextDeep)
	{
		m_iNextDeep = iNextDeep;
	}

	inline bool IsLoad()
	{
		return m_bIsLoad;
	}
private:
	/**
	 *    ��ӡ��־��
	 */
	void PrintLog(LogFunc *pLogFunc, const char *psFormatStr)
	{
		if (!IsPrintLog(pLogFunc))
		{
				return;
		}

		unsigned int iCurIndex = 0;
		memset(m_sPrintBuffer, 0, sizeof(m_sPrintBuffer));
		//��ӡ����������־
		const char *ps = psFormatStr, *psEnd = NULL;
		while(*ps)
		{
			if (ps[0] == '$')
			{
				ps ++;	//����'$'����
				ps ++;	//����'['����
				if ((psEnd = strchr(ps, ']')) == NULL)
				{
					return;	//���ұ�������
				}
				PrintVars(pLogFunc, iCurIndex, ps, psEnd - ps);	//$[VAR_NAME]
				ps = psEnd + 1;	//����']'����
			}
			else
			{
				m_sPrintBuffer[iCurIndex ++] = *(ps++);
			}
		}
		m_sPrintBuffer[iCurIndex ++] = '\n';
		m_sPrintBuffer[iCurIndex ++] = '\0';
		m_sPrintBuffer[4095] = '\0';
		fputs(m_sPrintBuffer, pLogFunc->m_pLogFileHandle);
	}

	void PrintTime(LogFunc *pLogFunc, unsigned int &iCurIndex, struct timeb &tPrintTime)
	{
		char sIntStr[64];
		struct tm *timeinfo = localtime(&tPrintTime.time);

		const char *ps = m_sTimeFormat, *psEnd = NULL;
		while(ps[0])
		{
			switch(ps[0])
			{
			case 'Y':
			case 'M':
			case 'D':
			case 'H':
			case 'S':
				{
					if (strncmp(ps, "YY", 2) == 0)
					{
						memset(sIntStr, 0, sizeof(sIntStr));
						sprintf(sIntStr, "%02d", (timeinfo->tm_year + 1900) % 100);
						strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
						iCurIndex += strlen(sIntStr);
						ps += 2;
					}
					else if (strncmp(ps, "MM", 2) == 0)
					{
						memset(sIntStr, 0, sizeof(sIntStr));
						sprintf(sIntStr, "%02d", timeinfo->tm_mon + 1);
						strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
						iCurIndex += strlen(sIntStr);
						ps += 2;
					}
					else if (strncmp(ps, "DD", 2) == 0)
					{
						memset(sIntStr, 0, sizeof(sIntStr));
						sprintf(sIntStr, "%02d", timeinfo->tm_mday);
						strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
						iCurIndex += strlen(sIntStr);
						ps += 2;
					}
					else if (strncmp(ps, "HH", 2) == 0)
					{
						memset(sIntStr, 0, sizeof(sIntStr));
						sprintf(sIntStr, "%02d", timeinfo->tm_hour);
						strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
						iCurIndex += strlen(sIntStr);
						ps += 2;
					}
					else if (strncmp(ps, "MI", 2) == 0)
					{
						memset(sIntStr, 0, sizeof(sIntStr));
						sprintf(sIntStr, "%02d", timeinfo->tm_min);
						strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
						iCurIndex += strlen(sIntStr);
						ps += 2;
					}
					else if (strncmp(ps, "SS", 2) == 0)
					{
						memset(sIntStr, 0, sizeof(sIntStr));
						sprintf(sIntStr, "%02d", timeinfo->tm_sec);
						strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
						iCurIndex += strlen(sIntStr);
						ps += 2;
					}
					else if (strncmp(ps, "MLL", 3) == 0)
					{
						memset(sIntStr, 0, sizeof(sIntStr));
						sprintf(sIntStr, "%02d", tPrintTime.millitm);
						strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
						iCurIndex += strlen(sIntStr);
						ps += 3;
					}
					break;
				}
			default:
				{
					m_sPrintBuffer[iCurIndex ++] = *(ps++);
				}
			}
		}
	}

	/**
	 *    ��ӡ������
	 */
	void PrintVars(LogFunc *pLogFunc, unsigned int &iCurIndex, const char *psVarName, unsigned iVarNameLength)
	{
		if (strncmp(psVarName, "FILE_NAME", iVarNameLength) == 0)
		{
			strcpy(m_sPrintBuffer + iCurIndex, pLogFunc->m_psFile);
			iCurIndex += strlen(pLogFunc->m_psFile);
		}
		else if (strncmp(psVarName, "FUNC_NAME", iVarNameLength) == 0)
		{
			const char *ps=strchr(pLogFunc->m_psFunc, '(');
			if ((ps == NULL) || (ps == pLogFunc->m_psFunc))
			{
				strcpy(m_sPrintBuffer + iCurIndex, pLogFunc->m_psFunc);
				iCurIndex += strlen(pLogFunc->m_psFunc);
			}
			else
			{
				strncpy(m_sPrintBuffer + iCurIndex, pLogFunc->m_psFunc, ps - pLogFunc->m_psFunc);
				iCurIndex += ps - pLogFunc->m_psFunc;
			}
		}
		else if (strncmp(psVarName, "LINE_ID", iVarNameLength) == 0)
		{
			char sIntStr[64];
			memset(sIntStr, 0, sizeof(sIntStr));
			sprintf(sIntStr, "%d", pLogFunc->m_iLine);
			strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
			iCurIndex += strlen(sIntStr);
		}
		else if (strncmp(psVarName, "BEGIN_TIME", iVarNameLength) == 0)
		{
			PrintTime(pLogFunc, iCurIndex, m_tBeginTime);
		}
		else if (strncmp(psVarName, "END_TIME", iVarNameLength) == 0)
		{
			PrintTime(pLogFunc, iCurIndex, m_tEndTime);
		}
		else if (strncmp(psVarName, "DURATION", iVarNameLength) == 0)
		{
			char sIntStr[64];
			memset(sIntStr, 0, sizeof(sIntStr));
			sprintf(sIntStr, "%08d", (m_tEndTime.time - m_tBeginTime.time) * 1000 + m_tEndTime.millitm - m_tBeginTime.millitm);
			strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
			iCurIndex += strlen(sIntStr);
		}
		else if (strncmp(psVarName, "PID", iVarNameLength) == 0)
		{
			char sIntStr[64];
			memset(sIntStr, 0, sizeof(sIntStr));
			sprintf(sIntStr, "%d", GETPID());
			strcpy(m_sPrintBuffer + iCurIndex, sIntStr);
			iCurIndex += strlen(sIntStr);
		}
		else if (strncmp(psVarName, "SERVICE_NO", iVarNameLength) == 0)
		{
			strcpy(m_sPrintBuffer + iCurIndex, g_tOprInfo.sServiceNo);
			iCurIndex += strlen(g_tOprInfo.sServiceNo);
		}
		else if (strncmp(psVarName, "LOGIN_NO", iVarNameLength) == 0)
		{
			strcpy(m_sPrintBuffer + iCurIndex, g_tOprInfo.sLoginNo);
			iCurIndex += strlen(g_tOprInfo.sLoginNo);
		}
		else if (strncmp(psVarName, "OP_CODE", iVarNameLength) == 0)
		{
			strcpy(m_sPrintBuffer + iCurIndex, g_tOprInfo.sOpCode);
			iCurIndex += strlen(g_tOprInfo.sOpCode);
		}
		else if (strncmp(psVarName, "CONTACT_ID", iVarNameLength) == 0)
		{
			strcpy(m_sPrintBuffer + iCurIndex, g_tOprInfo.sContactId);
			iCurIndex += strlen(g_tOprInfo.sContactId);
		}
		else if (strncmp(psVarName, "LOGIN_ACCEPT", iVarNameLength) == 0)
		{
			strcpy(m_sPrintBuffer + iCurIndex, g_tOprInfo.sLoginAccept);
			iCurIndex += strlen(g_tOprInfo.sLoginAccept);
		}
	}

public:
	/**
	 *<summary>��¼�����Ľ���ʱ��</summary>
	 */
	struct timeb m_tBeginTime;

	/**
	 *<summary>��¼�����Ľ���ʱ��</summary>
	 */
	struct timeb m_tEndTime;
private:
	unsigned int m_iRefreshSecond;	//ˢ�µ�ʱ������������㡣
	bool m_bPrintLog;	//�Ƿ��ӡ��־�Ŀ���
	unsigned int m_iLogDeep;	//��ӡ��־�����
	char m_sTimeFormat[255+1];	//ʱ���ʽ�Ķ���
	char m_sInFormat[255+1];	//���뺯����ӡ��־�ĸ�ʽ
	char m_sOutFormat[255+1];	//�˳�������ӡ��־�ĸ�ʽ
	
	//����ֻ���ض��ĳ���Ŵ�ӡ��ֻ�е�m_bPrintLogΪfalse������£��˱�������Ч��
	//��Ҫ���PRINT_PROGRAM���Ƿ���������̵ĳ������ƣ��Ա����ô˱�����true����false��
	bool m_bPrintProgram;

	char m_sCurrProgramName[1023+1];	//��ǰ��������ơ�
	unsigned int m_iErrorStatus;	//����״̬��
	unsigned int m_iNextDeep;	//��һ����ȡ�
	bool m_bIsLoad;		//�Ƿ���������ļ��ˡ�
	char m_sPrintBuffer[4095+1];	//��ӡʹ�õ���ʱ��������
};

static LogCtrl g_LogCtrl;	//��־��ӡ������

LogFunc::LogFunc(const char *psKeyWord, const void *pInParam, const void * pErrorInfo, FILE *pLogFileHandle,
	const char *psFile, const char *psFunc, unsigned int iLine)
	: m_psKeyWord(psKeyWord), m_pInParam(pInParam), m_pErrorInfo(pErrorInfo), m_pLogFileHandle(pLogFileHandle),
	m_psFile(psFile), m_psFunc(psFunc),	m_iLine(iLine), m_pvExternInfo(NULL)
{
	struct timeb timebuffer;
	memset(&timebuffer, 0, sizeof(timebuffer));
	ftime(&timebuffer);

	if (g_LogCtrl.GetErrorStatus())
	{
		//��־��״̬����
		return;
	}

	if (!g_LogCtrl.IsLoad())
	{
		if (!g_LogCtrl.LoadCfg())	//���������ļ�
		{
			return;
		}
	}
	else if ((g_LogCtrl.m_tBeginTime.time + g_LogCtrl.GetRefreshSecond()) <= timebuffer.time)
	{
		g_LogCtrl.ReLoadCfg();	//���¼��������ļ���
	}

	m_iCurrentDeep = g_LogCtrl.GetNextLevel();

	memcpy(&g_LogCtrl.m_tBeginTime, &timebuffer, sizeof(timebuffer));
	
	if (m_pLogFileHandle == NULL)
	{
		m_pLogFileHandle = stdout;
	}

	//��ӡ����������־
	g_LogCtrl.PrintBeginLog(this);
}

LogFunc::~LogFunc()
{
	if (g_LogCtrl.GetErrorStatus())
	{
		//��־��״̬����
		return;
	}

	g_LogCtrl.SetNextLevel(m_iCurrentDeep - 1);

	memset(&g_LogCtrl.m_tEndTime, 0, sizeof(g_LogCtrl.m_tEndTime));
	ftime(&g_LogCtrl.m_tEndTime);

	//��ӡ�����Ƴ���־
	g_LogCtrl.PrintEndLog(this);
}

