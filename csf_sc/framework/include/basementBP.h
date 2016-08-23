#ifndef __BASEMENTBP_H__
#define __BASEMENTBP_H__

//Ê¡¼¶×éÖ¯»ú¹¹¶¨Òå
#define CHINA_GROUP                     "1000"         /*ÖÐ¹ú×éÖ¯»ú¹¹½Úµã*/
#define PROVINCE_GROUP                  "10011"        /*×éÖ¯»ú¹¹Ê¡½Úµã, °²»Õ*/
#define SHANXI_PROVINCE_GROUP           "10011"        /*É½Î÷×éÖ¯»ú¹¹Ê¡½Úµã*/
#define SICHUAN_PROVINCE_GROUP          "10008"        /*ËÄ´¨×éÖ¯»ú¹¹Ê¡½Úµã*/
#define JILIN_PROVINCE_GROUP            "10013"        /*¼ªÁÖ×éÖ¯»ú¹¹Ê¡½Úµã*/
#define HEILONGJIANG_PROVINCE_GROUP     "10014"        /*ºÚÁú½­×éÖ¯»ú¹¹Ê¡½Úµã*/
#define ANHUI_PROVINCE_GROUP            "10017"        /*°²»Õ×éÖ¯»ú¹¹Ê¡½Úµã*/
#define ROOT_TD_GROUP                   "100170"       /*°²»ÕÌúÍ¨×éÖ¯»ú¹¹Ê¡¼¶½Úµã*/

#define ROOT_OP_ROLE                   0               /*op½ÇÉ«¸ù½Úµã*/

#define ROLE_ROOT "100000"                             /*½ÇÉ«´úÂë¸ù½Úµã*/
#define REGION_ROOT 10                                 /*µØÓò¸ù½Úµã*/
#define BASE_IN_WORKN_OPTCODE "CX01"                   /*»ù´¡¹ÜÀí¶ÌÐÅ±àÂë*/

//¹¤ºÅÀàÐÍ¶¨Òå
#define MNG_LOGIN_FLAG  "2"                            /*¹¤ºÅÀàÐÍÎªÏµÍ³¹ÜÀíÔ±*/

#define SYS_END_DATE "20500101000000"                  /*ÏµÍ³Ä¬ÈÏ½áÊøÊ±¼äÎª2050-01-01*/

#define POLI_REGION "0"                                /*ÐÐÕþÇøÓòÀàÐÍ*/
#define TELE_REGION "1"                                /*¹ÜÀíÇøÓòÀàÐÍ*/

#define INTERFACE_WEB "11"                             /*Éí·ÝÑéÖ¤ÇþµÀÎªÇ°Ì¨ÑéÖ¤*/

//ÄÚ´æÊý¾Ý¿â±êÇ©
#define LABELMDB "imdb"                                /*ÏµÍ³¼¶ÄÚ´æÊý¾Ý¿âÓÃ»§£¬¾ßÓÐËùÓÐÈ¨ÏÞ*/
#define LABELMDBQUERY "imdb_query"                     /*ÄÚ´æÊý¾Ý¿â²éÑ¯ÓÃ»§£¬¾ßÓÐ²éÑ¯È¨ÏÞ*/
#define LABELMDBOPR "imdb_opr"                         /*ÄÚ´æÊý¾Ý¿â²Ù×÷ÓÃ»§£¬¾ßÓÐÔöÉ¾¸Ä²éÈ¨ÏÞ*/

//µÇÂ¼ÑéÖ¤±ê¼Ç
#define LOGIN_CHK_RAND_PASSWD           "CHK_RAND_PASSWD"             /*Ëæ»úÃÜÂëÑéÖ¤±ê¼Ç*/

