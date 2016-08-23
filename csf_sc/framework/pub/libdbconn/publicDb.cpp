/******************************************
 *      Prg:  publicDb.cp
 *     Edit:  guo.yj
 * Modi/Add:  zhaohao  2001.10.31
 *     Date:  2001.02.02
 ******************************************/


#include "pub.h"
#include <string>
#include "publicsrv.h"
#include <map>



static map<string, db_connect*> _dbmap;
otl_connect *db = 0;
DCI* mdb=0;


int spublicDBLogin(void *transIN, void *transOUT,char *srvName,char *connect_name)
{
	db_connect* pdb=NULL;
	map<string, db_connect*>::iterator iter;
	try
	{
		iter=_dbmap.find(connect_name);
		if(iter==_dbmap.end()){
			pdb=new db_connect(connect_name);
			_dbmap[connect_name]=pdb;
		}else
			pdb=iter->second;
		db=&pdb->getOtlHandle();
		mdb=&pdb->getMDBHandle();
		pdb->doConnect();
		return 0;
	}catch(...){
		return -1;	
	}
}


int sChkDBLogin(void *transIN, void *transOUT, char *srvName,char *connect_name)
{
	db_connect* pdb=NULL;
	map<string, db_connect*>::iterator iter;
	try
	{
		iter=_dbmap.find(connect_name);
		if(iter==_dbmap.end()){
			pdb=new db_connect(connect_name);
			_dbmap[connect_name]=pdb;
		}else
			pdb=iter->second;
		db=&pdb->getOtlHandle();
		mdb=&pdb->getMDBHandle();
		pdb->tryConnect();
		return 0;
	}catch(...){
		return -1;	
	}
}
 

int spublicDBClose(char *connect_name)
{
 	db_connect* pdb=NULL;
	map<string, db_connect*>::iterator iter;
	try
	{
		iter=_dbmap.find(connect_name);
		if(iter==_dbmap.end()){
			pdb=new db_connect(connect_name);
			_dbmap[connect_name]=pdb;
		}else
			pdb=iter->second;
		db=&pdb->getOtlHandle();
		mdb=&pdb->getMDBHandle();
		pdb->doClose();
		return 0;
	}catch(...){
		return -1;	
	}
}



/*******************************/
/* name:     spublicGenMAC     */
/* writer:   zhaohao           */
/* date:     2001.02.21        */
/* function: 根据给定的字段    */
/*           产生MAC校验       */
/*******************************/
int spublicGenMAC(char *MAINKEY, struct MacStruc *macstruc, char *out_MAC)
{
        char buf[1024+1];
        char tmp_buf1[512+1];
        char tmp_buf2[512+1];
        char tmp_buf3[512+1];
        char tmp_int[20+1];
        char tmp_float[30+1];
        char tmp_char[20+1];
        char MAC_bcd[8+1];
        int  use_int, use_float, use_char;
        int  rtn_value;

        memset(buf, 0, sizeof(buf));
        memset(tmp_buf1, 0, sizeof(tmp_buf1));
        memset(tmp_buf2, 0, sizeof(tmp_buf2));
        memset(tmp_buf3, 0, sizeof(tmp_buf3));

        if (MAINKEY == NULL) {
                MAINKEY=(char *)(malloc(8+1));
                memset(MAINKEY, 0, 8+1);
                strcpy(MAINKEY, "bossboss");
        }

        if (macstruc->use_int < 0 || macstruc->use_float < 0 || macstruc->use_char < 0 ) {
                rtn_value = -1;
                return rtn_value;
        }

        /* 整型 */
        for(use_int=0; use_int<macstruc->use_int; use_int++) {
                memset(tmp_int, 0, sizeof(tmp_int));
                sprintf(tmp_int, "%d", macstruc->srcint[use_int]);

                if (use_int == 0) {
                        strcpy(tmp_buf1, tmp_int);
                }
                else {
                        strcat(tmp_buf1, tmp_int);
                }
        }

        /* 实型 */
        for(use_float=0; use_float<macstruc->use_float; use_float++) {
                memset(tmp_float, 0, sizeof(tmp_float));
                if (macstruc->srcfloat[use_float] < 0) {
                        macstruc->srcfloat[use_float] = macstruc->srcfloat[use_float] * -1;
                }
                sprintf(tmp_float, "%.0f", macstruc->srcfloat[use_float]*100);

                if (use_float == 0) {
                        strcpy(tmp_buf2, tmp_float);
                }
                else {
                        strcat(tmp_buf2, tmp_float);
                }
        }

        /* 字符串 */
        for(use_char=0; use_char<macstruc->use_char; use_char++) {
                if (use_char == 0) {
                        strcpy(tmp_buf3, Trim(macstruc->srcchar[use_char]));
                }
                else {
                        strcat(tmp_buf3, Trim(macstruc->srcchar[use_char]));
                }
        }

        strcpy(buf, tmp_buf1);
        strcat(buf, tmp_buf2);
        strcat(buf, tmp_buf3);

        memset(MAC_bcd, 0 ,sizeof(MAC_bcd));

	/*
        GenerateMAC(MAC_STAND, buf, strlen(buf), MAINKEY, MAC_bcd);
        BcdToAsc_(out_MAC,MAC_bcd,16);
	*/

        if (MAINKEY != NULL)
                free(MAINKEY);

        rtn_value = 0;
        return rtn_value;
}


