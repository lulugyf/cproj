#include <pub.h>
#include<string>

extern "C" void desenc(const char *src, char* dst, size_t len);//加密
//dst的空间长度len应为(strlen(src)+8)*2+1

extern "C" void desdec(const char *src, char* dst, size_t len);//解密
//dst的空间长度len应为src字符串长度+1

int Create_MD5_Cluster(const char *p_chKey,const char *p_chGene,int nGene,char  *MD5_str);
//MD5加密算法

/*
功能：
	对于DES加解密函数的封装
	整合加密和解密函数
	自动判断解密字符串长度
	输入参数和输出参数均为UTYPE类型，以便服务开通发送程序可以使用。

输入参数:
	└-1 OP_TYPE		string 操作类型（E加密；D解密）
	├-2 SRC  		string 源字符串
输出参数:
	└-1 DATA
	  ├-1.1 PPS_PWD  	string 处理后的字符串
*/
extern "C" utype * UserPassUtype( const utype* inparam, TCtrlInfo *errInfo)
{
	L4C_DEBUG("in UserPassUtype...");
	
	string op_type=utGetStr(inparam,"OP_TYPE");
	string src=utGetStr(inparam,"SRC");
	size_t len=0;
	
	uAutoPtr uapOutMsg(uInit(1));
	char *temp=NULL;
	
	if(op_type=="E")//加密
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
	else if(op_type=="D")//解密
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
	else //操作类型错误
	{
		L4C_ERROR("UserPassUtype,操作类型错误");
		return uapOutMsg.release();
	}
	
	L4C_DEBUG("out UserPassUtype...");
	return uapOutMsg.release();
}

/*
功能：
    对于MD5加解密函数的封装
    输入参数和输出参数均为UTYPE类型，以便服务开通发送程序可以使用。

输入参数:
    └-1 SEQ        string 源字符串1
    ├-2 SIDNAME    string 源字符串2
    ├-3 SIDLEN     string 源字符串2长度
	
输出参数:
    └-1 DATA
      ├-1.1 PPS_PWD    string 处理后的字符串
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
