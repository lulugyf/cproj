#include "allBCP.h"

#define _PRINT_MSG_ 1

utype* cQDual(const utype * inParam,TCtrlInfo *errInfo);


extern "C" void sQDual(TPSVCINFO *transb)
{
    tuxadp(transb->name, transb, LABELDBCHANGE, "cQDual", cQDual, 1);
}


utype* pDynSvc(const utype *inparam, TCtrlInfo *ptCtrlInfo);
extern "C" void sDynSvc(TPSVCINFO *transb)
{
	printf("%s\n",LABELDBCHANGE);
	tuxadp("sDynSvc", transb, LABELDBCHANGE, "pDynSvc", pDynSvc, 1);
}

//utype* cTest1(const utype * inParam,TCtrlInfo *errInfo);

utype* pMulTest(const utype * inParam,TCtrlInfo *errInfo);
extern "C" void sMulTest(TPSVCINFO *transb){
	//tuxadp("sDynSvc", transb, LABELDBCHANGE, "cTest1", cTest1, 1);
	tuxadp("sDynSvc", transb, LABELDBCHANGE, "pMulTest", pMulTest, 1);
}

/*

clxml sMulTest '{"ROOT":{"col1":1}}'
 */
