#include "llayerStruct.h"

CLCommand::CLCommand()
{
	ActiveConnection = NULL;
	CommondText = "";
	sFormatCommondText = "";
	bIsInit = false;
	m_iBindVarCount = 0;
	m_iRecordsAffected = 0;
	m_bIsAfterBindAndUserMemory = false;
	
	CommondType = adCmdUnknown;
	m_sqlType = DB_STMT_SELECT;
	
	m_stmthp = (OCIStmt *) NULL;

	memset(&pvsk, 0, sizeof(pvsk));
	memset(&indsk, 0, sizeof(indsk));
	memset(&rlsk, 0, sizeof(rlsk));
	memset(&rcsk, 0, sizeof(rcsk));

	int i;
	for (i = 0; i < MAXBINDS; i++)
	{
		m_bndhp[i] = (OCIBind *) 0;
	}
	for (i = 0; i < MAXCOLS; i++)
	{
		m_defnp[i] = (OCIDefine *) 0;
	}
	recordSet = (CLRecordSet *)NULL;

	m_inParamCount = 0;

	m_outParamCount = 0;

	iExecRowCount = 0;
}

CLCommand::~CLCommand()
{
	int i;
	for (i = 0; i < MAXBINDS; i++)
	{
		if (m_bndhp[i])
		{
			/*
			 * 使用OCIBindByPos会生成一个绑定句柄，此句柄的内存由OCI自己管理，不用调用OCIHandleFree释放。
			 * OCIHandleFree((dvoid *) m_bndhp[pos-1], (unsigned int) OCI_HTYPE_BIND);
			 */
			m_bndhp[i] = (OCIBind *) 0;
		}
	}
	for (i = 0; i < MAXCOLS; i++)
	{
		if (m_defnp[i])
		{
			/*
			 * 使用OCIDefineByPos会生成一个绑定句柄，此句柄的内存由OCI自己管理，不用调用OCIHandleFree释放。
			 * OCIHandleFree((dvoid *) m_defnp[i], (unsigned int) OCI_HTYPE_DEFINE);
			 */
			m_defnp[i] = NULL;

		}
	}

	Close();

	DetachRecordset();
	ClearParameters(0);
}

TDriverType CLCommand::GetDriverType() const
{
	return DRIVER_DATABASE;
}

//根据位置绑定变量值
//pos 从1开始
ETYPE CLCommand::BindInByPos(unsigned int pos, void * data, unsigned int dataLen, TDataTypeEnum dataType)  throw()
{
	ETYPE iRet = 0;
	unsigned short oraDataType;

	DBUG_ENTER("CLCommand::BindInByPos");
	
	if ((pos > MAXBINDS) || (pos <= 0))
	{
		DBUG_RETURN(CLError::E_DB_BIND_MAXIMUM);
	}
	if (m_bndhp[pos-1])
	{
		/*
		 * 使用OCIBindByPos会生成一个绑定句柄，此句柄的内存由OCI自己管理，不用调用OCIHandleFree释放。
		 * OCIHandleFree((dvoid *) m_bndhp[pos-1], (unsigned int) OCI_HTYPE_BIND);
		 */
		//m_bndhp[pos-1] = NULL;
	}

	if ((iRet = LocalTypeToDbType(dataType, oraDataType)) != 0)
	{
		DBUG_RETURN(iRet);
	}

	if ((iRet = OCIBindByPos(m_stmthp, &m_bndhp[pos-1], ActiveConnection->GetErrhp(), (unsigned int) pos,
				(dvoid *) data, (sb4)dataLen, (unsigned short)oraDataType,
				(dvoid *) 0, (unsigned short *)0, (unsigned short *)0,
				(unsigned int) 0, (unsigned int *) 0, ActiveConnection->GetOciMode())) != 0)
	{
		DBUG_RETURN(CLError::E_DB_SQLALD_BIND);
	}
	pvsk[pos - 1] = dataLen;
	iRet = OCIBindArrayOfStruct(m_bndhp[pos-1], ActiveConnection->GetErrhp(),
		pvsk[pos - 1], indsk[pos-1], rlsk[pos-1], rcsk[pos-1]);

	DBUG_RETURN(iRet);
}

