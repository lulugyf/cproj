


#ifndef __SCOREBP_H__
#define __SCOREBP_H__

//chudg begin
extern "C" utype* p3958Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3959Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3958CfmBoss(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3959CfmBoss(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* ScoreFuncMerge(const utype* puIn, TCtrlInfo *ptCtrlInfo);
utype* p3958QryScore(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3959QryGrpAudre(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3959Check(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryGrpScore(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryGrpScoreBoss(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAdjBrandQQT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAdjBrandSZX(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryGrpScoreRuleBoss(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryGrpScoreRule(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryBrandRuleBoss(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryBrandScoreRule(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pQryBrandScoreRuleDB(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pQryGrpScoreDB(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pTotalScoreQueryDB(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pQryScoreRuleDB(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUserBrandByMasPhone(const utype *inParam, TCtrlInfo *ptCtrlInfo);
//chudg end


/*#######################���Ż��ֵ���begin#######################*/

utype* p3961Chk(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3961Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQGrpScore(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p3961Cfm(const utype *puInParam, TCtrlInfo *errInfo);
/*#######################���Ż��ֵ���end########################*/
extern "C" utype* pPubScoreExchgCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubCurTotalScoreQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubScoreExchgChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubScoreExchgValid(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pScoreInterCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3968Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* p3967Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3964Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pUseRuleInfoQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3964Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pScoreCardInfoUpd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3975Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3975Rbk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pScoreExchgRbk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3963Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQExchgRate(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3999Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3999Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3999CfmL(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3966Chk (const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3793Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3793BlackChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pRBlackChkNforScore(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3966Chk_boss(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubScoreExchgValid_crm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pScoreTransCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################���Ż��ֲ�ѯbegin#######################*/
utype* p3960Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*#######################���Ż��ֲ�ѯend########################*/


utype* p3796Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3795Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3795Add(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3795Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3795Modify(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3795ResQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3795Warn(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pScoreCardInfoQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pQueryUnAcctRec(const utype *inParam, TCtrlInfo *errInfo);
utype* pQuerystatByPopedom(const utype *inParam, TCtrlInfo *errInfo);
utype* p3969Account(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype * pQUserScoreInfo(const utype *inParam, TCtrlInfo *errInfo);
extern "C" utype * pQScoreInfo(const utype *inParam, TCtrlInfo *errInfo);

/*#######################�����̳�ʡCRM�һ� begin ########################*/
utype* p3825Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3825Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3825Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3825Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3825IQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3893Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3977Cfm(const utype* inParam,TCtrlInfo* errInfo);
utype* p2258Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################�����̳�ʡCRM�һ� end ########################*/

/*#######################���ֶһ��ʷѲ�Ʒ�˶����� begin ########################*/
extern "C" utype* pPubScoreProFeeCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################���ֶһ��ʷѲ�Ʒ�˶����� end ########################*/
/*���ֲ�ѯ--end*/
utype* pPubScoreUserQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreInitQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*���ֲ�ѯ--end*/


/*#######################����Ԥռ�ӿ� begin ########################*/
utype* pPubMarkPreUse(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubMarkPreUnUse(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################����Ԥռ�ӿ� end ########################*/

/*#######################���ֶһ����� begin ########################*/
utype* p2274Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2274Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################���ֶһ����� end ########################*/

/*#######################���ֶһ���ҵ�� begin ########################*/
utype* p4033Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p4033RelChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################���ֶһ���ҵ�� end ########################*/

/*#######################���ֶһ�Ԥ�� begin ########################*/
utype* p3962Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3962Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################���ֶһ�Ԥ�� end ########################*/

utype* p3966ResQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*#######################����Ԥռ��̨������� begin ########################*/
utype* pPubScoreUseScan(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################����Ԥռ��̨������� end ########################*/
/*���ѻ��֡���������*/
utype* pPubScoreAdjQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUseQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*#######################�ͻ����������ѯ begin ########################*/
utype* pPubScoreAdjQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUseQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUserApplyChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubScoreUserCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*#######################���ֶһ����� begin ########################*/
extern "C" utype* p3968Cfm_SX(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*#######################��ȡ�û�Ʒ�� begin ########################*/
utype* pPubScoreGetBrand(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*####################### ����ת������ⲿ�ӿڵ���-ɽ�� begin ########################*/
utype* p3971CfmL(const utype *puInParam, TCtrlInfo *errInfo);
utype* pOrderBuildL(const utype *inParam, TCtrlInfo *errInfo);

/*####################### ȫ����Ʒʵʱ��ѯ�����Ͷ��� ########################*/
utype* p2258SendMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*####################### Ϊɽ��pebʵ�ֻ��ֶһ�Ԥ����ⲿ�ӿڹ���  ########################*/
extern "C" utype* p3962Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*####################### �������� ########################*/

extern "C" utype* pPubScoreUserDel(const utype * inParam, TCtrlInfo *ptCtrlInfo);

utype* pPubScoreUserQuery(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUserFlag(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3995Inter(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3996Inter(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUserAllChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pChgSmScoreUser(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pOrderCfmL_Adj(const utype *inParam, TCtrlInfo *errInfo);
/*####################### ������� ����ת�� ���������� ########################*/
utype* pITransScore(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*####################### ȫ�����ֶһ��첽���� ########################*/
extern "C" utype* p3968ObossCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreExchgChk_Oboss(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3968ObossOrdDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3973ObossL(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*���ֶһ�����ȯ*/
utype* p2069App(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2069Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2069Upd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2069Up (const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubEnDeCode (const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubGetEbillCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubTest(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2050Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*add by lankai end*/

/* �������ϵ��� 20120517 */
utype* pGetDetailScore(const utype *inParam, TCtrlInfo *ptCtrlInfo);


/*�������ֵ���У����� 20120522*/
utype* p3974Rule(const utype *inParam, TCtrlInfo *ptCtrlInfo);
 utype* p3971CrossRegionChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pScoreOutBusi(const utype * puInParam,TCtrlInfo *ptCtrlInfo);
utype* pScoreChkForStore(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubChkCodeBusi(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubInsertExcp(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*���ƻ��ּƻ���ع��� 2012/6/28 15:56:59*/
utype* pPubChgUserStatus(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubChgUserStatusPd(const utype * inParam,TCtrlInfo *ptCtrlInfo);

/*test*/
utype* ptestTixin(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pULimitOweOfUserInfoTest(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pULimitOweTest(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*���ֶһ���Ʒ�Զ�������*/
utype* p2044Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2044Query(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2044QueryWorkNo(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2044QueryResName(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2044QueryResCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2044RuleQuery(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2044addNew(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2044chg(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pInsertOpr(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pChkTimeOver(const utype *inParam, TCtrlInfo *ptCtrlInfo);

#endif
