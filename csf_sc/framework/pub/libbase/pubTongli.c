#include "publicsrv.h"



char *getTime(int type)
{
  time_t tm;
  char hh[2+1];
  char ehh[3+1];
  static char sysdatetime[17+1];

  tm = time(NULL);

  Sinitn(sysdatetime);
  Sinitn(hh);
  Sinitn(ehh);

  switch(type) {
    case 100:
      strftime(sysdatetime, 12, "%m  %d %Y", localtime(&tm));
      strncpy(hh, sysdatetime, 2);
      *sysdatetime = *ehh;
      *(sysdatetime+1) = *(ehh+1);
      *(sysdatetime+2) = *(ehh+2);
      break;
    case 101:
      strftime(sysdatetime, 11, "%m/%d/%Y", localtime(&tm));
      break;
    case 102:
      strftime(sysdatetime, 11, "%Y/%m/%d", localtime(&tm));
      break;
    case 103:
      strftime(sysdatetime, 11, "%m.%d.%Y", localtime(&tm));
      break;
    case 104:
      strftime(sysdatetime, 11, "%Y.%m.%d", localtime(&tm));
      break;
    case 105:
      strftime(sysdatetime, 11, "%m-%d-%Y", localtime(&tm));
      break;
    case 106:
      strftime(sysdatetime, 11, "%Y-%m-%d", localtime(&tm));
      break;
    case 107:
      strftime(sysdatetime, 9, "%m%d%Y", localtime(&tm));
      break;
    case 108:
      strftime(sysdatetime, 9, "%Y%m%d", localtime(&tm));
      break;
    case 109:
      strftime(sysdatetime, 9, "%H:%M:%S", localtime(&tm));
      break;
    case 110:
      strftime(sysdatetime, 9, "%H:%M:%S", localtime(&tm));
      break;
    case 111:
      strftime(sysdatetime, 6, "%H:%M", localtime(&tm));
      break;
    case 112:
      strftime(sysdatetime, 15, "%Y%m%d02/12/2004M%S", localtime(&tm));
      break;
    default:
      return NULL;
  }

  Sinitn(hh);

  if (type == 110 || type == 111) {
    strncpy(hh, sysdatetime, 2);

    if (atoi(hh) > 12 && atoi(hh) < 22) {
      sprintf(hh, "0%d", atoi(hh) - 12);
      strcat(sysdatetime, "PM");
    }
    else if (atoi(hh) >= 22) {
      sprintf(hh, "%d", atoi(hh) - 12);
      strcat(sysdatetime, "PM");
    }
    else
      strcat(sysdatetime, "AM");

    *sysdatetime = *hh;
    *(sysdatetime+1) = *(hh+1);
  }

  return sysdatetime;
}
    /*从字符串中截取某个子字符串*/
/*******************调用举例**************************
*	MID(pSource,pDes,1,2);			     *
*****************************************************/
int MID(char *src,char *des,int n,int m)
{
    int  len;
    len=strlen(src);
    /*    失败返回  */
    if(m==0||len==0||n>len||n<1)
       return(0);
    if(m>(len-n+1))
       m=len-n+1;
    src+=n-1;
    strncpy(des,src,m);
    des[m]='\0';
    return(1);
   }
/*将字符串开头的特定字符变为指定字符 如：000032 *****32 */
int CHRHEAD(char *src,char n,char m)
{
     int  i;
     i=0;
     while (src[i]==n)
     {
        src[i]=m;
        i++;
     }
     if(i>0)
	     return(1);
     else
         return(0);
}

/*将字符串开头的空格去掉 */
/*******************调用举例**************************
*	LTRIM(pSource,' ',pDes);		     *
*****************************************************/
int LTRIM(char *src,char n,char *des)
{
     int  i;
     char *ls_temp;
 
     if ( (des == NULL) || (strlen(des) == 0)) 
        return (1);
    i=0;
    ls_temp=src;

     while (ls_temp[0]==n)
     {
        ls_temp++;
        i++;
     }
     
     src=ls_temp;
       /*  strcpy(des,ls_temp);*/
     
     if(i>0)
	     return(1);
     else
         return(0);
}

