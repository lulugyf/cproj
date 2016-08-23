#include "cppcompile.h"

static int iFirstFileNamePos = -1;				//第一个文件的位置。
static const char *psSrcCppPathName = NULL;	//源文件所在的路径

static const char *psEscFuncFileName = NULL;	//过滤函数的文件名
static char *psSrcCppFileContent = NULL;	//文件内容。
static const char *psDbLoginString = NULL;	//数据库登录串。格式“user/password@db”。
static otl_connect *db = NULL;
char sCurrTime[14+1];					//当前时间，格式“YYYYMMDDHH24MISS”。

static TProgType tProgType=PT_UNKOWN;			//程序类型。
static bool bIsPrintDependSo=false;			//是否打印依赖库。

static bool bIsCheckConflictFileName=true;		//是否检查冲突的文件名。
static bool bIsCheckConflictFunction=true;		//是否检查冲突的函数。

static char sTableOwner[256];				//数据库表的属主

static bool bIsTreePrintDependSo = false;				//以树状关系打印依赖库，相当于从上层往底层查询依赖关系。
static bool bIsTreePrintDependedSo = false;				//以树状关系打印被依赖库，相当于从底层往上层查询依赖关系。

static bool bIsReserveCPPFunc = true;				//是否保留C++函数，默认保留。

#define DEF_ESC_FUNC_FILE_NAME "EscFuncFile.txt"
// ---------------------------------------------------------------------------
//
//  Usage()
//
// ---------------------------------------------------------------------------
void Usage()
{
	printf("\nUsage:\n"
		"    cppcompile [options]  cppfile1 cppfile2 cppfile3 ...>\n\n"
		"comment:\n"
		"	编译一个文件。\n\n"
		"Options:\n"
		"    -notchkfile   是否不检查冲突的文件名，加上此选项则不检查.\n"
		"    -notchkfunc   是否不检查冲突的函数名，加上此选项则不检查.\n"
		"    -reservecppf=yes  是否保留C++函数，默认保留，取值范围yes或no.\n"
		"    -progtype=so   程序的类型，取值范围exec、so和service.\n"
		"    -pdepso=no   是否打印依赖库，取值范围yes或no.\n"
		"    -ptreedepso     以树状关系打印依赖库，相当于从上层往底层查询依赖关系。\n"
		"    -ptreedepedso     以树状关系打印被依赖库，相当于从底层往上层查询依赖关系。\n"
		"    -path=xxx   源文件所在的路径.\n"
		"    -esc=FileName   过滤函数的文件名，默认“EscFuncFile.txt”.\n"
		"    -dbstr=psDbLoginString   数据库登录串，必填。格式“user/password@db”.\n"
		"    -towner=xxx   数据库表的属主.\n"
		"    -?          显示帮助.\n\n"
		"version: \n"
		"	1.0.20\n\n"
		"author: \n"
		"	lugz\n\n"
		"\n");
}

int AnalyseMainOption(int argc, char* argv[])
{
	if (argc < 2)
	{
		Usage();
		return 1;
	}

	memset(sTableOwner, 0, sizeof(sTableOwner));

	bool bFoundProgType = false;
	bool bFoundIsPrintDependSo = false;
	int iParamPos;
	for (iParamPos = 1; iParamPos < argc; iParamPos++)
	{
		if (argv[iParamPos][0] != '-')
			break;

		if (!strcmp(argv[iParamPos], "-?"))
		{
			Usage();
			return 1;
		}
		else if (!strncmp(argv[iParamPos], "-notchkfile", 11))
		{
			bIsCheckConflictFileName = false;
		}
		else if (!strncmp(argv[iParamPos], "-notchkfunc", 11))
		{
			bIsCheckConflictFunction = false;
		}
		else if (!strncmp(argv[iParamPos], "-path=", 6))
		{
			psSrcCppPathName = argv[iParamPos] + 6;
		}
		else if (!strncmp(argv[iParamPos], "-esc=", 5))
		{
			psEscFuncFileName = argv[iParamPos] + 5;
		}
		else if (!strncmp(argv[iParamPos], "-dbstr=", 7))
		{
			psDbLoginString = argv[iParamPos] + 7;
		}
		else if (!strncmp(argv[iParamPos], "-progtype=", 10))
		{
			bFoundProgType = true;
			if (strncmp(argv[iParamPos] + 10, "exec", 4) == 0)
			{
				tProgType = PT_EXEC;
			}
			else if (strncmp(argv[iParamPos] + 10, "so", 2) == 0)
			{
				tProgType = PT_SO;
			}
			else if (strncmp(argv[iParamPos] + 10, "service", 7) == 0)
			{
				tProgType = PT_SERVICE;
			}
			else
			{
				Usage();
				return 1;
			}
		}
		else if (!strncmp(argv[iParamPos], "-pdepso=", 8))
		{
			bFoundIsPrintDependSo = true;
			if (strncmp(argv[iParamPos] + 8, "yes", 3) == 0)
			{
				bIsPrintDependSo = true;
			}
			else if (strncmp(argv[iParamPos] + 8, "no", 2) == 0)
			{
				bIsPrintDependSo = false;
			}
			else
			{
				Usage();
				return 1;
			}
		}
		else if (!strncmp(argv[iParamPos], "-reservecppf=", 13))
		{
			if (strncmp(argv[iParamPos] + 13, "yes", 3) == 0)
			{
				bIsReserveCPPFunc = true;
			}
			else if (strncmp(argv[iParamPos] + 13, "no", 2) == 0)
			{
				bIsReserveCPPFunc = false;
			}
			else
			{
				Usage();
				return 1;
			}
		}
		else if (!strncmp(argv[iParamPos], "-ptreedepso", 11))
		{
			bIsTreePrintDependSo = true;
		}
		else if (!strncmp(argv[iParamPos], "-ptreedepedso", 13))
		{
			bIsTreePrintDependedSo = true;
		}
		else if (!strncmp(argv[iParamPos], "-towner=", 8))
		{
			strncpy(sTableOwner, argv[iParamPos] + 8, 255);
		}
		else
		{
			Usage();
			return 1;
		}
	}

	if (psSrcCppPathName == NULL)
	{
		Usage();
		return 1;
	}

	if (psEscFuncFileName == NULL)
	{
		psEscFuncFileName = DEF_ESC_FUNC_FILE_NAME;
	}

	if (psDbLoginString == NULL)
	{
		Usage();
		return 1;
	}

	if (!bFoundProgType)
	{
		Usage();
		return 1;
	}

	if (!bFoundIsPrintDependSo)
	{
		Usage();
		return 1;
	}
	
	if (iParamPos == argc)
    {
        Usage();
        return 1;
    }
	iFirstFileNamePos = iParamPos;

	return 0;
}

/**
 *     替换转义字符，为指定字符。
 */
void ClearEsc(char* srcStream, int c)
{
	int i;
	int inLen;

	if (srcStream == NULL) return;
	inLen=(int)strlen(srcStream);
	if (inLen <= 2 )
	{
		return;
	}
	
	i = 0;
	while(i < inLen)
	{
		if ((srcStream[i] == '\\') && (i != inLen - 1))
		{
			srcStream[i] = c;
			srcStream[i+1] = c;
			i ++;
		}
		i ++;
	}
}

/**
 *     清除预定义行，如#include, #define等以“#”开头的语句。
 */
void ClearPoundSignStmt(char* srcStream, int c)
{
	int i;
	int inLen;

	if (srcStream == NULL) return;
	inLen=(int)strlen(srcStream);
	if (inLen <= 2 )
	{
		return;
	}
	
	i = 0;
	while(i < inLen)
	{
		if (srcStream[i] == '#')
		{
			while((i < inLen) && (srcStream[i] != '\n'))
			{
				srcStream[i] = c;
				i ++;
			}
		}
		i ++;
	}
}


///前一个字符
inline char PreChar(const char* srcStream, int iPos)
{
	if (iPos != 0)
	{
		return srcStream[iPos - 1];
	}
	else
	{
		return 0;	//返回空字符。
	}
}

