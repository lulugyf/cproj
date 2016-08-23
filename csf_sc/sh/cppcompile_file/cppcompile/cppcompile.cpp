#include "cppcompile.h"

static int iFirstFileNamePos = -1;				//��һ���ļ���λ�á�
static const char *psSrcCppPathName = NULL;	//Դ�ļ����ڵ�·��

static const char *psEscFuncFileName = NULL;	//���˺������ļ���
static char *psSrcCppFileContent = NULL;	//�ļ����ݡ�
static const char *psDbLoginString = NULL;	//���ݿ��¼������ʽ��user/password@db����
static otl_connect *db = NULL;
char sCurrTime[14+1];					//��ǰʱ�䣬��ʽ��YYYYMMDDHH24MISS����

static TProgType tProgType=PT_UNKOWN;			//�������͡�
static bool bIsPrintDependSo=false;			//�Ƿ��ӡ�����⡣

static bool bIsCheckConflictFileName=true;		//�Ƿ����ͻ���ļ�����
static bool bIsCheckConflictFunction=true;		//�Ƿ����ͻ�ĺ�����

static char sTableOwner[256];				//���ݿ�������

static bool bIsTreePrintDependSo = false;				//����״��ϵ��ӡ�����⣬�൱�ڴ��ϲ����ײ��ѯ������ϵ��
static bool bIsTreePrintDependedSo = false;				//����״��ϵ��ӡ�������⣬�൱�ڴӵײ����ϲ��ѯ������ϵ��

static bool bIsReserveCPPFunc = true;				//�Ƿ���C++������Ĭ�ϱ�����

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
		"	����һ���ļ���\n\n"
		"Options:\n"
		"    -notchkfile   �Ƿ񲻼���ͻ���ļ��������ϴ�ѡ���򲻼��.\n"
		"    -notchkfunc   �Ƿ񲻼���ͻ�ĺ����������ϴ�ѡ���򲻼��.\n"
		"    -reservecppf=yes  �Ƿ���C++������Ĭ�ϱ�����ȡֵ��Χyes��no.\n"
		"    -progtype=so   ��������ͣ�ȡֵ��Χexec��so��service.\n"
		"    -pdepso=no   �Ƿ��ӡ�����⣬ȡֵ��Χyes��no.\n"
		"    -ptreedepso     ����״��ϵ��ӡ�����⣬�൱�ڴ��ϲ����ײ��ѯ������ϵ��\n"
		"    -ptreedepedso     ����״��ϵ��ӡ�������⣬�൱�ڴӵײ����ϲ��ѯ������ϵ��\n"
		"    -path=xxx   Դ�ļ����ڵ�·��.\n"
		"    -esc=FileName   ���˺������ļ�����Ĭ�ϡ�EscFuncFile.txt��.\n"
		"    -dbstr=psDbLoginString   ���ݿ��¼���������ʽ��user/password@db��.\n"
		"    -towner=xxx   ���ݿ�������.\n"
		"    -?          ��ʾ����.\n\n"
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
 *     �滻ת���ַ���Ϊָ���ַ���
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
 *     ���Ԥ�����У���#include, #define���ԡ�#����ͷ����䡣
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


///ǰһ���ַ�
inline char PreChar(const char* srcStream, int iPos)
{
	if (iPos != 0)
	{
		return srcStream[iPos - 1];
	}
	else
	{
		return 0;	//���ؿ��ַ���
	}
}

///����ǰһ���ַ�
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


///��һ���ַ�
inline char NextChar(const char* srcStream, int iPos, int inLen)
{
	if (iPos < inLen - 1)
	{
		return srcStream[iPos + 1];
	}
	else
	{
		return 0;	//���ؿ��ַ���
	}
}

///��һ���Ϸ��ı����ַ���
inline bool IsLiteralChar(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
	{
		return true;
	}
	return false;
}

///�õ�ǰһ������
///iPos������λ�á�
///�ɹ����ص��ʵ�ǰһ��λ�á�
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
 *     ���ע�ͺ������е����ݡ�
 */
