#ifndef __CLFile_h__
#define __CLFile_h__

#define CFGDIR			"/cfg"

//BOSS��̬��
#define BOSS_SYNLIB_DIR	"BOSS_SYNLIB_DIR"


#define FN_LIBSTR		"/"
#define WORKDIR			"WORKDIR"

class CLFile :public CLDriver
{
public:
	CLFile()
	{
		
	}
	//�������Ͷ������
	virtual TDriverType GetDriverType() const;
	
	//�õ���������������
	static ETYPE GetEnvContext(const char *envLabel, char** envContext);

	//�����ļ���ȡ��$WORKDIR/cfg�µ��ļ�ȫ·��
	static ETYPE GetCfgDir(const char *shortFile, char *fullFile);

	//�����ļ���ȡ��$WORKDIR/public/synlib�µ��ļ�ȫ·��
	static ETYPE GetSynlibDir(const char *shortFile, char *fullFile);
	
private:
};

#endif //__CLFile_h__