//根据位置绑定变量值
//pos 从1开始
ETYPE CLCommand::BindInByName(const char* bindName, unsigned int pos, void * data, unsigned int dataLen, TDataTypeEnum dataType)  throw()
{
	ETYPE iRet = 0;
	unsigned short oraDataType;

	DBUG_ENTER("CLCommand::BindInByName");
	
	if ((pos > MAXBINDS) || (pos <= 0))
	{
		DBUG_RETURN(CLError::E_DB_BIND_MAXIMUM);
	}
	if (m_bndhp[pos-1])
	{
		/*
		 * 使用OCIBindByName会生成一个绑定句柄，此句柄的内存由OCI自己管理，不用调用OCIHandleFree释放。
		 * OCIHandleFree((dvoid *) m_bndhp[pos-1], (unsigned int) OCI_HTYPE_BIND);
		 */
		//m_bndhp[pos-1] = NULL;
	}

	if ((iRet = LocalTypeToDbType(dataType, oraDataType)) != 0)
	{
		DBUG_RETURN(iRet);
	}

	if ((iRet= OCIBindByName(m_stmthp, &m_bndhp[pos-1], ActiveConnection->GetErrhp(),
					(text *) bindName, (sb4) strlen((char *) bindName),
					(dvoid *) data, (sb4) dataLen, (unsigned short)oraDataType,
					(dvoid *) 0, (unsigned short *)0, (unsigned short *)0,
					(unsigned int) 0, (unsigned int *) 0, (unsigned int) ActiveConnection->GetOciMode()) ) != 0)
	{
		DBUG_RETURN(CLError::E_DB_SQLALD_BIND);
	}
	pvsk[pos - 1] = dataLen;
	iRet = OCIBindArrayOfStruct(m_bndhp[pos-1], ActiveConnection->GetErrhp(),
		pvsk[pos - 1], indsk[pos-1], rlsk[pos-1], rcsk[pos-1]);

	DBUG_RETURN(iRet);
}

//根据位置绑定变量值
//pos 从1开始
ETYPE CLCommand::BindOutByPos(unsigned int pos, void * data, unsigned int dataLen, TDataTypeEnum dataType)  throw()
{
	ETYPE iRet = 0;
	unsigned short oraDataType;

	DBUG_ENTER("CLCommand::BindOutByPos");
	
	if ((pos > MAXCOLS) || (pos <= 0))
	{
		DBUG_RETURN(CLError::E_DB_SELECT_MAXIMUM);
	}
	if (m_defnp[pos-1])
	{
		/*
		 * 使用OCIDefineByPos会生成一个绑定句柄，此句柄的内存由OCI自己管理，不用调用OCIHandleFree释放。
		 * OCIHandleFree((dvoid *) m_defnp[pos-1], (unsigned int) OCI_HTYPE_DEFINE);
		 */
		//m_defnp[pos-1] = NULL;
	}

	if ((iRet = LocalTypeToDbType(dataType, oraDataType)) != 0)
	{
		DBUG_RETURN(iRet);
	}

	if ((iRet = OCIDefineByPos(m_stmthp, &m_defnp[pos-1], ActiveConnection->GetErrhp(),
						(unsigned int) pos, (dvoid *) data,(sb4) dataLen, (unsigned short)oraDataType,
						(dvoid *) 0, (unsigned short *)0,(unsigned short *)0, (unsigned int) ActiveConnection->GetOciMode())) != 0)
	{
		DBUG_RETURN(CLError::E_DB_SQL_DEFINE);
	}
	pvsk[pos - 1] = dataLen;
	iRet = OCIDefineArrayOfStruct(m_defnp[pos-1], ActiveConnection->GetErrhp(),
		pvsk[pos - 1], indsk[pos-1], rlsk[pos-1], rcsk[pos-1]);

	DBUG_RETURN(iRet);
}

