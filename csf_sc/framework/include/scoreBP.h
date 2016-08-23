


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


/*#######################集团积分调整begin#######################*/

utype* p3961Chk(const utype *puInParam, TCtrlInfo *errInfo);
utype* p3961Query(const utype *puInParam, TCtrlInfo *errInfo);
utype* pQGrpScore(const utype *puInParam, TCtrlInfo *errInfo);
extern "C" utype* p3961Cfm(const utype *puInParam, TCtrlInfo *errInfo);
/*#######################集团积分调整end########################*/
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
/*#######################集团积分查询begin#######################*/
utype* p3960Query(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*#######################集团积分查询end########################*/


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

/*#######################积分商城省CRM兑换 begin ########################*/
utype* p3825Init(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3825Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3825Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3825Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3825IQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3893Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p3977Cfm(const utype* inParam,TCtrlInfo* errInfo);
utype* p2258Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################积分商城省CRM兑换 end ########################*/

/*#######################积分兑换资费产品退订冲正 begin ########################*/
extern "C" utype* pPubScoreProFeeCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################积分兑换资费产品退订冲正 end ########################*/
/*积分查询--end*/
utype* pPubScoreUserQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreInitQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/*积分查询--end*/


/*#######################积分预占接口 begin ########################*/
utype* pPubMarkPreUse(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubMarkPreUnUse(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################积分预占接口 end ########################*/

/*#######################积分兑换保险 begin ########################*/
utype* p2274Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2274Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################积分兑换保险 end ########################*/

/*#######################积分兑换新业务 begin ########################*/
utype* p4033Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p4033RelChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################积分兑换新业务 end ########################*/

/*#######################积分兑换预存 begin ########################*/
utype* p3962Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3962Chk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################积分兑换预存 end ########################*/

utype* p3966ResQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*#######################积分预占后台清理进程 begin ########################*/
utype* pPubScoreUseScan(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*#######################积分预占后台清理进程 end ########################*/
/*消费积分、调整积分*/
utype* pPubScoreAdjQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUseQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*#######################客户积分申请查询 begin ########################*/
utype* pPubScoreAdjQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUseQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUserApplyChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pPubScoreUserCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*#######################积分兑换龙币 begin ########################*/
extern "C" utype* p3968Cfm_SX(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*#######################获取用户品牌 begin ########################*/
utype* pPubScoreGetBrand(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*####################### 积分转移入库外部接口调用-山西 begin ########################*/
utype* p3971CfmL(const utype *puInParam, TCtrlInfo *errInfo);
utype* pOrderBuildL(const utype *inParam, TCtrlInfo *errInfo);

/*####################### 全网礼品实时查询，发送短信 ########################*/
utype* p2258SendMsg(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*####################### 为山西peb实现积分兑换预存的外部接口功能  ########################*/
extern "C" utype* p3962Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*####################### 积分申请 ########################*/

extern "C" utype* pPubScoreUserDel(const utype * inParam, TCtrlInfo *ptCtrlInfo);

utype* pPubScoreUserQuery(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUserFlag(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3995Inter(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3996Inter(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreUserAllChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pChgSmScoreUser(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pOrderCfmL_Adj(const utype *inParam, TCtrlInfo *errInfo);
/*####################### 巢湖拆分 积分转移 供开户调用 ########################*/
utype* pITransScore(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*####################### 全网积分兑换异步处理 ########################*/
extern "C" utype* p3968ObossCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubScoreExchgChk_Oboss(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3968ObossOrdDeal(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p3973ObossL(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*积分兑换电子券*/
utype* p2069App(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2069Cfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* p2069Upd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2069Up (const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubEnDeCode (const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubGetEbillCode(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubTest(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* p2050Qry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/*add by lankai end*/

/* 积分向上调整 20120517 */
utype* pGetDetailScore(const utype *inParam, TCtrlInfo *ptCtrlInfo);


/*批量积分调整校验服务 20120522*/
utype* p3974Rule(const utype *inParam, TCtrlInfo *ptCtrlInfo);
 utype* p3971CrossRegionChk(const utype *inParam, TCtrlInfo *ptCtrlInfo);

utype* pScoreOutBusi(const utype * puInParam,TCtrlInfo *ptCtrlInfo);
utype* pScoreChkForStore(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubChkCodeBusi(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubInsertExcp(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*完善积分计划相关规则 2012/6/28 15:56:59*/
utype* pPubChgUserStatus(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPubChgUserStatusPd(const utype * inParam,TCtrlInfo *ptCtrlInfo);

/*test*/
utype* ptestTixin(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pULimitOweOfUserInfoTest(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pULimitOweTest(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/*积分兑换礼品自动化配置*/
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