/***************  数据的合法性检验 ****************/

/*       1 合法      0  不合法     */

//check_syn(char    *str, int     type, unsigned int sz1)
//{
//        int     i = 0 , j = 0;
//        int     flag = 0;
//        static char     temp[51];
//        
//        strcpy(temp,str);
//        if (temp[0] != 0) {
//                switch ( type ) {
//                        case CHAR:
//                        case VARCHAR:
//                                /* 只进行长度的合法性检查 */
//                                flag = check_char( sz1 , temp);
//                                break;
//                        case BIT:
//                        case TINYINT:
//                        case INT:
//                        case SMALLINT:
//                                flag = check_int( type, temp);
//                                break;
//                        case SMALLMONEY:
//                        case MONEY:
//                        case NUMERIC:
//                        case FLOAT:
//                        case REAL:
//                        case DECIMAL:
//                                flag = check_money( type, temp );
//                                break;
//                        case SMALLDATETIME:
//                        case DATETIME:
//                                flag = check_datetime( type, temp);
//                                break;
//                        case SYSNAME:
//                        case DATETIMN:
//                        case TEXT:
//                        case TIMESTAMP:
//                        case BINARY:
//                        case VARBINARY:
//                        case NCHAR:
//                        case NVARCHAR:
//                        case INTN:
//                        case MONEYN:
//                        case NUMERICN:
//                        case FLOATN:
//                        case DECIMALN:
//                                /* 系统暂时不支持此数据类型 */
//                                flag = 0;
//                                break;
//                        default:
//                                /* 数据库中有非法数据类型 */
//                                flag = 0;
//                                break;
//                }
//        }
//        return flag;
//}

/* 检查字符型的合法性 */
int check_char(unsigned int  wid, char    *cond)
{ 
        if ( strlen(cond) > wid ) {
                /* 长度超宽 */
                return ( 0 );
        }
        return ( 1 );
}

