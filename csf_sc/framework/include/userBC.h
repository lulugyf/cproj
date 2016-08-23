#ifndef _USER_BC_H_
#define _USER_BC_H_

utype* cGetUsrMasterRunInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDateOfUserTeamMbrByTmId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBrandRelByIdAndExpDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateInfoOfUserBrandRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUseBrandRelHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cURunOfCrmToBossStateInfoCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserRelHisBakExpDate(const utype * inParam,TCtrlInfo *errInfo);
utype * cQUserImsiInfoByImsiNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserByGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype * cIRecgarageSMSTemp(const utype * inParam,TCtrlInfo *errInfo);
utype * cIRecgarageSMSInfo(const utype * inParam,TCtrlInfo *errInfo);
utype * cQScoreUseByCreateDateWrt(const utype * inParam,TCtrlInfo *errInfo);
utype * cQUsrGrpMbrHisByom(const utype * inParam,TCtrlInfo *errInfo);
utype * cQUsrGrpByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype * cIScoreUseOptAcptRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype * cIScoreUseBakByOpTimeLoginWrtoff(const utype * inParam,TCtrlInfo *errInfo);
utype * cUWrtoffOfScoreUseByLoginWrt(const utype * inParam,TCtrlInfo *errInfo);
utype * cIScoreUseStatTemp(const utype *inParam, TCtrlInfo *errInfo);
utype * cQScoreUseStatTempGroupBy(const utype *inParam, TCtrlInfo *errInfo);
utype * cIScoreUseBakByOpTimeGiftLoginWrtoff(const utype *inParam, TCtrlInfo *errInfo);
utype * cQScoreUseRdByQryCond(const utype *inParam, TCtrlInfo *errInfo);
utype * cUScoreUseInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQScoreUseRdByTimeFlagLogin(const utype *inParam, TCtrlInfo *errInfo);
utype * cQServiceNoInfoByMasterNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUStandOfAcStopDelayUser(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCntOfUseRuleByBrandGiftId(const utype *inParam, TCtrlInfo *errInfo);
utype * cUValidFlagOfUseRuleDict(const utype *inParam, TCtrlInfo *errInfo);
utype * cGetUseRuleDictByCond(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUseRuleDict(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUseRuleDictHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cUUseRuleDictByRuleId(const utype *inParam, TCtrlInfo *errInfo);
utype * cQMaxIdOfUseRuleDict(const utype *inParam, TCtrlInfo *errInfo);
utype * cIScoreruleAuditRd(const utype *inParam, TCtrlInfo *errInfo);
utype * cQMaxIdOfAuditRd(const utype *inParam, TCtrlInfo *errInfo);
utype * cGetUsrListPageInfoByCustId(const utype *inParam, TCtrlInfo *errInfo);
utype * cQStopDelayUserByEndTimeDelayType(const utype *inParam, TCtrlInfo *errInfo);
utype * cQStopDelayUserByIdNoDelayType(const utype *inParam, TCtrlInfo *errInfo);
utype * cDStopDelayUserByIdNoDelayType(const utype *inParam, TCtrlInfo *errInfo);
utype * cQStopDelayUserByEndTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cIStopDelayUser(const utype *inParam, TCtrlInfo *errInfo);
utype * cIStopDelayUserHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIStopDelayUserHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cIScoreUseHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCrmToBossStateHisByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserBusiExpireRdByExpTimeType(const utype *inParam, TCtrlInfo *errInfo);
utype * cIChgScoreInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIChgScoreInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIChgScoreListInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIChgScoreListInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserStateInfoHisByExpDate(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserExtInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserExtInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserStateInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserStateInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserInnetInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserInnetInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIServAddNumInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIServAddNumInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cQServAddNumInfoHisByUpdate(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserServLocInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserServLocInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserBillModeInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserBillModeInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserExpireInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserExpireInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserAddInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserAddInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserContactInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserContactInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserResInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserResInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserSimInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserSimInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cICustUserRel(const utype *inParam, TCtrlInfo *errInfo);
utype * cICustUserRelHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserRel(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserRelHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cURunCodeOfUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishFlagOfUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUExpDateOfUserStateInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserBillModeInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserExpireInfoByIdNo (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserInfoHisByUpdate (const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserStateInfoHisBak (const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserDeadInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserExtInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserExtDeadInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserExtInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserAddInfoHisBakByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserAddDeadInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserAddInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserStateInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserInnetInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserInnetInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserBillModeInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserBillModeInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserExpireInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserExpireInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserServLocInfoHisBak (const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserServLocInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserContactInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserContactInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserCreditInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserCreditInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserCreditInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserCreditRecHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserCreditRec(const utype *inParam, TCtrlInfo *errInfo);
utype * cISubscriberAttrInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDSubscriberAttrInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cISpecialListInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDSpecialListInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserValueInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserValueInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIPasswdResetInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDPasswdResetInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cICustUserRelHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDCustUserRel(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserRelHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserGroupByGroupName(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserRel(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserSimInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserSimInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserResInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserResInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIServAddNumInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDServAddNumInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserModifiedInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserModifiedInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserDeadInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserExtDeadInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserAddDeadInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserDeadInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserExtDeadInfo (const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserAddDeadInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserDeadInfoByPhone(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserRelByMasterId(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserRelBySlaveId(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserSimInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUSimNoOfUserSimInfo (const utype *inParam, TCtrlInfo *errInfo);
utype * cUOpInfoOfUserSimInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishFlagOfUserSimInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserImsiInfoHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype * cUExpDateOfUserImsiInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserImsiInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserInfoByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserInfoByCustId (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserBrandRelByIdNo (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserExpireInfoByIdTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCntOfUserExpireInfoByIdType(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCntOfUserExpireInfoByIdTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserExpireInfoByIdType(const utype *inParam, TCtrlInfo *errInfo);
utype * cUExpireTimeOfUserExpireInfo (const utype *inParam, TCtrlInfo *errInfo);
utype * cUBeginTimeOfUserExpireInfo  (const utype *inParam, TCtrlInfo *errInfo);
utype * cUOpInfoOfUserExpireInfo (const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishFlagOfUserExpireInfo (const utype *inParam, TCtrlInfo *errInfo);
utype * cUOpInfoOfUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishFlagOfUserStateInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFieldValueOfUserAddInfo (const utype *inParam, TCtrlInfo *errInfo);
utype * cUOpInfoOfUserAddInfo (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserBrandRelByIdTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserInnetInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cULimitOweOfUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUUserPwdInfoOfUserInfo (const utype *inParam, TCtrlInfo *errInfo);
utype * cUCustIdOfUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQSpecialListInfoByIdType(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserExpireRec(const utype *inParam, TCtrlInfo *errInfo);
utype * cUOwedStopFlagOfUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCntOfPasswdResetByIdTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cQPasswdResetByIdTime(const utype *inParam, TCtrlInfo *errInfo);
utype * cIPasswdResetInfoHis (const utype *inParam, TCtrlInfo *errInfo);
utype * cIPasswdResetInfo (const utype *inParam, TCtrlInfo *errInfo);
utype * cUResetInfoOfPasswdReset(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserExtInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUQueryCdrFlagOfUserExtInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUAdjustTypeOfUserExtInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUOpInfoOfSpecialListInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserAddInfoByFieldCode(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserImsiInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserCreditInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQGroupRoleAttrByRole (const utype *inParam, TCtrlInfo *errInfo);
utype * cQGroupRoleAttrByRoleAttr(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCntOfGroupRoleAttrByRoleAttr(const utype *inParam, TCtrlInfo *errInfo);
utype * cQGroupRoleById  (const utype *inParam, TCtrlInfo *errInfo);
utype * cQGroupRoleByType(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserGroupById  (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserGroupByGroupId  (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserGroupByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserGroupMbrByGrpId(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserGroupMbrByMbrId  (const utype *inParam, TCtrlInfo *errInfo);
utype * cQAllUserGroupMbrByMemName  (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserGroupMbrByObjType(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserGroupMbrByGroupObjType(const utype * inParam,TCtrlInfo *errInfo);
utype * cQGroupMbrAttrByObjId(const utype *inParam, TCtrlInfo *errInfo);
utype * cQGroupMbrAttrByObjAttr (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserTeamById  (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserTeamByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserTeamMbrByTeamId(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserTeamMbrByObjId (const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserGroup(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserGroupHis (const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserGroupAttr(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserGroupAttrHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserGroupMbr    (const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserGroupMbrHis (const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserGroupMbrAttr(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserGroupMbrAttrHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserTeam(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserTeamByIdType(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserTeamHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserTeamMbr(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserTeamMbrHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cQResFreeTimesInfoByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFreeTimesOfResFreeTimesInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserSimInfoBySimNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserAddInfoHisBakByFieldCode (const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserAddInfoByFieldCode  (const utype *inParam, TCtrlInfo *errInfo);
utype * cQSpecialListInfoByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCntOfSpecialListInfoByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserInfoBySectionNo (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserTeamByIdNoType  (const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserInfoByContractNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUTypeOfUserExtInfoByType(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCntOfBlackListPhoneInfoByPhoneNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUOpInfoOfPasswdResetInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cISpecialListInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cISpecialListInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUOpInfoOfPasswdResetInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserSimBySimNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCntOfUserInfoByCustId(const utype *inParam, TCtrlInfo *errInfo);
utype * cDSpecialListInfoByIdType(const utype *inParam, TCtrlInfo *errInfo);
utype * cQUserExpireRecByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUExpInfoOfUserRel(const utype *inParam, TCtrlInfo *errInfo);
utype * cUEffInfoOfUserRel(const utype *inParam, TCtrlInfo *errInfo);
utype * cQCntOfUserRelByIdRelCode(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserRelHisBakByIdRelCode(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserCreditInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cISubscriberAttrInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cISubscriberAttrInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUOpInfoOfUserExtInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cIUserAddInfoHisBakByFieldCode(const utype *inParam, TCtrlInfo *errInfo);
utype * cDUserExpireRecByIdNo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishOfUserInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishOfUserInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishOfUserStateInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishOfUserStateInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishOfUserBillModeInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishOfUserBillModeInfo(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishOfUserExpireHis(const utype *inParam, TCtrlInfo *errInfo);
utype * cUFinishOfUserExpire(const utype *inParam, TCtrlInfo *errInfo);

utype* cIUserGroupHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserGroupByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStateOfUserGroupMbrByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserGroupAttrHisBakByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserGroupAttrByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserGroupMbrHisBakByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserGroupMbrHisBakByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStateOfUserGroupMbrByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserGroupMbrAttrHisBakByMbrId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserGroupMbrAttrByMbrId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserTeamHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserTeamByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserTeamMbrByTmId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserTeamMbrHisBakByTmId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserTeamMbrHisBakByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserTeamMbrByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAllUserTeamMbrByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMbrQryLmtByGrpIdAndMemID(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserGroupMbrByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserGroupMbrByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSIInfoByName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSIInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustUserByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustUserRelHisBakById(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustUserRelById(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserRelByIdCode(const utype * inParam,TCtrlInfo *errInfo);

utype * cUExpDateOfSpecialInfoList(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* cIUserGroupHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserGroupAttrHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserGroupMbrHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserGroupMbrAttrHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserTeamHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserTeamMbrHisBakByTmId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserTeamMbrHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStateOfUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGroupDescOfUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cULockFlagOfUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAttrValueOfUserGroupAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserGroupAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStateOfUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cULockFlagOfUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUMbrDescOfUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUMbrRoleOfUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAttrValueOfUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStateOfUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTeamNameOfUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStateOfUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUMbrRoleOfUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);
utype * cUExpDateOfSpecialInfoList(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cDUserGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserGroupAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrAttrByMbrId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupAttrByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGarageSMSByGroupIdDay(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGarageSMSByGroupIdMonth(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByMasCustId(const utype * inParam,TCtrlInfo *errInfo);
utype * cUFieldOtherValueOfUserAddInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUOtherValueOfUserAddInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQBadSMSDetailByDisposeNumTime(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIUserFreetimesHisBak(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUMbrDescOfUserTeamMbr(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQUserImsiInfoByPhoneNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIUserStateInfoHisBakByIdExp(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUFinishRunCodeOfUserInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUFinishRunCodeOfUserInfoHis(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUFinishRunCodeOfUserState(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUFinishRunCodeOfUserStateHis(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIUserBrandRel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQUserGroupMbrByGroupObjId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cQUnExpUserGroupMbrByGroupObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserBrandRelByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDKZQQTUser(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetKZQQTUserByMulCon(const utype * inParam,TCtrlInfo *errInfo);
utype* cDKZSZXUser(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetKZSZXUserByMulCon(const utype * inParam,TCtrlInfo *errInfo);
utype* cQYZQQTUserByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetYZQQTUserByMulCon(const utype * inParam,TCtrlInfo *errInfo);
utype* cIYZQQTUser(const utype * inParam,TCtrlInfo *errInfo);
utype* cDYZQQTUserByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByResNoBack(const utype* inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByIdNoBack(const utype* inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByIdType(const utype* inParam,TCtrlInfo *errInfo);
utype* cIResSellRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResSellRdExt(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByResId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByResType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByReceiveFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByResNoTypeFlagLogAcpt(const utype * inParam,TCtrlInfo *errInfo);
/*有价卡换卡新旧卡对应信息表*/
utype* cIResChgRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBakFlagOfResChgRdByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);

utype* cUBackFlagOfResSellRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetSendFlagByCurTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBrandRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIApproveRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginAcceptTime(const utype * inParam,TCtrlInfo *errInfo);

utype* cDResFreeTimesInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResFreeTimesInfoHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGarageSMSInfoHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGarageSMSInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBadSMSDetailHisYYYYMMBakByDisposedNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cDBadSMSDetailYYYYMMByDisposedNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserExpireRecHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBrandRelByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBrandRelHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserImsiInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserImsiInfoHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUApproveRdByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUShortNumOfUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUShortNumOfUserTeamMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrAttrByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserTeamMbrByMbrId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrAttrByMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserDeadInfoByMasPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrByObJId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByMasPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserDeadInfoByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQResSellRdByTimeFlag(const utype * inParam, TCtrlInfo *errInfo);
utype* cUExpInfoOfUserBillModeInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCntOfChgScoreByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIExtRuleValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cIExtRuleValueHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreUse(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreUseHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfScoreUseByIdWrtoff(const utype * inParam,TCtrlInfo *errInfo);
utype* cCntUserAddByFieldIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgScrByScrTypeIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreTransHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDScoreTransByFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreTransHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreTrans(const utype * inParam,TCtrlInfo *errInfo);
utype* cUScoreTransByFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreTransByFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreTransHisBakByFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustUserRelByCustIdCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpChgScoreListInfoByIdBill(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCurScoreOfGrpChgScoreListInfoByIdBillType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpChgScoreListInfoByIdBillOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpChgScoreListInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCurAdjOfGrpChgScoreListInfoByIdTypeBill(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCurUseOfGrpChgScoreListInfoByIdBill(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpChgScoreInfoByIdYear(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCurScoreOfGrpChgScoreInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCurScoreOfGrpChgScoreInfoByIdType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpChgScoreInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCurAdjGrpChgScoreInfoByIdTypeYear(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCurUseGrpChgScoreInfoByIdTypeYear(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpChgScoreInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpScrUseApproveRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpScrUseApproveRecByIdAudre(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpScrUseApproveRecByIdAudre(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAudreOfGrpScrUseApproveRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpScoreUseRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpExtRuleValueInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpChgScoreListInfoByIdBillType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpChgScoreInfoByIdType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgScoreByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQValueScoreByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetScoreListType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGetExtruleUseScrRuletyperltScrParam(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExtRuleValueByPhoneIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserSimByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUseLimitCfgDictByBrandId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfScoreParamByTypeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUseScoreParamUseRuleBrandDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExtRuleValueByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgUserByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgScoreListByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBrandRelHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpInfoOfUserBrandRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBrandRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBillModeInfoHisBakByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBillModeInfoByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cIConUserInfoHisBakByUniKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpInfoOfUserBillModeInfoByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExtRuleValueByLoginNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginQryRdByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetScrExtValueByPhoneLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpChgScoreListInfoByIdBillBetween(const utype * inParam,TCtrlInfo *errInfo);

utype* cIChgUserInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChgUserInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgUserInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDChgUserInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCoShopPosInfoByPosId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCurScoreOfCoShopInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreUseOptAcptRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfScoreUseRdByWrtoffFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChgScrListOfInitScrByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChgScrListOfAdjScrByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChgScrListOfUseScrByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChgScrListOfAdjScrByIdNoAdjScr(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChgScrListOfCurScrByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSeqOfResSellRdBySellSerialNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFinishOfUserExpireD(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreMngCheceByResCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUseRuleHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUseRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreMngCheckRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cDScoreMngCheckeRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUseRuleByGiftId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByVipCardNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUfirstUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFirstUseDateOfUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreMngCheckeByResCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cICoShopInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCoShopInfoByCoShopID(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCoShopInfoByCoShopID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCoShopInfoByCoShopName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCoShopInfoByCoShopId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICoShopInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICoShopInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCoShopPosByPosName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCoShopPosByPosId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICoShopPosInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCoShopPosInfoByPosId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCoShopPosInfoByPosId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICoShopPosInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByMeanId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupRoleByMbrIdType(const utype * inParam,TCtrlInfo *errInfo);
utype* cICoShopPosInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMaxIdOfUserExpireRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUseRuleDictByUseRuleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByCustIdRowNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cUReceiveFlagOfResSellRdByLoginAccept(const utype* inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByLoginAccept(const utype* inParam,TCtrlInfo *errInfo);
utype* cUBackFlagOfResSellRdByLoginAccept(const utype* inParam,TCtrlInfo *errInfo);
utype* cGetAcctHappyNodRecByIdNoPayType(const utype* inParam,TCtrlInfo *errInfo);
utype* cUFinishOfUserExpireE(const utype* inParam,TCtrlInfo *errInfo);
utype* cQScoreUseByLoginNoTime(const utype* inParam,TCtrlInfo *errInfo);
utype* cQScoreUseOptAcptByPosAccept(const utype* inParam,TCtrlInfo *errInfo);
utype* cQScoreUseByLoginAccept(const utype* inParam,TCtrlInfo *errInfo);
utype* cQScoreUseRdByLoginAccept(const utype* inParam,TCtrlInfo *errInfo);
utype* cQAcctHappyNodByIdNo(const utype* inParam,TCtrlInfo *errInfo);
utype* cQBusiLimitByIdNoLimFlag(const utype* inParam,TCtrlInfo *errInfo);
utype* cQAcctHappyNodByIdNo(const utype* inParam,TCtrlInfo *errInfo);
utype* cDBusiLimitByIdNoLimFlagFunCode (const utype* inParam,TCtrlInfo *errInfo);
utype* cIBusiLimit(const utype* inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByOwedStopGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoByMulCon01(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreUseRdByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetScoreUseOptAcptByPosId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResFreeTimeInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserImsiInfoHisBakByAccept(const utype *inParam, TCtrlInfo *errInfo);
utype* cQScoreParamByParamTypeDetail(const utype *inParam, TCtrlInfo *errInfo);
utype* cUBrandIdOfChgUser(const utype *inParam, TCtrlInfo *errInfo);
utype* cQBrandChgRuleByBrandId(const utype *inParam, TCtrlInfo *errInfo);
utype* cQUserGroupMbrByShortNum(const utype *inParam, TCtrlInfo *errInfo);
utype* cIUserBusiLimitHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype* cDUserBusiLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* cIUserBusiLimitHis(const utype *inParam, TCtrlInfo *errInfo);
utype* cIUserBusiLimit(const utype *inParam, TCtrlInfo *errInfo);
utype* cQSIBlackListBySINO(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserResInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserRelMasterSlave(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserTeamMbrByTeamObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoByTypePage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfSpecialListInfoByType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpScrUseApproveRecByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cISpanRegTransRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cISpanRegTransRdHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIMobStuffInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIMobStuffInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDMobStuffInfoByPh(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMobStuffInfoByPh(const utype * inParam,TCtrlInfo *errInfo);
utype* cIMobStuffInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoByTypePhoneLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfSpecialListInfoByTypePhoneLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTobSongBoxResultInfoByOpAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cITobSongBoxInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMuniciPalGovLettByLettersn(const utype * inParam,TCtrlInfo *errInfo);
utype* cIMuniciPalGovLett(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMuniciPalGovLettByQueryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserBusiLimit(const utype * inParam,TCtrlInfo *errInfo);
utype* cISiBlackListHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cISiBlackList(const utype * inParam,TCtrlInfo *errInfo);
utype* cISiBlackListHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDSiBlackList(const utype * inParam,TCtrlInfo *errInfo);
utype* cDSpanRegTransRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSiBlackListBySvcNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserServLocByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserServLocByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cIYZQQTUserHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIYZQQTUserHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDBlackList(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBlackList(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBlackListHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBlackListHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBlackListBySvcNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfBlackListByBlackNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreCashRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCurScoreOfCoShopInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserSimHisByUpdate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUseRuleByGiftBrandId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreParamDictByTypeNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cISpanRegTransRdHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAcctHappyNodByIdNoAcctType(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAcctHappyNodRecRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCurNodOfAcctHappyNod(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserSvcAttrByMainSvc(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserAttrCtrlById(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetScrExtValueByOutPhoneLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCallNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCallNumByCallNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cICallNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCallNumBySvcNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDeptmentBySvcNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cICallNumHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cICallNumHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupByGroupType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGrpByGroupType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCoShopPosByCoShopId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServRuleBySvcNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfServRuleByServRuleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cDServRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServRuleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServRuleHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfRouteRuleBySvcNumAndServRuleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRouteRuleBySvcNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRouteRuleBySvcNumAndRuleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRouteRuleBySvcNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRouteRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRouteRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfRouteRuleByRuleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRouteRuleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRouteRuleHisBak(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfUserRelBySlaveId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByMasPhoneLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserAddInfoByFieldCodeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserAddInfoByIdFieldCodeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMuniciPalGovLettOfTitle(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustUserRelByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginOprByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSellCardInfoHisByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSellCardInfoHisByGroupIdTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSellCardInfoByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cISellCardInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cISellCardDetailHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSellCardInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSellCardDetail(const utype * inParam,TCtrlInfo *errInfo);
utype* cISellCardInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cISellCardDetail(const utype * inParam,TCtrlInfo *errInfo);
utype* cDSellCardInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDSellCardDetailInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSIInfoByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpgradeDetail(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpgradeDetailByOpLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpgradeTotal(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfOpgradeTotalByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpgradeTotalByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfOpgradeTotal(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiLimitByRuleLvl(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBusiLimitHisBakByRuleLvl(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUserBusiLimitByRuleLvl(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBusiLimitByRuleLvl(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserAddDeadInfoHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserDeadInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserExtDeadInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUsrOrderInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreTypeByScoreType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSellCardHisByAll(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserStateInfoHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICardMulitNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCardMulitNumHisByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfChgScoreByIdNoType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfChgScoreByIdNoTypeYear(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfChgScoreByIdNoYear(const utype * inParam,TCtrlInfo *errInfo);
utype* cICrmToBossStateInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCrmRunOfCrmToBossStateInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBossRunOfCrmToBossStateInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCrmToBossStateInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICrmToBossStateInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICrmToBossStateInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpgradeDetailHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpgradeTotalHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFinishStateOfUserStateInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSumCurOfGrpChgScoreListInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQFavorableUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnfavorableUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFavorableUserInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnfavorableUserInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFavorableUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFavorablePlanByFaPlanID(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUnfavorableUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFavorablePlan(const utype * inParam,TCtrlInfo *errInfo);
utype* cISelWorkInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cISelWorkInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCrmToBossStateInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfUSerBrandRelByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cIWappushInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserExpireRecHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreOutBossAcceptRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreOutBossAcceptByOutAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMobStuffInfoByRegionId(const utype * inParam,TCtrlInfo *errInfo);

utype* cISmpCardModInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrByGrpIdShortNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserTeamMbrByRow(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserTeamMbrById(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBusiExpireRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiExpireRdByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBusiExpireRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGarageSMSInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServAddNumInfoByAddServiceNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cIGrpScoreUseRdHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserExpire(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserExpire(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpExtRuleValueInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserInfoByCust(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUnEffUserBrandRelByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUnEffUserBillModeByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServAddNumInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInterfaceDataSyn(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByPhoneNum(const utype * inParam,TCtrlInfo *errInfo);

utype* cQScoreUseByGiftidTimeBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceNoInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceNoInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreUseByGiftidTimeBakLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserFamilyGroupMbrByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDServiceNoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceNoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServiceNoInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUServAddNumInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUServiceNoInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserTeamMbrByTeamIdA(const utype * inParam,TCtrlInfo *errInfo);
utype* cUIdNoCol01OfServAddNumInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDServAddNumInfoByIdNoCol01(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServAddNumInfoHisBakByIdNoCol01(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServiceNoInfoByIdNoCol01(const utype * inParam,TCtrlInfo *errInfo);
utype* cDServiceNoInfoByIDNoCol01(const utype * inParam,TCtrlInfo *errInfo);
utype* cUIdNoCol01OfServiceNoInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserDeadInfoByCustIdRow(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByRunCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserDeadInfoByCustIdPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBrandCreateTypeOfUserExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cULimitOweOfUserCreditInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSellCardInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSellCardDetailHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cULoginAcceptOfUserBusiLimit(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiLimit(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServAddNumInfoByIDType(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateFinishFlagOfUserExpireInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnExpUserTeamMbrByTeamObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserCreditInfo2(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserCreditInfoHis2(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetUserCntByIdIccid(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserDeadInfoByIccidPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfDeptment(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDeptment(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDeptmentHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDeptmentHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDDeptment(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupByIdNoGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cICheckPasswdRecInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStateOfCheckPasswdRecInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCheckPasswdRecInfoByPhoneNoAndStateTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserCreditInfoByUserType(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserCreditInfoHisBakByUserType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMaxUserCreditByIdNoAndLmtOweType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByCodeMasterOpenTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginMsgByLoginNoFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStateOfCheckPasswdRecInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cUStateOfCheckPasswdRecInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTimesOfCheckPasswByPhoneNoOut(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTimesOfCheckPasswByPhoneNoIn(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTimesOfCheckPasswByPhoneNoOut(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTimesOfCheckPasswdRecInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICheckPasswdrec(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTimesOfCheckPasswdRecInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCheckPasswDrecByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCheckPasswDrec(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCheckPasswdrecByLoginPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMaxUserCreditByIdNoAndLmtOweType(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTimesOfCheckPasswByPhoneNoIn(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserGrpMbrByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLastUserGroupByIdNoGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLastUserGroupMbrByObJId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrByObJIdRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupByGrpIdGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAllUserGroupMbrByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserImsiInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserGroupMbrByGrpIdAndRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGoodLuckInfoByIdEff(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGoodLuckUseRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGoodLuckInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGoodLuckUseRdHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCurNodOfGoodLuckInfoByIdEff(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetUserSimById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLastUserDeadInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserInfoByPhoneMasTest(const utype * inParam,TCtrlInfo *errInfo);
utype* cISelWorkInfo01(const utype * inParam,TCtrlInfo *errInfo);
utype* cISelWorkInfoHis01(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBroadBand(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBroadBandHis(const utype * inParam,TCtrlInfo *errInfo);


utype* cQColorMsgSendbyPhoneNoandLatestTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDayCntOfColorMsgSendbyLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMinCntOfColorMsgSendbyLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrHisByMbrId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIColorMsgSend(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserResOrdByTypeNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserResOrdByTypeNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserResOrdByTypeNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserResOrd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserResOrdHisBakByTypeNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiLimitByIdnoProdIdPrcId(const utype * inParam,TCtrlInfo *errInfo);
utype* cCntOfUnExpMbrOfGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserServLocByAddressId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupByIdNoAndType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserMsgByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetHomeUserFavListByCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetMainRoleByBind(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfHomeUserFavByQryCond(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserInfoByMasRunTimePhoneLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cISpecialListInfoHisBakByIdType(const utype * inParam,TCtrlInfo *errInfo);

utype* cQAcceptOfUserResOrdBySvcNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserResOrdByAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserResOrdByAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserResOrdHisBakByAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetMainRoleByFamily(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserResInfoByIdNoResType(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEquipmentNoOfUserresInfoByIdNoResType(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserResInfoHisBakByResType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnExpUserGroupMbrByObJId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserSimInfoByImsiNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNeedCancleUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSimByGroupAndDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByTypeAndDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByTypeAndNoDa(const utype * inParam,TCtrlInfo *errInfo);

utype* cIHomeUserFavInfo(const utype * inParam,TCtrlInfo *errInfo);
int getValueByIndex(char *S, int I, char CH, char *RET);
utype* cIHomeUserFavInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBusiLimitHisBak2(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBusiLimitByDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrByGroupObjType(const utype * inParam,TCtrlInfo *errInfo);
utype* wzx(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetUserGroupMbrInfoByCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpenUserInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfSiBlackWhiteBySiNoSvcNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSiBlackListBySiNoSvcNum(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetMarketGoodLuckByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetMarketGoodLuckByGroupLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetResGoodLuckByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetResGoodLuckByGroupLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cGRegIdOfUserAndChngrpByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfChgScoreByIdNoTypeBeforeYear(const utype * inParam,TCtrlInfo *errInfo);
/*dailf*/
utype* cDSellCardDetailInfoByloginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSellCardDetailInfoByloginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cISellCardDetailHisByBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSellCardDetailInfoByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBusiLimitNew(const utype * inParam,TCtrlInfo *errInfo);
//新版积分查询
utype* cGetSumUseScoreByIdNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetSumCurScorebyIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetSumInitScoreByIdNoBillCycleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThreeMonth(const utype * inParam,TCtrlInfo *errInfo);
utype* cQHomeUserFavInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDHomeUserFavInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);

/* 集团需求，积分商城省CRM兑换 */
utype* cQOutOrderInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOutOrderInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOutOrderInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOutOrderInfoByCreateAccept(const utype * inParam,TCtrlInfo *errInfo);

/* 终端IMEI变更 */
utype* cIChgIMEI(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgIMEIBySellAcc(const utype * inParam,TCtrlInfo *errInfo);
utype* cUNewImeiOfChgIMEIInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgIMEIHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgIMEIHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfRecGarageSmsInfoBySendPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGetRecGarageSmsInfoBySendPhone(const utype * inParam,TCtrlInfo *errInfo);

/*白名单历史查询*/
utype* cQSpecialListInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cISpecialListInfoHis1(const utype * inParam,TCtrlInfo *errInfo);
utype* cISpecialListInfo1(const utype * inParam,TCtrlInfo *errInfo);
utype* cISpecialListInfoHisBakByIdType1(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoWhite(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustLevelOfSpecialListInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoByTypePage1(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoByIdType1(const utype * inParam,TCtrlInfo *errInfo);

/*两城一家*/
utype* cITwoCitySendInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTwoCitySendInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDTwoCitySendInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cITwoCitySendInfoBak(const utype * inParam,TCtrlInfo *errInfo);

/*积分兑换资费产品退订冲正*/
utype* cQExtRuleValueInfoByLoginApt(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServAddNumInfoByServiceMaster(const utype * inParam,TCtrlInfo *errInfo);
utype* cCntOfUserByIccidBillmode(const utype * inParam,TCtrlInfo *errInfo);

utype* cQSerAddNumInfoByAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSerAddNumInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSerAddNumInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

/*铁通融合移机修改局向*/
utype* cUBureauIOfUserServLocInfoByIdNO(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExchRoomAndExchOfUserServLocByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUMasterPhoneOfUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSlavePhoneOfUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgPhoneNoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDChgPhoneNoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgPhoneNoHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgPhoneNoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgPhoneNoHisBakByIdNoAndExpDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cDChgPhoneNoByIdNoAndExpDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceNoHisBakByIDType(const utype * inParam,TCtrlInfo *errInfo);
//铁通融合绑定上网账户校验
utype* cQUserServLocInfoById(const utype * inParam,TCtrlInfo *errInfo);
//铁通用户判断
utype* cQCntOfUserByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUpdatTypeOfUserGroupMbrByObJId(const utype * inParam,TCtrlInfo *errInfo);
//铁通黑名单改造

utype* cQCntOfBlackUserInfoByIccidAndMaster(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBlackListPhoneInfoByBlackNoAndMasterRow(const utype * inParam,TCtrlInfo *errInfo);
/*修改积分用户信息表*/
utype* cUChgUserInfoDealFlagByIdNo(const utype * inParam,TCtrlInfo *errInfo);
/*gejun*/
utype* cIUserPreDestroyHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPreDestroyHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserPreDestroyByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPreDestroy(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserPreDestroyByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPreDestroyFee(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPreDestroyFeeHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPreDestroyFee(const utype * inParam,TCtrlInfo *errInfo);
utype* cDDestroyTransFeeByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDesTransFeeByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDestroyTransFeeBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByMasGroupLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cURemarkOfApproveRdByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQApproveRdByIdNoAndCurTime(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetCntOfUserGroupMbrInfoByGroupTypePage(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUserGroupMbrInfoByGroupTypePage(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStopFlagOfUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCheckPasswdRecInfoByPhoneNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByRunTime(const utype * inParam,TCtrlInfo *errInfo);

utype* cQScoreParamByIndex(const utype * inParam,TCtrlInfo *errInfo);

utype* cIDestroyTransFeeBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDDestroyTransFeeByIdNo(const utype * inParam,TCtrlInfo *errInfo);

//=============CSS 山西 begin=============================
utype* cQUserBakSimHisByUpdateIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBakSimInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBakSimInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBakSimInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBakSimInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBakSimInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBakSimInfoBySimIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBakSimInfoByLoginAcceptIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQTerminalServiceByIdImeiStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cITerminalServiceInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cITerminalServiceInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserGradeCodeOfUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScfgByBrand(const utype * inParam,TCtrlInfo *errInfo);

utype* cQScoreParamByDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUseRuleByType(const utype * inParam,TCtrlInfo *errInfo);
utype* cIoutorderinfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
/* 积分兑换撤单 */
utype* cIScoreUseHisByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cDScoreUseByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBrandRelByIdEffDate(const utype * inParam,TCtrlInfo *errInfo);

utype* cQResSellRdByResNoLike(const utype * inParam,TCtrlInfo *errInfo);
/*批量销户申请时间大于3个月*/
utype* cQUserInfoByRunTime(const utype * inParam,TCtrlInfo *errInfo);

utype* cQScoreParamByIndex(const utype * inParam,TCtrlInfo *errInfo);
utype* cQInLoginOpByCols(const utype * inParam,TCtrlInfo *errInfo);
/*补充*/
//utype* cGetUsrMasterRunInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype * cQUserGroupMbrByObjType(const utype *inParam, TCtrlInfo *errInfo);
utype* cQOpenUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSerAddNumInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUpdatTypeOfUserGroupMbrByObJId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfBlackUserInfoByIccidAndMaster(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBlackListPhoneInfoByBlackNoAndMasterRow(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPreDestroyFee(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreParamByIndex(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDestroyTransFeeBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDDestroyTransFeeByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBrandRelByIdEffDate(const utype * inParam,TCtrlInfo *errInfo);

utype* cQBillDayInfoByID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBillDayInfoByMasPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserDayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserdayInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBillDayInfoByContractNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBillDayInfoByContractNoAndEffDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBillDayInfoByID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBillDayInfoByMasPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNowBillDayInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBillDayByContractNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserAssureByAssureNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInnetInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
/**tiansqa**/

utype* cIuserDayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserDayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserdayInfoHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cDUserBillDayDeadInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBillDayDeadInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBillDayDeadInfoByContractNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBillDayDeadHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserDayDeadInfoHis(const utype * inParam,TCtrlInfo *errInfo);
/*tiansqa end*/


utype* cQSerAddNumInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserExtInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserPrcByIdNoB(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSalesRdByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiLimitByIdNoA(const utype * inParam,TCtrlInfo *errInfo);

//家庭宽带产品信控停机管理
utype* cQServiceNoHisByServiceType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreParamByIndex(const utype * inParam,TCtrlInfo *errInfo);

utype* cQInLoginOpByCols(const utype * inParam,TCtrlInfo *errInfo);

/*欠费销户 yangzg*/
utype* cQUserGrpByIdNoGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGrpMbrByObjIdRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGrpByGrpIdGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLastUserGrpByIdNoGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLastUserGrpMbrByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupByIdNoCodeClass(const utype * inParam,TCtrlInfo *errInfo);

utype* cIUserfavInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserfavInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGoodsActInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGoodsActInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGoodsActInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGoodsActInfoByPhoneNO(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGoodsActInfoByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGoodsActDictByGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGoodsActDictByGroupAct(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGoodsActInfoByActCodeNumLevelLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGoodsActInfoByActCodeNumLevelLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGoodsActInfoByPhoneNoCodeNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGoodsActInfoByActCodeNumRowNumLevelLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGoodsActInfoHisBakByPhoneNoLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGoodsActInfoByPhoneNoLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGoodsActInfoByPhoneNoLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGoodsActInfoByPhoneNoLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
/*G3OP增加小区 wangzxa*/
utype* cQAddRoadMidByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAddRoadMidByLoginNoDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAddRoadMid(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAddRoadMidHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDAddRoadMidByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAddRoadMidByLogin(const utype * inParam,TCtrlInfo *errInfo);

/*满意度*/
utype* cQUserPlaceByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPlace(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPlaceHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPlaceHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserPlaceByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpMbrByOpTime(const utype * inParam,TCtrlInfo *errInfo);
/*免填单营销服务信息输入*/
utype* cICheckDetailInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCommonCheckRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cICommonCheckRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cICheckDetailInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICheckDetailInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cICheckDetailInfoHisBakByApplyAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceAdvtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceAdvtInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceAdvtInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServiceAdvtInfoByLoginNoAdvtDescLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCheckDetailInfoByApplyId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUServiceAdvtInfoByAdvtId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServiceAdvtInfoByAdvtId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCheckDetailInfoByApplyId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDServiceAdvtInfoByAdvtId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDServiceGrpInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceGrpInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServiceGrpInfoByGrpName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServiceGrpInfoByIdNoGrpNameLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cUIdNoOfServiceGrpInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceGrpInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIServiceGrpInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpAdvtRelInfoByAdvtId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpAdvtRelInfoByObjGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpAdvtRelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpAdvtRelInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpAdvtRelInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServiceGrpInfoByObjGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpAdvtRelInfoByObjGrpIdAndAdvtId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpAdvtRelInfoByObjGrpIdAndAdvtId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpAdvtRelInfoByGrpIdAdvtIdGrpTypeLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByValueGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCheckDetailInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByValueGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByValueAndBeginGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByBeginGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfPrintadvtRdYYYYMM(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServiceGrpInfoByIdNoObjType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCheckDetailInfoByApplyIdStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpAdvtRelInfoByObjGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpAdvtRelInfoHisBakByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPrintAdvtRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPrintadvtRdByIdNoAndAdvtId(const utype * inParam,TCtrlInfo *errInfo);
/*开户入用户品牌关系表bug修改	wangzxa*/

utype* cQSumScoreUseByAccept(const utype * inParam,TCtrlInfo *errInfo);

utype* cQParBrandByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSumScoreParamByTypeValue(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserTeamMbrByObjId1(const utype * inParam,TCtrlInfo *errInfo);

//=============CSS 山西 end=============================
/*---------------------------测试卡------------------begin*/
utype* cIFreePhoneApplyHisAll(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFreePhoneApplyHisById(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFreePhoneApply(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFreePhoneApply(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFreePhoneApply(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFreePhoneApplyByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFreePhonePoolHisAll(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFreePhonePool(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFreePhonePool(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFreePhonePool(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFreePhonePoolHisById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFreePhonePoolByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFreePhonePoolByVaildFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFreePhoneVaildFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTestTypeByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQValidTestType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTestTypeByPK(const utype * inParam,TCtrlInfo *errInfo);
/*------------------------------测试卡------------end*/
/*------------------------------个性话费提醒------------begin*/
utype* cQFeeAwokeAddById(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFeeAwokeAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFeeAwokeAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFeeAwokeAddHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFeeAwokeAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFeeAworkAddByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFeeAwokeByIdAndType(const utype * inParam,TCtrlInfo *errInfo);
/*------------------------------个性话费提醒------------end*/
utype* cIRentMach(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRentMachHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRentMachInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCloseTimeOfRentMachInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cURentMachInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRentMachHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQryAssureInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserAssure(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserAssureHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserAssure(const utype * inParam,TCtrlInfo *errInfo);


utype* cDBillDayInfoByContractNo(const utype * inParam,TCtrlInfo *errInfo);


utype* cQryAssureInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserAssure(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserAssureHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserAssure(const utype * inParam,TCtrlInfo *errInfo);


utype* cDBillDayInfoByContractNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDateInfoOfUserBrandRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBrandRelByIdAndEffDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBillModeInfoByIdNoAndEffDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDateOfUserBillModeInfoByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDateOfUserTeam(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDateOfUserGroupMbrAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDateOfUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);

utype* cIUserfavInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserfavInfoHis(const utype * inParam,TCtrlInfo *errInfo);

/*------------------------------积分转移------------begin*/
utype* cQScoreParamByGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntScoreParamByGroup(const utype * inParam,TCtrlInfo *errInfo);
/*------------------------------积分转移------------end*/
utype* cDRentMachInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBalanceByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBalanceHisBakByPhoneNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBalanceByPhoneNoTime(const utype * inParam,TCtrlInfo *errInfo);
//utype* cGetUsrMasterRunInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserGrpByIdNoGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGrpMbrByObjIdRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGrpByGrpIdGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupByIdNoCodeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLastUserGrpMbrByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLastUserGrpByIdNoGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBillDayInfoByBillDay(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserBalanceByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBalanceHisBakByPhoneNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBalanceByPhoneNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBalRiskInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBalRiskInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBalanceByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserBalanceInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBalanceHisBakByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBalanceInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBalanceInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefByCodeClass(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetUserInfoByIdIccid(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDateOfUserBusiLimitByRuleLvl(const utype * inParam,TCtrlInfo *errInfo);

utype* cIUserDayHisBakByUniKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserDayByUniKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPassInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cUEffDateOfUserBrandRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEffDateOfUserBrandRelHis(const utype * inParam,TCtrlInfo *errInfo);

//1501
utype* cQTempPubDictElemlateByTepIdPubObj(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCssConFigByPubCodeEleIdValue(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQEleValuesByEleId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCntOfCssConfigByEleVlaue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTempPubByCodeFirSecBusiCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cISynthtTicCodfigHisBakByEleConfig(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCssConFigByLoginAcceptEleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICssConFigHisBakByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cDsynTheTicconfigByConfigId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDisOfTempPubDictByObjectCodeFir(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTempPubDictByObjectCodeFirSec(const utype * inParam,TCtrlInfo *errInfo);
utype* cQElementValuesByElementId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDisOfCssConfigByEleVlaue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssConFigByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEletemlateByTepCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQsynTheTicconfigByConfigEleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICssConFig(const utype * inParam,TCtrlInfo *errInfo);
utype* cICssConFigHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEletemlateByTepId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQElementPoolByElementId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICssConFigHisBakByEleLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cDcssConFigByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssConFigByLoginacceptEleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssConFigByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssConFigByQryPublishObj(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserTeamMbrByObjId1(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBalRiskInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);

utype* cUUserPlaceByIdNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cQDoubleCarRiskByFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoByTypePhoneMod(const utype *inParam, TCtrlInfo *errInfo);
utype* cQCssConFigByPubCodeEleIdValue(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQTempPubDictElemlateByTepIdPubObj(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQEleValuesByEleId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cDCopyCardIni(const utype * inParam,TCtrlInfo *errInfo);
utype* cICopyCard(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCopyCard(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCopyCard(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCopyCardByPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCopyCardByFindTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCopyCardByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCopyCardByGroupAndTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDoubleCarRiskHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICopyCardHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCopyCardByFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFilmOrder(const utype *InParam, TCtrlInfo *ptCtrlInfo);
utype* cIFilmOrderHis(const utype *InParam, TCtrlInfo *ptCtrlInfo);
utype* cQCustAssureInfobyIccid(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByValue(const utype *inParam,TCtrlInfo *errInfo);

utype* cITransScoreHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cITransScore(const utype * inParam,TCtrlInfo *errInfo);

/*巢湖拆分换号 wangzxa*/
utype* cQUserRelByMSId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserRelByRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cURelStatusOfUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBusiLimitByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBusiLimitHisBakU(const utype * inParam,TCtrlInfo *errInfo);
utype* cULimitOweOfUserInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserCreditInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiLimitByIdNo(const utype * inParam,TCtrlInfo *errInfo);
/*马鞍山换号新增*/
utype* cQUserRelByGroupId(const utype * inParam,TCtrlInfo *errInfo);
/* 积分商城兑换 */
utype* cQScorePreOccByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfScoreUseByIdBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfScoreUseRdByBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScorePreOccHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScorePreOcc(const utype * inParam,TCtrlInfo *errInfo);
utype* cDScorePreOccByIdNoLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScorePreOccByIdNoLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUsedPointOfScorePreOccByLoginAcceptIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreUsetemp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreUsetemp(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreUsetempBakByAcceptSeq(const utype * inParam,TCtrlInfo *errInfo);
utype* cDScoreUsetempByAcceptSeq(const utype * inParam,TCtrlInfo *errInfo);
utype* cDScoreUsetempByInterAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreUsetempByInterAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreUsetempBakByInterAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUScoreUsetempByInterAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSumScoreUsetempByInterAccept(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserBookingInfoByNoCode(const utype *inParam,TCtrlInfo *errInfo);
utype* cQUserBookingAttrByLoginAccept(const utype *inParam,TCtrlInfo *errInfo);
utype* cUStatusOfUserBookingInfoByLoginAccept(const utype *inParam,TCtrlInfo *errInfo);
utype* cIUserBookingInfoHisBak(const utype *inParam,TCtrlInfo *errInfo);
utype* cIUserBookingInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* cIUserBookingInfoHis(const utype *inParam,TCtrlInfo *errInfo);
utype* cIUserBookingAttrInfo(const utype *inParam,TCtrlInfo *errInfo);
utype* cIUserBookingAttrInfoHis(const utype *inParam,TCtrlInfo *errInfo);
utype* cURelValueOfUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnInfoDepMsgByDepIdLevel(const utype *inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByGrpValueBegin(const utype *inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetSiNoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChgUserInfoBy1IdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrSysCodeDefByCodeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrSysCodeDefByCodeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQParBrandByBrandId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPdBrandNumByGroupidAndBrandid(const utype * inParam,TCtrlInfo *errInfo);

utype* cITerminalServiceInfoHisOthr(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStatusAndFeeOfTermSrvByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChnInfoDepMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChnInfoDepMsgByDepId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDChnInfoDepMsgByDepId(const utype * inParam,TCtrlInfo *errInfo);

/* 积分兑换龙币 */
utype* cQUseRuleByGiftBrand(const utype * inParam,TCtrlInfo *errInfo);

utype* cUFeeOfTermSrvByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);

utype* cDChgInfoPersonMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgInfoPersonMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChgInfoPersonMsg(const utype * inParam,TCtrlInfo *errInfo);

utype* cQAddServiceNoByType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeValueName(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPassInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByBeginEndNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiLimitByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByResNoType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServAddNumInfoByMsterType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeValueGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetStopUserInfoByRunCodeTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQStopofCrmToBossStateHisByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeClassGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICreditCodeChgHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICreditCodeChg(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCreditCodeChgByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICreditCodeChgHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCreditCodeChgByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntCreditCodeChgByIdNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleUserMbrByObjId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQappSpartyExsist(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAppByIdTimeSparty(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfVipDelayOffByIdNoType(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfUserGroupMbrByIdType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserShortNumByGroupIDandCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSAddNumInfoByAddServNoAndType(const utype * inParam,TCtrlInfo *errInfo);

utype* cIVipDelayOff(const utype * inParam,TCtrlInfo *errInfo);
utype* cIVipDelayOffHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnInfoPersonMsgByDepId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEbillOrderInfoByIdNoCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEmailInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfVipDelayOffByIdNoTypeFlagChk(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserBrandRelByIdEff(const utype * inParam,TCtrlInfo *errInfo);

utype* cIVipDelayOffHisBakByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUVipDelayOffByIdTypeLoginAccept(const utype * inParam,TCtrlInfo *errInfo);

utype* cIEbillOrderInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEbillOrderInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEbillOrderInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPostNameOfEbillOrderInfoByIdBillCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cDEbillOrderInfoByIdBillCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEmailInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEmailAddrOfEmailInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEmailInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEmailInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEbillOrderIntf(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSendDayOfEbillOrderInfoByIdBillCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBatchOpenInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDBatchOpenInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBatchOpenInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBatchOpenByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeValueGroupIdRow(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrSysCodeDefByClassGroupId(const utype * inParam,TCtrlInfo *errInfo);

utype* cQTerminalServiceInfoByBusiAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFeeOfTermSrvByBusiAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStatusOfTermSrvByBusiAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserNameOfTermSrvByBusiAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserPhoneOfTermSrvByBusiAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserChgTmpBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserChgTmpHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserChgTmp(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserChgTmp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCrm2BossStateByOpTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBatchOpenByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFreePhoneByFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFreePhoneByFlagRegionId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFreePhoneByFlagPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFreePhoneByFlagTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFreePhoneByFlagPhoneNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserExtInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBatchOpenByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByValueBegin(const utype * inParam,TCtrlInfo *errInfo);

utype* cIScoreUseBusi(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBillModeInfoByIdEff(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScoreUseHisBusi(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiLimitByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUQryFlagOfCustBillQryReqByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustBillQryReqInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserGroupMbrByGrpRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChargeOnLineRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDChargeOnLineRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChargeOnLineRelByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChargeOnLineRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChargeOnLineRelHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScfgByBrand(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCrossDictByMutiP(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserPlaceByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPlace(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPlaceHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserPlaceByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPlaceHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserPlaceByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserPassInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustBillQryReqInfoByIdNoBeginEnd(const utype * inParam,TCtrlInfo *errInfo);
utype* cUQryFlagOfCustBillQryReqByIdNoBeginEnd(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustBillQryReqHisByIdNoBeginEnd(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserImeiInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserImeiInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserImeiInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnUserInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBatchOpenInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBatchOpenInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBatchOpenHisByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfUserBalRisk(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBalRiskInfoHisBakByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBalRiskInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBalRiskInfoByNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPhoneById(const utype * inParam,TCtrlInfo *errInfo);


utype* cQChgUserByIdNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgUerCntByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgUserExp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByGrpValueBegin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgUserPre(const utype * inParam,TCtrlInfo *errInfo);
utype* cDChgUserByIdNoTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChgUserExpDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgUerCntByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgUserExp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByBeginEnd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByGroup(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfApproveRdByLogNoSparty(const utype * inParam,TCtrlInfo *errInfo);
utype* cQApproveRdByIdNoSparty(const utype * inParam,TCtrlInfo *errInfo);
utype* cQApproveRdByTimeSparty(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfApproveRdByTimeSparty(const utype * inParam,TCtrlInfo *errInfo);

//比对版本增加
//新增首次激活自动订购产品配置
utype* cQUrUniCodeDefByCodeClassAndDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSAddNumInfoByAddServNoAndType(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLastDayOfMonthBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChargeOnLineRelByIdNoBusiNo(const utype * inParam,TCtrlInfo *errInfo);
/*wangzxa 电子渠道宽带开户*/
utype* cQPayCHkInfoByChk(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPayCheckInfoHisByOutOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPayCheckInfoByOutOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPayCHkInfoByOutOrder(const utype * inParam,TCtrlInfo *errInfo);

/* 充值卡充值 add by muwb begin */
utype* cDDConWrongMsgByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDDConWrongMsgByTotalDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDConWrongMsgHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIwReChargeMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDConWrongMsgBy7450(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDConWrongMsgBy7452(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDConWrongMsgByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDConWrongMsgByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginAcceptOfBillDead(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOldRunOfUserDeadByIdNo(const utype * inParam,TCtrlInfo *errInfo);
/* 充值卡充值 add by muwb end */

utype* cQUserImeiInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserImeiInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserImeiInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserImeiInfoHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiLimitByIdAndPrcId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCsImsiInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cUGroupIdOfUserGroupMbr(const utype * inParam,TCtrlInfo *errInfo);

utype* cIUserPreInstallInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserPreInstallInfo(const utype * inParam,TCtrlInfo *errInfo);

//系统积分
utype* cQryAssureInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUniCodeDefByClassGroupName(const utype * inParam,TCtrlInfo *errInfo);
//电子券
utype* cQUserMidMinusResValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResValueMinusUserMid(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResValueUseByBusiAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResValueUseByResCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPdUniCodeDefByGroupClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResValueUseByBusiAcceptOpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserImeiInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserAddMidByIdNoMidType(const utype *puInParam, TCtrlInfo *errInfo);
utype* cQPdBrandNumByGroupidAndBrandid(const utype * inParam,TCtrlInfo *errInfo);

//欠费销户增加

utype* cDUrUnicodeDefByCodeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUrUnicodeDef(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUrUnicodeDefHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrSysCodeDefByClassGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrSysCodeDefByCodeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrSysCodeDefByCodeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeClassGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeValueGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUniCodeDefByCodeValueName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUrUnicodeDefByOutdataname(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInfoByStaticMasterServId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgImeiByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSellRdByLoginAcceptBackFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCNTPriceSellResRdByLogAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCNTTypeNumSellResRdByLogAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCNTSellResByLogAcceptBackFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBackFlagSellResRdByLAcceptOpCode(const utype * inParam,TCtrlInfo *errInfo);
/*换号模块新增*/
utype* cULimitOweOfUserInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBusiLimitHisBakU(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBusiLimitByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUserCreditInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cITransScoreHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSlavePhoneOfUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cUMasterPhoneOfUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserRelByMSId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserRelByRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cURelStatusOfUserRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cITransScore(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupByGrpTypeIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserGroupMbrInfoHisByMemberIdAndUpdateType(const utype * inParam,TCtrlInfo *errInfo);
/* 集团跨区入网积分转移 */
utype* cQCssCodeDefDictByBeginGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrByGrpIdExp(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserGrpByIdNoGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGrpMbrByObjIdRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGrpByGrpIdGrpType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoByTypeDate(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetGradeAvgByAttrValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserForumInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUserForumByAttrTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserforumByAttrValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserFormByAttrValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserForumByApproveAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserForumInfoByUserNameAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserForumRelByApproveAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserForumInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserForumRelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserForumRelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserForumRelByApproveAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserForumRelInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTopFlagOfUserForumInfoByAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserForumInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cDScorePreOccByIdNoLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIScorePreOcc(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScorePreOccByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScorePreOccByIdNoLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUsedPointOfScorePreOccByLoginAcceptIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRuleUserGroupMbrByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRuleUserFamilyMbrByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQtest1(const utype * inParam,TCtrlInfo *errInfo);

utype* cQApproveRdByIdLoginTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByGrpBeginEnd(const utype * inParam,TCtrlInfo *errInfo);

utype* cDWlanHotspot(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetWlanHotspotByCodeName(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWlanHotspot(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWlanHotspotHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWlanHotSpot(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfWlanHotspotByCodeName(const utype * inParam,TCtrlInfo *errInfo);

utype* cUBatchOpenInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

/*乘机方便行*/
utype* cQPlaneOrderInfoByPname(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfPlaneOrderInfoByPname(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfPlaneFlightInfoInNormal(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPlaneFlightInfoInNormal(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfPlaneFlightInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPlaneFlightInfoHis(const utype * inParam,TCtrlInfo *errInfo);

/*乘机方便行会员积分*/
utype* cIVitualMoneyInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUVitualMoneyOfVitualMoneyInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIVirtualMoneyInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIVirtualMoneyInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntVitualMoneyInfoByPhoneNoAndVLFLAG(const utype * inParam,TCtrlInfo *errInfo);
utype* cQVitualMoneyInfoByPhNoAndVitualFlag(const utype * inParam,TCtrlInfo *errInfo);

/*乘机方便行模版配置*/
utype* cQCssCodeDefDictByBeginValue(const utype * inParam,TCtrlInfo *errInfo);

/*add by lankai*/
/*用户满意度回访*/
utype* pUserBack(const utype * puInParam,TCtrlInfo * ptCtrlInfo);
/*客户承诺书*/
utype* cIPromiseRecordInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPromiseRecordInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPromiseRecordInfoByPhoneTimeStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPromiseRecordInfoByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPromiseRecordInfoByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntPromiseRecordInfoByPhoneTimeStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPromiseRecordInfoByPage(const utype * inParam,TCtrlInfo *errInfo);
/*积分兑换电子券*/
utype* cUEffSerialPoolInfoByEbillCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEffserialPoolinfoByValidFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEBillInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEBillInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEBillInfoByEBillCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEBillInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResvalueuse(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResvalueuseHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreOutBossAcceptByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQScoreUseBack(const utype * inParam,TCtrlInfo *errInfo);
/*add by lankai end*/
utype* cQBcInterfaceByBusiidNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBcSucessByBusiidNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBcInterfaceDeadByBusiidNo(const utype * inParam,TCtrlInfo *errInfo);


/*haoxz*/
utype* cICheckPasswdRecHisNoStates(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCheckPasswdRecByPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cICheckPasswdrecByStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCheckPasswdrecByStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCheckPasswdRecInfoByPhoneStaOptyTime(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCssCodeDefDictByCodeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUListTypeOfSpecialInfoList(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoByIdCodeList(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoByIdCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByGrpValueBegin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFreePhoneByTypeAndRegion(const utype * inParam,TCtrlInfo *errInfo);

/* 积分兑换电子券 */
utype* cQEffSerialPoolRand(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEffSerialPoolRand(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupInfoOfMbrByObjIdAndGroupType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGrpMbrByStateObjIdRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserGrpMbrByGrpIdState(const utype * inParam,TCtrlInfo *errInfo);

/*省内携号转网新增BC*/
utype* cQGroupChgByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupChgByIdNoDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupChgByIdNoExpDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGroupChgInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpInfoOfGroupChgInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGroupChgInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupChgByIdNoNoEff(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGroupChgHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGroupChgHisBak(const utype * inParam,TCtrlInfo *errInfo);

/*集团账务*/
utype* cQMebFeeBackInfoByFeeAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIMebFeeBackInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIMebFeeBackInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBusiLimitByIdAndPrcId(const utype * inParam,TCtrlInfo *errInfo);

/*积分兑换唐久金虎便利店*/
utype* cIEBillExcpInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEBillExcpInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEBillInfoByIdEBill(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEBillInfoByIdEBillFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEBillInfoEff(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEBillInfoOutTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEBillInfoUsed(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEBillInfoByCreateAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEBillInfoByIdEBill(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEBillInfoHisByCreateAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEBillExpDateByCreateAccept(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserGroupMbrByGrpIdAndState(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserCreditInfoByIdNoMul(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUserGroupMbrByGrpIdAndOpTime(const utype * inParam,TCtrlInfo *errInfo);



utype* cQResValueUseByIdNoAndBusi(const utype * inParam,TCtrlInfo *errInfo);
utype* cUResValueUse(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResValueUseByIdNoWrtoff(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResValueUseByBackAcc(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResValueUseByBusiApt(const utype * inParam,TCtrlInfo *errInfo);


/* 对账框架 */
utype* cICompareBillResult(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillResultHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCompareBillOutMinus(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCompareBillOutByBack(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCompareBillOutByOut(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillOutHisByOut(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillOutHisByBack(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillIn(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCompareBillInMinus(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillInHisByOut(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillInHisByBack(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCompareBillInByOut(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCompareBillInByBack(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCompareBillInValue4(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillInHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillInScore(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNgLessDZQ(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNgMore(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNgLessJF(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillOutHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCompareBillOutValue14(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResultNgMore(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResultHisNgMore(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResultHisNgLess(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResultNgLess(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCompareResultByBusiFile(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCompareResultByOutAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareResultHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResultNgBal(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResultHisNgBal(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntCompareBillResult(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCompareBillResultOutKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareResultHisBakAll(const utype * inParam,TCtrlInfo *errInfo);
utype* cUComPareBillOutByValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCompareOutByValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cDComPareBillOutByValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cICompareBillOutHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResultNgNotExistsHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResultNgNotExists(const utype * inParam,TCtrlInfo *errInfo);

utype* cULimitOwe200(const utype * inParam,TCtrlInfo *errInfo);

utype* cUStatusOfChgUserByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChgUserInfoHisBakByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBrandRelHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cQMutiUseRuleByGiftId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMutiUseRuleHisByGiftId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMutiUseRuleAllHisByGiftId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUseRuleDictNew(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUseRuleDictHisNew(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUseRuleExpDateByIndex(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMutiUseRuleByWorkNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCssCodeDefDictByIdDesc(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMutiUseRulePreByGiftId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUseruleByIndex(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCssCodeDefDictByGrpValueBeginEnd(const utype * inParam,TCtrlInfo *errInfo);

utype* cQPreOpenByIdTypeIdIccidAndPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPreOpenByIdTypeIdIccidAndPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cDPreOpenByIdTypeIdIccidAndPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPreOpenByIdTypeIdIccidAndPhoneBak(const utype * inParam,TCtrlInfo *errInfo);

utype* cCntUserAddByFieldIdNoTime(const utype * inParam,TCtrlInfo *errInfo);

#endif

utype* cQSpecialListInfoHisByTypePage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpecialListInfoHisByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* IPerOpenInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* IPerOpenInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPerOpenInfoByID(const utype * inParam,TCtrlInfo *errInfo);
utype* uEvaluateByInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPerOpenInfoByIDPHONE(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupMbrInfoByGroupIdTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cCntOfUserGroupMbrInfoByGroupIdTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupChgByIdNoEff(const utype * inParam,TCtrlInfo *errInfo);

utype* cQServAddNumInfoHisByIDType(const utype * inParam,TCtrlInfo *errInfo);


utype* cQChgUserByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgUserHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChgUserHisByUpdate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserBrandRelByIdAndUniCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGroupChgByPhoneOptime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTestTypeByExtendFlag(const utype * inParam,TCtrlInfo *errInfo);

utype* cQSumCheckScoreBusiUse(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSumCheckScoreBusiByType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMinusScoreOutBossAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSumScoreOutBossAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMallBossLessDetail(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMallBossMoreDetail(const utype * inParam,TCtrlInfo *errInfo);

utype* cQApproveByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQApproveRdByAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQServiceNoInfoByServiceNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cISmpCardFsInfo(const utype * inParam,TCtrlInfo *errInfo);
/*majx 2012-08-20*/
utype* InPerOpenInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* InPerOpenInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfmkactrecordtermiinfoByPhoneNoAndTime(const utype * inParam,TCtrlInfo *errInfo);

//chenjj test
utype* cQUserInfoByIdNocjj(const utype * inParam,TCtrlInfo *errInfo);

/*信用度延伸*/
utype* cQSumOfUserRelByMidMonth(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserRelBySixMonth(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserRelByMidMonth(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserRelByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cURelStatusOfUserRelBySlavePhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserRelByRelationCode(const utype * inParam,TCtrlInfo *errInfo);

/*优化前台靓号预约功能*/
utype* cICustResAddOrdInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustResAddOrdInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustResAddOrdInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustResAddOrdInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustResAddOrdInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustResAddOrdInfoByRes(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCssCodeDefDictByOther(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetLoginAcceptTimeBySparty(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserStateHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cCntUserGroupInfoByObjIdAndIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupInfoByObjId(const utype * inParam,TCtrlInfo *errInfo);

utype* cDClubMemberInfo(const utype * inParam,TCtrlInfo *errInfo);
//yinzx  2012/9/25 11:53:13业务受限需求
utype* cQUserBusiLimitByOnlyIdA(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cQUserBusiLimitByOnlyIdB(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//add by cencm 20120928
utype* cQUserRelByExpDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTimesOfCheckPasswByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQChgUserPreByIdTime(const utype * inParam,TCtrlInfo *errInfo);

utype* cUEffDateByRelaCodeAndMasterPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEffDateByRelaCodeAndSlavePhone(const utype * inParam,TCtrlInfo *errInfo);

utype* cQClubMemberInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUClubMemberValue4(const utype * inParam,TCtrlInfo *errInfo);
utype* cIClubmebsrcInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIClubmebsrcInfoHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cUExpDateByRelAndSlaveId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIuserRelHisByMaSlaRelOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserRelByRelAndSlaveId(const utype * inParam,TCtrlInfo *errInfo);

utype* cDUserResOrdByLoginNo(const utype * inParam,TCtrlInfo *errInfo);

//短息验证码
utype* cIChkSmsPwd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChkSmsPwd(const utype * inParam,TCtrlInfo *errInfo);
utype* cISendSmsPwd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSendSmsPwd(const utype * inParam,TCtrlInfo *errInfo);
