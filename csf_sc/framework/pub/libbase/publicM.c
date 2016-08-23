#include "publicsrv.h"
extern int errno;

void Mdoubletocase(double sum,char *ccase);

/* ���ת���� */
/******************************************************************************/
/* name:     Mchartocase 						      */
/* writer:              						      */
/* modi:     zhaohao           						      */
/* date:     2001.11.1       						      */
/* function: ���ַ�c��Ӧ������ת���ɺ��ֵ�Ҽ������,Ȼ�󸽼���dest��           */
/******************************************************************************/
void Mchartocase(char *dest,char c)
{
	switch (c) {
		case '1':
			strcat(dest,"Ҽ");
			break;
		case '2':
			strcat(dest,"��");
			break;
		case '3':
			strcat(dest,"��");
			break;
		case '4':
			strcat(dest,"��");
			break;
		case '5':
			strcat(dest,"��");
			break;
		case '6':
			strcat(dest,"½");
			break;
		case '7':
			strcat(dest,"��");
			break;
		case '8':
			strcat(dest,"��");
			break;
		case '9':
			strcat(dest,"��");
			break;
		case '0':
			strcat(dest,"��");
			break;
		default :
			break;
	}
	return;
}

/******************************************************************************/
/* name:     Mchgmoney	 						      */
/* writer:              						      */
/* modi:     zhaohao           						      */
/* date:     2001.11.1       						      */
/* function: ��src��ȡ��(ȥ�����еĶ���)�����˫������ddest��Ȼ����ת��Ϊ     */
/*           ������ʽcdest  						      */
/******************************************************************************/
void Mchgmoney(char *src,char *cdest,char *ddest)
{
	int i=0, j=0;
	char tmpstr[150];

	memset(tmpstr, 0, sizeof(tmpstr));
	for(i=0;i<strlen(src);i++)
	{
		if (src[i] != ',')
		{
			ddest[j]=src[i];
			j++;
			ddest[j]=0;
		}
	}

	Mdoubletocase(atof(ddest),tmpstr);
	for(i=0;i<strlen(tmpstr);i++)
	{
		cdest[i]=tmpstr[i];
	}
	cdest[i]=0;

	return ;
}


