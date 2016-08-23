#include <string>
#include <iostream>
#include <map>
#include "framework.h"

const char *CSF_get_POOL_ID();

utype* doMerge(map<string, void*>* m, TCtrlInfo* errInfo) ;

utype* AssiMutiConnWork(const utype* in, TCtrlInfo* errInfo,
		TUtypeFuncPtr ptUtypeFuncPtr, TDoMerge ptDoMerge, const char *psDbLabel,
		int iConnType);