/*将字符串后面的空格给清楚掉*/
/*******************调用举例**************************
*	RTRIM(pSource);				     *
*****************************************************/
char *RTRIM(char *src)
{
     int  i,Len;
     char *ls_temp;
     
     if ( (src == NULL) || (strlen(src) == 0))
        return  src;
     
     Len=strlen(src);

     for(i=Len-1;i>=0;i--)
        {
           if(src[i]==' ')
               src[i]='\0';
           else
               break;
        }
        
     ls_temp=src;
     for(i=0;i<strlen(src);i++)
        {
           if(src[i]==' ')
                 ls_temp++;
           else
               break;
        }
     src=ls_temp; 
     /*    strcpy(src,ls_temp);      */
}

/*按照相关的格式显示*/
char *FORMAT(int option,char *src,char *fm)
{
    char tmp[20];
    char des[40];
    memset(des,'\0',sizeof(des));
    memset(tmp,'\0',sizeof(tmp));
    switch(option)
    {
    case 1:
       MID(src,tmp,1,4);
       strcpy(des,tmp);
       strcat(des,"-");

       MID(src,tmp,5,2);
       strcat(des,tmp);
       strcat(des,"-");

       MID(src,tmp,7,2);
       strcat(des,tmp);     
       des[11]='\0';
       RTRIM(des);
       return(des);
       break;
    case 2:
       MID(src,tmp,1,2);
       strcpy(des,tmp);
       strcat(des,":");
       MID(src,tmp,3,2);
       strcat(des,tmp);
       strcat(des,":");
       MID(src,tmp,5,2);
       strcat(des,tmp);
       RTRIM(des); 
       return(des);
       break;
   } 
}

/*  获取某个字符串出现的第一次位置    */
#if !defined(__GETCHARPOS__)
#define __GETCHARPOS__

int GETCHARPOS(char *src,char *des,int *pos)
{
    int src_len;
    int i,j;
    char test_char[256];
    src_len=strlen(des);
    for(j=0;j<strlen(src);j++)
        {
           if(strlen(src)-j>=strlen(des))
                {
                    if(strncmp(&src[j],des,strlen(des))==0)
                       {
                         *pos=j;
                         return(1);
                       }
                 }

        }
     *pos=strlen(src);
     return(0);
}

#endif

/*    大整数的相加      */
char *StringAdd(char *s_input1,char *s_input2)
{
  int i=0;
  char *s1,*s2,*s3;
  char s_end[30];
  int len1,len2,len_max;
  int ch1,ch2,ch3,ch_add;

  ch3=0;

  if(strlen(s_input1)>strlen(s_input2))
	s1=s_input2,s2=s_input1;
  else
	s1=s_input1,s2=s_input2;
  s3=s_end;
  memset(s3,'\0',strlen(s3));
  s3++;
  len1=strlen(s1);
  len2=strlen(s2);
  len_max=len1>len2?len1:len2;
  memset(s3,'0',len_max+1);
  s3[len_max+1]='\0';
  s3[len_max]='\0';
  for(i=1;i<=len_max;i++)
	if((i<=len1)&&(i<=len2)){
		(s3[len_max-i]=s1[len1-i]+s2[len2-i]+ch3-48)<58?
		ch3=0:(s3[len_max-i]-=10)+(ch3=1);
	}
	else
		break;
  for(i=len2-len1-1;i>=0;i--)
		(s3[i]=ch3+s2[i])<58?
		ch3=0:(s3[i]-=10)+(ch3=1);
  if(1==ch3) s3--,s3[0]='1';
  return(s3);
}

