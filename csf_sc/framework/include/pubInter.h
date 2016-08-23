#ifndef __INTERBCP_H__
#define __INTERBCP_H__

/********************************************************BC*******************************************************/



/********************************************************BP*************/
utype* pubQueryContractPreDet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserOweFee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserDeadOweFee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryContractDeposit(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserLastPay(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserMark(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubUpdatePhoneRes(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

#endif

