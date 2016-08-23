#ifndef __ZZBTESTBCP_H__
#define __ZZBTESTBCP_H__

#include "pub.h"
#include "tuxadp.h"
#include "pubCrm.h"
#include "publicBC.h"
#include "pubBCP.h"
#include "allBCP.h"
//#include "pubbase.h"

//bc
utype* cDUserInfoByIdNo(const utype *inParam , TCtrlInfo *errInfo);
utype* cIUserInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* cQUserInfoByIdNo(const utype *inParam , TCtrlInfo *errInfo);
utype* cUUserInfoByIdNo(const utype *inParam , TCtrlInfo *errInfo);
utype* cIUserAddInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* cQCustResOrdInfoByIccid(const utype *inParam , TCtrlInfo *errInfo);
utype* cQCustResOrdInfoByResourceNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustResOrdInfoByResourceNo(const utype *inParam , TCtrlInfo *errInfo);
utype* cDCustResOrdInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* cICustResOrdInfoHis(const utype *inParam , TCtrlInfo *errInfo);
utype* cICustResOrdInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* cIDPHONERES(const utype *inParam , TCtrlInfo *errInfo);
utype* cDDPHONERES(const utype *inParam , TCtrlInfo *errInfo);
utype* cQbsUniCodeDefDictByCodeValue(const utype *inParam , TCtrlInfo *errInfo);
utype* cQbsUniCodeDefDictByCodeClass(const utype *inParam , TCtrlInfo *errInfo);
utype* cILoginOpr(const utype *inParam , TCtrlInfo *errInfo);
utype* cQSimResLimit(const utype *inParam , TCtrlInfo *errInfo);
//bp 
utype* pQCustResOrdInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* pDCustResOrdInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* pOperateChk(const utype *inParam , TCtrlInfo *errInfo);
utype* pICustResOrdInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* pQSimResLimitOt(const utype *inParam , TCtrlInfo *errInfo);

utype* p1004QCustRes(const utype *inParam , TCtrlInfo *errInfo);
utype* p1004UnLock(const utype *inParam , TCtrlInfo *errInfo);
utype* p1004Cfm(const utype *inParam , TCtrlInfo *errInfo);
utype* p1004QPhInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* pPubQPhList(const utype *inParam , TCtrlInfo *errInfo);
utype* pPubQCustList(const utype *inParam , TCtrlInfo *errInfo);
//utype* stest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
#endif
