//#define DEPART_PROVINCE 10011

#ifndef __CUSTSVCBC_H__
#define __CUSTSVCBC_H__
//���ſͻ���������
utype *p3844Qry(const utype *inParam , TCtrlInfo *errInfo);
extern "C" utype* p3859Cfm(const utype *inParam , TCtrlInfo *errInfo);
//utype* pGrpCreate(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetDeptId(const utype *inParam, TCtrlInfo *errInfo);
utype *pIGrpMebInfoadd(const utype *inParam , TCtrlInfo *errInfo);
utype* pIGrpCustInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIGrpCustExtInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIGrpDeptInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIGrpAddrListInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pICustApproveRec(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3851CfmAH(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3851CfmSX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3851Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pICustoperatorInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *p3851Check(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype *pECCustInfoSynInfo(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
//���ſͻ�������Ϣ����
utype* pOtherNetManager(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOtherNetProductMan(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUOtherNetInfoOfGrpCustExtInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpRivalInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIOtherNetManager(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUOtherNetManagerByCustIdAndManagerNO(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDOtherNetManagerByCustIdAndManagerNO(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIOtherNetProduct(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUOtherNetProductByCustIDAndProductNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDOtherNetProductByCustIDAndProductNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3866Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//��ѯҳ��չʾ�ֶ�
utype* pGetFieldesByOpCode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetNocFieldesByOpCode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//��ͨ�ͻ�����ά��
utype* pUCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUPersonalCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUUnitInfoOfCustWorkInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUContactInfoOfCustContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* p3845Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* p3845CfmL(const utype * inParam,TCtrlInfo *errInfo);

//���ſͻ�������Ϣά��
utype *p3858Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pPubGrpBaseInfoQry(const utype *inParam , TCtrlInfo *errInfo);
utype *pUCustInfoByCustID(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpCustInfoByCustIDAndUnitID(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpCustExtInfoByCustID(const utype *inParam , TCtrlInfo *errInfo);
utype *pNewGrpCustExtInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pGetNewGrpCustExtInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pUNameOfGrpDeptInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pNewGrpCustAttrInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pPubGrpBaseInfoQrySX(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpCustAttrInfoByCustID(const utype *inParam , TCtrlInfo *errInfo);

//���ſͻ�������Ϣά��
utype *p3859Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pPubGrpMulExtInfoQry(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpCustInfoByCustIDGrpMulExt(const utype *inParam , TCtrlInfo *errInfo);
utype *pUCustInfoGrpMulExt(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpCustExtInfoGrpMulExt(const utype *inParam , TCtrlInfo *errInfo);
utype *pUContactInfoOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pUCustvistInfoOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pUCustcompOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pUCustOprOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);

//����������bp�����ӿ�
utype* pQGrpCustInfoByQryCond(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//���ſͻ�������֤��
//utype *p3844Qry(const utype *inParam , TCtrlInfo *errInfo);
//utype* p3844Qry(const utype * inParam,TCtrlInfo *errInfo);
utype *pUCustKeyInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pUCustNameOfCustInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pUConNameOfContractInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pUIccIdOfCustContactInfo(const utype *inParam , TCtrlInfo *errInfo);

//utype *p3844BossSyn(const utype *inParam , TCtrlInfo *errInfo);
//���ſͻ���Ӫָ��ά��
utype* pUGrpCustExtInfoByCustID02(const utype * inParam,TCtrlInfo *errInfo);
utype* pUGrpCustInfoByCustID(const utype * inParam,TCtrlInfo *errInfo);
utype* p3861Qry(const utype * inParam,TCtrlInfo *errInfo);

utype* pPasswordCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetCustProduct(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCustContUserByIdNo1(const utype *inParam, TCtrlInfo *errInfo);

//��ͥ�ͻ�����
utype* p3880Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubHomeMebInfoQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUConInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUHomeExtInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUHomeInfoOfCustInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUWorkInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubHomeCustInfoQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3885Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIHomeMember(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUHomeMember(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDHomeMember(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//���ſͻ�IT��Ϣά��
utype* pUGrpCustITInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pGrpITInfoQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p3863Qry(const utype * inParam,TCtrlInfo *errInfo);

//���ſͻ���������
utype *p3852Qry(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
//utype *pCustInfoApprCfm(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype *pUStatusOfCustInfo(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype *pUCustApproveRec(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

//�ͻ���ҳ��Ϣ��ѯ
utype* pBaseInfoOfCustsvc(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDetailInfoOfCustsvc(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//��ͬ��Ϣά��
utype *p3862Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pPubGrpContractInfoQry(const utype *inParam , TCtrlInfo *errInfo);
utype *pIAgreementInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pUAgreementInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pDAgreementInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pQAgreementInfo(const utype *inParam , TCtrlInfo *errInfo);

//��ҵ��ͻ�����ά��
utype* pPersCustInfoQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p3846Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUPersCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUPersPersonalCustInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUPersCustExtInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUPersCustConsumeInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUPersCustContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIPersCustContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDPersCustContactInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUPersCustWorkInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUPersCustSpcdayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pIPersCustSpcdayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pDPersCustSpcdayInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pUPersCustEduInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pContactQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pSpcDayQry(const utype * inParam,TCtrlInfo *errInfo);

//�ͻ���ϵ����
utype* pPubCustQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pCustRelQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p3890Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* pICustRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pUCustRel(const utype * inParam,TCtrlInfo *errInfo);
utype* pDCustRel(const utype * inParam,TCtrlInfo *errInfo);

//�����˻�����
utype* p3900Qry(const utype * inParam,TCtrlInfo *errInfo);

//������Ҫ��Ա��Ϣά��
utype *pIGrpVIPMebInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpVIPMebInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pDGrpVIPMebInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *p3864Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pPubGrpVIPMebInfoQry(const utype *inParam , TCtrlInfo *errInfo);
utype *pMasterServerQryOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pCustQryOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pGrpCustQryOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pGetGrpVIPMebInfoHist(const utype *inParam , TCtrlInfo *errInfo);
utype *pQCardTypeOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pUPersonalInfoOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pQGrpVIPMebInfoByIdNo(const utype *inParam , TCtrlInfo *errInfo);
utype *pQGrpVIPMebInfoByPhoneNo(const utype *inParam , TCtrlInfo *errInfo);
utype *pKeymanQryOfGrpVIPMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pUpdPersonNum(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpMebInfoById(const utype *inParam , TCtrlInfo *errInfo);
utype *pIGrpMebInfoById(const utype *inParam , TCtrlInfo *errInfo);
utype *pDGrpMebInfoById(const utype *inParam , TCtrlInfo *errInfo);
utype *pUPositionOfGrpMebInfoById(const utype *inParam , TCtrlInfo *errInfo);
utype *pSingleQueryByPhoneNo(const utype *inParam , TCtrlInfo *errInfo);
utype *pIGrpMebRoleInfo(const utype *inParam , TCtrlInfo *errInfo);
//��̸��Ϣά��
utype *p3865Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pPubGrpVisitInfoQry(const utype *inParam , TCtrlInfo *errInfo);
utype *pIGrpVisitInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpVisitInfo(const utype *inParam , TCtrlInfo *errInfo);

//�˻�����ά��
utype* p3901Qry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pURepresentPhoneofContractInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUBillPostInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUContractAddInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);




//�ͻ���������
utype* p2108Qry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pCustDocuMan(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetOptsnCustNameByPhoneNo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pIDocumentInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQDocumentInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUPhoneOfDocumentInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUValidOfDocumentInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//######################## �ͻ�����ӿ�BP #######################################
utype* pLoginGrpList(const utype *inParam , TCtrlInfo *errInfo);
utype* pLoginConList(const utype *inParam , TCtrlInfo *errInfo);
utype* pLoginUsrList(const utype *inParam , TCtrlInfo *errInfo);
utype* pLoginCustId(const utype *inParam , TCtrlInfo *errInfo);
utype* pLoginGrpInfo(const utype *inParam , TCtrlInfo *errInfo);
utype* pQryLevel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryGrpLevel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPukQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pBaseInfoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCustInfoListByCert(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQUserInfoListByCert(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCustInfoByCertPhone(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCustInfoByCertLevel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCustInfoByNameLevel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQCustInfoName(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQPayRelationByIdNo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQInfoByContractNo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQInfoByPhoneNo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQInfoByIdNo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQDeadInfoByPhoneNo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQPhoneNoByCustInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQDeadInfoByIdNo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQInfoBySimNo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubJudgeTrustUser(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQConUserRelation(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQUserVPMNGroup(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQAddUserCredit(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpValidQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUsrLogCnt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpUsrQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pMemberInfoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUsrGrpInfoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpUsrInfoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUsrGrpNameQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUsrGrpMbrNameQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpBooking(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpBookingAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCustHallAddr(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQConInfoByCustId(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQConInfoByContactId (const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCustManagerLogin(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpKPerChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpLevelCnt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQStaLoginInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pCPHeadMag(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pCPHeadAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pCPHeadDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pCPHeadUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQCPHeadByPhoneNo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQGrpCustUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pCustMangagerUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQGrpCustBaseInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubInfoQryByUser(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQPerCustInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQHomeCustInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQGrpCustInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQCPHeadAreaMsg(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubQCustManager(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQBaseIf01(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQBaseIf02(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQBaseIf03(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQBaseIf04(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQBaseIf05(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPasschk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIVRInfoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pNamePhoneCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNameValid(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCustSel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetCustInfoByInPut(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetIdNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetPerCustInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetContactId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetGrpCustInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetGrpCustInfoForInter(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetGrpCustProInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetGrpManInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetExtCustInfoI(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetFields(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCreateOrderXML(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRetMsgQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPasschk1(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUsrOrgChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pOutSysInfoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pIccIdPasswdChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRandPasswdChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUsrBandChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pPubQCustContOut(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pPubQCustContListOut(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUsrGrpCustInfoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* phoneQry(const utype *inParam , TCtrlInfo *errInfo);

//���ſͻ��ؼ�����
utype* p3860Qry(const utype * inParam,TCtrlInfo *errInfo);

//���ſͻ����õȼ�����
utype* p3924Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pICustCreditRec(const utype *inParam, TCtrlInfo *errInfo);
utype* pQGrpCustInfoII(const utype *inParam, TCtrlInfo *errInfo);

utype* p3925Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUCreditOfGrpCustInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pCustCreditRecCheckQry(const utype *inParam, TCtrlInfo *errInfo);

utype* pUCfmOneOfCustCreditRec(const utype *inParam, TCtrlInfo *errInfo);
utype* pUCfmTwoOfCustCreditRec(const utype *inParam, TCtrlInfo *errInfo);

utype* p3926Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pCustCreditRecQry(const utype *inParam, TCtrlInfo *errInfo);

//���ſͻ�������Ա��Ϣά��
utype *p3868Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pPubOtherNetMbrInfoQry(const utype *inParam , TCtrlInfo *errInfo);
utype *pGetGrpOtherMebInfoHist(const utype *inParam , TCtrlInfo *errInfo);
utype *pIGrpOtherMebInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpOtherMebInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pDGrpOtherMebInfo(const utype *inParam , TCtrlInfo *errInfo);

//���ų�Ա��Ϣά��
utype *p3867Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pPubGrpMebInfoQry(const utype *inParam , TCtrlInfo *errInfo);
utype *pQEveryGrpMebInfoByIdNo(const utype *inParam , TCtrlInfo *errInfo);
utype *pQEveryGrpMebInfoByPhoneNo(const utype *inParam , TCtrlInfo *errInfo);
utype *pBrandNameQryOfGrpMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pAliasQryOfGrpMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pManagerQryOfGrpMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pCustQryOfGrpMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pQUserInfoOfGrpMeb(const utype *inParam , TCtrlInfo *errInfo);
utype *pIGrpMebInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pDGrpMebInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pIGrpDeptMbr(const utype *inParam , TCtrlInfo *errInfo);
utype *pDGrpDeptMbr(const utype *inParam , TCtrlInfo *errInfo);
utype *pQGrpDeptMbr(const utype *inParam , TCtrlInfo *errInfo);
utype *pUGrpDeptMbr(const utype *inParam , TCtrlInfo *errInfo);
utype *pQGrpDeptNameByIdNo(const utype *inParam , TCtrlInfo *errInfo);

//�ۺϲ�ѯ
utype *p3895Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pQGrpCustInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pQGrpCustList(const utype *inParam , TCtrlInfo *errInfo);
utype *pQHomeCustInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pQHomeCustList(const utype *inParam , TCtrlInfo *errInfo);
utype *pQPersCustInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pQPersCustList(const utype *inParam , TCtrlInfo *errInfo);
utype *pQUesrProInfo(const utype *inParam , TCtrlInfo *errInfo);
utype *pGetCustLevelStatus(const utype *inParam , TCtrlInfo *errInfo);

//�ͻ����ϵ���
utype *p3916Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pExtCustInfoApp(const utype *inParam , TCtrlInfo *errInfo);
utype *pIExpCustInfoRd(const utype *inParam , TCtrlInfo *errInfo);
utype *pIExpCustAdd(const utype *inParam , TCtrlInfo *errInfo);

utype *p3917Qry(const utype *inParam , TCtrlInfo *errInfo);
utype *pExtCustInfoCheck(const utype *inParam , TCtrlInfo *errInfo);
utype *pExtFieldChin(const utype *inParam , TCtrlInfo *errInfo);
utype *pUCfmOfExpCustInfoRdByLogin(const utype *inParam , TCtrlInfo *errInfo);
utype *pTrsanCodeTochin(const utype *inParam , TCtrlInfo *errInfo);
utype *pTranDate(const utype *inParam , TCtrlInfo *errInfo);

utype *p3918Qry(const utype *inParam , TCtrlInfo *errInfo);
//������֯�ṹ����
utype* p3870Qry(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDGrpDeptInfo(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUGrpDeptInfo(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

//�ͻ����ϵ���
utype *pGetExtFieldsQry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGetExtInfo(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGetExtCustInfo(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGetAllInfoOfPer(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGetExtCust(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGetAllInfoOfGrp(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGrpVIPMebInfoQryBy3917(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pKeymanQryBy3917(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pQGrpVIPMebInfoBy3917(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGreatText(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

//�������ſͻ�������˽����ѯ
utype *p3875Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pQEcCustResultByUnitId(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

utype *p3874Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGetAllInfoOfSecGrpCfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pISecGrpInfoOfSecOBGrpCustInter(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pSelParCustInfoByECCode(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pSelSecGrpInfoByECCode(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pUSecGrpInfoOfSecOBGrpCustInter(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pCancelCustInfo(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
//utype *p3874Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *p3916Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *p3917Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

//ȡ���ű�����ˮ
utype *pGetUnitId(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

//���ŵȼ����
utype* pUGrpCustLvl(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTraCustId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pGetGrpCustInfoByCity (const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pGetGrpLevel(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGetGrpCustInfoInetgrityPrecent(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGetGrpCustInfoInetgrity(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
extern "C" utype *pQTotalScoreView(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

//�ҵ��Ŷӹ���
utype* pILoginRel(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDLoginRel(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3791Qry(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3791Cfm(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* pULoginRel(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

utype *pEOSInterFace(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pGetErrInfo(const utype *puInParam , TCtrlInfo *ptCtrlInfo);


//����������������Ϣ
utype* p3727Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQInterBasicInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pIInterBasicInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUInterBasicInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pDGrpMbrInfoForOut(const utype *inParam , TCtrlInfo *errInfo);
/*�ͻ�������shell���÷���*/
utype *pShellInvoke(const utype *inParam, TCtrlInfo *errInfo);
utype*  pShellEXEC(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
//����������ϲ�ѯ
utype* pQBroadBasicInfo(const utype * inParam, TCtrlInfo *errInfo);

//ת��CUST_ID
utype* pPubTraCustId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pIGrpCustExtForCustLevel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUGrpCustExtForCustLevel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3718Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubOrdXml(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetFileDetail(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetGrpLevelInetgrity(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDContractInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubRadius(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* cQOrderInfoByIdNo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3714Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pECCustSyn(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQECCustInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pSqlServer(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3824Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p3710Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3710Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pGetTradeTree(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3712Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pCheckVaildUser(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pGetInPutXml(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3712Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pQListMebInfo(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3711Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3711Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pListGrpStaffMan(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pCheckVaildGrpCust(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

utype* pECCustInfoSynCen(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pECCustInfoSynCrm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pQECCustInfoSynCen(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

utype *pAppUserInterNamePass(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pInternetLogin(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pInternetLogout(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pNetPwdEncrypt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pUserInterPassChange(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype *pUserPetNameChange(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pGetTopNumOfDocumentInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubSendMsgOfExt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//��������
utype *pMemExport(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pIVRCustQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3783Cfm(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

//���ſͻ���ϵ��Ϣ
utype *pUGrpCustContactInfo(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pIGrpCustContactInfo(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDGrpCustContactInfo(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3873Qry(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubGrpContactInfoQry(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

utype* pPubBaseInfoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQBroadBandUseInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//�ͻ������޸�
utype* p3903Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3903Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3903CheckPwd(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

//����ͨ�ŷ�����Ϣ
utype* p3906Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3906Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);


//�˻������޸�
extern "C" utype* p3904Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3904CheckPwd(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

//������ҵ�ṹ��ѯ
utype* p3905Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

//ɧ���û���������
utype* p3907QryHarass(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3907Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3907Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3907DelCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3907CfmBatchChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3907AddCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//�������Ա����
utype* p3908Qry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3908Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *p3908QryAuditer(const utype *inParam , TCtrlInfo *errInfo);

//�����޸ļ��ſͻ�״̬
extern "C" utype *p3909Cfm(const utype *inParam , TCtrlInfo *errInfo);

//Ŀ�꼯��¼��
utype* p3910Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pIGrpTargetListRec(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3910Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

//Ŀ�꼯�����
utype* p3911Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3911Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);

//Ŀ�꼯��ת����
utype* p3912Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3912Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3913Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3913Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
//�������Ľӿ�
utype* pIsGrpMember(const utype *inParam , TCtrlInfo *errInfo);
utype* pCustQuery(const utype *inParam , TCtrlInfo *errInfo);
utype* pCustITQuery(const utype *inParam , TCtrlInfo *errInfo);
utype* pCustQuerySX(const utype *inParam , TCtrlInfo *errInfo);
//ADC������Ϣ����
utype* p3915Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3915Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3915QryByAcceptAndECID(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3915CheckPwd(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3915QryGrpInf(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* p3915CheckECID(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
//EC�ͻ���Ϣ����
utype* p3914Qry(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
//�ʻ����ϴ���ͨ��Ӧ�ü���ƽ̨������Դ�ӿ�
utype *p3900QryGroup(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
//�û����ϲ�ѯ
utype*  p3919Qry(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

//esop���ſͻ�-���ſͻ���Ϣ
utype*  pEsopGrpCustQry(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype*  pEsopGrpCustConQry(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype*  pEsopGCustCfm(const utype * puInParam, TCtrlInfo *ptCtrlInfo);
utype*  pGrpCustMemQry(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

//ESOP��̨�ӿ�
utype *pGrpAttentQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pGrpTargetListCountQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pGetKeyContactBirQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pPubGetMemberQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pPubGetMemberCfm(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pGrpKeyFalyQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pGrpMemberQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pEsopGrpAttenQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pEsopGrpNoAttenQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pGetCustInfoQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pComDetailQry(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype *pCheckBlackListByNo(const utype *inParam , TCtrlInfo *ptCtrlInfo);
utype* pGrpCustInfoCommit(const utype *inParam , TCtrlInfo *errInfo);

//ESOP��ѯ���ſͻ����û����ײ���Ϣ
utype* pGetUsrProdMsg(const utype *inParam, TCtrlInfo *errInfo);
//���˿ͻ��������ù���ͨ�ӿ�
utype* p3839IccidCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pBlackListAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//��������֤
utype* p1226Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//һ��BOSS
utype* pECOneBoss(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//ESOP��ȡ������־��д��������ͻ��б�ӿ�
utype* pServiceJournal(const utype *inParam, TCtrlInfo *errInfo);
//���������ӿ�-���ŵ�¼��֤
utype* pGrpLoginVerify(const utype *inParam , TCtrlInfo *errInfo);
//���������ӿ�-���ſͻ��Թ����պ����ѯ
utype* pPubDocMsg(const utype *inParam , TCtrlInfo *errInfo);
//���������ӿ�-���ſͻ��Թ����������ѯ
utype* pGrpSelPubUsrMg(const utype *inParam , TCtrlInfo *errInfo);
//���������ӿ�-������ҵ����ѯ
utype* pPubGrpSelAddr(const utype *inParam , TCtrlInfo *errInfo);

/*�ƶ���ʹ����������*/
extern "C" utype* p3936Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3936Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3936HisQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3936CfmBatchChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3936AddCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3936DelCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3936AddCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3936CfmBatch(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3936Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQGrpMebNum(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetGrpCust(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//���ź�����
utype* p2105QByLic(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
int myLG_GetinterForCust(char *group, char *inMsg, char *outMsg);
utype* pCreateGrpCust(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//ADC������Ϣ΢��ӿ� ���ſͻ������޸�
utype* pPubADCModify(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pIGrpCustCmdDay(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQADCGrpCustInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *p3914Cfm(const utype *uInParam , TCtrlInfo *errInfo);

utype* pGrpMobileNumCrm(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//��ͬ��������
utype* pAgreementQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//Ŀ�꼯�ű�����Ϣ��
utype* pIGrpTarOrig(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
//���ۻ�ȡ���ſͻ�ID�ӿ�
utype* pQUnitIDByCustID(const utype *inParam, TCtrlInfo *ptCtrlInfo);

//��������ϵͳͬ������ϵͳ����
utype* pUBlackList(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//����������¼У����ʱ�ӿ�
utype* pGrpCustIsNew(const utype *inParam , TCtrlInfo *errInfo);
//���ػ���ѯ�ӿ�
utype* pSwitchQuery(const utype * inParam,TCtrlInfo *errInfo);
utype* p1525HlrQry(const utype * inParam,TCtrlInfo *errInfo);


extern "C" utype *pOrderMemberCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pEsopCustMemQry(const utype *inParam , TCtrlInfo *errInfo);
extern "C" utype* pEsopCustMemMod(const utype *inParam , TCtrlInfo *errInfo);
//�嵥���ŷ����ӿ�
utype* p3939Query(const utype * inParam,TCtrlInfo *errInfo);
utype* p3911EsopQry(const utype * inParam,TCtrlInfo *errInfo);

utype* pOprLocusMsgQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOprLocusMsgMod(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//�������Զ�ɾ��
utype* pAutoDelBlacklist(const utype * inParam,TCtrlInfo *errInfo);
//����������
utype *p2106Query(const utype * inParam,TCtrlInfo *errInfo);
utype *p2106Add(const utype *inParam, TCtrlInfo *errInfo);
utype *p2106Del(const utype *inParam, TCtrlInfo *errInfo);
utype *pQryBlackDelInfo(const utype *inParam, TCtrlInfo *ptCtrlInfo);


utype* p3909Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//ȫ��BBoss->Boss�Ŀͻ���Ϣͬ�� �ӿڳ������
utype* p3914BBossToBoss(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pBBossCraGrpCustInfo(const utype *inParam, TCtrlInfo *errInfo);
//��ѯһ��BOSS��TOBBBOSSCUSTNUMBERSYN������ȡ��Ҫͬ������ˮ
utype* pQtobbbosscustnumbersyn(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//�嵥�ͻ������޸�
utype* p3954Cfm(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
//3895 У���û�����
utype *pCheckPhonePwd(const utype *puInParam , TCtrlInfo *errInfo);
//ESOP��ע�ͻ����ɹ���  ��ѯ�쵼�����ͻ������б�
utype* pQCustManagerByRoleCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);

const long NUMMONEY = 100;
//���β���ϰ  ���ݿͻ�ID��ѯ�û���Ϣ
utype* pQCtcustinfoByCustid(const utype *inParam, TCtrlInfo *errInfo);
//���β�  ���ݼ��ſͻ�ID��ѯ���ſͻ���Ա��Ϣ
utype* p3989Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//����Ӫҵִ�պŻ�CustId��ѯ��������������Ϣ
utype * pQGrpCustBylicensenno(const utype * inParam,TCtrlInfo *errInfo);
utype*  p3701Qry(const utype * inParam, TCtrlInfo *errInfo);
utype * pQCustInComeByIccid(const utype * inParam,TCtrlInfo *errInfo);
utype * pQCustInComeByCustId(const utype * inParam,TCtrlInfo *errInfo);
utype* p3701AddCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3701Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3701Del(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pQGrpCustByCustId(const utype * inParam,TCtrlInfo *errInfo);


//����   �����û�ID��ѯ�û���Ϣ��ϰ
utype* pQct2CustInfoByCustId(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pIGrpMemberMsgForBrand(const utype *inParam, TCtrlInfo *errInfo);
utype* pQGrpMemberMsgByIdNo(const utype *inParam, TCtrlInfo *errInfo);

char* pApartProvince(const utype * inParam);
utype* pEsopLogin(const utype *inParam , TCtrlInfo *errInfo);

//�����ӿ�
extern "C" utype* pUCustidOfCustMngObj(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//����������
utype * p2106AddSX(const utype * inParam,TCtrlInfo * errInfo);
utype * p2106DelSX(const utype * inParam,TCtrlInfo * errInfo);
utype * p2106AddAH(const utype * inParam,TCtrlInfo * errInfo);
utype * p2106DelAH(const utype * inParam,TCtrlInfo * errInfo);
//��Ч����ɾ��
utype* pDGrpCustInfo(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpMemberList(const utype *inParam, TCtrlInfo *errInfo);

utype* pQGrpCustInfoAH (const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQGrpCustListAH (const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pStaffRule(const utype *inParam , TCtrlInfo *errInfo);
extern "C" utype* pCheckStaffLog(const utype *inParam , TCtrlInfo *errInfo);
utype* p3785Qry(const utype *inParam , TCtrlInfo *errInfo);
utype* p3928Qry(const utype *inParam , TCtrlInfo *errInfo);
utype* p3953(const utype *inParam , TCtrlInfo *errInfo);
utype* pGrpAccountInfoQry(const utype *inParam , TCtrlInfo *errInfo);
utype* pGrpConRelQry(const utype *inParam , TCtrlInfo *errInfo);
utype* pGCustQry(const utype *inParam , TCtrlInfo *errInfo);
utype* pGAgreeQry(const utype *inParam , TCtrlInfo *errInfo);

utype* p3702Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype *p2106LInit(const utype *inParam, TCtrlInfo *errInfo);
utype* pGrpCustNet(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

utype* pPubQGrpCustInfoByLincenum(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* p2209Check(const utype *inParam, TCtrlInfo *ptCtrlInfo);

#endif


