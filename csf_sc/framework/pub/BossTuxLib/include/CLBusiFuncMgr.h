#ifndef __CLBusiFuncMgr_h__
#define __CLBusiFuncMgr_h__

#define RULE_TYPE_MANUS		0	//手工
#define RULE_TYPE_SQL		1	//SQL
#define RULE_TYPE_TUXEDO	2	//TUXEDO函数
#define RULE_TYPE_FUNCTION	3	//普通C函数

class CLBusiFuncParam
{
public:
	CLBusiFuncParam() :
		m_param(NULL)
	{
	}

	~CLBusiFuncParam()
	{
		ClearParam();
	}
	void ClearParam()
	{
		if (m_param)
		{
			uFree(m_param);
			m_param = NULL;
		}
	}

	utype *GetParam()
	{
		return m_param;
	}
	utype **GetParamAddr()
	{
		return &m_param;
	}
public:
	ETYPE Init(int cnt)
	{
		ClearParam();
		m_param = uInit(cnt);
		if (!m_param)
			return CLError::E_MEMORY_LACK;
		return 0;
	}

	ETYPE SetInt(int occ,int iv)
	{
		if (uSetInt(m_param, occ, iv) == NULL)
		{
			return CLError::E_MEMORY_LACK;
		}
		return 0;
	}

	int GetInt(int occ)
	{
		return uGetInt(m_param, occ);
	}

	ETYPE SetLong(int occ,long iv)
	{
		if (uSetLong(m_param, occ, iv) == NULL)
		{
			return CLError::E_MEMORY_LACK;
		}
		return 0;
	}

	long GetLong(int occ)
	{
		return uGetLong(m_param, occ);
	}

	ETYPE SetDouble(int occ,double iv)
	{
		if (uSetDouble(m_param, occ, iv) == NULL)
		{
			return CLError::E_MEMORY_LACK;
		}
		return 0;
	}

	double GetDouble(int occ)
	{
		return uGetDouble(m_param, occ);
	}

	ETYPE SetStr(int occ,const char * iv)
	{
		if (uSetStr(m_param, occ, iv) == NULL)
		{
			return CLError::E_MEMORY_LACK;
		}
		return 0;
	}

	char * GetStr(int occ)
	{
		return uGetStr(m_param, occ);
	}

	ETYPE SetArray(int occ,utype * iv)
	{
		if (uSetArray(m_param, occ, iv) == NULL)
		{
			return CLError::E_MEMORY_LACK;
		}
		return 0;
	}

	utype * GetArray(int occ)
	{
		return (utype*)uGetArray(m_param, occ);
	}

	ETYPE SetStruct(int occ,utype * iv)
	{
		if (uSetStruct(m_param, occ, iv) == NULL)
		{
			return CLError::E_MEMORY_LACK;
		}
		return 0;
	}

	utype* GetStruct(int occ)
	{
		return (utype*)uGetStruct(m_param, occ);
	}
private:
	utype *m_param;
};

//utype的管理类
class CLBusiFuncMgr
{
public:
	CLBusiFuncMgr() :
		m_FuncBusiness(NULL),m_ruleType(RULE_TYPE_FUNCTION)
	{
		memset(&m_ctrlInfo, 0, sizeof(m_ctrlInfo));
	}

	~CLBusiFuncMgr()
	{
	}

	CLBusiFuncParam& GetInParam()
	{
		return m_inParam;
	}

	CLBusiFuncParam& GetOutParam()
	{
		return m_outParam;
	}

	void ClearParams()
	{
		m_inParam.ClearParam();
		m_outParam.ClearParam();
	}
	
	TCtrlInfo *GetCtrlInfo()
	{
		return &m_ctrlInfo;
	}

	void SetFuncAddr(TFuncBusiness FuncBusiness)
	{
		m_FuncBusiness = FuncBusiness;
	}

	ETYPE Execute()
	{
		DBUG_ENTER("Execute");

		DBUG_RETURN( m_FuncBusiness(m_inParam.GetParam(), m_outParam.GetParamAddr(), &m_ctrlInfo));
	}
private:
	//参数编码
	CLBusiFuncParam m_inParam;

	//参数编码
	CLBusiFuncParam m_outParam;

	TCtrlInfo m_ctrlInfo;

	TFuncBusiness m_FuncBusiness;

	//规则类型
	ub4 m_ruleType;

};

#endif//__CLBusiFuncMgr_h__

