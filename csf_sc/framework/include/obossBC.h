#ifndef __CUSTVIEW_H__
#define __CUSTVIEW_H__

utype* cQSobidTypeConvertByIdType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSobVipSrvLevelCodeBySrvLevel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSobBrandCodeBySmCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSobRunCodeConvertByRunCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfDobMarkOperateMsgBykeys(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfDobMarkOperateMsgBykey(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOrdStatusOfDobMarkOperateMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOrdStatusOfDobMarkOperate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSobStaticDataCfgByParaid(const utype * inParam,TCtrlInfo *errInfo);
utype* cITobTdVideoCountCilInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTobTdVideoCountCilInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfTobTdVideoCountCilByIdValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cITobTdVideoCountCilInfoHis(const utype * inParam,TCtrlInfo *errInfo);
#endif

