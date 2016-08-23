/*
*  FILE
*
*	dbug.c	 runtime support routines for dbug package
*/

#include "libdbug.h"

namespace NSPrime
{
	const char* CLDBug::_DBUG_START_CONDITION_ = "d:t";
#ifndef __WIN__
	const int	CLDBug::EOS;  // End Of String marker 
	const int	CLDBug::PRINTBUF;    // Print buffer size 
	const int	CLDBug::INDENT;       // Indentation per trace level 
	const int	CLDBug::MAXDEPTH;     // Maximum trace depth default 
	const int	CLDBug::TRACE_ON;	// Trace enabled 
	const int	CLDBug::DEBUG_ON;	// Debug enabled 
	const int	CLDBug::FILE_ON;	// File name print enabled 
	const int	CLDBug::LINE_ON;	// Line number print enabled 
	const int	CLDBug::DEPTH_ON;	// Function nest level print enabled 
	const int	CLDBug::PROCESS_ON;	// Process name print enabled 
	const int	CLDBug::NUMBER_ON;	// Number each line // output 
	const int	CLDBug::PROFILE_ON;// Print out pr//iling code 
	const int	CLDBug::PID_ON;	// Identify each line with process id 
	const int	CLDBug::SANITY_CHECK_ON;	// Check safemalloc on DBUG_ENTER 
	const int	CLDBug::FLUSH_ON_WRITE;	// Flush on every write 
#endif
	
	/*
	* The default file for profiling.  Could also add another flag
	* (G?) which allowed the user to specify this.
	*
	* If the automatic variables get allocated on the stack in
	* reverse order from their declarations, then define AUTOS_REVERSE.
	* This is used by the code that keeps track of stack usage.  For
	* forward allocation, the difference in the dbug frame pointers
	* represents stack used by the callee function.  For reverse allocation,
	* the difference represents stack used by the caller function.
	*
	*/

	const char*	const CLDBug::PROF_FILE	=	"dbugmon.out";
	const char*	const CLDBug::PROF_EFMT	=	"E\t%ld\t%s\n";
	const char*	const CLDBug::PROF_XFMT	=	"X\t%ld\t%s\n";

	/*
	*	Externally supplied functions.
	*/


	int _sanity(const char *file,ub4 line);


	/* Return current user time (ms) */
	static unsigned long Clock (void);
	static int DelayArg(int value);

	/*
	*	Miscellaneous printf format strings.
	*/

#define ERR_MISSING_RETURN "%s: missing DBUG_RETURN or DBUG_VOID_RETURN macro in function \"%s\"\n"
#define ERR_OPEN "%s: can't open debug output stream \"%s\": "
#define ERR_CLOSE "%s: can't close debug file: "
#define ERR_ABORT "%s: debugger aborting because %s\n"
#define ERR_CHOWN "%s: can't change owner/group of \"%s\": "

	/*
	*	Macros and defines for testing file accessibility under UNIX and MSDOS.
	*/

#undef EXISTS
#if !defined(HAVE_ACCESS) || defined(MSDOS)
#define EXISTS(pathname) (FALSE)	/* Assume no existance */
#define Writable(name) (TRUE)
#else
#define EXISTS(pathname)	 (access (pathname, F_OK) == 0)
#define WRITABLE(pathname)	 (access (pathname, W_OK) == 0)
#endif
#ifndef MSDOS
#define ChangeOwner(name)
#endif

	/*
	*	Translate some calls among different systems.
	*/

#if defined(unix) || defined(xenix) || defined(VMS) || defined(__NetBSD__)
# define Delay(A) sleep((ub4) A)
#elif defined(AMIGA)
	IMPORT int Delay ();			/* Pause for given number of ticks */
#else
	static int Delay(int ticks);
#endif


	CODE_STATE *CLDBug::code_state(void)
	{
#ifdef THREAD
		CODE_STATE *state=0;
		NSPrime::CLThread::TThreadVar *tmp=(NSPrime::CLThread::TThreadVar *)NSPrime::CLThread::GetThreadVar();
		if (tmp)
		{
#ifndef DBUG_OFF
			if (!(state=(CODE_STATE *) tmp->dbug))
			{
				state=(CODE_STATE*) CLMalloc::GlobalMalloc(sizeof(*state));
				memset(state, 0, sizeof(sizeof(*state)));
				state->lineno = 0;
				state->level = 0;
				state->func="?func";
				state->file="?file";
				state->jmplevel = 0;
				state->jmpfunc = NULL;
				state->jmpfile = NULL;
				state->u_line = 0;
				state->u_keyword = "?";
				state->locked = 0;
				tmp->dbug=(gptr) state;
			}
#endif
		}
		return state;
#else
		return &static_code_state;
#endif
	}


