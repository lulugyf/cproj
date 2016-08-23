#ifndef __CLDriver_h__
#define __CLDriver_h__

//�������Ͷ���
enum TDriverType
{
	DRIVER_NONE			= -1,//û����������
	DRIVER_DATABASE		= 0,//���ݿ���������
	DRIVER_FILE			= 1,//�ļ���������
	DRIVER_SHM			= 2,//�����ڴ���������
	DRIVER_MQ			= 3,//MQ��������
	DRIVER_ZDB			= 4 //ѹ�����ݿ���������
};

/*
 ��������Ļ��ඨ�壬Ϊ�����࣬���붨�����࣬ʵ�������ĸ��ֲ�����
 */
class CLDriver :public CLLayer
{
public:
	virtual TLayerNo GetLayerNo() const;

	//�������Ͷ������
	virtual TDriverType GetDriverType() const = 0;
};

#endif //__CLDriver_h__
