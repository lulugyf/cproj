#ifndef __CLDbDriver_h__
#define __CLDbDriver_h__

#define MAXLABELLEN	12
#define MAXLOGIN        100

#define MAX_COL_LENGTH 60

//数据库连接结构。
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


//连接数据库参数
typedef enum tagDbConnFlag
{
	DB_CONN_UNUSE_LABEL = 0,	//不使用标签作连接。
	DB_CONN_USE_LABEL = 1		//使用标签作连接。
}EDbConnFlag;

//断开数据库参数
typedef enum tagDbDisConnFlag
{
	DB_DISCONN_COMMIT = 1,		//在断开连接之前，提交数据库操作。
	DB_DISCONN_ROLLBACK = 2		//在断开连接之前，回滚数据库操作。
}EDbDisConnFlag;

//当执行ExecuteSql()函数时，如果查询操作，当从游标读取一行数据完成后会触发此事件。
//返回值：如果返回值不为零，则中断当前游标的执行，并返回此函数的错误代码。
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

	//驱动类型定义代码
	virtual TDriverType GetDriverType() const;
public:
	/*
	 Data Source:数据源
	 User Id:用户名
	 Password:口令
	 */
	string ConnectString;

	/*
	 * bIsDefaultConn：是否是默认数据库连接
	 * psConnName：连接名，没有传递就是为空。
	 */
	ETYPE Open(ub4 connDbType, bool bIsDefaultConn, const char *psConnName) throw();

	//通过数据库标签连接数据库，此种连接设置全局默认连接为此连接。
	inline ETYPE Open(const char* dbLabel) throw()
	{
		ETYPE iRet;
		if ( (iRet = GetDbP(dbLabel)) != 0)
		{
			return iRet;
		}
		return Open(DB_CONN_TYPE_PROC, true,NULL);
	}
	
	//通过数据库标签连接数据库
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

	//提交事物
	int Commit() throw();

	//回滚事物
	int Rollback() throw();

	//是否登录状态
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

	//返回CLConnection的内部连接“CLCommand *”。
	CLCommand *GetCommand()
	{
		return m_Command;
	}

	//得到此连接的名称。
	const char *GetConnName()
	{
		return m_sConnName;
	}
	
	//得到连接的数据库类型。
	ub4 GetConnDbType()
	{
		return m_connDbType;
	}

	//判断此连接是否是默认连接
	bool IsDefaultConn()
	{
		return m_bIsDefaultConn;
	}

	//连接的数据库类型
	//OCI模式
	static const ub4 DB_CONN_TYPE_OCI	= 0;

	//PRO*C模式
	static const ub4 DB_CONN_TYPE_PROC	= 1;

	//PRO*C模式，使用现有的pro*c连接
	static const ub4 DB_CONN_TYPE_USE_EXISTS_PROC	= 2;
private:
	/*
		生成一个命令类，
	 */
	ETYPE CreateCommond(bool bIsDefaultConn) throw();

	/*
		删除一个命令类，
	 */
	void DeleteCommond() throw();

	ETYPE InitHandles();
	void FreeHandles();

	//初始化用户句柄
	ETYPE Initialize();

	// Logon to the database using given username, password & credentials
	ETYPE LogOn(const char *uid, const char *pwd, const char* tnsName, ub4 credt);

	ETYPE AttachServer(const char *tnsName);
	void LogOutDetachServer();
	void Destruction();

	//得到数据库标签的内容：数据库名、用户名和口令。
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

	//连接的数据库类型
	ub4 m_connDbType;

	//是否是默认连接
	bool m_bIsDefaultConn;

	CLCommand *m_Command;

	//连接名，一般是CLConnection连接的唯一标识。此连接名可以用于，知道CLConnection是哪一个连接，
	//对使用连接池比较有用。
	char m_sConnName[255+1];
};

//全局数据库命令类指针
extern CLCommand *g_Command;

#endif //__CLDBDriver_h__