/******************************************************************************/
/* name:     Mdoubletocase						      */
/* writer:   Unknown           						      */
/* modi:     zhaohao           						      */
/* date:     2001.11.1       						      */
/* function: ��˫���ȵ���ת��Ϊ��д�Ľ��				      */
/******************************************************************************/
void Mdoubletocase(double sum,char *ccase)
{
   int i;
   int count;
   char c;
   char *trace;
   char *tail;
   char s[150];
   char upcase[150];

   sprintf(upcase,"%.2lf",sum);
   s[0]='\0';
   i=-1;
   while (c=upcase[++i])
      if ((c>'9' || c<'0') && c!='\0' && c!='.')
         return ;

   i=-1;
   while (upcase[++i]=='0');
   if (upcase[i]=='\0' || upcase[i]=='.')
      strcat(s,"��Ԫ");

   if (upcase[i]=='\0')
   {
	strcat(s,"��");
 	strcpy(upcase,s);
      	strcpy(ccase,upcase);
      	return ;
   }
   trace=upcase+i;

   for (i=0;;i++)
       if (trace[i]=='.' || trace[i]=='\0')
          break;

   if (i>8)
      return ;
   count=i-1;
   tail=s;
   for (i=0;i<=count;i++)
   {
      if (strncmp(tail-2,"��",2)!=0 || trace[i]!='0')
	/*This means the tail of the string is not "��"*/
      {

         Mchartocase(s,trace[i]);
         tail+=2;
      }
      if (trace[i]!='0' )
      switch (count-i){
         case 0:strcat(s,"Ԫ");
                tail+=2;
                break;
         case 1:strcat(s,"ʰ");
                tail+=2;
                break;
         case 2:strcat(s,"��");
                tail+=2;
                break;
         case 3:strcat(s,"Ǫ");
                tail+=2;
                break;
         case 4:strcat(s,"��");
                tail+=2;
                break;
         case 5:strcat(s,"ʰ");
                tail+=2;
                break;
         case 6:strcat(s,"��");
		tail+=2;
                break;
         case 7:strcat(s,"Ǫ");
                tail+=2;
                break;
         default:break;
      } else if((count-i)==4)
             {
                if (strncmp(tail-2,"��",2)==0)
                {
                   (*(tail-2))='\0';
                   tail-=2;
                }
                strcat(s,"��");
                tail+=2;
             }
             else if((count-i)==0)
             {
                if (strncmp(tail-2,"��",2)==0)
                {
                   (*(tail-2))='\0';
                   tail-=2;

                }
                strcat(s,"Ԫ");
                tail+=2;
             }
   } /* -- of for -- */
   if (trace[count+1]=='\0')
   {
      strcat(s,"��");
      tail+=2;
      strcpy(upcase,s);
      strcpy(ccase,upcase);
      return ;
   }
   i=count+2;

   if (trace[i]=='0' && trace[i+1]!='0' && trace[i+1]!='\0')
   {
      strcat(s,"��");
      Mchartocase(s,trace[i+1]);
      strcat(s,"��");
      strcpy(upcase,s);
      strcpy(ccase,upcase);
      return ;
   }
   if (trace[i]=='0' && trace[i+1]=='0')
   {
      strcat(s,"��");
      tail+=2;
      strcpy(upcase,s);
      strcpy(ccase,upcase);
      return ;
   }
   else {
      if (trace[i]!='0' && trace[i]!='\0')
      {
         if (trace[i-2]=='0')
         strcat(s,"��");
         Mchartocase(s,trace[i]);
         tail+=2;
         strcat(s,"��");
         tail+=2;
         if (trace[i+1]=='0'|| trace[i+1]=='\0')
         {
            strcat(s,"��");
            tail+=2;
            strcpy(upcase,s);
            strcpy(ccase,upcase);
            return ;
	}
      } else if (trace[i]=='\0')
             {
                strcat(s,"��");
                tail+=2;
                strcpy(upcase,s);
                strcpy(ccase,upcase);
                return ;
             }
      if (trace[i+1]!='0' && trace[i+1]!='\0')
      {
         Mchartocase(s,trace[i+1]);
         strcat(s,"��");
        /* strcat(s,"��"); */
         tail+=6;
      }
   }
   strcpy (upcase,s);
   strcpy(ccase,upcase);
   return ;
}



/*****ʱ��ת������**********
***f_time: �����ϵ�ʱ��ֵ***
***r_year: ������ֵ      ***
***r_month:������ֵ      ***
***r_day:  ������ֵ      ***/

void chg_time(
char* f_time,
char* r_year,
char* r_month,
char* r_day)
{
     int  i;
     char cur_time[20];
     char cur_year[5],cur_month[3],cur_day[3];
   
     r_month[0]=f_time[0];
     r_month[1]=f_time[1];
     r_month[2]=0;
     if (r_month[0] == '0')
         r_month[0]=0x20;

     r_day[0]=f_time[3];
     r_day[1]=f_time[4];
     r_day[2]=0;
     if (r_day[0] == '0')
        r_day[0]=0x20;

     r_year[0]=f_time[6];
     r_year[1]=f_time[7];
     r_year[2]=f_time[8];
     r_year[3]=f_time[9];
     r_year[4]=0;
     
}

void change_password(
char *in,
char *out)
{
             char s1[10];
             char s2[10];
             unsigned char s3[10];
             int leng,i,j;
             int  change[10]={11,22,9,15,27,18,14,22,13,5};


             strcpy(s1,in);
             leng = strlen(s1);
             for(i=0;i<leng;i++)
             {
                s3[leng-i-1] = s1 [i] + i;
             }
             for(i=0;i<leng;i++)
             {
                s3[i] = s3[i]+change[i]  ;
                if (s3[i] > 58 && s3[i] < 65 ) s3[i] = 8+s3[i]  ;
                if (s3[i] > 90 && s3[i] < 97 ) s3[i] = 8+s3[i]  ;
                if (s3[i] > 122 ) s3[i] = s3[i]-122+97  ;
             }
             strcpy(s2,(char *)s3);
             for(i=0;i<leng;i++)
             {
                s3[leng-i-1] = s2 [i] ;
             }
             s3[leng]=0;
             strcpy(out,(char *)s3);
}

/* ��С�����numλ������������ */
