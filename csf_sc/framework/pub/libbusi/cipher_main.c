#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

char asc_val[] = {
  'A','z','C','s','E','k','G','r','I','y',
  'K','u','M','q','O','n','Q','l','S','f',
  'U','h','W','c','Y','a','Z','b','X','d',
  'e','T','g','V','i','j','F','p','m','P',
  'o','N','R','H','D','t','L','v','w','B',
  'J','x'
};

/***************************************************/
/*  en_cipher():���ܺ���                           */
/*    src:�������,����,�̶�6�ֽ�����              */
/*    dst:�������,����,�̶�6�ֽ���ĸ              */
/***************************************************/
void en_cipher(char *src,char *dst)
{
  int val,i,m;
  struct timeval tv;

  if(src==NULL || dst==NULL)
    return;

  val=atoi(src);
  gettimeofday(&tv,NULL);

  val=(tv.tv_usec%2146)*1000000+val;

  for(i=0;i<6;i++)
  {
    m=val%52;
    val=val/52;
    dst[i]=asc_val[m];
  }
  dst[6]=0;

  return;
}

/***************************************************/
/*  de_cipher():���ܺ���                           */
/*    src:�������,����,�̶�6�ֽ���ĸ              */
/*    dst:�������,����,�̶�6�ֽ�����              */
/***************************************************/
void de_cipher(char *src,char *dst)
{
  int val,m,i;

  if(src==NULL || dst==NULL)
    return;

  for(val=0,i=5;i>=0;i--)
  {
    for(m=0; m<52 && asc_val[m]!=src[i]; m++);
    val=val*52+m;
  }
  sprintf(dst,"%06d\0",val%1000000);

  return;
}

/***************************************************/
/*  cmp_cipher():����У�麯��                      */
/*    s1:�������1,���Ļ�����,�̶�6�ֽ����ֻ���ĸ  */
/*    s2:�������2,���Ļ�����,�̶�6�ֽ����ֻ���ĸ  */
/*  ���:����У��ɹ�������0                       */
/***************************************************/
int cmp_cipher(char *s1,char *s2)
{
  char ss1[8],ss2[8];
  char *sp1,*sp2;

  if(s1==NULL || s2==NULL)
    return -1;

  if(s1[0]>'9')
  {
    de_cipher(s1,ss1);
    sp1=ss1;
  }
  else
    sp1=s1;

  if(s2[0]>'9')
  {
    de_cipher(s2,ss2);
    sp2=ss2;
  }
  else
    sp2=s2;

  if(strncmp(sp1,sp2,6)==0)
    return 0;
  else
    return 1;
}

/*** TEST ***/
int main(int argc,char **argv)
{
  char src[8],dst[8],ss[16];
  int ret;

  if(argc!=2)
  {
    printf("Usage:%s cipher[000000-999999]\n",argv[0]);
    exit(1);
  }

  strncpy(src,argv[1],6);

  en_cipher(src,dst);
  de_cipher(dst,ss);
  ret=cmp_cipher(src,dst);

  printf("---%s---%s---%s---%s---%d---\n",argv[1],src,dst,ss,ret);
}
/*** TEST ***/