/*将所用时间长度转化为00:00:00的格式*/
char *DURATIME(int dur)
{
    int flag,dur_hour,dur_min,dur_sec,dur_tmp;
    char char_dur[15];
    dur_hour=dur_min=dur_sec=0;
	dur_tmp = dur;
    if(dur>=3600) flag=0;	
    else if(dur>=60) flag=1;	
    else flag=2;			
    switch(flag)
    {
		case 0:	/*	小时	 */
			dur_hour = dur_tmp / 3600;
			dur_tmp = dur_tmp % 3600;
        case 1:	/*	分	*/	
			dur_min = dur_tmp / 60;
			dur_tmp = dur_tmp % 60;
        case 2:	/*	秒	*/
			dur_sec = dur_tmp;
    }
    sprintf(char_dur,"%.2d:%.2d:%.2d",dur_hour,dur_min,dur_sec);
    char_dur[9]='\0';
    return(char_dur);
}
/*将所用时间长度转化为00:00:00的格式*/

/*****************************************************
*       功能:分割操作符左右字符的函数                *
*****************************************************/

/*******************调用举例**************************
*                                                    *
*       char *pSource="abcdakkk";                    *
*	char *pLeft = new char[20];                  *
*	char *pRight = new char[20];                 *
*	char *pDiv="cd";                             *
*                                                    *
*	f_div_string(pSource,pLeft,pRight,pDiv);     *
*		                                     *
*	SetDlgItemText(IDC_EDIT1,pLeft);             *
*	SetDlgItemText(IDC_EDIT2,pRight);            *
*                                                    *
*****************************************************/

int f_div_string(char *szSource,char *szLeft,char *szRight,char *szDivide)
{
   
   int iLen; 
   int iDivLen;
   char *pdest = NULL;
   int iPos;
   int iRightLen;
   iLen = strlen(szSource);
   iDivLen = strlen(szDivide);
   
   
   pdest = strstr(szSource, szDivide);
   if (pdest == NULL)
   	return 1;
   	   
   iPos = pdest - szSource + 1;
 
   
   memset(szLeft,0,iPos);
   memcpy(szLeft,szSource,iPos - 1);
   *(szLeft + iPos - 1 ) = '\0';
   
   
   iRightLen = iLen - iPos + 1 - iDivLen; 
   memset(szRight,0,iRightLen);
   strcpy(szRight,szSource + iPos -1 + iDivLen);
   *(szRight + iRightLen ) = '\0';
   
   return 0;
}
#if 0
/*错误公用函数.Tiger*/
char * COMMON_ERROR(long al_DbErrorCode,char *ac_ServiceName,int idx)
{
	EXEC SQL BEGIN DECLARE SECTION;
		char lc_bss_errid[16+1] = "";
		char lc_ora_code[16+1] = "";
		char lc_ora_errdesc[640+1] = "";
		char lc_ora_errreas[1024+1] = "";
		char lc_ora_stmtidx[10+1] = "";
		char lc_ora_service[20+1] = "";
		char lc_ora_conn[50] = "";
	EXEC SQL END DECLARE SECTION;
	char lc_err_msg[1664+1] = "";
	sprintf(lc_ora_code,"%d",al_DbErrorCode);/*-10006*/
	RTRIM(lc_ora_code);
	LTRIM(lc_ora_code,' ',lc_ora_code);
	sprintf(lc_ora_stmtidx,"%d",idx);/* 6 */
	RTRIM(lc_ora_stmtidx);
	LTRIM(lc_ora_stmtidx,' ',lc_ora_stmtidx);
	strcpy(lc_ora_service,ac_ServiceName);
	RTRIM(lc_ora_service);
	LTRIM(lc_ora_service,' ',lc_ora_service);
	/*strcpy(lc_ora_conn,"tbss/tbss");*/
	/*EXEC SQL connect :lc_ora_conn;*/
	
	/*printf("\n%s",lc_ora_code);
	printf("\n%s",lc_ora_stmtidx);
	printf("\n%s",lc_ora_service);*/
	
	/*EXEC SQL INSERT INTO tsm_err_msg_log(error_no,index_no,services_name,error_time)
			VALUES(:lc_ora_code,:lc_ora_stmtidx,:lc_ora_service,sysdate);
	if ( sqlca.sqlcode != 0 )
	{
		tpabort(0);
		strcpy(lc_err_msg,"|200001|记录错误日志时系统严重错误|请与系统管理员联系|");
		RTRIM(lc_err_msg);
		return lc_err_msg;
	}*/
	
	EXEC SQL SELECT nvl(ERROR_ID,0),nvl(ERROR_DESC,' '),nvl(ERROR_REASON,' ')
		INTO :lc_bss_errid,:lc_ora_errdesc,:lc_ora_errreas
		FROM TSM_ERROR_MESSAGE
		WHERE trim(SYS_ERROR) = :lc_ora_code ;
	if ( sqlca.sqlcode != 0 )
	{ 	
		tpabort(0);
		strcpy(lc_err_msg,"|200000|系统严重错误|请与系统管理员联系|");
		RTRIM(lc_err_msg);
		return lc_err_msg;
	}
	RTRIM(lc_bss_errid);
	RTRIM(lc_ora_errdesc);
	RTRIM(lc_ora_errreas);
	sprintf(lc_err_msg,"|%s|%s|%s|",lc_ora_code,lc_ora_errdesc,lc_ora_errreas);
	/*EXEC SQL commit work;
	printf("\n comm.pc commit sqlca.sqlcode=%d",sqlca.sqlcode);*/
	return lc_err_msg;
}
#endif
/*判断一字符串是否为NULL或空*/
/*******************调用举例********************************************************
*	if ( COMM_NULL(pSource) == 1 )					  	  *
*	{									  *
*		如果pSource为空则执行pSource为空时的代码				  *
*	}				     					  *
***********************************************************************************/
long COMM_NULL(char *ac_msg)
{	
	RTRIM(ac_msg);
	if ( (ac_msg == NULL) || (strlen(ac_msg) == 0))
		return 1; /*NULL*/
	return 0; /*NOT NULL*/ 
}