void ClearQuotationConentAndComment(char* srcStream, int c)
{
	int i;
	int inLen;
	bool bInClearMark=false;	//�Ƿ��������ǿ��
	typedef enum tagClearMark
	{
		CLEAR_MARK_NONE = 0,				//����������
		CLEAR_MARK_DOUBLE_QUOTATION = 1,	//˫����
		CLEAR_MARK_SINGLE_QUOTATION = 2,	//������
		CLEAR_MARK_LINE_COMMENT = 3,		//�б�ע��//��
		CLEAR_MARK_BLOCK_COMMENT = 4		//�鱸ע ��/**/��
	}TClearMark;

	TClearMark enumClearMark = CLEAR_MARK_NONE;

	if (srcStream == NULL) return;
	inLen=(int)strlen(srcStream);
	if (inLen <= 2 )
	{
		return;
	}
	
	//���˫���ź͵������е����ݡ�
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
				//�������򣬲�������
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
		throw BaseExcept(1, "�ļ�[%s]����Ϊ�գ�\n", psSrcCppFileName);
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
			throw BaseExcept(1, "���� %s û����������", sFuncCallName.c_str());
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
				throw BaseExcept(1, "�õ��м���ص����������Ƴ���");
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
			throw BaseExcept(1, "���� %s û����������", sFuncCallName.c_str());
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
				throw BaseExcept(1, "�õ�˫��ص����������Ƴ���");
			}
			std::string sCallBackFunctionName;
			sCallBackFunctionName = sWord; 
			AddCallFunc(sCallBackFunctionName, sFuncDefName, lstFuncCall, lstEscFunc);
		}
	}
}


