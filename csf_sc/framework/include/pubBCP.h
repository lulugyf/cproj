#ifndef __PUBBC_H__
#define __PUBBC_H__

///*######################BP################################################*/
utype* pubUpdateSimRes(const utype * inParam,TCtrlInfo *errInfo);
utype* pubQuerySIMInfoBySimNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserSimQuery(const utype * inParam,TCtrlInfo *errInfo);
utype* pubQuerySimRes(const utype * inParam,TCtrlInfo *errInfo);
utype* pubQueryPhoneRes(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* pubQuerySimResByPhone(const utype * inParam,TCtrlInfo *ptCtrlInfo);


utype* pPubGetSeq(const utype * inParam,TCtrlInfo *ptCtrlInfo);

utype* pIccidCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetDateMinus(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLastDayOfMonthBak(const utype * inParam,TCtrlInfo *errInfo);
#endif