	/*
	*  FUNCTION
	*
	*	_db_push_	push current debugger state and set up new one
	*
	*  SYNOPSIS
	*
	*	VOID _db_push_ (control)
	*	char *control;
	*
	*  DESCRIPTION
	*
	*	Given pointer to a debug control string in "control", pushes
	*	the current debug state, parses the control string, and sets
	*	up a new debug state.
	*
	*	The only attribute of the new state inherited from the previous
	*	state is the current function nesting level.  This can be
	*	overridden by using the "r" flag in the control string.
	*
	*	The debug control string is a sequence of colon separated fields
	*	as follows:
	*
	*		<field_1>:<field_2>:...:<field_N>
	*
	*	Each field consists of a mandatory flag character followed by
	*	an optional "," and comma separated list of modifiers:
	*
	*		flag[,modifier,modifier,...,modifier]
	*
	*	The currently recognized flag characters are:
	*
	*		d	Enable output from DBUG_<N> macros for
	*			for the current state.	May be followed
	*			by a list of keywords which selects output
	*			only for the DBUG macros with that keyword.
	*			A null list of keywords implies output for
	*			all macros.
	*
	*		D	Delay after each debugger output line.
	*			The argument is the number of tenths of seconds
	*			to delay, subject to machine capabilities.
	*			I.E.  -#D,20 is delay two seconds.
	*
	*		f	Limit debugging and/or tracing, and profiling to the
	*			list of named functions.  Note that a null list will
	*			disable all functions.	The appropriate "d" or "t"
	*			flags must still be given, this flag only limits their
	*			actions if they are enabled.
	*
	*		F	Identify the source file name for each
	*			line of debug or trace output.
	*
	*		i	Identify the process with the pid for each line of
	*			debug or trace output.
	*
	*		g	Enable profiling.  Create a file called 'dbugmon.out'
	*			containing information that can be used to profile
	*			the program.  May be followed by a list of keywords
	*			that select profiling only for the functions in that
	*			list.  A null list implies that all functions are
	*			considered.
	*
	*		L	Identify the source file line number for
	*			each line of debug or trace output.
	*
	*		n	Print the current function nesting depth for
	*			each line of debug or trace output.
	*
	*		N	Number each line of dbug output.
	*
	*		o	Redirect the debugger output stream to the
	*			specified file.  The default output is stderr.
	*
	*		O	As O but the file is really flushed between each
	*			write. When neaded the file is closed and reopened
	*			between each write.
	*
	*		p	Limit debugger actions to specified processes.
	*			A process must be identified with the
	*			DBUG_PROCESS macro and match one in the list
	*			for debugger actions to occur.
	*
	*		P	Print the current process name for each
	*			line of debug or trace output.
	*
	*		r	When pushing a new state, do not inherit
	*			the previous state's function nesting level.
	*			Useful when the output is to start at the
	*			left margin.
	*
	*		S	Do function _sanity(_file_,_line_) at each
	*			debugged function until _sanity() returns
	*			something that differs from 0.
	*			(Moustly used with safemalloc)
	*
	*		t	Enable function call/exit trace lines.
	*			May be followed by a list (containing only
	*			one modifier) giving a numeric maximum
	*			trace level, beyond which no output will
	*			occur for either debugging or tracing
	*			macros.  The default is a compile time
	*			option.
	*
	*	Some examples of debug control strings which might appear
	*	on a shell command line (the "-#" is typically used to
	*	introduce a control string to an application program) are:
	*
	*		-#d:t
	*		-#d:f,main,subr1:F:L:t,20
	*		-#d,input,output,files:n
	*
	*	For convenience, any leading "-#" is stripped off.
	*	此函数不是线程安全的，应放在新建其它线程之前执行。
	*/

	void CLDBug::_db_push_ (const char *control)
	{
		reg1 char *scan;
		reg2 TDbLink *temp;
		CODE_STATE *state;
		char *new_str;

		if (! CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_)
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_= stderr;		/* Output stream, default stderr */

		if (*control == '-')
		{
			if (*++control == '#')
				control++;
		}
		if (*control)
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._no_db_=0;			/* We are using dbug after all */

		new_str = StrDup (control);
		PushState ();
		state=code_state();

		scan = static_strtok (new_str, ':');
		for (; scan != NULL; scan = static_strtok ((char *)NULL, ':'))
		{
			switch (*scan++)
			{
			case 'd':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_on_ = TRUE;
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= DEBUG_ON;
				if (*scan++ == ',') {
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> keywords = ListParse (scan);
				}
				break;
			case 'D':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> delay = 0;
				if (*scan++ == ',') {
					temp = ListParse (scan);
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> delay = DelayArg (atoi ((const char*)(temp -> ptr)));
					FreeList (temp);
				}
				break;
			case 'f':
				if (*scan++ == ',') {
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> functions = ListParse (scan);
				}
				break;
			case 'F':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= FILE_ON;
				break;
			case 'i':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= PID_ON;
				break;
#ifndef THREAD
			case 'g':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_pon_ = TRUE;
				if (OpenProfile(PROF_FILE))
				{
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= PROFILE_ON;
					if (*scan++ == ',')
						CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> p_functions = ListParse (scan);
				}
				break;
#endif
			case 'L':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= LINE_ON;
				break;
			case 'n':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= DEPTH_ON;
				break;
			case 'N':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= NUMBER_ON;
				break;
			case 'A':
			case 'O':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= FLUSH_ON_WRITE;
			case 'a':
			case 'o':
				if (*scan++ == ',') {
					temp = ListParse (scan);
					DBUGOpenFile((const char*)(temp -> ptr), (int) (scan[-2] == 'A' || scan[-2] == 'a'));
					FreeList (temp);
				} else {
					DBUGOpenFile ("-",0);
				}
				break;
			case 'p':
				if (*scan++ == ',') {
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> processes = ListParse (scan);
				}
				break;
			case 'P':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= PROCESS_ON;
				break;
			case 'r':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->sub_level= state->level;
				break;
			case 't':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= TRACE_ON;
				if (*scan++ == ',') {
					temp = ListParse (scan);
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> maxdepth = atoi ((const char*)(temp -> ptr));
					FreeList (temp);
				}
				break;
			case 'S':
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= SANITY_CHECK_ON;
				break;
			}
		}
		CLMalloc::GlobalFree(new_str);
		new_str = NULL;
	}


	/*
	*  FUNCTION
	*
	*	_db_pop_    pop the debug stack
	*
	*  DESCRIPTION
	*
	*	Pops the debug stack, returning the debug state to its
	*	condition prior to the most recent _db_push_ invocation.
	*	Note that the pop will fail if it would remove the last
	*	valid state from the stack.  This prevents user errors
	*	in the push/pop sequence from screwing up the debugger.
	*	Maybe there should be some kind of warning printed if the
	*	user tries to pop too many states.
	*	此函数不是线程安全的，应放在除主线程外所有其它线程结束后执行。
	*	
	*/

