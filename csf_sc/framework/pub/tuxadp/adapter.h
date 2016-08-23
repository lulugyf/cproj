
#include <iostream>
#include <string>
#include <map>

using namespace std;

#include <utype.h>

utype* doMerge(map<string, void*>* m, TCtrlInfo* errInfo);

typedef utype* (*TDoMerge)(map<string, void*>* m, TCtrlInfo* errInfo);


/**
 * ��������ں���
 * @inparam    obuf             �������ָ��
 * @inparam    obufLen          ������ݳ���
 * @inparam    psServiceName	��������
 * @inparam    inputstr			��δ���xml �� json
 * @inparam    clientaddr       �����Ĳ������ͻ��˵�ַ, ����Ϊ NULL
 * @inparam    psDbLabel		���ݿ����ӱ�ǩ
 * @inparam    psUtypeFunc		utype��������
 * @inparam    ptUtypeFuncPtr	utype������ַ
 * @inparam    ptDoMerge	         ����ϲ��ص������� ����ΪNULL�� ��ʹ��Ĭ�ϵ� doMerge
 * @inparam    iConnType		���ݿ����ӷ�ʽ,1������,0������
 */
void adpt_entry(char **obuf,        //����, ��Ҫ�ⲿ�ͷ����ڴ�ռ�
		int* obufLen,              //���γ���
		const char *psServiceName, //��������
		char *inputstr,    //��δ���xml �� json
		char *clientaddr,  //�����Ĳ������ͻ��˵�ַ, ����Ϊ NULL
		const char *psDbLabel,     //���ݿ����ӱ�ǩ
		const char *psUtypeFunc,   // BP/BC ������
		TUtypeFuncPtr ptUtypeFuncPtr, // BP/BC �ĺ���ָ��
		TDoMerge ptDoMerge,   //����ϲ��ص������� ����ΪNULL�� ��ʹ��Ĭ�ϵ� doMerge
		int iConnType         //���ݿ��������ͣ�  1-������  0-������
		);


//�򻯰汾�ĺ���,  �� dotuxadp �Ĳ������£�
//1. ���Զ���ϲ������������ʹ���Դ��ģ�����һ����Σ�
//2. ������ҵ�����doRule��
//3. �����ý��������Powerfilter
//4. ��ȫ��ʹ���ڴ����ݿ�
void adpt_entry1(
		char **obuf,
		int* obufLen,
		const char *psServiceName,
		char *inputstr,
		char *clientaddr,
		const char *psDbLabel,
		const char *psUtypeFunc,
		TUtypeFuncPtr ptUtypeFuncPtr,
		int iConnType
		);
