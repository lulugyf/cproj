#include "publicsrv.h"

extern int errno;

/* ʱ�䴦���� */

/****
�·ݴ�д��Сд
@inparam
				��д��ĸ�·ݡ�JAN��
@outparam
				�������ĸ��01����02��
***/
char *Teton(char *src, char *dest)
{
	Sinitn(dest);

	if (strncmp(src, "Jan", 3) == 0) {
		strcpy(dest, "01");
		return dest;
	}
	if (strncmp(src, "Feb", 3) == 0) {
		strcpy(dest, "02");
		return dest;
	}
	if (strncmp(src, "Mar", 3) == 0) {
		strcpy(dest, "03");
		return dest;
	}
	if (strncmp(src, "Apr", 3) == 0) {
		strcpy(dest, "04");
		return dest;
	}
	if (strncmp(src, "May", 3) == 0) {
		strcpy(dest, "05");
		return dest;
	}
	if (strncmp(src, "Jun", 3) == 0) {
		strcpy(dest, "06");
		return dest;
	}
	if (strncmp(src, "Jul", 3) == 0) {
		strcpy(dest, "07");
		return dest;
	}
	if (strncmp(src, "Aug", 3) == 0) {
		strcpy(dest, "08");
		return dest;
	}
	if (strncmp(src, "Sep", 3) == 0) {
		strcpy(dest, "09");
		return dest;
	}
	if (strncmp(src, "Oct", 3) == 0) {
		strcpy(dest, "10");
		return dest;
	}
	if (strncmp(src, "Nov", 3) == 0) {
		strcpy(dest, "11");
		return dest;
	}
	if (strncmp(src, "Dec", 3) == 0) {
		strcpy(dest, "12");
		return dest;
	}

	return NULL;
}

/****
�·� Сд���д
@inparam
				�������ĸ��01����02��
@outparam
				��д��ĸ�·ݡ�JAN��
***/
char *Tntoe(char *src, char *dest)
{
	Sinitn(dest);

	switch(atoi(src)) {
		case 1:
			strcpy(dest, "Jan");
			break;
		case 2:
			strcpy(dest, "Feb");
			break;
		case 3:
			strcpy(dest, "Mar");
			break;
		case 4:
			strcpy(dest, "Apr");
			break;
		case 5:
			strcpy(dest, "May");
			break;
		case 6:
			strcpy(dest, "Jun");
			break;
		case 7:
			strcpy(dest, "Jul");
			break;
		case 8:
			strcpy(dest, "Aug");
			break;
		case 9:
			strcpy(dest, "Sep");
			break;
		case 10:
			strcpy(dest, "Oct");
			break;
		case 11:
			strcpy(dest, "Nov");
			break;
		case 12:
			strcpy(dest, "Dec");
			break;
		default:
			return NULL;
	}

	return  dest;
}

/***
ʱ��ת������
@inparam
		src:    20010716142900
@outparam
		dest:    Jul 16 2001  2:29PM
***/
int TconvertcDate(char *src, char *dest)
{
/*
**   src:    20010716142900
**  dest:    Jul 16 2001  2:29PM
*/
    char yy[4+1];
    char mm[3+1];
    char tmpmm[3+1];
    char dd[2+1];
    char hh[2+1];
    char mi[2+1];
    char ap_flag[2+1];

    Sinitn(yy);
    Sinitn(mm);
    Sinitn(tmpmm);
    Sinitn(dd);
    Sinitn(hh);
    Sinitn(mi);
    Sinitn(ap_flag);

    strncpy(yy, src, 4);
    strncpy(tmpmm, src+4, 2);
    strncpy(dd, src+6, 2);
    strncpy(hh, src+8, 2);
    strncpy(mi, src+10, 2);

    Sinitn(mm);
    Tntoe(tmpmm, mm);

    if (atoi(hh) > 12) {
	strcpy(ap_flag, "PM");
	sprintf(hh, "%d", atoi(hh) - 12);
        if (atoi(hh) < 10)
            sprintf(hh, "0%d", atoi(hh));
    }
    else
	strcpy(ap_flag, "AM");

    strcpy(dest, mm);
    strcat(dest, " ");
    strcat(dest, dd);
    strcat(dest, " ");
    strcat(dest, yy);
    strcat(dest, " ");
    strcat(dest, hh);
    strcat(dest, ":");
    strcat(dest, mi);
    strcat(dest, ap_flag);

    return 0;
}