///查找前一个字符
inline const char* FindPreChar(const char* srcStream, int iPos, int c)
{
	while (iPos >= 0)
	{
		if (srcStream[iPos] == c)
		{
			return srcStream + iPos;
		}
		iPos --;
	}
	return NULL;
}


///下一个字符
inline char NextChar(const char* srcStream, int iPos, int inLen)
{
	if (iPos < inLen - 1)
	{
		return srcStream[iPos + 1];
	}
	else
	{
		return 0;	//返回空字符。
	}
}

///是一个合法的变量字符。
inline bool IsLiteralChar(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
	{
		return true;
	}
	return false;
}

///得到前一个单词
///iPos包含本位置。
///成功返回单词的前一个位置。
inline int GetPreWord(const char* srcStream, int iPos, char *psWord)
{
	while(iPos >= 0)
	{
		if (isspace(srcStream[iPos]))
		{
			iPos --;
			continue;
		}
		break;
	}

	int iEnd = iPos;
	if (iPos >=0)
	{
		bool bIsLiteralWord = IsLiteralChar(srcStream[iPos]);
		
		while(iPos >= 0)
		{
			if (!isspace(srcStream[iPos]))
			{
				if (bIsLiteralWord != IsLiteralChar(srcStream[iPos]))
				{
					break;
				}
				else if (!bIsLiteralWord)
				{
					iPos --;
					break;
				}
				iPos --;
				continue;
			}
			break;
		}
		if (iPos < 0)
		{
			strncpy(psWord, srcStream, iEnd + 1);
			psWord[iEnd] = '\0';
		}
		else
		{
			strncpy(psWord, srcStream + iPos + 1, iEnd - iPos);
			psWord[iEnd - iPos] = '\0';
		}
	}

	return iPos;
}


/**
 *     清除注释和引号中的内容。
 */
void ClearQuotationConentAndComment(char* srcStream, int c)
{
	int i;
	int inLen;
	bool bInClearMark=false;	//是否在清除标记块里。
	typedef enum tagClearMark
	{
		CLEAR_MARK_NONE = 0,				//不在清除块里。
		CLEAR_MARK_DOUBLE_QUOTATION = 1,	//双引号
		CLEAR_MARK_SINGLE_QUOTATION = 2,	//单引号
		CLEAR_MARK_LINE_COMMENT = 3,		//行备注“//”
		CLEAR_MARK_BLOCK_COMMENT = 4		//块备注 “/**/”
	}TClearMark;

	TClearMark enumClearMark = CLEAR_MARK_NONE;

	if (srcStream == NULL) return;
	inLen=(int)strlen(srcStream);
	if (inLen <= 2 )
	{
		return;
	}
	
	//清除双引号和单引号中的内容。
	i = 0;
	while(i < inLen)
	{
		if (enumClearMark == CLEAR_MARK_NONE)
		{
			if ((srcStream[i] == '\"') || (srcStream[i] == '\'') || (srcStream[i] == '/'))
			{
				if (srcStream[i] == '\"')
				{
					enumClearMark = CLEAR_MARK_DOUBLE_QUOTATION;
				}
				else if (srcStream[i] == '\'')
				{
					enumClearMark = CLEAR_MARK_SINGLE_QUOTATION;
				}
				else //srcStream[i] == '/'
				{
					char cNextChar = NextChar(srcStream, i, inLen);
					if (cNextChar == '/')
					{
						enumClearMark = CLEAR_MARK_LINE_COMMENT;
						srcStream[i] = c;
						srcStream[i+1] = c;
					}
					else if (cNextChar == '*')
					{
						enumClearMark = CLEAR_MARK_BLOCK_COMMENT;
						srcStream[i] = c;
					}
				}
			}
			else
			{
				//正常程序，不做处理。
			}
		}
		else
		{
			switch(enumClearMark)
			{
			case CLEAR_MARK_DOUBLE_QUOTATION:
				{
					if (srcStream[i] == '\"')
					{
						enumClearMark = CLEAR_MARK_NONE;
					}
					else
					{
						srcStream[i] = c;
					}
					break;
				}
			case CLEAR_MARK_SINGLE_QUOTATION:
				{
					if (srcStream[i] == '\'')
					{
						enumClearMark = CLEAR_MARK_NONE;
					}
					else
					{
						srcStream[i] = c;
					}
					break;
				}
			case CLEAR_MARK_LINE_COMMENT:
				{
					if (srcStream[i] == '\n')
					{
						enumClearMark = CLEAR_MARK_NONE;
					}
					else
					{
						srcStream[i] = c;
					}
					break;
				}
			case CLEAR_MARK_BLOCK_COMMENT:
				{
					char cNextChar = NextChar(srcStream, i, inLen);
					if ((srcStream[i] == '*') &&(cNextChar == '/'))
					{
						enumClearMark = CLEAR_MARK_NONE;
						srcStream[i] = c;
						srcStream[i+1] = c;
					}
					else
					{
						srcStream[i] = c;
					}
					break;
				}
			}
		}
		i ++;
	}
}

void GetFileConent(int fhSrcCppFile, const char *psSrcCppFileName)
{
	int iFileSize;
	/* Set the end of the file: */
#ifdef WIN32
	iFileSize = _lseek( fhSrcCppFile, 0L, SEEK_END );
#else
	iFileSize = lseek( fhSrcCppFile, 0L, SEEK_END );
#endif

#ifdef WIN32
	_lseek( fhSrcCppFile, 0L, SEEK_SET );
#else
	lseek( fhSrcCppFile, 0L, SEEK_SET );
#endif
	if (iFileSize == 0)
	{
		throw BaseExcept(1, "文件[%s]内容为空！\n", psSrcCppFileName);
	}
	else
	{
		psSrcCppFileContent = (char *)malloc(iFileSize + 1);
		memset(psSrcCppFileContent, 0, iFileSize + 1);

#ifdef WIN32
		int iRealRead = _read(fhSrcCppFile, (void*)psSrcCppFileContent, iFileSize);
#else
		int iRealRead = read(fhSrcCppFile, (void*)psSrcCppFileContent, iFileSize);
#endif
		psSrcCppFileContent[iRealRead] = '\0';

		ClearEsc(psSrcCppFileContent, ' ');
		ClearQuotationConentAndComment(psSrcCppFileContent, ' ');
		ClearPoundSignStmt(psSrcCppFileContent, ' ');
	}
}

bool ValidBusiFunc(const char *psCallFuncName, std::list<std::string> &lstEscFunc)
{
	std::list<std::string>::iterator iterEscFunc;

	for(iterEscFunc = lstEscFunc.begin(); iterEscFunc != lstEscFunc.end(); iterEscFunc ++)
	{
		if (strcmp(psCallFuncName, (*iterEscFunc).c_str()) == 0)
		{
			return false;
		}
	}
	return true;
}

inline void AddCallFunc(std::string &sFuncCallName, std::string &sFuncDefName, std::list<StringPair> &lstFuncCall,
	std::list<std::string> &lstEscFunc)
{
	if (ValidBusiFunc(sFuncCallName.c_str(), lstEscFunc))
	{
		bool bFound = false;
		std::list<StringPair>::iterator iterFuncCall;
		for(iterFuncCall = lstFuncCall.begin(); iterFuncCall != lstFuncCall.end(); iterFuncCall ++)
		{
			if (((*iterFuncCall).first.compare(sFuncDefName) == 0))
			{
				if (((*iterFuncCall).second.compare(sFuncCallName) == 0))
				{
					bFound = true;
					break;
				}
			}
		}

		if (!bFound)
		{
			lstFuncCall.push_back(StringPair(sFuncDefName, sFuncCallName));
		}
	}
}

