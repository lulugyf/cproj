#ifndef __CLRight_h__
#define __CLRight_h__
/**
 *  Ȩ�޹�����
 */
extern "C" ETYPE CheckFuncRight(const char *loginNo, const char *opCode);

//����м�Ȩ��
//    ��Ȩ�޷����㣬���򷵻ط���
extern "C" ETYPE CheckColumnRight(const char *loginNo, ub8 columnId);

class CLRight : public CLBase
{
public:
	//��鹦��Ȩ��
	//loginPasswd���ܺ������
	static ETYPE CheckFuncPwdRight(const char *loginNo,
		const char *loginPasswd, const char *opCode) throw();

	//����м�Ȩ��
	//    ��Ȩ�޷����㣬���򷵻ط���
	static inline ETYPE CheckColumnRight(const char *loginNo, ub8 columnId)
	{
		return ::CheckColumnRight(loginNo, columnId);
	}
};

#endif //__CLRight_h__
