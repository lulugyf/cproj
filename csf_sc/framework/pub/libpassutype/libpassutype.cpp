#include <pub.h>
#include<string>

extern "C" void desenc(const char *src, char* dst, size_t len);//����
//dst�Ŀռ䳤��lenӦΪ(strlen(src)+8)*2+1

extern "C" void desdec(const char *src, char* dst, size_t len);//����
//dst�Ŀռ䳤��lenӦΪsrc�ַ�������+1

int Create_MD5_Cluster(const char *p_chKey,const char *p_chGene,int nGene,char  *MD5_str);
//MD5�����㷨

/*
���ܣ�
	����DES�ӽ��ܺ����ķ�װ
	���ϼ��ܺͽ��ܺ���
	�Զ��жϽ����ַ�������
	������������������ΪUTYPE���ͣ��Ա����ͨ���ͳ������ʹ�á�

�������:
	��-1 OP_TYPE		string �������ͣ�E���ܣ�D���ܣ�
	��-2 SRC  		string Դ�ַ���
�������:
	��-1 DATA
	  ��-1.1 PPS_PWD  	string �������ַ���
*/
extern "C" utype * UserPassUtype( const utype* inparam, TCtrlInfo *errInfo)
{
	L4C_DEBUG("in UserPassUtype...");
	
	string op_type=utGetStr(inparam,"OP_TYPE");
	string src=utGetStr(inparam,"SRC");
	size_t len=0;
	
	uAutoPtr uapOutMsg(uInit(1));
	char *temp=NULL;
	
	if(op_type=="E")//����
	{
		len=(src.length()+8)*2+1;
		temp=(char*)malloc(len);
		desenc(src.c_str(),temp, len);
		L4C_TRACE("UserPassUtype,PPS_PWD=[%s]", temp);
		uAutoPtr uTemp(uInit(1));
		utAddStr(uTemp, "PPS_PWD",temp);
		utAddStruct(uapOutMsg,"DATA",uTemp.release());
		free(temp);
	}
	else if(op_type=="D")//����
	{
		len=src.length()+1;
		temp=(char*)malloc(len);
		desdec(src.c_str(),temp, len);
		L4C_TRACE("UserPassUtype,PPS_PWD=[%s]", temp);
		uAutoPtr uTemp(uInit(1));
		utAddStr(uTemp, "PPS_PWD",temp);
		utAddStruct(uapOutMsg,"DATA",uTemp.release());
		free(temp);
	}
	else //�������ʹ���
	{
		L4C_ERROR("UserPassUtype,�������ʹ���");
		return uapOutMsg.release();
	}
	
	L4C_DEBUG("out UserPassUtype...");
	return uapOutMsg.release();
}

/*
���ܣ�
    ����MD5�ӽ��ܺ����ķ�װ
    ������������������ΪUTYPE���ͣ��Ա����ͨ���ͳ������ʹ�á�

�������:
    ��-1 SEQ        string Դ�ַ���1
    ��-2 SIDNAME    string Դ�ַ���2
    ��-3 SIDLEN     string Դ�ַ���2����
	
�������:
    ��-1 DATA
      ��-1.1 PPS_PWD    string �������ַ���
*/
extern "C" utype * MD5PassUtype(const utype* inparam, TCtrlInfo *errInfo)
{
	L4C_DEBUG("in MD5PassUtype...");

	LogUtype(inparam);

	string seq = utGetStr(inparam,"SEQ");
	string sid_name = utGetStr(inparam, "SIDNAME");
	int sid_len = utGetInt(inparam, "SIDLEN");

	char MD5_Str[256];
	memset(MD5_Str, 0, sizeof(MD5_Str));
	Create_MD5_Cluster(seq.c_str(), sid_name.c_str(), sid_len, MD5_Str);

	uAutoPtr uTemp(uInit(1));
	uAutoPtr uapOutMsg(uInit(1));
	utAddStr(uTemp, "sidpwd", MD5_Str);
	utAddStruct(uapOutMsg, "DATA", uTemp.release());

	LogUtype(uapOutMsg);
	L4C_DEBUG("out MD5PassUtype...");
	return uapOutMsg.release();
}

extern "C" utype * UniveralPassUtype(const utype * inparam, TCtrlInfo * errInfo)
{
        uAutoPtr ret(pubEncryptPasswd(inparam, errInfo));
        return ret.release();
}