void AddMiddwareServiceCallBackFunc(const char* srcStream, int iLeftParenthesisPos, std::list<std::string> &lstFuncDef, std::list<StringPair> &lstFuncCall,
	std::list<std::string> &lstEscFunc, std::string &sFuncDefName, std::string &sFuncCallName)
{
	char sLine[512];
	int iPos;
	char sWord[512];

	memset(sWord, 0, sizeof(sWord));
	//modified by zhengxg at 20111215 to add tuxadp1
	if ((sFuncCallName.compare("tuxadp") == 0)||
		(sFuncCallName.compare("TUXADP") == 0)||
		(sFuncCallName.compare("tuxadpEx") == 0)||
		(sFuncCallName.compare("TUXADPEX") == 0)||
		(sFuncCallName.compare("tuxadp1") == 0)||
		(sFuncCallName.compare("TUXADP1") == 0))
	{
		memset(sLine, 0, sizeof(sLine));
		const char *psSemicolon= strchr(srcStream + iLeftParenthesisPos, ';');
		if (psSemicolon == NULL)
		{
			throw BaseExcept(1, "函数 %s 没有正常结束", sFuncCallName.c_str());
		}
		const char *psComma = strchr(srcStream + iLeftParenthesisPos, ',');
		int iCommaCount = 0;
		while(psComma)
		{
			iCommaCount ++;
			psComma = strchr(psComma + 1, ',');
			if (psComma > psSemicolon)
			{
				break;
			}
			else if (iCommaCount == 4)
			{
				break;
			}
		}
											
		if ((iCommaCount == 4)&&(psComma < psSemicolon))
		{
			if ( (iPos = GetPreWord(srcStream, psComma - srcStream - 1, sWord)) < 0)
			{
				throw BaseExcept(1, "得到中间件回调函数的名称出错");
			}
			std::string sCallBackFunctionName;
			sCallBackFunctionName = sWord; 
			AddCallFunc(sCallBackFunctionName, sFuncDefName, lstFuncCall, lstEscFunc);
		}
	}	//modified by zhengxg at 20111215 to add AssiMutiConnWork
	else if((sFuncCallName.compare("AssiMutiConnWork") == 0))
	{
		const char *psSemicolon= strchr(srcStream + iLeftParenthesisPos, ';');
		if (psSemicolon == NULL)
		{
			throw BaseExcept(1, "函数 %s 没有正常结束", sFuncCallName.c_str());
		}
		const char *psComma = strchr(srcStream + iLeftParenthesisPos, ',');
		int iCommaCount = 0;
		while(psComma)
		{
			iCommaCount ++;
			psComma = strchr(psComma + 1, ',');
			if (psComma > psSemicolon)
			{
				break;
			}
			else if (iCommaCount == 2)
			{
				break;
			}
		}
											
		if ((iCommaCount == 2)&&(psComma < psSemicolon))
		{
			if ( (iPos = GetPreWord(srcStream, psComma - srcStream - 1, sWord)) < 0)
			{
				throw BaseExcept(1, "得到双库回调函数的名称出错");
			}
			std::string sCallBackFunctionName;
			sCallBackFunctionName = sWord; 
			AddCallFunc(sCallBackFunctionName, sFuncDefName, lstFuncCall, lstEscFunc);
		}
	}
}


/**
 *  得到依赖的动态链接库字符串。
 */
void AddFuncDef(std::list<std::string> &lstFuncDef, std::string &sFuncDefName)
{
	std::list<std::string>::iterator iterDependSo;
	bool bIsFound = false;
	for(iterDependSo = lstFuncDef.begin(); iterDependSo != lstFuncDef.end(); iterDependSo ++)
	{
		if (iterDependSo->compare(sFuncDefName) == 0)
		{
			bIsFound = true;
		}
	}

	if (!bIsFound)
	{
		lstFuncDef.push_back(sFuncDefName);
	}
}

/**
 * 函数定义定义原则，参考规则1和规则二：
 *     （1）type func (type value, ...) {}
 *     （2）考虑 “type func (type value, ...) throw (...){}”这种异常等类的定义。
 *     （3）考虑 “type func (type value, ...) const{}”这种常量函数的定义。
 */
void DealStream(const char* srcStream, std::list<std::string> &lstFuncDef, std::list<StringPair> &lstFuncCall,
	std::list<std::string> &lstEscFunc)
{
	int i = 0, iFuncDeep=0, j = 0, iPos;
	const char *p;
	bool isQuotationMark=false, bIsFunc=false;
	char sWord[512];
	std::string sFuncDefName, sFuncCallName;

	if (srcStream == NULL) return;
	int inLen=(int)strlen(srcStream);
	if (inLen < 2 )
	{
		return;
	}

	i = 0;
	while (i < inLen)
	{
		if ((srcStream[i] == '\"') && PreChar(srcStream, i) != '\\')
		{
			isQuotationMark = !isQuotationMark;
		}

		if (!isQuotationMark)
		{
			if (iFuncDeep == 0)	//函数外面
			{
				if (srcStream[i] == '{')
				{
					iFuncDeep ++;
				
					if ( (iPos = GetPreWord(srcStream, i - 1, sWord)) < 0)
					{
						throw BaseExcept(1, "分析函数失败1");
					}
					
					if (strcmp(sWord, ")") == 0)
					{
						p = FindPreChar(srcStream, iPos, '(');
						if (!p)
						{
							throw BaseExcept(1, "分析函数失败2");
						}

						if ( (iPos = GetPreWord(srcStream,  p - srcStream - 1, sWord)) < 0)
						{
							throw BaseExcept(1, "分析函数失败3");
						}

						if (strcmp(sWord, "throw") == 0)	//分析规则2.
						{
							//异常信息。
							p = FindPreChar(srcStream, iPos, '(');
							if (!p)
							{
								throw BaseExcept(1, "分析函数失败4");
							}

							if ( (iPos = GetPreWord(srcStream, p - srcStream - 1, sWord)) < 0)
							{
								throw BaseExcept(1, "分析函数失败5");
							}
						}

						bIsFunc = true;
						//sWord是函数定义的名字。
						sFuncDefName = sWord;
						AddFuncDef(lstFuncDef, sFuncDefName);
					}
					else
					{
						if ( (iPos = GetPreWord(srcStream, i - 1, sWord)) < 0)
						{
							throw BaseExcept(1, "分析函数失败6");
						}

						if (strcmp(sWord, "const") == 0)  //分析规则3.
						{
							p = FindPreChar(srcStream, iPos, '(');
							if (!p)
							{
								throw BaseExcept(1, "分析函数失败7");
							}

							if ( (iPos = GetPreWord(srcStream, p - srcStream - 1, sWord)) < 0)
							{
								throw BaseExcept(1, "分析函数失败8");
							}

							bIsFunc = true;
							//sWord是函数定义。
							sFuncDefName = sWord;
							AddFuncDef(lstFuncDef, sFuncDefName);
						}
						else
						{
							//不是函数。
							bIsFunc = false;
						}
					}
				}

				if (srcStream[i] == '}')
				{
					iFuncDeep --;
					if (iFuncDeep == 0)
					{
						//不是函数。
						bIsFunc = false;
					}
				}
			}
			else
			{
				if (srcStream[i] == '{')
				{
					iFuncDeep ++;
				}
				else if (srcStream[i] == '}')
				{
					iFuncDeep --;
					if (iFuncDeep == 0)
					{
						//不是函数。
						bIsFunc = false;
					}
				}
				else if (bIsFunc)
				{
					//处理函数里面的信息。
					if (srcStream[i] == '(')	//判断是否调用了函数。
					{
						if ( (iPos = GetPreWord(srcStream, i - 1, sWord)) < 0)
						{
							throw BaseExcept(1, "分析函数失败9");
						}

						if (IsLiteralChar(sWord[0]))
						{
							sFuncCallName = sWord;

							if ( (iPos = GetPreWord(srcStream, iPos, sWord)) < 0)
							{
								throw BaseExcept(1, "分析函数失败10");
							}

							if (sWord[0] == '.')
							{
								if (bIsReserveCPPFunc)
								{
									AddCallFunc(sFuncCallName, sFuncDefName, lstFuncCall, lstEscFunc);
									//中间件服务，还需要查找回调函数。
									if ((tProgType == PT_SO) || (tProgType == PT_SERVICE))
									{
										AddMiddwareServiceCallBackFunc(srcStream, i, lstFuncDef, lstFuncCall,
											lstEscFunc, sFuncDefName, sFuncCallName);
									}
								}
								else
								{
									//过滤成员函数。
								}
							}
							else if (sWord[0] == '>')
							{
								if (srcStream[iPos] == '-')
								{
									if (bIsReserveCPPFunc)
									{
										AddCallFunc(sFuncCallName, sFuncDefName, lstFuncCall, lstEscFunc);
										//中间件服务，还需要查找回调函数。
										if ((tProgType == PT_SO) || (tProgType == PT_SERVICE))
										{
											AddMiddwareServiceCallBackFunc(srcStream, i, lstFuncDef, lstFuncCall,
												lstEscFunc, sFuncDefName, sFuncCallName);
										}
									}
									else
									{
										//过滤成员函数。
									}
								}
								else
								{
									AddCallFunc(sFuncCallName, sFuncDefName, lstFuncCall, lstEscFunc);
									//中间件服务，还需要查找回调函数。
									if ((tProgType == PT_SO) || (tProgType == PT_SERVICE))
									{
										AddMiddwareServiceCallBackFunc(srcStream, i, lstFuncDef, lstFuncCall,
											lstEscFunc, sFuncDefName, sFuncCallName);
									}
								}
							}
							else if (IsLiteralChar(sWord[0]))
							{
								//是C++的构造函数，过滤掉。
								if (strcmp(sWord,  "return") == 0)
								{
									AddCallFunc(sFuncCallName, sFuncDefName, lstFuncCall, lstEscFunc);
									//中间件服务，还需要查找回调函数。
									if ((tProgType == PT_SO) || (tProgType == PT_SERVICE))
									{
										AddMiddwareServiceCallBackFunc(srcStream, i, lstFuncDef, lstFuncCall,
											lstEscFunc, sFuncDefName, sFuncCallName);
									}
								}
							}
							else
							{
								AddCallFunc(sFuncCallName, sFuncDefName, lstFuncCall, lstEscFunc);
								//中间件服务，还需要查找回调函数。
								if ((tProgType == PT_SO) || (tProgType == PT_SERVICE))
								{
									AddMiddwareServiceCallBackFunc(srcStream, i, lstFuncDef, lstFuncCall,
										lstEscFunc, sFuncDefName, sFuncCallName);
								}
							}
						}
					}
				}
			}
		}

		i ++;
	}
}