//Êý¾ÝÍ¬²½º¯Êý
extern "C" utype* DataSynch(const utype *puInParam ,TCtrlInfo *ptCtrlInfo);
extern "C" utype* xmlSend2Spms(const utype *uInput,TCtrlInfo *ptCtrlInfo);
void GetFtpCfg2(const char* label,string sDBSrvOpt, string sDBUsrOpt, string sDBPasswdOpt, string& ip, string&  user, string& passwd, string& path);
/////###################public BP #############################
utype* pubGetBaseAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* pPublicRight(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRegionByAddr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginGroupCmp(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pubGetBaseTime(const utype * inParam,TCtrlInfo *errInfo);
utype* pGroupTown(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pSubGrpQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pBaseDataSynch(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetBrief(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
int isChinese(char ch);
char* getBrief(const char* str, char* brief);
utype* pubBaseSrvHead(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubBaseSrvTail(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
int IsLeapYear(int year);
int GetDaysOfMonth(int year, int month);
int BaseCheckDate(const char* pSysDate, char* pErrMsg);

utype* pQryFuncList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckOpLogin(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetNoteMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckPdom(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQCountyGrp(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupCity(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLogGrpRole(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pubLoginRoleMenuManage(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUnsetTaskAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pUnsetTaskQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDealUnsetTask(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpgradeAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpgradeQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckLoginFavor(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRolFavorQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDimenGrpQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
char* ChangeDateFormat(const char* pDate, char* FormatDate);
utype* pBankPayChg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pBusiMastChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pMastCtrlChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetMastCtrl(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pGetGroupRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//ÎÄ¼þ½Ó¿Ú
char* GetLocalPath(char* pLocalPath);
void GetFileCfg(const char* pId, char* pHost, char* pUser, char* pPass, char* pPath, char* pLocalPath, TCtrlInfo *ptCtrlInfo);
utype * pInterLogin(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterGroup(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterRole(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterLogRol(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterRolPom(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterSynOrg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////####################ÄÚ´æÊý¾Ý¿â######################
utype * pInsAddLoginMsgToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInsAddRoleToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInsAddPodomToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInsAddRouteDataToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInsAddDataObjItemToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInsAddFuncDdataItemToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInsAddLoginRoleToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInsAddLoginPopedomToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInsAddProcedureToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInsAddRolePdomToMdb(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////####################¹¤ºÅÐÅÏ¢¹ÜÀí######################
utype* pLoginNoAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginNoUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginNoQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRolQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pCreateLogin(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginPdomQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginStfRel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pReportPdom(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStaffLog(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pSetLoginGroupRel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################### È¨ÏÞ¹ÜÀí zhangmeng #####################
utype* pFunctionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFunctionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQryPDOMList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProcedureAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDataItemAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDataItemQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncDataItemAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckFunc(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncProcQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProcDataQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncBusiCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncBusiQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleFunc(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////#################### LoginCheck ############################
void Get4AFlag();
char* str2upr(char* SrcStr);
int JudgeIP(const char *ipSrc, const char *ipDest);
int JudgeIP1(const char *ipSrc, const char *ipDest);
int CheckIP(const char *loginNo, const char *loginIP, int regionId, const char *isAgent, TCtrlInfo *ptCtrlInfo);
int CheckIP1(const char *loginNo, const char *loginIP, int regionId, const char *isAgent, TCtrlInfo *ptCtrlInfo);
utype* pCheckIP(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginCheckT(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetLoginMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetLoginCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLogintest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginPdomList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetLoginTheme(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pKFLogCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGet4AFlag(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pLoginMdlCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginThemeCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pShortcutCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pPdomSoundQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pLoginOut(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pDLoginMenu(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginMenuCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pGetOpAuthen(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetFuncVerify(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginMdlQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pShortcutQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pOutSysQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLogPdomAuth(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginCheckA(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/////#################### ¹¤ºÅ½âËø #######################
utype* pLoginUnLock(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////#################### ÃÜÂëÐÞ¸Ä #########################
utype* pMdfLoginPwd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################### ÃÜÂëÖØÖÃ#############################
utype* pRstLoginPwd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////#################### GroupTree ###########################
utype* pQuGroup(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

utype* pBusiChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDeptRegionChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ÐÐÕþÇøÓò¡¢±ê×¼µØÖ·²éÑ¯ ##################
utype* pGetPoliRegList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetTeleRegList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStandAddrByRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStandAddrByName(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRegionType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/////################# ÐÐÕþÇøÓò¹ÜÀí ##################
utype* pGetPoliRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPoliRegionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPoliRegionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ¹ÜÀíÇøÓò¹ÜÀí ##################
utype* pGetTeleRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTeleRegionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTeleRegionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ÇøÓò¹ØÏµ¹ÜÀí ##################
utype* pGetRegionRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRegionRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRegionRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRegionRelType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ±ê×¼µØÖ·¹ÜÀí ##################
utype* pGetStandAddr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStandAddrAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStandAddrUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ÒµÎñ×éÖ¯¹ÜÀí ##################
utype* pGroupAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupTree(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetGrpClass(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ÒµÎñ×éÖ¯ÉóºË ##################
utype* pUnAuditQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupAudit(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ¹¤ºÅ½ÇÉ«¹ÜÀí ##################
utype* pGrpLoginQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleTree(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRelAddChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ¹¤ºÅÈ¨ÏÞ¹ÜÀí ##################
utype* pFuncDomChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDataDomChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPopeDomCfm(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pubLoginMenuManage(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLogFavorQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLogFavorCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ½ÇÉ«¹ÜÀí ##################
utype* pRoleTreeList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleGrpCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleGrpQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleGrpList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ½ÇÉ«¹ØÏµ¹ÜÀí ##################
utype* pRoleRelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ½ÇÉ«È¨ÏÞ¹ØÏµ¹ÜÀí ##################
utype* pRoleFuncQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleDataQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRoleLogin(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRolePdom(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRolePdomCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRolFavorQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRolFavorCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTlphstAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTlphstUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTlphstDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTlphstGet(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ¹¤Î»ÐÅÏ¢¹ÜÀí ##################
utype* pStationList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStationAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStationUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginStatQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ¹¤ºÅ¹¤Î»¹ØÏµ¹ÜÀí ##################
utype* pLoginStationCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStatLoginMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStationLoginList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ¾ØÕó¹ØÏµ²éÑ¯ ##################
utype* pLoginRoleMtx(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRolePdomMtx(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ¹¤ºÅ¹ØÏµ¹ÜÀí ##################
utype* pTelephonistQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////###############Ô±¹¤ÐÅÏ¢¹ÜÀí ########################
utype* pStaffAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStaffUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStaffDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////###############¸ÚÎ»ÐÅÏ¢¹ÜÀí ########################
utype* pPositionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPositionQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPositionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////###############¹¤ºÅ¸ÚÎ»¹ØÏµÐÅÏ¢¹ÜÀí ########################
utype* pLoginPosQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginPosAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginPosDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//ÇøÓòÔÊÐíIPµØÖ·¹ÜÀí
utype* pRegionIpLmtCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//¿ìËÙ¿ª»§Ä£°åÅäÖÃ
utype* pIQuickInnetModelDict(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//Í¬²½×éÖ¯»ú¹¹Êý¾Ý
utype* pSyncGroup(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//²éÑ¯×ÔÖúÖÕ¶ËÐÅÏ¢
utype* pTermQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//¼Ó½âÃÜ¹¤ºÅÃÜÂë
utype* pEnDePasswd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//Á¬Í¨ÐÔ²âÊÔ
utype* pConnect(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//»ñÈ¡µØÊÐ´úÂë
utype* pGetCityCode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRegionIp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQGrpRegion(const utype *puInParam, TCtrlInfo *errInfo);

/////################# ¹«¸æÐÅÏ¢¹ÜÀí ##################
utype* pNoteAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteDelChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPublishNote(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPublishNoteChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteReadAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ×ÔÖúÖÕ¶Ë¹ÜÀí ##################
utype* pGetTerm(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTermAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTermUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTermDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* getMacAddr(const char *sHardInfo);

/////################# ÁÙÊ±ÊÚÈ¨¹ÜÀí ##################
utype* pTmpPdomQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomOp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomGrp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ×ÊÔ´¹ÜÀí add by chenhong(sx) ##################
utype * pResPhone(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pResSim(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pResPhoneImsi(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ¹¦ÄÜÈÏÖ¤¹ÜÀí ##################
utype* pFuncAuthGrpQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncAuthQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncGrpRelUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncGrpInUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncGrpInDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncGrpInAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncAuthUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncAuthDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncAuthAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncVerifyQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncVerifyAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncVerifyDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAuthenList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ²úÆ·ÈÏÖ¤¹ÜÀí ###################
utype* pGetProdOpAuthen(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdAuthenUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdAuthGrpQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdAuthGrpUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdAuthGrpDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdAuthGrpAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdAuthRelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdAuthRelUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdAuthRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pProdAuthRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCheckLoginPdom(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleAuthenCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleAuthenQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ½Ó¿Ú ###################
utype *pGetDataPdom(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pQRelGrpByGrpId(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ²âÊÔ ###################
utype* pQUserinfoByNo(const utype * inParam,TCtrlInfo *errInfo);

/////############## LoginStation ##############
utype* pLoginStationAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginStationQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginStationDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginStationUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//Í³Ò»´úÂë¹ÜÀí
utype* pUnicodeAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDynSrvQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDynSrvAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDynSrvUpd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDynSrvDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pCodeCreate(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pQUnicodeDef(const utype *puInParam , TCtrlInfo *ptCtrlInfo);
utype* pCodeTree(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUnicodeDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pUnicodeUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pQUnicodeClass(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//ÄÚ´æÊý¾Ý¿â
int spublicMDBclose(TCtrlInfo *pCtrlInfo);
int spublicMDBconn(char *pMdbLable, TCtrlInfo *pCtrlInfo);
utype* pCheckPdomInMDB(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pGetGroupParInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo); 
utype* pFunctionQry_guoxg(const utype *inParam , TCtrlInfo *errInfo);

utype* pProCitDisQry1(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDesHostUser(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p2091Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//²éÑ¯µ±Ç°µÇÂ¼¹¤ºÅÊÇ·ñ´æÔÚµÇÂ¼ÏÞÖÆ£¬´æÔÚÔòÐèÒª´Ó4AÏµÍ³µÇÂ¼NGBOSS
utype* pLoginSysChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//ÌúÍ¨ÈÚºÏÏà¹Ø
utype *pLoginBelonged(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRelGroupQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupAddDealed(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupUptDealed(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pAllGroupTown(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpRelAddChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRelGrpIdNameQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

utype* pQChnGroup(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

//¶àop
utype* pQryThemeDict(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pMdlTypeCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pMdlTypeQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQueryOpAuthen(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetFuncNote(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////####################ÈÕ³£ÈÎÎñ¹ÜÀí######################
utype* pTaskQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pTaskAdd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pTaskUpt(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pTaskDel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pTaskCntQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pTaskRemindQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/////####################¹¤×÷ÇøÉèÖÃ######################
utype* pPosFuncQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPosFuncCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/////####################Ïòµ¼######################
utype *pModelAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pModelUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pModelDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pModelQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pOpGuideAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pOpGuideUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pOpGuideQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pOpGuideDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pGetOpGuide(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pUnAuditGuideQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pGuideAuditUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
/////####################Ö¸±ê######################
utype* pGetTarget(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTargetCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTargetQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTargetAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTargetUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTargetDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//wangjxc add
utype* pOpRoleTreeList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpRoleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpRoleUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpRoleDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpRoleAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);  

utype* pWorkContQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pWorkContUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetContentId(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pWorkContAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetContentAll(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pWorkPanelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pWorkPanelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pWorkPanelUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pWorkPanelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetPanelAll(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpWorkPanelRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pCommRuleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCommRuleDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCommRuleUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRuleCode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pCommRuleAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pComRuleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pQThemeValue(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pThemeValueDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pThemeValueUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pThemeValueAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQOpTheme(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpThemeQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpRoleThemeCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pOpLoginQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginLogDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpLoginOprQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginOprDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//##################2941 µÇÂ¼Í³¼Æ·ÖÎö####################
utype* pQNumOfOpRole(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpLoginTime(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQNumOfOnLine(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//ÍÐÊÕÒøÐÐ¹ÜÀí 
utype* p2092(const utype *inParam, TCtrlInfo *errInfo);

//¸ÚÎ»½ÇÉ«¹ØÏµ¹ÜÀí
utype* pPosRoleAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPosRoleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPosRoleDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAllowableRoleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////##################»ñÈ¡ÃÜÂë####################
utype* pGetRandLoginPwd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pSendMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* kof(const utype *inParam, TCtrlInfo *errInfo);

utype* pCreateLoginSX(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

utype* pParFuncQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncListQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pQOrganise(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQueryPordOpAuth(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype *pPubGetDetailChnInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//Ð¡ÇøÐÅÏ¢²éÑ¯
utype* pBaseAreaQry(const utype *inParam,TCtrlInfo *ptCtrlInfo);

//ÒµÎñÌØÈ¨²éÑ¯
utype* pBusiPrivsQry(const utype *inParam,TCtrlInfo *ptCtrlInfo);

//²éÑ¯¹¤ºÅÏÂESOP½ÇÉ«ÏµÄÏÂ¼¶½ÇÉ«µÄ¹¤ºÅÐÅÏ¢
utype* pPubGetRoleLoginList(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

/*²éÑ¯¹¤ºÅÄÜ¹»²é¿´µÄ¹«¸æfor ESOP*/
utype* pLoginNoteQry(const utype* puInparam,TCtrlInfo *ptCtrlInfo);

/*ÑéÖ¤ÒµÎñ±àÂëÊÇ·ñ´æÔÚ*/
utype* pChkBusiCode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pFuncRelAdd(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

/*ÒµÎñÌØÈ¨Ôö¼Ó*/
utype* pBusiPrivsAdd(const utype* puInParam,TCtrlInfo* ptCtrlInfo);
/*ÒµÎñÌØÈ¨ÐÞ¸Ä*/
utype * pBusiPrivsUpt(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

utype* pGetRegionCode(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pPrivsDomChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pSunShineUpt(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pSunShineQry(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

/*·ÑÓÃÂäµØµÄÓªÒµÌü²éÑ¯*/
utype* pLoginGroupQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pLoginRoleCheck(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

utype* pLoginAgentQry(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

utype* pYXLogCheck(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pChannelClassAdd(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pChannelClassUpt(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pChnKindAdd(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

utype* pGroupLevel(const utype* puInParam,TCtrlInfo *ptCtrlInfo);


utype* pGroupMacAdd(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pGroupMacDel(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pGroupMacQry(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

utype* pAreaBillQry(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAreaBillAdd(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAreaBillDel(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pWlanHSpotQry(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pWlanHSpotAdd(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pWlanHSpotDel(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pAreaBillUpt(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pWlanHSpotUpt(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pLoginAreaQry(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
/*²éÑ¯Ê¡¼¶Group_id*/
utype* pProvinceGrp(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pLgnGrpQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLgnGrpAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLgnGrpUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLgnGrpDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
/*²éÑ¯bs_function_dict±íÈ«Á¿Êý¾Ý*/
utype* pFuncAllQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*4A½ð¿âÄ£Ê½ÈÏÖ¤*/
utype* p2901(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* p4AVerifyQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

utype* pLoginByGroupQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//¹¤ºÅ½ÇÉ«È¨ÏÞ(¹¤ºÅÈ¨ÏÞ)
utype* pLoginNoPopedomQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//¹¤ºÅÐÅÏ¢½Ó¿Ú
utype* pLoginKFQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//¹«¸æ·¢²¼ÏµÍ³BP
utype* pInfoPubQry(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pInfoPubAdd(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pInfoPubUpt(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pInfoPubDelChk(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pInfoPubDel(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pPublishInfoPub(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pPublishInfoPubChk(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pGetHostUserPwd(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pLoginReadInfoAdd(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pGetFuncInfoPub(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pGetInfoPubMsg(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pLoginReadInfoQry(const utype *puInParam,TCtrlInfo *ptCtrlInfo);
utype* pPareGroupQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginCheckTest(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//CTDÐ¡Çø¹ÜÀí
utype *pGetBaseArea(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pBaseAreaAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pBaseAreaUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pBaseAreaDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pBaseAreaQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//4AÈÕÖ¾Éó¼Æ
utype *p4A_log_audit(const utype *inParam , TCtrlInfo *errInfo);

//¿ÕÖÐÑ¡ºÅÐ¡Çø´úÂë
utype* pAreaCodeQry(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAreaCodeAdd(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAreaCodeDel(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pXMLtest(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

#endif
