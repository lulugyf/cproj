#ifndef __CLRecordSet_h__
#define __CLRecordSet_h__

class CLRecordSet :	public CLDriver
{
public:
	CLRecordSet();
	~CLRecordSet();
	
	//�������Ͷ������
	virtual TDriverType GetDriverType() const;
public:
	//��ǰ���������
	CLConnection *ActiveConnection;

	//��ǰ���������
	CLCommand *ActiveCommand;
public:
	//��ǰ��¼������¼����λ�á�
	ETYPE GetCurrentPosition(ub4* currentPosition) const throw();

	//�õ�select��䷵�ص�������
	ub4 GetColomnCount() throw();

	//�õ���ĿǰΪֹ���Ѿ����ص�������
	ETYPE GetRowCount(ub4* rowCount) const  throw();

	//�õ�Fetch��䷵�ص�������
	ETYPE GetRowFetched(ub4* rowFetched) const  throw();

	//�õ�select��䷵�ص��������ڲ��á�
	ETYPE SetColomnCount() throw();

	//ȡ����һ����¼
	ETYPE FetchNext(ub4 iRowCount=1) throw();

	//�õ��ֶ���Ϣ
	vector <CLParameter*>& GetFields() throw();

	//�õ��ֶ�ֵ

	const void* GetField(ub4 columnIndex, ub4 rowIndex) throw();
	const char* GetFieldName(ub4 columnIndex) throw();
private:

	ub4 m_iColumnCount;
};


#endif//__CLRecordSet_h__