	void CLDBug::_db_pop_ ()
	{
		if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack != NULL)
		{
			if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> keywords != NULL) {
				FreeList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> keywords);
			}
			if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> functions != NULL) {
				FreeList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> functions);
			}
			if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> processes != NULL) {
				FreeList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> processes);
			}
			if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> p_functions != NULL) {
				FreeList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> p_functions);
			}

			CloseFile (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> out_file);
			if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> prof_file)
				CloseFile (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> prof_file);

			CLMalloc::GlobalFree((char *) CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack);
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack = NULL;
			DbugStateDestroy();
		}
		else
		{
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_on_ = false;
		}
	}


	/*
	*  FUNCTION
	*
	*	_db_enter_    process entry point to user function
	*
	*  SYNOPSIS
	*
	*	VOID _db_enter_ (_func_, _file_, _line_,
	*			 _sfunc_, _sfile_, _slevel_, _sframep_)
	*	char *_func_;		points to current function name
	*	char *_file_;		points to current file name
	*	int _line_;		called from source line number
	*	char **_sfunc_;		save previous _func_
	*	char **_sfile_;		save previous _file_
	*	int *_slevel_;		save previous nesting level
	*
	*  DESCRIPTION
	*
	*	Called at the beginning of each user function to tell
	*	the debugger that a new function has been entered.
	*	Note that the pointers to the previous user function
	*	name and previous user file name are stored on the
	*	caller's stack (this is why the ENTER macro must be
	*	the first "executable" code in a function, since it
	*	allocates these storage locations).  The previous nesting
	*	level is also stored on the callers stack for internal
	*	self consistency checks.
	*
	*	Also prints a trace line if tracing is enabled and
	*	increments the current function nesting depth.
	*
	*	Note that this mechanism allows the debugger to know
	*	what the current user function is at all times, without
	*	maintaining an internal stack for the function names.
	*
	*/

	void CLDBug::_db_enter_ (
		const char *_func_,
		const char *_file_,
		ub4 _line_,
		const char **_sfunc_,
		const char **_sfile_,
		ub4 *_slevel_)
	{
		reg1 CODE_STATE *state;
		if (!CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._no_db_)
		{
			int save_errno=errno;
			/*
			Sasha: the test below is so we could call functions with DBUG_ENTER
			before my_thread_init(). I needed this because I suspected corruption
			of a block allocated by my_thread_init() itself, so I wanted to use
			SafeMalloc()/SafeFree() in my_thread_init()/my_thread_end()
			*/
			if (!(state=code_state()))
				return;
			if (!CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.init_done)
				_db_push_ (_DBUG_START_CONDITION_);

			*_sfunc_ = state->func;
			*_sfile_ = state->file;
			state->func =(char*)  _func_;
			state->file = (char*) _file_;		/* BaseName takes time !! */
			*_slevel_ =  ++state->level;
#ifndef THREAD
			if (DoProfile ())
			{
				(void) fprintf (_db_pfp_, PROF_EFMT , Clock (), state->func);
				(void) fflush (_db_pfp_);
			}
#endif
			if (DoTrace (state))
			{
				if (!state->locked)
				{
#ifdef THREAD
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Lock();
#endif
				}
				DoPrefix (_line_);
				Indent (state -> level);
#ifndef DBUG_OFF
				(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, ">%s [%d][%ld]\n",
					state->func,state->level, NSPrime::CLMalloc::GetTotalMallocTimes());
#else
				(void) fprintf (_db_fp_, ">%s [%d]\n",
					state->func,state->level);
#endif
				dbug_flush (state);			/* This does a unlock */
			}
#ifdef SAFEMALLOC
			if (stack -> flags & SANITY_CHECK_ON)
				if (_sanity(_file_,_line_))		/* Check of safemalloc */
					stack -> flags &= ~SANITY_CHECK_ON;
#endif
			errno=save_errno;
		}
	}

	/*
	*  FUNCTION
	*
	*	_db_return_    process exit from user function
	*
	*  SYNOPSIS
	*
	*	VOID _db_return_ (_line_, _sfunc_, _sfile_, _slevel_)
	*	int _line_;		current source line number
	*	char **_sfunc_;		where previous _func_ is to be retrieved
	*	char **_sfile_;		where previous _file_ is to be retrieved
	*	int *_slevel_;		where previous level was stashed
	*
	*  DESCRIPTION
	*
	*	Called just before user function executes an explicit or implicit
	*	return.  Prints a trace line if trace is enabled, decrements
	*	the current nesting level, and restores the current function and
	*	file names from the defunct function's stack.
	*
	*/

	void CLDBug::_db_return_ (
		ub4 _line_,
		const char **_sfunc_,
		const char **_sfile_,
		ub4 *_slevel_)
	{
		CODE_STATE *state;

		if (!CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._no_db_)
		{
			int save_errno=errno;
			if (!(state=code_state()))
				return;				
			if (!CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.init_done)
				_db_push_ ("");
			if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->flags & (TRACE_ON | DEBUG_ON | PROFILE_ON))
			{
				if (!state->locked)
				{
#ifdef THREAD
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Lock();
#endif
				}
				if (state->level != (int) *_slevel_)
					(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, ERR_MISSING_RETURN, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_,
					state->func);
				else
				{
#ifdef SAFEMALLOC
					if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & SANITY_CHECK_ON)
						if (_sanity(*_sfile_,_line_))
							CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->flags &= ~SANITY_CHECK_ON;
#endif
#ifndef THREAD
					if (DoProfile ())
						(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_pfp_, PROF_XFMT, Clock(), state->func);
#endif
					if (DoTrace (state))
					{
						DoPrefix (_line_);
						Indent (state->level);
#ifndef DBUG_OFF
						(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "<%s [%ld]\n", state->func, NSPrime::CLMalloc::GetTotalMallocTimes());
#else
						(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "<%s\n", state->func);
#endif
					}
				}
				dbug_flush(state);
			}
			state->level = *_slevel_-1;
			state->func = *_sfunc_;
			state->file = *_sfile_;
			errno=save_errno;
		}
	}


	/*
	*  FUNCTION
	*
	*	_db_pargs_    log arguments for subsequent use by _db_doprnt_()
	*
	*  SYNOPSIS
	*
	*	VOID _db_pargs_ (_line_, keyword)
	*	int _line_;
	*	char *keyword;
	*
	*  DESCRIPTION
	*
	*	The new universal printing macro DBUG_PRINT, which replaces
	*	all forms of the DBUG_N macros, needs two calls to runtime
	*	support routines.  The first, this function, remembers arguments
	*	that are used by the subsequent call to _db_doprnt_().
	*
	*/

	void CLDBug::_db_pargs_ (
		ub4 _line_,
		const char *keyword)
	{
		CODE_STATE *state=code_state();
		/* Sasha: pre-my_thread_init() safety */
		if (!state)
			return;
		state->u_line = _line_;
		state->u_keyword = (char*) keyword;
	}


	/*
	*  FUNCTION
	*
	*	_db_doprnt_    handle print of debug lines
	*
	*  SYNOPSIS
	*
	*	VOID _db_doprnt_ (format, va_alist)
	*	char *format;
	*	va_dcl;
	*
	*  DESCRIPTION
	*
	*	When invoked via one of the DBUG macros, tests the current keyword
	*	set by calling _db_pargs_() to see if that macro has been selected
	*	for processing via the debugger control string, and if so, handles
	*	printing of the arguments via the format string.  The line number
	*	of the DBUG macro in the source is found in u_line.
	*
	*	Note that the format string SHOULD NOT include a terminating
	*	newline, this is supplied automatically.
	*
	*/

	void CLDBug::_db_doprnt_ (const char *format,...)
	{
		va_list args;
		CODE_STATE *state;
		/* Sasha: pre-my_thread_init() safety */
		if (!(state=code_state()))
			return;

		va_start(args,format);

		if (_db_keyword_ (state->u_keyword)) {
			int save_errno=errno;
			if (!state->locked)
			{
#ifdef THREAD
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Lock();
#endif
			}
			DoPrefix (state->u_line);
			if (TRACING()) {
				Indent (state->level + 1);
			} else {
				(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%s: ", state->func);
			}
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%s: ", state->u_keyword);
			(void) vfprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, format, args);
			(void) fputc('\n',CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);
			dbug_flush(state);
			errno=save_errno;
		}
		va_end(args);
	}


	/*
	*  FUNCTION
	*
	*	      _db_dump_    dump a string until '\0' is found
	*
	*  SYNOPSIS
	*
	*	      void _db_dump_ (_line_,keyword,memory,length)
	*	      int _line_;		current source line number
	*	      char *keyword;
	*	      char *memory;		Memory to print
	*	      int length;		Bytes to print
	*
	*  DESCRIPTION
	*  Dump N characters in a binary array.
	*  Is used to examine corrputed memory or arrays.
	*/

	void CLDBug::_db_dump_(
		ub4 _line_,
		const char *keyword,
		const char *memory,
		ub4 length)
	{
		int pos;
		char dbuff[90];
		CODE_STATE *state;
		/* Sasha: pre-my_thread_init() safety */
		if (!(state=code_state()))
			return;

		if (_db_keyword_ ((char*) keyword))
		{
			if (!state->locked)
			{
#ifdef THREAD
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Lock();
#endif
			}
			DoPrefix (_line_);
			if (TRACING())
			{
				Indent (state->level + 1);
				pos= CLNumber::Min(CLNumber::Max(state->level-CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->sub_level,0)*INDENT,80);
			}
			else
			{
				fprintf(CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%s: ", state->func);
			}
			sprintf(dbuff,"%s: Memory: %p  Bytes: (%u)\n",
				keyword,(const char*)memory, length);
			(void) fputs(dbuff,CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);

			DoPrefix (_line_);
			if (TRACING())
			{
				Indent (state->level + 1);
				pos= CLNumber::Min(CLNumber::Max(state->level-CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->sub_level,0)*INDENT,80);
			}
			else
			{
				fprintf(CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%s: ", state->func);
			}
			pos=0;
			while (length-- > 0)
			{
				ub4 tmp= *((unsigned char*) memory++);
				if ((pos+=3) >= 80)
				{
					fputc('\n',CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);
					pos=3;
				}
				/*用十六进制输出字符的ASCII值*/
				fputc(NSPrime::CLNumber::_dig_vec[((tmp >> 4) & 15)], CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);
				fputc(NSPrime::CLNumber::_dig_vec[tmp & 15], CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);
				fputc(' ',CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);
			}
			(void) fputc('\n',CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);
			dbug_flush(state);
		}
	}

	/*
	*  FUNCTION
	*
	*	ListParse    parse list of modifiers in debug control string
	*
	*  SYNOPSIS
	*
	*	static TDbLink *ListParse (ctlp)
	*	char *ctlp;
	*
	*  DESCRIPTION
	*
	*	Given pointer to a comma separated list of strings in "cltp",
	*	parses the list, building a list and returning a pointer to it.
	*	The original comma separated list is destroyed in the process of
	*	building the linked list, thus it had better be a duplicate
	*	if it is important.
	*
	*	Note that since each link is added at the head of the list,
	*	the final list will be in "reverse order", which is not
	*	significant for our usage here.
	*
	*/

	TDbLink *CLDBug::ListParse (	char *ctlp)
	{
		REGISTER char *start;
		REGISTER TDbLink *new_malloc;
		REGISTER TDbLink *head;

		head = NULL;
		while (*ctlp != EOS) {
			start = ctlp;
			while (*ctlp != EOS && *ctlp != ',') {
				ctlp++;
			}
			if (*ctlp == ',') {
				*ctlp++ = EOS;
			}
			new_malloc = (TDbLink *) CLMalloc::GlobalMalloc (sizeof (TDbLink));
			new_malloc -> ptr = StrDup (start);
			new_malloc -> next_link = head;
			head = new_malloc;
		}
		return (head);
	}

	/*
	*  FUNCTION
	*
	*	InList	  test a given string for member of a given list
	*
	*  SYNOPSIS
	*
	*	static bool InList (linkp, cp)
	*	TDbLink *linkp;
	*	char *cp;
	*
	*  DESCRIPTION
	*
	*	Tests the string pointed to by "cp" to determine if it is in
	*	the list pointed to by "linkp".  Linkp points to the first
	*	link in the list.  If linkp is NULL then the string is treated
	*	as if it is in the list (I.E all strings are in the null list).
	*	This may seem rather strange at first but leads to the desired
	*	operation if no list is given.	The net effect is that all
	*	strings will be accepted when there is no list, and when there
	*	is a list, only those strings in the list will be accepted.
	*
	*/

	bool CLDBug::InList (TDbLink *linkp,const char *cp)
	{
		REGISTER TDbLink *scan;
		REGISTER bool result;

		if (linkp == NULL)
		{
			result = TRUE;
		} else {
			result = FALSE;
			for (scan = linkp; scan != NULL; scan = scan -> next_link) {
				if (STREQ ((const char*)(scan -> ptr), cp)) {
					result = TRUE;
					break;
				}
			}
		}
		return (result);
	}


	/*
	*  FUNCTION
	*
	*	PushState    push current state onto stack and set up new one
	*
	*  SYNOPSIS
	*
	*	static VOID PushState ()
	*
	*  DESCRIPTION
	*
	*	Pushes the current state on the state stack, and initializes
	*	a new state.  The only parameter inherited from the previous
	*	state is the function nesting level.  This action can be
	*	inhibited if desired, via the "r" flag.
	*
	*	The state stack is a linked list of states, with the new
	*	state added at the head.  This allows the stack to grow
	*	to the limits of memory if necessary.
	*
	*/

	void CLDBug::PushState ()
	{
		if (!CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.init_done)
		{
			DbugStateInit();
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack = (struct state *) CLMalloc::GlobalMalloc(sizeof (struct state));
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags = 0;
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> delay = 0;
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> maxdepth = MAXDEPTH;
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> sub_level=0;
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> out_file = stderr;
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> prof_file = (FILE*) 0;
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> functions = NULL;
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> p_functions = NULL;
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> keywords = NULL;
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> processes = NULL;
		}
		(void) code_state();				/* Alloc memory */
	}


	/*
	*  FUNCTION
	*
	*	DoTrace    check to see if tracing is current enabled
	*
	*  SYNOPSIS
	*
	*	static bool DoTrace (stack)
	*
	*  DESCRIPTION
	*
	*	Checks to see if tracing is enabled based on whether the
	*	user has specified tracing, the maximum trace depth has
	*	not yet been reached, the current function is selected,
	*	and the current process is selected.  Returns TRUE if
	*	tracing is enabled, FALSE otherwise.
	*
	*/

	bool CLDBug::DoTrace (CODE_STATE *state)
	{
		reg2 bool trace=FALSE;

		if (TRACING() &&
			state->level <= CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> maxdepth &&
			InList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> functions, state->func) &&
			InList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> processes, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_))
			trace = TRUE;
		return (trace);
	}


	/*
	*  FUNCTION
	*
	*	DoProfile    check to see if profiling is current enabled
	*
	*  SYNOPSIS
	*
	*	static bool DoProfile ()
	*
	*  DESCRIPTION
	*
	*	Checks to see if profiling is enabled based on whether the
	*	user has specified profiling, the maximum trace depth has
	*	not yet been reached, the current function is selected,
	*	and the current process is selected.  Returns TRUE if
	*	profiling is enabled, FALSE otherwise.
	*
	*/

	bool CLDBug::DoProfile ()
	{
		REGISTER bool profile;
		CODE_STATE *state;
		state=code_state();

		profile = FALSE;
		if (PROFILING() &&
			state->level <= CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> maxdepth &&
			InList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> p_functions, state->func) &&
			InList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> processes, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_))
			profile = TRUE;
		return (profile);
	}


	/*
	*  FUNCTION
	*
	*	_db_keyword_	test keyword for member of keyword list
	*
	*  SYNOPSIS
	*
	*	bool _db_keyword_ (keyword)
	*	char *keyword;
	*
	*  DESCRIPTION
	*
	*	Test a keyword to determine if it is in the currently active
	*	keyword list.  As with the function list, a keyword is accepted
	*	if the list is null, otherwise it must match one of the list
	*	members.  When debugging is not on, no keywords are accepted.
	*	After the maximum trace level is exceeded, no keywords are
	*	accepted (this behavior subject to change).  Additionally,
	*	the current function and process must be accepted based on
	*	their respective lists.
	*
	*	Returns TRUE if keyword accepted, FALSE otherwise.
	*
	*/

	int CLDBug::_db_keyword_ (
		const char *keyword)
	{
		REGISTER bool result;
		CODE_STATE *state;

		if (!CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.init_done)
			_db_push_ ("");
		/* Sasha: pre-my_thread_init() safety */
		if (!(state=code_state()))
			return FALSE;
		result = FALSE;
		if (DEBUGGING() &&
			state->level <= CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> maxdepth &&
			InList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> functions, state->func) &&
			InList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> keywords, keyword) &&
			InList (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> processes, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_))
			result = TRUE;
		return (result);
	}

	/*
	*  FUNCTION
	*
	*	Indent	  indent a line to the given indentation level
	*
	*  SYNOPSIS
	*
	*	static VOID Indent (indent)
	*	int indent;
	*
	*  DESCRIPTION
	*
	*	Indent a line to the given level.  Note that this is
	*	a simple minded but portable implementation.
	*	There are better ways.
	*
	*	Also, the indent must be scaled by the compile time option
	*	of character positions per nesting level.
	*
	*/

	void CLDBug::Indent (int indent)
	{
		REGISTER int count;

		indent= CLNumber::Max(indent-1-CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->sub_level,0)*INDENT;
		for (count = 0; count < indent ; count++)
		{
			if ((count % INDENT) == 0)
				fputc('|',CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);
			else
				fputc(' ',CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);
		}
	}


	/*
	*  FUNCTION
	*
	*	FreeList    free all memory associated with a linked list
	*
	*  SYNOPSIS
	*
	*	static VOID FreeList (linkp)
	*	TDbLink *linkp;
	*
	*  DESCRIPTION
	*
	*	Given pointer to the head of a linked list, frees all
	*	memory held by the list and the members of the list.
	*
	*/

	void CLDBug::FreeList (TDbLink *linkp)
	{
		REGISTER TDbLink *old;

		while (linkp != NULL) {
			old = linkp;
			linkp = linkp -> next_link;
			if (old -> ptr != NULL) {
				CLMalloc::GlobalFree(old -> ptr);
				old -> ptr = NULL;
			}
			CLMalloc::GlobalFree((char *) old);
			old = NULL;
		}
	}


	/*
	*  FUNCTION
	*
	*	StrDup	 make a duplicate of a string in new memory
	*
	*  SYNOPSIS
	*
	*	static char *StrDup (const char *str)
	*	char *string;
	*
	*  DESCRIPTION
	*
	*	Given pointer to a string, allocates sufficient memory to make
	*	a duplicate copy, and copies the string to the newly allocated
	*	memory.  Failure to allocated sufficient memory is immediately
	*	fatal.
	*
	*/
	char *CLDBug::StrDup (const char *str)
	{
		reg1 char *new_malloc;
		new_malloc = (char*)CLMalloc::GlobalMalloc((unsigned long) strlen (str) + 1);
		(void) strcpy (new_malloc, str);
		return (new_malloc);
	}


	/*
	*  FUNCTION
	*
	*	DoPrefix    print debugger line prefix prior to indentation
	*
	*  SYNOPSIS
	*
	*	static VOID DoPrefix (_line_)
	*	int _line_;
	*
	*  DESCRIPTION
	*
	*	Print prefix common to all debugger output lines, prior to
	*	doing indentation if necessary.  Print such information as
	*	current process name, current source file name and line number,
	*	and current function nesting depth.
	*
	*/
	void CLDBug::DoPrefix (ub4 _line_)
	{
		CODE_STATE *state;
		state=code_state();

		state->lineno++;
		if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & PID_ON) {
#ifdef THREAD
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%-7s: ", NSPrime::CLThread::ThreadName());
#else
#ifdef __WIN__
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%5d: ", (int) _getpid ());
#else
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%5d: ", (int) getpid ());
#endif
#endif
		}
		if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & NUMBER_ON) {
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%5d: ", state->lineno);
		}
		if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & PROCESS_ON) {
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%s: ", CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_);
		}
		if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & FILE_ON) {
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%14s: ", BaseName(state->file));
		}
		if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & LINE_ON) {
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%5d: ", _line_);
		}
		if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & DEPTH_ON) {
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, "%4d: ", state->level);
		}
	}


	/*
	*  FUNCTION
	*
	*	DBUGOpenFile	open new output stream for debugger output
	*
	*  SYNOPSIS
	*
	*	static VOID DBUGOpenFile (name)
	*	char *name;
	*
	*  DESCRIPTION
	*
	*	Given name of a new file (or "-" for stdout) opens the file
	*	and sets the output stream to the new file.
	*
	*/
	void CLDBug::DBUGOpenFile (const char *name,int append)
	{
		REGISTER FILE *fp;
		REGISTER bool newfile;

		if (name != NULL)
		{
			strcpy(CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->name,name);
			if (strcmp (name, "-") == 0)
			{
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_ = stdout;
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> out_file = CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_;
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags |= FLUSH_ON_WRITE;
			}
			else
			{
				if (!Writable((char*)name))
				{
					(void) fprintf (stderr, ERR_OPEN, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_, name);
					perror ("");
					fflush(stderr);
				}
				else
				{
					newfile= !EXISTS (name);
					if (!(fp = fopen(name, append ? "a+" : "w")))
					{
						(void) fprintf (stderr, ERR_OPEN, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_, name);
						perror ("");
						fflush(stderr);
					}
					else
					{
						CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_ = fp;
						CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> out_file = fp;
						if (newfile) {
							ChangeOwner (name);
						}
					}
				}
			}
		}
	}


	/*
	*  FUNCTION
	*
	*	OpenProfile    open new output stream for profiler output
	*
	*  SYNOPSIS
	*
	*	static FILE *OpenProfile (name)
	*	char *name;
	*
	*  DESCRIPTION
	*
	*	Given name of a new file, opens the file
	*	and sets the profiler output stream to the new file.
	*
	*	It is currently unclear whether the prefered behavior is
	*	to truncate any existing file, or simply append to it.
	*	The latter behavior would be desirable for collecting
	*	accumulated runtime history over a number of separate
	*	runs.  It might take some changes to the analyzer program
	*	though, and the notes that Binayak sent with the profiling
	*	diffs indicated that append was the normal mode, but this
	*	does not appear to agree with the actual code. I haven't
	*	investigated at this time [fnf; 24-Jul-87].
	*/
	FILE *CLDBug::OpenProfile (const char *name)
	{
		REGISTER FILE *fp;
		REGISTER bool newfile;

		fp=0;
		if (!Writable (name))
		{
			(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, ERR_OPEN, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_, name);
			perror ("");
			dbug_flush(0);
			(void) Delay (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> delay);
		}
		else
		{
			newfile= !EXISTS (name);
			if (!(fp = fopen (name, "w")))
			{
				(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, ERR_OPEN, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_, name);
				perror ("");
				dbug_flush(0);
			}
			else
			{
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_pfp_ = fp;
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> prof_file = fp;
				if (newfile)
				{
					ChangeOwner (name);
				}
			}
		}
		return fp;
	}

	/*
	*  FUNCTION
	*
	*	CloseFile    close the debug output stream
	*
	*  SYNOPSIS
	*
	*	static VOID CloseFile (fp)
	*	FILE *fp;
	*
	*  DESCRIPTION
	*
	*	Closes the debug output stream unless it is standard output
	*	or standard error.
	*
	*/
	void CLDBug::CloseFile (FILE *fp)
	{
		if (fp != stderr && fp != stdout) {
			if (fclose (fp) == EOF)
			{
#ifdef THREAD
				CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Lock();
#endif
				(void) fprintf (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_, ERR_CLOSE, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_);
				perror ("");
				dbug_flush(0);
			}
		}
	}

	/*
	*  FUNCTION
	*
	*	DbugExit    print error message and exit
	*
	*  SYNOPSIS
	*
	*	static VOID DbugExit (why)
	*	char *why;
	*
	*  DESCRIPTION
	*
	*	Prints error message using current process name, the reason for
	*	aborting (typically out of memory), and exits with status 1.
	*	This should probably be changed to use a status code
	*	defined in the user's debugger include file.
	*
	*/
	void CLDBug::DbugExit (const char *why)
	{
		(void) fprintf (stderr, ERR_ABORT, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_, why);
		(void) fflush (stderr);
		exit (1);
	}

	/**
	 *		像strtok函数，但是在一行中的两个分隔将被替代为一个分隔符。程序不支持
	 * 线程级的访问。.
	 */
	char *CLDBug::static_strtok (char *s1, char separator)
	{
		static char *end = NULL;
		reg1 char *rtnval,*cpy;

		rtnval = NULL;
		if (s1 != NULL)
			end = s1;
		if (end != NULL && *end != EOS)
		{
			rtnval=cpy=end;
			do
			{
				if ((*cpy++ = *end++) == separator)
				{
					if (*end != separator)
					{
						cpy--;		/* Point at separator */
						break;
					}
					end++;			/* Two separators in a row, skipp one */
				}
			} while (*end != EOS);
			*cpy=EOS;			/* Replace last separator */
		}
		return (rtnval);
	}


	/*
	*  FUNCTION
	*
	*	BaseName    strip leading pathname components from name
	*
	*  SYNOPSIS
	*
	*	static char *BaseName (pathname)
	*	char *pathname;
	*
	*  DESCRIPTION
	*
	*	Given pointer to a complete pathname, locates the base file
	*	name at the end of the pathname and returns a pointer to
	*	it.
	*
	*/
	char *CLDBug::BaseName (const char *pathname)
	{
		register const char *base;

		base = strrchr (pathname, FN_LIBCHAR);
		if (base++ == NULLS)
			base = pathname;
		return ((char*) base);
	}


	/*
	*  FUNCTION
	*
	*	Writable    test to see if a pathname is writable/creatable
	*
	*  SYNOPSIS
	*
	*	static bool Writable (pathname)
	*	char *pathname;
	*
	*  DESCRIPTION
	*
	*	Because the debugger might be linked in with a program that
	*	runs with the set-uid-bit (suid) set, we have to be careful
	*	about opening a user named file for debug output.  This consists
	*	of checking the file for write access with the real user id,
	*	or checking the directory where the file will be created.
	*
	*	Returns TRUE if the user would normally be allowed write or
	*	create access to the named file.  Returns FALSE otherwise.
	*
	*/


