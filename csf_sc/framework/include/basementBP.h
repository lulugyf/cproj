#ifndef __BASEMENTBP_H__
#define __BASEMENTBP_H__

//ʡ����֯��������
#define CHINA_GROUP                     "1000"         /*�й���֯�����ڵ�*/
#define PROVINCE_GROUP                  "10011"        /*��֯����ʡ�ڵ�, ����*/
#define SHANXI_PROVINCE_GROUP           "10011"        /*ɽ����֯����ʡ�ڵ�*/
#define SICHUAN_PROVINCE_GROUP          "10008"        /*�Ĵ���֯����ʡ�ڵ�*/
#define JILIN_PROVINCE_GROUP            "10013"        /*������֯����ʡ�ڵ�*/
#define HEILONGJIANG_PROVINCE_GROUP     "10014"        /*��������֯����ʡ�ڵ�*/
#define ANHUI_PROVINCE_GROUP            "10017"        /*������֯����ʡ�ڵ�*/
#define ROOT_TD_GROUP                   "100170"       /*������ͨ��֯����ʡ���ڵ�*/

#define ROOT_OP_ROLE                   0               /*op��ɫ���ڵ�*/

#define ROLE_ROOT "100000"                             /*��ɫ������ڵ�*/
#define REGION_ROOT 10                                 /*������ڵ�*/
#define BASE_IN_WORKN_OPTCODE "CX01"                   /*����������ű���*/

//�������Ͷ���
#define MNG_LOGIN_FLAG  "2"                            /*��������Ϊϵͳ����Ա*/

#define SYS_END_DATE "20500101000000"                  /*ϵͳĬ�Ͻ���ʱ��Ϊ2050-01-01*/

#define POLI_REGION "0"                                /*������������*/
#define TELE_REGION "1"                                /*������������*/

#define INTERFACE_WEB "11"                             /*�����֤����Ϊǰ̨��֤*/

//�ڴ����ݿ��ǩ
#define LABELMDB "imdb"                                /*ϵͳ���ڴ����ݿ��û�����������Ȩ��*/
#define LABELMDBQUERY "imdb_query"                     /*�ڴ����ݿ��ѯ�û������в�ѯȨ��*/
#define LABELMDBOPR "imdb_opr"                         /*�ڴ����ݿ�����û���������ɾ�Ĳ�Ȩ��*/

//��¼��֤���
#define LOGIN_CHK_RAND_PASSWD           "CHK_RAND_PASSWD"             /*���������֤���*/

//����ͬ������
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