/**
 *  更新数据库中的信息。
 *@lstOldDependSoFirstLayer 原来依赖的第一层动态链接库
 */
void RefreshCppInfo(std::list<std::string> &lstFuncDef, std::list<StringPair> &lstFuncCall, std::list<std::string> &lstOldDependSoFirstLayer,
	const char *psSrcCppFileName, const char *psSrcCppBaseFileName)
{
	otl_nocommit_stream otlstream;
	otlstream.set_flush(false);
	char sSqlStmt[1024], sSoName[100+1], sSoNameOut[100+1];

	memset(sSqlStmt, 0, sizeof(sSqlStmt));
	try
	{
		if (tProgType == PT_SO)
		{
			memset(sSoName, 0, sizeof(sSoName));
			memset(sSoNameOut, 0, sizeof(sSoNameOut));
			strcpy(sSoName, "lib");
			strcat(sSoName, psSrcCppBaseFileName);
			strcat(sSoName, ".so");

			sprintf(sSqlStmt,"select so_name"
								"  from %s.cp_cpp_dict"
								" where so_name in (select so_name"
								"                     from  %s.cp_deffunc_rela"
								"                    where define_function in (select call_function"
								"                                                from %s.cp_cppcall_dict"
								"                                               where cpp_name = :cpp_name<char[100+1]>"
								"                                                 and so_name = :so_name<char[100+1]>)"
								" AND define_function NOT IN ( SELECT define_function"
								"                                FROM %s.cp_deffunc_rela"
								"                               WHERE cpp_name = :cpp_name2<char[100+1]>"
								"                                 AND so_name = :so_name2<char[100+1]>))",
								sTableOwner, sTableOwner, sTableOwner, sTableOwner);
			otlstream.open(1, sSqlStmt, *db);
			otlstream<<psSrcCppFileName<<sSoName<<psSrcCppFileName<<sSoName;
			otlstream.flush();

			while (!otlstream.eof())
			{
				otlstream>>sSoNameOut;
				if(strcmp(sSoName, sSoNameOut) == 0)
				{
					continue;
				}
				lstOldDependSoFirstLayer.push_back(std::string(sSoNameOut));
			}
			otlstream.close();
		}

		//删除表cp_cppcall_dict
		sprintf(sSqlStmt, "delete from %s.cp_cppcall_dict where cpp_name=:cpp_name<char[100+1]> and data_source = :data_source<char[20+1]>", sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<psSrcCppFileName<<CPPCOMPILE_DATA_SOURCE;
		otlstream.flush();
		otlstream.close();

		//删除表cp_deffunc_rela
		sprintf(sSqlStmt, "delete from  %s.cp_deffunc_rela where cpp_name=:cpp_name<char[100+1]> and data_source = :data_source<char[20+1]>", sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<psSrcCppFileName<<CPPCOMPILE_DATA_SOURCE;
		otlstream.flush();
		otlstream.close();

		//删除表cp_cpp_dict
		sprintf(sSqlStmt, "delete from  %s.cp_cpp_dict where cpp_name=:cpp_name<char[100+1]> and data_source = :data_source<char[20+1]>", sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<psSrcCppFileName<<CPPCOMPILE_DATA_SOURCE;
		otlstream.flush();
		otlstream.close();

		//插入表cp_cpp_dict
		sprintf(sSqlStmt, "insert into %s.cp_cpp_dict"
						  "("
						  " cpp_name, so_name, cpp_path, update_time, data_source"
						  ")"
						  "values"
						  "("
						  " :cpp_name<char[100+1]>, 'lib'||:cpp_base_name<char[100+1]>||'.so', :cpp_path<char[255+1]>, to_date(:update_time<char[14+1]>,'YYYYMMDDHH24MISS'), :data_source<char[20+1]>"
						  ")", sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<psSrcCppFileName;
		otlstream<<psSrcCppBaseFileName;
		otlstream<<psSrcCppPathName;
		otlstream<<sCurrTime;
		otlstream<<CPPCOMPILE_DATA_SOURCE;
		otlstream.flush();
		otlstream.close();

		//插入表cp_deffunc_rela
		sprintf(sSqlStmt,"insert into %s.cp_deffunc_rela"
						  "("
						  " cpp_name, so_name, define_function, update_time, data_source"
						  ")"
						  "values"
						  "("
						  " :cpp_name<char[100+1]>, 'lib'||:cpp_base_name<char[100+1]>||'.so', :define_function<char[100+1]>, to_date(:update_time<char[14+1]>,'YYYYMMDDHH24MISS'), :data_source<char[20+1]>"
						  ")", sTableOwner);
		otlstream.open(lstFuncDef.size(), sSqlStmt, *db);
		std::list<std::string>::iterator iterFuncDef;
		for(iterFuncDef = lstFuncDef.begin(); iterFuncDef != lstFuncDef.end(); iterFuncDef ++)
		{
			otlstream<<psSrcCppFileName;
			otlstream<<psSrcCppBaseFileName;
			otlstream<< (*iterFuncDef).c_str();
			otlstream<<sCurrTime;
			otlstream<<CPPCOMPILE_DATA_SOURCE;
		}
		otlstream.flush();
		otlstream.close();

		if (bIsCheckConflictFunction)
		{
			char sConflictFile[100+1], sConflictFunction[100+1];
			sprintf(sSqlStmt, "select cpp_name, define_function"
							  "  from %s.cp_deffunc_rela"
							  " where cpp_name !=:cpp_name<char[100+1]>"
							  "   and define_function in ( select define_function"
							  "                              from %s.cp_deffunc_rela"
							  "                             where cpp_name =:cpp_name2<char[100+1]>)"
							  "   and rownum < 2"
							  , sTableOwner, sTableOwner);
			otlstream.open(1, sSqlStmt, *db);
			std::list<std::string>::iterator iterFuncDef;
			otlstream<<psSrcCppFileName;
			otlstream<<psSrcCppFileName;
			if (!otlstream.eof())
			{
				memset(sConflictFile, 0, sizeof(sConflictFile));
				memset(sConflictFunction, 0, sizeof(sConflictFunction));
				otlstream>>sConflictFile>>sConflictFunction;
				throw BaseExcept(1, "文件%s中的函数%s在文件%s中已经定义过!", psSrcCppFileName, sConflictFunction, sConflictFile);
			}
			otlstream.flush();
			otlstream.close();

		}

		//插入表cp_cppcall_dict
		sprintf(sSqlStmt,"insert into %s.cp_cppcall_dict"
						  "("
						  " cpp_name, so_name, define_function, call_function, update_time, data_source"
						  ")"
						  "values"
						  "("
						  " :cpp_name<char[100+1]>, 'lib'||:cpp_base_name<char[100+1]>||'.so', :define_function<char[100+1]>, :call_function<char[100+1]>, to_date(:update_time<char[14+1]>,'YYYYMMDDHH24MISS'), :data_source<char[20+1]>"
						  ")", sTableOwner);
		otlstream.open(lstFuncCall.size(), sSqlStmt, *db);
		std::list<StringPair>::iterator iterFuncCall;
		for(iterFuncCall = lstFuncCall.begin(); iterFuncCall != lstFuncCall.end(); iterFuncCall ++)
		{
			otlstream<<psSrcCppFileName;
			otlstream<<psSrcCppBaseFileName;
			otlstream<< (*iterFuncCall).first.c_str();
			otlstream<< (*iterFuncCall).second.c_str();
			otlstream<<sCurrTime;
			otlstream<<CPPCOMPILE_DATA_SOURCE;
		}
		otlstream.flush();
		otlstream.close();
	}
	catch (otl_exception &otlErr)
	{
		throw BaseExcept(1, "操作数据库出错，错误代码：%d\n错误信息：%s", otlErr.code, otlErr.msg);
	}
}

/**
 *  得到依赖的动态链接库列表。
 */
void GetDependSo(std::list<std::string> &lstDependSo, std::list<std::string> &lstNewDependSoFirstLayer,
	const char *psSrcCppFileName, const char *psSrcCppBaseFileName,
	TTreeNode &tRootNode)
{
	otl_nocommit_stream otlstream;
	otlstream.set_flush(false);

	char sSoName[100+1], sCppName[100+1],sSoNameOut[100+1], sCppNameOut[100+1];
	char sSqlStmt[1024];

	memset(sSqlStmt, 0, sizeof(sSqlStmt));
	memset(sCppName, 0, sizeof(sCppName));
	memset(sSoName, 0, sizeof(sSoName));
	memset(sSoNameOut, 0, sizeof(sSoNameOut));
	memset(sCppNameOut, 0, sizeof(sCppNameOut));

	strncpy(sCppName, psSrcCppFileName, 100);
	strcpy(sSoName, "lib");
	strcat(sSoName, psSrcCppBaseFileName);
	strcat(sSoName, ".so");

	TTreeNode *pTreeNode;		//节点指针。
	strcpy(tRootNode.sSoName, sSoName);
	std::list<StringNodePair> lstNodeStack1, lstNodeStack2;

	std::list<StringPair> lstDependSoTmp1, lstDependSoTmp2;
	try
	{
		sprintf(sSqlStmt,"select cpp_name, so_name"
							"  from %s.cp_cpp_dict"
							" where so_name in (select so_name"
							"                     from  %s.cp_deffunc_rela"
							"                    where define_function in (select call_function"
							"                                                from %s.cp_cppcall_dict"
							"                                               where cpp_name = :cpp_name<char[100+1]>"
							"                                                 and so_name = :so_name<char[100+1]>)"
							" AND define_function NOT IN ( SELECT define_function"
							"                                FROM %s.cp_deffunc_rela"
							"                               WHERE cpp_name = :cpp_name2<char[100+1]>"
							"                                 AND so_name = :so_name2<char[100+1]>))",
							sTableOwner, sTableOwner, sTableOwner, sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<sCppName<<sSoName<<sCppName<<sSoName;
		otlstream.flush();

		while (!otlstream.eof())
		{
			otlstream>>sCppNameOut>>sSoNameOut;
			//modified by zhengxg at 20111215
			if(0 == strcmp(sSoName, sSoNameOut))
			{
				continue;
			}
			lstDependSoTmp1.push_back(StringPair(std::string(sCppNameOut), std::string(sSoNameOut)));
			lstDependSo.push_back(std::string(sSoNameOut));
			
			if (tProgType == PT_SO)
			{
				lstNewDependSoFirstLayer.push_back(std::string(sSoNameOut));
			}

			tRootNode.iChildNum ++;
			tRootNode.pChildTreeNodeList = (TTreeNode**)SafeRealloc(tRootNode.pChildTreeNodeList, sizeof(TTreeNode*) * tRootNode.iChildNum);
			tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1] = (TTreeNode*)malloc(sizeof(TTreeNode));
			memset(tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1], 0, sizeof(TTreeNode));
			strcpy(tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1]->sSoName, sSoNameOut);
			tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1]->iChildNum = 0;
			tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1]->pChildTreeNodeList = NULL;
			lstNodeStack1.push_back(StringNodePair(std::string(sSoNameOut), tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1]));
		}
		otlstream.close();

		std::list<StringPair>::iterator iterDependSo1, iterDependSo2;
		std::list<StringNodePair>::iterator iterNodeStack1, iterNodeStack2;
		while(1)
		{
			for(iterDependSo1 = lstDependSoTmp1.begin(); iterDependSo1 != lstDependSoTmp1.end(); iterDependSo1 ++)
			{
				otlstream.open(1, sSqlStmt, *db);
				otlstream<<iterDependSo1->first.c_str()<<iterDependSo1->second.c_str()<<iterDependSo1->first.c_str()<<iterDependSo1->second.c_str();
				otlstream.flush();

				pTreeNode = NULL;
				for(iterNodeStack1 = lstNodeStack1.begin(); iterNodeStack1 != lstNodeStack1.end(); iterNodeStack1 ++)
				{
					if (iterNodeStack1->first.compare(iterDependSo1->second) == 0)
					{
						pTreeNode = iterNodeStack1->second;
						break;
					}
				}
				while (!otlstream.eof())
				{
					otlstream>>sCppNameOut>>sSoNameOut;
					//modified by zhengxg at 20111215
					if(0 == strcmp(sSoName, sSoNameOut))
					{
						continue;
					}
					lstDependSoTmp2.push_back(StringPair(std::string(sCppNameOut), std::string(sSoNameOut)));

					if (pTreeNode)
					{
						pTreeNode->iChildNum ++;
						pTreeNode->pChildTreeNodeList = (TTreeNode**)SafeRealloc(pTreeNode->pChildTreeNodeList, sizeof(TTreeNode*) * pTreeNode->iChildNum);
						pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1] = (TTreeNode*)malloc(sizeof(TTreeNode));
						memset(pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1], 0, sizeof(TTreeNode));
						strcpy(pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1]->sSoName, sSoNameOut);
						pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1]->iChildNum = 0;
						pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1]->pChildTreeNodeList = NULL;
						lstNodeStack2.push_back(StringNodePair(std::string(sSoNameOut), pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1]));
					}
				}
				otlstream.close();
			}

			if (lstDependSoTmp2.empty())
			{
				break;
			}
			else
			{
				lstDependSoTmp1.clear();
				bool bFound = false;
				for(iterDependSo2 = lstDependSoTmp2.begin(); iterDependSo2 != lstDependSoTmp2.end(); iterDependSo2 ++)
				{
					bFound = false;
					std::list<std::string>::iterator iterDependSo;
					for(iterDependSo = lstDependSo.begin(); iterDependSo != lstDependSo.end(); iterDependSo ++)
					{
						if (iterDependSo2->second.compare(*iterDependSo) == 0)
						{
							bFound = true;
						}
					}
					if (!bFound)
					{
						lstDependSo.push_back(std::string(iterDependSo2->second));
						lstDependSoTmp1.push_back(StringPair(iterDependSo2->first, iterDependSo2->second));

					}
				}
				lstDependSoTmp2.clear();

				lstNodeStack1.clear();
				for(iterNodeStack2 = lstNodeStack2.begin(); iterNodeStack2 != lstNodeStack2.end(); iterNodeStack2 ++)
				{
					lstNodeStack1.push_back(StringNodePair(iterNodeStack2->first, iterNodeStack2->second));
				}
				lstNodeStack2.clear();
			}
		}
	}
	catch (otl_exception &otlErr)
	{
		throw BaseExcept(1, "操作数据库出错，错误代码：%d\n错误信息：%s", otlErr.code, otlErr.msg);
	}
}