/***
ʱ��ת������
@inparam
		dest:    Jul 16 2001  2:29PM
@outparam
		src:    20010716142900
***/

int TconverteDate(char *src, char *dest)
{
/*
**   src:    Jul 16 2001  2:29PM
**  dest:    20010716142900
*/
    char yy[4+1];
    char mm[3+1];
    char tmpmm[3+1];
    char dd[2+1];
    char hh[2+1];
    char mi[2+1];
    char ap_flag[2+1];

    Sinitn(yy);
    Sinitn(mm);
    Sinitn(tmpmm);
    Sinitn(dd);
    Sinitn(hh);
    Sinitn(mi);
    Sinitn(ap_flag);

    strncpy(tmpmm, src, 3);
    strncpy(dd, src+4, 2);
    strncpy(yy, src+7, 4);
    strncpy(hh, src+12, 2);
    strncpy(mi, src+15, 2);
    strncpy(ap_flag, src+17, 2);

    Teton(tmpmm, mm);

    if (atoi(dd) < 10)
        sprintf(dd, "0%d", atoi(dd));

    if (strncmp(ap_flag, "PM", 2) == 0) {
        if (atoi(hh) < 12)
            sprintf(hh, "%d", atoi(hh) + 12);
    }
    else
        if (atoi(hh) < 10)
            sprintf(hh, "0%d", atoi(hh));

    strcpy(dest, yy);
    strcat(dest, mm);
    strcat(dest, dd);
    strcat(dest, hh);
    strcat(dest, mi);
    strcat(dest, "00");

    return 0;
}


