utype * cILoginOpr(const utype *inParam, TCtrlInfo *errInfo);
utype * cILoginQry(const utype *inParam, TCtrlInfo *errInfo);
utype * cQContactMsgRdByCustTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cQChnCodeDictByChnCode(const utype *inParam, TCtrlInfo *errInfo);
utype * cQContactStatusDictByContactStatus(const utype *inParam, TCtrlInfo *errInfo);
utype * cQInterfaceDictByInterfaceCode(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByPhoneTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByLoginAccept (const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByCustId(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByCustTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByCustLoginNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByLoginNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByCustLoginTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByLoginTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginOprByQryCond(const utype *inParam, TCtrlInfo *errInfo);
utype * cQLoginQryRdByQueryCond(const utype *inParam, TCtrlInfo *errInfo);

utype * cQChnCodeDictByCodeOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQInteractiveDictByCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQInteractiveDictByCodeOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQContactMsgRdByQryCond(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQLoginOprRdByConId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQContactMsgRdByConId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cICustRandPwdYYYYMM(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQCustRandPwdRdByIdType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIQryCapsRec(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cQCntOfContactMsgByChnBegin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginQryByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginQryByQOprCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginOprByOpTimeAndCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginOprByIdNoAndOpTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUnsettledTask(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUnsettledTaskByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnsettledTaskByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDealFlagOfUnsettledTaskByAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUnsettledTaskHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnsettledTaskByAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetContactMsgByCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncInfoParamDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncInterDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfOrderInfoByContactId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGroupRelaTypeOfOpAuthen(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGroupInnerTypeOfOpAuthenGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpAuthenGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfOpAuthenGrpByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpAuthen(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpAuthen(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpAuthGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfOpAuthenRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpAuthenRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpAuthenRelByOpAuthenCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpAuthenRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAuthenticationByParAuthen(const utype * inParam,TCtrlInfo *errInfo);
utype* cQContactMsgRdByCustIdDesc(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpAuthenHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpAuthenGrpHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpAuthenRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpAuthenGrpByGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginQryRdByCodeTime(const utype * inParam,TCtrlInfo *errInfo);

utype* cqLoginOprByIdCodeTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCmsMainSvcConfByWorkorderId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWsndcmddayByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWsndcmddayByPhoneNoOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQContactAuthenByQryCond(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIContactAuthen(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQOLPayFeeByOrderActionIdNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cILoginQryNew(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

