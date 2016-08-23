#include "libdbug.h"

namespace NSPrime
{
	NSPrime::TLibDbugGlobalVar *NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar=NULL;
	

	/**
	 *     库的初始化，此函数应该放在所有的库函数之前执行，应由主线程来调用此函
	 * 数。
	 * @return 0表示成功
	 *         非0表示失败
	 */
	int CLDbugLibInit::LibInit(const char* sProgramName)
	{
		int retVal=0;

		if (g_ptLibDbugGlobalVar)
		{
			retVal = -1;
			return retVal;
		}
		g_ptLibDbugGlobalVar = new NSPrime::TLibDbugGlobalVar[1];;

		g_ptLibDbugGlobalVar->m_sProgramName = sProgramName;

		if (!g_ptLibDbugGlobalVar)
		{
			retVal = -2;
			return retVal;
		}
		g_ptLibDbugGlobalVar->m_sProgramName = NULL;

		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.init_done = false;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack = NULL;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_ = stdout;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_ = (char*) "dbug";
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_pfp_ = stdout;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_pon_ = false;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_on_ = false;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar._no_db_ = false;
#ifdef THREAD
		if (!g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Init(0))
		{
			retVal = -4;
			return retVal;
		}
#else
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.lineno = 0;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.level = 0;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.func = "?func";
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.file = "?file";
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.jmplevel = 0;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.jmpfunc = NULL;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.jmpfile = NULL;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.u_line = 0;
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.u_line = '?'; //"?"->'?'by lxw0906
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.static_code_state.locked = 0;
#endif

		g_ptLibDbugGlobalVar->AbortHook = (void(*)(int))exit;
		g_ptLibDbugGlobalVar->ErrorHandlerHook = CLGlobalErrors::MsgNoCurses;
		g_ptLibDbugGlobalVar->FatalErrorHandlerHook = CLGlobalErrors::MsgNoCurses;

		g_ptLibDbugGlobalVar->globErrs[0] = "File '%s' not found (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[1] = "Can't create/write to file '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[2] = "Error reading file '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[3] = "Error writing file '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[4] = "Error on close of '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[5] = "Out of memory (Needed %u bytes)";
		g_ptLibDbugGlobalVar->globErrs[6] = "Error on delete of '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[7] = "Error on rename of '%s' to '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[8] = "";
		g_ptLibDbugGlobalVar->globErrs[9] = "Unexpected eof found when reading file '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[10] = "Can't lock file (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[11] = "Can't unlock file (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[12] = "Can't read dir of '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[13] = "Can't get stat of '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[14] = "Can't change size of file (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[15] = "Can't open stream from handle (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[16] = "Can't get working dirctory (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[17] = "Can't change dir to '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[18] = "Warning: '%s' had %d links",
		g_ptLibDbugGlobalVar->globErrs[19] = "%d files and %d streams is left open\n",
		g_ptLibDbugGlobalVar->globErrs[20] = "Disk is full writing '%s'. Waiting for someone to free space...";
		g_ptLibDbugGlobalVar->globErrs[21] = "Can't create directory '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[22] = "Character set '%s' is not a compiled character set and is not specified in the '%s' file";
		g_ptLibDbugGlobalVar->globErrs[23] = "Out of resources when opening file '%s' (Errcode: %d)";
		g_ptLibDbugGlobalVar->globErrs[24] = "Can't read value for symlink '%s' (Error %d)";
		g_ptLibDbugGlobalVar->globErrs[25] = "Can't create symlink '%s' pointing at '%s' (Error %d)";
		g_ptLibDbugGlobalVar->globErrs[26] = "Error on realpath() on '%s' (Error %d)";
		g_ptLibDbugGlobalVar->globErrs[27] = "Can't sync file '%s' to disk (Errcode: %d)";
		
		g_ptLibDbugGlobalVar->errMsg[0] = g_ptLibDbugGlobalVar->globErrs;
		g_ptLibDbugGlobalVar->errMsg[1] = NULL;
		g_ptLibDbugGlobalVar->errMsg[2] = NULL;
		g_ptLibDbugGlobalVar->errMsg[3] = NULL;

		memset(g_ptLibDbugGlobalVar->m_sErrBuff, 0, sizeof(g_ptLibDbugGlobalVar->m_sErrBuff));
	
#ifndef DBUG_OFF
		g_ptLibDbugGlobalVar->m_lTotalMallocTimes=0;
		g_ptLibDbugGlobalVar->lTotalSerialNo = 0;
		g_ptLibDbugGlobalVar->m_lTotalMallocSize=0;
		g_ptLibDbugGlobalVar->g_ptMallocLink = NULL;
#endif
#ifndef DBUG_OFF
		if(!g_ptLibDbugGlobalVar->m_thrLockMalloc.Init(0))
		{
			retVal = -5;
			return retVal;
		}
#endif
		g_ptLibDbugGlobalVar->hThreadKeySystem = 0;
		g_ptLibDbugGlobalVar->m_iThreadCount = 0;
#ifndef DBUG_OFF
		if (!(g_ptLibDbugGlobalVar->g_ptThreadList=(CLThread::TThreadList*)CLMalloc::GlobalMalloc(sizeof(CLThread::TThreadList))))
		{
			retVal = -6;
			return retVal;
		}
		g_ptLibDbugGlobalVar->g_ptThreadList->m_lMallocSize = 0;
		g_ptLibDbugGlobalVar->g_ptThreadList->m_ptMallocLink = NULL;
		g_ptLibDbugGlobalVar->g_ptThreadList->m_ptThreadListNext = NULL;
		g_ptLibDbugGlobalVar->g_ptThreadList->m_hThread = CLThread::GetCurrThreadHandle();
#endif
		if (!g_ptLibDbugGlobalVar->m_gLockThread.Init(0))
		{
			retVal = -6;
			return retVal;
		}
		if (!g_ptLibDbugGlobalVar->m_gLockThreadInterVar.Init(0))
		{
			retVal = -7;
			return retVal;
		}
		if (!g_ptLibDbugGlobalVar->m_gLockSysGlobal.Init(0))
		{
			retVal = -8;
			return retVal;
		}
		if (!NSPrime::CLThread::ThreadKeyCreate(&g_ptLibDbugGlobalVar->hThreadKeySystem))
		{
			retVal = -2;
			return retVal;
		}


		//此处是主线程的初始化
#ifdef __WIN__
		if (!NSPrime::CLThread::ThreadInit(GetCurrentThread(),GetCurrentThreadId()))
#else
		if (!NSPrime::CLThread::ThreadInit(pthread_self(),pthread_self()))
#endif
		{
			retVal = -7;
			return retVal;
		}
		

		return retVal;
	}

	/**
	 *     库的清理函数，此函数应该放在所有的库函数之后执行，应由主线程来调用此
	 * 函数。
	 * @return 0表示成功
	 *         小于0表示失败
	 *         大于0表示没有释放的内存数量。
	 */
	int CLDbugLibInit::LibDestroy()
	{
		int retVal=0;


		NSPrime::CLThread::ThreadEnd();//此处是主线程的清除处理
		if (!NSPrime::CLThread::ThreadKeyDelete(&g_ptLibDbugGlobalVar->hThreadKeySystem))
		{
			retVal = -1;
		}

		g_ptLibDbugGlobalVar->m_gLockSysGlobal.Term();
		g_ptLibDbugGlobalVar->m_gLockThreadInterVar.Term();
		g_ptLibDbugGlobalVar->m_gLockThread.Term();
#ifndef DBUG_OFF
		CLMalloc::GlobalFree(g_ptLibDbugGlobalVar->g_ptThreadList);
		g_ptLibDbugGlobalVar->g_ptThreadList = NULL;
		g_ptLibDbugGlobalVar->m_thrLockMalloc.Term();
#endif

#ifdef THREAD
		g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Term();
#endif
		retVal = (int)NSPrime::CLMalloc::GetTotalMallocTimes();
		delete g_ptLibDbugGlobalVar;

		return retVal;
	}
}

