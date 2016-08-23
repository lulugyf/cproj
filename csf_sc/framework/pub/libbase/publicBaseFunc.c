/*
 *
  ������ţ� cl0
  ��������ƣ� publicBaseFunc.cp
  �������ڣ� 2006.8.3
  ���˵���� ��������������������ڡ������������
 * 
 */
 
 
 
#include "publicsrv.h"

#include <sys/timeb.h>

/*
 *
    �����ţ� cl0_00001
    ������ƣ� round_F
    ������ܣ� ��С�����numλ������������
    ���룺
			source    double  Դ��ֵ
			num       int     ����
    �����
			tmpdouble double  �����������ֵ
  *
  */	 
double round_F(double source, int num)
{
	char tmpstr[64+1];
	char tmp1[12+1];
	double tmpdouble = 0.00;
	
	memset(tmpstr, 0, sizeof(tmpstr));
	memset(tmp1, 0, sizeof(tmp1));
	
	sprintf(tmp1, "%%12.%df", num);
	sprintf(tmpstr, tmp1, source);
	printf("\n tmpstr=[%s],tmp1=[%s] \n",tmpstr,tmp1);
	tmpdouble = atof(tmpstr);
	printf("\n tmpdouble=[%12.f]\n",tmpdouble);
	return tmpdouble;
}

/*
 *
    �����ţ� cl0_00002
    ������ƣ� AddMonth
    ������ܣ� �·�����,��yearmonth����addmonth����
    ���룺
			yearmonth    int  ��������
			addmonth     int  ��������
    �����
			a 					 int  ��������
  *
  */
int AddMonth(int yearmonth,int addmonth)
{
        int a = 0;
        if (addmonth >= 0)
                a =  (yearmonth/100+(yearmonth%100+addmonth)/12)*100+(yearmonth%100+addmonth)%12;
        else
                a = (yearmonth/100+addmonth/12)*100+yearmonth%100+addmonth%12;
        if (a%100==0)
        {
                return (a/100-1)*100+12;
        }
        else
                return a;
}

/*
int MinusMonth(int yearmonth,int minusmonth)
{
        int a = 0;
        if (addmonth >= 0)
                a =  (yearmonth/100+(yearmonth%100+addmonth)/12)*100+(yearmonth%100+addmonth)%12;
        else
                a = (yearmonth/100+addmonth/12)*100+yearmonth%100+addmonth%12;
        if (a%100==0)
        {
                return (a/100-1)*100+12;
        }
        else
                return a;
}
*/

/*
 *
    �����ţ� cl0_00003
    ������ƣ� PublicDecMonth
    ������ܣ� �·�����,��yearmonth��ȥnum����
    ���룺
			yearmonth    int  ��������
			num          int  ��������
    �����
			a 					 int  ��������
  *
  */
int PublicDecMonth(int yearmonth,int num)
{
	int year,month,i;
	year = yearmonth/100;
	month = yearmonth%year;
	for (i=1;i<=num;i++)
	{
		if (--month < 1)
		{
			month = 12;
			year--;
		}
	}
	return year*100+month;
}

/*
 *
    �����ţ� cl0_00004
    ������ƣ� PublicAddMon
    ������ܣ� ȡָ���·�����
    ���룺
			old    int  ��������
    �����
			a 		 int  ��������
  *
  */
int PublicAddMon(int old)
{
	int year,mon;

	year=old/100;
	mon=old%year;

	if(++mon > 12)
	{
		mon=1;
		year++;
	}

	return year*100+mon;
}



/*
 *
    �����ţ� cl0_00009
    ������ƣ� parseString
    ������ܣ� 
    ���룺
			��
    �����
			��
  *
  */
int parseString(char *source,char *result,char seperate){
	int i,j,k,len;
	char tmp[2000];
	
	Sinitn(tmp);
	len=strlen(source);
	
	if (len==0)
		return 0;
	for(i=0;i<len;i++){
		if (source[i]==seperate){
			result[i]='\0';
			break;
		}
		result[i]=source[i];	
	}
	
	if (i==len)
		result[i]='\0';
	
	k=0;
	for (j=i+1;j<len;j++){
		tmp[k]=source[j];
		k++;		
	}
	tmp[k]='\0';	
	strcpy(source,tmp);
	return 0;
}



