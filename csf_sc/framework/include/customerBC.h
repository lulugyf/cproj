#ifndef __CUSTOMERBC_H__
#define __CUSTOMERBC_H__

utype* cQGrpDeptInfoByCustIdDepname(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMonthQry(const utype * inParam, TCtrlInfo *errInfo);
utype* cQStaffGroupIdByLoginNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cILocusMsgByIdAccept(const utype * inParam, TCtrlInfo *errInfo);
utype* cULocusMsgByIdAccept(const utype * inParam, TCtrlInfo *errInfo);
utype* cQLocusMsgByIdAccept(const utype * inParam, TCtrlInfo *errInfo);
utype* cQListRelMastId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQListRelRecByStatus(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCntOfListRelRecByQryCond(const utype * inParam, TCtrlInfo *errInfo);
utype* cIGrpTarGetListExtInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cIGrpTarGetListExtHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cIGrpTarGetListExtHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cUGrpTarInfoListById(const utype * inParam, TCtrlInfo *errInfo);
utype* cUGrpTarExtInfoListById(const utype * inParam, TCtrlInfo *errInfo);

utype* cUCustNameTdtyById(const utype * inParam, TCtrlInfo *errInfo);
utype* cUEsopWorkCustInfoById(const utype * inParam, TCtrlInfo *errInfo);
utype* cQChnGroupByRegionId(const utype * inParam, TCtrlInfo *errInfo);
utype* cIGrpKeymanMemHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cUConKeyImpManInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQConKeyManTerminInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQConKeyManBaseInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQConMemListInfo(const utype * inParam, TCtrlInfo *errInfo);

utype* cQPartRegionByregionId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQChnGroupByRegionId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQGrpCustNameByNameQry(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCntOfGrpCustNameInfoByName(const utype * inParam, TCtrlInfo *errInfo);
utype* cGetCntOfCustIccidByQrycond(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCustUserInfoByIdIccid(const utype * inParam, TCtrlInfo *errInfo);

utype* cQCustApproveByLoNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQADCGrpCustInfoByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQTradeCodeByTrAndPt(const utype * inParam, TCtrlInfo *errInfo);
utype* cQBlackListPhoneInfoByBlackNoRow(const utype * inParam, TCtrlInfo *errInfo);
utype* cUAddIDExtOFCustInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberInfoByIdNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustResOrdHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cDCustResOrdInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCustResOrdInfoByResourceNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCustResOrdInfoByIccid(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustResOrdInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustResOrdInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQOLFeeByOrderId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQGrpCustImpManByIdNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQGrpCustMemMsgByIdNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cIGrpCustMemMsgHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cUGrpCustMemMsgByIdNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cIGrpCustMemMsgInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cIGrpCustMemMsgHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cDGrpCustMemMsgInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cUGrpCustImpMemByIdNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cUBbossGrpByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cIBbossGrpHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cUCompeByGrpMemInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cUCompeNoByGrpMemInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cICompeByMemInfoHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cICompeNoByMemInfoHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cUCustLevelByGrpCom(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustInfoLevelHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cUCustImpManMemByIdNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cUCustManMemByIdNo(const utype * inParam, TCtrlInfo *errInfo);


utype* cIGrpOtherMemberHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cIGrpOtherMember(const utype * inParam, TCtrlInfo *errInfo);
utype* cIGrpCustImpManHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cUGrpCustImpManByIdNo(const utype * inParam, TCtrlInfo *errInfo);

utype* cIGrpOtherMemberHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpOtherMember(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustMngObjInfoByIdCust(const utype * inParam, TCtrlInfo *errInfo);
utype* cDCustManagerRelByCustOrder(const utype * inParam, TCtrlInfo *errInfo);
utype* cQUniCodeInfoByClassAndGroup(const utype * inParam, TCtrlInfo *errInfo);
utype* cQUserHisInfoByIdNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQUserSimHisByIdNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cUEsopCustInfoById(const utype * inParam, TCtrlInfo *errInfo);
utype* cUEsopPersonCustById(const utype * inParam, TCtrlInfo *errInfo);
utype* cUEsopContactCustById(const utype * inParam, TCtrlInfo *errInfo);
utype* cQLineNumSeque(const utype * inParam, TCtrlInfo *errInfo);

utype* cQCustViewHisByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQContacrViewHisByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQBsBankdictByCodeValue(const utype * inParam, TCtrlInfo *errInfo);

utype* cQCustInfoByIccid(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCustInfoByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCustContactInfoByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustAddInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustAddInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustContactInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustContactInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cIPersonalCustInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cIPersonalCustInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustWorkInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustWorkInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustEduInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustEduInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustConsumeInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustConsumeInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cIHomeCustInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cIHomeCustInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cIPartyCustInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cIPartyCustInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCntOfBlackListInfoByIccid(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCustContactInfoByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustInfoHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cUStatusOfCustInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cUCustLevelOfCustInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCustInfoByStatusCode(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCntOfBlackListPhoneByPhoneNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cDBlackListInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cDBlackListPhone(const utype * inParam, TCtrlInfo *errInfo);
utype* cIBlackListInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cIBlackListInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cIBlackListInfoHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cIBlackListPhoneInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cIBlackListPhoneInfoHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cIBlackListPhoneInfoHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cQBlackListInfoByBlackNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQBlackListInfoByIccid(const utype * inParam, TCtrlInfo *errInfo);
utype* cQBlackListInfoByBlackType(const utype * inParam, TCtrlInfo *errInfo);
utype* cQBlackListPhoneInfoByBlackNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cICustIdentifyInfoHisBak(const utype * inParam, TCtrlInfo *errInfo);
utype* cUCustPwdOfCustIdentifyInfo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCustInfoByIdIccid(const utype * inParam, TCtrlInfo *errInfo);
utype* cQBlackListPhoneInfoByPhoneNo(const utype * inParam, TCtrlInfo *errInfo);
utype* cQPerCustInfoByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCustManagerRelByCustId(const utype * inParam, TCtrlInfo *errInfo);
utype* cQGrpCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustExtInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustIdentifyInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustIdentifyInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustCertScanInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustCertScanInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustInfoByUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByIdType(const utype * inParam,TCtrlInfo *errInfo);
utype* CustCertScanInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* CustCertScanInfoHis(const utype * inParam,TCtrlInfo *errInfo);

//客户管理组
utype* cQGrpCustExtInfoByConnctTel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOtherNetManager(const utype * inParam,TCtrlInfo *errInfo);
utype* cDOtherNetProduct(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetFieldesByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetNocFieldesByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustApproveRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustApproveRecByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustApproveRecByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCustApproveRecByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustContactHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustWorkInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpAddrListInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpAddrListInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustExtHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustExtInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpDeptInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpDeptInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOtherNetManager(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOtherNetManagerhis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOtherNetManagerHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOtherNetProduct(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOtherNetProductHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIOtherNetProductHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIPersonalCustInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustContactInfoByIdOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustWorkInfoByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustExtInfoByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustInfoByUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOtherNetManagerByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOtherNetProductByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cUContactInfoOfCustContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEvaluteInfoOfGrpCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOfficePhoneOfCustContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOtherNetInfoOfGrpCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOtherNetManager(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOtherNetProduct(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPersonalCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUnitInfoOfCustWorkInfo(const utype * inParam,TCtrlInfo *errInfo);


utype* cQCustInfoByCustName(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpInfoOfCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDAgreementInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAgreementInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAgreementInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIAgreementInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustITHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIHomeCustInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgreementInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustManagerRelByIdOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustRelByIdRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustITByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQHomeCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAgreementInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBaseInfoOfGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBusiInfoOfGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustAddressOfCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCustITInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUHomeExtOfHomeCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpInfoOfCustWorkInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpInfoOfGrpCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpInfoOfGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpInfoOfHomeCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTelBudgetOfGrpCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByTypeName(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpInfoOfCustContactInfoByIdOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAddressIdOfCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUAddrIdOfCustContactInfoByOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cUNameOfCustContactInfoByOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOpInfoOfCustContactInfoByOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cUConPhoneOfCustContactInfoByOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustNameOfCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUIccidInfoOfCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustRelHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStatusOfCustRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustRelByIdCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUApproveInfoOfCustApproveRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCustInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustRoelOfCustRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustRoleDictByRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfBlackListInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCustUserRelByIdRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetNumofCustlist(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgreementInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByIdGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustManagerByIdOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTime10(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCustExtInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustExtInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustConsumeInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustConsumeInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustConsumeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustWorkInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustEduInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustEduInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustEduInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustSpcdayInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustSpcdayInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustSpcdayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustSpcdayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustSpcdayInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPersCustInfoOfCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPersCustInfoOfPersonalCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustManagerRelByStaffId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustRelByMasId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUMbrInfoOfCustRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfGrpInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQHomeCustInfoByHomeId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByIcc(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetHomeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfHomeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfPerInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetPerInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cDGrpCustMemberInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustMemberInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustMemberInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustMemberInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberByRoleId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberByPk(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUMbrInfoOfGrpCustMember(const utype * inParam,TCtrlInfo *errInfo);

utype* cICustVisitInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustVisitInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustVisitInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustVisitInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCustVisitByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustVisitInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);

utype* cDCustContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustSpcdayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustRelTypeDictByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustRoleDictByCodeType(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDocumentInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDocumentInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPhoneNoOfDocumentInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUValidOfDocumentInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDocumentInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDocumentInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfDocumentInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByNameType(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustCreditRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCustInfoByTypeName(const utype * inParam,TCtrlInfo *errInfo);

utype* cUCfmOneOfCustCreditRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCfmTwoOfCustCreditRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCreditOfGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustCreditRecByCfm(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustCreditRecByCustId(const utype * inParam,TCtrlInfo *errInfo);

utype* cDGrpCustMemRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberRoleByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberRoleById(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustMemRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustMemRoleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustMemRoleHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cURoleCodeOfGrpCustMemRole(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfCustCreditRecByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustCreditRecByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustLoveOfPersCustInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetGrpCustMemInfoByIdRole(const utype * inParam,TCtrlInfo *errInfo);
utype* GrpCustMemberInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpCustMemberInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustCreditRecByOptsn(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustCreditRecHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustCreditRecHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfCustInfoByManager(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCustInfoByManager(const utype * inParam,TCtrlInfo *errInfo);
utype* cIExpCustInfoRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByIccidLeveType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByNameLevelType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExpCustInfoRdByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCfmOfExpCustInfoRdByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExpCustInfoRdByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustApproveRecHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfExpCustInfoRdByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustApproveRecHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPerNumOfGrpCustExtByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberRoleById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberRoleByCustRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustManagerRelByStaffLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustContactInfoByCustContact(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCustCertScanInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustCertScanInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustCertScanInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpOtherMemberByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCustContactByCustPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfGrpCustMemberByIdRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpCustMemberInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfGrpCustMemberInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberRoleByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExpCustInfoRdByxCfmStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCfmOfExpCustInfoRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMaxDocIdOfDocumentInfoByDocId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQExpCustAddByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cIExpCustAdd(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCustRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustITInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustITInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustContactInfoByContactOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEXPDateOfGrpCustMemberInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByNameTypeLike(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoHisByIdUpdateTypeTime(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpDeptInfoByCustIdAndParentId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpDeptInfoByGrpDeptId(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpDeptInfoByParentId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpDeptInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpDeptInfoByGrpDeptId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpDeptInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);

utype* cUStaffLoginOfCustManagerByIdOrder(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStaffLoginOfCustMngObjByIdCust(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStaffLoginOfCustManagerByCustLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustManagerRelHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustManagerRelByCustLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustMngObjByIdCust(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberRoleByCustRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustMngObjByStaffLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfSpecialListInfoByPhoneNo1(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAdcUserInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);


//客户管理接口

utype* cQSendGiftRdByIdGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cISendGiftRd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfSendGiftRdByNoGroup(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserPrcByIdMainA(const utype * inParam,TCtrlInfo *errInfo);

//集团统付管理

utype* cQCustInfoByIccidType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByCustType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberByIdNoCustId(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfGrpOtherMemberInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOrderInfoByCustIdAndHandleTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberByPK(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOperatorPhoneOfGrpCustByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfUserInfoByQrycond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUserInfoByQrycond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUIccIdOfCustContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSecOBGrpCustChkByUnitID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByTypeIccid(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfCustContactByCustPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberRoleByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoHisByIdUpdateTypeTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQLoginMsgDictByContactPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfContactMsgByChnBegin(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfCustContactInfobyCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByNameId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpDeveIfByCustIdAndAct(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustManagerRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSecOBGrpCustInterByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOBGrpCustInfoByECCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cISecOBGrpCustInterhisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSecGrpInfoOfSecOBGrpCustInter(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSecOBGrpCustInterByECCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cISecOBGrpCustInter(const utype * inParam,TCtrlInfo *errInfo);
utype* cISecOBGrpCustInterhis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOBGrpCustInfoByECName(const utype * inParam,TCtrlInfo *errInfo);
utype* cDSecOBGrpCustInterByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOrderInfoByIdNoAndHandleTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustSpcDayInfoByIDPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustContactInfoByIDPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustCareFlagOfCustManagerByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCompetitionInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCompetitionInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCompetitionInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCompetitionInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCompetitionInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpIncomeByCustIdAndAct(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpOweFeeByCustIdAndAct(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpOtherMbrByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustLevelOfCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCardTypeOfUserInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cIDobchiCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDobchiExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIDobchiKeyPersonList(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpCustInfoByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBak2OfGrpExtInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cIGrpDeptMbr(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpDeptMbrByIdEff(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpDeptMbrByIdEff(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpDeptMbrByIdEff(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpDeptMbrHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpDeptMbrHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustInfoHisByIdUpdateTypeTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustResOrdByResTypeExp(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCreditOfGrpCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMbrPortfolioIfByCustIdAndAct(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustLvlHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustLvl(const utype * inParam,TCtrlInfo *errInfo);
utype* cQHomeCustInfoByMasCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEsopMissionExpInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEsopMissionExpInfoByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cDEsopMissionExpInfoByCustID(const utype * inParam,TCtrlInfo *errInfo);

utype* cQInterBasicInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInterBasicInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUInterBasicInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInterBasicInfohis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIInterBasicInfohisBak(const utype * inParam,TCtrlInfo *errInfo);

utype* cQOrderInfoHisByCustIdAndHandleTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQOrderInfoHisByIdNoAndHandleTime(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAllSubGrpDept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCountOfSecOBGrpCustInter(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustMngObjInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByTypeNamePartition(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUserGroupMbrInfoByGroupType(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfDobChiCustInfobyECCode(const utype *inParam, TCtrlInfo *errInfo);
utype* cQSecOBGrpCustChkBySecECCode(const utype *inParam, TCtrlInfo *errInfo);
utype* cQCntOfLoginQryRdByCodeTime(const utype *inParam, TCtrlInfo *errInfo);
utype* cICustMngObjInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype* cQFeeCodeDictByFeeCode(const utype *inParam, TCtrlInfo *errInfo);
utype* cQScoreUseByGiftidTimeBakRegion(const utype *inParam, TCtrlInfo *errInfo);
utype* cIServiceNoInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* cIServiceNoInfoHis(const utype *inParam, TCtrlInfo *errInfo);
utype* cQGrpCustMemberRoleByCustIdRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAttrOpCodeRelByAttrName(const utype *inParam, TCtrlInfo *errInfo);
utype* cQAttrOpCodeRelByAttrDesc(const utype *inParam, TCtrlInfo *errInfo);
utype* cQMaxAttrIdofAttrOpCodeRel(const utype *inParam, TCtrlInfo *errInfo);
utype* cQScoreUseByGiftidTimeBakRegion(const utype *inParam, TCtrlInfo *errInfo);
utype* cIAttrOpCodeRel(const utype *inParam, TCtrlInfo *errInfo);
utype* cUAttrOpCodeRelByAttrName(const utype *inParam, TCtrlInfo *errInfo);
utype* cQCustInfoByCustNamePartition(const utype *inParam, TCtrlInfo *errInfo);
utype* cQCntOfGrpCustLvl(const utype *inParam, TCtrlInfo *errInfo);
utype* cQCustInfoByLimitCntIccid(const utype * inParam,TCtrlInfo *errInfo);

utype* cITobbBossCustNumberSyn(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTobBossECInfoSynByCustomerProvinceNumber(const utype * inParam,TCtrlInfo *errInfo);
utype* cITobBossECInfoSyn(const utype * inParam,TCtrlInfo *errInfo);
utype* cITobbBossCustomerManagerInfosyn(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfUserTransByToItemsEff(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetUserTransByToItemsEff(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPubExtInfoByStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPubExtInfoRdByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfPubExtInfoRdByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQPubExtInfoRdByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cIResInter(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetMaxIdOfGrpTarGetListInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpTarGetListInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpTarGetListInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpTarGetListInfoByCustName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpTarGetListInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpTarGetListInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpTarGetListInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpTarGetListInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpTarGetListInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDListGrpMeb(const utype * inParam,TCtrlInfo *errInfo);
utype* cIListGrpMeb(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfListGrpMebByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQListGrpMebByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQListGrpMebByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUListGrpMebByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cIListGrpMebHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIListGrpMebHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDListGrpRelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIListGrpRelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfListGrpRelInfoByMasId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfListGrpRelInfoBySlaUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQListGrpRelInfoByMasCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQListGrpRelInfoByMasIdSlaUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQListGrpRelInfoBySlaUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUListGrpRelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIListGrpRelInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIListGrpRelInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTradeCodeByParTradeCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTradeCodeByTradeCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStaffLoginOfGrpListById(const utype * inParam,TCtrlInfo *errInfo);


utype* cGetTobbBossCustNumberSynByDealRsp(const utype * inParam,TCtrlInfo *errInfo);
utype* cUDealFlagOfTobbBossCustNumberSynByLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustCdOfCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);

utype* cIUserInternetInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserInternetInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUErrDateOfUserInternetByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginDateOfUserInternetByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cULoginErrNumOfUserInternetByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPassOfUserInternetInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPetNameOfUserInternetInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserInternetInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserInternetInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfUserLoginNetByIdLogin(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserLoginNet(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserLoginNetByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUStatusLogoutOfUserLoginNetByIdStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTopNumOfDoucumentInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpTarGetListInfoByExport(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTradeCodeByTwo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBlackListPhoneInfoByBlackNoPhoneNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCustInfoByGrpCustName(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustNameInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCustNameInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpCustExtInfoByMasterPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCmWhiteListByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCmWhiteListByProvPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cICmWhiteList(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCmWhiteByPhoneProv(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCmWhiteList(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWhiteUserInfoByUser(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWhiteUserInfoByGrpTel(const utype * inParam,TCtrlInfo *errInfo);
utype* cIWhiteUserInfoByGrpMas(const utype * inParam,TCtrlInfo *errInfo);
utype* cDWhiteUserInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWhiteUserInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICmWhiteListHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICmWhiteListHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQWhiteUserInfoByPage(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetCntOfBlackListInfoByIccid(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetBlackListInfoByIccidPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBBOSSGrpCustinfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBBOSSGrpCustinfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBBOSSGrpCustKeyMemInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBBOSSGrpCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserBillpostInfo(const utype *inParam, TCtrlInfo *errInfo);
//经办人信息
utype* cICustoperatorInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustoperatorInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUserBillPostInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBillPostInfoByIDNO(const utype * inParam,TCtrlInfo *errInfo);
//集团附属信息表
utype* cQGrpCustAttrByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustAttrHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cULeaderTypeOfGrpCustAttrInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustAttrInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustAttrInfo(const utype * inParam,TCtrlInfo *errInfo);

utype* cUPolicyOfCustvistInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUInfoLeverOfCustvistInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUIncomenumOfCustvistInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUnionnumOfGrpCustComInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUOthernumOfGrpCustComInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTelcomnumOfGrpCustComInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUSpiritnumOfGrpCustComInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCustOpreateByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cULinkmannameOfCustOpreateByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cULinkmanIdTypeOfCustOpreateByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cULinkmanIdIccidOfCustOpreateByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cULinkmanPhoneOfCustOpreateByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cULinkmanTitleOfCustOpreateByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustoperatorInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpstructureByQryCond(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpCustTelFeeInfoByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustTelFeeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustTelFeeInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustTelFeeInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCustTelFeeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpstructureChild(const utype * inParam,TCtrlInfo *errInfo);
//骚扰用户名单查询
utype* cQSpecialListInfoByMulCon02(const utype * inParam,TCtrlInfo *errInfo);

//集团审核员管理
utype* cQGrpCustAuditerInfoByCustID(const utype * inParam, TCtrlInfo *errInfo);
utype* cGetAuditerLoginMsgByPageCount(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetAuditerLoginMsgByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustAuditerInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustAuditerInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustAuditerInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpCustAuditerInfoByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustAuditerInfo(const utype * inParam,TCtrlInfo *errInfo);

//批量修改集团客户状态
utype* cUGrpCustInfoStatusByCustId(const utype * inParam,TCtrlInfo *errInfo);

//目标集团录入
utype* cIGrptargetlistRec(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrptargetlistRecHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpTarGetListRecByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpTarGetListRecByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpTarGetListRecById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustArchresInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCustArchresInfoByID(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCustArchresInfoByID2(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrptargetlistRecById2(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrptargetlistRecHisBak(const utype * inParam,TCtrlInfo *errInfo);

//目标集团审核
utype* cQGrpTarGetListInfoByQryCond2(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCountOfGrpTarGetListInfoByQryCond2(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrptargetlistRecById(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpTarGetOrig(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCustArchresInfoByUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrptargetlistRecById(const utype * inParam,TCtrlInfo *errInfo);

utype* cICustMngObjInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);

utype* cUBaseInfoOfGrpCustInfo2(const utype * inParam,TCtrlInfo *errInfo);
utype* cUUnionNetgNumOfGrpCustComInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUMobleSumNumOfGrpCustComInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);

utype* cUCustResOrdInfoByResourceNo(const utype * inParam,TCtrlInfo *errInfo);

//目标集团转在网申请
utype* cGetCntOfGrpTarGetListInfoByQryCond2(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpTarGetListExtInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfGrpCustNameByNameId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpTarGetListInfoByQryCond2(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpCustNameByNameId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIListGrpRelrecHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIListGrpRelrec(const utype * inParam,TCtrlInfo *errInfo);

//目标集团转在网审核
utype* cIListGrpRelrecHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUListGrpRelrec(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGetListGrpRelRecByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetListGrpRelRecByQryCond(const utype * inParam,TCtrlInfo *errInfo);
/*接口*/
utype* cQCustCertScanInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByCustCd(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBlackDelRdByIccid(const utype * inParam,TCtrlInfo *errInfo);
//ADC集团信息管理
utype* cQCntOfADCGrpCustInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cIADCGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQADCGrpCustInfoByAcceptAndECID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQADCGrpCustInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfADCGrpCustInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cIADCGrpCustInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIADCGrpCustInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUADCGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDADCGrpCustInfoByAcceptAndECID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustIdentifyInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustInfoByLicenseAndCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cQADCGrpCustInfoByECID(const utype * inParam,TCtrlInfo *errInfo);
//EC信息管理
utype* cQBBOSSGrpCustInfoByCustomerId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBBOSSGrpCustInfoByCustomerParentId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBBOSSGrpCustInfoByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBBOSSGrpCustInfoByCustomerId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBBOSSGrpCustKeyMemInfoByCustomerId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBBOSSGrpCustExtInfoByCustomerId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustmoerCMCCPrdInfoByLoginAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustmoercmccprdInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBBOSSGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserGroupByGroupType(const utype * inParam,TCtrlInfo *errInfo);

//esop集团客户-集团客户信息
utype* cQEsopGrpCustInfoByUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQContactPhoneByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberNumByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEsopCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUEsopGrpCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustMemberByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQStaffInfoByUnintId(const utype * inParam,TCtrlInfo *errInfo);

//ESOP后台接口
utype* cGetEsopGrpCustInfoRecent(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntListNumByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntBirthdayOfImpManByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetBirthdayOfImpManByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntGrpMeb(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpMeb(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpMemberMsg(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpMemberMsgHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpMemberMsgHisBak(const utype * inParam,TCtrlInfo *errInfo);

utype* cIGrpKeyFamilyHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpKeyFamilyInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEsopKeyFamByPhNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpKeyFamilyHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpKeyFamilyInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpKeyFamilyInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEsopOfCustByPhoneCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEsopOfCustByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpKeymanInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpKeymanInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpKeymanInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpKeymanInfoByPhone(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetEsopOfCustByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEsopOfCustByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntNumRegionByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMemInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUMemInfoByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIMemInfoHisByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetEsopAttenByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEsopAttenByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetEsopNoAttenByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEsopNoAttenByQryCond(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustManagerHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCustManagerByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustByLicense(const utype * inParam,TCtrlInfo *errInfo);

//潜在集团转在网
utype* cQListGrpRelRecByMSId(const utype * inParam,TCtrlInfo *errInfo);

//投诉指引接口
utype* cQComDetailByComCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQComDetailByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);

//一卡多号设置BC
utype* cQUserMulsimCmdInfoByMainId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQUserMulsimCmdInfoBySubId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUsermulsimcmd(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUsermulsimcmdHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUsermulsimcmdHisByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cDUsermulsimcmd(const utype * inParam,TCtrlInfo *errInfo);
//ESOP获取服务日志填写界面关联客户列表接口
utype* cQEsopOfCustBySerNoUsrName(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustNameByUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetBirthOfImpManByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntBirthOfImpManByLoginNo(const utype * inParam,TCtrlInfo *errInfo);

//同步oneboss
utype* cITOBBBOSSCUSTNUMBERSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cITOBBOSSECINFOSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cITOBBBOSSCUSTOMERMANAGERINFOSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cITOBBBOSSKEYPERSONINFOSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cITOBBBOSSEXTINFOSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cITOBBBOSSCMCCPRDLISTSYN(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpCustInfoByLicenseNumber(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustInfoByLicenseNumber(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEsopGrpCustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);

/*查询8号键功能*/
utype* cQCntOfMebRightKeyByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetCntOfBBOSSGrpCustByParentId(const utype * inParam,TCtrlInfo *errInfo);

//查询集团客户信息
utype* cQCntGrpCustByLicenseID(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpCustByLicenseID(const utype * inParam,TCtrlInfo *errInfo);

/*集团红名单*/
utype* cQCustSpeciallistInfoById(const utype * inParam,TCtrlInfo *errInfo);

utype* cICustSpeciallistInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustSpeciallistInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustSpeciallistInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustSpeciallistInfoHisbak(const utype * inParam,TCtrlInfo *errInfo);

/*插入酒店通客户接口表*/
utype* cIGrpCustCmdDayInfo(const utype * inParam,TCtrlInfo *errInfo);

/*合同到期提醒*/
utype* cQAgreementByCompleteTime(const utype * inParam,TCtrlInfo *errInfo);
/*目标集团备份信息表*/
utype*  cIGrpTargetorigInfoByMonth(const utype * inParam,TCtrlInfo *errInfo);

/*临时保存工号信息*/
utype* cITmpLoginNo(const utype * inParam,TCtrlInfo *errInfo);

/*EC客户管理*/
utype* cIBBOSSGrpCustInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBBOSSGrpCustKeyMemInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBBOSSGrpCustExtInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cICustmoercmccprdInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDBBOSSGrpCustinfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIBBOSSGrpCustKeyMemInfoHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBBOSSGrpCustKeyMemInfo(const utype * inParam,TCtrlInfo *errInfo);
/*集团网厅临时接口*/
utype* cQSpaCustInfoByUnitID(const utype * inParam,TCtrlInfo *errInfo);

utype* cQBlackListDayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDBlackListDayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfBlackListDay(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetBlackListDay(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBlackListDay(const utype * inParam,TCtrlInfo *errInfo);

/*开关机查询接口*/
utype* switchHLRQuery(const utype * inParam,TCtrlInfo *errInfo);
utype* switchINFOQuery(const utype * inParam,TCtrlInfo *errInfo);
utype* switchQuery(const utype * inParam,TCtrlInfo *errInfo);

utype* cIWsndcmdManual(const utype * inParam,TCtrlInfo *errInfo);

/*集团清单分析接口*/
utype* cQCntOfGrpTargetByStatus(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpTarget(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpTargetByRegionCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpTargetByRegionCol(const utype * inParam,TCtrlInfo *errInfo);
/*判断批量导入客户是否存在重复*/
utype* cQGrpTarGetListInfoIsRepeat(const utype * inParam,TCtrlInfo *errInfo);
//黑名单自动删除
utype* cAutoDelBlackList(const utype * inParam,TCtrlInfo *errInfo);
utype* cAutoDelBlackListByIccid(const utype * inParam,TCtrlInfo *errInfo);
utype* cAutoIBlackListHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cAutoIBlackListHisByIccid(const utype * inParam,TCtrlInfo *errInfo);
utype* cAutoQBlackList(const utype * inParam,TCtrlInfo *errInfo);
utype* cAutoQCustInfoByIccid(const utype * inParam,TCtrlInfo *errInfo);
utype* cAutoQTime(const utype * inParam,TCtrlInfo *errInfo);
//3914 BBOSS发起接口 查询一级BOSS接口表信息
utype* cQTOBBBOSSCUSTNUMBERSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTOBBBOSSCMCCPRDLISTSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTOBBBOSSCUSTOMERMANAGERINFOSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTOBBBOSSEXTINFOSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTOBBBOSSKEYPERSONINFOSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cQTOBBOSSECINFOSYN(const utype * inParam,TCtrlInfo *errInfo);
utype* cUBBOSSGrpCustInfoByECID(const utype * inParam,TCtrlInfo *errInfo);
utype* cUTOBBBOSSCUSTNUMBERSYNByAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfBBOSSGrpCustByCustomerId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfBBOSSKeyMemByCustomerId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfBBOSSGrpCustExtByCustomerId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfBBOSSCMCCByCustomerId(const utype * inParam,TCtrlInfo *errInfo);
//3928 ESOP集成功能-清单客户批量修改
utype* cBatUGrpTargetListExtInfoById(const utype * inParam,TCtrlInfo *errInfo);
utype* cBatUGrpTargetListInfoById(const utype * inParam,TCtrlInfo *errInfo);
//3912 ESOP集成功能
utype* cQGrpTarGetListExtInfoACById(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpTarExtInfoListACById(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCntOfBlackListInfoByBlackType(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCustResOrdInfoByOpcode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIUserLoginMsgInfo(const utype * inParam,TCtrlInfo *errInfo);
//ESOP关注客户功能  查询领导下属客户经理
utype* cQCustManagerByRoleCode(const utype * inParam,TCtrlInfo *errInfo);

//龙治昌小练习  根据客户ID查询信息
utype* cQctcustinfoBycustid(const utype * inParam,TCtrlInfo *errInfo);
//龙治昌    根据集团客户ID查询集团客户成员信息
utype* cQGrpCustMemberByGrpCustId(const utype * inParam,TCtrlInfo *errInfo);
//龙治昌   根据GroupId 查询集团客户的区域类型
utype* cGetChnGrpRelByGroupId(const utype * inParam,TCtrlInfo *errInfo);
//3701模块集团客户语音收入信息管理模块
utype* cQCtCustInComeInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCtCustInComeInfoByIdIccid(const utype * inParam,TCtrlInfo *errInfo);
utype* CICtCustInComeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQctCustInComeInfoByCount(const utype * inParam,TCtrlInfo *errInfo);
utype* cDctCustInComeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* CICtCustInComeInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQctCustInComeInfoByIncomeAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQctGrpCustBylicensenno(const utype * inParam,TCtrlInfo *errInfo);//根据集团客户营业执照号关联多表查询集团客户信息
utype* cQctGrpCustByCustId(const utype * inParam,TCtrlInfo *errInfo);//根据集团客户ID关联多表查询集团客户信息
//张蒙   根据客户ID查询信息
utype* cQct1CustInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);

//wangqiana
utype* cQurspecialbygrpidwq(const utype *inParam, TCtrlInfo *errInfo);
utype* cQcounturspecialwq(const utype *inParam, TCtrlInfo *errInfo);
utype* cQcounturspecialwq2(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfSpecialListInfoBycond1(const utype * inParam,TCtrlInfo *errInfo);


utype* cQGrppaymanInfoByIdNo(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetCntOfEsopLoginByLoginRole(const utype *inParam , TCtrlInfo *errInfo);

utype* cUCustIdOfCustMngObjByIdCust(const utype * inParam,TCtrlInfo *errInfo);

/*xiangyl 撤单时客户经理对象表中增加数据*/
utype* cICustMngObjFromHis(const utype * inParam,TCtrlInfo *errInfo);

utype* cQCustMngObjByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCreateNoteOfCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustInfoByGrpCustNameOnly(const utype * inParam,TCtrlInfo *errInfo);

utype* cIBlackListPhone(const utype * inParam, TCtrlInfo *errInfo);
utype* cIBlackListPhoneHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cIBlackListPhoneHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cQBlackListPhoneByMasterId(const utype * inParam,TCtrlInfo *errInfo);

utype* cDGrpCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpCustNameInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpCustMemberInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfGrpCustMemberInfoByCustId(const utype * inParam,TCtrlInfo *errInfo);

utype* cQGrpCustExtLevelInfoByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGrpCustExtLevelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustExtLevelInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustExtLevelHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cIGrpCustExtLevelInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cDGrpTarGetListInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustNameByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustManagerByMasterId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCustManagerByMasterId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustManagerByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQGrpCustLvlByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustLvlByPage(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfCustManagerByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfGrpCustMemberHisByUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpCustMemberHisByUnitId(const utype * inParam,TCtrlInfo *errInfo);
utype* cIContractExtInfoHis2(const utype * inParam,TCtrlInfo *errInfo);
utype* cIHdAleTsInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cIHdAleTsInfoHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cQNextTwoDay(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberRoleByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfGrpCustMemberRoleByCustIdRoleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfGrpCustHighByMul(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpCustHighByIDPage(const utype * inParam,TCtrlInfo *errInfo);
utype *cCntOfGetAgreementInfobyPage(const utype * inParam,TCtrlInfo *errInfo);
utype *cGetAgreementInfobyPage(const utype * inParam,TCtrlInfo *errInfo);
utype *cCntOfGetGrpCustInfobyPage(const utype * inParam,TCtrlInfo *errInfo);
utype *cGetGrpCustInfobyPage(const utype * inParam,TCtrlInfo *errInfo);

utype* cICustResOrdHisByIdResBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDCustResOrdInfoByIDResExp(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustResOrdInfoByResTypeExp(const utype * inParam,TCtrlInfo *errInfo);

utype* cQBlackListPhoneByMasterIdM(const utype * inParam,TCtrlInfo *errInfo);
utype* cQsOprCmd(const utype * inParam,TCtrlInfo *errInfo);

/*测试环境联调测试增加*/
utype* cGetCntOfGrpCustMemberByIdRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGtCntOfGrpCustMemberByIdRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetGrpCustMemInfoByIdRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cGtGrpCustMemInfoByIdRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEGrpCustMemRoleHis(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEGrpCustMemRoleHisBak(const utype * inParam,TCtrlInfo *errInfo);
utype* cDEGrpCustMemRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cDEGrpCustMemRoleCnd1(const utype * inParam,TCtrlInfo *errInfo);
utype* cIEGrpCustMemRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfEGrpCustMemberRoleByCustRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfEGrpCustMemberRoleById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfEGrpCustMemberRoleByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEGrpCustMemberRoleByCustIdRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEGrpCustMemberRoleByCustRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEGrpCustMemberRoleById(const utype * inParam,TCtrlInfo *errInfo);
utype* cQEGrpCustMemberRoleByIdNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cURoleCodeOfEGrpCustMemRole(const utype * inParam,TCtrlInfo *errInfo);
utype* cQContPersonalCustInfoHisByCustId(const utype * inParam,TCtrlInfo *errInfo);

#endif