/**
 *  判读文件是否冲突，不同目录下有相同的文件名称。
 */
void CheckConflictFileName(const char *psSrcCppFileName, const char *psSrcCppBaseFileName)
{
	otl_nocommit_stream otlstream;
	otlstream.set_flush(false);

	char sCppName[100+1], sSoName[100+1], sCppPath[255+1];
	char sSqlStmt[1024];

	memset(sSqlStmt, 0, sizeof(sSqlStmt));
	memset(sCppName, 0, sizeof(sCppName));
	memset(sSoName, 0, sizeof(sSoName));
	memset(sCppPath, 0, sizeof(sCppPath));

	strncpy(sCppName, psSrcCppFileName, 100);
	strcpy(sSoName, "lib");
	strcat(sSoName, psSrcCppBaseFileName);
	strcat(sSoName, ".so");

	try
	{
		sprintf(sSqlStmt,"select cpp_path"
						  "  from %s.cp_cpp_dict"
						  " where cpp_name = :cpp_name<char[100+1]>"
						  "   and so_name = :so_name<char[100+1]>",	sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<sCppName<<sSoName;
		otlstream.flush();

		while (!otlstream.eof())
		{
			otlstream>>sCppPath;
			if (strcmp(sCppPath, psSrcCppPathName) != 0)
			{
				throw BaseExcept(1, "目录%s下已经存在文件%s", sCppPath, sCppName);
			}
		}
		otlstream.close();
	}
	catch (otl_exception &otlErr)
	{
		throw BaseExcept(1, "操作数据库出错，错误代码：%d\n错误信息：%s", otlErr.code, otlErr.msg);
	}
}

/**
 *  得到依赖的动态链接库字符串。
 */
void GetDependSoString(std::list<std::string> &lstDependSo, std::string &sDependSoList)
{
	const char* ps= NULL;
	std::list<std::string>::iterator iterDependSo;
	for(iterDependSo = lstDependSo.begin(); iterDependSo != lstDependSo.end(); iterDependSo ++)
	{
		ps = strchr(iterDependSo->c_str(), '.');
		if (ps)
		{
			if (strncmp(iterDependSo->c_str(), "lib", 3) ==0)
			{
				sDependSoList.append("-l");
				sDependSoList.append(iterDependSo->c_str() + 3, ps - iterDependSo->c_str() - 3);
				sDependSoList.append(" ");
			}
			else
			{
				throw BaseExcept(1, "错误的动态链接库名字：%s", iterDependSo->c_str());
			}
		}
		else
		{
			throw BaseExcept(1, "错误的动态链接库名字：%s", iterDependSo->c_str());
		}
	}
}

void PrintTreeNodeLevel(TTreeNode *ptNode, int iLevel)
{
	for(int i = 0; i < iLevel; i ++)
	{
		printf("    ");
	}
	printf("%s\n", ptNode->sSoName);
	for(int j = 0; j < ptNode->iChildNum; j ++)
	{
		PrintTreeNodeLevel(ptNode->pChildTreeNodeList[j], iLevel + 1);
	}
}

void PrintTreeNode(TTreeNode &tRootNode)
{
	printf("Tree Info:\n");
	printf("%s\n", tRootNode.sSoName);
	for(int i = 0; i < tRootNode.iChildNum; i ++)
	{
		PrintTreeNodeLevel(tRootNode.pChildTreeNodeList[i], 1);
	}
}

void FreeTreeNode(TTreeNode *ptNode)
{
	for(int i = 0; i < ptNode->iChildNum; i ++)
	{
		FreeTreeNode(ptNode->pChildTreeNodeList[i]);
	}

	if (ptNode->iChildNum)
	{
		free(ptNode->pChildTreeNodeList);
	}
	free(ptNode);
}

void FreeTreeNodeRoot(TTreeNode &tRootNode)
{
	for(int i = 0; i < tRootNode.iChildNum; i ++)
	{
		FreeTreeNode(tRootNode.pChildTreeNodeList[i]);
	}

	if (tRootNode.iChildNum)
	{
		free(tRootNode.pChildTreeNodeList);
	}
}

/**
 *@bChangeDependSo  是否变换了依赖的动态链接库。
 */
void DealFile(std::list<std::string> &lstEscFunc, std::list<std::string> &lstDependSo, bool &bChangeDependSo, int argc, char* argv[])
{
	const char *psSrcCppFileName = NULL;	//文件名
	char sSrcCppBaseFileName[1024];		//不带扩展名的文件名。
	std::string sDependSoList;
	std::list<std::string> lstFuncDef;	//函数定义列表。
	std::list<StringPair> lstFuncCall; //函数调用列表。
	std::list<std::string> lstOldDependSoFirstLayer;	//原来依赖的第一层动态链接库
	std::list<std::string> lstNewDependSoFirstLayer;	//新依赖的第一层动态链接库
	for(int i = iFirstFileNamePos; i < argc; i ++)
	{
		psSrcCppFileName = argv[i];
		lstFuncDef.clear();
		lstFuncCall.clear();

		memset(sSrcCppBaseFileName, 0, sizeof(sSrcCppBaseFileName));
		const char *p = strchr(psSrcCppFileName, '.');
		if (p == NULL)
		{
			strcpy(sSrcCppBaseFileName, psSrcCppFileName);
		}
		else
		{
			strncpy(sSrcCppBaseFileName, psSrcCppFileName, p - psSrcCppFileName);
		}
		if (bIsCheckConflictFileName)
		{
			CheckConflictFileName(psSrcCppFileName, sSrcCppBaseFileName);
		}

		int fhSrcCppFile;
#ifdef WIN32
		if ( (fhSrcCppFile = _open( psSrcCppFileName, _O_RDONLY )) == -1)
#else
		if ( (fhSrcCppFile = open( psSrcCppFileName, O_RDONLY )) == -1)
#endif
		{
			throw BaseExcept(1, "打开文件[%s]出错！\n", psSrcCppFileName);
		}

		GetFileConent(fhSrcCppFile, psSrcCppFileName);
#ifdef WIN32
		_close( fhSrcCppFile );
#else
		close( fhSrcCppFile );
#endif

		DealStream(psSrcCppFileContent, lstFuncDef, lstFuncCall, lstEscFunc);
		RefreshCppInfo(lstFuncDef,lstFuncCall, lstOldDependSoFirstLayer, psSrcCppFileName, sSrcCppBaseFileName);
	
		if (bIsPrintDependSo)
		{
			TTreeNode tRootNode;
			memset(&tRootNode, 0, sizeof(TTreeNode));
			printf("Depend ");
			GetDependSo(lstDependSo, lstNewDependSoFirstLayer, psSrcCppFileName, sSrcCppBaseFileName, tRootNode);
			if (bIsTreePrintDependSo)
			{
				PrintTreeNode(tRootNode);
			}
			FreeTreeNodeRoot(tRootNode);
		}
	}
	if (bIsPrintDependSo)
	{
		std::string sSoName;

		for(int i = iFirstFileNamePos; i < argc; i ++)
		{
			psSrcCppFileName = argv[i];

			memset(sSrcCppBaseFileName, 0, sizeof(sSrcCppBaseFileName));
			const char *p = strchr(psSrcCppFileName, '.');
			if (p == NULL)
			{
				strcpy(sSrcCppBaseFileName, psSrcCppFileName);
			}
			else
			{
				strncpy(sSrcCppBaseFileName, psSrcCppFileName, p - psSrcCppFileName);
			}

			sSoName = "lib";
			sSoName.append(sSrcCppBaseFileName);
			sSoName.append(".so");

			std::list<std::string>::iterator iterDependSo;
			for(iterDependSo = lstDependSo.begin(); iterDependSo != lstDependSo.end(); iterDependSo ++)
			{
				if  (iterDependSo->compare(sSoName) == 0)
				{
					std::string tmp=*iterDependSo;
					lstDependSo.remove(tmp);
					break;
				}
			}
		}
		GetDependSoString(lstDependSo, sDependSoList);
		printf("DependSoList:%s\n", sDependSoList.c_str());

		if (tProgType == PT_SO)
		{
			bool bFound= false;
			std::list<std::string>::iterator iterOldDepend, iterNewDepend;
			for(iterNewDepend = lstNewDependSoFirstLayer.begin(); iterNewDepend != lstNewDependSoFirstLayer.end(); iterNewDepend ++)
			{
				bFound = false;
				for(iterOldDepend = lstOldDependSoFirstLayer.begin(); iterOldDepend != lstOldDependSoFirstLayer.end(); iterOldDepend ++)
				{
					if (iterNewDepend->compare(*iterOldDepend) == 0)
					{
						bFound = true;
						break;
					}
				}

				if (!bFound)
				{
					//表示依赖了新的动态链接库
					bChangeDependSo = true;
					break;
				}
			}
		}
	}

}

char* Trim(char *S)
{
	int I = 0, i = 0, L = 0;
	
	if (S == NULL)
	{
		return NULL;
	}
			
	L = (int)(strlen(S) - 1);
	I = 0;
	while ( (I <= L) && (S[I] <= ' ') && (S[I] > 0) )
	{
		I ++;
	}
	if (I > L)
	{
		S[0] = '\0';
	}
	else
	{
		while ( (S[L] <= ' ')  && (S[L] > 0 ) )
		{
			L --;
		}
		strncpy(S, S + I, L + 1);
		S[L + 1 - I] = '\0';
	}
	return S;
}

//读取过滤函数。
void ReadEscFunc(const char* psFileName, std::list<std::string> &lstEscFunc)
{
	FILE *fp = NULL;

	if ((fp = fopen(psFileName, "r")) == NULL)
	{
		throw BaseExcept(1, "打开过滤函数文件[%s]出错！\n", psFileName);
	}
	char sLine[512];
	memset(sLine, 0, sizeof(sLine));
	std::string sEscFunc;
	while(fgets(sLine, 511, fp))
	{
		Trim(sLine);
		sEscFunc = sLine;
		lstEscFunc.push_back(sEscFunc);
	}
	fclose(fp);
}

void GetCurrTime()
{
	time_t tmCurrTime = time(NULL);
	struct tm *timeinfo = localtime(&tmCurrTime);

	char sIntStr[64];
	memset(sIntStr, 0, sizeof(sIntStr));
	sprintf(sIntStr, "%d", timeinfo->tm_year + 1900);
	strcpy(sCurrTime, sIntStr);

	memset(sIntStr, 0, sizeof(sIntStr));
	sprintf(sIntStr, "%02d", timeinfo->tm_mon + 1);
	strcat(sCurrTime, sIntStr);

	memset(sIntStr, 0, sizeof(sIntStr));
	sprintf(sIntStr, "%02d", timeinfo->tm_mday);
	strcat(sCurrTime, sIntStr);

	memset(sIntStr, 0, sizeof(sIntStr));
	sprintf(sIntStr, "%02d", timeinfo->tm_hour);
	strcat(sCurrTime, sIntStr);

	memset(sIntStr, 0, sizeof(sIntStr));
	sprintf(sIntStr, "%02d", timeinfo->tm_min);
	strcat(sCurrTime, sIntStr);

	memset(sIntStr, 0, sizeof(sIntStr));
	sprintf(sIntStr, "%02d", timeinfo->tm_sec);
	strcat(sCurrTime, sIntStr);

	sCurrTime[14] = '\0';
}

/**
 *  得到被依赖的动态链接库列表。
 */
void GetDependedSo(std::list<std::string> &lstDependSo, const char *psSrcCppFileName, const char *psSrcCppBaseFileName,
	TTreeNode &tRootNode)
{
	otl_nocommit_stream otlstream;
	otlstream.set_flush(false);

	char sSoName[100+1], sCppName[100+1],sSoNameOut[100+1], sCppNameOut[100+1];
	char sSqlStmt[1024];

	memset(sSqlStmt, 0, sizeof(sSqlStmt));
	memset(sCppName, 0, sizeof(sCppName));
	memset(sSoName, 0, sizeof(sSoName));
	memset(sSoNameOut, 0, sizeof(sSoNameOut));
	memset(sCppNameOut, 0, sizeof(sCppNameOut));

	strncpy(sCppName, psSrcCppFileName, 100);
	strcpy(sSoName, "lib");
	strcat(sSoName, psSrcCppBaseFileName);
	strcat(sSoName, ".so");

	TTreeNode *pTreeNode;		//节点指针。
	strcpy(tRootNode.sSoName, sSoName);
	std::list<StringNodePair> lstNodeStack1, lstNodeStack2;

	std::list<StringPair> lstDependSoTmp1, lstDependSoTmp2;
	try
	{
		sprintf(sSqlStmt,   "select cpp_name, so_name"
							"  from %s.cp_cpp_dict"
							" where so_name in (select so_name"
							"                     from  %s.cp_cppcall_dict"
							"                    where call_function in (select define_function"
							"                                                from %s.cp_deffunc_rela"
							"                                               where cpp_name = :cpp_name<char[100+1]>"
							"                                                 and so_name = :so_name<char[100+1]>))"
							"   and so_name != :so_name2<char[100+1]>",
							sTableOwner, sTableOwner, sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<sCppName<<sSoName<<sSoName;
		otlstream.flush();

		while (!otlstream.eof())
		{
			otlstream>>sCppNameOut>>sSoNameOut;
			if(strcmp(sSoName, sSoNameOut) == 0)
			{
				continue;
			}
			lstDependSoTmp1.push_back(StringPair(std::string(sCppNameOut), std::string(sSoNameOut)));
			lstDependSo.push_back(std::string(sSoNameOut));

			tRootNode.iChildNum ++;
			tRootNode.pChildTreeNodeList = (TTreeNode**)SafeRealloc(tRootNode.pChildTreeNodeList, sizeof(TTreeNode*) * tRootNode.iChildNum);
			tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1] = (TTreeNode*)malloc(sizeof(TTreeNode));
			memset(tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1], 0, sizeof(TTreeNode));
			strcpy(tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1]->sSoName, sSoNameOut);
			tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1]->iChildNum = 0;
			tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1]->pChildTreeNodeList = NULL;
			lstNodeStack1.push_back(StringNodePair(std::string(sSoNameOut), tRootNode.pChildTreeNodeList[tRootNode.iChildNum - 1]));
		}
		otlstream.close();

		std::list<StringPair>::iterator iterDependSo1, iterDependSo2;
		std::list<StringNodePair>::iterator iterNodeStack1, iterNodeStack2;
		while(1)
		{
			for(iterDependSo1 = lstDependSoTmp1.begin(); iterDependSo1 != lstDependSoTmp1.end(); iterDependSo1 ++)
			{
				otlstream.open(1, sSqlStmt, *db);
				otlstream<<iterDependSo1->first.c_str()<<iterDependSo1->second.c_str()<<iterDependSo1->second.c_str();
				otlstream.flush();

				pTreeNode = NULL;
				for(iterNodeStack1 = lstNodeStack1.begin(); iterNodeStack1 != lstNodeStack1.end(); iterNodeStack1 ++)
				{
					if (iterNodeStack1->first.compare(iterDependSo1->second) == 0)
					{
						pTreeNode = iterNodeStack1->second;
						break;
					}
				}
				while (!otlstream.eof())
				{
					otlstream>>sCppNameOut>>sSoNameOut;
					if(strcmp(sSoName, sSoNameOut) == 0)
					{
						continue;
					}
					lstDependSoTmp2.push_back(StringPair(std::string(sCppNameOut), std::string(sSoNameOut)));

					if (pTreeNode)
					{
						pTreeNode->iChildNum ++;
						pTreeNode->pChildTreeNodeList = (TTreeNode**)SafeRealloc(pTreeNode->pChildTreeNodeList, sizeof(TTreeNode*) * pTreeNode->iChildNum);
						pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1] = (TTreeNode*)malloc(sizeof(TTreeNode));
						memset(pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1], 0, sizeof(TTreeNode));
						strcpy(pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1]->sSoName, sSoNameOut);
						pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1]->iChildNum = 0;
						pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1]->pChildTreeNodeList = NULL;
						lstNodeStack2.push_back(StringNodePair(std::string(sSoNameOut), pTreeNode->pChildTreeNodeList[pTreeNode->iChildNum - 1]));
					}
				}
				otlstream.close();
			}

			if (lstDependSoTmp2.empty())
			{
				break;
			}
			else
			{
				lstDependSoTmp1.clear();
				bool bFound = false;
				for(iterDependSo2 = lstDependSoTmp2.begin(); iterDependSo2 != lstDependSoTmp2.end(); iterDependSo2 ++)
				{
					bFound = false;
					std::list<std::string>::iterator iterDependSo;
					for(iterDependSo = lstDependSo.begin(); iterDependSo != lstDependSo.end(); iterDependSo ++)
					{
						if (iterDependSo2->second.compare(*iterDependSo) == 0)
						{
							bFound = true;
						}
					}
					if (!bFound)
					{
						lstDependSo.push_back(std::string(iterDependSo2->second));
						lstDependSoTmp1.push_back(StringPair(iterDependSo2->first, iterDependSo2->second));

					}
				}
				lstDependSoTmp2.clear();

				lstNodeStack1.clear();
				for(iterNodeStack2 = lstNodeStack2.begin(); iterNodeStack2 != lstNodeStack2.end(); iterNodeStack2 ++)
				{
					lstNodeStack1.push_back(StringNodePair(iterNodeStack2->first, iterNodeStack2->second));
				}
				lstNodeStack2.clear();
			}
		}
	}
	catch (otl_exception &otlErr)
	{
		throw BaseExcept(1, "操作数据库出错，错误代码：%d\n错误信息：%s", otlErr.code, otlErr.msg);
	}
}

