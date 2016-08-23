#include "libdbug.h"

namespace NSPrime
{
#ifndef __WIN__
	const ETYPE CLGlobalErrors::EE_FILENOTFOUND;
	const ETYPE CLGlobalErrors::EE_CANTCREATEFILE;
	const ETYPE CLGlobalErrors::EE_READ;
	const ETYPE CLGlobalErrors::EE_WRITE;
	const ETYPE CLGlobalErrors::EE_BADCLOSE;
	const ETYPE CLGlobalErrors::EE_OUTOFMEMORY;
	const ETYPE CLGlobalErrors::EE_DELETE;
	const ETYPE CLGlobalErrors::EE_LINK;
	const ETYPE CLGlobalErrors::EE_EOFERR;
	const ETYPE CLGlobalErrors::EE_CANTLOCK;
	const ETYPE CLGlobalErrors::EE_CANTUNLOCK;
	const ETYPE CLGlobalErrors::EE_DIR;
	const ETYPE CLGlobalErrors::EE_STAT;
	const ETYPE CLGlobalErrors::EE_CANT_CHSIZE;
	const ETYPE CLGlobalErrors::EE_CANT_OPEN_STREAM;
	const ETYPE CLGlobalErrors::EE_GETWD;
	const ETYPE CLGlobalErrors::EE_SETWD;
	const ETYPE CLGlobalErrors::EE_LINK_WARNING;
	const ETYPE CLGlobalErrors::EE_OPEN_WARNING;
	const ETYPE CLGlobalErrors::EE_DISK_FULL;
	const ETYPE CLGlobalErrors::EE_CANT_MKDIR;
	const ETYPE CLGlobalErrors::EE_UNKNOWN_CHARSET;
	const ETYPE CLGlobalErrors::EE_OUT_OF_FILERESOURCES;
	const ETYPE CLGlobalErrors::EE_CANT_READLINK;
	const ETYPE CLGlobalErrors::EE_CANT_SYMLINK;
	const ETYPE CLGlobalErrors::EE_REALPATH;
	const ETYPE CLGlobalErrors::EE_SYNC;
	const ETYPE CLGlobalErrors::GLOBERRS;// 全局错误的数量
	const int CLGlobalErrors::MAX_MAP_NUM;	// 错误代码最大映射数
	const int CLGlobalErrors::ERR_MOD;//在一个错误映射中的最大值
#endif

	ETYPE CLGlobalErrors::MsgNoCurses(ETYPE error,const char *str, myf MyFlags)
	{
		DBUG_ENTER("MsgNoCurses");
		DBUG_PRINT("enter",("message: %s",str));
		(void) fflush(stdout);
		(void)fputs(str,stderr);
		(void)fputc('\n',stderr);
		(void)fflush(stderr);
		DBUG_RETURN(0);
	}


	ETYPE CLGlobalErrors::GetErrMsg(ETYPE nr,myf MyFlags, ...)
	{
		va_list	ap;
		ub4		olen, plen;
		reg1 const char *tpos;
		reg2 char	*endpos;
		char		* par;
		char		ebuff[ERR_MSG_SIZE+20];
		DBUG_ENTER("GetErrMsg");

		va_start(ap,MyFlags);
		DBUG_PRINT("my", ("nr: %d  MyFlags: %d  errno: %d", nr, MyFlags, errno));

		olen=(ub4) strlen(tpos= CLDbugLibInit::g_ptLibDbugGlobalVar->errMsg[nr / ERR_MOD][nr % ERR_MOD]);
		endpos=ebuff;

		while (*tpos)
		{
			if (tpos[0] != '%')
			{
				*endpos++= *tpos++;	/* Copy ordinary char */
				olen++;
				continue;
			}
			if (*++tpos == '%')		/* test if %% */
			{
				olen--;
			}
			else
			{
				/* Skipp if max size is used (to be compatible with printf) */
				while (IsDigit(*tpos) || *tpos == '.' || *tpos == '-')
					tpos++;
				if (*tpos == 'l')				/* Skipp 'l' argument */
					tpos++;
				if (*tpos == 's')				/* String parameter */
				{
					par = va_arg(ap, char *);
					plen = (ub4) strlen(par);
					if (olen + plen < ERR_MSG_SIZE+2)		/* Replace if possible */
					{
						endpos=strcpy(endpos,par);
						tpos++;
						olen+=plen-2;
						continue;
					}
				}
				else if (*tpos == 'd' || *tpos == 'u')	/* Integer parameter */
				{
					register int iarg;
					iarg = va_arg(ap, int);
					if (*tpos == 'd')
						plen= (ub4) (CLNumber::int2str((long) iarg,endpos, -10) - endpos);
					else
						plen= (ub4) (CLNumber::int2str((long) (ub4) iarg,endpos,10)- endpos);
					if (olen + plen < ERR_MSG_SIZE + 2) /* Replace parameter if possible */
					{
						endpos+=plen;
						tpos++;
						olen+=plen-2;
						continue;
					}
				}
			}
			*endpos++='%';		/* % used as % or unknown code */
		}
		*endpos='\0';			/* End of errmessage */
		va_end(ap);
		DBUG_RETURN((*CLDbugLibInit::g_ptLibDbugGlobalVar->ErrorHandlerHook)(nr, ebuff, MyFlags));
	}

	//Error as printf
	ETYPE CLGlobalErrors::PrintfError(ETYPE error, const char *format, myf MyFlags, ...)
	{
		va_list args;
		char ebuff[ERR_MSG_SIZE+20];

		va_start(args,MyFlags);
		(void) vsprintf (ebuff,format,args);
		va_end(args);
		return (*CLDbugLibInit::g_ptLibDbugGlobalVar->ErrorHandlerHook)(error, ebuff, MyFlags);
	}
	
	ETYPE CLGlobalErrors::Message(ETYPE error, const char *str, register myf MyFlags)
	{
		return (*CLDbugLibInit::g_ptLibDbugGlobalVar->ErrorHandlerHook)(error, str, MyFlags);
	}
}