/*按指定符号分离字符串*/
int COMM_DIVSTRING(char *ac_source,char *ac_io_left,char *ac_io_right,char *ac_divide)
{
	/*若找不到匹配串则返回-1否则返回0及左右字符串*/
	int li_len;
	int li_divlen;
	char *lp_dest = NULL;
	int li_pos;
	int li_rightlen;
	if ( (lp_dest = strstr(ac_source,ac_divide)) == NULL )
		return -1;
	li_len = strlen(ac_source);
	li_divlen = strlen(ac_divide);

	li_pos = lp_dest - ac_source;
	memset(ac_io_left,0,li_pos);
	memcpy(ac_io_left,ac_source,li_pos);
	*( ac_io_left + li_pos ) = '\0';

	li_rightlen = li_len - li_pos - li_divlen;
	memset(ac_io_right,0,li_rightlen);
	strcpy(ac_io_right,ac_source + li_pos + li_divlen);
	*(ac_io_right + li_rightlen) = '\0';

	return 0;
}

/*对字符串中的指定字符串用别的代替*/
void STRCHANGE(char *ParamSoStr,char *ParamVal)
{
	long len;
	int li_pos;
	char *lpdest0 = NULL;
	char *lpdest1 = NULL;
	char lpleft[1023+1] = "";
	char lpStr[2+1] = "";
	len = strlen(ParamSoStr);
	lpdest0 = strstr(ParamSoStr,"%s");
	lpdest1 = strstr(ParamSoStr,"%d");
	
	if ( lpdest0 == NULL )
	{
		li_pos = lpdest1 - ParamSoStr;
		strcpy(lpStr,"%d");
	}
	else if (lpdest1 == NULL)
	{
		li_pos = lpdest0 - ParamSoStr;
		strcpy(lpStr,"%s");
	}
	else if (strlen(lpdest0)<strlen(lpdest1))
	{
		li_pos = lpdest1 - ParamSoStr;
		strcpy(lpStr,"%d");
	}
	else
	{
		li_pos = lpdest0 - ParamSoStr;
		strcpy(lpStr,"%s");
	}
	
	
	memcpy(lpleft,ParamSoStr,li_pos);
	*(lpleft+li_pos) = '\0';
	switch(*(lpStr+1))
	{
		case 'd':
		  strcat(lpleft,ParamVal);
		  strcat(lpleft,ParamSoStr+li_pos+2);
		  memset(ParamSoStr,0,len);
		  strcpy(ParamSoStr,lpleft);
		  break;
		case 's':
		  strcat(lpleft,"'");
		  strcat(lpleft,ParamVal);
		  strcat(lpleft,"'");
		  strcat(lpleft,ParamSoStr+li_pos+2);
		  memset(ParamSoStr,0,sizeof(ParamSoStr));
		  strcpy(ParamSoStr,lpleft);
		  RTRIM(ParamSoStr);
		  break;
		default :
		  break;  
	}
}

