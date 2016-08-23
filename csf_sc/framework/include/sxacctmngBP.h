/*BP函数声明*/
#include "framework.h"
#include "pubinterface.h"
/*wangyla 练习*/
utype* pWylTest(const utype* inParam, TCtrlInfo* errInfo);
utype* pYanKMA(const utype * inParam,TCtrlInfo *errInfo);

/*公共函数*/
int PublicGetLoginNoType( char *inLoginNo );
int checkDefOwePlan(const char *pay_type, const char *act_item);
int	checkDefSpecOwePlan(const char *pay_type, const char *act_item);
int AddMonth(int yearmonth,int addmonth);
int GetFeeValue(char arrFeeCode[][8+1],long arrFee[],char *strFeeList,char *OutResult);
double round_F(double source, int num);
int otl_UserStatuInterface(BC_PUB_OPERATION_INPUT_TYPE *bc_pub_operation_input,INTER_PUBINFO_TYPE *inter_pubinfo);
int writeLoginDailyRPT(RPT_BUSI_INFO_TYPE *rpt_busi_info,INTER_PUBINFO_TYPE *inter_pubinfo);
int Getpayname(char* inPayType,char* outPayCode,char* outPayName);
void getCycleProduct(int md, char* s);
void freeinfo(struct detail_info *detailhead);
int GetAccountName(char* InAccountType,char* outAcctTypeName);
char *substr_q(char *fat,char flag);
char *substr_wtt(char *father,char flag,int site);
char *pGetConFee(char *father,char flag,int site);
char *LRTrim(char *str);
utype * pGetConFee(const utype *inParam , TCtrlInfo *errInfo);
utype* pGetChgGroup(const utype * inParam,TCtrlInfo *errInfo);
/*详单查询函数*/
int query_detail(char *phone,int qtype,char *begtime,char *endtime,char *result,struct detail_info *detailinfo,char *servip,int servport,int tout,char *para[9]);
void substring(char* sz,const char* szSrc,int begin,int end);
char *substr_wt(char *father,char flag,int site);
int conversation(TPSVCINFO *rqst, FBFR32 *transIN, FBFR32 *fbfr, char *record_str, char *temp_buf,char *conn);
int formatOtherParty( char *szDealedOther );
int SecondToTimeString(int nSecond, char* szTime, int nSize);
int sp_search(char * sp_code, char * oper_code, char * sp_name, char * oper_name, char * open_price, char * serv_code);
char *substr(char *source,int begin,int num);
int PublicGetLastDayOfMonth(int YearMonth);
int GetBalanceFee(char* szPhoneNo, double* pFee,char* InIP,int InPort);
//int conversation1(int rqst, FBFR *fbfr, char *record_str, char *temp_buf);
utype* pPrepayTranIn(const utype* inParam, TCtrlInfo *errInfo);

/*免费分钟数查询*/
int tcp_connect(const char * server_name, int port);
int tcp_writen(int fd, char *ptr, int nbytes);
int tcp_readn(int fd, char *ptr, size_t n);
int tcp_close(int sd);

/*调用服务*/
void replaceParam(char *strbuf,const char *param_id,const char *param_value);
int payReplaceParam(char *strbuf,char *pBusiTemplate,char *pXMLFinal);
void findParamValue(char *in_strbuf,const char *in_param_id,char * in_param_type,char *out_param_value);
int tpcallServer(char* in_server_name,char* in_input_params,char* out_return_code,char* out_return_msg,char* rev_buf);

/*充值卡信息查询*/
int split1(char *string, char *fields[],int nfields,char  *sep);
int publicGetValueByKey(char *OStr,char* ekey,char* ebark,char* retval);
int pubGetCardName(char* InCardType,char* outCardName);

