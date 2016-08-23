/////###################公共类 BEGIN##################
utype* pBillDayQryTTt(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pBusiBillDay(const utype *puInParam, TCtrlInfo *errInfo);
utype* pChkMasterUser(const utype *inParam, TCtrlInfo *errInfo);
utype *p4000BatchPrc_B(const utype *inParam,const utype *uInBusiInfo,TCtrlInfo *errInfo);
utype* pPrcBusiChkDeal(const utype *inParam, const utype *uInBusiPrc, TCtrlInfo *errInfo);
utype* pChk1106Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pNoticMsgInfo(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkUserPrc(const utype *inParam,TCtrlInfo *errinfo);
utype * pChkLimitSend1(const utype *inParam,TCtrlInfo *errInfo);
utype* pChkSlavUser(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetMastUserList(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserWlanPrcQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pMbrModMainMbrPrcChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pMainMbrModMbrPrcChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pOrdMainMbrPrcChk(const utype *inParam, TCtrlInfo *errInfo);
utype* cQUserSvcAttrByUserAttrIn(const utype *inParam, TCtrlInfo *errInfo);
utype* cQAttrMinus(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdBusiCode(const utype *inParam, TCtrlInfo *errInfo);
utype* pOneSimMultiNoCancel(const utype *inParam, TCtrlInfo *errInfo);
utype* pOneSimMultiNoOrder(const utype *inParam, TCtrlInfo *errInfo);
utype* pQOneSimMultiNo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQEnumber(const utype *inParam, TCtrlInfo *errInfo);
utype* pTimeRuleQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pMarkTimeRule(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubProdEncode(const utype *puInParam, TCtrlInfo* errInfo);
utype* pActualTNameQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pPubQProdInfoAll(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubAttrQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubUserSvcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQUsrProdAttr(const utype *inParam, TCtrlInfo *errInfo);
utype* pBusiRelChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pEffExpDateQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pArgsValueChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubAttrQryNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQUsrProdAttrNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pCalcDateQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkReg(const utype *inParam, TCtrlInfo *errInfo);
utype* pQPrcByIdName(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pQryWlanPassWd(const utype *inParam,TCtrlInfo *errinfo);
utype* pQBizClassLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* pGroupQryChg(const utype *inParam, TCtrlInfo *errInfo);
/////###################公共类 END###################
/////###################产品相关类 BEGIN###############
utype* pGroupRoleQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pProdPrcQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pQProdPrc(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pPubProdPrcQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pQUsrProdPrc(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pPubProdPrcQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pPrcAutoDivertQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pBrandQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pCalcDate(const utype * inParam,TCtrlInfo *errInfo);
utype* pQProdList(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdCatalog(const utype *inParam, TCtrlInfo *errInfo);
utype* pQSubCataItem(utype *inParam, utype *outParam, TCtrlInfo *errInfo, int level, char *RecNo);
utype* pQProdPrcs(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdCatalogTree(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdDetail(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdDetailQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdListQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdCataQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdCataQryNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pAttrQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserSvcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUsrProdAttr(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUsrProdDetail(const utype *inParam, TCtrlInfo *errInfo);
utype* pOrdProdDetailByRloeId(utype *inUnOrderParam, utype *inOrderParam, TCtrlInfo *errInfo);
utype* pPubProdDetailQry(utype *inParam, TCtrlInfo *errInfo);
utype* pPubQUsrProdDetail(utype *inParam, TCtrlInfo *errInfo);
utype* pMainSvcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubProdListQry(utype *inParam, TCtrlInfo *errInfo);
utype* pProdCataChk(utype *inParam, TCtrlInfo *errInfo);
utype* pQActionFee(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdFee(const utype *inParam, TCtrlInfo *errInfo);
utype* pQBusiFee(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserBaseInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQSvcSpecOfPrc(const utype *inParam, TCtrlInfo *errInfo);
utype* pGrpPrdListQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUsrPrdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pAttrQryNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUsrProdAttrNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pNullAttrQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdPrcLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubProdPrcLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* pProductListQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkGroupMbrMax(const utype *puInParam, TCtrlInfo* errInfo);
utype* pGetFKByPhoneNoHead(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubGetFKByPhoneNoHead(utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQUserSvcType(const utype *inParam, TCtrlInfo *errInfo);
utype* p1104UserCreditQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pSplitOrder(const utype *inParam, TCtrlInfo *errInfo);
utype* p1104Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserLimitQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProductListOrg(const utype *inParam1, const utype *inParam2,TCtrlInfo *errInfo);
utype* pProductListOr1(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkUserSvc(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkUsrSchoolVNet(const utype *puInParam, TCtrlInfo* errInfo);
extern "C" utype* pQUserNextBrand(const utype *inParam, TCtrlInfo *errInfo);
utype* pAfterLmtRuleQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkShortNum(const utype *puInParam, TCtrlInfo* errInfo);
extern "C" utype* pUserLimitCfm(const utype *puInParam, TCtrlInfo* errInfo);
extern "C" utype* pSiBlackListCfm(const utype *puInParam, TCtrlInfo* errInfo);
utype* pSiBlackListQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pCallNumQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pDeptmentQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pBlackListQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pBlackListCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pServRuleQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pServRuleCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pRouteRuleQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pRouteRuleCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pQGrpUsrOfFamily(const utype *inParam, TCtrlInfo *errInfo);
utype* pServOfferQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1229Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1238Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pMemberQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkMainRoleOfFamily(const utype *puInParam,TCtrlInfo *errinfo);
utype* p1238Chk(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pGetUserIdType(const utype *puInParam,TCtrlInfo *errinfo);
utype* pActualTNameQry(const utype * puInParam, TCtrlInfo* errInfo);
extern "C" utype* pIAddSvcOfMbr(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkMbrPrc(const utype *puInParam, TCtrlInfo* errInfo);
utype* pMainProdInfo(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdCfgCfm(const utype *inParam, TCtrlInfo *errInfo);
//extern "C"  utype* pSvcFinishCfm(const utype *inParam,TCtrlInfo* errInfo);
utype * pTestUtype(const utype *inParam,TCtrlInfo *errInfo);

/////###################产品相关类 END################
/////###################产品资费相关类 BEGIN############
utype* pReleaseChk(const utype * inParam,TCtrlInfo *errInfo);
utype* pStorePrcCfm(const utype * inParam,TCtrlInfo *errInfo);
utype* pStorePrcQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pHotPrcQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pGrpPrdPrcQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pPrcAndProdQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pMbrPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pPrcDivertQry(const utype *puInParam, TCtrlInfo *errInfo);
/////###################产品资费相关类 END##############
/////###################订单处理类 BEGIN###############
extern "C" utype* pProdOrderCfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pProdFinish(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pProdFinish_SX(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* pProdFinish_AH(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* pIUserPrcSpGroup(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pIUserPrcSpGroup_SX(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* pIUserPrcSpGroup_AH(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserPrc(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserBusiLimit(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserPrcSp(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserPrcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserProdAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserSvcTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserSvcAttrTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserSvc(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserSvcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserGroupAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetLastDayOfMonth(const utype *inParam, TCtrlInfo *errInfo);
utype* pUUserPrc(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserPrcSp(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserPrcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserProdAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserSvcTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserSvcAttrTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserSvc(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserSvcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserGroupAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);

utype* pDUserPrc(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserBusiLimit(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserPrcSp(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserPrcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserProdAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserSvcTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserSvcAttrTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserSvc(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserSvcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserGroupAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);

utype* pChkUserOrderPrc(const utype	*puInParam,	TCtrlInfo* errInfo);
utype* pPubProdEncode(const	utype *puInParam, TCtrlInfo* errInfo);

utype* pQPreOrdOfProdInfo(const	utype *puInParam, TCtrlInfo* errInfo);

extern "C" utype* pSp1108Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p4000Cfm(const utype * inParam, TCtrlInfo *errInfo);
utype* pPub4000Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* pPassResetCfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p1147PreCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1147PreOrdQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdCancelCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1111Cfm(const utype *inParam,TCtrlInfo *errinfo);
utype* p1111CfmBatch(const utype *inParam,TCtrlInfo *errinfo,TCtrlInfo *errinfo2 = NULL);
utype* p1111CfmBatchServ(const utype *inParam,TCtrlInfo *errinfo);
utype* pBlkWhtListCfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pCallNumCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p3GNetBookCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserAttrCfm(const utype *inParam,TCtrlInfo *errinfo);
utype* pSubProdCfm(const utype *inParam,TCtrlInfo *errinfo);
utype* pUExpDateOfUserSvcTrace(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" utype* pCallNumGrpCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserPrcSmsSend(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsOrdQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsbindPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype *pGprsRelChk(const utype *inParam, TCtrlInfo *errInfo);
utype *pUserWlanPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype *pStkPrcChk(const utype *inParam, TCtrlInfo *errInfo);
/////###################订单处理类 END#################
/////###################订购实例查询类 BEGIN#############
utype* pQUsrProdInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserOrdInfoQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserOrderQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserOrdAllQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserOrdProdQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pTeamMbrQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpInfoQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pQGroupMbrInfo(const utype *inParam,TCtrlInfo *errinfo);
utype* pQGroupMbrInfo_1(const utype *inParam,TCtrlInfo *errinfo);
utype* pQUsrMbr(const utype *inParam,TCtrlInfo *errinfo);
utype* pPubQUsrMbr(const utype *inParam,TCtrlInfo *errinfo);
utype* pQUserGroupMbr(const utype *inParam,TCtrlInfo *errinfo);
utype* pChkUserProdMbr(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkComDetail(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQMbrPrc(const utype *inParam,TCtrlInfo *errinfo);
utype* pVisibleProdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserParamQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pQMbrAttrInfo(const utype *inParam,TCtrlInfo *errinfo);
utype* pMWOrdInfoQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpPrdOrdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserPrcHisQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryMWOrdInfo(const utype *inParam, TCtrlInfo *errInfo);

utype* pReturnInfoDeal(const utype *inReqParam,const utype * inParam,TCtrlInfo *errInfo);
utype* pSendConfirmSms(const utype *inParam,TCtrlInfo *errInfo);
utype* pReConfirmChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pPopulateOprInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pPopulateBusiInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pReadProdPrcId(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pMainPrcChg(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pSubProdDeal(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pSpInfoDeal(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateProductList(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateGroupInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateParGroupMbrInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateTeamInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateTeamMbrInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateProduct(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateProdPrcInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateAttrInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pCheckOtherPrc(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pQkProdListQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pQkProdPrcQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pQBatchResult(const utype *inParam,TCtrlInfo *errInfo);
utype* p1104CustQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pExpCustInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pubWriteFile(const utype *inParam,TCtrlInfo *errInfo);
utype* pPubQAllAttr(const utype *inParam,TCtrlInfo *errInfo);
utype* pIPubExtInfo(const utype *inParam,TCtrlInfo *errInfo);
utype *p4000BatchCfm(const utype *inParam, TCtrlInfo *errInfo);
utype *pGoodLuckBusi(const utype *inParam, TCtrlInfo *errInfo);
utype* pBindRule(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pChkConRel(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkGrpConRel(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkOtherConRel(const utype *inParam, TCtrlInfo *errInfo);
utype *p4000PrintCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pFuseUserChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pUserSvcInfo_A(const utype *inParam,TCtrlInfo *errinfo);
utype* pBatchSubProdDeal(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);

//houning 20110810 add
utype* p4000Cfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pPub4000Cfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pCheckOtherPrc_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pReturnInfoDeal_B(const utype *inReqParam, const utype *inParam, TCtrlInfo *errInfo);
utype* pSendConfirmSms_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pReConfirmChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pPopulateOprInfo_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pPopulateBusiInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateProductList_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pReadProdPrcId_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pMainPrcChg_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pSubProdDeal_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pSpInfoDeal_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateProduct_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateOpMsgList_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateOpMsg_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateProdPrcInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateParGroupMbrInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateGroupInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateTeamInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateTeamMbrInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateAttrInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pQRtByPrcId_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pSendPrcSms_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pCancelPrc_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkWlanSolFee_B(const utype *inParam,TCtrlInfo *errInfo);

utype* pUserGprsbindPrcQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype *pGprsRelChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsPrcQry_B(const utype *inParam, TCtrlInfo *errInfo);


utype* pKdInfoQry(const utype *inParam, TCtrlInfo *errInfo);
/////###################订购实例查询类 END##############

/////###################营销执行类 BEGIN###############
utype* p1148pubCheck(const utype *inParam, TCtrlInfo *errInfo);
utype* p1148Chk02(const utype *inParam, TCtrlInfo *errInfo);
utype* p1148Qry(const utype *inParam, TCtrlInfo *errInfo);
/////###################营销执行类 END################

////################## add by yangxj (最后再归类)##############################
utype* p1147Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* p1147Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p4037Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pSalesSmsSend(const utype *inParam, TCtrlInfo *errInfo);
utype* pSalesTemplateQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pCustInfoQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryIdIccidByPhoneNo(const utype *inParam,TCtrlInfo *errInfo);
utype* pPrcListQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pPrcListByClassQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pResSellQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pConUserQry(const utype *inParam, TCtrlInfo *errInfo);

utype* p4032PreOrdQry(const utype *inParam, TCtrlInfo *errInfo);
utype* p4032PreOrdListQry(const utype *inParam, TCtrlInfo *errInfo);
utype* p4034PreOrdQry(const utype *inParam, TCtrlInfo *errInfo);
utype* p4034PreOrdCfm(const utype *inParam, TCtrlInfo *errInfo);

utype* pUserOrderChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdPrcCfgQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pOldMbrQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pPrcFeeQry(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype* p1147Rbk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1147FeeCfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p4029Cfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p4029Rbk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p4030Cfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p4030Print(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1147Print(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pResSellRdBackExt(const utype *inParam,TCtrlInfo *errInfo);

////####################  add by yangxj end ############################

///#####################other start########################################
utype* pSIInfoListQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pSpInfoQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pSpBizTypeQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pCtdProdChk(const utype *inParam,TCtrlInfo *errinfo);
utype* pCtdProdCfm(const utype *inParam,TCtrlInfo *errinfo);
utype* pGetRandPass(const utype *inParam, TCtrlInfo *errInfo);
utype* pSchoolQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pReadFile(const utype *inParam,TCtrlInfo *errinfo);
utype* pReadModel(const utype *inParam,TCtrlInfo *errinfo);
utype* pResolFile(const utype *inParam,TCtrlInfo *errinfo);
utype* pResolFileData(const utype *inParam,TCtrlInfo *errinfo);

utype* pProdAny(const utype *inParam,TCtrlInfo *errinfo,TCtrlInfo *errinfo2 = NULL);
int getstringNum(const string str,string sign);
utype* pubWriteTxtFile(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pSelfTeminalQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pMWSendSms(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserSmsCfm(const utype *inParam,TCtrlInfo *errinfo);
utype* pWebShopQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpSpecPrdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGetCustPrdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pNetRelChk(const utype *inParam,TCtrlInfo *errinfo);
utype* pCrntOrdChg(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUserPrcQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUserQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUserQryFDB(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUserPrcQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUserMbrQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpOrdInfoQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpOrdInfoQryFor2DB(const utype *inParam,TCtrlInfo *errinfo);
utype* pQUsrProdInfoF2DB(const utype *inParam,TCtrlInfo *errinfo);
utype* pSIBlackQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pQkUserProdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pPrcLevelChg(const utype *inParam,TCtrlInfo *errinfo);
utype* pCardTradeProd(const utype *inParam,TCtrlInfo *errinfo);
utype* p3GNetBookChk(const utype *inParam,TCtrlInfo *errinfo);
///#####################other end########################################

///#####################add by chenying only test use ##################
utype* cheny_test(const utype* inParam,TCtrlInfo *errInfo);
///#####################end###############################################

///#####################add by lq for test ##################
utype* pMebTrancPrcChk(const utype *puInParam, TCtrlInfo *errInfo);
utype* pProdByPrcId(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQProdBusiCode(const utype *puInParam,TCtrlInfo* errInfo);
utype* pSmsSendChk(const utype *puInParam,TCtrlInfo* errInfo);
utype* pQYKTProdInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
///#####################add by lq for test ##################

///#####################add by xujg ##################
utype* pQXAgeLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* pQXJjkFlag(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pChkBalancePrice(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pRQUserOweFeeFuncaa(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pChkEcMas(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pChkVPrcId(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pChkV1106(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdResBackCfm(const utype *inParam,TCtrlInfo *errInfo);
utype* pProdResDealCfm(const utype *inParam,TCtrlInfo *errInfo);
utype* p1140Back(const utype *inParam,TCtrlInfo *errInfo);
utype* pEcMas(const utype *inParam,TCtrlInfo *errInfo);
utype* pEcMasAttrValue(const utype *inParam,TCtrlInfo *errInfo);
utype* pDuserPrcStates(const utype *inParam,TCtrlInfo *errInfo);
utype* pSendPrcSms(const utype *inParam,TCtrlInfo *errInfo);
utype* pCancelPrc(const utype *inParam,TCtrlInfo *errInfo);
utype* pActInfoQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pBusiQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pCardInfoQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pChkUOrderByPhoneClassId(const utype *inParam,TCtrlInfo *errInfo);
utype* pReleaseAddList(const utype *inParam,TCtrlInfo *errInfo);
utype* pUserAttrInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pNoteForMngerAdd(const utype *inParam,TCtrlInfo *errInfo);
utype* pQFreePrcInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pChkUserBillMode(const utype *inParam,TCtrlInfo *errInfo);
utype* pCountUserPrc(const utype *inParam,TCtrlInfo *errInfo);
utype* pQPrcDetailDict(const utype *inParam,TCtrlInfo *errInfo);
///#####################end by xujg ##################
extern "C" utype* pChkWlanBalance(const utype *inParam,TCtrlInfo *errInfo);
///#####################add by chenjun ##################
utype* pMISCOrdInfoQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pEffNumChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pPrcMsgCfm(const utype *inParam, TCtrlInfo *errInfo);
void GetLocalPath1();
void GetFileCfg1(const char* pId, char* pHost, char* pUser, char* pPass, char* pPath);
utype * pInterProdDict(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterPrcDict(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterRelease(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterPdRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetPrcByProdMasterServId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProdByMasterServId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRelease(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProdProdRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pProdAndPrdProcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pFriendNumChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pMaxFriendNumQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pGuoqhTest(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQProdByCust(const utype *inParam, TCtrlInfo *errInfo);
utype* pLISExcpInfoQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pLISInterCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pResSellQryByOrdId(const utype *inParam, TCtrlInfo *errInfo);
utype *pSalesInterQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pExceImeiDeal(const utype *inParam, TCtrlInfo *errInfo);

utype *pUUserResState(const utype *inParam, TCtrlInfo *errInfo);
utype *pUResUserPasswd(const utype *inParam, TCtrlInfo *errInfo);
utype *pUserResInfoChk(const utype *inParam, TCtrlInfo *errInfo);

utype * p1286Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1147MSG(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkBind(const utype *inParam,TCtrlInfo *errInfo);
utype* pQryOrdDis(const utype *inParam,TCtrlInfo *errInfo);
utype* pQryUsrOrdDis(const utype *inParam,TCtrlInfo *errInfo);
utype* pBindMbr(const utype *inParam,TCtrlInfo *errInfo);
utype* DoQueryParam(const utype *inParam,TCtrlInfo *errInfo);
utype* BCTest(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype* pXXTBackChk(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pUserGrpMbrChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkOrdLimitRel(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkOrdNumLimit(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkPrdNumLimit(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkUserOtherProd(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkUserOtherPrcList(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkProdLastDay(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkUserPrcOrderList(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkUserMainPrc(const utype *inParam,TCtrlInfo *errinfo);

utype *pFFOlPriceQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserInfoChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pMaxProdLimitQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkWlanSolFee(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pQryDataFlow(const utype *inParam,TCtrlInfo *errInfo);
utype *pQZDInfo(const utype *inParam, TCtrlInfo *errInfo);
utype *pQResSaleNoFF(const utype *inParam, TCtrlInfo *errInfo);
utype *pDelUsrFFInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pInLalaPackage(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUserOrderInfoSP(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQryFYFHInfo(const utype *puInParam,TCtrlInfo* errInfo);
utype* pGetGroupInfoByCustId(const utype *inParam, TCtrlInfo *errInfo);
utype* pInterSerialNum(const utype *inParam, TCtrlInfo *errInfo);
utype* pInterUserLimit(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkUserBelong(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pYYZDOver(const utype *inParam,TCtrlInfo *errinfo);
utype *pA23Qry(const utype *inParam, TCtrlInfo *errInfo);
///#####################add by chenjun ##################

///#####################add by liuxra ##################
utype* pUserfavInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserNetAge(const utype *inParam, TCtrlInfo *errInfo);
///#####################add by liuxra ##################


///#####################add by huanglm for saleExec ##################
utype* pChkUserForDig(const utype *inParam, TCtrlInfo *errInfo);

utype* pPubProdSmsSend(const utype *inParam, TCtrlInfo *errInfo);

utype* pChkProdSvcRes(const utype *inParam, TCtrlInfo *errInfo);

utype* pScoreToProdCfm(const utype *inParam, TCtrlInfo *errInfo);

utype* pDigSaleRollBack(const utype *inParam, TCtrlInfo *errInfo);

utype* pSaleActCfm(const utype *inParam, TCtrlInfo *errInfo);


///#####################SMS BEGIN ##################
utype* pubCallFunc(const utype *puInParam,TCtrlInfo* errInfo);
utype* pubGetSmsParam(const utype* puInParam,TCtrlInfo* errInfo);
utype* pubGetSmsTplt(const utype *puInParam,TCtrlInfo* errInfo);
utype* pubRepSmsTplt(const utype* puInParam,TCtrlInfo* errInfo);
void pubSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
void pubTXSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
void pPubSmsTpltSend(const utype *puInParam,TCtrlInfo* errInfo);
void pPubTXSmsTpltSend(const utype *puInParam,TCtrlInfo* errInfo);
void pPubICrmWorkSheetNT(const utype *inParam,TCtrlInfo *errInfo);
void pubWapPushSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
utype* pPrcSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
utype* pFuncSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
utype* pFuncReCfmSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
utype* pNetArgsChk(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" utype* pGetSmsParamInJTJH(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pGetSmsParamInJFK(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryCompMbr(const utype *puInParam,TCtrlInfo* errInfo);
void pubSmsSendSX(const utype *puInParam,TCtrlInfo* errInfo);
utype* pubGetSmsTpltSX(const utype *puInParam,TCtrlInfo* errInfo);
///#####################SMS END ##################
utype* pProdDataQry(const utype *puInParam,TCtrlInfo* errInfo);
///##################### 一卡多号 ##################
utype* pChkMasterUser(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkSlavUser(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetMastUserList(const utype *inParam, TCtrlInfo *errInfo);
utype* pOneSimMultiNoCancel(const utype *inParam, TCtrlInfo *errInfo);
utype* pOneSimMultiNoOrder(const utype *inParam, TCtrlInfo *errInfo);
utype * pQOneSimMultiNo(const utype *inParam, TCtrlInfo *errInfo);
///#####################一卡多号 ##################
utype* pIPubExtInfoRd(const utype *inParam,TCtrlInfo *errinfo);
utype* p4037Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p4037Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pProdOrderDelay(const utype *inParam,TCtrlInfo *errinfo);

utype* pSqlServer(const utype *inParam,TCtrlInfo *errinfo);
utype* pModelContentQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pSplitOrderByRoute(const utype *inParam, TCtrlInfo *errInfo);
utype* pSvcChk(const utype *inParam, TCtrlInfo *errInfo);

//#####################新增营业员自定义费用科目 zhoujz20100726 ##################
utype* pGetAddFeeInfo(const utype *inParam, TCtrlInfo *errInfo);


utype* cQChnGroupRelByParentGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCustByPhoneNoAndMasterServId(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* p1285Query(const utype *puInParam,TCtrlInfo *ptCtrlInfo);

utype* pNullcpp(const utype *inParam, TCtrlInfo *errInfo);

///#####################精品推荐需求新增函数说明 ##################
utype* pBusiRecommendQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pRecommendCfgQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pRecommendOrderQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pRecommendSend(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pRecommendSendNew(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubRecommendSend(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pRecommendSendQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//####################产品管理配置 精品静态配置 ####################
utype* pDealOrdcommend(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pDealPrcStat(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pDealRecommend(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* cQLoginPCGrp(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* cDOrdCommByCommId(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* cIOrdCommHisCommId(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
//####################融合资费增加 ####################
extern "C" utype* p3106Cfm(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p3105Cfm(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pPrcTranXml(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pDealMbrPrcBack(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pDealMbrPrcComple(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pProdOrdCfm(const utype *puInParam,TCtrlInfo* errInfo);
//####################为欠费销户优化增加的专用服务 ####################
utype* pUserDealXH(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pMemberKQChk(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pZhVpmnChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pQRtByPrcId(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);

utype* pPopulateOpMsgList(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateOpMsg(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype *pAlterUsrPrcCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pUunsettask(const utype *inParam,TCtrlInfo *errInfo);
//####################成员管理 ##############################
utype* p1106Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPrcTranXmll(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pImsPrcChk(const utype *puInParam, TCtrlInfo* errInfo);
extern "C" utype* pGetDMTPhoneBycust(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQUserImsChk(const utype* inParam, TCtrlInfo* errInfo);
utype* pTestWangxlc(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pProvCarryUserChk(const utype *inParam,TCtrlInfo *errInfo);

utype* pSIBlackListQry(const utype *uInParam,TCtrlInfo *errinfo);
utype* cQUniCodeDefByCodeClassAndCodeName(const utype *puInParam,TCtrlInfo* errInfo);
utype* cUIsBackOfPdSales(const utype *puInParam,TCtrlInfo* errInfo);

utype* pPubQCustContUserByIdNo2(const utype *inParam, TCtrlInfo *errInfo);

utype* pProdBillDeal(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQUserProdGrpInfo(const utype* inParam, TCtrlInfo* errInfo);
utype* pQUserGroupListByGroupType(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUsrPrdInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUserPrdOutRel(const utype *inParam, TCtrlInfo *errInfo);

utype* pSaveBatchFile(const utype *inParam,TCtrlInfo *errinfo);
utype* batchinsert(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpInfoQryByPh(const utype *InParam,TCtrlInfo *errinfo);
#include <vector>
void splitstring(const string str,vector<string> &vec,string sign);

extern "C" utype* pChkOrdGprs(const utype *inParam,TCtrlInfo *errinfo);
utype* pRecommendSendCheck(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQPrcAndCity(const utype *inParam,TCtrlInfo *errinfo);
utype* pQPrcForCity(const utype *inParam,TCtrlInfo *errinfo);
utype* pChkOrdCity(const utype *inParam,TCtrlInfo *errinfo);
utype* pQMinBill(const utype * puInParam, TCtrlInfo * errInfo);
utype* pQOUBill(const utype * puInParam, TCtrlInfo * errInfo);
utype* pInvoiceVerCfm(const utype * puInParam, TCtrlInfo * errInfo);
utype *pTimeQryMonth(const utype *puInParam, TCtrlInfo *ptCtrlInfo);


utype* pProdMaxNumChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pFundAllocate(const utype *puInParam,TCtrlInfo* errInfo);
//透明消费增加代码
utype* pQOutOprErrMain(const utype *inParam,TCtrlInfo *errInfo);
utype* pQOutOprErrDetail(const utype *inParam,TCtrlInfo *errInfo);
utype* pIOutOprErrInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pUOutCallOprInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pQOutErrInfoDetail(const utype *inParam,TCtrlInfo *errInfo);
//优惠城市名称查询
utype* pQUsrCityInfo(const utype *inParam,TCtrlInfo *errinfo);
utype* pFirOrdChk(const utype *inParam,TCtrlInfo *errInfo);

utype* pQUserPrcCredit(const utype *inParam, TCtrlInfo *errInfo);//add by dicy
utype* pMASXXJQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pImsUserInfoQry(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype * pConDayQry(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype * p1119Init(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype * pConDayCalQry(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype * p1119Qry(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype * pPrcInsCalQry(const utype *inParam,TCtrlInfo *errinfo);
utype *pPubChkPrcBillDay(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* p1119BusiDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype * pAlterPrcRelChk(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* p1119OrderCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUUserPrcInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pUpdateUserBrandRelForBill(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateUserBillModeInfoForBill(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateUserMbrInfoForBill(const utype *puInParam, TCtrlInfo *errInfo);
utype* pUDateUserSvcTrace(const utype *puInParam,TCtrlInfo* errInfo);
utype* pUpdateConUserInfoForBill(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUDateUserTrans(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" utype * p1119MBillInfo(const utype *puInParam,TCtrlInfo *errinfo);
utype* pUUserPrcInfoForBill(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkUGroupMbr(const utype *inParam,TCtrlInfo *errInfo);
/*tiansqa*/
extern "C" utype* pChkPrdUnNatural(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pUserOrdChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserOrdQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pTeamMbrQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pVisiblPrdQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserParamQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pMWOrdInfoQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserGprsQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserCanOrdQ_B(const utype *inParam,TCtrlInfo *errinfo);
/////###################公共类 BEGIN##################
utype* pUserWlanPrcQry(const utype *inParam, TCtrlInfo *errInfo);

utype* cQUserSvcAttrByUserAttrIn(const utype *inParam, TCtrlInfo *errInfo);
utype* cQAttrMinus(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdBusiCode(const utype *inParam, TCtrlInfo *errInfo);
utype* pQEnumber(const utype *inParam, TCtrlInfo *errInfo);
utype* pTimeRuleQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pPubProdEncode(const utype *puInParam, TCtrlInfo* errInfo);
utype* pActualTNameQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pPubQUsrProdInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubAttrQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubUserSvcQry(const utype *inParam, TCtrlInfo *errInfo);

utype* p8832Query(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQUsrProdAttr(const utype *inParam, TCtrlInfo *errInfo);
utype* pBusiRelChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pEffExpDateQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pArgsValueChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubAttrQryNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQUsrProdAttrNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pCalcDateQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkReg(const utype *inParam, TCtrlInfo *errInfo);
utype* pQPrcByIdName(const utype *puInParam, TCtrlInfo *errInfo);
/////###################公共类 END###################
/////###################产品相关类 BEGIN###############
utype* pGroupRoleQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pProdPrcQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pQProdPrc(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pPubProdPrcQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pQUsrProdPrc(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pPubProdPrcQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pPrcAutoDivertQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pVisiblePrcQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pBrandQry(const utype* inParam, TCtrlInfo* ptCtrlInfo);
utype* pCalcDate(const utype * inParam,TCtrlInfo *errInfo);
utype* pQProdList(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdCatalog(const utype *inParam, TCtrlInfo *errInfo);
utype* pQSubCataItem(utype *inParam, utype *outParam, TCtrlInfo *errInfo, int level, char *RecNo);
utype* pQProdPrcs(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdCatalogTree(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdDetail(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdDetailQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdListQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdCataQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdCataQryNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pAttrQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserSvcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUsrProdAttr(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUsrProdDetail(const utype *inParam, TCtrlInfo *errInfo);
utype* pOrdProdDetailByRloeId(utype *inUnOrderParam, utype *inOrderParam, TCtrlInfo *errInfo);
utype* pPubProdDetailQry(utype *inParam, TCtrlInfo *errInfo);
utype* pPubQUsrProdDetail(utype *inParam, TCtrlInfo *errInfo);
utype* pMainSvcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubProdListQry(utype *inParam, TCtrlInfo *errInfo);
utype* pProdCataChk(utype *inParam, TCtrlInfo *errInfo);
utype* pQActionFee(const utype *inParam, TCtrlInfo *errInfo);
utype* pQProdFee(const utype *inParam, TCtrlInfo *errInfo);
utype* pQBusiFee(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserBaseInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQSvcSpecOfPrc(const utype *inParam, TCtrlInfo *errInfo);
utype* pGrpPrdListQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUsrPrdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pAttrQryNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUsrProdAttrNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pNullAttrQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdPrcLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubProdPrcLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* pProductListQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkGroupMbrMax(const utype *puInParam, TCtrlInfo* errInfo);
utype* pGetFKByPhoneNoHead(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubGetFKByPhoneNoHead(utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQUserSvcType(const utype *inParam, TCtrlInfo *errInfo);
utype* pSplitOrder(const utype *inParam, TCtrlInfo *errInfo);
utype* p1104Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserLimitQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProductListOrg(const utype *inParam1, const utype *inParam2,TCtrlInfo *errInfo);
utype* pProductListOr1(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkUserSvc(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkUsrSchoolVNet(const utype *puInParam, TCtrlInfo* errInfo);
extern "C" utype* pQUserNextBrand(const utype *inParam, TCtrlInfo *errInfo);
utype* pAfterLmtRuleQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkShortNum(const utype *puInParam, TCtrlInfo* errInfo);
extern "C" utype* pUserLimitCfm(const utype *puInParam, TCtrlInfo* errInfo);
extern "C" utype* pSiBlackListCfm(const utype *puInParam, TCtrlInfo* errInfo);
utype* pSiBlackListQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pCallNumQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pDeptmentQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pBlackListQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pBlackListCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pServRuleQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pServRuleCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pRouteRuleQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pRouteRuleCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pQGrpUsrOfFamily(const utype *inParam, TCtrlInfo *errInfo);
utype* pServOfferQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1229Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1238Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pMemberQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkMainRoleOfFamily(const utype *puInParam,TCtrlInfo *errinfo);
utype* p1238Chk(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pGetUserIdType(const utype *puInParam,TCtrlInfo *errinfo);
utype* pActualTNameQry(const utype * puInParam, TCtrlInfo* errInfo);
extern "C" utype* pIAddSvcOfMbr(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkMbrPrc(const utype *puInParam, TCtrlInfo* errInfo);
utype* pMainProdInfo(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdCfgCfm(const utype *inParam, TCtrlInfo *errInfo);

/////###################产品相关类 END################
/////###################产品资费相关类 BEGIN############
utype* pReleaseChk(const utype * inParam,TCtrlInfo *errInfo);
utype* pStorePrcCfm(const utype * inParam,TCtrlInfo *errInfo);
utype* pStorePrcQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pHotPrcQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pGrpPrdPrcQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pPrcAndProdQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pMbrPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pPrcDivertQry(const utype *puInParam, TCtrlInfo *errInfo);
/////###################产品资费相关类 END##############
/////###################订单处理类 BEGIN###############
extern "C" utype* pProdOrderCfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pProdFinish(const utype *inParam, TCtrlInfo *errInfo);
utype* pIUserPrc(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserBusiLimit(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserPrcSp(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserPrcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserProdAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserSvcTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserSvcAttrTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserSvc(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserSvcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserGroupAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetLastDayOfMonth(const utype *inParam, TCtrlInfo *errInfo);
utype* pUUserPrc(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserPrcSp(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserPrcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserProdAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserSvcTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserSvcAttrTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserSvc(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserSvcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserGroupAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);

utype* pDUserPrc(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserBusiLimit(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserPrcSp(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserPrcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserProdAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserSvcTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserSvcAttrTrace(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserSvc(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserSvcAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserGroupAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);

utype* pChkUserOrderPrc(const utype	*puInParam,	TCtrlInfo* errInfo);
utype* pPubProdEncode(const	utype *puInParam, TCtrlInfo* errInfo);

utype* pQPreOrdOfProdInfo(const	utype *puInParam, TCtrlInfo* errInfo);

extern "C" utype* pSp1108Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p4000Cfm(const utype * inParam, TCtrlInfo *errInfo);
utype* pPub4000Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* pPassResetCfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p1147PreCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1147PreOrdQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdCancelCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1111Cfm(const utype *inParam,TCtrlInfo *errinfo);
utype* pBlkWhtListCfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pCallNumCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p3GNetBookCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserAttrCfm(const utype *inParam,TCtrlInfo *errinfo);
utype* pSubProdCfm(const utype *inParam,TCtrlInfo *errinfo);
utype* pUExpDateOfUserSvcTrace(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" utype* pCallNumGrpCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserPrcSmsSend(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsOrdQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsbindPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype *pGprsRelChk(const utype *inParam, TCtrlInfo *errInfo);
utype *pUserWlanPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype *pStkPrcChk(const utype *inParam, TCtrlInfo *errInfo);
/////###################订单处理类 END#################
/////###################订购实例查询类 BEGIN#############
utype* pQUsrProdInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserOrdInfoQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserOrderQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserOrdAllQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserOrdProdQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pTeamMbrQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpInfoQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pQGroupMbrInfo(const utype *inParam,TCtrlInfo *errinfo);
utype* pQGroupMbrInfo_1(const utype *inParam,TCtrlInfo *errinfo);
utype* pQUsrMbr(const utype *inParam,TCtrlInfo *errinfo);
utype* pPubQUsrMbr(const utype *inParam,TCtrlInfo *errinfo);
utype* pQUserGroupMbr(const utype *inParam,TCtrlInfo *errinfo);
utype* pChkUserProdMbr(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkComDetail(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQMbrPrc(const utype *inParam,TCtrlInfo *errinfo);
utype* pVisibleProdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserParamQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pQMbrAttrInfo(const utype *inParam,TCtrlInfo *errinfo);
utype* pMWOrdInfoQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpPrdOrdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserPrcHisQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryMWOrdInfo(const utype *inParam, TCtrlInfo *errInfo);

utype* pReturnInfoDeal(const utype *inReqParam,const utype * inParam,TCtrlInfo *errInfo);
utype* pSendConfirmSms(const utype *inParam,TCtrlInfo *errInfo);
utype* pReConfirmChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pPopulateOprInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pPopulateBusiInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pReadProdPrcId(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pMainPrcChg(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pSubProdDeal(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pSpInfoDeal(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateProductList(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateGroupInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateParGroupMbrInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateTeamInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateTeamMbrInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateProduct(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateProdPrcInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pPopulateAttrInfo(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pCheckOtherPrc(const utype * inParam,const utype *uInBusiUap,TCtrlInfo *errInfo);
utype* pQkProdListQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pQkProdPrcQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pQBatchResult(const utype *inParam,TCtrlInfo *errInfo);
utype* p1104CustQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pExpCustInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pubWriteFile(const utype *inParam,TCtrlInfo *errInfo);
utype* pPubQAllAttr(const utype *inParam,TCtrlInfo *errInfo);
utype* pIPubExtInfo(const utype *inParam,TCtrlInfo *errInfo);
utype *p4000BatchCfm(const utype *inParam, TCtrlInfo *errInfo);
utype *pGoodLuckBusi(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype* pChkConRel(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkGrpConRel(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkOtherConRel(const utype *inParam, TCtrlInfo *errInfo);
utype *p4000PrintCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pFuseUserChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pUserSvcInfo_A(const utype *inParam,TCtrlInfo *errinfo);
/////###################订购实例查询类 END##############

///#####################other start########################################
utype* pSIInfoListQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pSpInfoQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pSpBizTypeQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pCtdProdChk(const utype *inParam,TCtrlInfo *errinfo);
utype* pCtdProdCfm(const utype *inParam,TCtrlInfo *errinfo);
utype* pGetRandPass(const utype *inParam, TCtrlInfo *errInfo);
utype* pSchoolQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pReadFile(const utype *inParam,TCtrlInfo *errinfo);
utype* pReadModel(const utype *inParam,TCtrlInfo *errinfo);
utype* pResolFile(const utype *inParam,TCtrlInfo *errinfo);
utype* pResolFileData(const utype *inParam,TCtrlInfo *errinfo);

int getstringNum(const string str,string sign);
utype* pubWriteTxtFile(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pSelfTeminalQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pMWSendSms(const utype *inParam,TCtrlInfo *errinfo);
//utype* pUserSmsCfm(const utype *inParam,TCtrlInfo *errinfo);
utype* pWebShopQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpSpecPrdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGetCustPrdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pNetRelChk(const utype *inParam,TCtrlInfo *errinfo);
utype* pCrntOrdChg(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUserPrcQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUserQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUserMbrQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpOrdInfoQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pSIBlackQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pQkUserProdQry(const utype *inParam,TCtrlInfo *errinfo);
utype* pPrcLevelChg(const utype *inParam,TCtrlInfo *errinfo);
utype* pCardTradeProd(const utype *inParam,TCtrlInfo *errinfo);
utype* p3GNetBookChk(const utype *inParam,TCtrlInfo *errinfo);
///#####################other end########################################

///#####################add by chenying only test use ##################
utype* cheny_test(const utype* inParam,TCtrlInfo *errInfo);
///#####################end###############################################

///#####################add by lq for test ##################
utype* pMebTrancPrcChk(const utype *puInParam, TCtrlInfo *errInfo);
utype* pProdByPrcId(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQProdBusiCode(const utype *puInParam,TCtrlInfo* errInfo);
utype* pSmsSendChk(const utype *puInParam,TCtrlInfo* errInfo);
utype* pQYKTProdInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
///#####################add by lq for test ##################

///#####################add by xujg ##################
utype* pQXAgeLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* pQXJjkFlag(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pChkBalancePrice(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pRQUserOweFeeFuncaa(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pChkEcMas(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdResBackCfm(const utype *inParam,TCtrlInfo *errInfo);
utype* pProdResDealCfm(const utype *inParam,TCtrlInfo *errInfo);
utype* p1140Back(const utype *inParam,TCtrlInfo *errInfo);
utype* pEcMas(const utype *inParam,TCtrlInfo *errInfo);
utype* pEcMasAttrValue(const utype *inParam,TCtrlInfo *errInfo);
utype* pDuserPrcStates(const utype *inParam,TCtrlInfo *errInfo);
utype* pSendPrcSms(const utype *inParam,TCtrlInfo *errInfo);
utype* pCancelPrc(const utype *inParam,TCtrlInfo *errInfo);
utype* pActInfoQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pBusiQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pCardInfoQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pChkUOrderByPhoneClassId(const utype *inParam,TCtrlInfo *errInfo);
///#####################end by xujg ##################
extern "C" utype* pChkWlanBalance(const utype *inParam,TCtrlInfo *errInfo);
///#####################add by chenjun ##################
utype* pMISCOrdInfoQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pEffNumChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pPrcMsgCfm(const utype *inParam, TCtrlInfo *errInfo);
void GetLocalPath1();
void GetFileCfg1(const char* pId, char* pHost, char* pUser, char* pPass, char* pPath);
utype * pInterProdDict(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterPrcDict(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterRelease(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterPdRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetPrcByProdMasterServId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProdByMasterServId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRelease(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProdProdRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pProdAndPrdProcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pFriendNumChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pMaxFriendNumQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pGuoqhTest(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQProdByCust(const utype *inParam, TCtrlInfo *errInfo);
utype* pLISExcpInfoQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pLISInterCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pResSellQryByOrdId(const utype *inParam, TCtrlInfo *errInfo);
utype *pSalesInterQry(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pExceImeiDeal(const utype *inParam, TCtrlInfo *errInfo);

utype * p1286Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1147MSG(const utype *inParam, TCtrlInfo *errInfo);
utype* cInterUserMsg(const utype * inParam,TCtrlInfo *errInfo,FILE *pf);
utype* pChkBind(const utype *inParam,TCtrlInfo *errInfo);
utype* pQryOrdDis(const utype *inParam,TCtrlInfo *errInfo);
utype* pQryUsrOrdDis(const utype *inParam,TCtrlInfo *errInfo);
utype* pBindMbr(const utype *inParam,TCtrlInfo *errInfo);
utype* DoQueryParam(const utype *inParam,TCtrlInfo *errInfo);
utype* BCTest(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype* pXXTBackChk(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pUserGrpMbrChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChkOrdLimitRel(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkOrdNumLimit(const utype *inParam,TCtrlInfo *errinfo);
utype *pFFOlPriceQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserInfoChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pMaxProdLimitQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkWlanSolFee(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pQryDataFlow(const utype *inParam,TCtrlInfo *errInfo);
utype *pQZDInfo(const utype *inParam, TCtrlInfo *errInfo);
utype *pQResSaleNoFF(const utype *inParam, TCtrlInfo *errInfo);
utype *pDelUsrFFInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUserOrderInfoSP(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQryFYFHInfo(const utype *puInParam,TCtrlInfo* errInfo);
utype* pGetGroupInfoByCustId(const utype *inParam, TCtrlInfo *errInfo);
utype* pAcceptQry(const utype *inParam, TCtrlInfo *errInfo);
///#####################add by chenjun ##################



///#####################add by huanglm for saleExec ##################
utype* pChkUserForDig(const utype *inParam, TCtrlInfo *errInfo);

utype* pPubProdSmsSend(const utype *inParam, TCtrlInfo *errInfo);

utype* pChkProdSvcRes(const utype *inParam, TCtrlInfo *errInfo);

utype* pScoreToProdCfm(const utype *inParam, TCtrlInfo *errInfo);

utype* pDigSaleRollBack(const utype *inParam, TCtrlInfo *errInfo);

utype* pSaleActCfm(const utype *inParam, TCtrlInfo *errInfo);

utype* pAB10(const utype *inParam, TCtrlInfo *errInfo);

utype* pAB101(const utype *inParam, TCtrlInfo *errInfo);


utype* pA20(const utype *inParam, TCtrlInfo *errInfo);

utype* pDealAB10(const utype *inParam, TCtrlInfo *errInfo);

utype* pDealAB101(const utype *inParam, TCtrlInfo *errInfo);



///#####################SMS BEGIN ##################
utype* pubCallFunc(const utype *puInParam,TCtrlInfo* errInfo);
utype* pubGetSmsParam(const utype* puInParam,TCtrlInfo* errInfo);
utype* pubGetSmsTplt(const utype *puInParam,TCtrlInfo* errInfo);
utype* pubRepSmsTplt(const utype* puInParam,TCtrlInfo* errInfo);
void pubSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
void pubTXSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
void pPubSmsTpltSend(const utype *puInParam,TCtrlInfo* errInfo);
void pPubTXSmsTpltSend(const utype *puInParam,TCtrlInfo* errInfo);
void pPubICrmWorkSheetNT(const utype *inParam,TCtrlInfo *errInfo);
void pubWapPushSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
utype* pPrcSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
utype* pFuncReCfmSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
utype* pNetArgsChk(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" utype* pGetSmsParamInJTJH(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pGetSmsParamInJFK(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryCompMbr(const utype *puInParam,TCtrlInfo* errInfo);
///#####################SMS END ##################
utype* pProdDataQry(const utype *puInParam,TCtrlInfo* errInfo);
///##################### 一卡多号 ##################
utype* pIPubExtInfoRd(const utype *inParam,TCtrlInfo *errinfo);
utype* p4037Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p4037Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pProdOrderDelay(const utype *inParam,TCtrlInfo *errinfo);

utype* pSqlServer(const utype *inParam,TCtrlInfo *errinfo);
utype* pModelContentQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pSplitOrderByRoute(const utype *inParam, TCtrlInfo *errInfo);
utype* pSvcChk(const utype *inParam, TCtrlInfo *errInfo);

//#####################新增营业员自定义费用科目 zhoujz20100726 ##################
utype* pGetAddFeeInfo(const utype *inParam, TCtrlInfo *errInfo);


utype* cQChnGroupRelByParentGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCustByPhoneNoAndMasterServId(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* p1285Query(const utype *puInParam,TCtrlInfo *ptCtrlInfo);

utype* pNullcpp(const utype *inParam, TCtrlInfo *errInfo);



//####################产品管理配置 精品静态配置 ####################
utype* pDealOrdcommend(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pDealPrcStat(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pDealRecommend(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* cQLoginPCGrp(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* cDOrdCommByCommId(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* cIOrdCommHisCommId(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
//####################融合资费增加 ####################
extern "C" utype* p3106Cfm(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p3105Cfm(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pPrcTranXml(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pDealMbrPrcBack(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pDealMbrPrcComple(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pProdOrdCfm(const utype *puInParam,TCtrlInfo* errInfo);
//####################为欠费销户优化增加的专用服务 ####################
utype* pUserDealXH(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pMemberKQChk(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pZhVpmnChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pQRtByPrcId(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);

utype* pPopulateOpMsgList(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateOpMsg(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype *pAlterUsrPrcCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pUunsettask(const utype *inParam,TCtrlInfo *errInfo);
//####################成员管理 ##############################
utype* p1106Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPrcTranXmll(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pImsPrcChk(const utype *puInParam, TCtrlInfo* errInfo);
extern "C" utype* pGetDMTPhoneBycust(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQUserImsChk(const utype* inParam, TCtrlInfo* errInfo);
utype* pTestWangxlc(const utype *inParam, TCtrlInfo *errInfo);

utype* pSIBlackListQry(const utype *uInParam,TCtrlInfo *errinfo);
utype* cQUniCodeDefByCodeClassAndCodeName(const utype *puInParam,TCtrlInfo* errInfo);
utype* cUIsBackOfPdSales(const utype *puInParam,TCtrlInfo* errInfo);


utype* pProdBillDeal(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQUserProdGrpInfo(const utype* inParam, TCtrlInfo* errInfo);
utype* pQUserGroupListByGroupType(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUsrPrdInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUserPrdOutRel(const utype *inParam, TCtrlInfo *errInfo);

utype* pSaveBatchFile(const utype *inParam,TCtrlInfo *errinfo);
utype* batchinsert(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpInfoQryByPh(const utype *InParam,TCtrlInfo *errinfo);

//add by wangxlc SX start
//--家庭网
extern "C" utype*  pMainFamOrderChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pOwnDisplayOrderChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pFamMbrChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pNextFeeChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pMbrOrderLimitChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pFamTFChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pSxFamTransChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pMainFamOrdChk(const utype *inParam, TCtrlInfo *errInfo);
//--V网
extern "C" utype* pDoBusiRegionChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pSxBvMemKWChk(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pYGGLOrderChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pLoginPowerChk(const utype *inParam, TCtrlInfo *errInfo);
//提供给客服的接口
utype* pQMbrByMainId(const utype *inParam,TCtrlInfo *errinfo);
//add by wangxlc SX end
#include <vector>
void splitstring(const string str,vector<string> &vec,string sign);

extern "C" utype* pChkOrdGprs(const utype *inParam,TCtrlInfo *errinfo);
utype* pRecommendSendCheck(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQPrcAndCity(const utype *inParam,TCtrlInfo *errinfo);
utype* pQPrcForCity(const utype *inParam,TCtrlInfo *errinfo);
utype* pChkOrdCity(const utype *inParam,TCtrlInfo *errinfo);
utype* pQMinBill(const utype * puInParam, TCtrlInfo * errInfo);
utype* pQOUBill(const utype * puInParam, TCtrlInfo * errInfo);
utype* pInvoiceVerCfm(const utype * puInParam, TCtrlInfo * errInfo);
utype *pTimeQryMonth(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype *pBillDayCalQry(const utype *inParam,TCtrlInfo *errinfo);

inline string getLoginType(char *pLoginNo)
{
	map<string,string> mapopr;

	mapopr["YzzzzpzHN"] = "01";
	mapopr["YZZZZPTTB"] = "02";
	mapopr["Y18600WEB"] = "03";
	mapopr["Y18600WAP"] = "04";
	mapopr["Y18600SMS"] = "05";
	mapopr["Y18600IVR"] = "06";

	if(mapopr.find(pLoginNo) != mapopr.end())
		return mapopr[pLoginNo];
	else
		return "55";
}
inline string sx_getLoginType(char *pLoginNo)
{
	map<string,string> mapopr;

	mapopr["aa1860"] = "01";	//网厅
	mapopr["mcsms0"] = "02";	//短厅
	mapopr["mcwap0"] = "03";	//wap厅
	mapopr["yjboss"] = "04";	//一级boss
	mapopr["yjpaym"] = "05";	//无线音乐平台
	mapopr["YJKCR0001"] = "06";	//彩铃平台
	mapopr["mcadc0"] = "07";	//ADC平台
	mapopr["aa1865"] = "08";	//IVR 自助语音台

	if(mapopr.find(pLoginNo) != mapopr.end())
		return mapopr[pLoginNo];
	else
		return "55";
}
utype* pProdMaxNumChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pFundAllocate(const utype *puInParam,TCtrlInfo* errInfo);
//透明消费增加代码
utype* pQOutOprErrMain(const utype *inParam,TCtrlInfo *errInfo);
utype* pQOutOprErrDetail(const utype *inParam,TCtrlInfo *errInfo);
utype* pIOutOprErrInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pUOutCallOprInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pQOutErrInfoDetail(const utype *inParam,TCtrlInfo *errInfo);
//优惠城市名称查询
utype* pQUsrCityInfo(const utype *inParam,TCtrlInfo *errinfo);
utype* pFirOrdChk(const utype *inParam,TCtrlInfo *errInfo);

utype* pQUserPrcCredit(const utype *inParam, TCtrlInfo *errInfo);//add by dicy
utype* pImsUserInfoQry(const utype *inParam, TCtrlInfo *errInfo);//>>>>>>> .r953

utype* pGrpOrdInfoQryFor2DB(const utype *inParam,TCtrlInfo *errinfo);
utype* pQUsrProdInfoF2DB(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpUserQryFDB(const utype *inParam,TCtrlInfo *errinfo);
utype* pQUserBusiInfo(const utype *inparam,TCtrlInfo *errInfo);
utype* pMASXXJQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pTTUser(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pActionMapForTT(const utype *inParam, TCtrlInfo *errInfo);
utype* pUsrFamilyQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pSelCataQry(const utype *inParam, TCtrlInfo *errInfo);
//精品配置 add by gaohn
utype* pRecmdCfgNewQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pQPMSqlCfg(const utype *inParam, TCtrlInfo *errInfo);

utype* pUserBusiInfo(const utype *inparam,TCtrlInfo *errInfo);
utype* pUserBusiInfoQry(const utype *inparam,TCtrlInfo *errInfo);
utype* pUserBusiInfoByPast(const utype *inParam,TCtrlInfo *errInfo);
utype* pNewBusiQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pBusiDescQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pPrcClassRecursiveQry(const utype *inParam,TCtrlInfo *errInfo);

extern "C" utype* pChkNextBillRule(const utype *inParam,TCtrlInfo *errInfo);
utype* pUpdateUserTeamInfoForBill(const utype *inParam, TCtrlInfo *ptCtrlInfo);

void pubSmsSendSX(const utype *puInParam,TCtrlInfo* errInfo);
utype* pubGetSmsTpltSX(const utype *puInParam,TCtrlInfo* errInfo);
utype* pLoginPowerChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pQMbrByMainId(const utype *inParam,TCtrlInfo *errinfo);
utype* pUsrPrcRtChk(const utype *puInParam, TCtrlInfo *errInfo);
utype* pIUserTransPrc(const utype *puInParam,TCtrlInfo* errInfo);
utype* pUUserTransPrc(const utype *puInParam,TCtrlInfo* errInfo);
utype* pDUserTransPrc(const utype *puInParam,TCtrlInfo* errInfo);
utype* pFriendChkSX(const utype *puInParam,TCtrlInfo* errInfo);
utype* pUsrPrcTrans(const utype *inParam, TCtrlInfo *errInfo);
utype* pOprPMCodeCfg(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pOprPMSqlCfg(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

utype* pHomeShtNumQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pHomeShtNumChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pVPMNMbrQry(const utype *inParam,TCtrlInfo *errinfo);

//vip担保业务
utype* p1339BusiChk(const utype *inParam, TCtrlInfo *errInfo);
utype* p1339Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1339PreDeal(const utype *inParam, TCtrlInfo *errInfo);

utype* pMbrHeadChk(const utype *puInParam, TCtrlInfo* errInfo);
extern "C" utype *p4000Chk(const utype *inparam,TCtrlInfo *ptCtrlInfo);
utype* pPub4000Chk(const utype *inparam,TCtrlInfo *ptCtrlInfo);
utype* p1104UserCreditQry(const utype *inParam, TCtrlInfo *errInfo);

utype* pDZOrderBack(const utype *inParam,TCtrlInfo *errInfo);
utype *pMProdChgChk (const utype *inParam, TCtrlInfo *errInfo);
utype *pQAgeLimit(const utype *inParam,TCtrlInfo *errInfo);
utype *pQOpenLimit(const utype *inParam,TCtrlInfo *errInfo);
utype *pGetMonthDiff(const utype *pInParam,TCtrlInfo *errInfo);
utype *pQPhRuleLimit(const utype *inParam,TCtrlInfo *errInfo);
utype *pQCustLvlLimit(const utype *inParam,TCtrlInfo *errInfo);
utype *pQScoreLimit(const utype *inParam,TCtrlInfo *errInfo);
utype* pMPrcChgRulChk(const utype *inParam, TCtrlInfo *errInfo);

utype *pMember10002Prc(const utype *inParam, TCtrlInfo *errInfo);
utype *pQUserOrdInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryUrOrderInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetGrpOpType(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserSpePrcQry(const utype *inParam , TCtrlInfo *errInfo);
utype *pCTDQry(const utype *inParam , TCtrlInfo *errInfo);
utype *pQUserPrcInfo(const utype *inParam , TCtrlInfo *errInfo);

extern "C" utype* pChkUserPrc(const utype *inParam,TCtrlInfo *errinfo);
utype *pCkUserPrc(const utype *inParam , TCtrlInfo *errInfo);
extern "C" utype* pFamOpenBackChk(const utype *inParam,TCtrlInfo *errInfo);
utype* pGetRing(const utype *inParam, TCtrlInfo *errInfo);

/* add by hanyi 20110922 ***/
extern "C" utype* pUpdateConUserInfoForBillAH(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pUpdateConUserInfoForBillSX(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype *pPubChkPrcBillDaySX(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype *pPubChkPrcBillDayAH(const utype *inParam,TCtrlInfo *errinfo);
/* add by hanyi 20110922 ***/
/* add by zhanghq 20110922 begin*/

utype* pMaxNumChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserOrdChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserOrdQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pTeamMbrQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pVisiblPrdQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserParamQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pMWOrdInfoQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserGprsQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* pUserCanOrdQ_B(const utype *inParam,TCtrlInfo *errinfo);
utype* p4000Cfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pPub4000Cfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pCheckOtherPrc_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pReturnInfoDeal_B(const utype *inReqParam, const utype *inParam, TCtrlInfo *errInfo);
utype* pSendConfirmSms_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pReConfirmChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pPopulateOprInfo_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pPopulateBusiInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateProductList_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pReadProdPrcId_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pMainPrcChg_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pSubProdDeal_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pSpInfoDeal_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateProduct_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateOpMsgList_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateOpMsg_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateProdPrcInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateParGroupMbrInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateGroupInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateTeamInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateTeamMbrInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pPopulateAttrInfo_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pQRtByPrcId_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pSendPrcSms_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pCancelPrc_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkWlanSolFee_B(const utype *inParam,TCtrlInfo *errInfo);
utype* pGetMemberProdPrcInfo_B(const utype *inParam,TCtrlInfo *errInfo);
utype *Common_4000Cfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_UserOrdQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_UserOrdChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserSmsCfm_B(const utype *inParam,TCtrlInfo *errinfo);
utype* Common_pUserSmsCfm_B(const utype *inParam,TCtrlInfo *errinfo);
utype* Common_UserParamQry_B(const utype *inParam,TCtrlInfo *errinfo);
utype* Common_MWOrdInfoQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_MWSendSms_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_UserGprsQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_NetRelChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_RelChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_VisiblPrdQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_VisiblPrcQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_PrdDetailQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_KdInfoQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_Sp1108Cfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_ConDayQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_PassResetCfm(const utype *inParam, TCtrlInfo *errInfo);
utype *pGprsRelChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserGprsPrcQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pKdInfoQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pKdInfoQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pVisiblePrcQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pMWSendSms_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pPassResetCfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pGrpUserQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pCfmMebSign_B(const utype *inParam, TCtrlInfo *errInfo);

/* add by zhanghq 20110922 end*/


/* add by hanyi 20110923 ***/
utype* p4063Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pubSmsSendCfg(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20110923 ***/

/* add by hanyi 20110926 ***/
utype* pPubPushSmsInfo(const utype *inParam, TCtrlInfo *errInfo);

/* add by hanyi 20110929 ***/
utype* Common_QryMemUrFam(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_CfmMebSign(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryNXTUrEc_B(const utype *inParam,TCtrlInfo *errInfo);
utype* Common_QryNXTUrEc_B(const utype *inParam, TCtrlInfo *errInfo);


/* add by zhanghq20110930 begin */
extern "C" utype* pSvcPauseInit(const utype* puParamIn, TCtrlInfo* errInfo);
extern "C" utype* pBizCtrlSvcPauseCfm(const utype* puParamIn, TCtrlInfo* errInfo);
extern "C" utype* pQYCLBsumOrdChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pTfGrpsChk(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pTfTDChk(const utype *inParam,TCtrlInfo *errinfo);
utype *pProdAcctDeal(const utype *inParam,TCtrlInfo *errinfo);
/* add by zhanghq20110930 end */

utype* pBusiRuleChk(const utype* puParamIn, TCtrlInfo* errInfo);

/* add by zhanghq20111001 begin */
utype* Common_XQCHX_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pXQCX_B(const utype *inParam,TCtrlInfo *errInfo);
/* add by zhanghq20111001 end */

/* add by hanyi 20111003  */
utype* pUserOrdInfoClass_B(const utype *inParam, TCtrlInfo *errInfo);
utype *pPrcLevelChg_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_pPrcLevelChg(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111003  */

/* add by hanyi 20111004  */
utype* pUserLimitDeal(const utype *inParam, TCtrlInfo *errInfo);
utype* cQVillageResByIdNo(const utype * inParam,TCtrlInfo *errInfo);

/* add by hanyi 20111008  */
extern "C" utype* pDYCancelChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQBizCodeByCust(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQXXTByCust(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pQXXTMbrFeeChk(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pQProdOrdByCust(const utype *puInParam, TCtrlInfo *errInfo);
/* add by hanyi 20111008  */

/* add by hanyi 20111009  */
utype* pUserPrcSmsSend_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pNewBusiQryWeb(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserOrdProdQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserOrdAllQry_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111009  */

/* add by hanyi 20111011  */
utype * pPrcExpirTimeRule(const utype *puInParam, TCtrlInfo *errInfo);
utype* p4000WebCfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdSelNumChk_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by zhanghq20111001 end */

/* add by hanyi 20111003  */
utype* pUserOrdInfoClass_B(const utype *inParam, TCtrlInfo *errInfo);
utype *pPrcLevelChg_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_pPrcLevelChg(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111003  */

/* add by hanyi 20111004  */
utype* pUserLimitDeal(const utype *inParam, TCtrlInfo *errInfo);
utype* cQVillageResByIdNo(const utype * inParam,TCtrlInfo *errInfo);

/* add by hanyi 20111008  */
extern "C" utype* pDYCancelChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQBizCodeByCust(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQXXTByCust(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pQXXTMbrFeeChk(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pQProdOrdByCust(const utype *puInParam, TCtrlInfo *errInfo);
/* add by hanyi 20111008  */

/* add by hanyi 20111009  */
utype* pUserPrcSmsSend_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pNewBusiQryWeb(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserOrdProdQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserOrdAllQry_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111009  */

/* add by hanyi 20111011  */
utype * pPrcExpirTimeRule(const utype *puInParam, TCtrlInfo *errInfo);
utype* p4000WebCfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pProdSelNumChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pBatchSubProdDeal_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
/* add by hanyi 20111011  */

/* add by hanyi 20111012  */
utype* pGetUserPrcHis_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_GetUserPrcHis_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111012  */

/* add by hanyi 20111013  */
utype* Common_pSIInfoListQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_pGrpPrdPrcQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_pGrpPrdListQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_pGrpUsrPrdQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_pGrpPrdOrdQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_pGrpSpecPrdQry_B(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pQueryContractBalance(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111013  */

/* add by hanyi 20111017  */
extern "C" utype* pDelMbrChk(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111017  */

/* add by hanyi 20111019  */
utype*  pGrpUserPrcQry_B(const utype *InParam,TCtrlInfo *errinfo);
utype* pQUserOrderInfoSP_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111019  */

/* add by hanyi 20111021  */
utype* pGetJTUsrProdMsg_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111021  */
utype* pGetMastUserList(const utype *inParam, TCtrlInfo *errInfo);
utype * pQOneSimMultiNo(const utype *inParam, TCtrlInfo *errInfo);

/* add by hanyi 20111026  */
utype* Common_JTVWInfoQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pGrpInfoQryByPh_B(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pProdActRecordLimit(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pProdRecomInfoLimit(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pPubOrLimit(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pPubAndLimit(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pPubSellLimit(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111026  */

/* add by hanyi 20111027  */
extern "C" utype* pUserProdCntQry(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111027  */

/* add by hanyi 20111028  */
utype* Common_UserQryChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserQryChk_B(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pMbrPrcOrdThreeChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pKQUserPrcQry(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111028  */

/* add by hanyi 20111029  */
extern "C" utype* pOrdWarnInfoChk(const utype *inParam, TCtrlInfo *errInfo);

utype* Com_pSpInfoQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pSpInfoQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype *pNetRelChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pGrpMbrInfoQryByAddServiceNoMastSvcId(const utype *inParam,TCtrlInfo *errinfo);
utype* pGrpMbrInfoQryByServiceNo(const utype *inParam,TCtrlInfo *errinfo);
utype* Com_pGrpUserQry(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111029  */

/* add by hanyi 20111101  */
utype* pGrpMbrRoleQryByServiceNo(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pMbrVPMNOrdChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pKDNoFeeUseMonthChk(const utype *inParam, TCtrlInfo *errInfo);
utype* p4073Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserPrcHisByIdNoAndOpTime(const utype *inParam, TCtrlInfo *errInfo);
utype* p4073Qry(const utype *InParams, TCtrlInfo *errInfo);
utype* p4076Chk(const utype *inParam, TCtrlInfo *errInfo);
utype* p4076Cfm(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype* pGJMYOrdChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pGJZBOrdChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkCanProdVld(const utype *inParam, TCtrlInfo *errInfo);
utype* p3971CfmL(const utype *puInParam, TCtrlInfo *errInfo);
utype* pOrderBuildL(const utype *inParam, TCtrlInfo *errInfo);

/* add by hanyi 20111101  */


/* add by hanyi 20111104  */
utype* pQRegionIdByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype* common_CfmMember_B(const utype *inParam, TCtrlInfo *errInfo);
utype *pCfmMember_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pPrcDynInfosQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQSearchIdContentRel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPrcAddInfosQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQryPrcByConditions(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPrcActionQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckUpdateFlag(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQUsrPrcInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubPrcActionQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpUserInfoQry_B(const utype *inParam,TCtrlInfo *errinfo);

/* add by hanyi 20111104  */

/* add by zhaojie 20111104  */
utype* pTurnOutXml(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryIdNoByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);


/* add by zhaojie 20111104  */


utype* pConUserRelIF(const utype *inParam, TCtrlInfo *errInfo);


/* add by hanyi 20111107  */
utype *p4000BatchCfm_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111107  */

/* add by hanyi 20111108  */
utype* p4074Qry(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pProdContractLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryBindUserInfo_B(const utype *inParam,TCtrlInfo *errinfo);
/* add by hanyi 20111108  */

/* add by hanyi 20111109  */
extern "C" utype* pAddMbrBrandChk(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111109  */

/* add by hanyi 20111110  */
utype* pGrpMbrInfoQryByPhoneNo(const utype *inParam,TCtrlInfo *errinfo);
/* add by hanyi 20111110  */

/* add by hanyi 20111111 */
utype* pQKdTimeInfo(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pBindRuleAH(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pBindRuleSX(const utype *inParam,TCtrlInfo *errInfo);
utype* pConfirmSmsSend(const utype *puInParam,TCtrlInfo* errInfo);
/* add by hanyi 20111111 */

/* add by hanyi 20111114 */
extern "C" utype* pOrdPrcLimitInfoChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C"  utype *p1119Finish(const utype *inParam,TCtrlInfo *errinfo);
extern "C"  utype *p1119SmsSendAH(const utype *inParam,TCtrlInfo *errinfo);
extern "C"  utype *p1119SmsSendSX(const utype *inParam,TCtrlInfo *errinfo);
utype *pChkUsrPwd(const utype *inParam,TCtrlInfo *errInfo);
/* add by hanyi 20111114 */

/* add by hanyi 20111115 */
utype* pFamilyUpdateNumChk_B(const utype *inParam, const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* pUserOrdSpQry_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUsrOrdQryAll_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pCLDOrderQry_B(const utype *inParam,TCtrlInfo *errInfo);
utype *pCLDUserQry(const utype *inParam, TCtrlInfo *errInfo);
utype* p3572NewOpQry(const utype *inParam, TCtrlInfo *errInfo);
int GetColorBell(const utype *inParam,TCtrlInfo *errInfo);
int GetSMS(const string strIdNo,string BusinessNo,string strContractNo);
utype* p7429Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p7315UserCheck(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111115 */

/* add by huangpp 20111116 */
extern "C" utype* p1147BackLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* pAdviceContent_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_pAdviceContent_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_p4000BatchCfm_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by huangpp 20111116 */

/* add by hanyi 20111117 */
utype* pChkBathVld(const utype *inParam, TCtrlInfo *errInfo);
int GetSMS(const utype *inParam,TCtrlInfo *errInfo);
utype* pGroupMbrQuit(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111117 */

/* add by huangpp 20111117 */
extern "C" utype* p1147Chk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1147pubCheck(const utype *inOprInfo,const utype *inLimitInfo,const utype *inInputValueInfo,TCtrlInfo *errInfo);
/* add by huangpp 20111117 */

/* add by hanyi 20111119 */
utype *pGetMonthDiff(const utype *pInParam,TCtrlInfo *errInfo);

utype *pSetDelPrcChk(const utype *pParmaIn,TCtrlInfo *errinfo);
utype *pPrcBusiRelChk(const utype *pInParam,TCtrlInfo *errinfo);
utype *pSetPrdListTime(const utype *pInParam,TCtrlInfo *errinfo);
utype *pPrcSetForTrance(const utype *inParam,TCtrlInfo *errinfo);
utype* p1104Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pQFamilyNews_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_QFamilyNews_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111119 */

/* add by hanyi 20111121 */
extern "C" utype* pMaterPhoneQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pNewShortNumUseChk(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111121 */

/* add by hanyi 20111124 */
utype *pCfmBlackWhiteListName_B(const utype *inParam, TCtrlInfo *errInfo);
utype *pECMemberCfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pSpProdCataQry(const utype *inParam, TCtrlInfo *errInfo);
utype *pQTimeByOffSet(const utype *inParam,TCtrlInfo *ptCtrlInfo);
/* add by hanyi 20111124 */

/* add by hanyi 20111125 */
utype* Common_CardPayChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* Common_SendPushMsg_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pCardPayChk_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pSendPushMsg_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111125 */

extern "C" utype* pSyncrtePheExchgChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pIMSFuseNetOrdChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pFreePhonePoolChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pCaiLingAddChk(const utype *inParam, TCtrlInfo *errInfo);

utype* pUsrFreePrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pMbrModMainMbrPrcChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pMainMbrModMbrPrcChk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pIsOrderTermByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryMkStaticDate(const utype *inParam, TCtrlInfo *errInfo);

//liangqi add for 9元幸福卡叠加亲情号码资费的业务规则20111218 begin
extern "C" utype* pChkUserXXPrcSX(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pBackProdInfoChk(const utype *inParam, TCtrlInfo *errInfo);

//liangqi add for 9元幸福卡叠加亲情号码资费的业务规则20111218 end

/* add by hanyi 20111215 */
utype* Common_pAlterUsrPrcCfm_B(const utype *inParam, TCtrlInfo *errInfo);
utype *pAlterUsrPrcCfm_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111215 */

/* add by huangpp	 20111216 */
extern "C"  utype* p4966Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQResSellByImei(const utype *inParam, TCtrlInfo *errInfo);
/* add by huangpp 20111216 */
utype* pQMbrCount(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryMbrRoleNum(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryAttrInfo(const utype *inParam, TCtrlInfo *errInfo);

utype* pPubQryOprLocusMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUptOprLocusMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpenMdlInfQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpenMdlInfAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDealMdlInf(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/* add by hanyi 20111223 */
utype* pFamilyShortNumChk_B(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111223 */

/* add by hanyi 20111224 */
utype* pChangeAction(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20111224 */

utype* pQMktTypeImei(const utype *inParam, TCtrlInfo *errInfo);
utype* pReplaceImeiNo(const utype *inParam, TCtrlInfo *errInfo);

/* add by hanyi 20120106 */
utype* pQUserAttrInfos(const utype *inParam, TCtrlInfo *errInfo);
/* add by hanyi 20120106 */

/* add by hanyi 20120107 */
utype* pInterSendSms_B(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/* add by hanyi 20120107 */

utype* pMarHappSendsQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pMarHappSendsCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pMarSendsTailQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pMarSendsSourceQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pSendsConSume(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/* add by zhaojie 20120117 */
utype* p4967Cfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p4967FeeCfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p4967Rbk(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetProdBackBusiInfo(const utype *inParam, TCtrlInfo *errInfo);
/* add by zhaojie 20120117 */
/* add by zhaojie 20120207 */
utype* pQryTroubleInfo(const utype *inParam, TCtrlInfo *errInfo);utype* pAcceptQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetProdBackBusiInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryTroubleInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* p4967Cfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p4967FeeCfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p4967Rbk(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p4968Cfm(const utype *inParam, TCtrlInfo *errInfo);
/* add by zhaojie 20120207 */

utype* pADC_ECMebChg_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pADC_ECChgUser_B(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pGetSmsCustNameError(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pGetSmsCustNameOK(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetBusiInfo_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pSameCityChk_B(const utype *inParam, TCtrlInfo *errInfo);

utype* pQryDiscutInfo(const utype *puInParam, TCtrlInfo *errInfo);
utype* pSetDiscutInfo(const utype *puIn, TCtrlInfo *errInfo);
utype* pOrderDiscutInfo(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQryUrOrderInfo(const utype *inParam, TCtrlInfo *errInfo);

/* add by zhaojie 20120224 */
utype* p4035QPayAccept(const utype *inParam, TCtrlInfo *errInfo);
utype* p4035Lottery(const utype *inParam, TCtrlInfo *errInfo);
utype* pQSmsCfgInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQSmsCfgByMeansId(const utype *inParam, TCtrlInfo *errInfo);
utype* p4966SendRedBag(const utype *inParam, TCtrlInfo *errInfo);
extern "C"  utype* p4966Rbk(const utype *inParam, TCtrlInfo *errInfo);
/* add by zhaojie 20120224 */
extern "C" utype* pChkTimeExpect(const utype *inParam,TCtrlInfo *errInfo);

utype* pQPrcByCid(const utype *inParam,TCtrlInfo *errInfo);
utype* pPrcClassQry(const utype *inParam,TCtrlInfo *errInfo);

extern "C" utype* pChkSiBlackInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pUsrPrcTrans(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChk1109Back(const utype *inParam,TCtrlInfo *errInfo);

/****** added by biyj at 2012-3-6 11:33:54 begin for exercise ******/
utype* pCustConInfoQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pEquipSmsSend(const utype *inParam, TCtrlInfo *errInfo);
utype* pFinishSmsSend(const utype *inParam, TCtrlInfo *errInfo);
utype* pubEquipSmsTplt(const utype* puInParam,TCtrlInfo* errInfo);
utype* cQDualBysOpTimeAnd1(const utype * inParam,TCtrlInfo *errInfo);
/****** added by biyj at 2012-3-6 11:33:54 end for exercise ******/
utype* pHomeShtNumQry(const utype *inParam, TCtrlInfo *errInfo);

utype* p1339BusiChk(const utype *inParam, TCtrlInfo *errInfo);
utype* p1339Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1339PreDeal(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUserInfoByLt(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubCallFunc_L(const utype *inParam, TCtrlInfo *errInfo);

//extern "C" utype* pBindRuleAH(const utype * inParam,TCtrlInfo *errInfo);
//extern "C" utype* pBindRuleSX(const utype * inParam,TCtrlInfo *errInfo);
// zhaoje 2012/03/07 start
utype* pSaleProdList(const utype *inParam, TCtrlInfo *errInfo);
utype* pBusiInfoProdList(const utype *inParam,const utype *uInBusiUap, TCtrlInfo *errInfo);
utype* p4035IntCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p4035IntChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pA24(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pA14(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pA15(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pA26(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pA10(const utype *inParam, TCtrlInfo *errInfo);
utype* pA00(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pA18(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pA19(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pA25(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pA04(const utype *inParam, TCtrlInfo *errInfo);
utype* pA11(const utype *inParam, TCtrlInfo *errInfo);
utype* pA02(const utype *inParam, TCtrlInfo *errInfo);
utype* pB02(const utype *inParam, TCtrlInfo *errInfo);
utype* pA17(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pStrrep(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUserUnionPhone_B(const utype *inParam, TCtrlInfo *errInfo);
utype *pMarkTimeQry(const utype *inParam,TCtrlInfo *ptCtrlInfo);
utype* p4035SmsReplace(const utype *inParam, TCtrlInfo *ptCtrlInfo);
// zhaoje 2012/03/07 start
extern "C" utype* pChkOlOrderInfo(const utype *inParam,TCtrlInfo *errInfo);

utype* pTest_B(const utype *inParam, TCtrlInfo *errInfo);

utype* pSaleProdList1(const utype *inParam, TCtrlInfo *errInfo);
utype* pBusiInfoProdList1(const utype *inParam,const utype *uInBusiUap, TCtrlInfo *errInfo);

extern "C" utype* pPrcSmsSend_AH(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" utype* pPrcSmsSend_SX(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" utype* pubGetSmsParam_SX(const utype* puInParam,TCtrlInfo* errInfo);
extern "C" utype* pubGetSmsParam_AH(const utype* puInParam,TCtrlInfo* errInfo);
extern "C" void pubSmsSend_AH(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" void pubSmsSend_SX(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" void pPubSmsTpltSend_AH(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" void pPubSmsTpltSend_SX(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" utype* pFuncReCfmSmsSend_AH(const utype *puInParam,TCtrlInfo* errInfo);
extern "C" utype* pFuncReCfmSmsSend_SX(const utype *puInParam,TCtrlInfo* errInfo);


utype* pPopuAttrInfo(const utype *inParam, TCtrlInfo *errInfo);

utype* pPubUserSvcAllqq(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubUserSvcAll(const utype *inParam, TCtrlInfo *errInfo);
utype* pQShortNum(const utype *puInParam, TCtrlInfo *errInfo);
utype* pOpenMdlHeadChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpenMdlCellDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpenMdlLineDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserMainPrcYK(const utype * inParam,TCtrlInfo *errInfo);
utype* pQUserMainPrcYK1(const utype * inParam,TCtrlInfo *errInfo);
utype* pQryMasterType(const utype *inParam, TCtrlInfo *errInfo);

utype* pQGrpMbrNumByIdNo(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pPubProdPrcQry_SX(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pPubProdPrcQry_AH(const utype *puInParam, TCtrlInfo *errInfo);

utype* pFamilySmsToMain_B(const utype *inParam, TCtrlInfo *errInfo);

utype* pPubKdPrcQry(const utype *puInParam, TCtrlInfo *errInfo);

utype* pHppQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTDPrcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pQGrpInfoByAddServiceNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pLossProdQry(const utype *inParam , TCtrlInfo *errInfo);
utype* pA014(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pAddSvcAttrNode(utype *uUnicodedefList, utype *uNoteForProduct, utype *uTemp , utype *uNoteForProdprcInfo, TCtrlInfo* errInfo);

extern "C" utype* pChkUserDataFlow(const utype *inParam,TCtrlInfo *errinfo);
utype* pPubSqlCfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pBatchOpenBackRule(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pChkBVSpecialGrp(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype* pVWGetSmsParam(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkBIsCanJVByA(const utype *inParam, TCtrlInfo *errInfo);
utype* pBJoinVpmn(const utype *inParam, TCtrlInfo *errInfo);
utype* p4073CustQry(const utype *InParams, TCtrlInfo *errInfo);
utype* pQryDiscutInfo_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkIMSUser(const utype *inParam,TCtrlInfo *errInfo);
utype* pIUserSpAttrTrace(const utype *puInParam,TCtrlInfo* errInfo);
utype* pRoamSvcChk(const utype *puInParam,TCtrlInfo* errInfo);
utype *pMoveBaseProdChk(const utype *inParam , TCtrlInfo *errInfo);
utype *p1111PrcChk(const utype *inParam , TCtrlInfo *errInfo);

utype *pWapRelChk(const utype *inParam , TCtrlInfo *errInfo);
utype *pQUsrMainPrcInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pQUsrAddPrcInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* pQPreOrder(const utype *inParam, TCtrlInfo *errInfo);
utype* pUPreOrder1(const utype *inParam, TCtrlInfo *errInfo);
utype* pUPreOrder2(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetProvinceId(const utype *puInParam,TCtrlInfo* errInfo);

utype* pQWebPreOrder(const utype *inParam, TCtrlInfo *errInfo);
utype* pUWebPreOrder1(const utype *inParam, TCtrlInfo *errInfo);
utype* pUWebPreOrder2(const utype *inParam, TCtrlInfo *errInfo);
utype* p4000NetRuleChk(const utype *inParam, TCtrlInfo *errInfo);
utype* p4000OweFeeRuleChk(const utype *inParam, TCtrlInfo *errInfo);
utype* p4000BlankRuleChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pIsChkShortNumVmember(const utype *inParam, TCtrlInfo *errInfo);
utype *pWapRelChk_B(const utype *inParam , TCtrlInfo *errInfo);
utype *pQUsrMainPrcInfo_B(const utype *inParam , TCtrlInfo *errInfo);
utype *pQUsrAddPrcInfo_B(const utype *inParam , TCtrlInfo *errInfo);

utype* pQryOffsetInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pSmsSendCtrl(const utype *puInParam,TCtrlInfo* errInfo);
utype* pSpSmsSend(const utype *puInParam,TCtrlInfo* errInfo);

extern "C" utype* pPrcRelChk(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pShortNumChk(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkBillDayChg(const utype *inParam,TCtrlInfo *errInfo);
//utype* pGetPrcRelOrder(const utype *inParam, multimap<string> &MULMAP_ELEMENT,TCtrlInfo *errInfo);

/*add by zhangwqa 20120625*/
utype* p4098BatchAdd(const utype *inParam, TCtrlInfo *errInfo);
utype* p4098Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p4098ReadFile(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryConsoleByGrp(const utype *inParam, TCtrlInfo *errInfo);
utype* p4098BatchDel(const utype *inParam, TCtrlInfo *errInfo);
utype* pSingleDel(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkGrpPower(const utype *inparam, TCtrlInfo *errInfo);




extern "C"  utype * pChkSvcStateIsP(const utype *inParam,TCtrlInfo *errinfo);
extern "C"  utype * pChkSvcStateAndTime(const utype *inParam,TCtrlInfo *errinfo);
extern "C"  utype * pChkDataRemind(const utype *inParam,TCtrlInfo *errinfo);

utype *pIPChangInfoQry(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype * pChkFuseVGrp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPXprcid(const utype *inParam,TCtrlInfo *errInfo);
utype* pGetPrcRelOrder(const utype *inParam, multimap<string,string> &MULMAP_ELEMENT,TCtrlInfo *errInfo);
utype* pQPrcRelyInfo(const utype *inParam,TCtrlInfo *errInfo);

utype *pGetRemindCnt(const utype *inparam,TCtrlInfo *ptCtrlInfo);
utype *pGetBusiAddInfo(const utype *pInparam,TCtrlInfo *errinfo);
utype *pGetBusiDelInfo(const utype *pInparam,TCtrlInfo *errinfo);
utype *pGetBusiType(const utype *inparam,TCtrlInfo *ptCtrlInfo);
utype *pGetBusiUoprInfo(const utype *pInparam,TCtrlInfo *errinfo);
utype *pGetSvcEffExpInfo(const utype *puInparam, TCtrlInfo *errInfo);
utype *pFlagSvcEffRule(const utype *pParamIn,TCtrlInfo *errInfo);

extern "C"  utype * pMonthFeeChk(const utype *inParam,TCtrlInfo *errInfo);

utype *pCTDQry_SX(const utype *inParam , TCtrlInfo *errInfo);
extern "C" utype *pChkPhonePayInfo(const utype *inParam, TCtrlInfo *errInfo);
extern "C"  utype * pChkLimitSend(const utype *inParam,TCtrlInfo *errInfo);


extern "C"  utype * pQorderInfoLoginTime(const utype *inParam,TCtrlInfo *errInfo);
utype* pPrcSpeEffQry(const utype *inParam,TCtrlInfo* errInfo);
extern "C" utype* pChkUserProd(const utype *inParam,TCtrlInfo *errinfo);
extern "C" utype* pChkSXUserDataFlow(const utype *inParam,TCtrlInfo *errinfo);

utype* p1111WebCfm(const utype *inParam,TCtrlInfo *errInfo);
utype* pComOprInfo(const utype *inParam, TCtrlInfo *errInfo);
utype *pTzafeiQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pGeneralProductOrder(const utype *puInParam, TCtrlInfo *errInfo);
utype* pGeneralProduct(const utype *puInParam, const utype *outPrcUap,TCtrlInfo *errInfo);
utype* pGeneralReadPrc(const utype *puInParam, TCtrlInfo *errInfo);

utype* pQPrcOrdMdl(const utype * puInParam, TCtrlInfo * errInfo);
utype* pYyzySmsSend(const utype * puInParam, TCtrlInfo * errInfo);
utype* pChkMarketVuser(const utype * puInParam, TCtrlInfo * errInfo);

utype* p4000MainRuleChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryNowDate(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryDbMktadm(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserWL_B(const utype *inParam, TCtrlInfo *errInfo);
utype* pUsBrTeHxwQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pRiskUsrPrcTrans(const utype *inParam,TCtrlInfo* errInfo);
utype *pPubSmsSendTmp(const utype *inParam, TCtrlInfo *errInfo);
utype* pEffNuChkPrc(const utype *inParam, TCtrlInfo *errInfo);
utype* pTransLoginClassCodeSX(const utype *inParam, TCtrlInfo *errInfo);