/*此函数用于替换*/
#if !defined(__REPLACESTR__)
#define __REPLACESTR__

void REPLACESTR(char *ParamStr1,char *ParamStr2,char *ParamStr3)
{
	int pos;
	int oldpos = 0;
	int len;
	char right[4000+1]="";
	len = strlen(ParamStr2);
	for(;;)
	{
		GETCHARPOS(ParamStr1+oldpos,ParamStr2,&pos);
		/*printf("\npos=%d",pos);*/
		if (pos == strlen(ParamStr1+oldpos)) break;
		/*如果*/
		if (*(ParamStr1+oldpos+pos+len) != '|' && *(ParamStr1+oldpos+pos+len) != ',')
		{
			oldpos += pos + len;
			continue;
		}
		oldpos += pos;
		memset(right,0,sizeof(right));
		strcpy(right,ParamStr1+oldpos+len);
		RTRIM(right);
		memset(ParamStr1+oldpos,0,strlen(ParamStr1+oldpos));
		strcat(ParamStr1,"'");
		strcat(ParamStr1,ParamStr3);
		strcat(ParamStr1,"'");
		strcat(ParamStr1,right);
		
	}
}
#endif

#if 0
/*此函数对SQL语句重的变量用域值来替代.Tiger*/
void VARFML(char *ParamSQL,FBFR32 *ParamFMLBM,FBFR32 *ParamFMLRM)
{
	/*0营销类 1资源类*/
	EXEC SQL BEGIN DECLARE SECTION;
		char lc_o_os[20+1] = "";
		long ll_o_fld = 0;
		char lc_o_fld[4+1] = ":F";
		char lc_o_value[200+1] = "";
		char lc_o_qfld[10+1] = "";
		/*char lc_ora_conn[50] = "";*/
	EXEC SQL END DECLARE SECTION;
	int pos;
	int oldpos = 0;
	int npos = 0;
	 FLDLEN32	ll_Len;
	/*char findstr[10+1]=":FIELD";*/
	
	for(;;)
	{
		GETCHARPOS(ParamSQL+oldpos,lc_o_fld,&pos);
		/*printf("\nVARFML.pos = %d\tstrlen=%d",pos,strlen(ParamSQL+oldpos));*/
		if (pos == strlen(ParamSQL+oldpos)) break;
		npos = pos;
		for(;;)
		{
			if ((*(ParamSQL+oldpos+pos+2) == '|') ||(*(ParamSQL+oldpos+pos+2) == ',') ) break;
			*(lc_o_fld+strlen(lc_o_fld)) = *(ParamSQL+oldpos+pos+2);
			pos++;
			RTRIM(lc_o_fld);
		}
		oldpos += pos;
		/*取得值后再取*/
		memset(lc_o_qfld,0,sizeof(lc_o_qfld));
		strcpy(lc_o_qfld,lc_o_fld+1);
		EXEC SQL SELECT nvl(var_os,'0'),nvl(var_fml,0)
			INTO :lc_o_os,:ll_o_fld
			FROM tphsv_prnt_var
			WHERE var_name = :lc_o_qfld;
		/*printf("\nlc_o_fld=%s",lc_o_fld);*/
		if (sqlca.sqlcode != 0)
		{
			printf("\nVARFML.sqlcode=%d\tlc_o_qfld=%s",sqlca.sqlcode,lc_o_qfld);
			break;
		}
		memset(lc_o_value,0,sizeof(lc_o_value));
		ll_Len = sizeof(lc_o_value);
		if (*lc_o_os=='0') /*营销*/
			Fget32(ParamFMLBM,ll_o_fld,0L,lc_o_value,&ll_Len);
		else if (*lc_o_os == '1') /*资源*/
			Fget32(ParamFMLRM,ll_o_fld,0L,lc_o_value,&ll_Len);
		else if (*lc_o_os == '2') /*工作流*/
			Fget32(ParamFMLBM,ll_o_fld,0L,lc_o_value,&ll_Len);
		RTRIM(lc_o_value);
		/*printf("\n^_^lc_o_value=%s",lc_o_value);*/
		/*printf("\n|oldpos = %d\tlc_o_fld=%s",oldpos,lc_o_fld);*/
		REPLACESTR(ParamSQL+ oldpos - pos + npos,lc_o_fld,lc_o_value);
		/*printf("\n快的看东方%s",ParamSQL);*/
		memset(lc_o_fld,0,sizeof(lc_o_fld));
		strcpy(lc_o_fld,":F");
	}
	
}
#endif



