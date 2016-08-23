#include "allBCP.h"



utype* pRuleCheck(const utype* puParamIn, TCtrlInfo* errInfo);

extern "C" void sRuleCheck(TPSVCINFO *transb)
{
	tuxadp1(transb->name, transb,
			LABELDBCHANGE, "pRuleCheck", pRuleCheck, 1);
}
