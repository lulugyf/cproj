#pragma once

//#include "global.h"
/**
 *     NSPrime 库的命名空间
 */
#define EE(X) NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->errMsg[NSPrime::CLGlobalErrors::GLOB_POSITION][X]
namespace NSPrime
{
	typedef void (*TAbortHook)(int error);
	typedef ETYPE (*TErrorHandlerHook)(ETYPE error,const char *str,myf MyFlags);
	typedef ETYPE (*TFatalErrorHandlerHook)(ETYPE error,const char *str,myf MyFlags);
	/**
	*  全局错误对象
	*/
	class CLGlobalErrors
	{
	public:

		/* 全局错误信息的编码定义*/
		static const ETYPE EE_FILENOTFOUND			=	0;
		static const ETYPE EE_CANTCREATEFILE		=	1;
		static const ETYPE EE_READ					=	2;
		static const ETYPE EE_WRITE					=	3;
		static const ETYPE EE_BADCLOSE				=	4;
		static const ETYPE EE_OUTOFMEMORY			=	5;
		static const ETYPE EE_DELETE				=	6;
		static const ETYPE EE_LINK					=	7;
		static const ETYPE EE_EOFERR				=	9;
		static const ETYPE EE_CANTLOCK				=	10;
		static const ETYPE EE_CANTUNLOCK			=	11;
		static const ETYPE EE_DIR					=	12;
		static const ETYPE EE_STAT					=	13;
		static const ETYPE EE_CANT_CHSIZE			=	14;
		static const ETYPE EE_CANT_OPEN_STREAM		=	15;
		static const ETYPE EE_GETWD					=	16;
		static const ETYPE EE_SETWD					=	17;
		static const ETYPE EE_LINK_WARNING			=	18;
		static const ETYPE EE_OPEN_WARNING			=	19;
		static const ETYPE EE_DISK_FULL				=	20;
		static const ETYPE EE_CANT_MKDIR			=	21;
		static const ETYPE EE_UNKNOWN_CHARSET		=	22;
		static const ETYPE EE_OUT_OF_FILERESOURCES	=	23;
		static const ETYPE EE_CANT_READLINK			=	24;
		static const ETYPE EE_CANT_SYMLINK			=	25;
		static const ETYPE EE_REALPATH				=	26;
		static const ETYPE EE_SYNC					=	27;

		static const ETYPE GLOB_POSITION				=	0;/*全局错误在*/
		static const ETYPE GLOBERRS = 28;	/* 全局错误的数量 */

		static const int MAX_MAP_NUM				=	4;/* 错误代码最大映射数 */
		static const int ERR_MOD					=	1000;/*在一个错误映射中的最大值*/

		static const int ERR_MSG_SIZE				=	512;/*Max length of a error message*/
		
		static const int NRERRBUFFS					=	2;	/* Buffers for parameters */

		/*是否是数字*/
		static inline int IsDigit(ub4 val)
		{
			return (val >='0' && val <='9');
		}

		 /*本库的错误代码提取函数*/
		static inline ETYPE GetLastError(void)
		{
			NSPrime::CLThread::TThreadVar *tmp=(NSPrime::CLThread::TThreadVar *)NSPrime::CLThread::GetThreadVar();
			if (tmp)
			{
				return tmp->thrErrno;
			}
			else
			{
				return 0;
			}
		}

		 /*本库的错误代码设置函数*/
		static inline void SetLastError(ETYPE dwErrCode)
		{
			NSPrime::CLThread::TThreadVar *tmp=(NSPrime::CLThread::TThreadVar *)NSPrime::CLThread::GetThreadVar();
			if (tmp)
			{
				tmp->thrErrno = dwErrCode;
			}
		}
	
		/*得到错误信息*/
		static ETYPE GetErrMsg(ETYPE nr,myf MyFlags, ...);

		//Error as printf
		static ETYPE PrintfError(ETYPE error, const char *format, myf MyFlags, ...);

		static ETYPE MsgNoCurses(ETYPE error,const char *str, myf MyFlags);

		/*
		  Give message using error_handler_hook

		  SYNOPSIS
			Message()
			  error	Errno
			  str	Error message
			  MyFlags	Flags
		*/
		static ETYPE Message(ETYPE error, const char *str, register myf MyFlags);
	};
	
	class CLOsErrMsg
	{
	public:
		CLOsErrMsg()
		{
			m_psBuffer = NULL;
		}

		~CLOsErrMsg()
		{
			if (m_psBuffer != NULL)
			{
				free( m_psBuffer );
				m_psBuffer = NULL;
			}
		}

		//打印操作系统的错误信息，到标准错误输出。
		static void PrintOsErrMsg(int iErrNo)
		{
#ifdef __WIN__
			LPVOID lpMsgBuf;
			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				iErrNo,
				0, // Default language
				(LPTSTR) &lpMsgBuf,
				0,
				NULL 
			);
			fprintf(stderr, "%s", lpMsgBuf);
			LocalFree( lpMsgBuf );

#else
			fprintf(stderr, "%s", strerror(iErrNo));
#endif
			return ;
		}

		/**
		 * <summary>得到操作系统的错误信息，并放到psBuffer变量中。</summary>
		 * <outparam name="iBufferSize" type="int">
		 *    输出缓冲的大小，默认为1023字节。
		 *        如果输出的iBufferSize=0，表示没有长度限制，全部返回，此时要小
		 *    心，返回的长度如果溢出客户端的缓冲长度，就可能coredump出错。
		 * </outparam>
		 * <returns>返回得到的错误信息！</returns>
		 */
		char* GetOsErrMsg(int iErrNo, int iBufferSize=0)
		{
			char* lpMsgBuf = NULL;
#ifdef __WIN__
			FormatMessageA( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				iErrNo,
				0, // Default language
				(LPSTR) &lpMsgBuf,
				0,
				NULL 
			);

#else
			lpMsgBuf = strerror(iErrNo);
#endif
			if (lpMsgBuf)
			{
				if (iBufferSize <= 0)
				{
					m_psBuffer = (char*) malloc(strlen((const char*)lpMsgBuf) + 1);
					memset(m_psBuffer, 0, strlen((const char*)lpMsgBuf) + 1);
					strcpy(m_psBuffer, (const char*)lpMsgBuf);
				}
				else
				{
					m_psBuffer = (char*) malloc(iBufferSize + 1);
					memset(m_psBuffer, 0, iBufferSize + 1);
					strncpy(m_psBuffer, (const char*)lpMsgBuf, iBufferSize);
				}
#ifdef __WIN__
				LocalFree(lpMsgBuf);
#endif
			}
			else
			{
				m_psBuffer = (char*) malloc(63 + 1);
				memset(m_psBuffer, 0, 63 + 1);

				if (iBufferSize <= 0)
				{
					strcpy(m_psBuffer, "Unknown  error");
				}
				else
				{
					strncpy(m_psBuffer, "Unknown  error", iBufferSize);
				}
			}
			return m_psBuffer;
		}
	private:
		char* m_psBuffer;
	};
}
#define GET_OS_ERR_MSG(iErrNo) NSPrime::CLOsErrMsg().GetOsErrMsg(iErrNo, 0)