#ifndef Writable

	static bool Writable (
		char *pathname)
	{
		REGISTER bool granted;
		REGISTER char *lastslash;

		granted = FALSE;
		if (EXISTS (pathname)) {
			if (WRITABLE (pathname)) {
				granted = TRUE;
			}
		} else {
			lastslash = strrchr (pathname, '/');
			if (lastslash != NULL) {
				*lastslash = EOS;
			} else {
				pathname = ".";
			}
			if (WRITABLE (pathname)) {
				granted = TRUE;
			}
			if (lastslash != NULL) {
				*lastslash = '/';
			}
		}
		return (granted);
	}
#endif


	/*
	*  FUNCTION
	*
	*	ChangeOwner    change owner to real user for suid programs
	*
	*  SYNOPSIS
	*
	*	static VOID ChangeOwner (pathname)
	*
	*  DESCRIPTION
	*
	*	For unix systems, change the owner of the newly created debug
	*	file to the real owner.  This is strictly for the benefit of
	*	programs that are running with the set-user-id bit set.
	*
	*	Note that at this point, the fact that pathname represents
	*	a newly created file has already been established.  If the
	*	program that the debugger is linked to is not running with
	*	the suid bit set, then this operation is redundant (but
	*	harmless).
	*
	*/

#ifndef ChangeOwner
	static void ChangeOwner (
		char *pathname)
	{
		if (chown (pathname, getuid (), getgid ()) == -1)
		{
			(void) fprintf (stderr, ERR_CHOWN, _db_process_, pathname);
			perror ("");
			(void) fflush (stderr);
		}
	}
