#ifndef __CLCommand_h__
#define __CLCommand_h__

#define MAXBINDS		40
#define MAXITER			10
#define MAXCOLS			MAXBINDS

//数据库操作语句类型
#define  DB_STMT_SELECT  1                              /* select statement */
#define  DB_STMT_UPDATE  2                              /* update statement */
#define  DB_STMT_DELETE  3                              /* delete statement */
#define  DB_STMT_INSERT  4                              /* Insert Statement */
#define  DB_STMT_CREATE  5                              /* create statement */
#define  DB_STMT_DROP    6                                /* drop statement */
#define  DB_STMT_ALTER   7                               /* alter statement */
#define  DB_STMT_BEGIN   8                   /* begin ... (pl/sql statement)*/
#define  DB_STMT_DECLARE 9                /* declare .. (pl/sql statement ) */


typedef enum tagCommondType
{
	//Does not specify the command type argument.
	adCmdUnspecified		= -1,

	//Evaluates CommandText as a textual definition of a command or stored procedure call.
	adCmdText				= 1,

	//Evaluates CommandText as a table name whose columns are all returned by an internally generated SQL query.
	adCmdTable				= 2,

	//Evaluates CommandText as a stored procedure name.
	adCmdStoredProc			= 4,

	//Default. Indicates that the type of command in the CommandText property is not known.
	adCmdUnknown			= 8,

	//Evaluates CommandText as the file name of a persistently stored Recordset. Used with Recordset.Open or Requery only.
	adCmdFile				= 256,

	//Evaluates CommandText as a table name whose columns are all returned.
	//Used with Recordset.Open or Requery only. To use the Seek method,
	//the Recordset must be opened with adCmdTableDirect. 
	//This value cannot be combined with the ExecuteOptionEnum value adAsyncExecute.
	adCmdTableDirect		= 512
} TCommondType;

//Specifies the data type of a Field, Parameter, or Property.
typedef enum tagDataTypeEnum
{
	DT_UB1		= 1,	//一字节整型
	DT_UB2		= 2,	//二字节整型
	DT_UB4		= 3,	//四字节整型
	DT_UB8		= 4,	//八字节整型
	DT_FLOAT	= 5,	//浮点型
	DT_DOUBLE	= 6,	//双精度浮点型
	DT_PUB1		= 7		//一字节整型指针
} TDataTypeEnum;


//Indicates whether the Parameter represents an input parameter, 
//an output parameter, an input and an output parameter, 
//or if the parameter is the return value from a stored procedure.
typedef enum tagParameterDirectionEnum
{
	// Indicates that the parameter direction is unknown. 
	adParamUnknown		= 0,

	//Default. Indicates that the parameter represents an input parameter. 
	adParamInput		= 1,
	
	// Indicates that the parameter represents an output parameter.  
	adParamOutput		= 2,

	// Indicates that the parameter represents both an input and output parameter. 
	adParamInputOutput	= 3,

	// Indicates that the parameter represents a return value. 
	adParamReturnValue	= 4

} TParameterDirectionEnum;


//数据操作类型
typedef union tagLVariant
{
	char *p1Val;
	short int *p2Val;
	int *p4Val;
	long int *p8Val;
	float *pfVal;
	double *pdVal;
	void *pVal;
}TLVariant;

class CLProperty
{
public:
	CLProperty() :
	  Attributes(0)
	{
	}
	
	//对象的一个或多个特性值
	long Attributes;

	//对象的名称
	string Name;

	//表明CLProperty的操作类型。
	TDataTypeEnum Type;

	//属性值
	TLVariant Value;
};

class CLParameter 
{
public:
	CLParameter() :
	  Attributes(0), Direction(adParamInput),
	  NumericScale(0),Precision(0),Size(0),Type(DT_PUB1)
	{
		memset(Name, 0, sizeof(Name));
		Value.pVal = NULL;
	}
	CLParameter(TDataTypeEnum type, TParameterDirectionEnum direction,
		long size, void *value)
	{
		memset(Name, 0, sizeof(Name));
		Attributes  = 0;
		NumericScale = 0;
		Precision = 0;
		this->Type = type;
		this->Direction = direction;
		this->Size = size;
		this->Value.pVal = value;
	}
	~CLParameter()
	{
		for (unsigned int i=0;i < Properties.size(); i ++)
		{
			delete Properties.at(i);
		}
		Properties.clear();
	}
public:

	//对象的一个或多个特性值
	long Attributes;

	//表明参数的方向
	TParameterDirectionEnum Direction;

	//对象的名称
	char Name[MAX_COL_LENGTH+1];

	//Indicates the scale of numeric values in a Parameter or Field object.
	ub1 NumericScale;

