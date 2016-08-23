#include "allBCP.h"
#include "libstaticorder.h"

int tpsvrinit(int argc, char *argv[])
{
	return BOrderTuxInit(argc, argv, LABELDBCHANGE, "R2105Cfm");
}

void tpsvrdone()
{
	BOrderTuxDone(LABELDBCHANGE);
}
                                                                  
extern "C" void s2105Cfm(TPSVCINFO *transb)
{
        tuxadp("s2105Cfm", transb, LABELDBCHANGE, "OrderBusiDeal", OrderBusiDeal, 1);
}