//
///* 检查整形的合法性 */
//int check_int(unsigned int type, char *cond)
//{
//        int     i,len,count,o_i;
//        int     flag;
//        int     flag1=1;
//        char    ch;
//        char    dat1[51] , dat2[51];
//
//        if (cond[0] != '-' && !isdigit(cond[0])) {
//                flag = 0;
//                return flag;
//        }
//        else {
//                if (cond[0] == '-') {
//                        flag1 = -1;
//                        memset(dat1, 0, sizeof(dat1));
//                        strncpy(dat1, cond+1, strlen(cond)-1);
//                        memset(cond, 0, sizeof(cond));
//                        strcpy(cond, dat1);
//                }
//        }
//
//        i = 0;  count = 0;
//        ch = cond[i];
//        for (i=0; i<strlen(cond); i++) {
//                if ( !isdigit(cond[i]) ) {
//                        break;
//                }
//        }
//        if ( i<strlen(cond) ) {
//                /* 字符串中有非数字的字符 */
//                flag = 0;
//                return flag;
//        }
//        
//        if (type == BIT) {
//                if ( (atoi(cond)*flag1 != 0) || (atoi(cond)*flag1 != 1) )
//                        flag = 0;
//                else
//                        flag = 1;
//        }
//        else if (type == TINYINT) {
//                if ( (atoi(cond)*flag1 < 0) || (atoi(cond)*flag1 > 255) )
//                        flag = 0;
//                else
//                        flag = 1;
//        }
//        else if (type == SMALLINT) {
//                if ( (atoi(cond)*flag1 < -32768) || (atoi(cond)*flag1 > 32767) )
//                        flag = 0;
//                else
//                        flag = 1;
//        }
//        else if (type == INT) {
//                if ( (atoi(cond)*flag1 < -214748363) || (atoi(cond)*flag1 > 2147483646) ) {
//                        flag = 0;
//                }
//                else {
//                        flag = 1;
//                }
//        }
//
//        return flag;
//
//}
//
//
///* 检查钱币型和高精度型数值的合法性 */
//int check_money(unsigned int type, char *cond)
//{
//        int     i,j,len,o_i;
//        int     flag, dot_num;
//        int     flag1=1;
//        char    dat1[51] , dat2[51];
//
//        memset(dat1, 0, sizeof(dat1));
//        memset(dat2, 0, sizeof(dat2));
//
//        if (cond[0] != '-' && !isdigit(cond[0])) {
//                flag = 0;
//                return flag;
//        }
//        else {
//                if (cond[0] == '-') {
//                        flag1 = -1;
//                        strncpy(dat1, cond+1, strlen(cond)-1);
//                        memset(cond, 0, sizeof(cond));
//                        strcpy(cond, dat1);
//                }
//        }
//
//        i = 0;  dot_num = 0;
//        for (i=0; i<strlen(cond); i++) {
//                if ( isdigit(cond[i]) || (cond[i] == '.') ) {
//                        if (cond[i] == '.') dot_num++;
//                        continue;
//                }
//                else {  
//                        break;
//                }
//        }
//
//        if ( i<strlen(cond) || dot_num > 1) {
//                /* 字符串中有非数字的字符 */
//                flag = 0;
//                return flag;
//        }
//
//        for(j=0; j<strlen(cond); j++) {
//                if (cond[j] == '.' ) {
//                        if (j == strlen(cond)-1)
//                                strcat(cond, "00");
//                        else if (j == strlen(cond)-2)
//                                strcat(cond, "0");
//                        cond[j+3] = '\0';
//                        break;
//                }
//        }
//        if (dot_num == 0)
//                strcat(cond, ".00");
//        
//        if (type == SMALLMONEY) {
//                if ( (atoi(cond)*flag1 < -214748.3648) || (atoi(cond)*flag1 > 214748.3648) )
//                        flag = 0;
//                else
//                        flag = 1;
//        }
//        else if (type == MONEY) {
//                if (flag1 == -1) {
//                        sprintf(dat2, "-%s", cond);
//                        /* strlen("-922337203685477.58") == 19 */
//                        if (strlen(dat2) > 19)
//                                flag = 0;
//                        else 
//                                if (strcmp(dat2, "-922337203685477.58") > 0)
//                                        flag = 0;
//                                else
//                                        flag = 1;
//                }
//                else {
//                        strcpy(dat2, cond);
//                        if (strlen(dat2) > 18)
//                                flag = 0;
//                        else
//                                if (strcmp(dat2, "922337203685477.58") > 0)
//                                        flag = 0;
//                                else
//                                        flag = 1;
//                }
//        }
//        else if ( (type == NUMERIC) || (type == FLOAT) || (type == REAL) || (type == DECIMAL) ) {
//                if (flag1 == -1) {
//                        sprintf(dat2, "-%s", cond);
//                        if (strlen(dat2) > 34)
//                                flag = 0;
//                        else
//                                if (strcmp(dat2, "-100000000000000000000000000000.00") > 0)
//                                        flag = 0;
//                                else
//                                        flag = 1;
//                }
//                else {
//                        strcpy(dat2, cond);
//                        if (strlen(dat2) > 33)
//                                flag = 0;
//                        else
//                                if (strcmp(dat2, "100000000000000000000000000000.00") > 0)
//                                        flag = 0;
//                                else
//                                        flag = 1;
//                }
//        }
//
//        return flag;
//
//}
//
///* 检查日期型数值的合法性 */
//int check_datetime(unsigned int type, char *cond)
//{
//        int     i,len,o_i;
//        int     flag;
//        int     flag1,flag2;
//        char    date_tmp[8+1];
//        char    time_tmp[8+1];
//        char    dat1[51] , dat2[51], dat3[51];
//        
//        memset(date_tmp, 0, sizeof(date_tmp));
//        memset(time_tmp, 0, sizeof(time_tmp));
//        memset(dat1, 0, sizeof(dat1));
//        memset(dat2, 0, sizeof(dat2));
//        memset(dat3, 0, sizeof(dat3));
//
//        i = 0;
//        for (i=0; i<strlen(cond); i++) {
//                if ( isdigit(cond[i]) || (cond[i] == ':') || (cond[i] == ' ') ) {
//                        continue;
//                }
//                else {  
//                        break;
//                }
//        }
//        if ( i<strlen(cond) ) {
//                /* 字符串中有非数字的字符 */
//                flag = 0;
//                return flag;
//        }
//
//        for (i=0; i<strlen(cond); i++) {
//                if (cond[i] == ' ') break;
//        }       
//        strncpy(dat1, cond, i);
//        strncpy(dat2, cond+i, strlen(cond)-i);
//
//        for (i=0; i<strlen(dat2); i++) {
//                if (dat2[i] != ' ') break;
//        }
//        strncpy(dat3, dat2+i, strlen(dat2)-i);
//        
//userlog("cccccccccc dat1=[%s]\n", dat1);
//userlog("cccccccccc dat3=[%s]\n", dat3);
//        if (strlen(dat1) == 8 && (strlen(dat3) == 8 || dat3[0] == 0)) {
//                if ( (test_date(dat1, type) == 0) || (flag2 = test_time(dat3) == 0) )
//                        return( 0 );
//        }
//        else
//                return( 0 );
//
//        return( 1 );
//}


