#pragma once
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include "utype.h"
/**
 * < summary>
 *     LOG_FUNC��Ϊ�궨������ƣ���ɺ�����ͳһ��־��ӡ���˺궨���ڲ����ȡ__FILE__��__FUNCTION__��__LINE__�����궨�壬
 * �õ�������λ����Ϣ���˺궨���ʹ�÷����������£�
 *        utype* ExampleFunc(const utype *puInParam, TCtrlInfo * pErrorInfo)
 *        {
 *                LOG_FUNC(puInParams, pErrorInfo, NULL);	//���Ӵ�����Ϣ��
 *                ���� //��������Ϣ��
 *        }
 *</summary>
 *<param name=�� psKeyWord�� type=��const char*��>�����ؼ��֣�������"BP"��"BC"�ȡ�</param >
 *<param name=�� puInParams�� type=��utype*��>ҵ��������������Ϊ��չ����ʹ��</param >
 *<param name=�� pErrorInfo�� type=��TCtrlInfo*��>
 *    ���������Ϣ����Ϊ�Ժ����չ����ʹ�á�
 *</param >
 *<param name=�� pLogFileHandle�� type=��FILE*��>��ӡ�ĺ��������Ĭ����NULL��</param >
 */
#ifndef LOG_FUNC
#define LOG_FUNC(psKeyWord,puInParams, pErrorInfo, pLogFileHandle) \
	LogFunc __logFunc(psKeyWord, puInParams, pErrorInfo, pLogFileHandle, __FILE__, __FUNCTION__, __LINE__)
#define LOG_FUNC_BP() LOG_FUNC("BP", NULL, NULL, NULL)
#define LOG_FUNC_BC() LOG_FUNC("BC", NULL, NULL, NULL)
#endif

class LogFunc
{
public:
	/**
	 *<summary>��־���캯��</summary>
	 */
	LogFunc(const char *psKeyWord, const void *pInParam, const void * pErrorInfo, FILE *pLogFileHandle,
		const char *psFile, const char *psFunc, unsigned int iLine);

	/**
	 *<summary>��־��������</summary>
	 */
	~LogFunc();
public:
	const char *m_psKeyWord;//���Թ��캯��
	const void *m_pInParam;	//���Թ��캯��
	const void *m_pErrorInfo;	//���Թ��캯��
	FILE *m_pLogFileHandle;		//��ӡ�����ļ����,NULL����׼�����
	const char *m_psFile;	//���Թ��캯��
	const char *m_psFunc;	//���Թ��캯��
	unsigned int m_iLine;	//���Թ��캯��

	unsigned int m_iCurrentDeep;	//��ǰ��ȡ�

	//��չ��Ϣ��������LogFunc����չʹ�ô���Ϣ���Ա�֤�޸Ķ�̬���ӿ⣬�������޸Ĵ�ͷ�ļ���
	void* m_pvExternInfo;
private:
	/**
	 *<summary>��ֹʹ��Ĭ�Ϲ��캯��</summary>
	 */
	LogFunc()
	{
	}
};

typedef struct tagOprInfo
{
	char sServiceNo[100+1];	//�������
	char sLoginNo[20+1];	//����
	char sOpCode[8+1];	//��������
	char sContactId[127+1];	//�ͻ��Ӵ�ID
	char sLoginAccept[127+1];	//������ˮ
}TOprInfo;

/**
 *    ��ʼ��������Ϣ
 */
void GlobalInitOprInfo(TOprInfo &tOprInfo);

int NMLogCallBack(
	const char *psServiceName,		//��������
	TCtrlInfo *ptCtrlInfo,			//����Ӫҵ����ȡ
	const char *psDbLabel,			//���ݿ��ǩ����
	const char *psUtypeFunc,		//�������BP����
	const utype *pu_in,				//�������Utype
	struct timeval *tp_begin,		//������ÿ�ʼʱ��
	const int retCode,              //���񷵻ش���
	const char *retMsg              //���񷵻���Ϣ
	);
	
	
void GlobalBusiInit(const char *psServiceName,		//��������
	const char *psDbLabel,							//���ݿ��ǩ����
	const char *psUtypeFunc,						//�������BP����
	const utype *pu_in								//�������Utype
	);
