#ifndef __CLLayer_h__
#define __CLLayer_h__

//�㶨��
enum TLayerNo
{
	//����Э���
	LAYER_DRIVER		= 0,
	
	//ԭ������Э���
	LAYER_ATOM			= 1,

	//�߼�����Э���
	LAYER_LOGICDATA		= 2,

	//ҵ���߼�Э���
	LAYER_BUSINESS		= 3,

	//Ӧ���߼�Э���
	LAYER_APPLICATION	= 4
};

class CLLayer :public CLBase
{
public:
	//�õ���˾����
	virtual TLayerNo GetLayerNo() const = 0;
};

#endif //__CLLayer_h__
