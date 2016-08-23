#ifndef __CLDbug_h__
#define __CLDbug_h__

namespace NSPrime
{
	/*
	*	Debugging states can be pushed or popped off of a
	*	stack which is implemented as a linked list.  Note
	*	that the head of the list is the current state and the
	*	stack is pushed by adding a new state to the head of the
	*	list or popped by removing the first link.
	*/

	struct state {
		int flags;			/* Current state flags */
		int maxdepth;			/* Current maximum trace depth */
		ub4 delay;			/* Delay after each output line */
		int sub_level;		/* Sub this from code_state->level */
		FILE *out_file;		/* Current output stream */
		FILE *prof_file;		/* Current profiling stream */
		char name[PATH_MAX];		/* Name of output file */
		TDbLink *functions;	/* list of functions */
		TDbLink *p_functions;	/* list of profiled functions */
		TDbLink *keywords;	/* list of debug keywords */
		TDbLink *processes;	/* list of process names */
	};



	typedef struct st_code_state {
		int lineno;			/* Current debugger output line number */
		int level;			/* Current function nesting level */
		const char *func;		/* Name of current user function */
		const char *file;		/* Name of current user file */
		int jmplevel;			/* Remember nesting level at setjmp () */
		const char *jmpfunc;		/* Remember current function for setjmp */
		const char *jmpfile;		/* Remember current file for setjmp */

		/*
		*	The following variables are used to hold the state information
		*	between the call to _db_pargs_() and _db_doprnt_(), during
		*	expansion of the DBUG_PRINT macro.  This is the only macro
		*	that currently uses these variables.
		*
		*	These variables are currently used only by _db_pargs_() and
		*	_db_doprnt_().
		*/

		ub4 u_line;			/* User source code line number */
		const char *u_keyword;	/* Keyword for current macro */
		int  locked;			/* If locked with _db_lock_file */
	} CODE_STATE;

	typedef struct tagDBugGlbalVar
	{
		bool init_done; /* Set to TRUE when initialization done */
		struct state *stack;

		/*
		*	Variables which are available externally but should only
		*	be accessed via the macro package facilities.
		*/
		FILE *_db_fp_;	/* Output stream, default stderr */
		const char *_db_process_; /* Pointer to process name; argv[0] */
		FILE *_db_pfp_;	/* Profile stream, 'dbugmon.out' */
		bool _db_pon_;	/* TRUE if profile currently on */
		bool _db_on_;		/* TRUE if debugging currently on */
		bool _no_db_;		/* TRUE if no debugging at all */

#ifdef THREAD
		NSPrime::CLCriticalSection m_tThrLockDbug;
#else
		CODE_STATE  static_code_state;
#endif
	}TDBugGlbalVar;

	class CLDBug
	{
	public:
		static void perror (const char *s);		/* Fake system/library error print routine */
		static CODE_STATE *code_state(void);

		static void DbugStateInit(void);
		static void DbugStateDestroy(void);

		/*
		*	      Manifest constants that should not require any changes.
		*/
		static const char*	_DBUG_START_CONDITION_;//"d:t"
		static const int	EOS				=	0;  // End Of String marker 
		static const int	PRINTBUF			=	1024;    // Print buffer size 
		static const int	INDENT			=	2;       // Indentation per trace level 
		static const int	MAXDEPTH			=	200;     // Maximum trace depth default 
		static const int	TRACE_ON			=	000001;	// Trace enabled 
		static const int	DEBUG_ON			=	000002;	// Debug enabled 
		static const int	FILE_ON			=	000004;	// File name print enabled 
		static const int	LINE_ON			=	000010;	// Line number print enabled 
		static const int	DEPTH_ON			=	000020;	// Function nest level print enabled 
		static const int	PROCESS_ON		=	000040;	// Process name print enabled 
		static const int	NUMBER_ON		=	000100;	// Number each line of output 
		static const int	PROFILE_ON		=	000200;	// Print out profiling code 
		static const int	PID_ON			=	000400;	// Identify each line with process id 
		static const int	SANITY_CHECK_ON	=	001000;	// Check safemalloc on DBUG_ENTER 
		static const int	FLUSH_ON_WRITE	=	002000;	// Flush on every write 

		static int TRACING ();
		static int DEBUGGING ();
		static int PROFILING ();

		static inline int STREQ (const char* a,const char* b) { return strcmp(a,b) == 0;}

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

		static const char*	const PROF_FILE;
		static const char*	const PROF_EFMT;
		static const char*	const PROF_SFMT;
		static const char*	const PROF_XFMT;


		static int _db_keyword_(const char *keyword);
		static void _db_setjmp_(void);
		static void _db_longjmp_(void);
		static void _db_push_(const char *control);
		static void _db_pop_(void);
		static void _db_enter_(const char *_func_,const char *_file_,ub4 _line_,
			const char **_sfunc_,const char **_sfile_,
			ub4 *_slevel_);
		static void _db_return_(ub4 _line_,const char **_sfunc_,const char **_sfile_,
			ub4 *_slevel_);
		static void _db_pargs_(ub4 _line_,const char *keyword);
		static void _db_doprnt_ (const char *format,...);
		static void _db_dump_(ub4 _line_,const char *keyword,const char *memory,
			ub4 length);
		static void _db_lock_file();
		static void _db_unlock_file();

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
		static TDbLink *ListParse (char *ctlp);

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

