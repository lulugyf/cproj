#include "llayerStruct.h"

TDriverType CLFile::GetDriverType() const
{
	return DRIVER_FILE;
}

//�õ���������������
ETYPE CLFile::GetEnvContext(const char *envLabel, char** envContext)
{
	if ((*envContext = getenv(envLabel)) == NULL)
	{
		return CLError::E_FILE_ENV;
	}
	return 0;
}

//�����ļ���ȡ��$WORKDIR/cfg�µ��ļ�ȫ·��
ETYPE CLFile::GetCfgDir(const char *shortFile, char *fullFile)
{
	char* envContext=NULL;
	ETYPE iErrNo;
	
	if ((iErrNo=GetEnvContext(WORKDIR, &envContext)) != 0)
	{
		return iErrNo;
	}
	
	strcpy(fullFile,envContext);
	strcat(fullFile,CFGDIR);
	strcat(fullFile,FN_LIBSTR);
	strcat(fullFile,shortFile);
	
	return 0;
}

//�����ļ���ȡ��$WORKDIR/public/synlib�µ��ļ�ȫ·��
ETYPE CLFile::GetSynlibDir(const char *shortFile, char *fullFile)
{
	char* envContext=NULL;
	ETYPE iErrNo;
	
	if ((iErrNo=GetEnvContext(BOSS_SYNLIB_DIR, &envContext)) != 0)
	{
		return iErrNo;
	}
	
	strcpy(fullFile,envContext);
	strcat(fullFile,FN_LIBSTR);
	strcat(fullFile,shortFile);
	
	return 0;
}
