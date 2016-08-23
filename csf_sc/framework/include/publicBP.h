#ifndef __PUBLICBP_H__
#define __PUBLICBP_H__


//###############################3、BOSS接口BP#########################################################/
//********************************************************BP*************/

utype* pQFeeReminder(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQbalance(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p8833Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p8832Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryContractBalance(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryContractPreDet(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserOweFee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserDeadOweFee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryContractDeposit(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserLastPay(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserMark(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubUpdatePhoneRes(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubChangeUserMark(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
void pPubICrmWorkSheetNT(const utype *inParam,TCtrlInfo *errInfo);
utype* pubQWideTraffic(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserInstantFee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCardPayByNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCOweFixFee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserInfoForSH1(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubAgentDeductFee(const utype *inParam,TCtrlInfo *errInfo);
//################################################################################################/

///*######################BP###2、资源接口BP#####################################################################*/
utype* pubUpdateSimRes(const utype * inParam,TCtrlInfo *errInfo);
utype* pubQuerySIMInfoBySimNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserSimQuery(const utype * inParam,TCtrlInfo *errInfo);
utype* pubQuerySimRes(const utype * inParam,TCtrlInfo *errInfo);
utype* pubQueryPhoneRes(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* pubQuerySimResByPhone(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* pPubResChkPhoneAndCard(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubActivCard(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCardNum(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQryChkCardInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUpdCardByChgInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQryNoInfoByNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQryOrChnBusiNum(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUpdNoSimInfoByOpr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQBlankSimByNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubWritSimNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUpdResByBookObject(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUpdNoByNoOrg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQryJFLRES(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryResCODEByBlur(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUpdJFLRESStore(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQryChkResInfoBySta(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUpdResInfoByNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubUTTHlrByNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
///*######################BP###资源接口BP#############################################*/

//------------------------------终端销售----------------------------------
utype* pPubUWarrantyCardInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQWarrantyCardInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQImeiInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubImeiSale(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//utype* pPubQCardType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQResType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCardList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUCardInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubImeiRollBack(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubImeiRollBackBack(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubImeiExchange(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubImeiExchangeRollBack(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubCanceOrderImei(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQIMEIDetailInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//------------------------------终端销售----------------------------------

/*#############################维系挽留接口BP#########################################*/
utype* pPubDClubVipService(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubAirdromeFreeTimeMinus(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubVIPTime(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubCustGradeChangeInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubHCustAlertInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubCustomGradeProcessor(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*#############################维系挽留接口BP#########################################*/

/*########################1、公共信息查询BP#################################################*/
utype* pPubQCustList(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQCust(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQCustCont(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQCustContList(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQCustUserList(const utype *inParam, TCtrlInfo *errInfo);

utype* pPubQCustContUserByMasPhone(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQCustContUserByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQCustContUserByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQCustContUserByContractNo(const utype *inParam, TCtrlInfo *errInfo);
utype *pPubQUserBrand(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQDeadSHInfoByPhone(const utype *inParam, TCtrlInfo *errInfo);
utype* pQDeadSHInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubIWorkSheetNT(const utype *inParam,TCtrlInfo *errInfo);
utype* pPubChkCustNum(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/**********************记录查询失败次数或时长********************************/
utype* pPubIQryCapsRec(const utype *inParam,TCtrlInfo *errInfo);
/**********************密码解密********************************/
utype* pPubBossEnc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/**********************获取序列********************************/
utype* pPubGetSeq(const utype * inParam,TCtrlInfo *ptCtrlInfo);
/**********************记录查询失败次数，或者查询成功后记录时长*********************************************/
utype* pPubIQryCapsRec(const utype *inParam,TCtrlInfo *errInfo);
/************************************外部接口BP******************************************************************/

/***********************************PMOS************************************************/
/***************短信发送接口***************************/
utype* pPubSendSMS(const utype *inParam,TCtrlInfo *errInfo);
utype* pPubGetSmsInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/***************销售系统给操作员发短信接口***************************/
utype* pPubPtpSendMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/***************CRM下发短信***************************/
utype* pPubPushSerialSms(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pPubWapPush(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*#########################################################################***************************/

/*###################################客户服务首页面####################################*/
utype* pPubHomeOfCustSvc(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pPubMsgRemind(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*##################################################################################*/
/*###################################业务规则验证动态库####################################*/
extern "C" utype* pRQUserOweFeeFunc(const utype* puInParam, TCtrlInfo* errInfo);
extern "C" utype* pRQContractPreDet(const utype* puInParam, TCtrlInfo* errInfo);
extern "C" utype* pRQCustContUserByIdNo(const utype* puInParam, TCtrlInfo* errInfo);
/*##################################################################################*/

utype* pPubQSimFeeByRegionSim(const utype *inParam, TCtrlInfo *errInfo);


/***********************************************************************************/
utype *pPubGetOtherCustInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetCustInfoName(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pPubGetOtherContractInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserInfoForSH(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUserInfoName(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetUserSVCInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetContInfoName(const utype *inParam, TCtrlInfo *errInfo);
utype* pQCustInfoForSH(const utype *inParam, TCtrlInfo *errInfo);
utype*  getCodeNameByValue(const char* codeValue, int codeClass,TCtrlInfo *errInfo);
char* GetContactTypeName(const char* CONTACT_TYPE, char* CONTACT_TYPE_NAME);
utype *pPubGetOtherContractInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pApprovedIf(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/************************************LIS接口**********************************/
utype* pPubGifMarketOutPut(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubGifMarketOutPutRollBack(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubSaleActionPublish(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/************************************LIS接口**********************************/

utype* pPubGetFeeInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*zhoujz20100726 ADD*/
utype* pGetAddFeeInfo(const utype *puInParam, TCtrlInfo *errInfo);
utype* pPubInAcctFeeSht(const utype *inParam,TCtrlInfo *errInfo);
utype* pPubQResSalePrice(const utype *inParam , TCtrlInfo *errInfo);
utype* pubUpdGiftByID(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQryGiftByGrpID(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*读应用集成平台配置文件*/
int DcReadCfg(char* section, char* key, char* value);
/*调用应用集成平台服务*/
int MYLG_Getinter(char *group, char *inMsg, char *outMsg);
int MYLG_Getinter_L(char *group, char *inMsg, char *outMsg);
/*通过查询通用代码表查询boss服务是否可用*/
utype* pPubSvcStatus(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*数据同步接口*/
utype* pInDataSyn(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*资源回退撤单操作函数，chenjj 20100308*/
utype* pPubResSellBack(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryBrandScoreRuleDB(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTotalScoreQueryDB(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubPtpSendMsgList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubWsRollbackSaleAction(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryBindResByTD(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pPubQMallInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUMallInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUMallInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUMallInfo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubActivCardInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*VIP担保客服 chenyong 20110622*/
utype* pPubPreOrderPut(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*PBOSS*/
utype* pubTPortPre(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQryPhoneHlr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

 /*积分查询 20110815 积分明细、积分汇总*/
utype* pPubScoreInitQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTotalScoreQuery(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQUsrOfFeeRemind(const utype *puInParam,TCtrlInfo* errInfo);
utype* pChgScoreQuery(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*ADD BY LVJY 20100807 批量开户资源校验BP*/
utype* p1002ChkRes(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pUDUserDayInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);


/*###################################山西5.7项目增加分版本接口####################################*/
utype* pPubQResType_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCardList_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQuerySimResLimitByPhone_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubUpdateSimRes_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pPubQCardNum_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQBlankSimByNo_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQryChkCardInfo_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUpdCardByChgInfo_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubResChkPhoneAndCard_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQryJFLRES_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryNoInfoByNo_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryBindResByTD_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUpdJFLRESStore_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUCardInfo_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUpdNoSimInfoByOpr_NEW(const utype *puInParam, TCtrlInfo *ptCtrlInfo);




extern "C" utype* pPubUCardInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUCardInfo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQBlankSimByNo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQBlankSimByNo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryChkCardInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryChkCardInfo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryJFLRES_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryJFLRES_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryNoInfoByNo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryNoInfoByNo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUpdJFLRESStore_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUpdJFLRESStore_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQueryBindResByTD_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQueryBindResByTD_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryOrChnBusiNum_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryOrChnBusiNum_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQMallInfo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQMallInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pChkImeiInfo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pChkImeiInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pChkImeiInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pUpdTerminal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pUpdTerminal_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pUpdTerminal_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryTermDetInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryTermDetInfo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryTermDetInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* pQryPusInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* pQryPusInfo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* pQryPusInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryProvidInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryProvidInfo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryProvidInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUpdGiftByID(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUpdGiftByID_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUpdGiftByID_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryResCODEByBlur_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryResCODEByBlur_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryTypeInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryTypeInfo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryTypeInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQImeiByBlur(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQImeiByBlur_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQImeiByBlur_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*#############################有价卡类##############################################################*/
extern "C" utype* pPubQCardList_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQCardList_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQCardNum_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQCardNum_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQResType_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQResType_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*#############################号卡接口类##############################################################*/
extern "C" utype* pubQuerySimRes_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQuerySimRes_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQueryPhoneRes_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQueryPhoneRes_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUpdResByBookObject_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUpdResByBookObject_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQuerySIMInfoBySimNo_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQuerySIMInfoBySimNo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQuerySimResByPhone_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQuerySimResByPhone_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQuerySimResLimitByPhone_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubQuerySimResLimitByPhone_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubUpdatePhoneRes_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubUpdatePhoneRes_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubUpdateSimRes_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pubUpdateSimRes_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubUpdNoSimInfoByOpr_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*#############################号卡查询业务组件类##############################################################*/
utype* pPubQPhListT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQSimListT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQSimByPhT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubSimHandT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQSimResT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubPhoneHandT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUResStateT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubUSimStateT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*############################一级BOSS远程写卡######################################################*/
extern "C" utype* pPubQWriteCardDataByNo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubWriteCardResult_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*###################################山西5.7项目增加分版本接口####################################*/
utype*  pPubFavChk(const utype *inParam, TCtrlInfo *errInfo);

utype*  pPubQUserBrand(const utype *inParam, TCtrlInfo *errInfo);

utype* pUDUserDayInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUConUserInfoIf(const utype* puInParam,TCtrlInfo *errInfo );
utype* pWsReCommonManage(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubGetActRecord(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubGetActRecordDetail(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pPubUpdCardByChgInfo_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pPubResChkPhoneAndCard_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubResChkPhoneAndCard_SX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pPubUpdNoSimInfoByOpr_AH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*###################################山西5.7项目增加统一开发环境服务资源类型查询####################################*/
utype* pPubQueryRes(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIBatchOpenInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubOtaDataDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*山西新老系统并行，新系统号码开户校验在老系统是否已存在*/
extern "C" utype* pPubQLoginNumCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pPubSmsIdSend(const utype *puInParam,TCtrlInfo* errInfo);

//有限电视开户
utype*  pPubWire(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCHOrderCfm(const utype* inParam,TCtrlInfo* ptCtrlInfo);
utype* pSingleProdOrderCfm(const utype* inParam,TCtrlInfo* errInfo);
utype* pIUserPlaceInfo(const utype* inParam,TCtrlInfo* ptCtrlInfo);
//大客户身份转移
utype* pCustHighChange(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pSXUserDataFlow(const utype *inParam,TCtrlInfo *errInfo);

utype* pUserDataFlow(const utype *inParam,TCtrlInfo *errInfo);

extern "C" utype* pPubFreeMinQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);


utype* pubQPhoneNoBindBankNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* keyValue2Utypee(char *inMsg); 

utype* pubUpdNoByNoGrp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pQIdNoByProdId(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubQryUpdNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pCreateUserRelInfoSX(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pCreateUserRelInfoAH(const utype *inParam, TCtrlInfo *ptCtrlInfo);


#endif
