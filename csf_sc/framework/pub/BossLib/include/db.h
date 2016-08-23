#ifndef __db_h__
#define __db_h__

#define SQLCODE sqlca.sqlcode
#define SQLERRMSG sqlca.sqlerrm.sqlerrmc
#define NOTFOUND 1403

//默认函数的最大返回数量
#define DEFAULT_MAX_ROWCOUNT	100

int ProcDBLogin(const char* m_sDataSource, const char* m_sUserId, const char* m_sPasswd);


void ProcDBClose();

#endif /*__db_h__*/

