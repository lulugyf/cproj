/*********************************************************
 *
 *  FileName:
 *      db_func.h
 *
 *  Version:
 *      1.00 2004.11.09
 *
 *  tabstop = 4
 *
 ********************************************************/

#ifndef __INCLUDE_DB_FUNC_H__
#define __INCLUDE_DB_FUNC_H__

#define	SQLCODE			sqlca.sqlcode
#define SQLERRMSG       sqlca.sqlerrm.sqlerrmc

#define	SQL_OK			0
#define	OK			SQL_OK
#define	NO_MORE_ROWS	1403
#define	SQLROWS			sqlca.sqlerrd[2]

struct cmd11
{
    long	command_id;
    char	hlr_code[8];
    char	phone_no[20];
    char	command_code[8];
    char	op_code[8];
    char	imsi_no[32];
    char	new_phone[20];
    char	new_imsi[32];
    char	otherinfo[160];
    char	business_status[8];
    char	request_time[15];
    char    login_no[7];
    char    group_id[11];
};

typedef int (* entry_callback)(struct cmd11 *cmds, const int rec_count, const int connid);

void entry_loop(const char *hlrcode, const char *tname, entry_callback callback, const int connid);

int db_login(char *user,char *pswd,char *name);
int db_logout();


#endif
