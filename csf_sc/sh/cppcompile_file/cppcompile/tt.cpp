#include "allBCP.h"
#include "libstaticorder.h"

int tpsvrinit(int argc, char *argv[])
{
        return BOrderTuxInit(argc, argv, LABELDBCHANGE, "ROrdResume");
}

void tpsvrdone()
{
        BOrderTuxDone(LABELDBCHANGE);
}

extern "C" void sOrdResQry(TPSVCINFO *transb)
{
       #ifdef CRMNGA
        tuxadpEx("sOrdResQry", transb, LABELDBCHANGE, "OrderResumeQuery", OrderResumeQuery, (TDoMerge)OrderQueryMerge, 1);
       #else
         tuxadpEx("sOrdResQry", transb, LABELDBCHANGEALL, "OrderResumeQuery", OrderResumeQuery, (TDoMerge)OrderQueryMerge, 1);
       #endif
}

extern "C" void sOResCfm(TPSVCINFO *transb)
{
        tuxadp("sOResCfm", transb, LABELDBCHANGE, "OrderResume", OrderResume, 1);
}

void sOResCfm(TPSVCINFO *transb)
{
   Usage();
}