/****************************************
name:     Tchgformat							     
writer:   zhaohao           						
modi:     zhaohao           						
date:     2001.11.1       						 
function: ��ʱ���ʽ����ת��						
     ��׼ʱ���ʽ��1��20011031 11:30:30              
			   2��10312001 11:30:30
			   3��2001/10/31 11:30:30
			   4��10/31/2001 11:30:30
			   5��2001-10-31 11:30:30
			   6��10-31-2001 11:30:30
			   7��2001.10.31 11:30:30
			   8��10.31.2001 11:30:30
			   9��Oct 31 2001 11:51AM
			   10��20011031113030
		type:  	1.2 ����20011031 11:30:30 �� 10312001 11:30:30��ת����
		      	9.3 ���� Oct 31 2001 11:51AM �� 2001/10/31 11:30:30��
			�����������Ʊ������ṩ����ʱ�亯��֮���ת��
		ע�⣺Ĭ��Ϊʱ�䷶Χ�ǺϷ��ġ�				      
*****************************************************************************/
char *Tchgformat(char *src, char *dest, char *type)
{
	int  i=0;
	char tmpsrctime[19+1];
	char tmpl[2+1], tmpr[2+1];
	char tmptime[9+1];
	char tmpflag[1+1];

	Sinitn(dest);
	Sinitn(tmpsrctime);
	Sinitn(tmpl);
	Sinitn(tmpr);
	
	for(i=0; i<strlen(type); i++) {
		if (*(type+i) == '.')
			break;
	}
	
	strncpy(tmpl, type, i);
	strcpy(tmpr, type+i+1); 

	if (atoi(tmpl) == atoi(tmpr))
		return src;
		
	switch(atoi(tmpl)) {
		case 1:
			strncpy(tmpsrctime, src, 8);
	 		strncat(tmpsrctime, src+9, 2);
			strncat(tmpsrctime, src+12, 2);
			strncat(tmpsrctime, src+15, 2);
			break;
		case 2:
			strncpy(tmpsrctime, src+4, 4);
			strncat(tmpsrctime, src, 4);
			strncat(tmpsrctime, src+9, 2);
			strncat(tmpsrctime, src+12, 2);
			strncat(tmpsrctime, src+15, 2);
			break;
		case 3:
		case 5:
		case 7:
			strncpy(tmpsrctime, src, 4);
			strncat(tmpsrctime, src+5, 2);
			strncat(tmpsrctime, src+8, 2);
			strncat(tmpsrctime, src+11, 2);
			strncat(tmpsrctime, src+14, 2);
			strncat(tmpsrctime, src+17, 2);
			break;
		case 4:
		case 6:
		case 8:
			strncpy(tmpsrctime, src+6, 4);
			strncat(tmpsrctime, src, 2);
			strncat(tmpsrctime, src+3, 2);
			strncat(tmpsrctime, src+11, 2);
			strncat(tmpsrctime, src+14, 2);
			strncat(tmpsrctime, src+17, 2);
			break;
		case 9:
			TconverteDate(src, tmpsrctime);
			break;
		case 10:
			strcpy(tmpsrctime, src);
			break;
		default:
			return NULL;
	}

	Sinitn(tmptime);
	strcpy(tmptime, " ");
	strncat(tmptime, tmpsrctime+8, 2);
	strcat(tmptime, ":");
	strncat(tmptime, tmpsrctime+10, 2);
	strcat(tmptime, ":");
	strncat(tmptime, tmpsrctime+12, 2);

	Sinitn(tmpflag);
	if (atoi(tmpr) == 3 || atoi(tmpr) == 4)
		strcpy(tmpflag, "/");	
	else if (atoi(tmpr) == 5 || atoi(tmpr) == 6)
		strcpy(tmpflag, "-");	
	else if (atoi(tmpr) == 7 || atoi(tmpr) == 8)
		strcpy(tmpflag, ".");	

	switch(atoi(tmpr)) {
		case 1:
			strncpy(dest, tmpsrctime, 7);
			strcat(dest, tmptime);
			break;
		case 2:
			strncpy(dest, tmpsrctime+4, 4);
			strncat(dest, tmpsrctime, 4);
			strcat(dest, tmptime);
			break;
		case 3:
		case 5:
		case 7:
			strncpy(dest, tmpsrctime, 4);
			strcat(dest, tmpflag);
			strncat(dest, tmpsrctime+4, 2);
			strcat(dest, tmpflag);
			strncat(dest, tmpsrctime+6, 2);
			strcat(dest, tmptime);
			break;
		case 4:
		case 6:
		case 8:
			strncpy(dest, tmpsrctime+4, 2);
			strcat(dest, tmpflag);
			strncat(dest, tmpsrctime+6, 2);
			strcat(dest, tmpflag);
			strncat(dest, tmpsrctime, 4);
			strcat(dest, tmptime);
			break;
		case 9:
			TconvertcDate(tmpsrctime, dest);
			break;
		case 10:
			strcpy(dest, tmpsrctime);
			break;
		default:
			return NULL;
	}
	
	return dest;
}