//生成一个输入参数
//Size	1、参数一行的最大字节位数，Value指向的内存大小＝Size * 每次取出的行数。
//      2、对于查询语句中传入的字符串，使用strlen得到字符串的长度。
//Value	参数的数组值.Value.p1Val[0], Value.p1Val[1], ...
void CLCommand::SetInParameter (TDataTypeEnum Type, long Size, void *Value) throw(CLException)
{
	ETYPE iRet=0;
	CLParameter * param=NULL;

	DBUG_ENTER("CLCommand::SetInParameter");

	if ((m_inParamCount > MAXBINDS ) )
	{
		throw CLException(CLError::E_DB_BIND_MAXIMUM);
	}

	param = inParams.at(m_inParamCount);
	param->Type = Type;
	param->Size = Size;
	param->Value.pVal = Value;

	m_inParamCount ++;

	CheckExecute();

	DBUG_VOID_RETURN;
}

//生成一个输出参数
//Size	参数一行的最大字节位数，Value指向的内存大小＝Size * 每次取出的行数。
//Value	参数的数组值.Value.p1Val[0], Value.p1Val[1], ...
void CLCommand::SetOutParameter (TDataTypeEnum Type, long Size, void *Value) throw(CLException)
{
	ETYPE iRet=0;
	CLParameter * param=NULL;

	DBUG_ENTER("CLCommand::SetOutParameter");
	if ((m_outParamCount > MAXBINDS ) )
	{
		throw CLException(CLError::E_DB_BIND_MAXIMUM);
	}
	param = outParams.at(m_outParamCount);
	param->Type = Type;
	param->Size = Size;
	param->Value.pVal = Value;

	m_outParamCount ++;
	DBUG_VOID_RETURN;
}

//清空输入输出参数列表
ETYPE CLCommand::InitParameters (int initOptions) throw()
{
	ETYPE iRet=0;
	CLParameter * param=NULL;
	unsigned int i = 0;

	DBUG_ENTER("CLCommand::InitParameters");
   
	for ( i = 0; i < MAXBINDS; i ++ )
	{
		param = new CLParameter(DT_PUB1, adParamInput, 0, NULL);
		if (param == (CLParameter *)NULL)
		{
			DBUG_RETURN(CLError::E_MEMORY_LACK);
		}
		inParams.push_back(param);
	}

	for ( i = 0; i < MAXCOLS; i ++ )
	{
		param = new CLParameter(DT_PUB1, adParamOutput, 0, NULL);
		if (param == (CLParameter *)NULL)
		{
			DBUG_RETURN(CLError::E_MEMORY_LACK);
		}
		outParams.push_back(param);
	}
	bIsInit = true;

	DBUG_RETURN(iRet);
}


//清空输入输出参数列表
void CLCommand::ClearParameters (int clearOptions) throw()
{
	ETYPE iRet=0;
	unsigned int i = 0;

	DBUG_ENTER("CLCommand::ClearParameter");
   
	if (bIsInit)
	{
		for ( i = 0; i < inParams.size(); i ++ )
		{
			delete inParams.at(i);
		}

		for ( i = 0; i < outParams.size(); i ++ )
		{
			delete outParams.at(i);
		}

		inParams.clear();
		outParams.clear();
	}

	DBUG_VOID_RETURN;
}



