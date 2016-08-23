#ifndef __CUSTVIEW_BP_H__
#define __CUSTVIEW_BP_H__

utype * pUnifyView(const utype *puInParam, TCtrlInfo *ptCtrlInfo); 
utype * pUnifyEnter(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pUTest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * p1127FeeList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * p3817Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * p3817Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * p3818Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQUserDetailInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * p3818Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * p3818batch(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * p3818batchQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pCheckLoginPdom(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * p3821Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype * p3821Cfm(const utype *puInParam, TCtrlInfo *errInfo);

utype *p3819Cfm(const utype *inParam , TCtrlInfo *errInfo);
utype *p3819Qry(const utype *inParam , TCtrlInfo *errInfo);
utype* p3819QryByRuleCode(const utype *inParam, TCtrlInfo *errInfo);

utype * p3823BatchUp(const utype *puInParam, TCtrlInfo *errInfo);
utype * p3823Del(const utype *puInParam, TCtrlInfo *errInfo);
utype * p3823Inadd(const utype *puInParam, TCtrlInfo *errInfo);
utype * p3823Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype * p3823QryDetail(const utype *puInParam, TCtrlInfo *errInfo);
utype * p3823Querry(const utype *puInParam, TCtrlInfo *errInfo);
utype * p3823UpdDetail(const utype *puInParam, TCtrlInfo *errInfo);
utype * transformUtype(const utype *inParam , TCtrlInfo *errInfo);
utype* pUnifyViewCheck(const utype * inParam, TCtrlInfo *errInfo);

utype * p3715Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQTwoCityInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pQMarActInfo(const utype * inParam,TCtrlInfo *errInfo);

utype *pRuleListQry(const utype *inParam , TCtrlInfo *errInfo);

#endif
