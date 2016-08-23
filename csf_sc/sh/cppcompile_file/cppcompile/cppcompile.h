#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include <ctype.h>
#include <string>
#include <list>

#ifdef WIN32
#include <io.h>
#include <time.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#define OTL_ORA11G // Compile OTL 4/OCI8
#include "otlv4.h"

typedef std::pair <std::string, std::string> StringPair;

#define CPPCOMPILE_DATA_SOURCE "cppcompile";

class BaseExcept
{
public:
	BaseExcept(int iErrNo, const char* psErrMsg, ...)
		: m_iErrNo(iErrNo)
	{
		va_list args;

		memset(m_psErrMsg, 0, sizeof(m_psErrMsg));


		va_start(args, psErrMsg);
		(void) vsnprintf (m_psErrMsg, 1023, psErrMsg, args);
		va_end(args);
	}

private:
	BaseExcept()
	{
		m_iErrNo = 0;
		memset(m_psErrMsg, 0, sizeof(m_psErrMsg));
	}
public:
	int m_iErrNo;
	char m_psErrMsg[1024];
};

typedef enum enumProgType
{
	PT_UNKOWN = 0,		//����ʶ��
	PT_EXEC = 1,		//��ִ�г���
	PT_SO = 2,			//��̬���ӿ⡣
	PT_SERVICE = 3		//�м������
} TProgType;

typedef struct tagTreeNode
{
	char sSoName[100+1];	//��̬������ơ�
	int iChildNum;			//�ӽڵ�����
	struct tagTreeNode **pChildTreeNodeList;	//�ӽڵ��б�
} TTreeNode;

typedef std::pair <std::string, TTreeNode*> StringNodePair;

inline void* SafeRealloc(void*ptr, size_t size)
{
	if (ptr)
	{
		return realloc(ptr, size);
	}
	else
	{
		return malloc(size);
	}
}


