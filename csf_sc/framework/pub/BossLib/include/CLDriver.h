#ifndef __CLDriver_h__
#define __CLDriver_h__

//驱动类型定义
enum TDriverType
{
	DRIVER_NONE			= -1,//没有驱动类型
	DRIVER_DATABASE		= 0,//数据库驱动类型
	DRIVER_FILE			= 1,//文件驱动类型
	DRIVER_SHM			= 2,//共享内存驱动类型
	DRIVER_MQ			= 3,//MQ驱动类型
	DRIVER_ZDB			= 4 //压缩数据库驱动类型
};

/*
 驱动器层的基类定义，为抽象类，必须定义子类，实现驱动的各种操作。
 */
class CLDriver :public CLLayer
{
public:
	virtual TLayerNo GetLayerNo() const;

	//驱动类型定义代码
	virtual TDriverType GetDriverType() const = 0;
};

#endif //__CLDriver_h__