/**
 *  �õ������Ķ�̬���ӿ��ַ�����
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
 * �������嶨��ԭ�򣬲ο�����1�͹������
 *     ��1��type func (type value, ...) {}
 *     ��2������ ��type func (type value, ...) throw (...){}�������쳣����Ķ��塣
 *     ��3������ ��type func (type value, ...) const{}�����ֳ��������Ķ��塣
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
			if (iFuncDeep == 0)	//��������
			{
				if (srcStream[i] == '{')
				{
					iFuncDeep ++;
				
					if ( (iPos = GetPreWord(srcStream, i - 1, sWord)) < 0)
					{
						throw BaseExcept(1, "��������ʧ��1");
					}
					
					if (strcmp(sWord, ")") == 0)
					{
						p = FindPreChar(srcStream, iPos, '(');
						if (!p)
						{
							throw BaseExcept(1, "��������ʧ��2");
						}

						if ( (iPos = GetPreWord(srcStream,  p - srcStream - 1, sWord)) < 0)
						{
							throw BaseExcept(1, "��������ʧ��3");
						}

						if (strcmp(sWord, "throw") == 0)	//��������2.
						{
							//�쳣��Ϣ��
							p = FindPreChar(srcStream, iPos, '(');
							if (!p)
							{
								throw BaseExcept(1, "��������ʧ��4");
							}

							if ( (iPos = GetPreWord(srcStream, p - srcStream - 1, sWord)) < 0)
							{
								throw BaseExcept(1, "��������ʧ��5");
							}
						}

						bIsFunc = true;
						//sWord�Ǻ�����������֡�
						sFuncDefName = sWord;
						AddFuncDef(lstFuncDef, sFuncDefName);
					}
					else
					{
						if ( (iPos = GetPreWord(srcStream, i - 1, sWord)) < 0)
						{
							throw BaseExcept(1, "��������ʧ��6");
						}

						if (strcmp(sWord, "const") == 0)  //��������3.
						{
							p = FindPreChar(srcStream, iPos, '(');
							if (!p)
							{
								throw BaseExcept(1, "��������ʧ��7");
							}

							if ( (iPos = GetPreWord(srcStream, p - srcStream - 1, sWord)) < 0)
							{
								throw BaseExcept(1, "��������ʧ��8");
							}

							bIsFunc = true;
							//sWord�Ǻ������塣
							sFuncDefName = sWord;
							AddFuncDef(lstFuncDef, sFuncDefName);
						}
						else
						{
							//���Ǻ�����
							bIsFunc = false;
						}
					}
				}

				if (srcStream[i] == '}')
				{
					iFuncDeep --;
					if (iFuncDeep == 0)
					{
						//���Ǻ�����
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
						//���Ǻ�����
						bIsFunc = false;
					}
				}
				else if (bIsFunc)
				{
					//�������������Ϣ��
					if (srcStream[i] == '(')	//�ж��Ƿ�����˺�����
					{
						if ( (iPos = GetPreWord(srcStream, i - 1, sWord)) < 0)
						{
							throw BaseExcept(1, "��������ʧ��9");
						}

						if (IsLiteralChar(sWord[0]))
						{
							sFuncCallName = sWord;

							if ( (iPos = GetPreWord(srcStream, iPos, sWord)) < 0)
							{
								throw BaseExcept(1, "��������ʧ��10");
							}

							if (sWord[0] == '.')
							{
								if (bIsReserveCPPFunc)
								{
									AddCallFunc(sFuncCallName, sFuncDefName, lstFuncCall, lstEscFunc);
									//�м�����񣬻���Ҫ���һص�������
									if ((tProgType == PT_SO) || (tProgType == PT_SERVICE))
									{
										AddMiddwareServiceCallBackFunc(srcStream, i, lstFuncDef, lstFuncCall,
											lstEscFunc, sFuncDefName, sFuncCallName);
									}
								}
								else
								{
									//���˳�Ա������
								}
							}
							else if (sWord[0] == '>')
							{
								if (srcStream[iPos] == '-')
								{
									if (bIsReserveCPPFunc)
									{
										AddCallFunc(sFuncCallName, sFuncDefName, lstFuncCall, lstEscFunc);
										//�м�����񣬻���Ҫ���һص�������
										if ((tProgType == PT_SO) || (tProgType == PT_SERVICE))
										{
											AddMiddwareServiceCallBackFunc(srcStream, i, lstFuncDef, lstFuncCall,
												lstEscFunc, sFuncDefName, sFuncCallName);
										}
									}
									else
									{
										//���˳�Ա������
									}
								}
								else
								{
									AddCallFunc(sFuncCallName, sFuncDefName, lstFuncCall, lstEscFunc);
									//�м�����񣬻���Ҫ���һص�������
									if ((tProgType == PT_SO) || (tProgType == PT_SERVICE))
									{
										AddMiddwareServiceCallBackFunc(srcStream, i, lstFuncDef, lstFuncCall,
											lstEscFunc, sFuncDefName, sFuncCallName);
									}
								}
							}
							else if (IsLiteralChar(sWord[0]))
							{
								//��C++�Ĺ��캯�������˵���
								if (strcmp(sWord,  "return") == 0)
								{
									AddCallFunc(sFuncCallName, sFuncDefName, lstFuncCall, lstEscFunc);
									//�м�����񣬻���Ҫ���һص�������
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
								//�м�����񣬻���Ҫ���һص�������
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
 *  �������ݿ��е���Ϣ��
 *@lstOldDependSoFirstLayer ԭ�������ĵ�һ�㶯̬���ӿ�
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

		//ɾ����cp_cppcall_dict
		sprintf(sSqlStmt, "delete from %s.cp_cppcall_dict where cpp_name=:cpp_name<char[100+1]> and data_source = :data_source<char[20+1]>", sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<psSrcCppFileName<<CPPCOMPILE_DATA_SOURCE;
		otlstream.flush();
		otlstream.close();

		//ɾ����cp_deffunc_rela
		sprintf(sSqlStmt, "delete from  %s.cp_deffunc_rela where cpp_name=:cpp_name<char[100+1]> and data_source = :data_source<char[20+1]>", sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<psSrcCppFileName<<CPPCOMPILE_DATA_SOURCE;
		otlstream.flush();
		otlstream.close();

		//ɾ����cp_cpp_dict
		sprintf(sSqlStmt, "delete from  %s.cp_cpp_dict where cpp_name=:cpp_name<char[100+1]> and data_source = :data_source<char[20+1]>", sTableOwner);
		otlstream.open(1, sSqlStmt, *db);
		otlstream<<psSrcCppFileName<<CPPCOMPILE_DATA_SOURCE;
		otlstream.flush();
		otlstream.close();

		//�����cp_cpp_dict
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

		//�����cp_deffunc_rela
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
				throw BaseExcept(1, "�ļ�%s�еĺ���%s���ļ�%s���Ѿ������!", psSrcCppFileName, sConflictFunction, sConflictFile);
			}
			otlstream.flush();
			otlstream.close();

		}

		//�����cp_cppcall_dict
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
		throw BaseExcept(1, "�������ݿ����������룺%d\n������Ϣ��%s", otlErr.code, otlErr.msg);
	}
}

/**
 *  �õ������Ķ�̬���ӿ��б�
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

	TTreeNode *pTreeNode;		//�ڵ�ָ�롣
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
		throw BaseExcept(1, "�������ݿ����������룺%d\n������Ϣ��%s", otlErr.code, otlErr.msg);
	}
}

/**
 *  �ж��ļ��Ƿ��ͻ����ͬĿ¼������ͬ���ļ����ơ�
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
				throw BaseExcept(1, "Ŀ¼%s���Ѿ������ļ�%s", sCppPath, sCppName);
			}
		}
		otlstream.close();
	}
	catch (otl_exception &otlErr)
	{
		throw BaseExcept(1, "�������ݿ����������룺%d\n������Ϣ��%s", otlErr.code, otlErr.msg);
	}
}

/**
 *  �õ������Ķ�̬���ӿ��ַ�����
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
				throw BaseExcept(1, "����Ķ�̬���ӿ����֣�%s", iterDependSo->c_str());
			}
		}
		else
		{
			throw BaseExcept(1, "����Ķ�̬���ӿ����֣�%s", iterDependSo->c_str());
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
 *@bChangeDependSo  �Ƿ�任�������Ķ�̬���ӿ⡣
 */