#endif


	/*
	*  FUNCTION
	*
	*	_db_setjmp_    save debugger environment
	*
	*  SYNOPSIS
	*
	*	VOID _db_setjmp_ ()
	*
	*  DESCRIPTION
	*
	*	Invoked as part of the user's DBUG_SETJMP macro to save
	*	the debugger environment in parallel with saving the user's
	*	environment.
	*
	*/

#ifdef HAVE_LONGJMP

	EXPORT void _db_setjmp_ ()
	{
		CODE_STATE *state;
		state=code_state();

		state->jmplevel = state->level;
		state->jmpfunc = state->func;
		state->jmpfile = state->file;
	}

	/*
	*  FUNCTION
	*
	*	_db_longjmp_	restore previously saved debugger environment
	*
	*  SYNOPSIS
	*
	*	VOID _db_longjmp_ ()
	*
	*  DESCRIPTION
	*
	*	Invoked as part of the user's DBUG_LONGJMP macro to restore
	*	the debugger environment in parallel with restoring the user's
	*	previously saved environment.
	*
	*/

	EXPORT void _db_longjmp_ ()
	{
		CODE_STATE *state;
		state=code_state();

		state->level = state->jmplevel;
		if (state->jmpfunc) {
			state->func = state->jmpfunc;
		}
		if (state->jmpfile) {
			state->file = state->jmpfile;
		}
	}