/*此函数用于专门替换*/
void REPLACESTRORD(char *ParamStr1,char *ParamStr2,char *ParamStr3)
{
	int pos;
	int oldpos = 0;
	int len;
	char right[5000+1]="";
	len = strlen(ParamStr2);
	for(;;)
	{
		
		
		
		GETCHARPOS(ParamStr1+oldpos,ParamStr2,&pos);
		
		if (pos == strlen(ParamStr1+oldpos)) break;
		/*如果*/
		if (*(ParamStr1+oldpos+pos+len) != '|' && *(ParamStr1+oldpos+pos+len) != ',')
		{
			oldpos += pos + len;
			continue;
		}
		oldpos += pos;
		memset(right,0,sizeof(right));
		strcpy(right,ParamStr1+oldpos+len);
		RTRIM(right);
		memset(ParamStr1+oldpos,0,strlen(ParamStr1+oldpos));
		
		strcat(ParamStr1,"'");
		strcat(ParamStr1,ParamStr3);
		
		strcat(ParamStr1,"'");
		strcat(ParamStr1,right);

		break;
	}
}

/*返回小写字母串*/
char *TOSMALL(char *src)
{
 int  len;
 int  i;
 char temp[10];
 char temp1[255];
 char *src1="";
  
 memset(src1,0,sizeof(src1));     
 len=strlen(src);
 if (len==0)
 {
    strcpy(src,"");
 }
 else
 {
   printf("\n src= %s",src);        
   for (i=1;i<=len;i++)
   {    
      MID(src,temp,i,1);

      if      (strcmp(temp,"A")==0)
      {
              strcpy(temp1,"a");  
              strcat(src1,temp1);                 
              continue;    
      }
      else if (strcmp(temp,"B")==0)
      {  
              strcpy(temp1,"b");         
              strcat(src1,temp1);               
              continue;  
      }
      else if (strcmp(temp,"C")==0)
      {
              strcpy(temp1,"c");         
              strcat(src1,temp1);               
              continue;  
      }
      else if (strcmp(temp,"D")==0)
      {
              strcpy(temp1,"d");                       
              strcat(src1,temp1);               
              continue;  
      }
      else if (strcmp(temp,"E")==0)
      {
              strcpy(temp1,"e");         
              strcat(src1,temp1);               
              continue;  
      }
      else if (strcmp(temp,"F")==0)
      {
              strcpy(temp1,"f");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"G")==0)
      {
              strcpy(temp1,"g");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"H")==0)
      {
              strcpy(temp1,"h");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"I")==0)
      {
              strcpy(temp1,"i");         
              strcat(src1,temp1);                             
              continue;  
      }
      else if (strcmp(temp,"J")==0)
      {
              strcpy(temp1,"j");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"K")==0)
      {
              strcpy(temp1,"k");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"L")==0)
      {
              strcpy(temp1,"l");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"M")==0)
      {
              strcpy(temp1,"m");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"N")==0)
      {
              strcpy(temp1,"n");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"O")==0)
      {
              strcpy(temp1,"o");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"P")==0)
      {
              strcpy(temp1,"p");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"Q")==0)
      {
              strcpy(temp1,"q");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"R")==0)
      {
              strcpy(temp1,"r");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"S")==0)
      {
              strcpy(temp1,"s");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"T")==0)
      { 
              strcpy(temp1,"t");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"U")==0)
      {
              strcpy(temp1,"u");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"V")==0)
      {
              strcpy(temp1,"v");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"W")==0)
      {
              strcpy(temp1,"w");         
              strcat(src1,temp1);                             
              continue;                
      }
      else if (strcmp(temp,"X")==0)
      {
               strcpy(temp1,"x");       
              strcat(src1,temp1);                              
               continue;                
      }
      else if (strcmp(temp,"Y")==0)
      {
              strcpy(temp1,"y");                
              strcat(src1,temp1);                                                                                                                                                                                                                                                         
              continue;                                                                                                                                                                                                                                                                                                                                                 
      } 
      else if (strcmp(temp,"Z")==0)
      {
              strcpy(temp1,"z");                
              strcat(src1,temp1);                                                                                                                                                                                                                                                                                          
              continue;                                                                                                                                                                                                                                                                                            
      }
      else
      {       
      strcpy(temp1,temp);                          
      strcat(src1,temp1);            
      continue;
      }
   } 
  memset(src,0,sizeof(src)); 
  strcpy(src,src1);   
  printf("\n src= %s",src);       	  
  } 
}