int test_time(char    *time)
{
        char    str[5];
        int     hour,minute,second;
        int     flag;

        if (time[0] == 0) return( 1 );
        strncpy(str, time,   2);   str[2]=0;  hour   = atoi(str);
        strncpy(str, time+3, 2);   str[2]=0;  minute = atoi(str);
        strncpy(str, time+6, 2);   str[2]=0;  second = atoi(str);

        if (time[2] != ':' || time[5] != ':')
                return( 0 );
        
        if ((hour < 0 || hour > 24) || (minute < 0 || minute > 60) 
                || ( second < 0 || second > 60))
                return( 0 );

        return( 1 );
}
//
//int test_date( char    *date, int     type)
//{
//        char    str[5];
//        int     year,month,day;
//        int     flag;
//        strncpy(str, date,   4);   str[4]=0;   year  = atoi(str);
//        strncpy(str, date+4, 2);   str[2]=0;   month = atoi(str);
//        strncpy(str, date+6, 2);   str[2]=0;   day   = atoi(str);
//
//        if ( day < 1 ) {
//                return( 0 );
//        }
//
//        switch(month) {
//                case 1: case 3: case 5: case 7:
//                case 8: case 10: case 12:
//                        if ( day > 31 )
//                                return( 0 );
//                        break;
//                case 4: case 6: case 9: case 11:
//                        if ( day > 30 )
//                                return( 0 );
//                        break;
//
//                case 2:
//                        if ( day > 29 )
//                                return 0;
//                        else if (  day == 29 &&
//                                year % 400 != 0 && (year % 4 != 0
//                                || year % 100 == 0))
//                                return 0;
//                        break;
//                default:
//                        return 0;
//                        break;
//        }
//
//        if (type == SMALLDATETIME) {
//                if (year < 1900 || year > 2079)
//                        return 0;
//        }
//        else if (type == DATETIME) {
//                if (year < 1753 || year > 9999)
//                        return 0;
//        }
//
//        return( 1 );
//}