/*缴费相关*/
utype* p8000Cfm(const utype * inParam, TCtrlInfo *errInfo);
utype* p8000GrpCfm(const utype * inParam, TCtrlInfo *errInfo);
utype* p8000_Valid(const utype * inParam,TCtrlInfo *errInfo);
utype* p8000_GrpValid(const utype * inParam,TCtrlInfo *errInfo);
utype* pCheckPayMoney(const utype * inParam, TCtrlInfo *errInfo);
utype* pRecordPayLog(const utype * inParam, TCtrlInfo *errInfo);
utype* pGetConMsgFee(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetDynamicUnbill(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetPhoneFee(const utype * inParam,TCtrlInfo *errInfo);
utype* pMulSimOpen(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserOpenOpr(const utype * inParam,TCtrlInfo *errInfo);
utype* pMediaUserOpen(const utype * inParam,TCtrlInfo *errInfo);
utype* pMulConUserOpen(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetMulSimOwe(const utype * inParam,TCtrlInfo *errInfo);
utype * pConOpen(const utype *inParam , TCtrlInfo *errInfo);
utype * pConOpenflag(const utype *inParam , TCtrlInfo *errInfo);

utype* pSpecialPayOwe(const utype * inParam,TCtrlInfo *errInfo);
//utype* pSpecialPayOwe(const utype * inParam,TCtrlInfo *errInfo,TCtrlInfo *errInfo_other);//modify by xianjb for test
utype* getDelayRate(const utype * inParam,TCtrlInfo *errInfo);
utype* getDelayFee(const utype * inParam,TCtrlInfo *errInfo);
utype* pHWFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pHandFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pAllFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pMarkOweQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pMarkQuery(const utype * inParam,TCtrlInfo *errInfo);
utype* pPayedFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pKFBillQuery(const utype * inParam,TCtrlInfo *errInfo);
utype* pBillQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8003Init(const utype *inParam, TCtrlInfo *errInfo);
utype* p8003Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUnbillFee(const utype *inParam , TCtrlInfo *errInfo);
utype* pBossToCrm(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetDelayRate(const utype *inParam , TCtrlInfo *errInfo);
utype* pGetDelayRateNew(const utype *inParam , TCtrlInfo *errInfo);
utype* pGetDelayFee(const utype *inParam , TCtrlInfo *errInfo);
utype* pGetControlOweFee(const utype * inParam,TCtrlInfo *errInfo);

utype* p8000MR(const utype * inParam,TCtrlInfo *errInfo);
utype* pMarketFee(const utype * inParam,TCtrlInfo *errInfo);
utype* p8005(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetVoiceFh(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetInvNote(const utype *inParam, TCtrlInfo *errInfo);
utype* GetMemBillDyn(const utype *inParam, TCtrlInfo *errInfo);
//utype* GetMemBillDyn(const utype *inParam, TCtrlInfo *errInfo,TCtrlInfo *errInfo_other);//modify by xianjb for test
utype* GetMemBillDynNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUnbillFeeInMid(const utype *inParam, TCtrlInfo *errInfo);

utype* p8107PayQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pHandFeeSpe(const utype * inParam,TCtrlInfo *errInfo);
utype* pBackFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pQBankInfo( const utype *inParam, TCtrlInfo *errInfo );
utype* pQBankOrPrepayInfo(const utype *inParam, TCtrlInfo *errInfo );
utype* pQPrePayByBank( const utype *inParam, TCtrlInfo *errInfo );
utype* pSendShortMsg(const utype *inParam, TCtrlInfo *errInfo);
utype * pGetLoginGroup(const utype *inParam , TCtrlInfo *errInfo);

/*账期查询*/
utype* pDynTypeIVRQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pDynTypeAccQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pDynTypeQry(const utype * inParam,TCtrlInfo *errInfo);

/*缴费补充需求与遗漏开发*/
utype* pUpdateMediaMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* pWriteOffAccount(const utype *inParam, TCtrlInfo *errInfo);
utype* pSendChargeMess(const utype *inParam, TCtrlInfo *errInfo); 
utype* pUpUserExpireTime(const utype *inParam, TCtrlInfo *errInfo); 
utype* pSalesActFreeCharge(const utype *inParam, TCtrlInfo *errInfo); 
utype* pGetWriteOffFlagAndMonth(const utype *inParam, TCtrlInfo *errInfo); 
utype* pInsertAcctBook(const utype *inParam, TCtrlInfo *errInfo); 
utype* pInsertIgwabm(const utype *inParam, TCtrlInfo *errInfo); 
utype* pCheckMediaFlag(const utype *inParam, TCtrlInfo *errInfo);
utype* pInsertPayMent(const utype *inParam, TCtrlInfo *errInfo);
utype* pReadWriteOffPlan(const utype * inParam,TCtrlInfo *errInfo);

/*有效期查询*/
utype* p8128(const utype *inParam, TCtrlInfo *errInfo);

utype* p8104_App(const utype *inParam, TCtrlInfo *errInfo);
utype* p8104QryHis(const utype * inParam,TCtrlInfo *errInfo);
utype* p8108Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8109Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* pBusiCardPayQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pQryBalance(const utype * inParam,TCtrlInfo *errInfo);

/*查询用户账号,ID_NO*/
utype* pMultConQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pUserDeadInfoQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pFunConUserQry(const utype * inParam,TCtrlInfo *errInfo);

/*预存与欠费查询*/
utype* pFeeOweQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8135Cust(const utype * inParam,TCtrlInfo *errInfo);
utype* p8101Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* pFeePayQry(const utype * inParam,TCtrlInfo *errInfo);

/*发票打印*/
utype* p8000Print(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetBrandIdName(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetLastPayTime(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetBillCycle(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetVoiceFh(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetInvNote(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUnbillFeeInMidByConNo(const utype * inParam,TCtrlInfo *errInfo);
utype *pGetUnbillFeeByConNo( const utype *inParam , TCtrlInfo *errInfo);
utype* p8000PrintComm(const utype * inParam,TCtrlInfo *errInfo);
utype* p8000BankPrint(const utype * inParam,TCtrlInfo *errInfo);
utype* p8004Init(const utype *inParam, TCtrlInfo *errInfo);
utype* p8004Print(const utype *inParam, TCtrlInfo *errInfo);
utype* p8004ConInit(const utype *inParam, TCtrlInfo *errInfo);
utype* p8001Print(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetFundLastPayTime( const utype *inParam, TCtrlInfo *errInfo);
int Mdoubletocase(double sum,char *ccase);
utype* pInvoiceModelInstant(const utype* puInParam, TCtrlInfo *pCtrlInfo);
utype* p8017Print(const utype* puInParam, TCtrlInfo *pCtrlInfo);
utype* p8020GrpPrint(const utype* puInParam, TCtrlInfo *pCtrlInfo);
utype* p8209Cfm(const utype* puInParam, TCtrlInfo *pCtrlInfo);
utype* p8209Back(const utype* puInParam, TCtrlInfo *pCtrlInfo);
utype* p8209Print(const utype* puInParam, TCtrlInfo *pCtrlInfo);
utype* p8209Qry(const utype* puInParam, TCtrlInfo *pCtrlInfo);
utype* pUnfilledForm(const utype* puInParam, TCtrlInfo *pCtrlInfo);
utype* pSPDBankPrint(const utype* puInParam, TCtrlInfo *pCtrlInfo);
utype* pSPDBankSuccess(const utype* puInParam, TCtrlInfo *pCtrlInfo);

/*账单打印*/
utype* p8100(const utype * inParam,TCtrlInfo *errInfo);
utype* p8102(const utype * inParam,TCtrlInfo *errInfo);
utype* p8100FeeVary(const utype * inParam,TCtrlInfo *errInfo);
utype* p8100Recommend(const utype * inParam,TCtrlInfo *errInfo);
utype* pBillCycleQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8000BillPrint(const utype * inParam,TCtrlInfo *errInfo);
utype* p8100Pnt(const utype * inParam,TCtrlInfo *errInfo);
utype* p8102ShowQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8100FavQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8100PayQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pPhoneQueryBill(const utype * inParam,TCtrlInfo *errInfo);
utype* pPhoneQryBill(const utype * inParam,TCtrlInfo *errInfo);
utype* p8103(const utype * inParam,TCtrlInfo *errInfo);
utype* p8103(const utype * inParam,TCtrlInfo *errInfo);

utype* p8100HomePage(const utype * inParam,TCtrlInfo *errInfo);
utype* pQrySixBillInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* pQryBillScheme(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryBillHome(const utype *inParam, TCtrlInfo *errInfo);
utype* pBillQryForNew(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryBillApxPage(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryBillPay(const utype *inParam, TCtrlInfo *errInfo);
utype* p8143Pnt(const utype *inParam, TCtrlInfo *errInfo);
utype* p8143SendSms(const utype *inParam, TCtrlInfo *errInfo);
utype* pQryDetailUsed(const utype *inParam, TCtrlInfo *errInfo);
utype* p8143SendEmail(const utype *inParam, TCtrlInfo *errInfo);

utype* pBillDetailQry(const utype *inParam, TCtrlInfo *errInfo);
utype* pDetailShowQry(const utype *inParam, TCtrlInfo *errInfo);

utype* pWapBillQry(const utype *inParam, TCtrlInfo *errInfo);

utype* pGetUnbillFeeByConNoForBill(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUnbillFeeForBill(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUnbillFeeInMidForBill(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetUnbillFeeInMidByConNoForBill(const utype *inParam, TCtrlInfo *errInfo);

/*账本信息查询*/
utype* pQbalance(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetCurPre(const utype *inParam, TCtrlInfo *errInfo);
utype* pQueryWap(const utype *inParam, TCtrlInfo *errInfo);

/*账本专款费用查询*/
utype* pSpecialFeeQry( const utype *inParam, TCtrlInfo *errInfo );

/*分月划拨缴费返费查询*/
utype* pReturnFeeQry(const utype * inParam,TCtrlInfo *errInfo);

/*详单查询*/
utype* p8110print(const utype * inParam,TCtrlInfo *errInfo);
utype* pHW8117print(const utype * inParam,TCtrlInfo *errInfo);
utype* pGprsUsedQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8110Selfmms(const utype * inParam,TCtrlInfo *errInfo);
utype* pQryDetailInfo(const utype * inParam,TCtrlInfo *errInfo);/*boss侧详单查询服务*/
utype* pDetailPush(const utype * inParam,TCtrlInfo *errInfo);/*peb侧详单查询服务*/
utype* pQryDetailInfoPub(const utype * inParam,TCtrlInfo *errInfo);/*add 详单公共BP*/
/*sp查询*/
utype* p8117SpBack(const utype * inParam,TCtrlInfo *errInfo);

/*根据procId套餐月租费用查询*/
utype* pQRtByPrcId(const utype *inParam, TCtrlInfo *errInfo);

/*积分查询*/
utype* pYearMarkQry(const utype * inParam,TCtrlInfo *errInfo);

/*根据服务号码、服务标识查询保留预存账本信息*/
utype* pQChkBookDeposit( const utype *inParam, TCtrlInfo *errInfo );

/*根据缴费流水、用户id查询用户缴费费用信息*/
utype* pQFeeByAccept( const utype *inParam, TCtrlInfo *errInfo );

/*缴费冲正*/
utype* p8003Init(const utype *inParam, TCtrlInfo *errInfo);  
utype* p8003Cfm(const utype *inParam, TCtrlInfo *errInfo);  
utype* pGetPayBackMsg(const utype *inParam, TCtrlInfo *errInfo);  
utype* pPayBackOpr(const utype *inParam, TCtrlInfo *errInfo);  
utype* pPayBackFeeOpr(const utype *inParam, TCtrlInfo *errInfo);
utype* p8003Print(const utype *inParam, TCtrlInfo *errInfo);

void Mchartocase(char *dest,char c);

/*呆坏账回收*/
utype* pQ8006Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pI8006Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p8006Print(const utype *inParam, TCtrlInfo *errInfo);
utype* pDeadSpecWriteOff(const utype *inParam , TCtrlInfo *errInfo);
utype* pDeadWriteOff(const utype *inParam , TCtrlInfo *errInfo);
utype* pDeadWriteOffOpr(const utype *inParam , TCtrlInfo *errInfo);
utype* p8006Print(const utype *inParam, TCtrlInfo *errInfo);
utype* pDeadGetLastPayTime( const utype *inParam, TCtrlInfo *errInfo );
utype* pBlackListToCrm( const utype *inParam, TCtrlInfo *errInfo );

utype* pQAcctDetailInfo( const utype *inParam, TCtrlInfo *errInfo );
utype* pQAcctGroup( const utype *inParam, TCtrlInfo *errInfo );
utype* pQAdjRemark( const utype *inParam, TCtrlInfo *errInfo );
utype* pQBillType( const utype *inParam, TCtrlInfo *errInfo );

utype* pDeadWriteOffAccount(const utype *inParam, TCtrlInfo *errInfo);
utype * pReadDeadWriteOffPlan(const utype *inParam , TCtrlInfo *errInfo);

/*呆坏账回收回退*/
utype* pQ8007Qry( const utype *inParam, TCtrlInfo *errInfo );
utype* p8007(const utype *inParam, TCtrlInfo *errInfo);
utype* p8007Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p8007Print(const utype *inParam, TCtrlInfo *errInfo);
utype* pDeadWriteOffCon(const utype *inParam, TCtrlInfo *errInfo);
utype* pDeadPayBackOpr(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetPayDeadBackMsg(const utype *inParam, TCtrlInfo *errInfo);

/*客户呆坏账信息查询*/
utype* pDeadOweQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetDeadOwe(const utype* inParam,TCtrlInfo* errInfo);
utype* pGetCustDeadOwe(const utype* inParam,TCtrlInfo* errInfo);

/*呆坏账发票打印*/
utype* p8007Print(const utype *inParam, TCtrlInfo *errInfo);

/*查询呆坏账个数*/
utype* pQBadActCou(const utype *inParam, TCtrlInfo *errInfo);

/*单个用户费用补收*/
utype* pQ8010Qry( const utype *inParam, TCtrlInfo *errInfo );
utype* pQ8010InitSp( const utype *inParam, TCtrlInfo *errInfo );
utype* FillDetailMsg( const utype *inParam, TCtrlInfo *errInfo );
utype* p8010SPCfm( const utype *inParam, TCtrlInfo *errInfo );
utype* p8010Cfm( const utype *inParam, TCtrlInfo *errInfo );
utype* p8010SPBackQry( const utype *inParam, TCtrlInfo *errInfo );
utype* p8010SPBackOut( const utype *inParam, TCtrlInfo *errInfo );

utype* p8010BillInit( const utype *inParam, TCtrlInfo *errInfo );
utype* p8010FeeBackQry( const utype *inParam, TCtrlInfo *errInfo );

/*客户的离网用户是否有呆帐*/
utype* pB_ZWZDCX02( const utype *inParam, TCtrlInfo *errInfo );
utype* pDeadOweChk( const utype *inParam, TCtrlInfo *errInfo );

/*查询用户消费金额*/
void AnalyseString(char* szOut, char* szIn, char* szHead, char cFliter, bool bIn);
utype* pB_ZWZDCX01( const utype *inParam, TCtrlInfo *errInfo );
utype* pExpenseQry( const utype *inParam, TCtrlInfo *errInfo );
char* TrimSpace(char* src);

/*查询离网用户基本信息*/
utype* pUserDeadInfo(const utype *inParam, TCtrlInfo *errInfo);

/*查询银行名称以及支票费用*/
utype* pQBankOrPrepayInfo(const utype *inParam, TCtrlInfo *errInfo);
utype* pQPrePayByBank( const utype *inParam, TCtrlInfo *errInfo );
utype* pQBankInfo( const utype *inParam, TCtrlInfo *errInfo );

/*卡类缴费查询*/
utype* p8000BaseMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* pCheckInterPay(const utype *inParam, TCtrlInfo *errInfo);
utype* p8000PayQuery(const utype *inParam, TCtrlInfo *errInfo);


/*免费分钟数查询*/
utype* p8123Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p8123Valid(const utype * inParam,TCtrlInfo *errInfo);

/*积分接口*/
utype* pMarkPre(const utype * inParam,TCtrlInfo *errInfo);
utype* pMarkUnPre(const utype * inParam,TCtrlInfo *errInfo);
utype* pMarkPreQry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8832Query(const utype * inParam,TCtrlInfo *errInfo);
utype* p8833Query(const utype * inParam,TCtrlInfo *errInfo);
utype* pChgQuery(const utype * inParam,TCtrlInfo *errInfo);

/*营销赠费查询*/
utype* p8134Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8134Init(const utype * inParam,TCtrlInfo *errInfo);

/*短信查询*/
utype* pPayDxValid(const utype * inParam,TCtrlInfo *errInfo);
utype* pSmsQuery(const utype * inParam,TCtrlInfo *errInfo);

/*空中充值*/
utype* p8016(const utype *inParam, TCtrlInfo *errInfo);
utype* p8016AgentTranOut(const utype *inParam, TCtrlInfo *errInfo);
utype* p8016Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p8016Check(const utype *inParam, TCtrlInfo *errInfo);
utype* p8016SendShortMsg(const utype *inParam, TCtrlInfo *errInfo);    
utype* p8016Qry(const utype *inParam, TCtrlInfo *errInfo);
utype* pSendShortMsg(const utype *inParam, TCtrlInfo *errInfo);
int JM8016(unsigned char* strD,char* strE,unsigned char* out_data_head);
int BcdToAsc_(unsigned char *dest, unsigned char *src, int length);
int check_passwd(char *in_passwd,char *en_passwd,char *pwd_flag);
static void permute(char *inblock, char perm[16][16][8], char *outblock);
static void iter(int num, char *inblock, char *outblock);
static void perminit(char perm[16][16][8], char p[64]);
static void kinit(char *key);
static void sinit(void);
static void p32init(void);
static void f(char *right, int num, char *fret);
static void expand(char *right, char *bigright);
static void contract(char *in48, char *out32);
static void perm32(char *inblock, char *outblock);
void desinit(char *key);
void endes(unsigned char *inblock, unsigned char *outblock);
void dedes(unsigned char *inblock, unsigned char *outblock);
int DES(int op, char *key, char *inblock, char *outblock, int len);
char *GenerateMAC(int method, char *databuf, int datalen, char *key, char *MAC);
int AscToBcd_(unsigned char *dest, unsigned char *src, int length);
void GenNewKey(char *key);
void  Do_XOR(char *dest, char *source, int size);
char *GetSysDate();
char *GetSysTime();
char *alltrim(char *str);
unsigned char *decode(unsigned char *src);
int spublicEncrypt( char *src, char *dest, int flag, int ende, int size );
char * GetReturnMsg(char * in_src_msg,int in_suc_flag,char * in_agent_phone,char *in_cust_phone,long in_tran_money);
utype* pAgentAreaCheck(const utype *inParam, TCtrlInfo *errInfo);

/*空中充值返销*/
utype* p8009Check(const utype *inParam, TCtrlInfo *errInfo);
utype* p8009Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p8009Init(const utype *inParam, TCtrlInfo *errInfo);
utype* p8009Print(const utype *inParam, TCtrlInfo *errInfo);
utype* pBackAgentPayMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* pBackCustPayMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* pCustAndAgentInfo(const utype *inParam, TCtrlInfo *errInfo);

/*网厅银行卡赠费*/
utype* pBankpayInit(const utype * inParam,TCtrlInfo *errInfo);

/*直销卡转账*/
utype* pTransPay(const utype *inParam, TCtrlInfo *errInfo);
utype* pTranOut(const utype *inParam, TCtrlInfo *errInfo);
utype* pSendMsg(const utype *inParam, TCtrlInfo *errInfo);
char * GetReturnMsg1(char * in_src_msg,int in_suc_flag,char * out_phone,char *in_phone,long in_tran_money);


/*资金帐号分户*/
utype* p8201Init(const utype * inParam,TCtrlInfo *errInfo);
utype* p8201Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p8201PhoneQry(const utype * inParam,TCtrlInfo *errInfo);

/*资金帐户缴费*/
utype* p8001Init(const utype * inParam,TCtrlInfo *errInfo);
utype* p8001Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p8001PayQry(const utype * inParam,TCtrlInfo *errInfo);

/*退预存款*/
utype* pQ8008Qry( const utype *inParam, TCtrlInfo *errInfo );
utype* pI8008Cfm( const utype *inParam, TCtrlInfo *errInfo );
utype* p8008Print( const utype *inParam, TCtrlInfo *errInfo );
utype* pQ8008NotBackMoney( const utype *inParam, TCtrlInfo *errInfo );
utype * pGetPhoneFeeAll(const utype *inParam , TCtrlInfo *errInfo);
utype* CompYxLmitLFee( const utype *inParam, TCtrlInfo *errInfo );
utype* CompYxLmitLFeeNew( const utype *inParam, TCtrlInfo *errInfo );
utype* pGetThePayTypePre(const utype * inParam,TCtrlInfo *errInfo);
utype* GetYxLmitLFee( const utype *inParam, TCtrlInfo *errInfo );

/*批量缴费手工导入*/
utype * p8208Write(const utype *inParam , TCtrlInfo *errInfo);
utype * p8208Cfm(const utype *inParam , TCtrlInfo *errInfo);
utype * p8208Audit(const utype *inParam , TCtrlInfo *errInfo);
utype * p8208AuditQry(const utype *inParam , TCtrlInfo *errInfo);
utype * p8208ActQry(const utype *inParam , TCtrlInfo *errInfo);
utype * p8208DataQry(const utype *inParam , TCtrlInfo *errInfo);
int 	spublicGetTmpDir(const char *file, char *rtn_path);
char  *	spublicGetEnvDir( char *env);
int 	strToFields(const char* src, char separateChar, ...);

/*区县补收限额分配*/
utype* p8203IOrU( const utype *inParam, TCtrlInfo *errInfo );
utype* p8203Init( const utype *inParam, TCtrlInfo *errInfo );

/*调账操作查询*/
utype* p8124Qry(const utype * inParam,TCtrlInfo *errInfo);

/*综合退预存*/
utype* pI8013Cfm( const utype *inParam, TCtrlInfo *errInfo );
utype* pQ8013Qry( const utype *inParam, TCtrlInfo *errInfo );
utype* PublicUpdateAccountPrepay( const utype *inParam, TCtrlInfo *errInfo );
utype *pGetPayTypePre(const utype *, TCtrlInfo *);
utype* PublicUpdateAddPrepay( const utype *inParam, TCtrlInfo *errInfo );

/*边界漫游查询*/
utype* p8120Qry(const utype * inParam,TCtrlInfo *errInfo);

/*判断用户某套餐是否在扣费提醒期间*/
utype* pQFeeReminder( const utype *inParam, TCtrlInfo *errInfo );

/*转账送费*/
utype* pQ8016ChargeQry( const utype *inParam, TCtrlInfo *errInfo );
utype* pI8016Charge( const utype *inParam, TCtrlInfo *errInfo );
utype* pI8016ChargeNew( const utype *inParam, TCtrlInfo *errInfo );

utype* pZWDFCX01(const utype * inParam,TCtrlInfo *errInfo);

/*县区冲正限额分配*/
utype* p8204Init(const utype *inParam, TCtrlInfo *errInfo);
utype* p8204Cfm(const utype *inParam, TCtrlInfo *errInfo);

utype* pUserChgQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserChg(const utype * inParam,TCtrlInfo *errInfo);

/*缴费冲正验证*/
utype * p8003Check(const utype *inParam , TCtrlInfo *errInfo);

/*分月划拨冲正*/
utype* pPayBackReturnFee(const utype *inParam, TCtrlInfo *errInfo);
utype* pPayBackCashFee(const utype *inParam, TCtrlInfo *errInfo);

/*9901详单查询*/
utype* p8122Init(const utype * inParam,TCtrlInfo *errInfo);
utype* p8122Valid(const utype * inParam,TCtrlInfo *errInfo);
utype* p8122Port(const utype * inParam,TCtrlInfo *errInfo);
utype* p8122Record(const utype * inParam,TCtrlInfo *errInfo);

/*详单日志查询*/
utype* p8139Qry(const utype * inParam,TCtrlInfo *errInfo);

/*单个用户分月划拨*/
utype* pQ8015Qry( const utype *inParam, TCtrlInfo *errInfo );
utype* pI8015Cfm( const utype *inParam, TCtrlInfo *errInfo );

/*判断用户是否有账务优惠信息*/
utype* pAcctFavCheck(const utype *inParam, TCtrlInfo *errInfo);

/*特殊用户欠费回收*/
utype* p8012Init( const utype *inParam, TCtrlInfo *errInfo );
utype* p8012Cfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pWriteOffAccountDead(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetSpecUserInf(const utype *inParam, TCtrlInfo *errInfo);

/*信息费导入*/
utype* pI8200Cfm( const utype *inParam, TCtrlInfo *errInfo );
int spubGetTmpDir(const char *file, char *rtn_path);
char *spubGetEnvDir( char *env);

/*批量补收文件导入*/
utype* p8011Init( const utype *inParam, TCtrlInfo *errInfo );
utype* p8011Audit( const utype *inParam, TCtrlInfo *errInfo );

/*==========多账户预存欠费查询==========*/
utype* p8124Qry(const utype * inParam,TCtrlInfo *errInfo);

/*代理商空中开户，扣代理商账务预存*/
utype* pAgentTranOut(const utype *inParam, TCtrlInfo *errInfo);
utype* pPrepayTranOut(const utype *inParam, TCtrlInfo *errInfo);
utype* pInsertBookPayOut(const utype *inParam, TCtrlInfo *errInfo);
utype* pSendBusiDaily(const utype *inParam, TCtrlInfo *errInfo);

/*==========边界漫游查询==========*/
utype* p8131Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8131Cfm(const utype * inParam,TCtrlInfo *errInfo);

/*==========sp查询==========*/
utype* pESOPFeeQry(const utype * inParam,TCtrlInfo *errInfo);

/*立即话费查询*/
utype* pInFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pjf000013(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetOweInMid(const utype * inParam,TCtrlInfo *errInfo);

/*用户消费量查询*/
utype* pUsedSumInfo(const utype * inParam,TCtrlInfo *errInfo);

/*密码验证*/
utype* ppubCheckPasswd(const utype * inParam,TCtrlInfo *errInfo);
utype* ppubEnPasswd(const utype * inParam,TCtrlInfo *errInfo);

/*ADC费用查询*/
utype* pADCFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetSpecialFee(const utype * inParam,TCtrlInfo *errInfo);


/*集团清单打印*/
utype * PublicGetUnbill(const utype *inParam , TCtrlInfo *errInfo);
utype* p8100ListGrp(const utype * inParam,TCtrlInfo *errInfo);

/*融合产品共享分钟详单查询*/
utype* p8110ShareQry(const utype * inParam,TCtrlInfo *errInfo);

/*投诉预处理*/
utype* pBillAccQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pStopFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pRemainFeeQry(const utype * inParam,TCtrlInfo *errInfo);

/*WAP单月账单查询*/
utype* pWapBillQry(const utype * inParam,TCtrlInfo *errInfo);

/*资金账户查询*/
utype* pFunConUserQry(const utype * inParam,TCtrlInfo *errInfo);

/*员工资金账户管理*/
utype* p8211Valid(const utype * inParam,TCtrlInfo *errInfo);
utype* p8211Qry(const utype * inParam,TCtrlInfo *errInfo);
utype* p8211PassCheck(const utype * inParam,TCtrlInfo *errInfo);

/*集团缴费*/
utype* pConPayOwe(const utype * inParam,TCtrlInfo *errInfo);
utype* p8017GrpInit(const utype * inParam,TCtrlInfo *errInfo);
utype* p8017GrpCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* pGetCustInfo(const utype * inParam,TCtrlInfo *errInfo);

/*==========sp查询==========*/
utype* p8100ListGrp(const tagutype*,tagCtrlInfo*);

/*==========账号缴费查询==========*/
utype* p8211Cfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p8211ConCfm(const utype * inParam,TCtrlInfo *errInfo);
utype* p8211UserQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetFundCon(const utype * inParam,TCtrlInfo *errInfo);

/*取其他账户下的欠费*/
utype* pGetOtherConFee(const utype * inParam,TCtrlInfo *errInfo);
/*查询用户在本账号下的欠费*/
utype* pGetUserConFee(const utype * inParam,TCtrlInfo *errInfo);

/*赠费查询*/
utype* pActFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pNoBackFeeQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pUserBackFeeQry(const utype * inParam,TCtrlInfo *errInfo);


/*空中充值销户退预存*/
utype* p8018Init(const utype *inParam, TCtrlInfo *errInfo);
utype* p8018Cfm(const utype *inParam, TCtrlInfo *errInfo);

/*应用集成平台服务*/
utype* pubGetInterXml(const utype *inParam, TCtrlInfo *errInfo);
utype* pubGetInterStr(const utype *inParam, TCtrlInfo *errInfo);
int strsplit(char* split_str, char* src_str, const char split_char);
int charpos(const char* source,const char target);
extern "C" { int LG_Getinter(char *newaddress,int appid,int priority,const char *transcode,const char *inmsg,char *outmsg);}

/*==========支付查询==========*/
utype* p8020GrpInit(const utype * inParam,TCtrlInfo *errInfo);
utype* p8020CfmGrp(const utype * inParam,TCtrlInfo *errInfo);

/*充值卡信息查询*/
utype* p8140(const utype * inParam,TCtrlInfo *errInfo);

/*手机帐户到IPTV点播帐户转帐*/
utype* p8014Cfm( const utype *inParam, TCtrlInfo *errInfo );
utype* pGetTheConPre(const utype * inParam,TCtrlInfo *errInfo);


utype* pNewCardPay(const utype *inParam, TCtrlInfo *errInfo);

void de_cipher(char *src,char *dst);
void en_cipher(char *src,char *dst);

/*扣费*/
utype* pChargeConFirm(const utype * inParam,TCtrlInfo *errInfo);
utype* pDeductQrySrv(const utype * inParam,TCtrlInfo *errInfo);
utype* pDeductResSrv(const utype * inParam,TCtrlInfo *errInfo);
utype* pGetOrderInfo(const utype * inParam,TCtrlInfo *errInfo);

/*话单权限*/
utype* p8214Query(const utype * inParam,TCtrlInfo *errInfo);
utype* p8214Confirm(const utype * inParam,TCtrlInfo *errInfo);

/*员工交话费*/
utype* p8019Init(const utype * inParam,TCtrlInfo *errInfo);
utype* p8019Cfm(const utype * inParam,TCtrlInfo *errInfo);

/*一键导航*/
utype* p9630(const utype * inParam,TCtrlInfo *errInfo);

/*缴费开机发送命令状态查询*/
utype* pQryOpenCmd(const utype* inParam, TCtrlInfo* errInfo);

/*检查传入金额是否足够划拨欠费*/
utype* pHandFeeChk(const utype * inParam,TCtrlInfo *errInfo);
/*wangyla pHandFeeQryTest*/
utype* pHandFeeQryTest(const utype * inParam,TCtrlInfo *errInfo);

utype* pHWFeeQryT1(const utype * inParam,TCtrlInfo *errInfo);
/*新帐单打印附录页*/
utype * p8100ApxPage( const utype * inParam, TCtrlInfo * errInfo );
utype * pAcctOrDetailList( const utype * inParam, TCtrlInfo * errInfo );
utype * pComUsedDetail( const utype * inParam, TCtrlInfo * errInfo );
utype *pGetAllBillFee(const utype * inParam, TCtrlInfo *errInfo);
utype * p8100BillDetail(const utype * inParam, TCtrlInfo * errInfo);// acct detail list for custservice
utype * pGetInAcctDetailToMid(const utype* inParam, TCtrlInfo* errInfo);
/*缴费信息查询 */
utype* pPayFeeQry(const utype *inParam, TCtrlInfo *errInfo);

//xianjb add 跨库访问
int DBconnect();

//wangyla 公共函数
utype* pServiceNoInfo(const utype* inParam, TCtrlInfo* errInfo);
utype* pLimitOweQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pWLANDealFeeQry( const utype *inParam, TCtrlInfo *errInfo );
utype* pSjPayQry(const utype * inParam,TCtrlInfo *errInfo);

utype* pGetPhoneMsg(const utype *inParam, TCtrlInfo *errInfo);
utype* p8000Pay(const utype *inParam, TCtrlInfo *errInfo);
utype* pDetailQryPub(const utype* inParam, TCtrlInfo* errInfo);

//fanck  通用发票套打
utype* p8215Print(const utype *inParam, TCtrlInfo *errInfo);
utype* p8215disCNAMon(const utype *inParam, TCtrlInfo *errInfo);
//fanck 新增账目项
utype *p8206SearchAcct(const utype *inParam, TCtrlInfo *errInfo);
utype* p8206NewAcctItm(const utype *inParam, TCtrlInfo *errInfo);
utype* p8206ItemRelConf(const utype * inParam,TCtrlInfo *errInfo);
utype *p8206SearchItemCode(const utype *inParam, TCtrlInfo *errInfo);
utype* p8206AcctRelation(const utype* inParam,TCtrlInfo* errInfo);
utype* p8206QueryAcctGroup(const utype* inParam,TCtrlInfo* errInfo);
utype* p8206NewAcctInGroup(const utype* inParam,TCtrlInfo* errInfo);
//查询是否A号码给B号码发送短信
utype* pQrySendFlag(const utype* inParam, TCtrlInfo* errInfo);
utype* pQryCallFlag(const utype* inParam, TCtrlInfo* errInfo);
utype* pQryDetailFlag(const utype* inParam, TCtrlInfo* errInfo);

//有价卡缴费记录查询
utype* pValueCardQry(const utype* inParam, TCtrlInfo* errInfo);
utype* pubGetInterStrNew(const utype* inParam, TCtrlInfo* errInfo);

//有价卡解除代人充值
utype* pValueCardRem(const utype* inParam, TCtrlInfo* errInfo);

//有价卡充值
utype* pHWCardPayIn(const utype* inParam, TCtrlInfo* errInfo);

//上发账单
utype* pPutBill(const utype* inParam, TCtrlInfo* errInfo);
utype* pPutBbPm(const utype* inParam, TCtrlInfo* errInfo);

utype* pKCOweQry(const utype* inParam, TCtrlInfo* errInfo);
utype* pAirAgentCheck(const utype* inParam, TCtrlInfo* errInfo);
utype* pKCCheck(const utype* inParam, TCtrlInfo* errInfo);

int atoASCII(char* in_str, char* out_str);
int gb2unicode(unsigned char *GB2312Msg, unsigned char *GB13000Msg);
void disp_data(char *buf,int len,char *des);
int  GetAscii(char * int_source_src,int in_source_len,char * out_des_src);

int gen_pw(char *mobile,char *pw);
int DectoBCD(int Dec,unsigned char *Bcd,int length);
void generat_mac_data(char *in_str, int in_str_len, char *mac_data[5]);

utype* pGetConPrePayFee(const utype* inParam, TCtrlInfo* errInfo);
utype* pGetCurPreNew(const utype* inParam, TCtrlInfo* errInfo);

//add by xianjb 20120517
utype* pGetConPre(const utype* inParam, TCtrlInfo* errInfo);

//权限操作
utype* p8216PriQry(const utype *inParam, TCtrlInfo *errInfo);
utype* p8216GraOrRev(const utype *inParam, TCtrlInfo *errInfo);

/*小额支付查询*/
utype* pXezfQry( const utype *inParam, TCtrlInfo *errInfo );
utype* pUserConsumeQry( const utype *inParam, TCtrlInfo *errInfo );
utype * pGetUserAllBillFee(const utype * inParam, TCtrlInfo *errInfo);

/*转账操作*/
utype* p8014tranCfm(const utype *inParam, TCtrlInfo *errInfo);
utype* p8014tranQry(const utype *inParam, TCtrlInfo *errInfo);

/*0缴费*/
utype* pZeroPay(const utype* inParam, TCtrlInfo *errInfo);

/*查询服务*/
utype* pOrderExQry(const utype * inParam,TCtrlInfo *errInfo);

utype* pOprLocusMsgQry(const utype *inParam, TCtrlInfo *ptCtrlInfo);
utype* pOprLocusMsgMod(const utype *inParam, TCtrlInfo *ptCtrlInfo);


utype* pTestUX(const utype* inParam, TCtrlInfo* errInfo);


 /*坏账核销*/
utype* p8217Cfm(const utype *inParam, TCtrlInfo *errInfo);


/*直销卡欠费开机服务接口*/
utype* pPhoneOpenCrm(const utype *inParam, TCtrlInfo *errInfo);

/*后付费集团用户*/
utype* p8218_ktj(const utype *inParam, TCtrlInfo *errInfo);
utype* p8218_jfq(const utype *inParam, TCtrlInfo *errInfo);

/*后付费集团用户缴费期*/
utype* pPaymentPeriod(const utype *inParam, TCtrlInfo *errInfo);
utype* pUPaymentPeriod(const utype *inParam, TCtrlInfo *errInfo);

/*优惠币奖励查询*/
utype* pSepMarkQry(const utype * inParam,TCtrlInfo *errInfo);
utype* pSepMarkOpr(const utype * inParam,TCtrlInfo *errInfo);
utype* pSpeMarkPre(const utype * inParam,TCtrlInfo *errInfo);
utype* pSpeMarkUnPre(const utype * inParam,TCtrlInfo *errInfo);
