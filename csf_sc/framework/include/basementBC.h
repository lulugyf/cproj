#ifndef __BASEMENTBC_H__
#define __BASEMENTBC_H__
#define SEG_SIGN '|'
#define LOGINMSG_MAXLEN 4096

utype *cQRolePdomByRoleChildPdom(const utype *inParam, TCtrlInfo *errInfo);
utype *cISmsMaintenanceLogInfo(const utype *inParam, TCtrlInfo *errInfo);
utype *cQUniCodeDefByCodeValue(const utype *inParam, TCtrlInfo *errInfo);
utype *cQUniCodeDefByIdCodeName(const utype *inParam, TCtrlInfo *errInfo);
utype *cQUniCodeDefByIdCodeNameClass(const utype *inParam, TCtrlInfo *errInfo);
utype *cQUnicodeDefByCodeNameAndCodeValue(const utype *inParam, TCtrlInfo *errInfo);
utype *cQUniCodeDefByCodeClass(const utype *inParam, TCtrlInfo *errInfo);
utype *cQCustLevelByCustLevel(const utype *inParam, TCtrlInfo *errInfo);
utype *cQChnGroupByGroupId(const utype *inParam, TCtrlInfo *errInfo);
utype *cQHlrDictByPhoneHead(const utype *inParam, TCtrlInfo *errInfo);
utype *cQRunCodeDictByRunCode(const utype *inParam, TCtrlInfo *errInfo);
utype *cQForceOpenExpireByRegId(const utype *inParam, TCtrlInfo *errInfo);
utype *cQUniCodeDefByGrpCodeValue(const utype *inParam, TCtrlInfo *errInfo);
utype *cQUniCodeDefByGrpCodeClass(const utype *inParam, TCtrlInfo *errInfo);
utype *cQBusiCodeByIdx(const utype *inParam, TCtrlInfo *errInfo);
utype *cQFunctionByFunctionCode(const utype *inParam, TCtrlInfo *errInfo);
utype *cGetOrgTypeAndOptrLvl(const utype *inParam, TCtrlInfo *errInfo);
utype *cQAccountTypeByAccountType(const utype * inParam,TCtrlInfo *errInfo);
utype *cQConPayByPayCode(const utype * inParam,TCtrlInfo *errInfo);
utype *cQCntOfFuncVerifyByFuncReg(const utype * inParam,TCtrlInfo *errInfo);
utype *cQCntOfOpAuthenRelByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype *cQProdOpAuthenByMulProdOp(const utype * inParam,TCtrlInfo *errInfo);
utype *cQProdOpAuthGrpByMulProdOp(const utype * inParam,TCtrlInfo *errInfo);
utype *cGetAuthenRelByMulProdOpAuthGrpInter(const utype * inParam,TCtrlInfo *errInfo);
utype *cQryAddrCfgByCoopMode(const utype * inParam,TCtrlInfo *errInfo);
utype *cGetPopedomByLoginRole(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime0(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime1(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime2(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime3(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime4(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime5(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime13(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime6(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTimeNow(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTimeAdd(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTimeMinus(const utype * inParam,TCtrlInfo *errInfo);
utype * cQSeqAttrId(const utype * inParam,TCtrlInfo *errInfo);
utype * cQSeqProdPrcInsId(const utype * inParam,TCtrlInfo *errInfo);
utype * cQSeqGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype * cQSeqMemberId(const utype * inParam,TCtrlInfo *errInfo);
utype * cQSeqTeamId(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime7(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime8(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime9(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime10(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTime12(const utype * inParam,TCtrlInfo *errInfo);
utype * cQChnGroupRelByParentLevel(const utype * inParam,TCtrlInfo *errInfo);
utype * cQStaffInfoByStaffId(const utype * inParam,TCtrlInfo *errInfo);
utype * cQSimFeeByRegionSim(const utype * inParam,TCtrlInfo *errInfo);
utype * cQBureauBankByBankCode(const utype * inParam,TCtrlInfo *errInfo);
utype * cQbcInfoByBcName(const utype * inParam,TCtrlInfo *errInfo);
utype * cUBcinfoByBcName(const utype * inParam,TCtrlInfo *errInfo);
utype * cQBankDictByParBankCode(const utype * inParam,TCtrlInfo *errInfo);
utype * cQSpecialChoiceLimitDictByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype * cQStandardAddrDictByAddrId(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTimeSub(const utype * inParam,TCtrlInfo *errInfo);
utype * cQTimeSub1(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTimeMinusByDay(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTimeNowFmt(const utype * inParam,TCtrlInfo *errInfo);

utype * cQBankDictByParGroup(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQFileColModelByRowNum(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQFileColModelByColId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIFileColModel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUColInfoOfFileColModel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cDFileColModel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQFuncExecPeriodByFuncCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIFuncExecPeriod(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUTimeOfFuncExecPeriod(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cDFuncExecPeriod(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQFileByFileId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQFileColumnByFileId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIFile(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIFileColumn(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cDFile(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cDFileColumn(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUFileInfoOfFile(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUStatusOfFileByFileId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQExtAttrDictByFieldCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQExtAttrDictByAttrType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQExtAttrDictByAttrType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIInWorknT(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype * cQFuncApplyFileByMasFuncCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIFuncApplyFile(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cDFuncApplyFile(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQSeqFileId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQSeqColId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQCntOfFileColModel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQSeqTimeId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQBankDictByBankCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQSeqContactId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cIContactMsgRd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUStatusOfContactMsgRd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cUEndTimeOfContactMsgRd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQTime10(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQTime11(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cICustRandPwdRd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cDCustRandPwdRd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cICustRandPwdYYYYMM(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQPoliRegionByRegionId(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cICustRandPwdYYYYMM(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype * cQCustRandPwdRdByIdType(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* cQBusiAccept(const utype * inParam,TCtrlInfo *errInfo);

utype* cCheckWorkStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cDChnGroupDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDChnGroupRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginIpLimitDictByDelCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginMenuDictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginMenuDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginModule(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginPopedomRelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginPopedomRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginRoleRelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginRoleRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginShortcut(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginThemeByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRegionRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRegionRelByPReg(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRegionRelByTReg(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRolePdomByDelCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRoleRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRoleRelByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetDataByFunc(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncByPar(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncDataByProc(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncList(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncListByFuncType(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetStationLoginList(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChnGroupDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChnGroupRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDataObjItem(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncDataItem(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFunction(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginCheck(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginIpLimitDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMenu(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMenuHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginModule(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginModuleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMsgDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMsgHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginPopedom(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginPopedomHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRoleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRoleRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginShortcut(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginShortcutHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginStationHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginTheme(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginThemeHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPoliRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPopedom(const utype * inParam,TCtrlInfo *errInfo);
utype* cIProcedureDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRegionRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleHisBakByChild(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRolePdom(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRolePdomHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRolePdomHisBakByRoleDown(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIStandAddr(const utype * inParam,TCtrlInfo *errInfo);
utype* cITeleRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWorkStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWorkStationHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWorkStationHisBakByChild(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfRoleByLoginRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGrpByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfChnGrpByIdName(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGrpByIdName(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGrpRelByIdLevel(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGrpRelByAuditFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGrpRelByLevel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginModule(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDataItemByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExpireTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncDataItemByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProcedureDictByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFunctionByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfFunctionByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFunctionByOneParent(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFunctionByParent(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncPEdomByParCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAuthenInfoByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginCheckByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginCheckByLoginDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginDataPdomByAll(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginIpLimitDictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginIpLimitDictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMenuByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginMenuByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMenuDictByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMenuDictByShowOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginModuleByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginModuleDictByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginMsgByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByPageCount(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMsgByStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByIdValid(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMsgDictByLoginPrefix(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMsgDictHisByUpdateCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginPdomListByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginPopedomByAll(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginPopedomByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPopedomByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginPopedomByRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginRoleByLoginRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRoleByRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginRoleByValidFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRoleRelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginRoleByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginPEdomByPEdomCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRoleSysByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfLoginRoleRelByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginRoleByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginSerialByLoginPrefix(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginShortInfoByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginShortcutByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginShortcutDictByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRelInfoByLoginStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginStationByStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRelTimeByLoginStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginThemeByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFunctionDcit(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpAuthenByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpAuthenRelByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAuthenInfoByAuthenGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpAuthGrpByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfRoleByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetPdomSoundByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetPoliRegionByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPoliRegionByPar(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPopedomByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRegionIpLmtByRegId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRegRelInfoByIdRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRegionType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRegRelType(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleInfoByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleDictByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleDictByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntRolePdomByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRolePdomByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncCodeByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRolePdomMatrixByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleRelByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleRelByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRootStationByStationId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetStandAddrByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQStandAddrByName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQStandAddrByParent(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetStationInfoByStationId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetTeleRegionByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTeleRegionByPar(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThemeDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfChnGroupDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAuditFlagOfChnGroupDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUHasChildOfChnGroupDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfFunctionDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStatusOfLoginCheckByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUShowOrderOfLoginModule(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTryTimesStatusOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPasswdStatusOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPasswdOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStatusOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTryTimesOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPrivsOfLoginPdomRelByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cUValueOrderOfLoginShortcut(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfPoliRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChildUseFlagOfRoleByRar(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPrivsOfRolePdomRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfStandAddrByPRegId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfTeleRegionByPar(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStationInfoOfWorkStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChildStatusOfWorkStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfChnGroupRelByTwoGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMsgDictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPdomByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRoleRelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRolePdomByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDTeleLoginRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTeleLoginRelByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cITeleLoginRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetTeleLoginRelByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cITeleLoginRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUseFlagOfTelephonist(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfTelephonistByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetTelephonistByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cITelephonistHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFileColFunc(const utype * inParam,TCtrlInfo *errInfo);
utype* cUXMLPathOfFileColFunc(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFileColFunc(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFileColFuncByColIdFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChannelClassByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChannelKindByClassKind(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBatchFuncRelByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBatchFuncRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDBatchFuncRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOutSystemByOutSysId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFileColFuncByColId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAuthenRelByAuthenGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPopedomByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginMsgByLoginPrefix(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFunctionOfLoginShortcut(const utype * inParam,TCtrlInfo *errInfo);

utype* cIStaff(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfStaff(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCurTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cIExworkNmsg(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCustLevelDictByTypeCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cQPositionByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPosition(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPosition(const utype * inParam,TCtrlInfo *errInfo);
//utype* cQPositionByMulCond2(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginPositionByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPositionByLoginNO(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginPosition(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginPosition(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustShowCfgDictByTypeTab(const utype * inParam,TCtrlInfo *errInfo);

utype* cIRegionIpLmt(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRegionIpLmt(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustShowCfgDictByTypeCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFileColumnByColumnId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBrief(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSalePriceByGrpRes(const utype * inParam,TCtrlInfo *errInfo);
utype* cIQuickInnetModelDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIQuickInnetModelDictHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIQuickInnetModelDictHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQQuickInnetModelDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQQuickInnetModelDictByModelId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQQuickInnetModelDictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDQuickInnetModelDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQQuickInnetModelReleaseDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIQuickInnetModelReleaseDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDQuickInnetModelReleaseDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDQuickInnetModelReleaseDictByModelId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPopedomHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSeqModelId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfHlrDictByPhoneHead(const utype * inParam,TCtrlInfo *errInfo);
utype* cQQuickInnetModelReleaseDictByGroupId(const utype * inParam,TCtrlInfo *errInfo);

utype* cQHlrDictByRowNum(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChinaPhoneHead(const utype * inParam,TCtrlInfo *errInfo);
utype* cDChinaPhoneHeadByPhoneHead(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChinaPhoneHeadByPhoneHead(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChinaPhoneHeadByPhoneNoHead(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfChinaPhoneHeadByPhoneNoHead(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetCntOfLoginRoleByLoginRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLastDay(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGrpDictByLevel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTermByCodeHard(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRunStopTypeRelByRunCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMsgDictByContactPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRoleRelByRoleCodeType(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStaffOfLoginMsgByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCityPoliRegionById(const utype * inParam,TCtrlInfo *errInfo);

utype* cILoginPositionHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRegionIpLmtByRegIdPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfRegionIpLmtByRegId(const utype * inParam,TCtrlInfo *errInfo);

utype* cINoteDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cINoteHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTitleContentOfNote(const utype * inParam,TCtrlInfo *errInfo);
utype* cDNoteDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNoteById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNoteByNameLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNoteReleaseById(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetNoteByPowerGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginReadNote(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginReadNoteByLoginId(const utype * inParam,TCtrlInfo *errInfo);
utype* cINoteRelease(const utype * inParam,TCtrlInfo *errInfo);
utype* cDNoteRelease(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSalePriceByRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResPriceFeeCodeByRegionRes(const utype * inParam,TCtrlInfo *errInfo);
utype* cITermDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTermDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDTermDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTermDictByCodeRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfTermDictByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfTermDictByCodeRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAfterLmtRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAfterLmtRuleByRuleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUNoteRelease(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChinaPhoneHead(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGroupDictByLoginPrefix(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFuncApplyFile(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfChnGroupRelByGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFavorByLoginRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFavorByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFunctionByFunctionCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQClmuSicInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQClmuSicInfoByMusicNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetSingBoxSeq(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTeleRegionByRegionId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResPreTimesByClassResRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStatusOfUniCodeDef(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentDictByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentDictByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAgentDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAgentDictHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDAgentDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentDictByPhoneGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAgentRealPay(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAddActualOfAgentPayStatByGroupID(const utype * inParam,TCtrlInfo *errInfo);
utype* cURecAttrOfAgentRealPayByBankSeq(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSubActualOfAgentPayStatByMulCol01(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAddActualOfAgentPayStatByMulCol01(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSubActualOfAgentPayStatByGroupID(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetBankPayContrl(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByGroupRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfLoginMsgByGroupRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cDStaff(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginPositionByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPopedomCodeStatusOfUniCodeDef(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginPopedomByLoginPdomType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMenuByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDTeleLoginRelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGrpRelByGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfRegionIpLmtByRegIPLmt(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSeqTaskAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFavorOfRolePdomRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFavorOfLoginPdomRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGroupRelByTwoGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetTmpPopedomByFuncGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cITmpPopedom(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfTmpPopedomByFuncGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cDTmpPopedom(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetTmpPopedomByGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cITmpPopedomOpRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfRunStopTypeByStopType(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncDataItemHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRegionIpLmtHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPoliRegionHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIStandardAddrHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginIpLimitHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChnGroupDictHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIProcedureHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChnGroupRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPositionHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDataObjItemHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncVerifyHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cITermHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChinaPhoneHeadHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLastMonth(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRelByChildLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRelByParentLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAllSubLoginRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginRelByChildLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRelHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRunCodeCompRuleByCrmBossCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cIFunctionHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIStaffInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cITmpPopedomHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cITmpPopedomOpRdHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginPositionByPosiCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTermByTermCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNoteReleaseByNoteGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleRelByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleRelByRelId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleRelByRoleCodeType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGroupRelByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRegionIpLmtByRegIPLmt(const utype * inParam,TCtrlInfo *errInfo);
utype* cINoteReleaseHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByStaffNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGroupByIdTwoDimensional(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUniCodeDefByCodeName(const utype * inParam,TCtrlInfo *errInfo);

utype* cQResCodeByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResTypeByType(const utype * inParam,TCtrlInfo *errInfo);

//文件接口
utype* cQGroupByInterface(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRegionByInterface(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMsgByInterface(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleByInterface(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRoleByInterface(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRolePdomByInterface(const utype * inParam,TCtrlInfo *errInfo);

//add by chenhong(sx) 资源上传接口
utype* cQPhoneByRes(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSimByRes(const utype * inParam,TCtrlInfo *errInfo);
utype* cQimsiHlr(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginRelByChildAndMaster(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRelByParentAndMasterInPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfLoginRelByParentAndMaster(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetFuncVerifyByFuncRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncVerify(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncVerify(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncVerify(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfLoginMsgByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRoleByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSAProdPricePlanByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cDSAProdPricePlanByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cISAProdPricePlan(const utype * inParam,TCtrlInfo *errInfo);
utype* cISAProdPricePlanHisByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCodeOfSACode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfPopedom(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetResSellIdByRowNum(const utype * inParam,TCtrlInfo *errInfo);

utype* cQAuthenticationByAuthenCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQStaffInfoByStaffNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfTelePhonistByTeleLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cITelePhonistDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetTelePhonistByTeleLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cDTelePhonist(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTeleNameOfTelePhonistByTeleLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfTelePhonistByTeleLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfStandAddrByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleGroupHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleGroupByRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRoleGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleGroupByRoleGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfRoleGroupByRoleGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleGroupByRoleGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleGroupByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetMaxCommCodeOfStandAddr(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGroupRelByParGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGroupRelByDenormLevel(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfStandAddrByBuildCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRegionCfgByRegionId(const utype * inParam,TCtrlInfo *errInfo);
//utype* sLocalPath(const utype * inParam,TCtrlInfo *errInfo);
//utype* ptCtrlInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBimGroupByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetSitEnavigateByAreaTypeAttr(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginRouteByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRouteData(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPartionCodeOfRouteData(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleChildByRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQIdmMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPopedomAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDataObjItemAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRoleAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncDdataItemAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginPopedomAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIProcedureAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRolePdomAdd(const utype * inParam,TCtrlInfo *errInfo);

utype* cIFunctionRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFunctionRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncRelByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFunctionRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRolePdom(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMenuByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginModuleByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginShortcutByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTmpPopedomByFunc(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncBusiCodeByFunc(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncVerifyByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProdAuthenRelByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIProdOpAuthenRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDProdOpAuthenRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProdAuthenGrpByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIProdOpAuthGrpHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDProdOpAuthenGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProdAuthenByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIProdOpAuthenHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDProdOpAuthen(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBusiCodeByBusiCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBusiCodeHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBusiCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBusiCodeByBusiCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleInfoByRoleLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRegionGroupByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGrpCityByIdLevelClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMastterServCtrlByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetMasterServCtrlByIdx(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGroupTownByParGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cITmpLoginPdom(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleGroupByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFunctionRelByParFunc(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOneLevelParentByRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncVerifyByFuncReg(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpAuthenRelByOpInterface(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentDictByPhType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentDictByGroupType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentDictByLoginType(const utype * inParam,TCtrlInfo *errInfo);

utype* cUPasswordOfAgentDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRegionCfgByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype *cQCtdByUnicodeCode(const utype *inParam, TCtrlInfo *errInfo);
utype* cGetLastMonth(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetNextMonth(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInCrmWorknT(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInWorknTBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDInCrmWorknT(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChannelClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOptrInfoByClasscode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGroupIdByClasscode(const utype * inParam,TCtrlInfo *errInfo);
utype *cQUniCodeDefByBeginValue(const utype *inParam, TCtrlInfo *errInfo);
utype* cQQuickInnetModelDictByRegId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIQuiInnetModelRelDictHisBakByModelId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIQuiInnetModelRelDictHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQInCrmWorknT(const utype * inParam,TCtrlInfo *errInfo);

utype* cDRoleAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cDPopedomAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cDDataObjItemAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginRoleAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncDdataItemAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginPopedomAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cDProcedureAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRolePdomAdd(const utype * inParam,TCtrlInfo *errInfo);

utype* cIIdmMsgOp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleAddByIDBId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPopedomAddByIDBId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRoleAddByIDBId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPopedomAddByIDBId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProcedureAddByIDBId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRolePdomAddByIDBId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDataObjItemAddByIDBId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncDataItemAddByIDBId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfFuncPEdomByParCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQpcmacInfoByMacId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUpcmacInfoByMacId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIpcmacInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIpcmacInfohis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDBusiCodeByBusiCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBusiCodeByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBusiCodeByFuncMaster(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAgentDictByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGroupOwnorgOfAgentDictByContractNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfAgentDictByContractNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserinfoByNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginStatusByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfLoginStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntSvcRuleRelById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRuleFactorById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUniCodeDefByCodeValueNoGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleAuthenByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAuthenByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleAuthenRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleAuthenHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRoleAuthenByRoleDown(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleAuthenHisBakByRoleDown(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleAuthenByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleAuthen(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserServLocByAddressId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleAuthenInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGroupDictByGroupName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUniCodeDefByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUniCodeDefByCodeNameandBeginValue(const utype * inParam,TCtrlInfo *errInfo);

//统一代码管理
utype* cQDynSrvDictBySvcName(const utype *inParam, TCtrlInfo *errInfo);
utype* cQDynSrvDictByQryCond(const utype *inParam, TCtrlInfo *errInfo);
utype* cIDynSrvDict(const utype *inParam, TCtrlInfo *errInfo);
utype* cUDynSrvDict(const utype *inParam, TCtrlInfo *errInfo);
utype* cDDynSrvDict(const utype *inParam, TCtrlInfo *errInfo);
utype* cIDynSrvDictHis(const utype *inParam, TCtrlInfo *errInfo);
utype* cIDynSrvDictHisBak(const utype *inParam, TCtrlInfo *errInfo);
utype* cUUnicodeClassByCodeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnicodeClassByCodeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUnicodeClassHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUnicodeClassDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnicodeDefByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUnicodeDefHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUnicodeDefDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUnicodeDefByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfUniCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUnicodeClassByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfDynSrvByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUnicodeClassHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUnicodeDefHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUnicodeDefByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUnicodeClassByCodeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCodeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCodeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUnicodeDefByCodeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUnicodeDefByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnicodeDefByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUnicodeCodeClassByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUnicodeCodeClassByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUniCodeDefByCodeClassAndCodeName(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginRoleByValidFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRoleHisBakByRoleDown(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginRoleByDelCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentDictByPhTyDate(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginMsgByGroupID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGrpDictAndRelByRootDistanceAndParentGrpID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGroupByRootDistGrp(const utype * inParam,TCtrlInfo *errInfo);

//管理区域管理
utype* cQCntOfRegionRelByTRegionId(const utype * inParam,TCtrlInfo *errInfo);
utype* cITeleRegionHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTeleRegionByCon(const utype * inParam, TCtrlInfo *errInfo);

//公告信息管理
utype* cQNoteReleaseByNoteId(const utype * inParam, TCtrlInfo *errInfo);
utype* cGetNoteByMul(const utype * inParam, TCtrlInfo *errInfo);
utype* cINoteAttachment(const utype * inParam, TCtrlInfo *errInfo);
utype* cINoteAttachmentHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cDNoteAttachmentById(const utype * inParam, TCtrlInfo *errInfo);
utype* cQNoteAttachmentByNoteId(const utype * inParam, TCtrlInfo *errInfo);
utype* cGetAttachmentId(const utype * inParam, TCtrlInfo *errInfo);
utype* cGetNoteByPowerGroupFuzzy(const utype * inParam, TCtrlInfo *errInfo);
utype* cDLoginReadNoteByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginReadNoteByNote(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginReadNoteRc(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFlagOfLoginReadNoteRc(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginReadNoteByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetReadId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetBeforeTime(const utype * inParam,TCtrlInfo *ptCtrlInfo);

utype* cQTeleRegionByCon(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cITeleRegionHis(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cQCntOfRegionRelByTRegionId(const utype * inParam,TCtrlInfo *ptCtrlInfo);

utype* cQDataItemByObjid(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cQNoteAttachmentByNoteId(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cGetAttachmentId(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cINoteAttachmentHis(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cINoteAttachment(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cQNoteAttachmentByNoteId(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cGetCntOfNoteInfoByPage(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cGetNoteInfoByPage(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cQNoteReleaseByNoteId(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cGetNoteByMul(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cDNoteAttachmentById(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* _cQDataItemByObjid(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* _cQFunctionByFunctionCode(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* _cGetFavorByLogin(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* _cGetPopedomByLoginRole(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cUBriefOfFunction(const utype * inParam,TCtrlInfo *ptCtrlInfo);
utype* cQLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetDataPopedomByFunc(const utype * inParam,TCtrlInfo *errInfo);
utype* cQInterfaceDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAuthenOfFunction(const utype * inParam,TCtrlInfo *errInfo);

utype* cQProvinceInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCityInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDistrictInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cIRegionCfgDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRegionCfgDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetMaxCodeOfRegionCfg(const utype * inParam,TCtrlInfo *errInfo);

utype* cQPrivilegeLoginByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGroupLimitFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTimeBF(const utype * inParam,TCtrlInfo *errInfo);

//铁通融合
utype* cQMobCrcGroupByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMobCrcGroupByRelGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGroupRelByGroupAndPar(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMobCrcGroupRelByAll(const utype * inParam,TCtrlInfo *errInfo);
utype* cIMobCrcGroupRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIMobCrcGroupHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupLevelRelByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAllChnGroupTownByParGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMobCrcGroupUnion(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProvinceInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCityInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDistrictInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPoliRegionByRegionCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCodeIdOfunicodeClassByValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSvcIdOfUserSvcInfoHisById(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetChnGrpRelByGroupId(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetLoginMsgByPage2(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByPageCount2(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetChnGroupRelInfo(const utype * inParam,TCtrlInfo *errInfo);

//多OP改造
utype* cULoginModuleByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginModuleTypeDictByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetModuleTypeByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginModuleType(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginModuleTypeHis(const utype * inParam,TCtrlInfo *errInfo);
//zhangmeng add
utype* cGetScheduleTheme(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginThemeByLoginTheme(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThemeValueByThemeDefault(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThemeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfMdlTypeByName(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginModuleTypeByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginModuleTypeByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginModuleTypeByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginOpRoleByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRolePanelByOpRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWorkPanelByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWorkContentByPK(const utype * inParam,TCtrlInfo *errInfo);

utype* cILoginPanelRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginPanelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPanelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginPanelByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPanelByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPanelByIdFlag(const utype * inParam,TCtrlInfo *errInfo);

utype* cIFuncNoteRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncNoteHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpCodeOfFuncNote(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncNoteByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetNoteByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginCalendarById(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginCalendarRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginCalendarRelById(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginCalendarRelById(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginCalendarHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncNoteByGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginCalendarByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginCalendarByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetBasementAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginReadNoteByParGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUnsettledTaskByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginCalendarByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpGuideModelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpGuideModel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpGuideModelStepHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpGuideModelStep(const utype * inParam,TCtrlInfo *errInfo);
utype* cQModelStepByModelCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpGuideModelStep(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpGuideModel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpGuideModelByModelCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpGuideModelByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpGuideModel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpGuideHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpGuideStepHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpGuideStepDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGuideCode(const utype * inParam,TCtrlInfo *errInfo);
utype* uQCntOfOpGuideByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpGuideDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpGuideStepDictByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpGuideStepByGuideCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpGuideModelByName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpGuideByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpGuideByGuideCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpGuideByGuideCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpGuideByGuideCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpGuideByAuditStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetStepByGuideCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOpGuideStepByGuideCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginOpRoleRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginOpRoleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginOpRoleByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleDictByOpRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfOpGuideByModelCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleThemeByOpRoleTheme(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOpRoleThemeByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetThemeByOpRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginCalendarByRemind0(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginCalendarByRemind3(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCommRuleByFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginOpRoleByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpRoleThemeHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUThemeValueByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThemeValueByThemeId2(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfThemeValueByThemeDefault(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThemeValueByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpRoleThemeByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleThemeByThemeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginThemeByThemeValue(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginTargetByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginTargetByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginTargetByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginTargetByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginTargetByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginTargetByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginTargetDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginTargetHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginTargetByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginTargetByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMsgByLoginNoTemp(const utype * inParam,TCtrlInfo *errInfo);

//wangjxc add
utype* cGetOpRoleInfoByParentId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfOpRoleMsgByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOpRoleMsgByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpRoleMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetMaxOpRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpRoleMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChildOfOpRoleDictById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleThemeByOpRoleId(const utype * inParam,TCtrlInfo *errInfo);

utype* cQFuncNoteByNoteId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncNoteByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginOpRoleByOpRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpRoleMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpRoleTheme(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpRolePanel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpRolePanelByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRolePanelByIdStatus(const utype * inParam,TCtrlInfo *errInfo);

utype* cQWorkContentByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDWorkPanel(const utype * inParam,TCtrlInfo *errInfo);
utype* cUWorkContent(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWorkContentByContentId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetMaxContentID(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWorkContent(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWorkContentHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAllWorkContent(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetWorkPanelByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDWorkPanelByPanelId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWorkPanelByPanelId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUWorkPanel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWorkPanelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQContentIdByContentPath(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWorkPanelByPanelCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWorkPanel(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAllWorkPanel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleByOpRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetPanelByOpRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDefauleFlagByPanelId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpRolePanelRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpRolePanelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleMsgByOpRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpRoleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWorkPanelByContentId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWorkContentByPath(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCommRuleByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCommRuleByRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCommRuleByRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCommRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cICommRuleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetMaxRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cICommRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCommRuleByEffFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCommRuleDefByRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentDictByGroupName(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetAllTheme(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAllThemeByFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThemeByThemeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDThemeValueByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cUThemeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cIThemeValueHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIThemeValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpThemeRelByThemeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpThemeByThemeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThemeNameByThemeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleByThemeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOpThemeRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOpTheme(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOpRoleByThemeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetWorkPanelByOpRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUThemeValueByThemeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOpRoleFlagByThemeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetDefPanelByRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetPanelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpRoleByParentRoleId(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetCntOfOpLoginlogByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOpLoginlogByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginLog(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfOpLoginOprByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOpLoginOprByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginOpr(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginOpRoleByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginCheckAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginOpRoleByLoginOpRole(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetCntOfOpLoginNumByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfOpRoleNumByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOpLoginSumTimeByMulCond(const utype * inParam,TCtrlInfo *errInfo);

//托收银行管理
utype* cGetCntOfBankDictByQryCond(const utype *inParam, TCtrlInfo *errInfo);
utype* cGetBankDictByQryCond(const utype *inParam, TCtrlInfo *errInfo);
utype* cIBankDict(const utype *inParam, TCtrlInfo *errInfo);
utype* cUBankDict(const utype *inParam, TCtrlInfo *errInfo);
utype* cDBankDict(const utype *inParam, TCtrlInfo *errInfo);
utype* cIBankDictHis(const utype *inParam, TCtrlInfo *errInfo);
utype* cIBankDictHisBak(const utype *inParam, TCtrlInfo *errInfo);

//岗位角色关系管理
utype* cQRoleGroupByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPositionRoleByPosRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPositionRoleRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPositionRoleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetPositionRoleByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cDPositionRoleByPosRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleDictByRoleFlag(const utype * inParam,TCtrlInfo *errInfo);

//SIM卡费用配置
utype* cQMaxResSellIdOfResSalePrice(const utype * inParam,TCtrlInfo *errInfo);
utype* cUResPriceFeeCodeById(const utype * inParam,TCtrlInfo *errInfo);
utype* cDResPriceFeeCodeById(const utype * inParam,TCtrlInfo *errInfo);
utype* cDResSellPriceById(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResPriceFeeCodeDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSalePriceByMulCol01(const utype * inParam,TCtrlInfo *errInfo);
utype* cQResSalePriceByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChannelClassByClassNameLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResSalePriceDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnGroupRelByCurrentLevel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChannelClassByClassCodeLike(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginSysCheckByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRandPwdByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRandPwd(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginRandPwd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUniCodeDefByGroupIdAndCodeClass(const utype * inParam,TCtrlInfo *errInfo);

utype* cQNextMonth(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUniCodeDefByCodeIdClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserPrcHisByIdNoAndPrcIdTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetNewRegMsgByIdSparty(const utype * inParam,TCtrlInfo *errInfo);

/*公告*/
utype* cQNoteReleaseLoginById(const utype * inParam,TCtrlInfo *errInfo);
utype* cINoteReleaseLoginHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cINoteReleaseLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNoteReleaseLoginByPK(const utype * inParam,TCtrlInfo *errInfo);

utype* cQOpenWebCtrl(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetLoginNoSX(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetBusiPrivsByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFunctionRelByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncListByQryCond(const utype * inParam,TCtrlInfo *errInfo);

utype* cQRentMachFavByCardCodeType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRentMachFavByCustIdType(const utype * inParam,TCtrlInfo *errInfo);
 /*1501*/
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
utype* cQOrganiseByID(const utype * inParam,TCtrlInfo *errInfo);

utype* cQTimeSub2(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRunStopTypeRelByOpRun(const utype * inParam,TCtrlInfo *errInfo);

utype* cQChannelInfoByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEleValuesByEleId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCssConFigByPubCodeEleIdValue(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cQTempPubDictElemlateByTepIdPubObj(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQNumSub(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQNumofDual(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*小区代码查询*/
utype* cQAreaDictByQryCond(const utype * inParam,TCtrlInfo *errInfo);

/*业务特权查询*/
utype* cQBusiPrivsByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBusiPrivsDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBusiPrivsDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDBusiPrivsDict(const utype * inParam,TCtrlInfo *errInfo);

/*根据父级角色查询所有子角色下的工号*/
utype* cQRoleLoginNoByQryCond(const utype * inParam,TCtrlInfo *errInfo);

/*查询角色产品认证关系信息*/
utype* cQRoleProdAuthenByQryCond(const utype* inParam, TCtrlInfo *errInfo);

/*查询角色的父级角色中是否有ESOP的顶级角色*/
utype* cQRoleParByRoleCode(const utype * inParam,TCtrlInfo *errInfo);

/*查询工号可以查看或者工号创建的公告*/
utype* cQNoteListByQryCond(const utype * inParam,TCtrlInfo *errInfo);

/*业务编码是否存在*/
utype* cQCntOfBusiCodeByBusiCode(const utype * inParam,TCtrlInfo *errInfo);
/*业务特权产寻*/
utype* cQBusiPrivsByBusiCode(const utype * inParam,TCtrlInfo *errInfo);
/*业务特权历史表*/
utype* cIBusiPrivsHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cQSonFuncByQryCond(const utype * inParam,TCtrlInfo *errInfo);

utype* cQParFuncByQryCond(const utype * inParam,TCtrlInfo *errInfo);

utype* cQFunctionRelByQryCond(const utype * inParam,TCtrlInfo *errInfo);

utype* cQPoliRegionByAreaCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBaseAreaHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDBaseAreaByCodeGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBaseAreaDict(const utype * inParam,TCtrlInfo *errInfo);
utype *cQBaseAreaByMul(const utype * inParam,TCtrlInfo *errInfo);
utype *cQBaseAreaByPage(const utype * inParam,TCtrlInfo *errInfo);
utype *cQCntOfBaseAreaByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseAreaByAreaCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cUTeleLoginRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTime14(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBUniCodeDefByClassGroupName(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSunShine(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSunShineByScode(const utype * inParam,TCtrlInfo *errInfo);
utype* cISunShine(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleInfoByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfRoleByMulCond(const utype * inParam,TCtrlInfo *errInfo);

/*费用落地对应的营业厅*/
utype* cQLoginGroupByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginGrpRelByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginGrpRel(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginAgentByRoleCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetChnGroupTownByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfChnGroupTownByPage(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginMsgDictByStaffId(const utype * inParam,TCtrlInfo *errInfo);

utype* cDChnClassRelByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChannelClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChannelClassByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUHasChildOfChnClassByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cURootDisOfChaClassByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChnClassRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChnClassRelByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChannelKind(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupRelByParGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChnClassRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChannelKindHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChannelClassHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGroupMacByMacAddress(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGroupMac(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGroupMacHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGroupMac(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupMacByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGroupMacByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupMacByQryCond(const utype * inParam,TCtrlInfo *errInfo);

utype* cIWlanHotSpotDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWlanHotSpotDictHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAreaBillDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAreaBillDictHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfWlanHotSpotDictByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWlanHotSpotDictByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfAreaBillByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAreaBillByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAreaBillByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWlanHotSpotDictByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAreaBillByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUWlanHotSpotByQryCond(const utype * inParam,TCtrlInfo *errInfo);

utype* cILoginMenuByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMenuHisByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginPdomTmp(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMenuHisByFun(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginMenuByFun(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginShortCutHisByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginShortCutByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginModuleHisByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginModuleByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginPdomTmp(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLgnGrpRelByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLgnGrpRelByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginGrpRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginGrpRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginGrpRel(const utype * inParam,TCtrlInfo *errInfo);

/*工号查询省级Group_Id*/
utype* cQChnGroupRelByParentLevelGrp(const utype * inParam,TCtrlInfo *errInfo);
/*查询bs_function_dict表全量数据*/
utype* cQFuncAllQry(const utype * inParam,TCtrlInfo *errInfo);

/*4A金库认证模式*/
utype* cI4AVerifyHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cI4AVerifyDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQ4AVerifyByFunctionCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cU4AVerifyDictByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cD4AVerifyDictByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQ4AVerifyDictByMul(const utype * inParam,TCtrlInfo *errInfo);


/*根据营业员工号查询值班经理工号*/
utype* cQLoginListByLoginRole(const utype * inParam,TCtrlInfo *errInfo);

/*计费批价优惠小区*/
utype* cILocationCodeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILocationCodeInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLocationCodeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cULocationCodeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLocationCodeInfoByCul(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginByGroupQry(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAgentDictHisByPhoneAndType(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAgentDictByPhoneAndType(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAgentDictHisByPhoneAndTypeAndLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntRoleByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
//工号角色权限(工号权限)
utype* cQLoginPopQry(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginPopCond(const utype * inParam,TCtrlInfo *errInfo);
//工号信息接口
utype* cQLoginKFQry(const utype * inParam,TCtrlInfo *errInfo);
//公告发布系统相关BC
utype* cQInfoPubByNameLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQInfoPubById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQInfoPubAttachmentByNoteId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncInfoPubByNoteId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQInfoPubReleaseById(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInfoPubHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInfoPubDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInfoPubAttachmentHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInfoPubAttachmentRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncInfoPubHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncInfoPubRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTitleContentOfInfoPub(const utype * inParam,TCtrlInfo *errInfo);
utype* cDInfoPubAttachmentById(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetInfoPubAttachmentId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncInfoPubByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQInfoPubReleaseByNoteGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInfoPubReleaseHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUInfoPubReleaseRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDInfoPubReleaseRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDInfoPubDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginReadInfoByNote(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginReadInfoByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginReadInfoByParGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInfoPubReleaseRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfInfoPubByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginReadInfoByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cQInfoPubReleaseByNoteId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetInfoPubByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFlagOfLoginReadInfoRc(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginReadInfoRc(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncInfoPubByGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetInfoPubByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginReadInfoListByNote(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginReadInfoCntByNote(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMsgByGroupAndLogin(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCrossDictByMutiP(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCrossDictByMuti(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCrossDictByMutiUser(const utype * inParam,TCtrlInfo *errInfo);


utype* cQChineseDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginYPopQry(const utype * inParam,TCtrlInfo *errInfo);

utype* cQNextTimeInControl(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAdminOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);

utype* cQUniCodeDefByCodeClassAndEndValue(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPublicRecordByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPublicRecord(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginIpLimitByLoginFlag(const utype * inParam,TCtrlInfo *errInfo);

utype* cQLoginSignatrue(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginSignatrue(const utype * inParam,TCtrlInfo *errInfo);

utype* cDAreaBillCodeDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAreaBillCodeDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAreaBillCodeDictHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAreaBillCodeByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAreaBillCodeByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfAreaBillCodeByPage(const utype * inParam,TCtrlInfo *errInfo);

utype* cQAdrolByStlevel(const utype * inParam,TCtrlInfo *errInfo);

utype* cIProdOpAuthen(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAfterLmtRuleNew(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGroupRelaTypeOfProdAuthenByProdOp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQProdOpAuthGrpByMulAuthGrpProdOp(const utype * inParam,TCtrlInfo *errInfo);
utype* cUProdAuthGrpInfoOfProdAuthenByProdOpAuthGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cIProdOpAuthGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetProdAuthenRelByAuthenGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfProdOpAuthenRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIProdOpAuthenRel(const utype * inParam,TCtrlInfo *errInfo);


#endif

