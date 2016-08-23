#include "allBCP.h"
utype* pDynSvc(const utype *inparam, TCtrlInfo *ptCtrlInfo);
extern "C" void sDynSvc(TPSVCINFO *transb)
{
	printf("%s\n",LABELDBCHANGE);
	tuxadp("sDynSvc", transb, LABELDBCHANGE, "pDynSvc", pDynSvc, 1);
}