/*
 *
    �����ţ� cl0_00011
    ������ƣ� PublicGetLastDayOfMonth
    ������ܣ� ���ĳ��ĳ�µ�������
    ���룺
			��
    �����
			��
  *
  */
int PublicGetLastDayOfMonth(int YearMonth)
{
	int InYear = 0;
	int InMonth = 0;
	InYear = YearMonth/100;
	InMonth = YearMonth%100;
	if ((1==InMonth)||(3==InMonth)||(5==InMonth)||(7==InMonth)||(8==InMonth)||(10==InMonth)||(12==InMonth))
	        return 31;
	if ((4==InMonth)||(6==InMonth)||(9==InMonth)||(11==InMonth))
	        return 30;
	if (2==InMonth)
	{
		if(InYear%4==0&&(InYear%100!=0||InYear%400==0))
			return 29;
		else
			return 28;
	}
	return 0;
}



/*
 *
    �����ţ� cl0_00013
    ������ƣ� get_input_parms32_tmp
    ������ܣ� 
    ���룺
			��
    �����
			��
			�Ѿ�������public/server/publicErr.cp
  *
  */
  
  /*---------------------------------------------------------------------------------
   commented by lab 2009.01.07 
   
void get_input_parms32_tmp(FBFR32 *transIN,int *input_par_num, 
                           int *output_par_num,char *dbconnName,char *connType)
{
	int i,j=0;
	int  occs=0,count=0;
	char temp[20];
	char temp_buf[100];
	char myerrno[10],errmsg[200];
	
	*input_par_num=0;
	*output_par_num=0;
	
	if(transIN == NULL)
	{
	    printf("\n1");
		strcpy(myerrno,"205");
		sprintf(errmsg, "lxg SERVICE %s: transIN buffer is NULL,you must allocate memory for transIN!");
		error_handler32(transIN,NULL,
			myerrno,errmsg,dbconnName,connType);
	}
	
	if(Fget32(transIN, SEND_PARMS_NUM32, 0, temp, NULL) == -1)
	{
		printf("\n2");
		strcpy(myerrno,"101");
		strcpy(errmsg,"Fget32 input parms error:SEND_PARAMS_NUM32");
		error_handler32(transIN,NULL,myerrno,errmsg,dbconnName,connType);
	}
	else
	{
		printf("\n3");
		*input_par_num=atoi(temp);
	}
	
	if(Fget32(transIN, RECP_PARMS_NUM32, 0, temp, NULL) == -1)
	{
		printf("\n4");
		strcpy(myerrno,"102");
		strcpy(errmsg,"Fget32 input parms error:RECP_PARAMS_NUM32");
		error_handler32(transIN,NULL,myerrno,errmsg,dbconnName,connType);
	}
	else
	{
		*output_par_num=atoi(temp);
	}
	for(i=0;i<*input_par_num;i++)
	{
		occs=(int)Foccur32(transIN,GPARM32_0+i);
		if(occs>1)
		{
			for(j=0;j<occs;j++)
			{
				if(Fget32(transIN,GPARM32_0+i,j,input_parms[count],NULL) == -1)
				{
				    printf("\n3");
				    strcpy(myerrno,"103");
				    sprintf(errmsg,"Fget32 input parms error: get param %ld value error in get_input_parms.",GPARM32_0+i);
				    error_handler32(transIN,NULL,myerrno,errmsg,dbconnName,connType);
				}
				count++;
			}
		}
		else
		{
			if(Fget32(transIN,GPARM32_0+i, 0, input_parms[count], NULL) == -1)
			{
				printf("\n5");
				strcpy(myerrno,"103");
				sprintf(errmsg,"Fget32 input parms error: get param %ld value error in get_input_parms.",GPARM32_0+i);
				error_handler32(transIN,NULL,myerrno,errmsg,dbconnName,connType);
			}
			count++;
		}
	}
}


---------------------------------------------------*/


