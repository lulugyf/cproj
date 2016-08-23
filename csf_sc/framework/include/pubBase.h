#ifndef __PUBBASEBC_H__
#define __PUBBASEBC_H__

#define RESULT_NUM_IN_PAGE 20

/////###################public BC #############################
utype* pubGetBaseAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* pPublicRight(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRegionByAddr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginGroupCmp(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pubGetBaseTime(const utype * inParam,TCtrlInfo *errInfo);
utype* pGroupTown(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//工号信息-yangsong
utype* cQLoginMsgDictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginPopedomHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRoleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMsgDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMsgHis(const utype * inParam,TCtrlInfo *errInfo);

//查询功能-zhangmeng
utype* cQFunctionByQryCond(const utype * inParam,TCtrlInfo *errInfo);

//角色权限管理-zhangmeng
utype* cIRolePdom(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRolePdomHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRolePdomByQryCond(const utype * inParam,TCtrlInfo *errInfo);

//工号角色--根据LOGIN_NO和ROLE_CODE查询
utype* cGetLoginRoleByLoginRole(const utype * inParam,TCtrlInfo *errInfo);

//查询权限
utype* cQPopedomByQryCond(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetChnGrpByGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginRoleRel(const utype * inParam,TCtrlInfo *errInfo);
/////###################public BP #############################

utype* cQLoginMsgTest(const utype * inParam,TCtrlInfo *errInfo);
/////####################工号信息管理######################
utype* pLoginNoAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginNoUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginNoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRolQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCntOfLoginMsgByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRoleRelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginRoleRelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPopedomByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginPopedomRelByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByIdValid(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginRoleByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pCreateLogin(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetLoginSerialByLoginPrefix(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginIpLimitDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginIpLimitDictByDelCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleDictByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginIpLimitDictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginPdomQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetLoginPopedomByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginPopedomByRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMsgByPageCount(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginMsgByLoginPrefix(const utype * inParam,TCtrlInfo *errInfo);

/////################### 权限管理 zhangmeng #####################
utype* cIPopedom(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFunction(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfFunctionDict(const utype * inParam,TCtrlInfo *errInfo);
utype* pFunctionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryPDOMList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProcedureAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cIProcedureDict(const utype * inParam,TCtrlInfo *errInfo);
utype* pDataItemAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cIDataObjItem(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDataItemByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* pDataItemQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQFuncDataItemByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncDataItem(const utype * inParam,TCtrlInfo *errInfo);
utype* pFuncDataItemAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetFuncList(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfFunctionByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* pCheckFunc(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQProcedureDictByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* pFuncProcQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetFuncDataByProc(const utype * inParam,TCtrlInfo *errInfo);
utype* pProcDataQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////#################### LoginCheck ############################
utype* cQLoginCheckByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginCheck(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginCheckbyLoginDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStatusOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTryTimesOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginCheckP(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetLoginMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetLoginCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLogintest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetLoginPdomListByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginPdomList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQLoginThemeByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThemeDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQThemeValueByThemeId(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetLoginTheme(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQRegionIpLmtByRegId(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetLoginModuleByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginModule(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginModule(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginModuleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginMdlCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetLoginShortInfoByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginShortcutByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUValueOrderOfLoginShortcut(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginMenuByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginTheme(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginThemeByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginThemeCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cILoginShortcut(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginShortcut(const utype * inParam,TCtrlInfo *errInfo);
utype* pShortcutCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cGetPdomSoundByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pPdomSoundQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cUStatusOfLoginCheckByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginOut(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cILoginThemeHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginShortcutHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cILoginMenuHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginMenuDictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMenu(const utype * inParam,TCtrlInfo *errInfo);
utype* pDLoginMenu(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginMenuCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* cGetAuthenInfoByFuncCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpAuthenRelByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpAuthenByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOpAuthGrpByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAuthenRelByAuthenGrp(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetOpAuthen(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginMdlQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pShortcutQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
int JudgeIP(const char *ipSrc, const char *ipDest);
int CheckIP(char *loginNo, const char *loginIP, int regionId);
utype* pLoginCheckTest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCntOfLoginModule(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFunctionOfLoginShortcut(const utype * inParam,TCtrlInfo *errInfo);

utype* cQOutSystemByOutSysId(const utype * inParam,TCtrlInfo *errInfo);
utype* pOutSysQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/////#################### 工号解锁 #######################
utype* pLoginUnLock(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cUTryTimesStatusOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);

/////#################### 密码修改 #########################
utype* pMdfLoginPwd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQLoginMsgDictHisByUpdateCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPasswdStatusOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExpireTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPasswdOfLoginMsg(const utype * inParam,TCtrlInfo *errInfo);

/////################### 密码重置#############################
utype* pRstLoginPwd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////#################### GroupTree ###########################
utype* pQuGroup(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetChnGrpRelByIdLevel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDownGroup(const utype * inParam,TCtrlInfo *errInfo);

utype* pBusiChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQCntOfChnGroupRelByTwoGrpId(const utype * inParam,TCtrlInfo *errInfo);
utype* pDeptRegionChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGroupId1(const utype * inParam,TCtrlInfo *errInfo);

/////################# 行政区域、标准地址查询 ##################
utype* cQPoliRegionByPar(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTeleRegionByPar(const utype * inParam,TCtrlInfo *errInfo);
utype* cQStandAddrByRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* cQStandAddrByParent(const utype * inParam,TCtrlInfo *errInfo);
utype* cQStandAddrByName(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetPoliRegList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetTeleRegList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStandAddrByRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStandAddrByName(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQRegionType(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetRegionType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/////################# 行政区域管理 ##################
utype* cGetPoliRegionByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetPoliRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIPoliRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* pPoliRegionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cDRegionRelByPReg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfStandAddrByPRegId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfPoliRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* pPoliRegionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# 管理区域管理 ##################
utype* cGetTeleRegionByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetTeleRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cITeleRegion(const utype * inParam,TCtrlInfo *errInfo);
utype* pTeleRegionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cDRegionRelByTReg(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfTeleRegionByPar(const utype * inParam,TCtrlInfo *errInfo);
utype* pTeleRegionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# 区域关系管理 ##################
utype* cGetRegRelInfoByIdRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetRegionRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIRegionRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pRegionRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cDRegionRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pRegionRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQRegRelType(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetRegionRelType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# 标准地址管理 ##################
utype* cGetStandAddrByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetStandAddr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIStandAddr(const utype * inParam,TCtrlInfo *errInfo);
utype* pStandAddrAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStandAddrUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# 业务组织管理 ##################
utype* pGroupAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cIChnGroupDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChnGroupRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pGroupUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cUBaseInfoOfChnGroupDict(const utype * inParam,TCtrlInfo *errInfo);
utype* pGroupQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetCntOfChnGrpByIdName(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChnGrpByIdName(const utype * inParam,TCtrlInfo *errInfo);
utype* pGroupTree(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetChnGrpRelByLevel(const utype * inParam,TCtrlInfo *errInfo);
utype* pGroupTreeT(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQChannelClassByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChannelKindByClassKind(const utype * inParam,TCtrlInfo *errInfo);

/////################# 业务组织审核 ##################
utype* pUnAuditQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetChnGrpRelByAuditFlag(const utype *inParam,TCtrlInfo *errInfo);
utype* pGroupAudit(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQChnGroupDictRelByHasChild(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAuditFlagOfChnGroupDict(const utype *inParam,TCtrlInfo *errInfo);
utype* cUHasChildOfChnGroupDict(const utype * inParam,TCtrlInfo *errInfo);

/////################# 工号角色管理 ##################
utype* pGrpLoginQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleTree(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQRoleDictByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginRoleQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetCntOfLoginRoleRelByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* pRelAddChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetLoginRoleByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfRoleByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfRoleByLoginRole(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginRoleAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cDLoginRoleRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFunctionByOneParent(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfLoginMenuByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMenuDictByShowOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginMenuDictHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMenuDictByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginMenuDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncCodeByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginModuleDictByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginModuleDictHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginShortcutDictByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginShortcutDictHis(const utype * inParam,TCtrlInfo *errInfo);

/////################# 工号权限管理 ##################
utype* pFuncDomChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetLoginPopedomByAll(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginDataPdomByAll(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginPopedomByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginPEdomByPEdomCode(const utype * inParam,TCtrlInfo *errInfo);
utype* pDataDomChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPopeDomCfm(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cILoginPopedom(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPrivsOfLoginPdomRelByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginPopedomRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pubLoginMenuManage(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQFunctionByParent(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncPEdomByParCode(const utype * inParam,TCtrlInfo *errInfo);

/////################# 角色管理 ##################
utype* cGetRoleInfoByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* pRoleTreeList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIRoleMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* pRoleAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cUChildUseFlagOfRoleByRar(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginRoleByRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleHisBakByChild(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRolePdomHisBakByRoleDown(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRolePdomByDelCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRoleRelByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* pRoleUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# 角色关系管理 ##################
utype* cGetRoleRelByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* pRoleRelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetRoleRelByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRoleRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pRoleRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cDRoleRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pRoleRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# 角色权限关系管理 ##################
utype* pRoleFuncQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleDataQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRoleLogin(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRolePdom(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRolePdomCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIRolePdomHisByRoleUp(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRolePdomByRoleUp(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPrivsOfRolePdomRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntRolePdomByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRolePdomByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFuncByPar(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetDataByFunc(const utype * inParam,TCtrlInfo *errInfo);

/////################# 工位信息管理 ##################
utype* cGetStationInfoByStationId(const utype * inParam,TCtrlInfo *errInfo);
utype* pStationList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cIWorkStationHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWorkStation(const utype * inParam,TCtrlInfo *errInfo);
utype* pStationAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cCheckWorkStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWorkStationHisBakByChild(const utype * inParam,TCtrlInfo *errInfo);
utype* cUChildStatusOfWorkStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStationInfoOfWorkStation(const utype * inParam,TCtrlInfo *errInfo);
utype* pStationUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQLoginStationByStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRelInfoByLoginStation(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginStatQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetRootStationByStationId(const utype * inParam,TCtrlInfo *errInfo);

/////################# 工号工位关系管理 ##################
utype* cILoginStationHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cILoginStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRelTimeByLoginStation(const utype * inParam,TCtrlInfo *errInfo);
utype* cDLoginStation(const utype * inParam,TCtrlInfo *errInfo);
utype* pLoginStationCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQLoginMsgByStation(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStatLoginMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cGetStationLoginList(const utype * inParam,TCtrlInfo *errInfo);
utype* pStationLoginList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# 矩阵关系查询 ##################
utype* pLoginRoleMtx(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQRoleDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetLoginRoleByValidFlag(const utype * inParam,TCtrlInfo *errInfo);
utype* pRolePdomMtx(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* cQFunctionDcit(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRolePdomMatrixByRoleCode(const utype * inParam,TCtrlInfo *errInfo);

/////################# 工号关系管理 ##################
utype* cDTeleLoginRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTeleLoginRelByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cITeleLoginRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cITeleLoginRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUseFlagOfTelephonist(const utype * inParam,TCtrlInfo *errInfo);
utype* cITelephonistHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetTelephonistByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetTeleLoginRelByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfTelephonistByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* pTelephonistQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////###############功能树接口 ########################
utype* cGetFuncListByFuncType(const utype * inParam,TCtrlInfo *errInfo);
utype* pQryFuncList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////###############员工信息管理 ########################
utype* cIStaff(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfStaff(const utype * inParam,TCtrlInfo *errInfo);
utype* pStaffAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStaffUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////###############员工信息管理 ########################
utype* cQPositionByMulCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPosition(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPosition(const utype * inParam,TCtrlInfo *errInfo);
utype* pPositionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPositionQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPositionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*static lib begin*/

/*static lib end*/


#endif
