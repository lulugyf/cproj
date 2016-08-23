#ifndef __CLShmDriver_h__
#define __CLShmDriver_h__

#define	SHMKDIR		"sDBLogin.cfg"
#define SHMKEY		1
 
class CLShmDriver :public CLDriver
{
public:
	CLShmDriver()
	{
		
	}
	//�������Ͷ������
	virtual TDriverType GetDriverType() const;
	
	
	static ETYPE	GetDbShmKey(key_t *kid);
	
	// �ӹ����ڴ���ȡ���� 
	static ETYPE GetDbShm(TComShm **shmp);

	// �Ͽ������ڴ������ݽṹ������
	static ETYPE DetachShm(const void *shmp);
private:
};

#endif //__CLShmDriver_h__