#endif

	/*
	*  FUNCTION
	*
	*	DelayArg   convert D flag argument to appropriate value
	*
	*  SYNOPSIS
	*
	*	static int DelayArg (value)
	*	int value;
	*
	*  DESCRIPTION
	*
	*	Converts delay argument, given in tenths of a second, to the
	*	appropriate numerical argument used by the system to delay
	*	that that many tenths of a second.  For example, on the
	*	amiga, there is a system call "Delay()" which takes an
	*	argument in ticks (50 per second).  On unix, the sleep
	*	command takes seconds.	Thus a value of "10", for one
	*	second of delay, gets converted to 50 on the amiga, and 1
	*	on unix.  Other systems will need to use a timing loop.
	*
	*/

#ifdef AMIGA
#define HZ (50)			      /* Probably in some header somewhere */
#endif

	static int DelayArg (
		int value)
	{
		ub4 delayarg = 0;

#if (unix || xenix)
		delayarg = value / 10;	/* Delay is in seconds for sleep () */
#endif
#ifdef AMIGA
		delayarg = (HZ * value) / 10; /* Delay in ticks for Delay () */
#endif
		return (delayarg);
	}


	/*
	*	A dummy delay stub for systems that do not support delays.
	*	With a little work, this can be turned into a timing loop.
	*/

