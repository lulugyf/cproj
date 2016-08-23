#include "../framework/include/allBCP.h"
using namespace std;

utype* cQUserInfoByPhoneNum(const utype * inParam,TCtrlInfo *errInfo);
extern "C" utype* pCustInfoByUrphno(const utype* inParam, TCtrlInfo* errInfo)
{
	uAutoPtr uUserInfoIn(uInit(1));  
	uAutoPtr uUserInfoOut(uInit(1)); 

	utAddStr(uUserInfoIn, "PHONE_NO", utGetStr(inParam,"PHONE_NO"));  
	uUserInfoOut = cQUserInfoByPhoneNum(uUserInfoIn, errInfo);
	if(uUserInfoOut->cnt == 0)                           
	{                                                              
                throw(appException(402040401, "error!"));                                                                
	}
	
	return uUserInfoOut.release();
 
}