/*
 *
    �����ţ� cl0_00014
    ������ƣ� get_input_one
    ������ܣ� 
    ���룺
			��
    �����
			��public/server/publicErr.cp
  *
  */
  
  /*--------------------------------------------------------------
    commented by lab 2009.01.07
    
void get_input_one(FBFR32 *transIN, int *input_par_num, int begin_no,int record_no,char *dbconnect_name,char *connect_type)
{
	int i,j,k;
	char temp[20];
	char temp_buf[100];
	char *myerrno,*errmsg;
	if(Fget32(transIN, SEND_PARMS_NUM32, 0, temp, NULL) == -1)
	{
		strcpy(myerrno,"101");
		strcpy(errmsg,"Fget32 input parms error:SEND_PARMS_NUM");
		error_handler32(transIN,NULL,myerrno,errmsg,dbconnect_name,connect_type);
	}
	else
	{
		*input_par_num=atoi(temp);
	}
	j = record_no;
	k = begin_no;
	for(i=k;i<*input_par_num;i++)
		{
		if(Fget32(transIN,GPARM32_0+i, j, input_parms[i], NULL) == -1)
		{
			strcpy(myerrno,"103");
			sprintf(errmsg,"Fget32 input parms error: get param %ld value error in get_input_parms32.",GPARM32_0+i);
			error_handler32(transIN,NULL,myerrno,errmsg,dbconnect_name,connect_type);
		}
	}
}

------------------------------------------*/

/*
 *
    �����ţ� cl0_00015
    ������ƣ� stradd
    ������ܣ� 
    ���룺
			��
    �����
			��
  *
  */
int stradd(char *s)
{
        int cur,num,len;

        if(s==NULL)
                return 0;

        len=strlen(s);
        for(cur=0,num=0;num<len;num++)
        {
                if(s[num]!=' ' && s[num]!='\t')
                {
                        s[cur++]=s[num];
                }
        }
        s[cur]=0;
        return cur;
}

/*
 *
    �����ţ� cl0_00016
    ������ƣ� charindex
    ������ܣ� ��ĳ���ַ���һ���ַ����е�һ�γ��ֵ�λ��
    ���룺
			��
    �����
			��
  *
  */
int charindex(char *ss,char divide_char)
{
         int j=0;
         for(j=0;j<=strlen(ss);j++){
                 if(ss[j]==divide_char){
                        return j+1;
                 }
                 else{
                      if(ss[j]=='\0')
                      {
                        return 0;
                      }
                 }
         }
}

/*
 *
    �����ţ� cl0_00017
    ������ƣ� addspace
    ������ܣ� ��ĳһ���ַ�����߻��ұ߼ӿո�ת����ָ��λ���Ĵ�
    ���룺
			��
    �����
			��
  *
  */
void addspace(char *in_ss,int len,int flag,char *out_ss)
{
        int i=0;
        char space_ss[1024];
        char tmp_ss[1024];

        memset(tmp_ss,0,sizeof(tmp_ss));
        memset(space_ss,0,sizeof(space_ss));
        sprintf(space_ss,"%1024s"," ");

        if(strlen(in_ss)<len){
            strncpy(tmp_ss,space_ss,len-strlen(in_ss));
            if(flag==0)
            sprintf(out_ss,"%s%s",tmp_ss,in_ss);
            else
            sprintf(out_ss,"%s%s",in_ss,tmp_ss);
        }
        else
        if(strlen(in_ss)>len){
            strncpy(out_ss,in_ss,len);
        }
}

/*
 *
    �����ţ� cl0_00018
    ������ƣ� getLastYM
    ������ܣ� �·��ƶ�����
    ���룺
			��
    �����
			��
  *
  */
  
  /*---------------------------------------------------------
    commented by lab 2009.01.07
    
int getLastYM(int curYM,int month){
	int curYear,curMonth,tmp1,tmp2;

	curYear=curYM/100-1;
	curMonth=curYM%100+12+month;
	tmp1=curMonth/12;
	tmp2=curMonth%12;

	if (tmp2==0){
		tmp1-=1;
		tmp2=12;
	}

	curYear+=tmp1;
	curMonth=tmp2;

	return curYear*100+curMonth;
}

--------------------------------------------------------------------*/

