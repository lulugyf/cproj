#ifndef __TESTBC_H__
#define __TESTBC_H__

///////////////// BC /////////////////////
utype* cGetRoute(const utype *inParam,TCtrlInfo *errInfo);
utype* cQdCustMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* cIdCustMsgTest(const utype *inParam,TCtrlInfo *errInfo);
utype* cQdCustMsgTest(const utype *inParam,TCtrlInfo *errInfo);

utype* cdgrpusermsgByusername(const utype *inParam,TCtrlInfo *errInfo);

utype* pQCustInfoByCustId(const utype *inParam,TCtrlInfo *errInfo);



utype* pQUserInfoByMulCol01(const utype *inParam,TCtrlInfo *errInfo);
utype* cQdGrpUserMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* cQdGrpUserMebMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* pGrpUserInfo(const utype *inParam, TCtrlInfo *errInfo);

utype* pQCustInfoByMulIccId(const utype *inParam, TCtrlInfo *errInfo);
utype* cQCustInfoByMulIccId(const utype *inParam, TCtrlInfo *errInfo);

utype* cIdGrpUserMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* cIdGrpUserMebMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* pGrpUserAdd(const utype *inParam,TCtrlInfo *errInfo);
utype* cQdCustMsgByPhoneNoMpTest(const utype *inParam,TCtrlInfo *errInfo);
utype* cUdCustMsgByPhoneNoTest(const utype *inParam,TCtrlInfo *errInfo);
utype* cIdCustMsgTest(const utype *inParam,TCtrlInfo *errInfo);
utype* cQdCustMsgByBelongCode(const utype *inParam,TCtrlInfo *errInfo);
utype* cDdCustMsgByPhoneNoTest(const utype *inParam,TCtrlInfo *errInfo);

utype* cQUserMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* pGetUserMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* cIUserExtInfoHisbyNo(const utype *inParam,TCtrlInfo *errInfo);
utype* cIUserInfoHisbyNo(const utype *inParam,TCtrlInfo *errInfo);


utype* pQUserCustInfoByPhoneNo(const utype *inParam,TCtrlInfo *errInfo);
utype* cQdGrpUserMsg(const utype *inParam,TCtrlInfo *errInfo);
utype* cQdGrpUserMembMsg(const utype *inParam, TCtrlInfo *errInfo);

 utype* cQBookPrc(const utype * inParam,TCtrlInfo *errInfo);
 utype* cQProdPrc(const utype * inParam,TCtrlInfo *errInfo);
 utype* pQBookPrc(const utype * inParam,TCtrlInfo *errInfo);

 //////####################test for yangxj end##################

//////####################test for changecard BC##################
utype* cUur_UserSim_info(const utype * inParam,TCtrlInfo *errInfo);
//utype* p1110Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserSimQuery(const utype * inParam,TCtrlInfo *errInfo);

/////####################test for lids BC##################


