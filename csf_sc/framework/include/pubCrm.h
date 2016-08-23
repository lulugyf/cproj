#ifndef __PUBCRMBCP_H__
#define __PUBCRMBCP_H__

/***BC***/

utype* cQryUserBySvcNum(utype * inParam,TCtrlInfo *errInfo);
utype* cQrycustByCustId(utype * inParam,TCtrlInfo *errInfo);

/***BP***/
utype* pQryUserInfo(utype * inParam, TCtrlInfo *errInfo);
#endif
