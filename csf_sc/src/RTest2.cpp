#include "allBCP.h"

#define _PRINT_MSG_ 1
extern "C" utype* pCustInfoByUrphno(const utype* inParam, TCtrlInfo* errInfo);

extern "C" void sCustInfoValid(TPSVCINFO *transb)                                            
{                                                                                     
	tuxadp(transb->name, transb, LABELDBCHANGE, "pCustInfoByUrphno", pCustInfoByUrphno, 1);  
}       