#if ! defined(Delay) && ! defined(AMIGA)
	static int Delay (
		int ticks)
	{
		return ticks;
	}
#endif


	/*
	*  FUNCTION
	*
	*	perror	  perror simulation for systems that don't have it
	*
	*  SYNOPSIS
	*
	*	static VOID perror (s)
	*	char *s;
	*
	*  DESCRIPTION
	*
	*	Perror produces a message on the standard error stream which
	*	provides more information about the library or system error
	*	just encountered.  The argument string s is printed, followed
	*	by a ':', a blank, and then a message and a newline.
	*
	*	An undocumented feature of the unix perror is that if the string
	*	's' is a null string (NOT a NULL pointer!), then the ':' and
	*	blank are not printed.
	*
	*	This version just complains about an "unknown system error".
	*
	*/
	void CLDBug::perror (const char *s)
	{
		if (s && *s != EOS) {
			(void) fprintf (stderr, "%s: ", s);
		}
		(void) fprintf (stderr, "<unknown system error>\n");
	}


	/* flush dbug-stream, free mutex lock & wait delay */
	/* This is because some systems (MSDOS!!) dosn't flush fileheader */
	/* and dbug-file isn't readable after a system crash !! */
	void CLDBug::dbug_flush(CODE_STATE *state)
	{
		if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->flags & FLUSH_ON_WRITE)
		{
#if defined(MSDOS) || defined(__WIN__)
			if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_ != stdout && CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_ != stderr)
			{
				if (!(freopen(CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->name,"a",CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_)))
				{
					(void) fprintf(stderr, ERR_OPEN, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_, CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->name);
					fflush(stderr);
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_ = stdout;
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> out_file = CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_;
					CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags|=FLUSH_ON_WRITE;
				}
			}
			else