/***************************************************************************
Function 10进制转换为字符串
Input    :              整数
Output   :              转换后的字符串
Author   : rlh
Date     : 2004-03-03
Modify   :
Modi_date:
***************************************************************************/
char *DecToStr(long lDecNum,char *cHexStr)
{
	int         iBitNum = 0;       /*余数*/
	long        lCir = 0;          /*循环*/
	long        lTotal = 0;        /*长度*/
	char        cAdd = '\0';       /*符号*/ 
	char        cNumChar = '\0';   /*字符*/
	
	/*负数*/
	if ( 0 > lDecNum )
	{
		cAdd = '-';
		lDecNum = abs(lDecNum);
	}
	else if ( 0 == lDecNum )
	{
		cHexStr[0] = '0';
		return cHexStr;
	}
	
	/*循环数字*/
	while ( 0 < lDecNum )
	{
		iBitNum = lDecNum%10;
		switch (iBitNum)
		{
			case 0:
			{
				cHexStr[lCir] = '0';
				break;
			}
			case 1:
			{
				cHexStr[lCir] = '1';
				break;
			}
			case 2:
			{
				cHexStr[lCir] = '2';
				break;
			}
			case 3:
			{
				cHexStr[lCir] = '3';
				break;
			}
			case 4:
			{
				cHexStr[lCir] = '4';
				break;
			}
			case 5:
			{
				cHexStr[lCir] = '5';
				break;
			}
			case 6:
			{
				cHexStr[lCir] = '6';
				break;
			}
			case 7:
			{
				cHexStr[lCir] = '7';
				break;
			}
			case 8:
			{
				cHexStr[lCir] = '8';
				break;
			}
			case 9:
			{
				cHexStr[lCir] = '9';
				break;
			}
			default:
			{
				memset(cHexStr,'\0',sizeof(cHexStr));
				return NULL;
			}
		}
		
		lDecNum = lDecNum/10;
		lCir++;
	}
	
	/*串上符号*/
	cHexStr[lCir] = cAdd;

	/*字符串反向,变为正常*/
	lCir = 0;
	lTotal = strlen(cHexStr);
	while ( (lTotal + 1)/2 > lCir )
	{
		cNumChar = cHexStr[lCir];
		cHexStr[lCir] = cHexStr[lTotal -1 - lCir];
		cHexStr[lTotal -1 - lCir] = cNumChar;
		lCir++;
	}	

	return cHexStr;
}
