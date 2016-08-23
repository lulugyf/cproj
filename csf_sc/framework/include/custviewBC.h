#ifndef __CUSTVIEW_BC_H__
#define __CUSTVIEW_BC_H__

utype* cGetFuncOpRelByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRuleInInterfaceByOpRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRuleOutInterfaceByOpRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQDataTypeByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRoleRuleOutByRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRuleCodeByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRuleInfoByRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQClassDictByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncOpByFunc(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRuleInfoByRuleCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cQRuleDictByRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRuleaddDictByRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRuleDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIClassDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRuleAddDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cURuleDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUClassNameOfClassDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQClassRelByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfClassRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cDClassRelByIncludeClass(const utype * inParam,TCtrlInfo *errInfo);

utype* cIClassRel(const utype * inParam,TCtrlInfo *errInfo);
utype* cUClassInfoOfClassDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetInParOfFunByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetOutParOfFunByOpCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cURuleAddDict(const utype * inParam,TCtrlInfo *errInfo);

utype* cQFuncRuleDictByOpRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMaxRuleOrderOfFuncRuleDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncRuleDict(const utype * inParam,TCtrlInfo *errInfo);

utype* cIFuncRuleIndict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncRuleInDisDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncRuleOutDisDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIFuncRuleOutDict(const utype * inParam,TCtrlInfo *errInfo);

utype* cQMaxValOfClassDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQMaxValOfRuleDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRuleDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQClassRelByIncludeClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cUClassRelByIncludeCode(const utype * inParam,TCtrlInfo *errInfo);

utype* cQFuncRuleInDictByOpRuleClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncRuleOutDictByOpRuleClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncRuleInDisDictByOpRuleClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQFuncRuleOutDisDictByOpRuleClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cQRuleaddDictByRuleClass(const utype * inParam,TCtrlInfo *errInfo);

utype* cDFuncRuleOutDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncRuleInDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncRuleOutDisdict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncRuleInDisdict(const utype * inParam,TCtrlInfo *errInfo);

utype* cIRuleInIfDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cIRuleOutIfDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfRuleInIfDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfRuleOutIfDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfFuncRuleInDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfFuncRuleOutDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRuleInIfDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cDRuleOutIfDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRuleInClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRuleOutClass(const utype * inParam,TCtrlInfo *errInfo);

utype* cGetClassByClassCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cIClassStruct(const utype * inParam,TCtrlInfo *errInfo);
utype* cQClassStructByParentNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfClassStructByClassNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCntOfClassStructByParentNo(const utype * inParam,TCtrlInfo *errInfo);
utype* cUParentNoOfClassStruct(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfFuncRuleOutDictByOpRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfFuncRuleInDictByOpRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cUColCouneOfFuncRuleInDisdictByOpRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cUColCouneOfFuncRuleOutDisdictByOpRule(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncRuleInDictByOpRuleClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncRuleOutDictByOpRuleClass(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncRuleOutDisdictByRuleOpPos(const utype * inParam,TCtrlInfo *errInfo);
utype* cDFuncRuleInDisdictByRuleOpPos(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRuleClassOutByRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetRuleClassInByRuleCode(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFuncRuleInDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFuncRuleOutDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFuncRuleOutDisDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cUFuncRuleInDisDict(const utype * inParam,TCtrlInfo *errInfo);
utype* cGetCntOfFuncRuleDict(const utype * inParam,TCtrlInfo *errInfo);

utype* cQClassStructByClassNo(const utype *inParam, TCtrlInfo *errInfo);
utype* cQClassStructByClassCode(const utype *inParam, TCtrlInfo *errInfo);
utype* cDFuncRuleDict(const utype *inParam, TCtrlInfo *errInfo);

utype* cQFuncOpRelByOpCode(const utype *inParam, TCtrlInfo *errInfo);
utype* cQFunctionDictByFunCode(const utype *inParam, TCtrlInfo *errInfo);
utype* cGetDisOPOfFuncOpRel(const utype *inParam, TCtrlInfo *errInfo);

utype* cQRuleInIfDictByRuleCode(const utype *inParam, TCtrlInfo *errInfo);
utype* cQRuleOutIfDictByRuleCode(const utype *inParam, TCtrlInfo *errInfo);
utype* cQClassDictByClassName(const utype *inParam, TCtrlInfo *errInfo);
utype* cQRuleAddDict(const utype *inParam, TCtrlInfo *errInfo);
utype* cQMaxValOfClassStruct(const utype *inParam, TCtrlInfo *errInfo);
utype* cGetFuncRuleInInfoByOpRule(const utype *inParam, TCtrlInfo *errInfo);
utype* cQFuncRuleInDictByOpRulePas(const utype *inParam, TCtrlInfo *errInfo);
utype* cQFuncRuleOutDictByOpRulePas(const utype *inParam, TCtrlInfo *errInfo);

utype* cQInfoDeveIfByPK(const utype *inParam, TCtrlInfo *errInfo);
utype* cQGrpStabIfInfoByPK(const utype *inParam, TCtrlInfo *errInfo);

utype* cIAuditInfo(const utype * inParam,TCtrlInfo *errInfo);
utype* cQCustNameByPhoneNo(const utype * inParam,TCtrlInfo *errInfo);


#endif

