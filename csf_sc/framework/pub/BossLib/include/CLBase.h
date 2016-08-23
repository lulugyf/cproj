#ifndef __CLBase_h__
#define __CLBase_h__

#define DEFAULT_COMPANY_NAME	"sitech"

#define DEFAULT_MIN_VERSION		0
#define DEFAULT_MAX_VERSION		1
#define DEFAULT_VERSION		"1.0"


class CLBase
{
public:
	//�õ���˾����
	virtual const char* GetCompanyName()
	{
		return DEFAULT_COMPANY_NAME;
	}

	//�õ�С�汾��
	virtual int GetMinVersion()
	{
		return DEFAULT_MIN_VERSION;
	}

	//�õ���汾��
	virtual int GetMaxVersion()
	{
		return DEFAULT_MAX_VERSION;
	}

	//�õ��汾�Ŵ�
	virtual const char *GetVersion()
	{
		return DEFAULT_VERSION;
	}
};

#endif/*__CLBase_h__*/