#endif
			{
				(void) fflush (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_);
				if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->delay)
					(void) Delay (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack->delay);
			}
		}
		if (!state || !state->locked)
		{
#ifdef THREAD
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Unlock();
#endif
		}
	} /* dbug_flush */


	void CLDBug::_db_lock_file()
	{
		CODE_STATE *state;
		state=code_state();
#ifdef THREAD
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Lock();
#endif
		state->locked=1;
	}

	void CLDBug::_db_unlock_file()
	{
		CODE_STATE *state;
		state=code_state();
		state->locked=0;
#ifdef THREAD
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.m_tThrLockDbug.Unlock();
#endif
	}

	/*
	 * Here we need the definitions of the clock routine.  Add your
	 * own for whatever system that you have.
	 */
	static unsigned long Clock (void)
	{
		return clock()*(1000/CLOCKS_PER_SEC);
	}
	
	/**
	 *     设置程序处于调试或非调试状态
	 */
	int CLDBug::SetDebug()
	{
		char	*env;
		if ((env = getenv("DBUG_OFF")))
		{
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_on_ = FALSE;
		}
		else
		{
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_on_ = TRUE;
		}
		return 0;
	}

	void CLDBug::DbugStateInit(void)
	{
		CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.init_done=TRUE;
	}
	
	void CLDBug::DbugStateDestroy(void)
	{
		if (CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.init_done)
		{
			CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.init_done=FALSE;
		}
	}

	int CLDBug::TRACING () { return CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & TRACE_ON;}
	int CLDBug::DEBUGGING () { return CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & DEBUG_ON;}
	int CLDBug::PROFILING () { return CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar.stack -> flags & PROFILE_ON;}

	/**
	 *     重定向标准输出和错误输出
	 */
	void CLDBug::SetStdOutErr(const char* psFile, char *psBuffer, size_t iSize, bool bAppend)
	{
		memset(psBuffer, 0, iSize);
		int iFlag = 0;
		if (psFile)
		{
#ifdef __WIN__
			if (bAppend)
			{
				iFlag = _O_APPEND;
			}
			else
			{
				iFlag = _O_TRUNC;
			}
			int logfd=_open(psFile, _O_RDWR|_O_CREAT|iFlag, _S_IREAD | _S_IWRITE);
			if(logfd != -1)
			{
				_dup2(logfd, 1);//将标准输出重定向
				_dup2(logfd, 2);//将标准错误重定向
				_close(logfd);
				setvbuf(stdout, psBuffer, _IOLBF, iSize);//设置行缓冲
			}
#else
			if (bAppend)
			{
				iFlag = O_APPEND;
			}
			else
			{
				iFlag = O_TRUNC;
			}
			int logfd=open(psFile, O_RDWR|O_CREAT|iFlag, S_IRWXU);
			if(logfd != -1)
			{
				dup2(logfd, 1);//将标准输出重定向
				dup2(logfd, 2);//将标准错误重定向
				close(logfd);
				setvbuf(stdout, psBuffer, _IOLBF, iSize);//设置行缓冲
			}
#endif
		}
	}
}

