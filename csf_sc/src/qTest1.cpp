#include <allBCP.h>


utype* pMyTest1(const utype * inParam,TCtrlInfo *errInfo);

utype * json2utype(const char *str);
char * utype2json(const utype *pu);
char * utype2json(const utype *pu, const char *arrPath);

int main(int argc, char *argv[])
{
	char dblabel[64];
	long retCode;
	char retMsg[2048];
	
	if(argc < 2){
		printf("give me a parameter\n");
		return 0;
	}
	
	uAutoPtr inParam;
	strcpy(dblabel, LABELDBCHANGE);
	
	inParam = uXml2Utype(argv[1]); //json2utype(argv[1]);
	if(inParam.get() == NULL){
		printf("invalide json, return\n");
		return 1;
	}
	
	memset(retMsg, 0, sizeof(retMsg));
	try{
		printf("----dblabel[%s]\n", dblabel);
		uAutoPtr u1(
			AssiMutiConnWork(inParam, NULL,
				pMyTest1, doMerge, dblabel, 0)
			);
			
		char *out = utype2json(u1);
		printf("OUT[%s]\n", out);
		free(out);
	} catch (uException& err) {
		retCode = 303 * 1000000 + err.errCode;
		strcpy(retMsg, err.errMsg);
	} catch (otl_exception& otlErr) { // intercept OTL exceptions
		retCode = 302 * 1000000 + abs(otlErr.code);
		memset(retMsg, 0, sizeof(retMsg));
		snprintf(retMsg, sizeof(retMsg) - 1, "DBERR 错误：%s : %s : %s",
				otlErr.msg, otlErr.stm_text, otlErr.var_info);
	} catch (appException& appErr) {
		retCode = appErr.errCode;
		memset(retMsg, 0, sizeof(retMsg));
		strncpy(retMsg, appErr.errMsg, sizeof(retMsg) - 1);
	} catch (std::exception& err) {
		retCode = 301 * 1000000;
		memset(retMsg, 0, sizeof(retMsg));
		strncpy(retMsg, err.what(), sizeof(retMsg) - 1);
	} catch (...) {
		retCode = 300 * 1000000;
		strcpy(retMsg, "未知错误请联系系统管理员!");
	}
	printf("retCode:%ld  retMsg:%s\n", retCode, retMsg);

	return 0;
}