		static bool InList (TDbLink *linkp,const char *cp);

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
		static void PushState ();

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
		static bool DoTrace (CODE_STATE *state);

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
		static bool DoProfile ();

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
		static void Indent (int indent);

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
		static void FreeList (TDbLink *linkp);

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
		static char *StrDup (const char *str);

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
		static void DoPrefix (ub4 _line_);

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
		static void DBUGOpenFile (const char *name,int append);

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
		static FILE *OpenProfile (const char *name);

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
		static void CloseFile (FILE *fp);

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
		static void DbugExit (const char *why);


		/*
		*		As strtok but two separators in a row are changed to one
		*		separator (to allow directory-paths in dos).
		*/
		static char *static_strtok (char *s1, char separator);

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
		static char *BaseName (const char *pathname);

		/* flush dbug-stream, free mutex lock & wait delay */
		/* This is because some systems (MSDOS!!) dosn't flush fileheader */
		/* and dbug-file isn't readable after a system crash !! */
		static void dbug_flush(CODE_STATE *state);

		static int SetDebug();

		/**
		 *     重定向标准输出和错误输出
		 */
		static void SetStdOutErr(const char* psFile, char *psBuffer, size_t iSize, bool bAppend);
	};
#ifndef DBUG_OFF
#define DBUG_ENTER(a) const char *_db_func_, *_db_file_; ub4 _db_level_; \
	NSPrime::CLDBug::_db_enter_ (a,__FILE__,__LINE__,&_db_func_,&_db_file_,&_db_level_)
#define DBUG_LEAVE \
	(NSPrime::CLDBug::_db_return_ (__LINE__, &_db_func_, &_db_file_, &_db_level_))
#define DBUG_RETURN(a1) {DBUG_LEAVE; return(a1);}
#define DBUG_VOID_RETURN {DBUG_LEAVE; return;}
#define DBUG_EXECUTE(keyword,a1) \
	{if (NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_on_) {if (NSPrime::CLDBug::_db_keyword_ (keyword)) { a1 }}}
#define DBUG_PRINT(keyword,arglist) \
	{if (NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_on_) {NSPrime::CLDBug::_db_pargs_(__LINE__,keyword); NSPrime::CLDBug::_db_doprnt_ arglist;}}
#define DBUG_PUSH(a1) NSPrime::CLDBug::_db_push_ (a1)
#define DBUG_POP() NSPrime::CLDBug::_db_pop_ ()
#define DBUG_PROCESS(a1) (NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_process_ = a1)
#define DBUG_FILE (NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_)
#define DBUG_SETJMP(a1) (_db_setjmp_ (), setjmp (a1))
#define DBUG_LONGJMP(a1,a2) (_db_longjmp_ (), longjmp (a1, a2))
#define DBUG_DUMP(keyword,a1,a2)\
	{if (NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_on_) {NSPrime::CLDBug::_db_dump_(__LINE__,keyword,a1,a2);}}
#define DBUG_IN_USE (NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_fp_ && NSPrime::CLDBug::_db_fp_ != stderr)
#define DEBUGGER_OFF NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._no_db_=true;NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._db_on_=false;
#define DEBUGGER_ON  NSPrime::CLDbugLibInit::g_ptLibDbugGlobalVar->m_tDBugGlbalVar._no_db_=false
#define DBUG_LOCK_FILE { NSPrime::CLDBug::_db_lock_file(); }
#define DBUG_UNLOCK_FILE { NSPrime::CLDBug::_db_unlock_file(); }
#define DBUG_ASSERT(A) assert(A)
#define DBUG_FRESH	NSPrime::CLDBug::SetDebug();
#else						/* No debugger */
#define DBUG_ENTER(a1)
#define DBUG_LEAVE
#define DBUG_RETURN(a1) return(a1)
#define DBUG_VOID_RETURN return
#define DBUG_EXECUTE(keyword,a1) {}
#define DBUG_PRINT(keyword,arglist) {}
#define DBUG_PUSH(a1) {}
#define DBUG_POP() {}
#define DBUG_PROCESS(a1) {}
#define DBUG_FILE (stderr)
#define DBUG_SETJMP setjmp
#define DBUG_LONGJMP longjmp
#define DBUG_DUMP(keyword,a1,a2) {}
#define DBUG_IN_USE 0
#define DEBUGGER_OFF
#define DEBUGGER_ON
#define DBUG_LOCK_FILE
#define DBUG_UNLOCK_FILE
#define DBUG_ASSERT(A) {}
#define DBUG_FRESH	;
#endif/*defined(DBUG_OFF)*/
}
#endif//__CLDbug_h__
