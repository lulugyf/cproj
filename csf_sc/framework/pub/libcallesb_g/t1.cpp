#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

#include <string>
#include "utype.h"

utype* pCallESBApi(const utype * inParam, const char *service_name, const char *route_key, const char * route_value, \
                         int call_type, int conn_timeout, int recv_timeout);

int main1()
{
    //�Է�������ѹ�� �۲�˳�����ڴ��������;

	uAutoPtr uptr_1(uInit(0));
	utAddStr(uptr_1, "PHONE_NO", "15799881753");
	utAddStr(uptr_1, "TEST", "���Ĳ���");
	uAutoPtr uptr_2(uInit(0));
	try
	{
		/* ��Ҫ��·��ֵ������ */
		uptr_2 = pCallESBApi(uptr_1, "sCustInfoValid", "10", "15799881753", 1, 2, 3);
		char *xmlstr = uUType2Xml(uptr_2,"ROOT");
		printf("���÷���ķ��ؽ��Ϊ:%s\n", xmlstr);
		free(xmlstr);
		xmlstr = NULL;

		/* ����Ҫ��·��ֵ�����
		uptr_2 = pCallESBApi(uptr_1, "sCustInfoValid", NULL, "", 0, 5 3);
		char *xmlstr = uUType2Xml(uptr_2,"ROOT");
		printf("���÷���ķ��ؽ��Ϊ:%s\n", xmlstr);
		free(xmlstr);
		xmlstr = NULL;
		*/
	}
	catch (appException& appErr)
	{
		printf("������÷����쳣 appException : %s\n", appErr.what());
	}
	catch (std::exception& err)
	{
		printf("������÷����쳣 exception : %s\n", err.what());
	}
	catch(...)
	{
		printf("������÷����쳣\n");
	}

	return 0;
}


utype * json2utype(const char *str);
char * utype2json(const utype *pu);

int main(int argc, char *argv[])
{
	const char *svc_name = argv[1];
	const char *input = argv[2];
	const char *route_key = argv[3];
	const char *route_value = argv[4];

	uAutoPtr uptr_1(json2utype(input));

	uAutoPtr uptr_2(uInit(0));
	try
	{
		/* ��Ҫ��·��ֵ������ */
		uptr_2 = pCallESBApi(uptr_1, svc_name, route_key, route_value, 0, 5, 3);
		char *outstr = utype2json(uptr_2);
		printf("���÷���ķ��ؽ��Ϊ:%s\n",  outstr);
		free(outstr);
	}
	catch (appException& appErr)
	{
		printf("������÷����쳣 appException : %s\n", appErr.what());
	}
	catch (std::exception& err)
	{
		printf("������÷����쳣 exception : %s\n", err.what());
	}
	catch(...)
	{
		printf("������÷����쳣\n");
	}

	return 0;
}