//得到绑定绑定变量的数量，并删除执行语句中的绑定变量类型信息。
int CLCommand::DealBindSql(char* sqlContext) throw()
{
	short in_str=0;
	bool in_comment=false;
	bool in_one_line_comment=false;
	char *c=sqlContext;

	m_iBindVarCount = 0;
	while(*c)
	{
		switch(*c)
		{
		case '\'':
			if(!in_comment&&!in_one_line_comment)
			{
				if(!in_str)
					in_str=1;
				else{
					if(c[1]=='\'')
						++c;
					else
						in_str=0;
				}
			}
			break;
		case '/':
			if(c[1]=='*'&&!in_str)
			{
				in_comment=true;
				++c;
			}
			break;
		case '-':
			if(c[1]=='-'&&!in_str)
			{
				in_one_line_comment=true;
				++c;
			}
			break;
		case '*':
			if(c[1]=='/'&&in_comment)
			{
				in_comment=false;
				++c;
			}      
			break;
		case '\n':
			if(in_one_line_comment)
				in_one_line_comment=false;
			break;
		}
		if(*c==':' && !in_str && !in_comment && !in_one_line_comment &&
			(c>sqlContext && *(c-1)!='\\' || c==sqlContext))
		{
			char* bind_var_ptr=c;
			char var[64];
			char* v=var;
			*v++=*c++;
			while(isalnum(*c)||*c=='_'||*c=='#')
				*v++=*c++;
			while(isspace(*c)&&*c)
				++c;
			if(*c=='<')
			{
				*c=' ';
				while(*c!='>'&&*c)
				{
					*v++=*c;
					*c++=' ';
				}

				if(*c)*c=' ';
				*v='\0';
				//AddVar(i,var);
			}
			m_iBindVarCount++;
		}
		if(*c)++c;
	}

	return m_iBindVarCount;
}