/*********************************************
 name:     Tgetsysdatetime(int type)				
 writer:   zhaohao           						    
 modi:     zhaohao           						    
 date:     2001.11.1       						      
 function: ���ݸ���������ȡϵͳʱ��					
		type ��ʽ 
		100 Oct 31 2001
		101 10/31/2001
		102 2001/10/31
		103 10.31.2001
		104 2001.10.31
		105 10-31-2001
		106 2001-10-31
		107 10312001
		108 20011031
		109 10:05:16
		110 10:05:16AM
		111 10:05AM						      
******************************************************************************/
char *Tgetsysdatetime(int type)
{
	time_t tm;
	char hh[2+1];
	char ehh[3+1];
    	static char sysdatetime[12+1];

	tm = time(NULL);
	
	Sinitn(sysdatetime);
	Sinitn(hh);
	Sinitn(ehh);
	switch(type) {
		case 100:
    			strftime(sysdatetime, 12, "%m  %d %Y", localtime(&tm));
			strncpy(hh, sysdatetime, 2);
			Tntoe(hh, ehh);
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


/*******************************************
name:     Tgetssysdatetime						    
writer:   zhaohao           						  
modi:     zhaohao           						  
date:     2001.11.1       						    
function: ���������Ը������ַ��ָ�				
****************************************************************************/
char *Tgetssysdatetime(char s)
{
        time_t tm;
        static char ssysdatetime[11+1];

        tm = time(NULL);

        Sinitn(ssysdatetime);
        strftime(ssysdatetime, 12, "%Y %m %d", localtime(&tm));
	*(ssysdatetime+4) = s;
	*(ssysdatetime+7) = s;

	return ssysdatetime;
}

/************************************
 name:     Tgetyear							   
 writer:   zhaohao           				
 modi:     zhaohao           				
 date:     2001.11.1       					
 function: ȡ��ǰ��							   
*****************************************************************************/
char *Tgetyear()
{
        time_t tm;
        static char curyear[4+1];

        tm = time(NULL);

        Sinitn(curyear);
        strftime(curyear, 5, "%Y", localtime(&tm));

	return curyear;
}


/**************************************
name:     Tgetmonth							   
writer:   zhaohao           					
modi:     zhaohao           					
date:     2001.11.1       						
function: ȡ��ǰ��							     
****************************************************************************/
char *Tgetmonth()
{
        time_t tm;
        static char curmonth[2+1];

        tm = time(NULL);

        Sinitn(curmonth);
        strftime(curmonth, 3, "%m", localtime(&tm));

	return curmonth;
}


/************************************
name:     Tgetday							   
writer:   zhaohao           				
modi:     zhaohao           				
date:     2001.11.1       					
function: ȡ��ǰ��							   
****************************************************************************/
char *Tgetday()
{
        time_t tm;
        static char curday[2+1];

        tm = time(NULL);

        Sinitn(curday);
        strftime(curday, 3, "%d", localtime(&tm));

	return curday;
}

/*************************************
name:     Tgethour							    
writer:   zhaohao           				
modi:     zhaohao           				
date:     2001.11.1       					
function: ȡ��ǰСʱ							  
****************************************************************************/
char *Tgethour()
{
        time_t tm;
        static char curhour[2+1];

        tm = time(NULL);

        Sinitn(curhour);
        strftime(curhour, 3, "%H", localtime(&tm));

	return curhour;
}

/***************************************
name:     Tgetminute							    
writer:   zhaohao           					
modi:     zhaohao           					
date:     2001.11.1       						
function: ȡ��ǰ����							    
****************************************************************************/
char *Tgetminute()
{
        time_t tm;
        static char curminute[2+1];

        tm = time(NULL);

        Sinitn(curminute);
        strftime(curminute, 3, "%M", localtime(&tm));

	return curminute;
}

/**************************************
 name:     Tgetsecond							   
 writer:   zhaohao           					
 modi:     zhaohao           					
 date:     2001.11.1       						
 function: ȡ��ǰ��							     
*****************************************************************************/
char *Tgetsecond()
{
        time_t tm;
        static char cursecond[2+1];

        tm = time(NULL);

        Sinitn(cursecond);
        strftime(cursecond, 3, "%S", localtime(&tm));

	return cursecond;
}

/*************************************
 name:     Tvalid							      
 writer:   zhaohao           				
 modi:     zhaohao           				
 date:     2001.11.2       					
 function: �жϸ�����ʱ��ֵ�Ƿ�Ϸ�	
	     ����ֵ: 1 �Ϸ� 0 ���Ϸ�			
*****************************************************************************/
int Tvalid(char *src)
{
	return 1;
}