	//Indicates the degree of precision for numeric values in a Parameter object
	//or for numeric Field objects. 
	ub1 Precision;

	//属性
	vector<CLProperty*> Properties;

	//参数一行的最大字节位数，Value指向的内存大小＝Size * 每次取出的行数
	long Size;

	//表明CLParameter的操作类型。
	TDataTypeEnum Type;

	//数据库的类型参数。主要用于SELECT的返回参数。
	int m_iDbDataType;

	//数据库的字段返回的长度。主要用于SELECT的返回参数。
	int m_iDbDataSize;

	//参数的数组值.Value.p1Val[0], Value.p1Val[1], ...
	TLVariant Value;
};

class ol_exception : public std::exception
{
public:
	long code;
	char msg[2047+1];

	ol_exception(const int acode, const char* amsg)
	{
		memset(msg, 0, sizeof(msg));
		code = acode;
		strcpy(msg, amsg);
	}
	virtual const char* what() const throw()
	{
		return msg;
	}
};

class CLRecordSet;
class CLCommand :	public CLDriver
{
public:
	CLCommand();
	~CLCommand();
	
	//驱动类型定义代码
	virtual TDriverType GetDriverType() const;
public:
	string CommondText;
	TCommondType CommondType;

	//当前激活的连接
	CLConnection *ActiveConnection;

	//执行语句
	//  lOptions暂时无用
	ETYPE Execute(unsigned int iRecordsAffected = 0, long lOptions = 0) throw();

	//对Execute函数的简单封装
	ETYPE Exec(const char *psSqlText, unsigned int iRecordsAffected = 0, long lOptions = 0) throw()
	{
		CommondType = adCmdText;
		CommondText = psSqlText;
		return Execute(0,0);
	}

	//对Execute函数的封装
	void Open(int iRecordsAffected, const char* sqlText, CLConnection &con) throw(ol_exception);

	//得到记录行数
	int GetSqlRows() throw();

	//关闭语句
	void Close() throw();

	//清空输入输出参数列表
	//clearOptions:
	//	0:无意义
	//  1:清除参数类表中值占用的内存，暂时没用启用
	void ClearParameters (int clearOptions=0) throw();

	CLRecordSet* GetRecordSet() throw()
	{
		return recordSet;
	}

	vector <CLParameter*>& GetOutParameters() throw()
	{
		return outParams;
	}

	//得到ORACLE错误
	void GetOraError(int *errorCode, char* errMsg) throw();

	//设置输入参数。老函数将被废弃
	CLCommand* I(const char* data, unsigned int dataLength) throw(CLException);
	CLCommand* I(const char& data, unsigned int dataLength) throw(CLException);
	CLCommand* I(const unsigned short& data, unsigned int dataLength) throw(CLException);
	CLCommand* I(const unsigned int& data, unsigned int dataLength) throw(CLException);
	CLCommand* I(const unsigned long& data, unsigned int dataLength) throw(CLException);
	CLCommand* I(const float& data, unsigned int dataLength) throw(CLException);
	CLCommand* I(const double& data, unsigned int dataLength) throw(CLException);
	CLCommand* O(char* data, unsigned int dataLength) throw(CLException);
	CLCommand* O(char& data, unsigned int dataLength) throw(CLException);
	CLCommand* O(unsigned short& data, unsigned int dataLength) throw(CLException);
	CLCommand* O(unsigned int& data, unsigned int dataLength) throw(CLException);
	CLCommand* O(unsigned long& data, unsigned int dataLength) throw(CLException);
	CLCommand* O(float& data, unsigned int dataLength) throw(CLException);
	CLCommand* O(double& data, unsigned int dataLength) throw(CLException);

	//新函数
	CLCommand& operator<<(const unsigned char &cVal) throw(CLException);
	CLCommand& operator<<(const char* psVal) throw(CLException);
	CLCommand& operator<<(const unsigned char* psVal) throw(CLException);
	CLCommand& operator<<(const int &iVal) throw(CLException);
	CLCommand& operator<<(const float &fVal) throw(CLException);
	CLCommand& operator<<(const double &dVal) throw(CLException);
	CLCommand& operator<<(const short int &siVal) throw(CLException);
	CLCommand& operator<<(const unsigned int &uiVal) throw(CLException);
	CLCommand& operator<<(const long int &lVal) throw(CLException);
	CLCommand& operator>>(char* psVal) throw(CLException);
	CLCommand& operator>>(unsigned char* psVal) throw(CLException);
	CLCommand& operator>>(int& iVal) throw(CLException);
	CLCommand& operator>>(float& fVal) throw(CLException);
	CLCommand& operator>>(double& dVal) throw(CLException);
	CLCommand& operator>>(short int& siVal) throw(CLException);
	CLCommand& operator>>(unsigned int& iVal) throw(CLException);
	CLCommand& operator>>(long int& lVal) throw(CLException);
public:
	//初始化输入输出参数列表
	ETYPE InitParameters (int initOptions=0) throw();