/**
 *
 * 打印被依赖的动态链接库
 */
void PrintDependedSo(std::list<std::string> &lstDependSo, int argc, char* argv[])
{
	const char *psSrcCppFileName = NULL;	//文件名
	char sSrcCppBaseFileName[1024];		//不带扩展名的文件名。
	for(int i = iFirstFileNamePos; i < argc; i ++)
	{
		psSrcCppFileName = argv[i];

		memset(sSrcCppBaseFileName, 0, sizeof(sSrcCppBaseFileName));
		const char *p = strchr(psSrcCppFileName, '.');
		if (p == NULL)
		{
			strcpy(sSrcCppBaseFileName, psSrcCppFileName);
		}
		else
		{
			strncpy(sSrcCppBaseFileName, psSrcCppFileName, p - psSrcCppFileName);
		}

		TTreeNode tRootNode;
		memset(&tRootNode, 0, sizeof(TTreeNode));
		printf("Depended ");
		GetDependedSo(lstDependSo, psSrcCppFileName, sSrcCppBaseFileName, tRootNode);
		PrintTreeNode(tRootNode);
		FreeTreeNodeRoot(tRootNode);
	}
}

/**
 *
 * 刷新中间件服务依赖的动态链接库
 */
void RefreshServiceDependSo(std::list<std::string> &lstDependSo, int argc, char* argv[])
{
	otl_nocommit_stream otlstream;
	otlstream.set_flush(false);
	char sSqlStmt[1024];

	memset(sSqlStmt, 0, sizeof(sSqlStmt));

	const char *psSrcCppFileName = NULL;	//文件名
	char sSrcCppBaseFileName[1024];		//不带扩展名的文件名。
	for(int i = iFirstFileNamePos; i < argc; i ++)
	{
		psSrcCppFileName = argv[i];

		memset(sSrcCppBaseFileName, 0, sizeof(sSrcCppBaseFileName));
		const char *p = strchr(psSrcCppFileName, '.');
		if (p == NULL)
		{
			strcpy(sSrcCppBaseFileName, psSrcCppFileName);
		}
		else
		{
			strncpy(sSrcCppBaseFileName, psSrcCppFileName, p - psSrcCppFileName);
		}

		try
		{
			//删除表cp_execso_rela
			sprintf(sSqlStmt, "delete from %s.cp_execso_rela where exec_name=:exec_name<char[100+1]> and data_source = :data_source<char[20+1]>", sTableOwner);
			otlstream.open(1, sSqlStmt, *db);
			otlstream<<psSrcCppFileName<<CPPCOMPILE_DATA_SOURCE;
			otlstream.flush();
			otlstream.close();
		
			sprintf(sSqlStmt,"insert into %s.cp_execso_rela"
							  "("
							  " exec_name, so_name, update_time, data_source"
							  ")"
							  "values"
							  "("
							  " :exec_name<char[100+1]>, :cpp_base_name<char[100+1]>, to_date(:update_time<char[14+1]>,'YYYYMMDDHH24MISS'), :data_source<char[20+1]>"
							  ")", sTableOwner);
			otlstream.open(lstDependSo.size(), sSqlStmt, *db);
			std::list<std::string>::iterator iterDependSo;
			for(iterDependSo = lstDependSo.begin(); iterDependSo != lstDependSo.end(); iterDependSo ++)
			{
				otlstream<<psSrcCppFileName;
				otlstream<< (*iterDependSo).c_str();
				otlstream<<sCurrTime;
				otlstream<<CPPCOMPILE_DATA_SOURCE;
			}
			otlstream.flush();
			otlstream.close();
		}
		catch (otl_exception &otlErr)
		{
			throw BaseExcept(1, "操作数据库出错，错误代码：%d\n错误信息：%s", otlErr.code, otlErr.msg);
		}
	}
}

