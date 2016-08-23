#ifndef __CUSTSVCBP_H__
#define __CUSTSVCBP_H__

/***********************20110914**********************************/
extern int* sub_str();
utype* cIRealSmpCardModInfo(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* pActiveCardChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1541Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cICbinterfacebusi(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cQUserResOrdByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByResourceNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserResOrdByResourceNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCNTCrmToBossStateHisByIdNoOptime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCrmToBossStateHisByIdNoOptime(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserResOrdByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype*	p1126Cron(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserSmsPushPrc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pubSmsSendCfg(const utype *inParam, TCtrlInfo *errInfo);
utype* pIConUserInfoIf(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUConUserInfoIf(const utype* puInParam,TCtrlInfo *errInfo );
utype* cQUserRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* p0001(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQCnttInfoList(const utype *inParam,TCtrlInfo *errInfo);
utype*  pBscUsrInfoQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pDataSynReq(const utype *inParam,TCtrlInfo *errInfo);
utype* pQryUserInfoByCustId_t(const utype *inParam,TCtrlInfo *errInfo);
utype* pSMSTransFile(const utype *inParam,TCtrlInfo *errInfo);
utype* p2393TransFile(const utype *inParam,TCtrlInfo *errInfo);
utype* pCustNameInfoQry_nk(const utype *inParam , TCtrlInfo *errInfo);
utype* pGetUserListByAddServNo(const utype *inParam, TCtrlInfo *errInfo);
utype* p3966RuleChk(const utype *inParam, TCtrlInfo *errInfo);
utype* p1130Query(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1128Cfm (const utype *inParam, TCtrlInfo *errInfo);
utype* p1128Mng (const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1130Cfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1132Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1132Dul (const utype *inParam, TCtrlInfo *errInfo);
utype* pPossMsgSend(const utype *inParam, TCtrlInfo *errInfo);
utype* pPossMsgRecv(const utype *inParam, TCtrlInfo *errInfo);
utype* pIAlertMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* pGprsOpenData(const utype *inParam, TCtrlInfo *errInfo);
utype* pGprsCloseData(const utype *inParam, TCtrlInfo *errInfo);
utype* cIDalertResultMsgHis(const utype *inParam, TCtrlInfo *errInfo);
utype* cIDalertResultMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* p2354Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//utype* pIBlackListPhone(const utype *inParam, TCtrlInfo *errInfo);
//utype* pIBlackList(const utype *inParam, TCtrlInfo *errInfo);
utype* p2356(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pFuncElemQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * pElemInfoQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p2383Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2380Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserInfoByMasPhone(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* GetLoginAccept(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p10086Msg(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p1100Cfm(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pUserAddChg(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p1102Cfm(const utype *puInParam, TCtrlInfo *errInfo);
utype * pQryUserInfoByCustId(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQryUserProdByCustId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype *pQAllCustInfo(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQAllCust(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQAllCustByServNo(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQContactMsgListByCustId3Days(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQCustInfoByCustId(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pMainProdByIdno(const utype *puInParam, TCtrlInfo *errInfo);

utype* p2372Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2372QueryByIdIccid(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2372QueryByPhoneNo(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQUserCustInfoByPhoneNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQRestrainLimtOwe(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1128Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1130Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pInfoQuery(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1116Query(const utype *puInParam, TCtrlInfo *errInfo);

utype* pQUserInfoByMulCol01(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQCustInfoByMulIccId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckPasswdOrCertNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserCustInfoByIdNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1116BankQuery(const utype *puInParam, TCtrlInfo *errInfo);

 utype* pOptrLogChk(const utype *puInParam, TCtrlInfo *errInfo);
utype* pGetDoubleNums(const utype *puInParam, TCtrlInfo *errInfo);
utype* pCheckLimitOwe(const utype *puInParam, TCtrlInfo *errInfo);

utype* p1100Valid(const utype *puInParam, TCtrlInfo *errInfo);
utype* pSlectProd(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1128UpdateLimtOwe(const utype *InParam, TCtrlInfo *ptCtrlInfo);
utype* p1128UpdateType (const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pULimitOweOfUserInfo (const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUTypeOfUserExtInfoByType (const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1100Query(const utype *puInParam, TCtrlInfo *errInfo);

utype* pUUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pUUserStateInfoExpDate(const utype *inParam, TCtrlInfo *errInfo);
utype* pIUserStateInfoCust(const utype *inParam, TCtrlInfo *errInfo);

utype* pDUserAddInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUUserAddInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQConMsgListByCustId(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p1112Query(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* p1112QueryAH(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* p1112QuerySX(const utype * inParam,TCtrlInfo *errInfo);
utype* pQryInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pCheckSvcNum(const utype * inParam,TCtrlInfo *errInfo);
utype* pgCredInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pgContrInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pgUserScore(const utype * inParam,TCtrlInfo *errInfo);
utype* pgAcctItemInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pgInstanceFee(const utype * inParam,TCtrlInfo *errInfo);
utype* pgOweFeeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIInWorknT(const utype * inParam,TCtrlInfo *errInfo);
utype* pBandGrpUserDeal(const utype * inParam,TCtrlInfo *errInfo);


utype* pRedInfoChg(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* p1112Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);


utype* p1100Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* cQUserAddByIdNo(const utype *puInParam, TCtrlInfo *errInfo);
utype* pubQueryContractPreDet(const utype *puInParam, TCtrlInfo *errInfo);

// chudg begin
//彩铃工单XML解析、MD5加密
int isSuccess(char *xmlstr, char *returncode, char *Out_ErrInfo);
int readxmlstr(int flag, char *xmlstr, char *Out_ErrInfo, utype* ResultSet);
int getXmlDetail(int flag, char *psno, char *xmlstr, TCtrlInfo *ptCtrlInfo);
int Create_MD5_Cluster(const char *p_chKey,const char *p_chGene,int nGene,char  *MD5_str);

extern "C" utype* p1114CfmAH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1114CfmSC(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1114Finish(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* p1114Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1113Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2104Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1115Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2105Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1134Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126Finish(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1136Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2238Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1140Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1226Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1227Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1228Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1113CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1114CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1267CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQContactPhone(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1110CQSim(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pChkUserIccid(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1114Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1115Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2104Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2105Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1134Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126Lock(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126QryCard(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126QryResType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126QryResTypeL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126SellBack(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126SellCancel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1126Back(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pBackToGift(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1136Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRandPassAdm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckPasswd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckPasswdL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetContractInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetComInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQueryInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1113Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1114Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1113Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1114Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1115Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2104Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2105Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1134Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1136Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2238Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140QryBoxDetail(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140QryUserMusic(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140GetBoxDetail(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140GetUserMusic(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1226Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pBackToGift(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1227Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1227Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1228Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pBroadInfoQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pBindBroadQry(const utype *inParam, TCtrlInfo *errInfo);
utype* p4059QRes(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p4059QRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p4059QChaClass(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p4059QSellPrice(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p4059USellPrice(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p4059DSellPrice(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p4059ASellPrice(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pUUserPasswd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUCustPasswd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUContractPasswd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIPasswdResetInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUPasswdResetInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUUserOwnStopFlag(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUCustLevel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIUserAddInfo01(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDUserAddInfo01(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUQueryCrdFlag(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pISpecialListInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDSpecialListInfoByIdType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUExpDateOfSpecialInfoList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUOtherValueOfUserAddInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUFieldOtherValueOfUserAddInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUExpDateOfUserBrandRelByIdTime(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUFieldValueOfUserAddInfo01(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUserResMsg(const utype * puInParam,TCtrlInfo * ptCtrlInfo);
//================山西NG begin=================
extern "C" utype* pChgSmScoreUser(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pCheckPasswdAH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pCheckPasswdSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pCheckPasswdSC(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pIsWeakPasswdAH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pIsWeakPasswdSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pIsWeakPasswdSC(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p1114FinishAH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p1114FinishSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p1114FinishSC(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
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
utype* pGenOrderParam(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1114CfmLCheckAH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1114CfmLCheckSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1114CfmLCheckSC(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1267CfmSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1267FinishSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1267CfmSC(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1267FinishSC(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140Tone(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140ToneQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1140FinishSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetParmUtype(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1110InitL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1110PreCardL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1110CheckL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1110CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140QryToneSXL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1140CfmSXL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQChgSimTimes(const utype* puInParam, TCtrlInfo* ptCtrlInfo);
extern "C" utype* pQChgSimTimesL(const utype* puInParam, TCtrlInfo* ptCtrlInfo);
extern "C" utype* pQUserCLFlag(const utype* puInParam, TCtrlInfo* ptCtrlInfo);
utype* p1114HWPWChg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserCLFlagL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1140LocalToneSX(const utype* puInParam, TCtrlInfo* ptCtrlInfo);
//乘机方便行
utype* p2285QUserPlanOrder(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2285QUserCheckIn(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2285QPlane(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2285QPlaneOrder(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p2285UUserCheckIn(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2285UUserOrder(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2285UPlane(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2285RemindCheckIn(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2285UUserOrder1(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cQPlaneCheckInfoByMobileAndFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPlaneFlightInfoByFlNoAndFeXd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPlaneOrderInfoByDateAndFlNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPlaneOrderInfoByMobile(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfPlaneCheckInfoByMobileAndFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfPlaneFlightInfoByFlNoAndFeXd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfPlaneOrderInfoByDateAndFlNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfPlaneOrderInfoByMobile(const utype * inParam,TCtrlInfo *errInfo);

utype* cIPlaneCheckInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPlaneFlightInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPlaneOrderInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPlaneFlightInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPlaneFlightInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);

utype* cUSendFlagOfPlaneOrderInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSendFlagOfPlaneOrderInfoByFlNoAndTktNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAllOfPlaneFlightInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPayOfPlaneOrderInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cDPlaneFlightInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPlaneFlightInfoByFlId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAllPlaneOrderInfoByDateAndFlNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMobileOfPlaneOrderByDateAndFlNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPlaneOrderInfoByDateStatusFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSendFlagOfOrderInfoByDateStatusFlag(const utype * inParam,TCtrlInfo *errInfo);


//话单管家
utype* cQEmailInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEmailOfEmailInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEmailInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEmailInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEmailInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);

utype* pUBillEmailL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQBillEmailL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pHWBillEmailL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2101CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//密码修改增加证件次数校验
utype* cICheckLoginResInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCheckLoginResInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cUChgCountOfChgLoginRes(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1114CheckId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//话单禁查ligh2011/11/14 20:03:47
utype* p2303Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2303Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCntOfCustBillQryReqByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustBillQryReqByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustBillQryReq(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustBillQryReqHisByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCustBillQryReqOByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustBillQryReqByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustBillQryReqHis(const utype * inParam,TCtrlInfo *errInfo);

//退卡
extern "C" utype* p1507Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1507QCard(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByBeginEndNoType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdBySellSerialNo(const utype * inParam,TCtrlInfo *errInfo);
utype* p1507ChkCard(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetCnttId(const utype * inParam,TCtrlInfo *errInfo);
//浦发银行接口

utype* pWalletMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pWalletQInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQUserAddMidByIdTypeTime(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIUserAddInfoMid(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cDUserAddInfoMidByIdTypeBak2(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubAllFeeQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//乘机方便行会员管理
utype* p2073Add(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2073Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2073Update(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQClubMemberInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIClubMemberInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cUClubMemberInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIClubMemberInfoHis(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIClubMemberInfoHisBak(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQVitualMoneyInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQMemberAndVirtualmoney(const utype * puInParam,TCtrlInfo *ptCtrlInfo);
utype* cQPlaneOrderInfoByResIdTktNoFlNo(const utype * inParam,TCtrlInfo *errInfo);
//指令发送
utype* p2063Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2063QryPrc(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIWBWLANSNDCMDDAY(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEffPrcByPrcNameLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExpPrcByPrcNameLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAdcInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServAddInfoByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPdUnicodeByBeginValue1(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWADCSNDCMDDAY(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWHYWGSNDCMDDAY(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpByObjAndType(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWSMAPVPMNSNDDAY(const utype * inParam,TCtrlInfo *errInfo);
utype* cISvcForSpmsInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* p2063CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQUserUsergroup2(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserSvcAttrById(const utype * inParam,TCtrlInfo *errInfo);
utype* test8899A(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIWSMAPSNDDAY(const utype * inParam,TCtrlInfo *errInfo);
utype* pGenSql(const utype * inParam,TCtrlInfo *errInfo);
//================山西NG end=================
//安徽携号转网
utype* p1134BatchChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//安徽安全管理需求
utype* cQLoginQryDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginQryNew(const utype * inParam,TCtrlInfo *errInfo);

//安徽流量小闹钟
utype * p1547QState(const utype * puInParam,TCtrlInfo * ptCtrlInfo);
utype* pGenOrderParam1(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1547CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cISurplusawokeInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cISurplusawokeInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cISurplusawokeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSurplusawokeInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSurplusawokeInfoByIdTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cDSurplusawokeInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSurplusawokeInfoById(const utype * inParam,TCtrlInfo *errInfo);

//安徽流量提醒取消
utype * p1174Init(const utype * inParam,TCtrlInfo * errInfo);

//安徽流量提醒
utype* pQrySwitch(const utype *inParam, TCtrlInfo *errInfo);
utype* p1174Query(const utype *inParam, TCtrlInfo *errInfo);
utype* p1174Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * p1547Qry(const utype * puInParam,TCtrlInfo * ptCtrlInfo);

//小闹钟
utype* cUSurplusawokeInfoById(const utype * inParam,TCtrlInfo *errInfo);

//全网通
utype* pQAllNetFee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

// chudg end


utype* cQLoginOprByMul05(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQLoginOprByMul07(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetLimitOwe(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pIsSameRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQUserInfoByIdNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//add by  wanfh   begin
typedef utype * (*ScoreFuncPtr)(const utype * inParam, TCtrlInfoEx * errInfo);
utype * tuxadpso(const utype * inParam,ScoreFuncPtr str_funcname );
//utype * tuxadpso(const utype * inParam,ScoreFuncPtr str_funcname,CAdpConnect * scoredbc);
extern "C" int LG_Getinter(char *newaddress,int appid,int priority,char *transcode,char *inmsg,char *outmsg);
utype* pQUserDeadInfoByIccid(const utype * inParam, TCtrlInfo *errInfo);
utype* pQUserInfoByIccid(const utype * inParam, TCtrlInfo *errInfo);
utype* p2122Query(const utype * inParam,TCtrlInfo *errInfo);
utype* p2118Query(const utype * inParam,TCtrlInfo *errInfo);
utype * pQBlackInfoByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);
utype * pQBlackInfoByAllIccid(const utype *inParam, TCtrlInfo *errInfo);
utype * pAddQBlackInfoByIccid(const utype *inParam, TCtrlInfo *errInfo);
utype * pAddQBlackInfoByIccidL(const utype *inParam, TCtrlInfo *errInfo);
utype * pDelQBlackInfoByIccid(const utype *inParam, TCtrlInfo *errInfo);
utype * pQBlackInfoByIccid(const utype *inParam, TCtrlInfo *errInfo);
utype * pIBlackList(const utype * inParam,TCtrlInfo * errInfo);
utype * pIBlackListPhone(const utype * inParam,TCtrlInfo * errInfo);
utype * pDBlackList(const utype * inParam,TCtrlInfo * errInfo);
utype * pDBlackListPhone(const utype * inParam,TCtrlInfo * errInfo);
utype * p2107Check(const utype * inParam, TCtrlInfo *errInfo);
utype * p2107Query(const utype * inParam,TCtrlInfo * errInfo);
utype * p2107QDel(const utype * inParam,TCtrlInfo * errInfo);
utype * p2107QAdd(const utype * inParam,TCtrlInfo * errInfo);
utype * pQUserDeadInfoByIccid(const utype * inParam,TCtrlInfo * errInfo);
utype * pQUserInfoByIccid(const utype * inParam,TCtrlInfo * errInfo);
utype* p2120Query(const utype * inParam,TCtrlInfo *errInfo);
utype * p2120Check(const utype * inParam, TCtrlInfo * errInfo);
utype * pInsertBlack(const utype * inParam,TCtrlInfo * errInfo);
utype * pQryBlack(const utype * inParam,TCtrlInfo * errInfo);
utype * pInsertReleaseBlack(const utype * inParam,TCtrlInfo * errInfo);
utype * pQryReleaseBlack(const utype * inParam,TCtrlInfo * errInfo);
utype* p1148Query(const utype * inParam,TCtrlInfo *errInfo);
utype* pGprsSwitchClose(const utype * inParam, TCtrlInfo *errInfo);
utype* pGprsSwitchOpen(const utype * inParam, TCtrlInfo *errInfo);
utype * p3996Check(const utype * inParam,TCtrlInfo * errInfo);
utype * p3995Check(const utype * inParam,TCtrlInfo * errInfo);
utype* pScrUserDelete(const utype * inParam, TCtrlInfo *errInfo);
utype* pScrUserUpdate(const utype * inParam, TCtrlInfo *errInfo);
utype* pScrUserInsert(const utype * inParam, TCtrlInfo *errInfo);
utype * p3997Query(const utype * inParam,TCtrlInfo * errInfo);
utype * p3995Init(const utype * inParam,TCtrlInfo * errInfo);
utype * p3996Init(const utype * inParam,TCtrlInfo * errInfo);

utype * pCoShopAdd(const utype * inParam, TCtrlInfo * errInfo);
utype * pCoShopDel(const utype * inParam, TCtrlInfo * errInfo);
utype * pCoShopUpdate(const utype * inParam, TCtrlInfo * errInfo);
utype* p3991Query(const utype * inParam, TCtrlInfo *errInfo);
utype* p3992Query(const utype * inParam, TCtrlInfo *errInfo);
utype * pCoShopPosAdd(const utype * inParam, TCtrlInfo * errInfo);
utype * pCoShopPosDel(const utype * inParam, TCtrlInfo * errInfo);
utype * pCoShopPosUpdate(const utype * inParam, TCtrlInfo * errInfo);

//add by wanfh  end

utype * pubQueryContractBalance(const utype * inParam,TCtrlInfo * errInfo);
utype* pIUserAddInfoCust(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//add by chenjj 20091106
utype* p1122Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1122Valid(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1122Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2358Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*多OP改造，客户首页部分*/
utype* pQCnttInfoList(const utype *inParam,TCtrlInfo *errInfo);
utype* pBscUsrInfoQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pFuncElemQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pElemInfoQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQUsersSetByCustId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQBasicUserInfoByIdNoForPeb(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//zhaoqm

extern "C" utype* pPubOpenStopFunc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2112Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2112Check(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2112Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2112Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pForceOpenChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQForceOpenExpireDays(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pForceStopChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2112CfmL(const utype *puInParam, TCtrlInfo *errInfo);

/*PanLi*/
utype* p3858Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype *pPubGrpBaseInfoQry(const utype *inParam , TCtrlInfo *errInfo);
utype *GetHisParam(const utype *inParam,char type[2]);
utype *pUCustInfoByCustID(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpCustInfoByCustIDAndUnitID(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpCustExtInfoByCustID(const utype *inParam , TCtrlInfo *errInfo);
utype *pUCustContactInfoByCustIDAndContactOrder(const utype *inParam , TCtrlInfo *errInfo);
extern "C" utype* p3858Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1132Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQDeadInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pBCadmin(const utype *inParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* p1116Cfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* pIConTrustInfoCustsvc(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUContractInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1116ContQuery(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype *p1120Query(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype *p1120Chk(const utype *puInParam, TCtrlInfo *errInfo);
utype* pUConTrustInfoCustsvc(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*1162*/
utype* p1162Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1162QCard(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p1162Cfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1144OrderProd(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1144Query(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype *p1144Cfm(const utype *puInParam, TCtrlInfo *errInfo);
utype * pQCustBasicInfoByCustId(const utype *puInParam, TCtrlInfo *errInfo);
utype * pQBasicUserInfoByIdNo(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQBasicUserInfoByIdNoForPeb(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * p2374Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype * p2374Init(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1144L(const utype *puInParam, TCtrlInfo *errInfo);
utype* pOrderCfmL(const utype *inParam, TCtrlInfo *errInfo);
utype* p2372QueryByIdIccid(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2372QueryByPhoneNo(const utype *puInParam, TCtrlInfo *errInfo);
utype * pInfoQueryById(const utype * inParam, TCtrlInfo * errInfo);
extern "C" utype * pIMsgSend(const utype * inParam, TCtrlInfo * errInfo);
utype* p1100L(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQCustInfoByCustId(const utype *puInParam, TCtrlInfo *errInfo);
/*1164*/
utype* p1164Query(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p1164Cfm(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p1164RollBack(const utype *puInParam, TCtrlInfo *errInfo);
/*2382*/
utype* p2382Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2361Qry(const utype *puInParam, TCtrlInfo *errInfo);

utype* p1166Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* pICnttBegin(const utype *puInParam, TCtrlInfo *errInfo);
utype* pICnttEnd(const utype *puInParam, TCtrlInfo *errInfo);
utype* pPubGetCnttSeq(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQCnttMsgByStatus(const utype *puInParam, TCtrlInfo *errInfo);
utype* pUUserStateInfoCustFinish(const utype *inParam, TCtrlInfo *errInfo);
utype* pUUserInfoFinish(const utype *inParam, TCtrlInfo *errInfo);
utype* pUUserStateInfoExpDateFinish(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1100Finish(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1100QMbrInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//延长有效期，提供给外部接口使用  091125
utype* pValidQuery(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQValid(const utype *inParam, TCtrlInfo *errInfo);
utype* pUValid(const utype *inParam, TCtrlInfo *errInfo);

//091126
utype* pQResSellInfo(const utype *inParam, TCtrlInfo *errInfo);


utype * pQCnttMsgListByCustId(const utype *inParam, TCtrlInfo *errInfo);
utype * pQCnttMsgDetail(const utype *inParam, TCtrlInfo *errInfo);

utype* p1102CheckCfm(const utype *puInParam, TCtrlInfo *errInfo);

utype* p1175(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p1175Cfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* pInsertQryRecode(const utype *puInParam, TCtrlInfo *errInfo);
utype* pUpdateRecord(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1122Chk(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1144orderCfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* pOrder(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1174Order(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1176Cfm(const utype *puInParam, TCtrlInfo *errInfo);

/*#######################积分调整################begin#######*/
//积分转移
utype* p3971Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3971Chk(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3971SubChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pTotalScoreQuery(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p3971Cfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* pIScoreUse(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIExtRuleValue(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3971ApplyL(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3971L(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pApplyCfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* pDSCORETRANS(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pISCORETRANS(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3971ConfirmTran(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pConfirmCfm (const utype *puInParam, TCtrlInfo *errInfo);
utype* pUSCORETRANS(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3971ConfirmDate(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pConfirmDataCfm(const utype *puInParam, TCtrlInfo *errInfo);

//单号处理
utype* p3973Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* pListScore (const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3973Cfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3973L(const utype *puInParam, TCtrlInfo *errInfo);

//积分奖品管理
utype* p3972Query(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p3972Cfm(const utype *puInParam, TCtrlInfo *errInfo);
/*#######################积分调整################end#######*/
/*#######################业务查询################begin#######*/
utype* pBusiFind(const utype *puInParam, TCtrlInfo *errInfo);
utype* pScoreUserQuery(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2354Dul(const utype *puInParam, TCtrlInfo *errInfo);


/*#######################业务查询################end#######*/
utype* pPubQResInfo(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQResInfoByTime(const utype *puInParam, TCtrlInfo *errInfo);

utype* pCustConQry(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pInsertLoginQry(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* pInsertLoginQry_C(const utype *puInParam, TCtrlInfo *errInfo);

utype* pGetQryBusiOperationInfo(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pGetBusiOperationInfo(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pIOnceCntt(const utype *inParam, TCtrlInfo *tCtrlInfo);
/*#######################喜点查询################end#######*/
utype* p2384Query(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pGetAcctHappyNodValue(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pGetAcctHappyNodChg(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pHappyNodChgJudge(const utype *inParam, TCtrlInfo *tCtrlInfo);

/*#######################喜点查询################end#######*/
/*#######################业务受限管理################end#######*/
utype* pPhonelmt(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pGNewPhonelmt(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pGOldPhonelmt(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pDelUserInfo(const utype *inParam, TCtrlInfo *tCtrlInfo);
utype* pInsertUserInfo(const utype *inParam, TCtrlInfo *tCtrlInfo);
/*#######################业务受限管理################end#######*/
/*#######################积分查询################end#######*/
utype* pQueryPosSN(const utype *inParam, TCtrlInfo *tCtrlInfo);
/*#######################积分查询################end#######*/
/*#######################无线积分POS交易明细查询################end#######*/
utype* p3993Query(const utype *inParam, TCtrlInfo *tCtrlInfo);
/*#######################无线积分POS交易明细查询################end#######*/

/*------------无线积分POS交易明细查询------bengin----*/
utype* p1124Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1124CustQuery(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1124Contract(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1124ConUser(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQPhoneList(const utype* puInParam,TCtrlInfo *errInfo);
utype* p1124UserInfo(const utype* puInParam,TCtrlInfo *errInfo);
utype* pUConUserInfoCust(const utype *inParam, TCtrlInfo *errInfo);
utype* pDConUserInfoCust(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1124Cfm(const utype *puInParam, TCtrlInfo *errInfo);
/*------------无线积分POS交易明细查询------end----*/
/*#######################我家信息查询################end#######*/

utype* p2387Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pIHomeInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQHomeInfo(const utype *inParam, TCtrlInfo *errInfo);
/*#######################我家信息查询################end#######*/

/*#######################回馈积分汇总信息查询################end#######*/

utype* p2388Query(const utype *inParam, TCtrlInfo *errInfo);

/*#######################回馈积分汇总信息查询################end#######*/
/*#######################积分调整接口################end#######*/
utype* p3973Check(const utype *inParam, TCtrlInfo *errInfo);
utype* pDealSvcNumALLScr(const utype *inParam, TCtrlInfo *errInfo);
utype* pDealSvcNumListScr(const utype *inParam, TCtrlInfo *errInfo);

/*#######################积分调整接口################end#######*/


//充值卡换卡
utype* p1220Query(const utype *inParam, TCtrlInfo *errInfo);
utype* p1220QCard(const utype *inParam, TCtrlInfo *errInfo);
utype* p1220Check(const utype *inParam, TCtrlInfo *errInfo);
utype* pDealCardInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pCheckResType(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1220Cfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1220ClearCard(const utype *inParam,TCtrlInfo *errInfo);

//集团统付预存回馈登记
utype* p1225Query(const utype *inParam, TCtrlInfo *errInfo);
utype* pQRegInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQResType(const utype *inParam, TCtrlInfo *errInfo);
utype* pQResTypeInfoList(const utype *inParam, TCtrlInfo *errInfo);
utype* pQGiftCardList(const utype *inParam, TCtrlInfo *errInfo);
utype* pQPreInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* p1225Check(const utype *inParam, TCtrlInfo *errInfo);
utype* pCheckCard(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1225Cfm(const utype *inParam, TCtrlInfo *errInfo);

//政府来函管理
utype* p2109Query(const utype *inParam, TCtrlInfo *errInfo);
utype* pLetterAdd(const utype *inParam, TCtrlInfo *errInfo);
utype* pLetterSel(const utype *inParam, TCtrlInfo *errInfo);
utype* pSingleSel(const utype *inParam, TCtrlInfo *errInfo);
utype* pTitleSel(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pEndureChange(const utype *inParam, TCtrlInfo *errInfo);
utype* pLetterAddCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p2109Check(const utype *inParam, TCtrlInfo *errInfo);


extern "C" utype* p2109Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//---------集团统付管理
utype* p1219Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* pPassword(const utype *puInParam, TCtrlInfo *errInfo);
utype* pIUCheckCfm(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p1219Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pDAccount(const utype *inParam, TCtrlInfo *errInfo);
utype* pDUserTrans(const utype *inParam, TCtrlInfo *errInfo);
utype* pIAccount(const utype *inParam, TCtrlInfo *errInfo);
utype* pIUserTrans(const utype *inParam, TCtrlInfo *errInfo);
utype* pUAccount(const utype *inParam, TCtrlInfo *errInfo);
utype* pUUserTrans(const utype *inParam, TCtrlInfo *errInfo);
utype* pCheckCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1219GroupQuery(const utype *puInParam, TCtrlInfo *errInfo);
utype* pUConUserInfoj(const utype *inParam, TCtrlInfo *errInfo);
utype* pIConUserInfoCust(const utype *inParam, TCtrlInfo *errInfo);
/*#######################积分查询################begin#######*/
utype* p3979SrcQry(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3979SrcQrySX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3979SrcQryAH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreInitQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryScrTotal(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQrySillAttr(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQryScrList(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQryScrChange(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3979UsrSrc(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQueryScoreAdjust(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQryUseScrList(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3980SrcBatchQry(const utype *puInParam, TCtrlInfo *errInfo);
utype* pScoreQuery(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3981SrcMvQry(const utype *puInParam, TCtrlInfo *errInfo);
utype* pGetPassActSvcNum(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3982QrySrc(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQueryUserGenScore(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQueryUserEncScore(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQueryUserConScore(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQueryUserReDScore(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQueryUserSpareScore(const utype *puInParam, TCtrlInfo *errInfo);
utype* pInsertLoginQry(const utype *puInParam, TCtrlInfo *errInfo);
utype * pPubScoreCardInfoQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * pGetActiveSvcNum(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3993Pos(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3979Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetScoreList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);


/*#######################积分查询################end#######*/
utype * p1230UpdateLimtOwe(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * p1230ULimitOweOfIdNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//特约商户积分变现
utype * p3998Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype * p3998Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQGrpScrCust(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3993PosName(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//催停属性批量
utype * p1133Check(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * p1230Check(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1180Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pGetCnttSeq(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//停开被叫
utype* pUptodateUsrInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2113Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * cUAddrOfUserServLocInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//密码校验
utype* pCheckPassWord(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIsNotMaxCount(const utype * inParam,TCtrlInfo *errInfo);
utype* pInsertCheckPwdRec(const utype * inParam,TCtrlInfo *errInfo);
utype* pCheckPassWordNew(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIsNotMaxCountNew(const utype * inParam,TCtrlInfo *errInfo);
utype* pInsertCheckPwdRecNew(const utype * inParam,TCtrlInfo *errInfo);
//集团支付关系历史记录查询
utype* p2385Query(const utype *puInParam, TCtrlInfo *errInfo);

//固定IP业务查询
utype* p2128Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2128QIpInfo(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2128Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* pIPResultDeal(const utype *puInParam, TCtrlInfo *errInfo);
utype* pIPResultParse(const utype *puInParam, TCtrlInfo *errInfo);

//用户优惠激活退订信息查询
utype* p2126Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQryUserFav(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryUserUnFav(const utype *inParam, TCtrlInfo *errInfo);

utype* p1245Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pDowork(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetPlanid(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype* p1246Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1246Init(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1247Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1247Init(const utype *inParam, TCtrlInfo *errInfo);

utype* p2124Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p2124IQryInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* p2124QCardInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* p2124QBlackInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* p2124DBlackInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pCardResultDeal(const utype *inParam, TCtrlInfo *errInfo);
utype* pCardResultParse(const utype *inParam, TCtrlInfo *errInfo);

utype* pQMarketInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pCheckResNo(const utype *inParam, TCtrlInfo *errInfo);

utype* p1150Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pQueryScrLists(const utype *inParam, TCtrlInfo *errInfo);
utype* pQueryScrList(const utype *inParam, TCtrlInfo *errInfo);
utype* pQueryScrAdjusts(const utype *inParam, TCtrlInfo *errInfo);
utype* pQueryUseScrLists(const utype *inParam, TCtrlInfo *errInfo);
utype* pPubCurTotalScoreQrys(const utype *inParam, TCtrlInfo *errInfo);
utype* pQueryScrAdjust(const utype *inParam, TCtrlInfo *errInfo);
utype* pQueryUseScrList(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryScrLists(const utype *inParam, TCtrlInfo *errInfo);
utype* pTotalScoreQuerys(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetScoreLists(const utype *inParam, TCtrlInfo *errInfo);

utype* p3969Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* p3969Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p3969ICfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pQueryCarServ(const utype *inParam, TCtrlInfo *errInfo);

utype* p2391Query(const utype *inParam, TCtrlInfo *errInfo);
utype* pListScores(const utype *puInParam, TCtrlInfo *errInfo);

utype* pServRequest(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQueryUserScoreRec(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQueryUserScoreStat(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQueryCarServ(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2112Cron(const utype *puInParam, TCtrlInfo *errInfo);

utype* p3974Cfmx(const utype *puInParam, TCtrlInfo *errInfo);

utype* p1105QFeeType(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1105Query(const utype *puInParam, TCtrlInfo *errInfo);

utype* p1102L(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3979Inter(const utype *puInParam, TCtrlInfo *errInfo);
utype* pPubValidDate(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p1267Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1267Finish(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype * p1267BossAH(const utype * puInParam,TCtrlInfo * ptCtrlInfo);
utype* p1267AhCheckL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1267AhCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1267Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIUserHisTory(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p2354DelCustPass(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2354ModNameCert(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2354ModCard(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2354AppPreDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2354AppPreDestory(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2354ProdModify(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cCntOfLoginOrderOffer(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCustInfoHisByCustId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCustContactInfoByCustIdOnly(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCustInfoHisByCustId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCustContactInfoByCustIdOnly(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQUsrProdInfoPrcDictByMain(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cQCustInfoHisByUpdate(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCustInfoHisByUpdate(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQOLFeeByOrderActionId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQUsrProdInfoHisByMain(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserResHisInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQProdHisLimit(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQBusiHisLimit(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetUserPrcProdDictByProdType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetUserPrcProdDictByProdType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetUserPrcProdDictByProdType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetUserPrcProdDictByProdType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserTeamHisInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1219OrderCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1219MC(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckUser(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1269Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1269Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1269BatchCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUsersSetByCustId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQConUserInfoByIdEffExp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cUExpDateFinishFlagOfUserExpireInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdOrderDelay(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDAccountM(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype * p1282Cfm(const utype * puInParam,TCtrlInfo * ptCtrlInfo);
utype * pOpenPasswdRemind(const utype * puInParam,TCtrlInfo * ptCtrlInfo);
utype * p1269QRel(const utype * puInParam,TCtrlInfo * ptCtrlInfo);
int pIsWeakPasswd(const utype * puInParam,TCtrlInfo * ptCtrlInfo);

utype* pIsNotMaxCount(const utype * inParam,TCtrlInfo *errInfo);
utype* pInsertCheckPwdRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginMsgByLoginNoFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTimesOfCheckPasswByPhoneNoIn(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* p1120Warn(const utype * inParam,TCtrlInfo *errInfo);
utype* p1267Before(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetGroupRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* p2354BusiQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pGetSvsInfoByClassKindLimit(const utype *inParam, TCtrlInfo *ptCtrlInfo);


/*liuxjc*/
utype* p1284Query(const utype* inParam,TCtrlInfo* errInfo);
utype* pQColorMsgSendbyPhoneNoandLatestTime(const utype* inParam,TCtrlInfo* errInfo);
utype* pColorMsgSendbyLoginNo(const utype* inParam,TCtrlInfo* errInfo);
utype* p1292Qry(const utype* inParam,TCtrlInfo* errInfo);
utype * pProcQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pCombinFile(const utype * inParam,TCtrlInfo *errInfo);
utype * pTwoCityQuery(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*  pCommonUpdate(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUPhoneNo(const utype *inParam, TCtrlInfo *errInfo);
utype* p1512orderCfm(const utype *inParam, TCtrlInfo *errInfo);
utype * p1175L(const utype *puInParam, TCtrlInfo *errInfo);
utype * p1175QryL(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1513Init(const utype * inParam,TCtrlInfo *errInfo);
utype* p1513Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUResOccupy(const utype *inParam, TCtrlInfo *errInfo);
utype* pB925UpPerMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* pIMSInfoQry(const utype* inParam,TCtrlInfo* errInfo);
utype* p1640Qry(const utype* inParam,TCtrlInfo* errInfo);
utype* p1640GoodsQry(const utype* inParam,TCtrlInfo* errInfo);
utype* p1520Add(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1520Mod(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1520Del(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1520Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1522Add(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1522Del(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1522Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1521Add(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1521Del(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1521Update(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* pB925UpStatus(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* pB925UpDepMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1521Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1521BatchCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1523Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPrintAdvtCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1600BatchCfm(const utype *inParam,TCtrlInfo *errInfo);
utype* p1600Qry(const utype *inParam,TCtrlInfo *errInfo);
utype* p1600BatchCmt(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* p1112QueryL(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* p1180Cfm(const utype *inParam,TCtrlInfo *errInfo);
utype * pSastisfyCntQry(const utype *puInParam, TCtrlInfo *errInfo);
utype * pSastisfyQry(const utype *puInParam, TCtrlInfo *errInfo);
utype * p1528Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype * p1528CfmL(const utype *puInParam, TCtrlInfo *errInfo);
utype * p1530Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1529Qry(const utype *inParam,TCtrlInfo *errInfo);
utype* pQBindUser(const utype *inParam,TCtrlInfo *errInfo);
utype* pUserQuery(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1544Check(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1544(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1544Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*福分*/
utype* p3709Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3709QInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3708Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3708CfmL(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pIGoodLuckUse(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUGoodLuckInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3708Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2367ChgLogQuery(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2367ReverseChgLogQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);


/*renwei*/
utype* cQChnGroupRelByParentGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCustByPhoneNoAndMasterServId(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* p1285Query(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* p1267BroadQry(const utype *inParam, TCtrlInfo *errInfo);
utype* p1267CBroadPwdL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pCheckChgCashPay(const utype * puInParam,TCtrlInfo * ptCtrlInfo);

/*school code id*/
utype* pQCodeId(const utype *inParam, TCtrlInfo *errInfo);
utype* pQCodeIdbyCodeName(const utype *inParam, TCtrlInfo *errInfo);
utype* pQCodeIdbyGroupName(const utype *inParam, TCtrlInfo *errInfo);

/* add by lufei */
utype* pConUserRelIF(const utype *inParam, TCtrlInfo *errInfo);
utype* pGrpAccUserRelIF(const utype *inParam, TCtrlInfo *errInfo);
utype* pGrpAccUserRelIFbak(const utype *inParam, TCtrlInfo *errInfo);
utype* pSendConUserMsg(const utype *inParam , TCtrlInfo *errInfo);
utype* pQWChargeOLResul(const utype *inParam, TCtrlInfo *errInfo);
utype* pQWaterQuery(const utype *inParam, TCtrlInfo *errInfo);
utype* pQWaterResultGet(const utype *inParam, TCtrlInfo *errInfo);
utype*  pQWaterPrintGet(const utype *inParam, TCtrlInfo *errInfo);

utype* pConUserListIF(const utype* puInParam,TCtrlInfo *errInfo);
extern "C" utype* payConChk(const utype* puInParam,TCtrlInfo *errInfo);

utype* pIConRelL(const utype *inParam , TCtrlInfo *errInfo);
utype* pUConRelL(const utype *inParam , TCtrlInfo *errInfo);
utype* pDConRelL(const utype *inParam , TCtrlInfo *errInfo);
utype* p1124QryL(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1124CfmL(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1517QryL(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1517CfmL(const utype *puInParam, TCtrlInfo *errInfo);
utype* pResValueChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pPubAccLoginAccept(const utype *inParam,TCtrlInfo *errInfo);
utype* pPubAccGetProvCode(const utype *inParam,TCtrlInfo *errInfo);

utype* pCheckCustassureID(const utype *inParam, TCtrlInfo *errInfo);

utype* pCheckCfmM(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQMainRelConList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pGrpAccUserRelIF(const utype *inParam , TCtrlInfo *errInfo);
utype* pGetPayPri( const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDConUserEff(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQConUserRelRate(const utype *inParam , TCtrlInfo *errInfo);
utype* pDetailTreeQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDataSynReq(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2065Init(const utype *puInParam, TCtrlInfo *errInfo);
utype* pDUserHisTory(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1124ContractQry(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1124ConUserQry(const utype *puInParam, TCtrlInfo *errInfo);

//1517
utype* p1517GrpConQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1517AccRelQry(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1517Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1517Order(const utype *inParam, TCtrlInfo *errinfo);
utype* p1517Password(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQGrpContract(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1517IUCheckCfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1517CheckCfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1517IUCheckCfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1517Contract(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQMainRelConList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetPayPri( const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1517Cfm(const utype *puInParam, TCtrlInfo *errInfo);

//1219
utype* p1219IAccount(const utype *inParam, TCtrlInfo *errInfo);
utype* p1219DAccount(const utype *inParam, TCtrlInfo *errInfo);
utype* p1219DAccountM(const utype *inParam, TCtrlInfo *errInfo);
utype* p1219UAccount(const utype *inParam, TCtrlInfo *errInfo);



//实名登记
utype* p1294Init(const utype *inParam , TCtrlInfo *errInfo);

/*家庭计划功能优化*/
utype* p1290Query(const utype *inParam,TCtrlInfo *errInfo);
utype* p1291Query(const utype *inParam,TCtrlInfo *errInfo);
utype* p1291TransFile(const utype *inParam,TCtrlInfo *errInfo);

utype* p2104AddCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2104ComCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p2104Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//修改订购流水和oArder_id
utype* pPubUOrderIdLoginAccept(const utype * puInParam, TCtrlInfo* ptCtrlInfo);

extern "C" utype* p1259Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p1295Check(const utype *inParam, TCtrlInfo *errInfo);
utype* p1295Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* p2367Query(const utype *inParam, TCtrlInfo *errInfo);
//新版积分查询
utype* pNewScoreQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pzhengxgtest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTestzhoutt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//chenjj test
extern "C" utype* pPubIAlertMsg(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChgCustInfo(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1112Cfm(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* p1294CfmL(const utype *inParam,TCtrlInfo *ptCtrlInfo);
//强制开关机 by magang
extern "C" utype* p2112UseQry(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* p2112TsQry(const utype *inParam,TCtrlInfo *errInfo);

extern "C" utype* pProcessCall(const char* funcName, const int stepID, const utype* puParamIn, TCtrlInfo* errInfo);
utype* pQUserSmsPushPrc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pubSmsSendCfg(const utype *inParam, TCtrlInfo *errInfo);

/***********************四川的头文件申明****************************************/
extern "C" utype* pRuleDynamic(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubTotalMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubAccountMsg(const utype *inParam,TCtrlInfo *errInfo);
extern "C"   utype* pRuleGoldCardAdjust(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/***************************************************************/

utype* pGetRegionByPhoneNo(const utype *InParam, TCtrlInfo *errInfo);

utype* p1508Cfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2393Query(const utype *inParam,TCtrlInfo *errInfo);

/*白名单管理*/
utype* p1226CfmBatchChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1226AddCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1226DelCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1226AddCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1226CfmBatch(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUSpecLevel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*白名单历史查询*/
utype* p1226HisQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//全网白名单用户入库接口
utype *pCmWhiteAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//全网白名单用户新增接口
utype* pWhiteUserQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/**mazb**/
utype * cIScoreOrderInfo(const utype *inParam, TCtrlInfo *errInfo);

extern "C" utype* p231test(const utype *inParam, TCtrlInfo *errInfo);

utype* pPubActivCardInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p1518Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1518GrpQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*铁通移机*/
utype* p1120TTQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUAddress(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1120OrderDisCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pBoardConNoQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pConUserListIF(const utype* puInParam,TCtrlInfo *errInfo);
utype* pHLRQry(const utype *inParam, TCtrlInfo *errInfo);

utype* pListScoreFuc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype *GetProdPrcDescInner(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
/*红名单管理优化*/
utype* p2104CfmBatchChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUAccessType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
#define pProcCall(a,b,c) pProcessCall(__FUNCTION__, a,b,c)

utype* p2143Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pOpenData(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pCloseData(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQueryData(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pSwitchClose(const utype *inParam, TCtrlInfo *errInfo);
utype* pSwitchOpen(const utype *inParam, TCtrlInfo *errInfo);
utype* pSwitchOpen(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pSwitchClose(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p1221Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1692Query(const utype *inParam, TCtrlInfo *errInfo);
//客户服务综合配置
utype* pGetConfigId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Dyn(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501ModQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Modify(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//信用度调整
utype* pULimitOweOfUserInfoSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUserBusiInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2263Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2263SetPayType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2263UpdatePayType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2263DelPayType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2263DelPayType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2263Cfm(const utype *InParam, TCtrlInfo *ptCtrlInfo);
utype *pCom1501Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *p2262Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  pRuleGoldCardAdjust(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//songhui begin
extern "C" utype* pUUserChgBrnad(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2294Cfm(const utype* inParam,TCtrlInfo* errInfo);
extern "C"  utype* pB925UpStatus(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* pB925UpDepMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//songhui end
//G3固话转标准全球通查询
utype* p2269Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//短信发送查询
utype* p1690Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*多OP改造，客户首页部分*/
utype* pQCnttInfoList(const utype *inParam,TCtrlInfo *errInfo);
utype* pBscUsrInfoQry(const utype *inParam,TCtrlInfo *errInfo);
utype* pFuncElemQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pElemInfoQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//流程路由调用 add by zhengxg
extern "C" utype* pPubCallFunc(const char* sProvinceId, const char* sFuncName, const utype* puParamIn, TCtrlInfo* errInfo);

//指标展现 add by haoxz
utype* pQTargetDisInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pUnLockUserPwd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pInsertAuthInfoByPhone(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pSendErrorMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//批量发送短信
//全局流程调用结构 add by zhengxg
typedef struct tagFuncCtrl {
    char    sProvinceId[10 + 1];
    char    sFuncName[100 + 1];
    char    sDllName[255 + 1];
	void*   vDllHandle;
	TUtypeFuncPtr tFunc;
} funcCtrl;

//获取省份标志ID add by zhengxg
#define TYPEPHONE		1
#define TYPELOGINNO		2
#define TYPEGROUPID		3
//通过相应的入参获取省份group_id
extern "C" int pPubGetProvinceCode(const char* sInParam, const int iParamType, char* sOutParam, TCtrlInfo *errInfo);
//校验入参中是否有省份group_id，如果没有则添加上
extern "C" int pPubChkProvinceCode(utype* uOutParam, TCtrlInfo *errInfo);
extern "C"  utype* pyinzxa(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
#define pProcCall(a,b,c) pProcessCall(__FUNCTION__, a,b,c)

utype* pUserHeadChk(const utype *inParam, TCtrlInfo *errInfo);
utype* p1519Query(const utype *inParam, TCtrlInfo *errInfo);
utype* p1519Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetLoginOrder(const utype *inParam, TCtrlInfo *errInfo);
utype* p1519QueryL(const utype *inParam, TCtrlInfo *errInfo);

utype* pPubGetDoubleNums(const utype *inParam,TCtrlInfo *errInfo);
utype* pPubRunStopOpQry(const utype *inParam,TCtrlInfo *errInfo);
utype* p1100QMbr(const utype *inParam, TCtrlInfo *errInfo);
utype* p1100QMbrMainId(const utype * inParam,TCtrlInfo *errInfo);
utype* pOpenStopDeal(const utype * inParam,TCtrlInfo *errInfo);

utype* pQResSrvInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pCheckOpr(const utype *inParam,TCtrlInfo *errInfo);
utype* pQResSrvOprType(const utype *inParam,TCtrlInfo *errInfo);
utype* pDealResSrvInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pDealRepairMsg(const utype *inParam,TCtrlInfo *errInfo);

utype* p2215Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1629Query(const utype *inParam,TCtrlInfo *errInfo);
utype* p2267Query(const utype *inParam,TCtrlInfo *errInfo);
utype *pGetGroupRegion1(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1506Query(const utype *inParam,TCtrlInfo *errInfo);
utype* pQResSellRdList(const utype *inParam,TCtrlInfo *errInfo);
utype* pQResSellRd(const utype *inParam,TCtrlInfo *errInfo);

utype* pCssCICCheck(const utype *inParam,TCtrlInfo *errInfo);
utype* pIptvUserCheck(const utype *inParam,TCtrlInfo *errInfo);
utype* p2202Check(const utype *inParam,TCtrlInfo *errInfo);
utype* pPubTotalMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* pPubAccountMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* pGetLoginAccpet(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pCssCICCfm(const utype *InParam, TCtrlInfo *ptCtrlInfo);

//1501
utype* pGetConfigId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Dyn(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501ModQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Modify(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pCom1501Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1501CfmL(const utype *inParam,TCtrlInfo *errInfo);
int pubGetCharNum(char * sourceStr,char sign);
utype* p2211Qry(const utype *InParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubSendMsg(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* pChgCustStatusInfo(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChgConInfo(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pChgUserInfo(const utype *inParam, TCtrlInfo *errInfo);

utype* p1150CfmL(const utype * inParam, TCtrlInfo *errInfo);

utype* pFREECheckQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pFeeAwokeCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2215Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2215Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2209Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pFeeAwokeInit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2210DelCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1347Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1346Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pFreeCheckCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2209Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2210Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);


utype* pQRentMachFavInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pQRentMachInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* p2205Fee(const utype *inParam,TCtrlInfo *errInfo);
utype* p2206Query(const utype *inParam,TCtrlInfo *errInfo);
utype* p2207Query(const utype *inParam,TCtrlInfo *errInfo);
utype* p2207Fee(const utype *inParam,TCtrlInfo *errInfo);
utype* pGetUserL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCardFeeQuery(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pConDetailQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pScoreExchgCfmOrder(const utype * inParam,TCtrlInfo *errInfo);

utype* pQConUserRelList(const utype * inParam,TCtrlInfo *errInfo);
utype* pDConUserInfoIf(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserConTractQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pChkOutCfm(const utype * inParam,TCtrlInfo *errInfo);
utype* pDConUserALL(const utype * inParam,TCtrlInfo *errInfo);

/*1646*/
utype* p1646Check(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1646MembSel(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1646Order(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1646Qry(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQGrpContract(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1646PauseResume(const utype *puInParam, TCtrlInfo *errInfo);
utype* pConUserTypeChk( const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p2262IntFilmOrder (const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2262Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2262SendMesage (const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetLoginAccpet(const utype *inParam, TCtrlInfo *errInfo);

utype* p2283Query(const utype *inParam, TCtrlInfo *errInfo);

utype* p2211Cfm(const utype *InParam, TCtrlInfo *ptCtrlInfo);
utype* pOtherPayCheck(const utype *inParam, TCtrlInfo *errInfo);
utype* pConPriGen(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
///##################### 一卡多号 ##################
utype* pChkMasterUser(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetSlavUserList(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkSlavUser(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pOneSimMultiNoOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pOneSimMultiNoCancel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1117ChkSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1117OrdInterFace(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1117CancelInterFace(const utype *inParam, TCtrlInfo *ptCtrlInfo);
///#####################一卡多号 ##################
extern "C" utype* p2112TsQrySx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2282Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pInsrtConAuthen(const utype *inParam, TCtrlInfo *errInfo);

utype* p2283Cron(const utype *inParam,TCtrlInfo *errInfo);
utype* pCheckProd(const utype *inParam,TCtrlInfo *errInfo);
utype* pCheckInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pCheckPhoneNo(const utype * inParam,TCtrlInfo *errInfo);

extern "C" utype* p1100QMbrMainIdSX(const utype * inParam,TCtrlInfo *errInfo);
utype* pQryUserBaseMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserBaseForInter(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2211QryInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryLoginRd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pAcctFavCheck(const utype *inParam, TCtrlInfo *errInfo);

utype* pQryUserBaseMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//add by zhoutt
utype* pQMebMod(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQGetMebMod(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pUserHeadChk(const utype *inParam, TCtrlInfo *errInfo);
utype* p1501QryCond(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1524Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1524Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRollBack(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUResOccupy(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubTPortPre(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQryPhoneHlr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//2261
utype* pPubGetMulNums(const utype * inParam,TCtrlInfo *errInfo);

extern "C" utype* p2261Cfm(const utype *InParam, TCtrlInfo *ptCtrlInfo);

utype* p2261Qry(const utype *InParam, TCtrlInfo *ptCtrlInfo);
int fGetErrorMsg(char *vsmpMsg,char *retMsg,char *retCode);
utype* p2218Init(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2218L(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2262Cfm(const utype *InParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p2218Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2287Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2287Cron(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* p2287Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cDoubCardCnt(const utype * inParam,TCtrlInfo *errInfo);

utype* p1526Query(const utype *inParam,TCtrlInfo *errInfo);
utype* p1526QL(const utype *inParam,TCtrlInfo *errInfo);
utype* pQUserBaseInfoL(const utype *inParam,TCtrlInfo *errInfo);
utype* p1526L(const utype *inParam,TCtrlInfo *errInfo);
utype* p1526UStatus(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* pCreditLevelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDataImp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//有价卡销售改造
extern "C" utype* p1126QResAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126QResSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pGetLoginAccpetSms(const utype *inParam, TCtrlInfo *errInfo);
utype* pSMSSendMesage(const utype *InParam, TCtrlInfo *ptCtrlInfo);
utype* pMMSSendMesage(const utype *InParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* pSMmsCfm(const utype *InParam, TCtrlInfo *ptCtrlInfo);
utype* pSMmsChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  pTDUserEffBalance(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQryUserProdByCustId(const utype *inParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pIDchntermmobile(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pUDchntermmobile(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pUDchntermmobileStatus(const utype *inParam, TCtrlInfo *errInfo);

utype* pInterNetCrl(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pNetLoginAccpet(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pHwNewPWChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pChkKQ(const utype *inParam,TCtrlInfo *errInfo);

extern "C" utype* p1144Query_SX(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p1144Query_AH(const utype *puInParam, TCtrlInfo *errInfo);

utype* pChkResCode(const utype *inParam,TCtrlInfo *errInfo);

extern "C" utype* pSlectProd_SX(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pSlectProd_AH(const utype *inParam, TCtrlInfo *errInfo);
utype* pInterGetLoginAccpet(const utype *inParam, TCtrlInfo *errInfo);
utype* pInterSendSms(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2276CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2276QryL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1501Modify(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1501CfmL(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckBusiLimit(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pActiveCardInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserInfoFunc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pChkSlaveFunc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pChkMasterUser(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pGetSlavUserList(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pChkSlavUser(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1117ChkSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1117ChkAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1117MulAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1117MulSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pOneSimMultiNoOrder(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pOneSimMultiNoCancel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126InterFace(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p1100InterL(const utype *inParam, TCtrlInfo *errInfo);
utype* p1144InterChkL(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1144InterDeaL(const utype *puInParam, TCtrlInfo *errInfo);
utype* pCheckPassWord(const utype* puInParam,TCtrlInfo *errInfo );
utype* pIsNotMaxCountNet(const utype* puInParam,TCtrlInfo *errInfo );
utype* pInsertCheckPwdRecNet(const utype* puInParam,TCtrlInfo *errInfo );
utype* pCondGetLoginAccept(const utype* puInParam,TCtrlInfo *errInfo );
utype* pQryOprInfo(const utype* puInParam,TCtrlInfo *errInfo );
utype* pHwPhoneCheck(const utype* puInParam,TCtrlInfo *errInfo );
utype* pHwHisQry(const utype* puInParam,TCtrlInfo *errInfo );
utype* pCheckPassWordOut(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pQSiInfoByParm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pChkSiInfoMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * p4079Cfg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype *pUAccessType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p4079Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype * p1100SendAwoke(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype *p1100FamilyChg(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p1646UserList(const utype *puInParam, TCtrlInfo *errInfo);

utype* pInsertCheckPwdRecChn(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIsNotMaxCountChn(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pChnPWChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pSiBaseInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pSiBusiInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2299Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pCreditCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pCreditMod(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIsNotMaxCountChn(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUserStateQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQSiBusiByParm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQSiBusiChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * p4078Cfg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * p1294QL(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2101Query(const utype *inParam,TCtrlInfo *errInfo);
utype* p2301Query(const utype *inParam,TCtrlInfo *errInfo);
utype* p2301CfmL(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* p2102CfmL(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2261CfmL(const utype *inParam,TCtrlInfo *errInfo);
utype* p2102OrderCfmL(const utype *inParam,TCtrlInfo *errInfo);
utype* pCssCICCfmL(const utype *inParam,TCtrlInfo *errInfo);
utype* p1613CfmL(const utype *inParam,TCtrlInfo *errInfo);
utype* pQUserRegionInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* p2101QL(const utype *inParam,TCtrlInfo *errInfo);
utype* p2262InsertLoginOpr(const utype *inParam,TCtrlInfo *errInfo);
utype* pHWRingBoxCfm(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* p1126AgentQryAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126AgentQrySx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126AgentQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126CheckAh(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126CheckSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSellSimCard(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSellSimCardAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSellSimCardSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pActiveCardInfoAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pActiveCardInfoSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pActiveCardInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126InterFace(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1126IFCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIllegalMoney(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQBalanceInfo(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype* pStopTime(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pStopTimeSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pStopTimeAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2087CfmL(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p2087Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2300Cfm(const utype *puInParam, TCtrlInfo *errInfo);
utype* p2262Cfm(const utype *InParam, TCtrlInfo *ptCtrlInfo);
utype* pIllegalMoney(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUpdateUserExtInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" int ippsDES(int op, char *key, char *inblock, char *outblock, int len);
utype* p1166Batch(const utype *inParam,TCtrlInfo *errInfo);

utype* pIConRelL(const utype *inParam , TCtrlInfo *errInfo);
utype* pUConRelL(const utype *inParam , TCtrlInfo *errInfo);
utype* pDConRelL(const utype *inParam , TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByEndValueClass(const utype *inParam , TCtrlInfo *errInfo);

extern "C" utype* pQueryBrandInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQueryBrandInfoSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQueryBrandInfoAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1532Query(const utype *inParam,TCtrlInfo *errInfo);
extern "C" utype* p1112ChkProd(const utype *inParam,TCtrlInfo *errInfo);

utype * p1120CfmL(const utype *inParam, TCtrlInfo *errInfo);
utype* pDealCardInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pSndOneBoss(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pKDHisQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* p1117OrdFinish(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1117COrdFinish(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p1532Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIResValueUse(const utype *inParam,TCtrlInfo *errInfo);
utype* cIResValueUseHis(const utype *inParam,TCtrlInfo *errInfo);
utype* p1532CfmL(const utype *inParam,TCtrlInfo *errInfo);
utype* pResValueUseCron(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQryDataFlowMoney(const utype *puInParam,TCtrlInfo* errInfo);

utype* p1533CfmL(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1532OrderCfmL(const utype *inParam, TCtrlInfo *errInfo);
utype* pWlanInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pOpreation(const utype *inParam,TCtrlInfo *errInfo);
utype* pUserImeiInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pubGetResProvName(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1535QUserId(const utype *inParam,TCtrlInfo *errInfo);
utype* p1535QKdMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* pKickOutLanUse(const utype *inParam,TCtrlInfo *errInfo);
utype* pMailTrans(const utype *inParam,TCtrlInfo *errInfo);

utype* pSndBossMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cUResValueUse(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResValueUseByIdNoAndBusi(const utype * inParam,TCtrlInfo *errInfo);
utype * pProcQry(const utype *inParam, TCtrlInfo *errInfo);

utype* pAdviceQuery(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2283CheckInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* p2283DelAll(const utype *inParam, TCtrlInfo *errInfo);
utype* pubServiceNoInfoForCust(const utype* p, TCtrlInfo* errInfo);
int getValueByIndex(char *S, int I, char CH, char *RET);
utype* pMailTrans(const utype* p, TCtrlInfo* errInfo);
utype*	p2074GetSimByPhone(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	p2074ChkFile(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQSimCardList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	p2074GetSimByPhoneNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p9999Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* cISmpCardModInfo_Sx(const utype * inParam,TCtrlInfo *errInfo);
utype*	pHWCardPayIn(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	p1102Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype*	pLossDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2112Batch(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2112BatchChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype*  p2078Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pUserImeiInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* pGetMaster(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p8899Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1507Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1507QFeeNum(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*add by lankai begin*/
/*充值卡黑名单查询解除*/
utype* p2062Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2062Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*垃圾短信承诺书*/
utype* p2067Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2067Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*垃圾短信承诺书审批查询*/
 utype* p2041Query(const utype *inParam,TCtrlInfo *ptCtrlInfo);
 utype* p2041QType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*垃圾短息承诺书审批*/
 utype* p2040Appr(const utype *inParam,TCtrlInfo *ptCtrlInfo);
/*用户满意度*/
utype* p2058Chk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p2058Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pTempInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPopeDomChkSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPopeDomChkAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);

extern "C" utype* pSlaveCustListSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSlaveCustListAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSlaveCustList(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSlaveChkSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSlaveChkAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pSlaveChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQUserRelByMasterSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQUserRelByMasterAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQUserRelByMaster(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQUserRelBySlaveSx(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQUserRelBySlaveAh(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pQUserRelBySlave(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//网厅评价需求
utype* p1537CfmL(const utype *inParam, TCtrlInfo *errInfo);
utype* p1537ChkInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* p1537QNInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* p1537Query(const utype *inParam, TCtrlInfo *errInfo);
utype* p1538CfmL(const utype *inParam, TCtrlInfo *errInfo);
utype* p1539CfmL(const utype *inParam, TCtrlInfo *errInfo);
utype* p1540CfmL(const utype *inParam, TCtrlInfo *errInfo);

utype* p2072CfmL(const utype *inParam, TCtrlInfo *errInfo);
utype* p2072Query(const utype *inParam, TCtrlInfo *errInfo);
utype* pA09(const utype *inParam, TCtrlInfo *errInfo);
utype* pA05(const utype *inParam, TCtrlInfo *errInfo);
utype* pA16(const utype *inParam, TCtrlInfo *errInfo);
utype* p1613OrderCfmL(const utype *inParam, TCtrlInfo *errInfo);

utype* pQUserFeeScoreInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pSatisfyChk(const utype *inParam, TCtrlInfo *errInfo);
utype* pSatisfySend(const utype *inParam, TCtrlInfo *errInfo);

utype* pIUserLoginMsgInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1124MsgL(const utype *inParam,TCtrlInfo *errInfo);

//haoxz
utype* p1114PwdTest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubGetMaxTime(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubInsErrorTime(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubTransLimit(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1166AllQry(const utype *inParam,TCtrlInfo *errInfo);
utype * pWaitChkFreePhone(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2068Chk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2068Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2068Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pListTypeChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p1506AllCard(const utype *inParam, TCtrlInfo *errInfo);
utype*	pDealFile(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCnttBeginChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pOtherPayCheckB(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pOtherPayCheckC(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pBillDayChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p1542Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPasswdAlertSMS(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubQryRegisteInfoByIdNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p2107CfmAH(const utype * inParam, TCtrlInfo *errInfo);
utype* p2107CfmSX(const utype * inParam, TCtrlInfo *errInfo);

utype* pUsrInfoQryForOut(const utype * inParam, TCtrlInfo *errInfo);

/* 对账框架 */
utype* p2045LoadFileFail(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2045OutDataInit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2045InDataInit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2045CompareData(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2045InitDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2045AdjAcc(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2045Compare(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pChkIsSell(const utype *inParam,TCtrlInfo *errInfo);
utype* p2045InsertResult(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2045AutoAdj(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2045OutDataDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p2043Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*远程写卡证件校验*/
utype* p2088Check(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* p2063GetOpr(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2063GetAccept(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//外部提供的假bp
utype* pChannelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* checkCredit(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* checkFreeFlag(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p1551Qry(const utype* inParam,TCtrlInfo* errInfo);
utype * p2126InsertReleaseBlack(const utype * inParam,TCtrlInfo * errInfo);
utype * p2126QryReleaseBlack(const utype * inParam,TCtrlInfo * errInfo);

extern "C" utype *pGetMulNumsSX(const utype *, TCtrlInfo *);

extern "C"  utype* pQProdInfoAH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C"  utype* pQProdInfoSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
#endif