	/*
		生成一个记录集类，
	 */
	CLRecordSet * BindToRecordset() throw();

	OCIStmt *GetStmthp() throw()
	{
		return m_stmthp;
	}
private:
	//设置一个输入参数
	//Size	参数一行的最大字节位数，Value指向的内存大小＝Size * 每次取出的行数。
	//Value	参数的数组值.Value.p1Val[0], Value.p1Val[1], ...
	void SetInParameter (TDataTypeEnum Type,	long Size, void *Value) throw(CLException);

	//设置一个输出参数
	//Size	参数一行的最大字节位数，Value指向的内存大小＝Size * 每次取出的行数。
	//Value	参数的数组值.Value.p1Val[0], Value.p1Val[1], ...
	void SetOutParameter (TDataTypeEnum Type,	long Size, void *Value) throw(CLException);

	//得到绑定绑定变量的数量，并删除执行语句中的绑定变量类型信息。
	int DealBindSql(char* sqlContext) throw();

	void DetachRecordset() throw();

	//检查是否可以执行操作
	void CheckExecute() throw(ol_exception);

	//根据位置绑定变量值
	//pos 从1开始
	ETYPE BindInByPos(unsigned int pos, void * data, unsigned int dataLen, TDataTypeEnum dataType)  throw();

	//根据位置绑定变量值
	//pos 从1开始
	ETYPE BindInByName(const char* bindName, unsigned int pos, void * data, unsigned int dataLen, TDataTypeEnum dataType) throw();

	//根据位置绑定变量值
	//pos 从1开始
	ETYPE BindOutByPos(unsigned int pos, void * data, unsigned int dataLen, TDataTypeEnum dataType) throw();

	//本地数据类型到数据库类型的转换
	inline ETYPE LocalTypeToDbType(TDataTypeEnum &localType, unsigned short &dbType)
	{
		switch(localType)
		{
		case DT_UB1:
			{
				dbType = SQLT_INT;
				break;
			}
		case DT_UB2:
			{
				dbType = SQLT_INT;
				break;
			}
		case DT_UB4:
			{
				dbType = SQLT_INT;
				break;
			}
		case DT_UB8://不支持unsigned long，或long等大于等于64的整型
			{
				dbType = SQLT_INT;
				break;
			}
		case DT_FLOAT:
			{
				dbType = SQLT_FLT;
				break;
			}
		case DT_DOUBLE:
			{
				dbType = SQLT_FLT;
				break;
			}
		case DT_PUB1:
			{
				dbType = SQLT_AFC;
				break;
			}
		default:
			{
				return CLError::E_DB_SQL_DATA_TYPE;
			}
		}
		return 0;
	}

	//内部执行SQL语句
	ETYPE PrepareSql(const char* sqlContext, int preFlags);

	OCIStmt *m_stmthp;
private:
	bool bIsInit;//是否做过参数初始化操作。

	//  indicator skips
	unsigned int   pvsk[MAXCOLS];
	//  indicator skips
	unsigned int   indsk[MAXCOLS];
	//  return length skips
	unsigned int   rlsk[MAXCOLS];
	//  return code skips
	unsigned int   rcsk[MAXCOLS];

	OCIBind *m_bndhp[MAXBINDS];
	OCIDefine *m_defnp[MAXCOLS];

	//最后执行的SQL语句的类型
	unsigned short m_sqlType;
	
	//输入参数列表
	vector <CLParameter*> inParams;

	//输入参数数量
	unsigned int m_inParamCount;

	//输出的列参数表
	vector <CLParameter*> outParams;

	//输出参数数量
	unsigned int m_outParamCount;

	CLRecordSet* recordSet;

	//执行的记录行数
	int iExecRowCount;

	//经过格式化后的字符串
	string sFormatCommondText;

	//绑定变量的个数。
	unsigned int m_iBindVarCount;

	//影响执行数量
	int m_iRecordsAffected;

	//1. 检查绑定变量的数量，判读是否可以执行。
	//2. 用于设定是使用用户的变量内存地址，还是内部增加中间变量存储。true使用用户变
	//   量内存，false内部增加中间变量存储，内部变量每次只能读取一条记录。注意，如果
	//   是false，就要注意内存处理不能出现问题。
	bool m_bIsAfterBindAndUserMemory;
};


#endif//__CLCommand