/*
 *
    �����ţ� cl0_00018
    ������ƣ� PublicGetLastDayOfMonthNew
    ������ܣ� ȡ�����������
    ���������
    ���������
    �����룺
  *
  */
  
 /*--------------------------------------------------------------
   commented by lab 2009.01.07
   
int PublicGetLastDayOfMonthNew(int InYear,int InMonth){
        if ( (1 == InMonth) || (3 == InMonth) || (5 == InMonth) || (7 == InMonth) || (8 == InMonth) || (10 == InMonth) || (12 == InMonth) )
                return 31;
        if ( (4 == InMonth) || (6 == InMonth) || (9 == InMonth) || (11 == InMonth) )
                return 30;
        if ( 2 == InMonth){
                if (InYear % 4 == 0 && (InYear % 100 != 0 || InYear % 400 == 0))
                        return 29;
                else
                        return 28;
        }
        return 0;
}

---------------------------------------------------------------------*/

/*
 *
    �����ţ� cl0_00019
    ������ƣ� substr
    ������ܣ� 
    ���������
    ���������
    �����룺
  *
  */
  
  /*------------------------------------------------------------------
    commented by lab 2009.01.07
    
char *substr(char *source,int begin,int num)
{
    int i;
    char dest[2048+1]="\0";
    if(begin<1 || num<1) return NULL;
    for(i=begin-1;i<begin+num-1;i++){
        dest[i-begin+1]=source[i];
    }
    dest[i-begin+1]='\0';
    return dest;
}

---------------------------------------------------------------------*/

/*
 *
    �����ţ� cl0_00020
    ������ƣ� PrintTimeConsume
    ������ܣ� ��ӡ�ļ�����ʱ����Ϣ
    ���������
    ���������
    �����룺
  *
  */

void PrintTimeConsume(struct timeb start,int lines,char *filename)
{
    struct timeb finish;
    ftime(&finish);
    printf("---��ʱ[%s][%d][%d]\n",filename,lines,(finish.time-start.time)*1000+finish.millitm-start.millitm);
}





/*
 *
    �����ţ� cl0_00022
    ������ƣ� getMaxDay
    ������ܣ� ȡ�����������
    ���룺
			yearmonth������
    �����
			MaxDay		�������
			add by hexy
  *
  */
int getMaxDay(int yearmonth,char *MaxDay){
	int year_num=yearmonth/100;
	int month_num=yearmonth%100;
	printf("\nmonth_num=[%d]\n",month_num);
	if (year_num%100>=0&&year_num%4==0){
		switch(month_num){
			case 1:strcpy(MaxDay,"31");break;
			case 3:strcpy(MaxDay,"31");break;
			case 5:strcpy(MaxDay,"31");break;
			case 7:strcpy(MaxDay,"31");break;
			case 8:strcpy(MaxDay,"31");break;
			case 10:strcpy(MaxDay,"31");break;
			case 12:strcpy(MaxDay,"31");break;
			case 4:strcpy(MaxDay,"30");break;
			case 6:strcpy(MaxDay,"30");break;
			case 9:strcpy(MaxDay,"30");break;
			case 11:strcpy(MaxDay,"30");break;
			case 2:strcpy(MaxDay,"29");break;
			
		}
	}else {
		switch(month_num){
			case 1:strcpy(MaxDay,"31");break;
			case 2:strcpy(MaxDay,"28");break;
			case 3:strcpy(MaxDay,"31");break;
			case 5:strcpy(MaxDay,"31");break;
			case 7:strcpy(MaxDay,"31");break;
			case 8:strcpy(MaxDay,"31");break;
			case 10:strcpy(MaxDay,"31");break;
			case 12:strcpy(MaxDay,"31");break;
			case 4:strcpy(MaxDay,"30");break;
			case 6:strcpy(MaxDay,"30");break;
			case 9:strcpy(MaxDay,"30");break;
			case 11:strcpy(MaxDay,"30");break;
						
		}
	}	
	return 0;
}

/*
 *
    �����ţ� cl0_00023
    ������ƣ� getCurrentTime
    ������ܣ� ȡ�����������
    ���룺
			yearmonth������
    �����
			MaxDay		�������
			add by hexy
  *
  */
void getCurrentTime(char *filename,int linenum)
{
  struct timeb tm;
  struct tm    *time;

  memset(&tm,0,sizeof(struct timeb));

  ftime(&tm);

  time=localtime(&tm.time);
  
  printf("File [%s] Line [%d],Time is : [%02d:%02d:%02d:%03d]\n",filename,linenum,time->tm_hour,time->tm_min,time->tm_sec,tm.millitm);
}



