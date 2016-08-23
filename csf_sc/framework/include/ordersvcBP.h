#ifndef __ORDERSVCBP_H__
#define __ORDERSVCBP_H__

extern "C" utype * pQUserOweFee(const utype* puInParam, TCtrlInfo* errInfo);
extern "C" utype* pDelRHUser(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1184Finish(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype* pCreateUserBaseInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pCreateUserRelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pCreateUserResInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pCreateConMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* pUpdateCustMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* p1060FeeDeal(const utype * inParam,TCtrlInfo *errInfo);
utype* p1158UpRes(const utype * inParam,TCtrlInfo *errInfo);
utype* p1158Local(const utype * inParam,TCtrlInfo *errInfo);
utype* pICustUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIServAddNum(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserAddInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubChkBookDeposit(const utype * inParam,TCtrlInfo *errInfo);
utype* p1205DInfoBusi(const utype * inParam,TCtrlInfo *errInfo);
utype* p1205QInfoBusi(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserBillModeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserExpireInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserInnetInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserResInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserServLocInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserSimInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserImsiInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserStateInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserCreditInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pISubscriberAttrInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUFinishOfUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUFinishOfUserStateInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUFinishOfUserBillModeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUFinishOfUserExpire(const utype * inParam,TCtrlInfo *errInfo);
utype* p1222Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserDeadInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserExtDeadInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserAddDeadInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDConExtMovedInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* pIContractInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIContractAddInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIConTrustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIBillPost(const utype * inParam,TCtrlInfo *errInfo);
utype* pIBillPostInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIBillPostAddInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIContractExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIConUserList(const utype * inParam,TCtrlInfo *errInfo);
utype* pIConUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUFinishOfConUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUStateOfCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDCustResOrdInfo(const utype * inParam,TCtrlInfo *errInfo);

extern "C" utype* p1000Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1000Finish(const utype * inParam,TCtrlInfo *errInfo);
utype* pChkSvcNo(const utype* inParam , TCtrlInfo *errInfo);
utype* pQServiceNo(const utype* inParam , TCtrlInfo *errInfo);
utype* p1000QCList(const utype * inParam,TCtrlInfo *errInfo);
utype* p1000QCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pQUserByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pICustResOrdInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetRandPass(const utype * inParam,TCtrlInfo *errInfo);

utype* pChgHandGroup(const utype * inParam,TCtrlInfo *errInfo);


utype* pPubCheckId(const utype * inParam,TCtrlInfo *errInfo);
utype* pCheckBlack(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* pCheckBlack_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pCheckBlack_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckCustNum(const utype * inParam,TCtrlInfo *errInfo);

utype* p1050Init(const utype * inParam,TCtrlInfo *errInfo);
utype* p1050PwdChk(const utype * inParam,TCtrlInfo *errInfo);

/*资源*/
utype* pPubQPhList(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubQSimByPh(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubQSimList(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubQSimRes(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubUResState(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubUSimState(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubSimHand(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubPhoneHand(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* pUpdateResState(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateResStateAfterOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubPhonePre(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubUnLockRes(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubCheckLocNum(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubQryNoByBusiNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pResChkPhoneAndCard(const utype * inParam,TCtrlInfo *errInfo);

/*1110*/
utype* p1110Init(const utype * inParam,TCtrlInfo *errInfo);
utype* p1110QUserSim(const utype * inParam,TCtrlInfo *errInfo);
utype* pQUserSimInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserSimMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* p1110QSimRes(const utype * inParam,TCtrlInfo *errInfo);
//utype* p1110Back(const utype * inParam,TCtrlInfo *errInfo);
utype* p1110FeeDeal(const utype * inParam,TCtrlInfo *errInfo);

utype* pUpdateUserFreeTimes(const utype * inParam,TCtrlInfo *errInfo);
utype* pUpdateSimRes(const utype * inParam,TCtrlInfo *errInfo);
utype* pUpdateImsiInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* p1110UpdateSim(const utype * inParam,TCtrlInfo *errInfo);
utype* p1110Blank(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1110ChgType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1110CheckSpeNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p1110Back(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p2304Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p1110InitAH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p1110InitSC(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p1110InitSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p2271Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p2271Finish(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p1110Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo); 
extern "C"  utype* p1110Finish(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*yuxiao*/
utype* p1052WebChg(const utype * inParam,TCtrlInfo *errInfo);
utype* pURunCodeOfUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUserStateInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pQUserRelDetail(const utype* inParam , TCtrlInfo* ptCtrlInfo);

/*xiaohu*/
utype* pMovedUserBaseInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pMovedConMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* pDeleteUserRelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDeleteUserResInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserDeadInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserExtDeadInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIUserAddDeadInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserStateInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserInnetInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserBillModeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserExpireInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserServLocInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserCreditInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserCreditRec(const utype * inParam,TCtrlInfo *errInfo);
utype* pDSubscriberAttrInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDSpecialListInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserValueInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDPasswdResetInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIContractDeadInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIConExtMovedInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIConAddMovedInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDConTrustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDBillPost(const utype * inParam,TCtrlInfo *errInfo);
utype* pDBillPostInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDBillPostAddInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDCustUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pDConUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserSimInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserResInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDServAddNumInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserModifiedInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDResFreeTimesInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserImsiInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserBrandRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pDUserExpireRec(const utype * inParam,TCtrlInfo *errInfo);
utype* pDBadSMSDetailYYYYMM(const utype * inParam,TCtrlInfo *errInfo);
utype* pDGarageSMSInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* p1052Init(const utype* inParam , TCtrlInfo * errInfo);
utype* pubQueryUserInstantFee(const utype* inParam , TCtrlInfo* errInfo);

utype* p1053Init(const utype* inParam , TCtrlInfo* errInfo);
utype* p1055Init(const utype* inParam , TCtrlInfo* errInfo);
utype* pGroupInfo(const utype* inParam , TCtrlInfo* errInfo);
utype*  pUAgentDictByPhoneNoAndType(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*hao ma yu yue 1004*/
utype* pDCustResOrdInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* pOperateChk(const utype *inParam , TCtrlInfo *errInfo);
void pGetLaterTime(char endTime[18] , char sTime[18] , int LOCK_MINUTES);
/*utype* pICustResOrdInfo(const utype *inParam , TCtrlInfo *errInfo);*/
utype* p1004BackDel(const utype *inParam , TCtrlInfo *errInfo);

utype* p1004QCustRes(const utype *inParam , TCtrlInfo *errInfo);
utype* p1004UnLock(const utype *inParam , TCtrlInfo *errInfo);
utype* p1004Cfm(const utype *inParam , TCtrlInfo *errInfo);
utype* p1004QPhInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* pPubILoginOpr(const utype *inParam , TCtrlInfo *errInfo);
utype* pPubQPhResInfo(const utype *inParam , TCtrlInfo *errInfo);

/*1050*/
utype* pCreateUserFromMoved(const utype *inParam, TCtrlInfo *errInfo);
utype* pIUserInfoFromMoved(const utype *inParam, TCtrlInfo *errInfo);
utype* pIUserExtInfoFromMoved(const utype *inParam, TCtrlInfo *errInfo);
utype* pIUserAddInfoFromMoved(const utype *inParam, TCtrlInfo *errInfo);
utype* pIConInfoFromMoved(const utype *inParam, TCtrlInfo *errInfo);
utype* pIConAddInfoFromMoved(const utype *inParam, TCtrlInfo *errInfo);
utype* pIConExtInfoFromMoved(const utype *inParam, TCtrlInfo *errInfo);
utype* pDUserDeadInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pDUserExtDeadInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pDUserAddDeadInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pDConExtMovedInfo(const utype *inParam, TCtrlInfo *errInfo);
/*销号复装资料入库---用户其他信息资料落地*/
utype* pIUserOtherInfo(const utype *inParam, TCtrlInfo *errInfo);
/*销号复装资料入库---账户其他信息资料落地*/
utype* pIConOtherInfo(const utype *inParam, TCtrlInfo *errInfo);

/*2304*/
utype* p2304(const utype *inParam, TCtrlInfo *errInfo);
utype* p2304BackChk(const utype *inParam, TCtrlInfo *errInfo);
utype* p2304TraceReversal(const utype *inParam, TCtrlInfo *errInfo);
utype* p2304QBkOfferId(const utype *inParam, TCtrlInfo *errInfo);
utype* pRBlackChkTest(const utype *inParam, TCtrlInfo *errInfo);
utype* p2304CfmTest(const utype *inParam, TCtrlInfo *errInfo);

/*自助终端选号*/
utype* pLmtPhListMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetRelExMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* pSaveDisp(const utype *inParam, TCtrlInfo *errInfo);

/*OneBoss 1222*/
utype* p1222SimActive(const utype *inParam, TCtrlInfo *errInfo);
utype* p1222Cfm(const utype *inParam, TCtrlInfo *errInfo);

/*1207 1208 1209 1210*/
utype* p1207AddPh(const utype *inParam, TCtrlInfo *errInfo);
utype* p1208DelPh(const utype *inParam, TCtrlInfo *errInfo);
utype* p1210QueryPh(const utype *inParam, TCtrlInfo *errInfo);
utype* p1207ForAddMany(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1207AddPhMany(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1208ForDelMany(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1208DelPhMany(const utype *puInParam, TCtrlInfo *ptCtrlInfo);


/*网上商城接口*/
extern "C" utype* pUpdateOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pUpdatePay(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSaveOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPreOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pDelOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pCancelIMEI(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*商机转开户预订单入库*/
utype* p1057PreOrd(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*邮寄账单转电子账单*/
utype* p1216Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*副号码逻辑开关机查询*/
utype* p1206Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*宽带绑定号码修改*/
utype* p1187Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1187Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*3839*/
utype* pICustInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pICustExtInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3839Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pICustAddInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pICustContactInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIPersonalCustInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pICustWorkInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pICustEduInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pICustConsumeInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIHomeCustInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIPartyCustInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIPersonalCustMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pICustIdentifyInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pICustCertScanInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1158PhoneQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1158Local(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1158UpRes(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1158Fee(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1158Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1160PhoneQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1160Fee(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pDouSimCheck(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1160Cfm(const utype *inParam, TCtrlInfo *errInfo);
/*1169*/
utype* pColModelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pColModelCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pColModelChg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pColModelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*1167*/
utype* pFileModelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFileColQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1167Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFileModelCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFileColCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1167FileCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFileModelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFileColDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1167FileDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFileModelChg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1167FileChg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*1171*/
utype* pFileTimeQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFileTimeCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFileTimeChg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFileTimeDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*1172*/
utype* p1172Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1000QConLst(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIUserBrandRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*1173 Begin*/
utype* p1173ChkFile(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubDealLine(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubSplitStr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubBatchCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1173FirstNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubReadTxtFile(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubBatchCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*1173 End*/
/*1178 Begin*/
utype*	p1178QryAcc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*	p1178Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	p1178Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	p1178Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*1178 End*/
/*1002 Begin*/
utype*	p1002FileDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	p1002BatchCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*1002 End*/
/*1056 Begin*/
utype*	p1056Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	p1056QryProd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	pISelWorkInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	p1056CfmTemp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	p1056ExtendFee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*1056 End*/
/*1239 Begin*/
utype* p1239QryOrd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*1239 End*/
/*RGetWorkDetail Begin*/
utype*	pGetWorkDetail(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	pGetCustId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*RGetWorkDetail End*/
/*产品接口*/
utype* pInsertUserBrandRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateUserBrandRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDeleteUserBrandRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pInsertUserBillModeInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateUserBillModeInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDeleteUserBillModeInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pInsertConUserInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateConUserInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDeleteConUserInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateUserBrand(const utype *inParam, TCtrlInfo *ptCtrlInfo);


utype* p1001Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1001Add(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1001Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1001Del(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1001Chg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1001Post(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1003Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1060FeeDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1003Del(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1003Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1003ProdQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1003Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p1058Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p1059Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetModelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pInterModelInfo(const utype * inParam,TCtrlInfo *errInfo);
void GetFtpPath();

/*首次激活，通话,有效期计算*/
extern "C" utype*  p1183Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUFirstUseDateOfUserInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUBeginTimeOfUserExpireInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUExpireDateOfUserInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * pDExpireDateOfUserInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*宽带计费帐号&智能网VPMN帐号获取*/
utype* p1000GetAutNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQryAddrCfg(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*公共事业代收费*/
utype* p2310(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2312(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//utype* p2313(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2310Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2313(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pIchargeWorkSheet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2310QueryGet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQChargeOLResul(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pILoginOpr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2310PaySet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2310PayGet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2310PrintlnSet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2310PrintlnGet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2311QuerySet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2310PayGet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2311QueryGet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2313PrestoreGet(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2313PrintlnGet(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2313Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2312Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2312FlushesGet(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p231File(const utype *inParam, TCtrlInfo *ptCtrlInfo);
int readcfg(char *cfgname,char *section,char *key,char *value);
void pGetYesterTime(char endTime[15] , char sTime[15] , int iTimeSs);
int getStatus(int status);
void Generate_Mac(char	*param,char *outmac);

/*业务销售代理（SA）查询*/
extern "C" utype* p231File(const utype *inParam, TCtrlInfo *errInfo);
utype* p1200Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1200SaveSa(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1200Modify(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* rJustFunc(const utype* pu, TCtrlInfo* errInfo);

/*欠费销户*/
extern "C" utype* p1184Cfm(const utype *inParam , TCtrlInfo *errInfo);
utype* pIBlackListInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pIBlackListPhoneInfo(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype*  p1055Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*一卡双号用户查询*/
utype* pQUserRel(const utype *inParam , TCtrlInfo *errInfo);
utype* pGetUserServLoc(const utype *inParam , TCtrlInfo *errInfo);

utype* pDSpanRegTransRd(const utype *inParam , TCtrlInfo *errInfo);

utype* pQUserBaseAttr(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserIDByImsi(const utype *inParam, TCtrlInfo *ptCtrlInfo);


/*代理商信息管理*/
utype* p1204QRes(const utype *inParam , TCtrlInfo *errInfo);
utype * pIAgentDict(const utype *inParam , TCtrlInfo *errInfo);
utype* p1204Cfm(const utype *inParam , TCtrlInfo *errInfo);
utype * pDAgentDict(const utype *inParam , TCtrlInfo *errInfo);
utype* p1204Delete(const utype *inParam , TCtrlInfo *errInfo);
utype* pQGroupName(const utype *inParam , TCtrlInfo *errInfo);
utype* p1263UPassWord(const utype *inParam , TCtrlInfo *errInfo);
utype* p1204Modify(const utype *inParam , TCtrlInfo *errInfo);

/*add by zhusl for testing */
utype* pQUserInfo(const utype *inParam, TCtrlInfo *errInfo);

/*代办售卡现金管理*/
utype* p1205QSellCard(const utype *inParam , TCtrlInfo *errInfo);
utype * pUSellCard(const utype *inParam , TCtrlInfo *errInfo);
utype * pISellCard(const utype *inParam , TCtrlInfo *errInfo);
utype* p1205Cfm(const utype *inParam , TCtrlInfo *errInfo);
utype * pDSellCardInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* p1205Del(const utype *inParam , TCtrlInfo *errInfo);
utype * p1205DInfoBusi(const utype *inParam , TCtrlInfo *errInfo);
utype * p1205QInfoBusi(const utype *inParam , TCtrlInfo *errInfo);

utype* pCustInfoDeal(const utype *inParam , TCtrlInfo *errInfo);
utype* pUserInfoDeal(const utype *inParam , TCtrlInfo *errInfo);

utype* pQCustInfo(const utype *inParam , TCtrlInfo *errInfo);

extern "C"  utype* p1218Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pCheckSmsInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* p1000BusiDeal(const utype *inParam , TCtrlInfo *errInfo);
utype* p1000MBillInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* p1050BusiDeal(const utype *inParam , TCtrlInfo *errInfo);

utype* pUUserSimInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* pUUserImsiInfo(const utype *inParam , TCtrlInfo *errInfo);

utype* pSamplePasswdNotice(const utype *inParam , TCtrlInfo *errInfo);
utype* p1000SmsSend(const utype *inParam , TCtrlInfo *errInfo);
/*公共结构BP*/
utype*	pPubInterface(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	testtest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype * pPubOrderLimit(const utype* puInParam, TCtrlInfo* errInfo);
extern "C" utype* pChkDeposit(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype*	p1110FeeDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
void replacestring(char *s,char *oldstr,char *newstr);
utype*	cQFeeCodeDictByPayType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//extern "C" utype* p1213Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//utype* p1213Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//utype* p1213Refuse(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pISpanRegTransRd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype*	p1000GetAutNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1187Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1187Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1158Fee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1266Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1266Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1264Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p1160Fee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCustContUserByIdNo1(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1050PwdChk(const utype * inParam,TCtrlInfo *errInfo);

extern "C" utype* p1147Rbk(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetOwnorgCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*空中充值代理商好码管理*/
utype* p1265ChgNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1265QueryNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1265DelNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQAgentInfoByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntAgentByGroupId(const utype * inParam,TCtrlInfo *errInfo);

utype* pQGroupName(const utype * inParam,TCtrlInfo *errInfo);
utype* p1263UPassWord(const utype * inParam,TCtrlInfo *errInfo);
utype* p1264Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p1265ChgNo(const utype * inParam,TCtrlInfo *errInfo);
utype* p1265QueryNo(const utype * inParam,TCtrlInfo *errInfo);
utype* p1265DelNo(const utype * inParam,TCtrlInfo *errInfo);
utype* p1266Init(const utype * inParam,TCtrlInfo *errInfo);
utype* p1266Cfm(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype*  p2310Init(const utype *inParam, TCtrlInfo *errInfo);
utype* pIGdkd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryGdktRet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1184Init(const utype *inParam , TCtrlInfo *errInfo);
extern "C"  utype* p1184Back(const utype *inParam , TCtrlInfo *errInfo);
extern "C"  utype*  p1052TDRule(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1002Cfm(const utype *inParam , TCtrlInfo *errInfo);
utype* p2310PrintQryGet(const utype *inParam, TCtrlInfo *errInfo);
utype* pUnitInit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIPreDestroy(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pGetCancelUserGroupType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pDealChangeNO(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1055Del(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQModelAttrCfg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQryAddrCfg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
void pGetYesterTime(char endTime[15] , char sTime[15] , int iTimeSs);
utype* pUFirstUseDateOfUserInfo3(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2313Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateResStateAfterOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* pUFirstUseDateOfUserInfo3(const utype *inParam, TCtrlInfo *errInfo);
utype* p1184Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2310PrintQryGet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pResChkPhoneAndCard(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* pChkSonOfGroupIsActive(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUserSimById(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pSAByProdPrc(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetOwnorgCode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pSAByProdPrc(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p1002Cfm(const utype *inParam , TCtrlInfo *errInfo);

/* zhoujz20100805 */
utype* pDealConUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* p1002PreChkRes(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pDAccountRel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUnitInit(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*宽带密码加密*/
extern "C" void desenc(const char *src, char* dst, size_t len);//加密
extern "C" void desdec(const char *src, char* dst, size_t len);//解密
utype* pBroadEnc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pSeniorUnitInit(const utype * inParam,TCtrlInfo *errInfo);


/*ADD BY LVJY 20100807 批量开户资源校验BP*/
utype* p1002ChkRes(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*RFID更新客户及账户信息*/
utype* pChgRFID(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pOrdLoginQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*资源接口优化修正*/
utype* pUserResOrdBack(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*融合资费*/
utype* pOrderDis(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1000ResOrdBack(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubChkRes(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1000OrdBack(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1000PrcBack(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1000ResOrdBack(const utype *inParam , TCtrlInfo *errInfo);
utype* pSortBusiInfo(const utype *inParam , TCtrlInfo *errInfo);
utype*  pDAccountRel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  pChkMasMemberOweFee(const utype *inParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype*  pFUserGroup(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/* yangzg20100915 */
extern "C" utype*  pQRHGroupMbrInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  pChkSonOfGroupIsActive(const utype *inParam, TCtrlInfo *errInfo);

/*add by yangzg  20101211*/
utype*	p1085Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pPubOpenUserInter(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pOpenExtendInfoDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pCheckIccidInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pOpenExtendInfoDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pPubCustInfoDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pQCustInfoDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pAddGroupMbr(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pIccidCheck(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pPhoneCard(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1055OrdFinish(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*add by dailf 2010-8-20 */
utype* pChgRFID(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUserResOrdBack(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  p9999Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*下列TCutype不存在*/
/* utype* p1000ResOrdBack1(const utype *inParam, TCutype*  pUnitInit(const utype *inParam, TCtrlInfo *ptCtrlInfo); */

utype*  pUnitInit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pOrdLoginQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDealChgNoAndRecovery (const utype *inParam, TCtrlInfo *ptCtrlInfo);

extern "C"  utype* p1218Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype*	pGrpCustInfoDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pSendInnetSms(const utype* inParam,TCtrlInfo* ctrlInfo);

/*add by houboa for SMSSend*/
utype* pSendSms(const utype* inParam,TCtrlInfo* ctrlInfo);
utype* pSendInnetSms(const utype* inParam,TCtrlInfo* ctrlInfo);
extern "C" utype* pSendAlertSMS(const utype *inParam, TCtrlInfo *ptCtrlInfo);

#include <vector>
void strDeal(const string str,vector<string> &vec,string sign);

/*gejun*/
utype*  p1054ChkPhoneNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pIPreDestroy(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pPubGetBindNO(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDealBindInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDUserPreDestroy(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype*  pDDestroyTranseFee(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//铁通融合
utype*	pChkTSource(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

void compute(const char * curAreaCode ,  otl_connect* crm_db);
utype*  p1054Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pGetActionIdRunCodeByOpcode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pQBindPhoneNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDDestroyTranseFee(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDUserPreDestroy(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDealChgNoAndRecovery (const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1090Cfm(const utype* puInParam,TCtrlInfo* ptCtrlInfo);
utype*  pIPreDestroy(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pQCustInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*  ptiansqatest(const utype *inParam, TCtrlInfo *errInfo);
utype*  ptiansqatest2(const utype *inParam, TCtrlInfo *errInfo);
utype*  ptiansqatest3(const utype *inParam, TCtrlInfo *errInfo);
utype*  p1054Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p1054ChkPhoneNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pIPreDestroyFee(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pPhoneCard(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1055OrdFinish(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSendAlertSMS(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype*  pChargeOpCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1092Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1093Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* p1093Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryUserBaseForWeb(const utype *inParam, TCtrlInfo *errInfo);
utype* getOrderModel(const utype *inParam, TCtrlInfo *errInfo);
utype* p1053CfmForWeb(const utype *inParam, TCtrlInfo *errInfo);

/*铁通融合销户*/
utype*  p1055Del(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDealChangeNO(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pBatchDelUser(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDealBindInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDealGroupProductSituation(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDealGroupUserSituation(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pGetCancelUserGroupType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pGetPhoneNoAndSvcIdById(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pIDalertResultMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pIUserHisToryTemp(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype*  pPubGetBindNO(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pISpanRegTransRd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1213Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1213Refuse(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*tiansqa*/
utype* pQBillDayByUserDay(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIniBillDayQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*  pCheckDestroyPhoneNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//分月返回用户预销验证
extern "C" utype* pChkReturnMonth(const utype *inParam, TCtrlInfo *errInfo);

//结账日资料落地
utype* pCreateUserDayInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pDeleteUserDay(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIUserDayInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUUserDayInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQrySvcByProduct(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pQBindPhoneNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateUserExtInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pChkPrdUnNatural(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
//用户销户订单信息查询接口
utype*	pQUserOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C"	utype*	pRefundmentRule(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pAddAccPrd(const utype *inParam,TCtrlInfo *errinfo);
/*铁通融合开户*/
utype*	pChkTSource(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* 	p1000TPortBack(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*tiansqa start*/
utype* pUpdateUserExtInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  pChkReturnMonth(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype *pDelAccPrd(const utype *inParam,TCtrlInfo *errinfo);
utype*  pDCustMngObjInfoByIdCustRel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p1050UserQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pOrderGprs(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQrySvcByProduct(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype*  pIUserDayInfoFromMoved(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDUserDayDeadInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//跨区入网
utype* p1213UserQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1213Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1213OldUser(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1213QRouteKey(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//警示级黑名单优化
utype* pChkRunTime(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//电子渠道100%
utype* p1050InitForWeb(const utype *inParam, TCtrlInfo *errInfo);

/*tiansqa end*/
utype*  pCheckDestroyPhoneNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pPubQuitInt(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pQryAssureInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIAssureMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQOpenWebCtrl(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQBillDayByUserDay(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*  pIUserHisToryTemp(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pModifyReNeNnTime(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  p1055PreProdLimit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  p1055MobileFeeLimit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  p1055DiffLoginLimit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  p1055GroupAllUserMbrInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);


/*tiansqa*/
utype* pQryAssureInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*tiansqa*/


utype* pIConUserInfoIf(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pUserDayAlter(const utype *inParam, TCtrlInfo *errInfo);
utype* pDeleteUserDay(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pQryAssureDetailInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1004Lock(const utype *inParam , TCtrlInfo *errInfo);

/*add by zhanghq*/
utype*  pIDalertResultMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p1055Del(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/**add by  hanyi**/
utype*  pIUserBillDayDeadInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cQUniCodeDefByGroupIdAndCodeClass(const utype * inParam,TCtrlInfo *errInfo);
/*xiangyl删除销户相关信息*/
utype* pDCustMngObjInfoByIdCustRel(const utype * inParam,TCtrlInfo *errInfo);
utype*  pPubGetBindNO(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1004Lock(const utype *inParam , TCtrlInfo *errInfo);
utype* pQryAssureDetailInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

extern "C"  utype* pBusiCodeDisSX(const utype* inParam,TCtrlInfo* ptCtrlInfo);
extern "C" utype* pBusiCodeDisAH(const utype* inParam,TCtrlInfo* ptCtrlInfo);
utype* pUpdateUserBrand(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cQUrUniCodeDefByCodeClass(const utype * inParam,TCtrlInfo *errInfo);

extern "C" utype* pSendOpenSmsSX(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSendOpenSmsAH(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pGetPubRouteInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	pAirOpenUserInter(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pOpenEffExpDate(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p1013Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pMbrQuitGroupDestroy(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pQUserMbrType(const utype *inParam, TCtrlInfo *errInfo);
utype*	pADCOpenUserInter(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p1012QPrc(const utype *inParam , TCtrlInfo *errInfo);
utype* p1012QPrcDet(const utype *inParam , TCtrlInfo *errInfo);
utype* p1012Cfm(const utype *inParam , TCtrlInfo *errInfo);

utype*	p1010Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	p1010(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pActiveBatchOpen(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*	p1010Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pUUserStateOfUserInfo4(const utype *inParam, TCtrlInfo *errInfo);
utype*  pDCustUserBusiLimit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pSendActiveSms(const utype* inParam,TCtrlInfo* ctrlInfo);
utype* p1349DataSyn(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*  pDelActiveUserLimit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQryActiveTime(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  pOverDict(const utype *inParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* p1350Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p1350Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*G3OP增加预设小区*/
utype*	pOrderAddress(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pQryAddrOrd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pChkUserRel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pSavePreOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pDCustResOrdInfoBak(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*换号新增bp*/
extern "C" utype* p1075PreDelCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1098ReCallCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1097Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1098Scan(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C"	utype*  pOverDict(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1097Init(const utype *inParam, TCtrlInfo *errInfo);
utype* p1097(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1097Finish(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C"	utype*  pChkIsCH(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C"	utype*  pChkMainIsSingle(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//有限电视
utype* p1092Cfm(const utype *inParam, TCtrlInfo *errInfo);
//跨区入网
utype* p1213Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1213Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1213ChkScore(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1213Finish(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype*  pAutoAddProd(const utype *inParam, TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeClassAndDate(const utype * inParam,TCtrlInfo *errInfo);
/*wangzxa 电子渠道宽带开户&对账业务*/
utype* pQUserSignInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pCleanPay(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pQryChkPayOut(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pOpenOrdQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype*	pOpenEffExpDate(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pAddGroupMbr(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//合并需求新增
utype*  pSavePreOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*	pDCustResOrdInfoBak(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype*	pOrderGprs(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	p1010SMSChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pCreateUserBusiLimit(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//省内携号转网yinzx
extern "C" utype*  p1351Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  pGroupChgQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1351BusiDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype*  p1027(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pMasterCheckInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pPubOpenBusiInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pPubProdModifyBusiInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pPubSalvePhoneBusiInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pSlaveCheckInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  pDestroyUserBusiInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p1028(const utype *inParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pCheckUserAddInfo(const utype *inParam,TCtrlInfo *errInfo);
utype*	pTestMemer(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* keyValue2Utype( char* outMsg);
utype*  p1052test(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype*  pPubUPhoneRes(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p1030Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p1030Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p1030Upd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//yinzx 2012/6/18 16:18:51
extern "C" utype *pQUserIsGrpMbr(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pChkOBackCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//add by hz 20120710
utype*  pChkOrdDone(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*add by wangxinf 20120712*/
utype *pTzafeiQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pPreOpenDeal(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkUserCancelIf(const utype *inParam,TCtrlInfo *errInfo);//add at 2012-9-26 17:22:18
utype* cQLastUserDeadInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQContPersonalCustInfoHisByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype*  pWebFamPrcQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
#endif

#ifdef __ORDERSVCBP_H__
#define _S_V_C_ 1024
#endif 
