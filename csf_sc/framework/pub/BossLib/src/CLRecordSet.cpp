#include "llayerStruct.h"


CLRecordSet::CLRecordSet()  :
	m_iColumnCount(0)
{
	ActiveCommand = NULL;
	ActiveConnection = NULL;
}

CLRecordSet::~CLRecordSet()
{
}

TDriverType CLRecordSet::GetDriverType() const
{
	return DRIVER_DATABASE;
}

//��ǰ��¼������¼����λ�á�
ETYPE CLRecordSet::GetCurrentPosition(ub4* currentPosition) const  throw()
{
	ETYPE iRet;
	DBUG_ENTER("CLRecordSet::GetCurrentPosition");
	iRet = OCIAttrGet(ActiveCommand->GetStmthp(), (ub4)OCI_HTYPE_STMT, (dvoid *)currentPosition,
		(ub4*) 0, OCI_ATTR_CURRENT_POSITION, ActiveConnection->GetErrhp());
	DBUG_RETURN(iRet);
}

//�õ�select��䷵�ص�������
ETYPE CLRecordSet::SetColomnCount() throw()
{
	ETYPE iRet;
	DBUG_ENTER("CLRecordSet::SetColomnCount");
	iRet = OCIAttrGet(ActiveCommand->GetStmthp(), (ub4)OCI_HTYPE_STMT, (dvoid *)&m_iColumnCount,
		(ub4*) 0, OCI_ATTR_PARAM_COUNT, ActiveConnection->GetErrhp());
	DBUG_RETURN(iRet);
}

//�õ�select��䷵�ص�������
ub4 CLRecordSet::GetColomnCount() throw()
{
	return m_iColumnCount;
}

////�õ���ĿǰΪֹ���Ѿ����ص�������
ETYPE CLRecordSet::GetRowCount(ub4* rowCount) const  throw()
{
	DBUG_ENTER("CLRecordSet::GetRowCount");
	if (OCIAttrGet(ActiveCommand->GetStmthp(), (ub4)OCI_HTYPE_STMT, (dvoid *)rowCount,
		(ub4*) 0, OCI_ATTR_ROW_COUNT, ActiveConnection->GetErrhp()) != 0)
	{
		DBUG_RETURN(CLError::E_DB_GET_ROW_COUNT);
	}
	else
	{
		DBUG_RETURN(0);
	}
}

//�õ�Fetch��䷵�ص�������
ETYPE CLRecordSet::GetRowFetched(ub4* rowFetched) const  throw()
{
	DBUG_ENTER("CLRecordSet::GetRowFetched");
	if (OCIAttrGet(ActiveCommand->GetStmthp(), (ub4)OCI_HTYPE_STMT, (dvoid *)rowFetched,
		(ub4*) 0, OCI_ATTR_ROWS_FETCHED, ActiveConnection->GetErrhp()) != 0 )
	{
		DBUG_RETURN(CLError::E_DB_GET_FETCHED_COUNT);
	}
	else
	{
		DBUG_RETURN(0);
	}
}

//ȡ����һ����¼
ETYPE CLRecordSet::FetchNext(ub4 iRowCount) throw()
{
	ETYPE iRet=0;
	register ub4 i, j;
	DBUG_ENTER("CLRecordSet::FetchNext");

	if ( (iRet = OCIStmtFetch(ActiveCommand->GetStmthp(), ActiveConnection->GetErrhp(),
		(ub4) iRowCount, (ub4) OCI_FETCH_NEXT, (ub4)ActiveConnection->GetOciMode())) != 0)
	{
		if (iRet == OCI_NO_DATA)
		{
			DBUG_RETURN(CLError::E_DB_SQL_FETCH_NODATA);
		}
		else
		{
			DBUG_RETURN(CLError::E_DB_SQL_FETCH);
		}
	}

	//�����ַ��������һ���ַ�Ϊ���ַ���
	for(i = 0; i < this->GetColomnCount(); i ++)
	{
		if (ActiveCommand->GetOutParameters().at(i)->Type == DT_PUB1)
		{
			for (j = 0; j < iRowCount; j ++)
			{
				ActiveCommand->GetOutParameters().at(i)->Value.p1Val[(ActiveCommand->GetOutParameters().at(i)->Size) * (j+1)-1] = '\0';
			}
		}
	}
	DBUG_RETURN(iRet);
}

//�õ��ֶ���Ϣ
vector <CLParameter*>& CLRecordSet::GetFields() throw()
{
	return ActiveCommand->GetOutParameters();
}

const void* CLRecordSet::GetField(ub4 columnIndex, ub4 rowIndex) throw()
{
	return (((const char*)ActiveCommand->GetOutParameters().at(columnIndex)->Value.pVal) + rowIndex * (ActiveCommand->GetOutParameters().at(columnIndex)->Size));
}

const char* CLRecordSet::GetFieldName(ub4 columnIndex) throw()
{
	return ActiveCommand->GetOutParameters().at(columnIndex)->Name;
}