/* 根据类型得到数值 */
int ttov(char *type)
{
        if (strcmp(type, "BINARY") == 0)
                return 1;
        if (strcmp(type, "BIT") == 0)
                return 2;
        if (strcmp(type, "CHAR") == 0)
                return 3;
        if (strcmp(type, "DATETIME") == 0)
                return 4;
        if (strcmp(type, "DATETIMN") == 0)
                return 5;
        if (strcmp(type, "DECIMAL") == 0)
                return 6;
        if (strcmp(type, "DECIMALN") == 0)
                return 7;
        if (strcmp(type, "FLOAT") == 0)
                return 8;
        if (strcmp(type, "FLOATN") == 0)
                return 9;
        if (strcmp(type, "IMAGE") == 0)
                return 10;
        if (strcmp(type, "INT") == 0)
                return 11;
        if (strcmp(type, "INTN") == 0)
                return 12;
        if (strcmp(type, "MONEY") == 0)
                return 13;
        if (strcmp(type, "MONEYN") == 0)
                return 14;
        if (strcmp(type, "NCHAR") == 0)
                return 15;
        if (strcmp(type, "NUMERIC") == 0)
                return 16;
        if (strcmp(type, "NUMERICN") == 0)
                return 17;
        if (strcmp(type, "NVARCHAR") == 0)
                return 18;
        if (strcmp(type, "REAL") == 0)
                return 19;
        if (strcmp(type, "SMALLDATETIME") == 0)
                return 20;
        if (strcmp(type, "SMALLINT") == 0)
                return 21;
        if (strcmp(type, "SMALLMONEY") == 0)
                return 22;
        if (strcmp(type, "SYSNAME") == 0)
                return 23;
        if (strcmp(type, "TEXT") == 0)
                return 24;
        if (strcmp(type, "TIMESTAMP") == 0)
                return 25;
        if (strcmp(type, "TINYINT") == 0)
                return 26;
        if (strcmp(type, "VARBINARY") == 0)
                return 27;
        if (strcmp(type, "VARCHAR") == 0)
                return 28;
        return 0;
}


int ifand(char *str, char *strb, char *stre)
{
        int  i=0;
        int  sl, ifflag;
        char tmp_strb[40+1];
        char tmp_stre[40+1];

        if (str[0] == 0) return( 0 );

        memset(tmp_strb, 0, sizeof(tmp_strb));
        memset(tmp_stre, 0, sizeof(tmp_stre));

        sl = strlen(str);

        for (i=0; i<sl; i++)
                if ((i < sl-1) && (str[i] == '&') && (str[i+1] == '&')) {
                        strncpy(tmp_strb, str, i);
                        strncpy(tmp_stre, str+i+2, sl-i-2);
                        ifflag = 1;
                        break;
                }
                else
                        ifflag = 0;

        if (ifflag == 1) {
                strcpy(strb, Trim(tmp_strb));
                strcpy(stre, Trim(tmp_stre));
        }
        else
                strcpy(strb, Trim(str));

        return( 1 );
}


int sDBClose(FBFR32 *transIN, FBFR32 *transOUT, char *srvName, char *conName)
{
	return spublicDBClose(conName);
}
int DBClose(char *conName)
{
  return spublicDBClose(conName);
}
int sDBLogin(void *transIN, void *transOUT, char *srvName, char *conName)
{
  return spublicDBLogin(NULL,NULL,srvName,conName);
}

int DBLogin(char *conName)
{
  return spublicDBLogin(NULL,NULL,"xx",conName);
}