ETYPE CLCommand::Execute(unsigned int iRecordsAffected, long lOptions) throw()
{
	ETYPE iRet=0;

	DBUG_ENTER("CLCommand::Execute");

	m_iRecordsAffected = iRecordsAffected;
	
	if (!ActiveConnection)
	{
		DBUG_RETURN(CLError::E_DB_SQL_NOCONNECT);
	}

	if (!ActiveConnection->IsLoggedOn())
	{
		DBUG_RETURN(CLError::E_DB_SQL_NOCONNECT);
	}

	//初始化执行的记录条数为0.
	iExecRowCount = 0;

	//对于没有关闭的SQL语句进行关闭
	Close();

	if ((iRet = PrepareSql(CommondText.c_str(), 0)) != 0)
	{
		DBUG_RETURN(iRet);
	}

	if ( (m_sqlType != DB_STMT_SELECT) && (m_iRecordsAffected <=0 || m_iRecordsAffected>MAXITER))
	{
		DBUG_RETURN(CLError::E_DB_SQL_EXECUTE_ITERS);
	}

	for (unsigned int i = 0; i < m_inParamCount; i ++)
	{
		if ((iRet = BindInByPos(i+1, inParams.at(i)->Value.pVal, 
			inParams.at(i)->Size,
			inParams.at(i)->Type)) != 0)
		{
			DBUG_RETURN(iRet);
		}
	}

	// Execute the statement
	printf("+++++++++++++++++++\n");
	
	if (OCIStmtExecute(ActiveConnection->GetSvchp(), m_stmthp, ActiveConnection->GetErrhp(), (unsigned int) m_iRecordsAffected, (unsigned int) 0,
		(CONST OCISnapshot*) 0, (OCISnapshot*) 0,
		(unsigned int) ActiveConnection->GetOciMode()))
	{
		DBUG_PRINT("info", ("CLCommand::Execute OCIStmtExecute ERROR"));
		DBUG_RETURN(CLError::E_DB_SQL_EXECUTE);
	}

	if (m_sqlType == DB_STMT_SELECT)
	{
		if (recordSet != (CLRecordSet*)NULL)
		{
			sb4 paramStatus;
			unsigned short dtype;
			unsigned short iDataSize=0;
			text         *colName;
			unsigned int          colNameLen;
			OCIParam     *paramInfo = (OCIParam *) 0;

			if ((iRet = recordSet->SetColomnCount()) != 0)
			{
				DBUG_RETURN(CLError::E_DB_SQL_EXECUTE);
			}
			if (recordSet->GetColomnCount() >= MAXCOLS)
			{
				DBUG_RETURN(CLError::E_DB_SELECT_MAXIMUM);
			}
			
			for (unsigned int i = 0; i < recordSet->GetColomnCount() && i < outParams.size(); i ++)
			{
				paramStatus = OCIParamGet((dvoid *)m_stmthp, OCI_HTYPE_STMT, ActiveConnection->GetErrhp(),
							   (dvoid **)&paramInfo, (unsigned int) i+1);
				if (paramStatus != OCI_SUCCESS)
				{
					DBUG_RETURN(CLError::E_DB_GET_COL_ATTR);
				}

				if (OCIAttrGet((dvoid*) paramInfo, (unsigned int) OCI_DTYPE_PARAM, (dvoid*) &dtype,
					(unsigned int *) 0, (unsigned int) OCI_ATTR_DATA_TYPE,  ActiveConnection->GetErrhp()) != 0)
				{
					DBUG_RETURN(CLError::E_DB_GET_COL_ATTR);
				}
				outParams.at(i)->m_iDbDataType = dtype;

				if (OCIAttrGet((dvoid*) paramInfo, (unsigned int) OCI_DTYPE_PARAM, (dvoid*) &iDataSize,
					(unsigned int *) 0, (unsigned int) OCI_ATTR_DATA_SIZE,  ActiveConnection->GetErrhp()) != 0)
				{
					DBUG_RETURN(CLError::E_DB_GET_COL_ATTR);
				}
				outParams.at(i)->m_iDbDataSize = iDataSize;

				if ((outParams.at(i))->Size == -1)
				{
					if (OCIAttrGet((dvoid*) paramInfo, (unsigned int) OCI_DTYPE_PARAM, (dvoid*) &iDataSize,
						(unsigned int *) 0, (unsigned int) OCI_ATTR_DATA_SIZE,  ActiveConnection->GetErrhp()) != 0)
					{
						DBUG_RETURN(CLError::E_DB_GET_COL_ATTR);
					}
					outParams.at(i)->Size = iDataSize+1;
				}
				
				if ((iRet = BindOutByPos(i+1, (outParams.at(i))->Value.pVal, (outParams.at(i))->Size,
					(outParams.at(i))->Type)) != 0)
				{
					DBUG_RETURN(iRet);
				}


				if (OCIAttrGet((dvoid*) paramInfo, (unsigned int) OCI_DTYPE_PARAM, &colName,
					(unsigned int *) &colNameLen, (unsigned int) OCI_ATTR_NAME,  ActiveConnection->GetErrhp()) != 0)
				{
					DBUG_RETURN(CLError::E_DB_GET_COL_ATTR);
				}
				strncpy((outParams.at(i))->Name,(const char*)colName, MAX_COL_LENGTH);
				(outParams.at(i))->Name[MAX_COL_LENGTH] = '\0';
				if (OCIAttrGet((dvoid*) paramInfo, (unsigned int) OCI_DTYPE_PARAM, (dvoid*) &(outParams.at(i))->Precision,
					(unsigned int *) 0, (unsigned int) OCI_ATTR_PRECISION,  ActiveConnection->GetErrhp()) != 0)
				{
					DBUG_RETURN(CLError::E_DB_GET_COL_ATTR);
				}
				if (OCIAttrGet((dvoid*) paramInfo, (unsigned int) OCI_DTYPE_PARAM, (dvoid*) &(outParams.at(i))->NumericScale,
					(unsigned int *) 0, (unsigned int) OCI_ATTR_SCALE,  ActiveConnection->GetErrhp()) != 0)
				{
					DBUG_RETURN(CLError::E_DB_GET_COL_ATTR);
				}
				paramStatus=OCIDescriptorFree(paramInfo, (unsigned int)OCI_DTYPE_PARAM);
				if (paramStatus != OCI_SUCCESS)
				{
					DBUG_RETURN(CLError::E_DB_GET_COL_ATTR);
				}
			}
		}
	}
	else
	{
		this->Close();
	}

	//设置初始输入参数数量
	m_inParamCount = 0;
	m_outParamCount = 0;
	m_iBindVarCount = 0;
	CommondText = "";
	m_bIsAfterBindAndUserMemory = false;

	DBUG_PRINT("info", ("CLCommand::Execute OK"));
	DBUG_RETURN(iRet);
}

