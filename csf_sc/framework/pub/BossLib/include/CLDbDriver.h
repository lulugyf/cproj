#ifndef __CLDbDriver_h__
#define __CLDbDriver_h__

#define MAXLABELLEN	12
#define MAXLOGIN        100

#define MAX_COL_LENGTH 60

//���ݿ����ӽṹ��
typedef struct tagConnect
{
	char connectName[MAXLABELLEN+1];
	char dbSrv[MAXLABELLEN+1];
	char dbName[MAXLABELLEN+1];
	char userName[MAXLABELLEN + 1];
	char userPwd[MAXENDELEN+1];
	char baklbl[MAXENDELEN+1];
} TConnect;

typedef struct tagComShm
{
	unsigned int connectNum;
	TConnect connects[MAXLOGIN];
}TComShm;


//�������ݿ����
typedef enum tagDbConnFlag
{
	DB_CONN_UNUSE_LABEL = 0,	//��ʹ�ñ�ǩ�����ӡ�
	DB_CONN_USE_LABEL = 1		//ʹ�ñ�ǩ�����ӡ�
}EDbConnFlag;

//�Ͽ����ݿ����
typedef enum tagDbDisConnFlag
{
	DB_DISCONN_COMMIT = 1,		//�ڶϿ�����֮ǰ���ύ���ݿ������
	DB_DISCONN_ROLLBACK = 2		//�ڶϿ�����֮ǰ���ع����ݿ������
}EDbDisConnFlag;

//��ִ��ExecuteSql()����ʱ�������ѯ�����������α��ȡһ��������ɺ�ᴥ�����¼���
//����ֵ���������ֵ��Ϊ�㣬���жϵ�ǰ�α��ִ�У������ش˺����Ĵ�����롣
//typedef ETYPE (*OnFetchCursor)();

class CLConnection;
#define CS_DATA_SOURCE			"Data Source"
#define CS_USER_ID				"User Id"
#define CS_PASSWORD				"Password"

class CLCommand;
class CLConnection : public CLDriver
{
public:
	CLConnection();
	~CLConnection();

	//�������Ͷ������
	virtual TDriverType GetDriverType() const;
public:
	/*
	 Data Source:����Դ
	 User Id:�û���
	 Password:����
	 */
	string ConnectString;

	/*
	 * bIsDefaultConn���Ƿ���Ĭ�����ݿ�����
	 * psConnName����������û�д��ݾ���Ϊ�ա�
	 */
	ETYPE Open(ub4 connDbType, bool bIsDefaultConn, const char *psConnName) throw();

	//ͨ�����ݿ��ǩ�������ݿ⣬������������ȫ��Ĭ������Ϊ�����ӡ�
	inline ETYPE Open(const char* dbLabel) throw()
	{
		ETYPE iRet;
		if ( (iRet = GetDbP(dbLabel)) != 0)
		{
			return iRet;
		}
		return Open(DB_CONN_TYPE_PROC, true,NULL);
	}
	
	//ͨ�����ݿ��ǩ�������ݿ�
	inline ETYPE Open(const char* dbLabel,ub4 connDbType, bool bIsDefaultConn, const char *psConnName) throw()
	{
		ETYPE iRet;
		if ( (iRet = GetDbP(dbLabel)) != 0)
		{
			return iRet;
		}
		return Open(connDbType, bIsDefaultConn, psConnName);
	}

	void Close() throw();

	//�ύ����
	int Commit() throw();

	//�ع�����
	int Rollback() throw();

	//�Ƿ��¼״̬
	int IsLoggedOn() throw();

	OCIEnv *GetEnvhp() throw()
	{
		return m_envhp;
	}
	OCIServer *GetSrvhp() throw()
	{
		return m_srvhp;
	}
	OCISvcCtx *GetSvchp() throw()
	{
		return m_svchp;
	}
	OCISession *GetAuthp() throw()
	{
		return m_authp;
	}
	OCIError *GetErrhp() throw()
	{
		return m_errhp;
	}
	
	ub4 GetOciMode() throw()
	{
		return m_ociMode;
	}

	//����CLConnection���ڲ����ӡ�CLCommand *����
	CLCommand *GetCommand()
	{
		return m_Command;
	}

	//�õ������ӵ����ơ�
	const char *GetConnName()
	{
		return m_sConnName;
	}
	
	//�õ����ӵ����ݿ����͡�
	ub4 GetConnDbType()
	{
		return m_connDbType;
	}

	//�жϴ������Ƿ���Ĭ������
	bool IsDefaultConn()
	{
		return m_bIsDefaultConn;
	}

	//���ӵ����ݿ�����
	//OCIģʽ
	static const ub4 DB_CONN_TYPE_OCI	= 0;

	//PRO*Cģʽ
	static const ub4 DB_CONN_TYPE_PROC	= 1;

	//PRO*Cģʽ��ʹ�����е�pro*c����
	static const ub4 DB_CONN_TYPE_USE_EXISTS_PROC	= 2;
private:
	/*
		����һ�������࣬
	 */
	ETYPE CreateCommond(bool bIsDefaultConn) throw();

	/*
		ɾ��һ�������࣬
	 */
	void DeleteCommond() throw();

	ETYPE InitHandles();
	void FreeHandles();

	//��ʼ���û����
	ETYPE Initialize();

	// Logon to the database using given username, password & credentials
	ETYPE LogOn(const char *uid, const char *pwd, const char* tnsName, ub4 credt);

	ETYPE AttachServer(const char *tnsName);
	void LogOutDetachServer();
	void Destruction();

	//�õ����ݿ��ǩ�����ݣ����ݿ������û����Ϳ��
	ETYPE GetDbP(const char *connectName);
	
	OCIEnv *m_envhp;
	OCIServer *m_srvhp;
	OCISvcCtx *m_svchp;
	OCISession *m_authp;
	OCIError *m_errhp;

	int m_loggedOn;
	ub4 m_ociMode;
private:
	void GetLogInfo() throw();
	string m_sDataSource;
	string m_sUserId;
	string m_sPasswd;

	//���ӵ����ݿ�����
	ub4 m_connDbType;

	//�Ƿ���Ĭ������
	bool m_bIsDefaultConn;

	CLCommand *m_Command;

	//��������һ����CLConnection���ӵ�Ψһ��ʶ�����������������ڣ�֪��CLConnection����һ�����ӣ�
	//��ʹ�����ӳرȽ����á�
	char m_sConnName[255+1];
};

//ȫ�����ݿ�������ָ��
extern CLCommand *g_Command;

#endif //__CLDBDriver_h__