//�ļ��ӿ�
char* GetLocalPath(char* pLocalPath);
void GetFileCfg(const char* pId, char* pHost, char* pUser, char* pPass, char* pPath, char* pLocalPath, TCtrlInfo *ptCtrlInfo);
utype * pInterLogin(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterGroup(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterRole(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterLogRol(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterRolPom(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pInterSynOrg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////####################�ڴ����ݿ�######################
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

/////####################������Ϣ����######################
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

/////################### Ȩ�޹��� zhangmeng #####################
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
/////#################### ���Ž��� #######################
utype* pLoginUnLock(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////#################### �����޸� #########################
utype* pMdfLoginPwd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################### ��������#############################
utype* pRstLoginPwd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////#################### GroupTree ###########################
utype* pQuGroup(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

utype* pBusiChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDeptRegionChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# �������򡢱�׼��ַ��ѯ ##################
utype* pGetPoliRegList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetTeleRegList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStandAddrByRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStandAddrByName(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRegionType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
/////################# ����������� ##################
utype* pGetPoliRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPoliRegionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPoliRegionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ����������� ##################
utype* pGetTeleRegion(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTeleRegionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTeleRegionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# �����ϵ���� ##################
utype* pGetRegionRel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRegionRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRegionRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRegionRelType(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ��׼��ַ���� ##################
utype* pGetStandAddr(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStandAddrAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStandAddrUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ҵ����֯���� ##################
utype* pGroupAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupTree(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetGrpClass(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ҵ����֯��� ##################
utype* pUnAuditQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupAudit(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ���Ž�ɫ���� ##################
utype* pGrpLoginQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleTree(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRelAddChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRoleDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ����Ȩ�޹��� ##################
utype* pFuncDomChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pDataDomChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pPopeDomCfm(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pubLoginMenuManage(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLogFavorQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLogFavorCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ��ɫ���� ##################
utype* pRoleTreeList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleGrpCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleGrpQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleGrpList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ��ɫ��ϵ���� ##################
utype* pRoleRelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRoleRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ��ɫȨ�޹�ϵ���� ##################
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

/////################# ��λ��Ϣ���� ##################
utype* pStationList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStationAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStationUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginStatQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ���Ź�λ��ϵ���� ##################
utype* pLoginStationCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetStatLoginMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStationLoginList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# �����ϵ��ѯ ##################
utype* pLoginRoleMtx(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRolePdomMtx(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ���Ź�ϵ���� ##################
utype* pTelephonistQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRelQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRelAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginRelDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////###############Ա����Ϣ���� ########################
utype* pStaffAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStaffUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pStaffDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////###############��λ��Ϣ���� ########################
utype* pPositionAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPositionQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPositionUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////###############���Ÿ�λ��ϵ��Ϣ���� ########################
utype* pLoginPosQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginPosAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginPosDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//��������IP��ַ����
utype* pRegionIpLmtCfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//���ٿ���ģ������
utype* pIQuickInnetModelDict(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//ͬ����֯��������
utype* pSyncGroup(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//��ѯ�����ն���Ϣ
utype* pTermQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//�ӽ��ܹ�������
utype* pEnDePasswd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//��ͨ�Բ���
utype* pConnect(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
//��ȡ���д���
utype* pGetCityCode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetRegionIp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQGrpRegion(const utype *puInParam, TCtrlInfo *errInfo);

/////################# ������Ϣ���� ##################
utype* pNoteAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteDelChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteUpt(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPublishNote(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPublishNoteChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pNoteReadAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# �����ն˹��� ##################
utype* pGetTerm(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTermAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTermUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pTermDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* getMacAddr(const char *sHardInfo);

/////################# ��ʱ��Ȩ���� ##################
utype* pTmpPdomQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomList(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomOp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pTmpPdomGrp(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ��Դ���� add by chenhong(sx) ##################
utype * pResPhone(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pResSim(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype * pResPhoneImsi(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////################# ������֤���� ##################
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

/////################# ��Ʒ��֤���� ###################
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

/////################# �ӿ� ###################
utype *pGetDataPdom(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype *pQRelGrpByGrpId(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

/////################# ���� ###################
utype* pQUserinfoByNo(const utype * inParam,TCtrlInfo *errInfo);

/////############## LoginStation ##############
utype* pLoginStationAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginStationQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginStationDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLoginStationUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//ͳһ�������
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

//�ڴ����ݿ�
int spublicMDBclose(TCtrlInfo *pCtrlInfo);
int spublicMDBconn(char *pMdbLable, TCtrlInfo *pCtrlInfo);
utype* pCheckPdomInMDB(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pGetGroupParInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo); 
utype* pFunctionQry_guoxg(const utype *inParam , TCtrlInfo *errInfo);

utype* pProCitDisQry1(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pDesHostUser(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* p2091Cfm(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//��ѯ��ǰ��¼�����Ƿ���ڵ�¼���ƣ���������Ҫ��4Aϵͳ��¼NGBOSS
utype* pLoginSysChk(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//��ͨ�ں����
utype *pLoginBelonged(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pRelGroupQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupAddDealed(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGroupUptDealed(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pAllGroupTown(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pGrpRelAddChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pRelGrpIdNameQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

utype* pQChnGroup(const utype * puInParam, TCtrlInfo *ptCtrlInfo);

//��op
utype* pQryThemeDict(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pMdlTypeCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pMdlTypeQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQueryOpAuthen(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pGetFuncNote(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////####################�ճ��������######################
utype* pTaskQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pTaskAdd(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pTaskUpt(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pTaskDel(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pTaskCntQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
extern "C" utype* pTaskRemindQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);

/////####################����������######################
utype* pPosFuncQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pPosFuncCfm(const utype *inParam, TCtrlInfo *ptCtrlInfo);
/////####################��######################
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
/////####################ָ��######################
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

//##################2941 ��¼ͳ�Ʒ���####################
utype* pQNumOfOpRole(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pOpLoginTime(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQNumOfOnLine(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

//�������й��� 
utype* p2092(const utype *inParam, TCtrlInfo *errInfo);

//��λ��ɫ��ϵ����
utype* pPosRoleAdd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPosRoleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pPosRoleDel(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAllowableRoleQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/////##################��ȡ����####################
utype* pGetRandLoginPwd(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pSendMsg(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* kof(const utype *inParam, TCtrlInfo *errInfo);

utype* pCreateLoginSX(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

utype* pParFuncQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pFuncListQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pQOrganise(const utype *puInParam, TCtrlInfo *ptCtrlInfo);
utype* pQueryPordOpAuth(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype *pPubGetDetailChnInfo(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//С����Ϣ��ѯ
utype* pBaseAreaQry(const utype *inParam,TCtrlInfo *ptCtrlInfo);

//ҵ����Ȩ��ѯ
utype* pBusiPrivsQry(const utype *inParam,TCtrlInfo *ptCtrlInfo);

//��ѯ������ESOP��ɫϵ��¼���ɫ�Ĺ�����Ϣ
utype* pPubGetRoleLoginList(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

/*��ѯ�����ܹ��鿴�Ĺ���for ESOP*/
utype* pLoginNoteQry(const utype* puInparam,TCtrlInfo *ptCtrlInfo);

/*��֤ҵ������Ƿ����*/
utype* pChkBusiCode(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

utype* pFuncRelAdd(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

/*ҵ����Ȩ����*/
utype* pBusiPrivsAdd(const utype* puInParam,TCtrlInfo* ptCtrlInfo);
/*ҵ����Ȩ�޸�*/
utype * pBusiPrivsUpt(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

utype* pGetRegionCode(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pPrivsDomChk(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pSunShineUpt(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pSunShineQry(const utype* puInParam,TCtrlInfo *ptCtrlInfo);

/*������ص�Ӫҵ����ѯ*/
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
/*��ѯʡ��Group_id*/
utype* pProvinceGrp(const utype* puInParam,TCtrlInfo *ptCtrlInfo);
utype* pLgnGrpQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLgnGrpAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLgnGrpUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* pLgnGrpDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
/*��ѯbs_function_dict��ȫ������*/
utype* pFuncAllQry(const utype *puInParam, TCtrlInfo *ptCtrlInfo);

/*4A���ģʽ��֤*/
utype* p2901(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype* p4AVerifyQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

utype* pLoginByGroupQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//���Ž�ɫȨ��(����Ȩ��)
utype* pLoginNoPopedomQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//������Ϣ�ӿ�
utype* pLoginKFQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
//���淢��ϵͳBP
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

//CTDС������
utype *pGetBaseArea(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pBaseAreaAdd(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pBaseAreaUpt(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pBaseAreaDel(const utype *uInParam, TCtrlInfo *ptCtrlInfo);
utype *pBaseAreaQry(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

//4A��־���
utype *p4A_log_audit(const utype *inParam , TCtrlInfo *errInfo);

//����ѡ��С������
utype* pAreaCodeQry(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAreaCodeAdd(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pAreaCodeDel(const utype* puInParam, TCtrlInfo *ptCtrlInfo);
utype* pXMLtest(const utype *uInParam, TCtrlInfo *ptCtrlInfo);

#endif
