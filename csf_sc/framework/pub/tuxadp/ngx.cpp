#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <alloca.h>
#include <dlfcn.h>



#include "framework.h"

#include "adapter.h"



//#include <map>
//using namespace std;
//utype* doRule(const char* svc_name, const utype* puParamIn, TCtrlInfo* errInfo, string& sPromptMsg);
//void* busiwork(void* v1, db_connect* pdb, bool isLong);
//utype* doMerge(map<string, void*>* m, TCtrlInfo* errInfo);


//static const char *input = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><ROOT><route_code type=\"int\">100</route_code><route_value type=\"string\">13581595848</route_value><ROUTE_TYPE type=\"int\">10</ROUTE_TYPE><ROUTE_VALUE type=\"string\">15205500</ROUTE_VALUE></ROOT>";


void usage(char *pname)
{
    printf("Usage: %s <bc/bp name> <parameters> [servicename]\n", pname);
    exit(1);
}



char* cfgGetCurrentPatitionsLabel_2(const char* label, char *out)
{
	strcpy(out, label);
	strcat(out, cfgGetCurrentDBPatition());
	return out;
}

char *cfgGetAllPatitionsLabel_2(const char* label, char *out)
{
	char stemp[256];

    //dbchangea1,dbchangeb1
	const char* sIns=cfgGetCurrentDBInstance(); // b1
	const char* sLin=cfgGetStrSlient("MAIN", "ALLDBPATITIONS"); // a,b
	if(sLin[0]==0)
		return cfgGetCurrentPatitionsLabel_2(label, out);

	char* tar=(char*)alloca(strlen(sLin)+1);
	strcpy(tar, sLin);
	char* sDB=tar, *spos;
	spos = sDB;
	strcpy(stemp, "");
	/*sIns ++; */
	while(1){
		spos = strchr(sDB, ',');
		if (strlen(stemp) > 0)
		{
			strcat(stemp, ",");
		}
		if(spos == NULL){
			strcat(stemp, label);
			strcat(stemp, sDB);
			strcat(stemp, sIns);
			break;
		}else{
			*spos = 0;
			strcat(stemp, label);
			strcat(stemp, sDB);
			strcat(stemp, sIns);
			sDB = spos + 1;
		}
	}
	strcpy(out, stemp);
	return out;
}

/*读取服务配置表，获得对应服务的bpname， dblabel, isallpart 参数
 * 成功返回0 */
int readsvc(const char *svcname, const char *servicecfg,
		char *soname, char *bpname, char *dblabel, int *isallpart)
{
	FILE *fp;
	char line[128];
	char cfgservice[64];

	fp = fopen(servicecfg, "r");
	if(fp == NULL){
		return -1;
	}
	while(fgets(line, sizeof(line), fp) != NULL)
	{
		if(line[0] == '#') continue;
		if(sscanf(line, "%s %s %s %s %d", cfgservice, soname, bpname, dblabel, isallpart) != 5)
			continue;
		if(strcmp(cfgservice, svcname) == 0){
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return -2;
}

void *findFunc(void *handle, char *funcname)
{
	char cppfuncname[128], ostype[16];
	void *funcptr;
	funcptr = dlsym(handle, funcname);
	if(funcptr == NULL){
		//try c++ symble
		#if (defined(__hpux))
			sprintf(cppfuncname, "_Z%d%sPK8tagutypeP11tagCtrlInfo", strlen(funcname), funcname);
			strcpy(ostype, "hpux");
		#elif (defined(__sun))
			sprintf(cppfuncname, "__1cM%s6FpknItagutype_pnLtagCtrlInfo__p0_", funcname);
			strcpy(ostype, "sunos");
		#elif (defined(__linux__))
			sprintf(cppfuncname, "_Z%ld%sPK8tagutypeP11tagCtrlInfo", strlen(funcname), funcname);
			strcpy(ostype, "linux");
		#elif (defined(_AIX))
			sprintf(cppfuncname, "%s__FPC8tagutypeP11tagCtrlInfo",  funcname);
			strcpy(ostype, "aix");
		#else
			sprintf(cppfuncname, "_Z%d%sPK8tagutypeP11tagCtrlInfo", strlen(funcname), funcname);
			strcpy(ostype, "other");
		#endif
		printf("finding cppname[%s]\n", cppfuncname);
		funcptr = dlsym(handle, cppfuncname);
	}
	return funcptr;
}

extern "C" char *callservice (
		const char *servicename,
		const char *servicecfg,
		char *request_data,
		int *datalen)
{
	const char *psDbLabel;
	int iConnType = 1;
	int outlen = 0;

	char soname[128], bpname[128], dblabel[128], dbcfg[128];
	int isallpart;

	int rc;

    if( (rc = readsvc(servicename, servicecfg,
    		soname, bpname, dblabel, &isallpart) ) != 0)
    {
    	printf("读取服务配置失败 %d [%s] %s\n", rc, servicename, servicecfg);
    	return NULL;
    }
	if(isallpart){
		psDbLabel = cfgGetAllPatitionsLabel_2(dblabel, dbcfg);
	}else{
		psDbLabel = cfgGetCurrentPatitionsLabel_2(dblabel, dbcfg);
	}

	char clientaddr[128], *addr = NULL;
	char *output = NULL;

	TUtypeFuncPtr func = NULL;
	void *handle = NULL;
	
	printf("soname[%s] psDbLabel[%s] bpname[%s]\n",
			soname, psDbLabel, bpname);
	handle = dlopen(soname, RTLD_NOW);
	if(handle == NULL){
		printf("dlopen[%s] failed [%s]\n", soname, dlerror());
		return NULL;
	}
	func = (TUtypeFuncPtr)findFunc(handle, bpname);
	if(func == NULL){
		printf("can not found function[%s]\n", bpname);
		return NULL;
	}

	adpt_entry(&output, &outlen, servicename,
			request_data, addr,
			psDbLabel, bpname,
			func, NULL, iConnType);

	*datalen = outlen;
	return output;
}

#ifdef __TEST__
//#if 1
int main(int argc, char **argv)
{
	int datalen;
	char *rep;
	const char *svcname = "stestbc";
	const char *svclist = "svc.txt";
	const char *req = "{}";

	if(argc > 3){
		svcname = argv[1];
		svclist = argv[2];
		req = argv[3];
	}

	datalen = strlen(req);
	rep = callservice (svcname, svclist, (char *)req, &datalen);
	if(rep != NULL){
		printf("OUTPUT[%s]\n", rep);
		free(rep);
	}else{
		printf("OUTPUT is NULL\n");
	}
	return 0;
}
#endif