void DealFile(std::list<std::string> &lstEscFunc, std::list<std::string> &lstDependSo, bool &bChangeDependSo, int argc, char* argv[])
{
	const char *psSrcCppFileName = NULL;	//�ļ���
	char sSrcCppBaseFileName[1024];		//������չ�����ļ�����
	std::string sDependSoList;
	std::list<std::string> lstFuncDef;	//���������б�
	std::list<StringPair> lstFuncCall; //���������б�
	std::list<std::string> lstOldDependSoFirstLayer;	//ԭ�������ĵ�һ�㶯̬���ӿ�
	std::list<std::string> lstNewDependSoFirstLayer;	//�������ĵ�һ�㶯̬���ӿ�
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
			throw BaseExcept(1, "���ļ�[%s]����\n", psSrcCppFileName);
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
					//��ʾ�������µĶ�̬���ӿ�
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

//��ȡ���˺�����
void ReadEscFunc(const char* psFileName, std::list<std::string> &lstEscFunc)
{
	FILE *fp = NULL;

	if ((fp = fopen(psFileName, "r")) == NULL)
	{
		throw BaseExcept(1, "�򿪹��˺����ļ�[%s]����\n", psFileName);
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
 *  �õ��������Ķ�̬���ӿ��б�
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

	TTreeNode *pTreeNode;		//�ڵ�ָ�롣
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
		throw BaseExcept(1, "�������ݿ����������룺%d\n������Ϣ��%s", otlErr.code, otlErr.msg);
	}
}

/**
 *
 * ��ӡ�������Ķ�̬���ӿ�
 */
void PrintDependedSo(std::list<std::string> &lstDependSo, int argc, char* argv[])
{
	const char *psSrcCppFileName = NULL;	//�ļ���
	char sSrcCppBaseFileName[1024];		//������չ�����ļ�����
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
 * ˢ���м�����������Ķ�̬���ӿ�
 */
void RefreshServiceDependSo(std::list<std::string> &lstDependSo, int argc, char* argv[])
{
	otl_nocommit_stream otlstream;
	otlstream.set_flush(false);
	char sSqlStmt[1024];

	memset(sSqlStmt, 0, sizeof(sSqlStmt));

	const char *psSrcCppFileName = NULL;	//�ļ���
	char sSrcCppBaseFileName[1024];		//������չ�����ļ�����
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
			//ɾ����cp_execso_rela
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
			throw BaseExcept(1, "�������ݿ����������룺%d\n������Ϣ��%s", otlErr.code, otlErr.msg);
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
		fprintf(stderr, "������룺%d\n������Ϣ��%s", otlErr.code, otlErr.msg);
		return 2;return otlErr.code;
	}
	
	std::list<std::string> lstEscFunc;	//���˵ĺ����б�
	std::list<std::string> lstDependSo;
	bool bChangeDependSo = false;
	try
	{
		if (bIsTreePrintDependedSo)
		{
			//����״��ϵ��ӡ��������
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
		fprintf(stderr, "������룺%d\n������Ϣ��%s", e.m_iErrNo, e.m_psErrMsg);
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
					fprintf(stderr, "������룺%d\n������Ϣ��%s", e.m_iErrNo, e.m_psErrMsg);
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