//检查是否可以执行操作
void CLCommand::CheckExecute() throw(ol_exception)
{
	ETYPE iRet = 0;
	if (m_bIsAfterBindAndUserMemory)
	{
		if (m_iBindVarCount == m_inParamCount)
		{
			if ( (iRet = Execute(m_iRecordsAffected, 0)) != 0)
			{
				int oraErrorCode = 0;
				char errMsg[512];
				memset(errMsg, 0, sizeof(errMsg));
				GetOraError(&oraErrorCode, (char*)errMsg);
				if (oraErrorCode != 0)
				{
					throw(ol_exception(oraErrorCode,errMsg));
				}
				else
				{
					const char *psErrMsg = CLError::GetErrorMsg(iRet);
					if (psErrMsg)
					{
						throw(ol_exception(iRet,psErrMsg));
					}
					else
					{
						throw(ol_exception(iRet,"其他错误！"));
					}
				}
			}
		}
	}
}

void CLCommand::Open(int iRecordsAffected, const char* sqlText, CLConnection &con) throw(ol_exception)
{
	ETYPE iRet = 0;
	m_iRecordsAffected = iRecordsAffected;
	ActiveConnection = &con;
	BindToRecordset();//可以多次初始化，为了更新CLConnection。
	if (!bIsInit)
	{
		InitParameters(0);
	}
	
	int iLen = (int)strlen(sqlText);
	char *s = (char*)malloc(iLen + 1);
	memset(s, 0, iLen + 1);
	strcpy(s, sqlText);
	DealBindSql(s);
	CommondText = s;
	free(s);

	m_bIsAfterBindAndUserMemory = true;

	CheckExecute();
}

//得到记录行数
int CLCommand::GetSqlRows() throw()
{
	if (m_stmthp)
	{
		this->GetRecordSet()->GetRowCount((unsigned int*)&iExecRowCount);
	}
	return iExecRowCount;
}

//关闭语句
void CLCommand::Close() throw()
{
	if (m_stmthp)
	{
		this->GetRecordSet()->GetRowCount((unsigned int*)&iExecRowCount);
		(void) OCIHandleFree((dvoid *) m_stmthp, (unsigned int) OCI_HTYPE_STMT);
		m_stmthp = NULL;
	}
}

void CLCommand::GetOraError(int *errorCode, char* errMsg) throw()
{ 
	text  msgbuf[512];

	(void) OCIErrorGet((dvoid *)ActiveConnection->GetErrhp(), (unsigned int) 1, (text *) NULL, errorCode,
			msgbuf, (unsigned int) sizeof(msgbuf)-1, (unsigned int) OCI_HTYPE_ERROR);
	msgbuf[511] = '\0';
	strcpy(errMsg, (const char *)msgbuf);
	return;
}

void CLCommand::DetachRecordset() throw()
{
	if (recordSet)
	{
		delete recordSet;
	}
	return;
}


CLRecordSet * CLCommand::BindToRecordset() throw()
{
	if (!recordSet)
	{
		recordSet = new CLRecordSet();
	}
	recordSet->ActiveConnection = this->ActiveConnection;
	recordSet->ActiveCommand = this;
	return recordSet;
}

