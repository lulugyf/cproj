#ifndef __AHLOCALBC_H__
#define __AHLOCALBC_H__

utype* cQChargeWorkSheetOfAccept(const utype * inParam, TCtrlInfo *errInfo);
utype* cDChargeWorkSheetOfAccept(const utype * inParam, TCtrlInfo *errInfo);
utype* cIChargeWorkSheeHis(const utype * inParam, TCtrlInfo *errInfo);
utype* cQChargeOLResultOfAccept(const utype * inParam, TCtrlInfo *errInfo);
utype* cIChargeOnLine(const utype * inParam, TCtrlInfo *errInfo);
utype* cQChargeOnLineWater(const utype * inParam, TCtrlInfo *errInfo);
utype* cQChargeOnLineElectricity(const utype * inParam, TCtrlInfo *errInfo);
utype* cQChargeOnLineWaterB(const utype * inParam, TCtrlInfo *errInfo);
utype* cQChargeOnLineElectricityB(const utype * inParam, TCtrlInfo *errInfo);
utype* cUChargeOnLine(const utype * inParam, TCtrlInfo *errInfo);
utype* cISACodeDict(const utype * inParam, TCtrlInfo *errInfo);
utype* cQSACodeByRegionID(const utype * inParam, TCtrlInfo *errInfo);
utype* cQSACodeByRCode(const utype * inParam, TCtrlInfo *errInfo);
utype* cQSACodeByRName(const utype * inParam, TCtrlInfo *errInfo);
utype* cQSACodeByRCName(const utype * inParam, TCtrlInfo *errInfo);
utype* cQCntOfSACodeHisByRCode(const utype * inParam, TCtrlInfo *errInfo);

utype* cQSAProdPricePlanByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cDSAProdPricePlanByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cISAProdPricePlan(const utype * inParam,TCtrlInfo *errInfo);
utype* cISAProdPricePlanHisByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUCodeOfSACode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfChargeOnLineByWCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChargeOnLineWAccount(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfChargeOnLineByEleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChargeOnLineEAccount(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChargeWorkSheetAccount(const utype * inParam,TCtrlInfo *errInfo);
utype* cIChargeWorkSheet(const utype * inParam,TCtrlInfo *errInfo);

utype* cQSpanRegTransByEffDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpanRegTransByPhoneNoEffDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpanRegTransByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQSpanRegTransByPhoneNoRegionID(const utype * inParam,TCtrlInfo *errInfo);
 
utype* cUAgentByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cDAgentByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentByKey(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentByGroupId(const utype * inParam,TCtrlInfo *errInfo);
utype* cQAgentDictByLoginNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUPwdOfAgentDictByContractNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUGroupOfAgentDictByContractNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUExpDateOfAgentDictByContractNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChargeWorkSheetHisOfAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChargeOnLineGas(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChargeOnLineGasB(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfChargeOnLineByGCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChargeOnLineGAccount(const utype * inParam,TCtrlInfo *errInfo);

utype* cQSAProdPricePlanByRPrice(const utype * inParam, TCtrlInfo *errInfo);
void Generate_Mac(char  *param,char *outmac);

utype* cGetCntOfChargeOnLineByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChargeOnLineAccount(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChargeWorkSheetRetA(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChargeWorkSheetRetB(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChargeOnLineByCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChargeOnLineAccountB(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFlagOfChargeOnLineByAccept(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChargeOnLineByDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntChargeOnLineByDate(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfChargeOnLineByEleCode01(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetChargeOnLineEAccount01(const utype * inParam,TCtrlInfo *errInfo);

utype* cQChargeConfirm(const utype * inParam,TCtrlInfo *errInfo);
utype* cQChargeOnLineGasByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);
#endif

