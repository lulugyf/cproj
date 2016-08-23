#ifndef __ALLBC_H__
#define __ALLBC_H__


#include "pub.h"

#include "CustSvc.h"
#include "pubBCP.h"
//#include "pubBase.h"
#include "pubCrm.h"
#include "publicBP.h"
#include "ordersvcBP.h"
#include "commcustsvc.h"
#include "custsvcBP.h"
#include "pubProd.h"
#include "publicsrv.h"
#include "customerBC.h"
#include "userBC.h"
#include "accountBC.h"
#include "interactionBC.h"
#include "basementBC.h"
#include "basementBP.h"
#include "productBC.h"
#include "custmngBP.h"
#include "orderBC.h"
#include "testBCP.h" 
#include "scoreBP.h"
#include "obossBP.h"
#include "obossBC.h"
#include "ahlocalBC.h" 
#include "IVRBP.h" 
#include "kfBC.h"
#include "kfBP.h"

#include "custviewBC.h"
#include "custviewBP.h"
#include "marketBC.h"
#include "marketBP.h"
//#include "libborderdeal.h" 
//#include "pubPlat.h"
//#include "sxacctmngBP.h"

utype* pDynSvc(const utype *inparam, TCtrlInfo *ptCtrlInfo);
utype* pPubGetUserServ(const utype* inParam , TCtrlInfo *errInfo);
utype* pTestRegexExec(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* getSysdateTest(const utype* p, TCtrlInfo* errInfo);
#endif
