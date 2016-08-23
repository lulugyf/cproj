#include "allBCP.h"
#include "router.h"

extern "C" void sRouteInfo(TPSVCINFO *transb)
{
     //TUXADP("sRouteInfo", transb, LABELDBCHANGE, "getRouteInfo", getRouteInfo, 1);
        /*
                aaaaaaaaaaaaaaa
                bbbbbbbbbbbbbbb
                ccccccccccccccc
        */
          tuxadp("sRouteInfo", transb, LABELDBCHANGE, "getRouteInfo", getRouteInfo, 1); 
}


extern "C" void sQSysDT(TPSVCINFO *transb)
{
          tuxadp("sQSysDT", transb, LABELDBCHANGE, "getSysdateTest", getSysdateTest, 1);
}