int main(int argc, char* argv[])
{
	int iRet = 0;
	if ((iRet = AnalyseMainOption(argc, argv)) != 0)
	{
		return iRet;
	}
	GetCurrTime();
	
	otl_connect _db;
	db = &_db;
	try
	{
		otl_connect::otl_initialize();
		db->rlogon(psDbLoginString);
	}
	catch(otl_exception& otlErr)
	{
		fprintf(stderr, "错误代码：%d\n错误信息：%s", otlErr.code, otlErr.msg);
		return 2;return otlErr.code;
	}
	
	std::list<std::string> lstEscFunc;	//过滤的函数列表。
	std::list<std::string> lstDependSo;
	bool bChangeDependSo = false;
	try
	{
		if (bIsTreePrintDependedSo)
		{
			//以树状关系打印被依赖库
			PrintDependedSo(lstDependSo, argc, argv);
		}
		else
		{
			ReadEscFunc(psEscFuncFileName, lstEscFunc);
			DealFile(lstEscFunc, lstDependSo, bChangeDependSo, argc, argv);
		}
	}
	catch(BaseExcept &e)
	{
		fprintf(stderr, "错误代码：%d\n错误信息：%s", e.m_iErrNo, e.m_psErrMsg);
		db->rollback();
		db->logoff();
		return 2;
	}

	if (psSrcCppFileContent)
	{
		free(psSrcCppFileContent);
	}

	if (!bIsTreePrintDependedSo)
	{
		if (tProgType == PT_SO)
		{
			db->commit();
			if (bChangeDependSo)
			{
				printf("ChangedDependSo:YES\n");
			}
			else
			{
				printf("ChangedDependSo:NO\n");
			}
		}
		else
		{
			db->rollback();
			if (tProgType == PT_SERVICE)
			{
				try
				{
					RefreshServiceDependSo(lstDependSo, argc, argv);
				}
				catch(BaseExcept &e)
				{
					fprintf(stderr, "错误代码：%d\n错误信息：%s", e.m_iErrNo, e.m_psErrMsg);
					db->rollback();
					db->logoff();
					return 2;
				}
			}
		}
	}
	db->logoff();

	printf("Success!\n");
	return 0;
}