//内部执行SQL语句
ETYPE CLCommand::PrepareSql(const char* sqlContext, int preFlags)
{
	ETYPE iRet;

	DBUG_ENTER("CLCommand::PrepareSql");

	// Allocate a statement handle
	if (OCIHandleAlloc((dvoid *)ActiveConnection->GetEnvhp(), (dvoid **) &m_stmthp,
		(unsigned int)OCI_HTYPE_STMT, (CONST size_t) 0, (dvoid **) 0))
	{
		DBUG_RETURN(CLError::E_DB_OCI_HDL_ALLOC_STMT);
	}

	// Prepare the statement
	if (OCIStmtPrepare(m_stmthp, ActiveConnection->GetErrhp(), (const OraText *)sqlContext, (unsigned int)strlen((char *)sqlContext),
		(unsigned int) OCI_NTV_SYNTAX, (unsigned int)ActiveConnection->GetOciMode()))
	{
		DBUG_RETURN(CLError::E_DB_SQL_PREPARE);
	}

	if ((iRet = OCIAttrGet(m_stmthp, (unsigned int)OCI_HTYPE_STMT, (unsigned short *)&m_sqlType,
		(unsigned int*) 0, OCI_ATTR_STMT_TYPE, ActiveConnection->GetErrhp())) != 0)
	{
		int oraErrCode =0;
		char oraErrMsg[512];
		GetOraError(&oraErrCode, oraErrMsg);
		DBUG_PRINT("CLCommand::PrepareSql",("OCIAttrGet iRet=[%ld], oraErrCode=[%ld], oraErrMsg=[%s]",
			iRet, oraErrCode, oraErrMsg));
		DBUG_RETURN(CLError::E_DB_OCI_ATTR_GET);
	}

	switch(m_sqlType)
	{
	case OCI_STMT_SELECT :
		{
			m_sqlType = DB_STMT_SELECT;
			break;
		}
	case OCI_STMT_UPDATE :
		{
			m_sqlType = DB_STMT_UPDATE;
			break;
		}
	case OCI_STMT_DELETE :
		{
			m_sqlType = DB_STMT_DELETE;
			break;
		}
	case OCI_STMT_INSERT :
		{
			m_sqlType = DB_STMT_INSERT;
			break;
		}
	case OCI_STMT_CREATE :
		{
			m_sqlType = DB_STMT_CREATE;
			break;
		}
	case OCI_STMT_DROP   :
		{
			m_sqlType = DB_STMT_DROP;
			break;
		}
	case OCI_STMT_ALTER  :
		{
			m_sqlType = DB_STMT_ALTER;
			break;
		}
	case OCI_STMT_BEGIN  :
		{
			m_sqlType = DB_STMT_BEGIN;
			break;
		}
	case OCI_STMT_DECLARE:
		{
			m_sqlType = DB_STMT_DECLARE;
			break;
		}
	default:
		{
			DBUG_PRINT("CLCommand::PrepareSql",("OCI_ATTR_STMT_TYPE[%d]", m_sqlType));
			DBUG_RETURN(CLError::E_DB_SQL_UNKNOWN);
		}
	}
	DBUG_PRINT("CLCommand::PrepareSql",("OCI_ATTR_STMT_TYPE[%d][%s]", m_sqlType, sqlContext));

	//得到绑定变量的数量
	/*
	int i, j, sl;
	sb4 found;
	OraText bvnp[1][256]; // a place holder must be less than 256 bytes...
	ub1 bvnl[1];
	OraText invp[1][256];
	ub1 inpl[1];
	ub1 dupl[1];
	OCIBind* hndl[1];

	iRet = OCIStmtGetBindInfo (m_stmthp, ActiveConnection->GetErrhp(), 1, 1, &found,
				      (OraText**)bvnp, bvnl, (OraText**)invp, inpl, dupl, hndl);
	if ((iRet != 0) && (iRet != OCI_NO_DATA))
	{
		int oraErrCode =0;
		char oraErrMsg[512];
		GetOraError(&oraErrCode, oraErrMsg);
		DBUG_RETURN(CLError::E_DB_GET_BIND);
	}
	*/

	DBUG_RETURN(0);
}