/////###################test for wencq##################
utype* cQAllTables(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAllUsers(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginMsgByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginMsgByLoginNo(const utype * inParam,TCtrlInfo *errInfo);

/////###################test111##################
utype* cQLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginCheck(const utype * inParam,TCtrlInfo *errInfo);
/////###################test2222##################
utype* cQdGrpUsermsgDxh(const utype * inParam,TCtrlInfo *errInfo);
utype* cIdGrpUsermsgDxh(const utype * inParam,TCtrlInfo *errInfo);
utype* cUdGrpmsgDxhByname(const utype * inParam,TCtrlInfo *errInfo);
utype* cQmsgDxh(const utype * inParam,TCtrlInfo *errInfo);

utype* cQsparamcodeDxh(const utype * inParam,TCtrlInfo *errInfo);
utype* cUcfuncparamDxh(const utype * inParam,TCtrlInfo *errInfo);
utype* pTwoFunctionDxh(const utype * inParam,TCtrlInfo *errInfo);


utype* pMutilmsgDxh(const utype * inParam,TCtrlInfo *errInfo);

utype* pUpdatemsgDxh(const utype * inParam,TCtrlInfo *errInfo);

utype* cDdGrpmsgDxhByname(utype *inParam, TCtrlInfo *errInfo);
utype* pDeletemsgDxh(utype *inParam, TCtrlInfo *errInfo);
utype* pInsertmsgDxh(const utype * inParam,TCtrlInfo *errInfo);


utype* p1110CfmDxh(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIur_UserSim_info_hisD(utype *inParam, TCtrlInfo *errInfo);
//utype* p1110Cfm(utype *inParam, TCtrlInfo *errInfo);
//////####################test for wencq BP##################
utype* cILoginCheckRc(const utype * inParam,TCtrlInfo *errInfo);

utype* pSelectUserTables(utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRLoginCheck(utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////####################test for zhaoqm###############
utype* pCrtEmpl(utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQYYYYMMDD(utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQEmployeeAccept(utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIDemployee(utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryCustMsgTest(utype *inParam, TCtrlInfo *errInfo);



/////####################test for zengffBC###############
utype* cSdcustinfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cSduserinfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIdRule(const utype * inParam,TCtrlInfo *errInfo);

utype* cSdcustmsgcontract(const utype * inParam,TCtrlInfo *errInfo);
utype* cSdcustmsgphone(const utype * inParam,TCtrlInfo *errInfo);
utype* cSdgrpusermsg(const utype * inParam,TCtrlInfo *errInfo);

utype* cIUserExt(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserExt(const utype * inParam,TCtrlInfo *errInfo);
utype* cQmUserExt(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserExt(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserExt(const utype * inParam,TCtrlInfo *errInfo);
/////####################test for zengffBP###############
utype* pSvcmumByCustcerno(const utype *puInParam, TCtrlInfo *ptCtrlInfo);


utype* pUsernameByContractNoPhone(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pQFchange(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/////####################test for dongxhBP###############
utype* pGrpUserInfodxh(utype *inParam, TCtrlInfo *errInfo);
/////####################test for zhouttBP###############
utype* pGrpUserInfoztt(utype *inParam, TCtrlInfo *errInfo);
utype* cQLoginInfoByLogin_No(utype *inParam, TCtrlInfo *errInfo);
utype* pLoginInfoByLogin_No(utype *inParam, TCtrlInfo *errInfo);
utype* cQDgrpUserMebmsgById(utype *inParam, TCtrlInfo *errInfo);
utype* pQDgrpUserMebmsgByIdUser(utype *inParam, TCtrlInfo *errInfo);
utype* cIDgrpuserInfo(utype *inParam, TCtrlInfo *errInfo);
utype* pIDgrpuserInfo(utype *inParam, TCtrlInfo *errInfo);
utype* cUDGRPmsg(utype *inParam, TCtrlInfo *errInfo);
utype* pUDGRPmsg(utype *inParam, TCtrlInfo *errInfo);
utype* cDgrpuserMsg(utype *inParam, TCtrlInfo *errInfo);
utype* pDgrpuserMsg(utype *inParam, TCtrlInfo *errInfo);

utype* cQgrpuserMsgbyNo(utype *inParam, TCtrlInfo *errInfo);
utype* pQgrpuserMsgbyNo(utype *inParam, TCtrlInfo *errInfo);

utype* cQMutlTableSparam(utype *inParam, TCtrlInfo *errInfo);
utype* pQMutlTableSparam(utype *inParam, TCtrlInfo *errInfo);

utype* cQMutlRow(utype *inParam, TCtrlInfo *errInfo);
utype* pQMutlRow(utype *inParam, TCtrlInfo *errInfo);


utype* cQFindusByNo(const utype *inParam, TCtrlInfo *errInfo);
utype* cQFindusByUserId(const utype *inParam, TCtrlInfo *errInfo);
utype* p1130Query(const utype *inParam, TCtrlInfo *errInfo);


utype* cQSaverepByNo(const utype *inParam, TCtrlInfo *errInfo);

utype* pQMulResult(const utype *inParam, TCtrlInfo *errInfo);



utype* cQCustUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUserInfoByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);

utype* cQUserExtInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQUserExtInfo(const utype *inParam, TCtrlInfo *errInfo);


utype* cUUserExtInfo (const utype *inParam, TCtrlInfo *errInfo);
utype* pUUserExtInfo (const utype *inParam, TCtrlInfo *errInfo);



utype* cQUserInfoByNoType (const utype *inParam, TCtrlInfo *errInfo);


utype* pQFunctionByNode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//////####################test for zhabh BP##################
utype* cILoginCheckRc(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginMsgByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cSLoginMsgByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pRLoginCheck(utype *puInParam, TCtrlInfo *ptCtrlInfo);

//////####################test for gaoxp BC##################
//utype* cQdGrpUserMg(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQdGrpUserMembMg(const utype * inParam,TCtrlInfo *errInfo);
utype* pGrpUser(const utype *inParam, TCtrlInfo *errInfo);
//utype* cICustMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* pCustMsgAdd(const utype *inParam,TCtrlInfo *errInfo);
//utype* cGetGarBageSmsByMonth(const utype * inParam,TCtrlInfo *errInfo);
//utype* cGetGarBageSmsByDay(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetGarBageSms(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//utype* cIGarBageSms(const utype * inParam,TCtrlInfo *errInfo);
utype* pInsertGarBage(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//utype* cUGarBageSms(const utype * inParam,TCtrlInfo *errInfo);
utype* pUpdateGarBage(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//utype* cDGarBageSms(const utype * inParam,TCtrlInfo *errInfo);
utype* pDeleteGarBage(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//utype* cIContractInfoHis(const utype * inParam,TCtrlInfo *errInfo);
//utype* cICustIdentifyInfoHis(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQContractinfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
//utype* cUContractInfoByContractNo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cUCustIdentifyInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
//utype* cUUserInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQCustContactinfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQUserinfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetContractInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckPasswd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype*  pGetComInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//utype* cQCustLevelByCustLevel(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQChnGroupByGroupId(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIPwdresetInfo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIPwdresetInfoHis01(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIPwdresetInfoHis02(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQPwdresetInfoByMulCol01(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQPwdresetInfoByMulCol02(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQPwdresetInfoByMulCol03(const utype * inParam,TCtrlInfo *errInfo);
//utype* cUpwdresetInfoByMulCol01(const utype * inParam,TCtrlInfo *errInfo);



//////####################test for gaoxp BC##################
utype* cQLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* pRTest(utype *puInParam, TCtrlInfo *ptCtrlInfo);



/////####################test for bianchuang BC##################
utype* pRLoginCheckB(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserTeamById(const utype * inParam,TCtrlInfo *errInfo);

/////####################test for taohj BC&BP##################
utype* cQCtCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCtCustIdentifyInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCtGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);

/////####################test for chudg BC&BP##################
utype* cQLoginMsgByLoginNo1(const utype * inParam,TCtrlInfo *errInfo);
utype* pRLoginCheck1(utype *puInparam, TCtrlInfo *ptCtrlInfo);
utype* cQLoginMsgByLoginNoA(const utype * inParam,TCtrlInfo *errInfo);
utype* pRLoginCheckA(utype *puInparam, TCtrlInfo *ptCtrlInfo);
//utype* cQChnGroup(const utype * inParam,TCtrlInfo *errInfo);

////####################test for lifl BC&BP###################
utype* cQCustMsgByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* pQryCustLove(const utype * inParam,TCtrlInfo *errInfo);

////####################test for suhq BC&BP###################
utype* cQGetCustinfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pRGetCustInfo(const utype * inParam,TCtrlInfo *errInfo);

////####################test for denghd BC&BP###################
utype* cQryCustNameByCustid(const utype * inParam,TCtrlInfo *errInfo);
utype* pRGetCustName(utype *puInParam, TCtrlInfo *ptCtrlInfo);

////####################test for chenjj BC&BP###################
utype* cQCustIdByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pRGetCustId(utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cQMasterPhoneBySlavePhone(utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQSlavePhoneByMasterPhone(utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRGetMasterPhone(utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRGetSlavePhone(utype *puInParam, TCtrlInfo *ptCtrlInfo);

///---------------------------------------2009-10-13--------------------------------------
/////####################test for pQFchange BC###############
/*utype* cQUserExt(const utype * inParam,TCtrlInfo *errInfo);
utype* pQFchange(const utype *puInParam, TCtrlInfo *ptCtrlInfo);


utype* cQDemployeeById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSdeptmsgByParentID(const utype * inParam,TCtrlInfo *errInfo);
*/
/////####################test for pDoubleStats BC###############
utype* cQUserrelA(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserrelB(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserStatsB(const utype * inParam,TCtrlInfo *errInfo);
utype* cQinfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);

utype* pOptrLogChk(const utype *puInParam, TCtrlInfo *errInfo);
utype* pGetDoubleNums(const utype *puInParam, TCtrlInfo *errInfo);
utype* pCheck_Credit(const utype *puInParam, TCtrlInfo *errInfo);
utype* pDoubleStats(const utype *puInParam, TCtrlInfo *errInfo);

/////####################LoginNoManagement######################
//utype* LoginNoManage(utype *uInParam, TCtrlInfo *ptCtrlInfo);
//utype* cQsysdate(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQsysaccept(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQbs_LoginMsg_dictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIbs_LoginMsg_dict(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQLoginRole(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQLoginRoleMsg(const utype * inParam,TCtrlInfo *errInfo);
//utype* cILoginRoleHis(const utype * inParam,TCtrlInfo *errInfo);
//utype* cDLoginRole(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQLoginPopodom(const utype * inParam,TCtrlInfo *errInfo);
//utype* cILoginPopodomHis(const utype * inParam,TCtrlInfo *errInfo);
//utype* cDLoginPopodom(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQLoginMsg(const utype * inParam,TCtrlInfo *errInfo);

//utype* cQSysRightSeq(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIPopedom(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIFunction(const utype * inParam,TCtrlInfo *errInfo);
//utype* cUFunction(const utype * inParam,TCtrlInfo *errInfo);
//utype* pFunction_Ist(utype *puInParam, TCtrlInfo *ptCtrlInfo);
//utype* cQSysDate(const utype * inParam,TCtrlInfo *errInfo);

/////####################test for 1100###############

/*utype* cQUserinfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserrelA(const utype * inParam,TCtrlInfo *errInfo);
utype* pOptrLogChk(const utype *puInParam, TCtrlInfo *errInfo);
utype* pGetDoubleNums(const utype *puInParam, TCtrlInfo *errInfo);
utype* pCheck_Credit(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1100Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1100Valid(const utype *puInParam, TCtrlInfo *errInfo);
utype* p1100Cfm(const utype *puInParam, TCtrlInfo *errInfo);*/


//test lvlei
utype* cUdPhoneResByPhonenoNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pubUpdatePhoneRes(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQdGiftListByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQdGiftListByMulCol04Col05Col06(const utype * inParam,TCtrlInfo *errInfo);
utype* cQdGiftListByMulCol05Col06(const utype * inParam,TCtrlInfo *errInfo);
utype* pubQueryGiftList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryGiftTypeCode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryGiftTypeList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQueryUserInstantFee(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubChangeUserMark(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubQuerySimResLimitByPhone(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cDdChgScoreByUserId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQdChgScoreByUserId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQdChgUserInfoByUserId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUdChgScoreByUserId(const utype * inParam,TCtrlInfo *errInfo);
utype* pubQueryUserMark(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//utype* pQSimResByPhone(const utype * inParam,TCtrlInfo *errInfo);
//utype* pUResState(const utype * inParam,TCtrlInfo *errInfo);

//test zhaoqm
utype* cQSdeptmsgByParentID(const utype * inParam,TCtrlInfo *errInfo);

utype* pQDeptmsg(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserByCustid(const utype * inParam,TCtrlInfo *errInfo);

utype* pQAllUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBRANDDICTById(const utype * inParam,TCtrlInfo *errInfo);

//test zhenghan
utype* pCustInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cUCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByFieldcode(const utype * inParam,TCtrlInfo *errInfo);

//test huchao
utype* pQdPhoneresByPhoneno_no(const utype * inParam,TCtrlInfo *errInfo);
utype* cQdPhoneresByPhoneno_no(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSimResLimitByPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* pQryAcctInfoByCertId(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryCustInfoByCertId(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryUserInfoByCertId(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryAcctInfoByCustId(const utype *inParam, TCtrlInfo *errInfo);
utype* cQContractinfoByCust_id(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByCust_id(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByMulCol01(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByMulCol02(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByCust_id(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAccountTypeByAccountType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnicodedef_dictByCodeid(const utype * inParam,TCtrlInfo *errInfo);
utype* cQIdType_DictByIdtype(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRunCodeDictByRunCode(const utype * inParam,TCtrlInfo *errInfo);
utype* pPubResChkPhoneAndCard(const utype *inParam, TCtrlInfo *errInfo);
/***test begin**
utype* pChkComDetail(const utype *inParam, TCtrlInfo *errInfo);
utype* pChkUserProdMbr(const utype *inParam, TCtrlInfo *errInfo);
utype* cQUserGroupMbrByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserPrcByPrcAndPar(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserPrcByIdNoAndGoupId(const utype * inParam,TCtrlInfo *errInfo);
**test end*/
/////####################test for R1122Valid begin ##############
utype* cQUserExpireInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* p1122Valid(const utype *inParam, TCtrlInfo *errInfo);

/////####################test hanzg #####################

utype* cGetRoute(const utype * inParam,TCtrlInfo *errInfo);
/////####################test  end #####################

//utype* cQProdRel(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQPrcRel(const utype * inParam,TCtrlInfo *errInfo);

///test for lq begin
//utype* cQProdRelByCond(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQPrcRelByCond(const utype * inParam,TCtrlInfo *errInfo);
utype* pBusiRelChktest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
///test for lq end

//test shaoxb begin
utype* cQdtest(const utype * inParam,TCtrlInfo *errInfo);
utype* pTest(const utype * inParam,TCtrlInfo *errInfo);
utype* pTestI(const utype * inParam,TCtrlInfo *errInfo);
utype* cIdTest(const utype * inParam,TCtrlInfo *errInfo);

//test shaoxb end

utype* cQUserinfoByPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* pcao01Query(const utype * inParam,TCtrlInfo *errInfo);

//utype* cQUserForumInfoByUserName(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIUserForumInfo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIUserForumInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
//utype* p1537C(const utype *inParam,TCtrlInfo *errInfo);
//utype* p1537Qry(const utype *inParam,TCtrlInfo *errInfo);
//utype* p1537L(const utype *inParam,TCtrlInfo *errInfo);
//utype* p1537F(const utype *inParam,TCtrlInfo *errInfo);
//utype* cGetGradeAvgByAttrValue(const utype * inParam,TCtrlInfo *errInfo);
//utype* cGetUserForumByTime(const utype * inParam,TCtrlInfo *errInfo);
//utype* cGetUserForumByTopFlag(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQCntOfUserforumByAttrValue(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQUserBrandIdByIdNo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQUserBrandNameByBrandId(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQUserForumRelByApproveAccept(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQUserGroupIdByIdNo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQUserGroupNameByGroupId(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQUserFormByAttrValue(const utype * inParam,TCtrlInfo *errInfo);
//utype* p1538R(const utype *inParam,TCtrlInfo *errInfo);
//utype* cIUserForumRelInfo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIUserForumRelInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
//utype* cUStatusOfUserForumInfo(const utype * inParam,TCtrlInfo *errInfo);
//utype* p1539T(const utype *inParam,TCtrlInfo *errInfo);
//utype* cQUserForumByApproveAccept(const utype * inParam,TCtrlInfo *errInfo);
//utype* cDUserForumInfo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cDUserForumRelInfo(const utype * inParam,TCtrlInfo *errInfo);
//utype* cIUserForumInfoHisBakByApproveAccept(const utype * inParam,TCtrlInfo *errInfo);
//utype* p1540D(const utype *inParam,TCtrlInfo *errInfo);

utype* pOpenMdlCellDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpenMdlLineDeal(const utype *puInParam, TCtrlInfo *ptCtrlInfo);


////#########################wangqiana###################################
utype* pQurspecialwq(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cQgCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pQguoCustInfoByCustID(const utype *inParam, TCtrlInfo *ptCtrlInfo);

#endif