CLCommand* CLCommand::I(const char* data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::I const char*");
	SetInParameter (DT_PUB1, dataLength, (void*)data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::I(const char& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::I const char&");
	SetInParameter (DT_UB1, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::I(const unsigned short& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::I const unsigned short&");
	SetInParameter (DT_UB2, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::I(const unsigned int& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::I const unsigned int&");
	SetInParameter (DT_UB4, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::I(const unsigned long& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::I const unsigned long&");
	SetInParameter (DT_UB8, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::I(const float& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::I const float&");
	SetInParameter (DT_FLOAT, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::I(const double& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::I const double&");
	SetInParameter (DT_DOUBLE, dataLength, (void*)&data);
	DBUG_RETURN(this);
}


CLCommand* CLCommand::O(char* data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::O const char*");
	SetOutParameter (DT_PUB1, dataLength, (void*)data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::O(char& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::O const char&");
	SetOutParameter (DT_UB1, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::O(unsigned short& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::O const unsigned short&");
	SetOutParameter (DT_UB2, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::O(unsigned int& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::O const unsigned int&");
	SetOutParameter (DT_UB4, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::O(unsigned long& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::O const unsigned long&");
	SetOutParameter (DT_UB8, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::O(float& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::O const float&");
	SetOutParameter (DT_FLOAT, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand* CLCommand::O(double& data, unsigned int dataLength) throw(CLException)
{
	DBUG_ENTER("CLCommand::O const double&");
	SetOutParameter (DT_DOUBLE, dataLength, (void*)&data);
	DBUG_RETURN(this);
}

CLCommand& CLCommand::operator<<(const unsigned char &cVal) throw(CLException)
{
	SetInParameter (DT_UB1, sizeof(cVal), (void*)&cVal);
	return *this;
}

//字符串的长度为字符串中空字符之前的长度
CLCommand& CLCommand::operator<<(const char* psVal) throw(CLException)
{
	SetInParameter (DT_PUB1, (long)strlen(psVal), (void*)psVal);
	return *this;
}

//字符串的长度为字符串中空字符之前的长度
CLCommand& CLCommand::operator<<(const unsigned char* psVal) throw(CLException)
{
	SetInParameter (DT_PUB1, (long)strlen((const char*)psVal), (void*)psVal);
	return *this;
}

CLCommand& CLCommand::operator<<(const int &iVal) throw(CLException)
{
	SetInParameter (DT_UB4, sizeof(iVal), (void*)&iVal);
	return *this;
}

CLCommand& CLCommand::operator<<(const float &fVal) throw(CLException)
{
	SetInParameter (DT_FLOAT, sizeof(fVal), (void*)&fVal);
	return *this;
}

CLCommand& CLCommand::operator<<(const double &dVal) throw(CLException)
{
	SetInParameter (DT_DOUBLE, sizeof(dVal), (void*)&dVal);
	return *this;
}

CLCommand& CLCommand::operator<<(const short int &siVal) throw(CLException)
{
	SetInParameter (DT_UB2, sizeof(siVal), (void*)&siVal);
	return *this;
}

CLCommand& CLCommand::operator<<(const unsigned int &uiVal) throw(CLException)
{
	SetInParameter (DT_UB4, sizeof(uiVal), (void*)&uiVal);
	return *this;
}

CLCommand& CLCommand::operator<<(const long int &lVal) throw(CLException)
{
	SetInParameter (DT_UB8, sizeof(lVal), (void*)&lVal);
	return *this;
}

//字符串的长度由数据库求得。
CLCommand& CLCommand::operator>>(char* psVal) throw(CLException)
{
	SetOutParameter (DT_PUB1, -1, (void*)psVal);
	return *this;
}

//字符串的长度由数据库求得。
CLCommand& CLCommand::operator>>(unsigned char* psVal) throw(CLException)
{
	SetOutParameter (DT_PUB1, -1, (void*)psVal);
	return *this;
}

CLCommand& CLCommand::operator>>(int& iVal) throw(CLException)
{
	SetOutParameter (DT_UB4, sizeof(iVal), (void*)&iVal);
	return *this;
}

CLCommand& CLCommand::operator>>(float& fVal) throw(CLException)
{
	SetOutParameter (DT_FLOAT, sizeof(fVal), (void*)&fVal);

	return *this;
}

CLCommand& CLCommand::operator>>(double& dVal) throw(CLException)
{
	SetOutParameter (DT_DOUBLE, sizeof(dVal), (void*)&dVal);

	return *this;
}

CLCommand& CLCommand::operator>>(short int& siVal) throw(CLException)
{
	SetOutParameter (DT_UB2, sizeof(siVal), (void*)&siVal);
	return *this;
}

CLCommand& CLCommand::operator>>(unsigned int& iVal) throw(CLException)
{
	SetOutParameter (DT_UB4, sizeof(iVal), (void*)&iVal);
	return *this;
}

CLCommand& CLCommand::operator>>(long int& lVal) throw(CLException)
{
	SetOutParameter (DT_UB8, sizeof(lVal), (void*)&lVal);

	return *this;
}


