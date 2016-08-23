#include "Encrypt.h"
/***********************************
*函数名：int DcReadcfg
*功能：读取配置文件
*
*参数说明：
*    输入：
*    输出：
*时间：2005.11.18
*修改者：
*修改时间：
************************************/
int DcReadCfg(char* section, char* key, char* value)
{
	FILE*   cfgfile;
	char    buff[200];
	char    section_ext[200];
	char    key_value[200];
	int     find=0;
	char    value_ext[200];
	char    cfgname[100];
	char    * pBOSSCfg;
	
	memset(cfgname,0,sizeof(cfgname));	
	memset(section_ext,0,sizeof(section_ext));
	memset(key_value,0,sizeof(key_value));
	memset(buff,0,sizeof(buff));
	memset(value_ext,0,sizeof(value_ext));
		
	if(NULL!=(pBOSSCfg = getenv("PASSWORDCONFIG")))
    {
        sprintf(cfgname,"%s",pBOSSCfg);
	}else{
	   sprintf(cfgname,"%s","/etc/.ngpasswordconfig");
    }
    
    /*printf("=============.bossconfig路径=[%s]=============",cfgname);*/
		
	if((cfgfile = fopen(cfgname,"r"))==NULL)
	return -1;
	
	/*查找section*/
	sprintf(section_ext, "[%s]", section);
	for(;fgets(buff, sizeof(buff), cfgfile);)
	{
		if(buff[0] == '#')
		continue;
		if(buff[0]!= '[')
		continue;
		if(strstr(buff, section_ext) == NULL)
		continue;
		else
		{
			find = 1;
			break;
		}
	}

	if(find==0)
	{
		fclose(cfgfile);
		return -2;
	}

	/*查找key=value*/

	value_ext[0] = '0';
	find=0;

	for(; fgets(buff, sizeof(buff), cfgfile); )
	{
		if(buff[0] == '#')
		continue;
		if(strstr(buff, key) == NULL)
		continue;
		else
		{
			sprintf(key_value, "%s=%%s\n", key);
			sscanf(buff, key_value, value_ext);
			find = 1;
			break;
		}
	}

	fclose(cfgfile);
	if(find == 0)
	return -3; /* No such proces */

	if(value_ext[0] == '\0')
	return 1;   /* Interrupted system call */
	else
	{
		strcpy(value,value_ext);
		return 1;
	}
}

/*****************************************************************\
 * 	函 数 名	:	decrypt_rc2_array
 * 	函数功能	:	解密函数
 * 	编 程 者	:  	神州数码有限公司
 * 	编写日期	:	2002.08.09
 *	输入参数	:	des密钥、解密前字符串，解密字符串长度
 *	输出参数	:	解密后字符串
 * 	修 改 者	: 	
 * 	修改内容	:  	
 * 	修改日期	:	
\*****************************************************************/
int decrypt_rc2_array(unsigned char * buf,const int buf_len,char * key);


/*****************************************************************\
 * 	函 数 名	:	crypt_rc2_array
 * 	函数功能	:	加密函数
 * 	编 程 者	:  	神州数码有限公司
 * 	编写日期	:	2002.08.09
 *	输入参数	:	des密钥、加密前字符串，加密字符串长度
 *	输出参数	:	加密后字符串
 * 	修 改 者	: 	
 * 	修改内容	:  	
 * 	修改日期	:	
\*****************************************************************/

int crypt_rc2_array(unsigned char * buf,const int buf_len,char * key);



int rc2_keyschedule(unsigned short xkey[64],const unsigned char *key,unsigned len,unsigned bits);
/*****************************************************************\
 * 	函 数 名	:	rc2_encrypt
 * 	函数功能	:	对8位字符进行加密
 * 	编 程 者	:  	神州数码有限公司
 * 	编写日期	:	2002.08.09
 *	输入参数	:	des密钥、解密前字符串，解密字符串长度
 *	输出参数	:	解密后字符串
 * 	修 改 者	: 	
 * 	修改内容	:  	
 * 	修改日期	:	
\*****************************************************************/


void rc2_encrypt(const unsigned short xkey[64],const unsigned char *plain,unsigned char *cipher);
/*****************************************************************\
 * 	函 数 名	:	rc2_encrypt_chr
 * 	函数功能	:	对1位字符进行加密
 * 	编 程 者	:  	神州数码有限公司
 * 	编写日期	:	2002.08.09
 *	输入参数	:	des密钥、解密前字符串，解密字符串长度
 *	输出参数	:	解密后字符串
 * 	修 改 者	: 	
 * 	修改内容	:  	
 * 	修改日期	:	
\*****************************************************************/


void rc2_encrypt_chr(const unsigned short xkey[64],const unsigned char *plain,unsigned char *cipher);
/*****************************************************************\
 * 	函 数 名	:	rc2_decrypt
 * 	函数功能	:	对8位字符进行解密
 * 	编 程 者	:  	神州数码有限公司
 * 	编写日期	:	2002.08.09
 *	输入参数	:	des密钥、解密前字符串，解密字符串长度
 *	输出参数	:	解密后字符串
 * 	修 改 者	: 	
 * 	修改内容	:  	
 * 	修改日期	:	
\*****************************************************************/



void rc2_decrypt(const unsigned short xkey[64],unsigned char *plain,const unsigned char *cipher);
/*****************************************************************\
 * 	函 数 名	:	rc2_decrypt_chr
 * 	函数功能	:	对1位字符进行解密
 * 	编 程 者	:  	神州数码有限公司
 * 	编写日期	:	2002.08.09
 *	输入参数	:	des密钥、解密前字符串，解密字符串长度
 *	输出参数	:	解密后字符串
 * 	修 改 者	: 	
 * 	修改内容	:  	
 * 	修改日期	:	
\*****************************************************************/
void rc2_decrypt_chr(const unsigned short xkey[64],unsigned char *plain,const unsigned char *cipher);


int rc2_keyschedule(unsigned short xkey[64],
					 const unsigned char *key,
					 unsigned len,
					 unsigned bits )
{
	unsigned char x;
	unsigned i;
	/* 256-entry permutation table, probably derived somehow from pi */
	static const unsigned char permute[256] = {
	    217,120,249,196, 25,221,181,237, 40,233,253,121, 74,160,216,157,
	    198,126, 55,131, 43,118, 83,142, 98, 76,100,136, 68,139,251,162,
	     23,154, 89,245,135,179, 79, 19, 97, 69,109,141,  9,129,125, 50,
	    189,143, 64,235,134,183,123, 11,240,149, 33, 34, 92,107, 78,130,
	     84,214,101,147,206, 96,178, 28,115, 86,192, 20,167,140,241,220,
	     18,117,202, 31, 59,190,228,209, 66, 61,212, 48,163, 60,182, 38,
	    111,191, 14,218, 70,105,  7, 87, 39,242, 29,155,188,148, 67,  3,
	    248, 17,199,246,144,239, 62,231,  6,195,213, 47,200,102, 30,215,
	      8,232,234,222,128, 82,238,247,132,170,114,172, 53, 77,106, 42,
	    150, 26,210,113, 90, 21, 73,116, 75,159,208, 94,  4, 24,164,236,
	    194,224, 65,110, 15, 81,203,204, 36,145,175, 80,161,244,112, 57,
	    153,124, 58,133, 35,184,180,122,252,  2, 54, 91, 37, 85,151, 49,
	     45, 93,250,152,227,138,146,174,  5,223, 41, 16,103,108,186,201,
	    211,  0,230,207,225,158,168, 44, 99, 22,  1, 63, 88,226,137,169,
	     13, 56, 52, 27,171, 51,255,176,187, 72, 12, 95,185,177,205, 46,
	    197,243,219, 71,229,165,156,119, 10,166, 32,104,254,127,193,173
	};

	if(!(len > 0 && len <= 128))
	{
		printf("参数不对！\n");
		return -1;
	}
	if(!(bits <= 1024))
	{
		printf("参数不对！\n");
		return -1;
	}
	if (!bits)
		bits = 1024;

	memcpy(xkey, key, len);

	/* Phase 1: Expand input key to 128 bytes */
	if (len < 128) {
		i = 0;
		x = ((unsigned char *)xkey)[len-1];
		do {
			x = permute[(x + ((unsigned char *)xkey)[i++]) & 255];
			((unsigned char *)xkey)[len++] = x;
		} while (len < 128);
	}

	/* Phase 2 - reduce effective key size to "bits" */
	len = (bits+7) >> 3;
	i = 128-len;
	x = permute[((unsigned char *)xkey)[i] & (255 >> (7 & -bits))];
	((unsigned char *)xkey)[i] = x;

	while (i--) {
		x = permute[ x ^ ((unsigned char *)xkey)[i+len] ];
		((unsigned char *)xkey)[i] = x;
	}

	/* Phase 3 - copy to xkey in little-endian order */
	i = 63;
	do {
		xkey[i] =  ((unsigned char *)xkey)[2*i] +
		          (((unsigned char *)xkey)[2*i+1] << 8);
	} while (i--);

	return 0;
}

void rc2_encrypt(const unsigned short xkey[64],
				 const unsigned char *plain,
				 unsigned char *cipher )
{
	unsigned x76, x54, x32, x10, i;

	x76 = (plain[7] << 8) + plain[6];
	x54 = (plain[5] << 8) + plain[4];
	x32 = (plain[3] << 8) + plain[2];
	x10 = (plain[1] << 8) + plain[0];

	for (i = 0; i < 16; i++) {
		x10 += (x32 & ~x76) + (x54 & x76) + xkey[4*i+0];
		x10 = (x10 << 1) + (x10 >> 15 & 1);
		
		x32 += (x54 & ~x10) + (x76 & x10) + xkey[4*i+1];
		x32 = (x32 << 2) + (x32 >> 14 & 3);

		x54 += (x76 & ~x32) + (x10 & x32) + xkey[4*i+2];
		x54 = (x54 << 3) + (x54 >> 13 & 7);

		x76 += (x10 & ~x54) + (x32 & x54) + xkey[4*i+3];
		x76 = (x76 << 5) + (x76 >> 11 & 31);

		if (i == 4 || i == 10) {
			x10 += xkey[x76 & 63];
			x32 += xkey[x10 & 63];
			x54 += xkey[x32 & 63];
			x76 += xkey[x54 & 63];
		}
	}

	cipher[0] = (unsigned char)x10;
	cipher[1] = (unsigned char)(x10 >> 8);
	cipher[2] = (unsigned char)x32;
	cipher[3] = (unsigned char)(x32 >> 8);
	cipher[4] = (unsigned char)x54;
	cipher[5] = (unsigned char)(x54 >> 8);
	cipher[6] = (unsigned char)x76;
	cipher[7] = (unsigned char)(x76 >> 8);

	return;
}

void rc2_encrypt_chr(const unsigned short xkey[64],
					 const unsigned char *plain,
					 unsigned char *cipher )
{
	unsigned char src;
	int i;
	src=(*plain);

	for(i=0;i<64;i++)
	{
		src += ( xkey[i] >> 8 & 255);
		src ^= ( xkey[i] & 255 ); 
		src = (src << 5 & 224) + (src >> 3 & 31);

		if((i%16) == 4 || (i%16) == 5 | (i%16) == 14)
		{
			src ^= ( xkey[i] >> 8 & 255 );
			src -= ( xkey[i] & 255);
		}
	}

	*cipher = src;

	return;
}

void rc2_decrypt( const unsigned short xkey[64],
                  unsigned char *plain,
                  const unsigned char *cipher )
{
	unsigned x76, x54, x32, x10, i;

	x76 = (cipher[7] << 8) + cipher[6];
	x54 = (cipher[5] << 8) + cipher[4];
	x32 = (cipher[3] << 8) + cipher[2];
	x10 = (cipher[1] << 8) + cipher[0];

	i = 15;
	do 
	{
		x76 &= 65535;
		x76 = (x76 << 11) + (x76 >> 5);
		x76 -= (x10 & ~x54) + (x32 & x54) + xkey[4*i+3];

		x54 &= 65535;
		x54 = (x54 << 13) + (x54 >> 3);
		x54 -= (x76 & ~x32) + (x10 & x32) + xkey[4*i+2];
		
		x32 &= 65535;
		x32 = (x32 << 14) + (x32 >> 2);
		x32 -= (x54 & ~x10) + (x76 & x10) + xkey[4*i+1];

		x10 &= 65535;
		x10 = (x10 << 15) + (x10 >> 1);
		x10 -= (x32 & ~x76) + (x54 & x76) + xkey[4*i+0];

		if (i == 5 || i == 11) 
		{
			x76 -= xkey[x54 & 63];
			x54 -= xkey[x32 & 63];
			x32 -= xkey[x10 & 63];
			x10 -= xkey[x76 & 63];
		}
	} while (i--);

	plain[0] = (unsigned char)x10;
	plain[1] = (unsigned char)(x10 >> 8);
	plain[2] = (unsigned char)x32;
	plain[3] = (unsigned char)(x32 >> 8);
	plain[4] = (unsigned char)x54;
	plain[5] = (unsigned char)(x54 >> 8);
	plain[6] = (unsigned char)x76;
	plain[7] = (unsigned char)(x76 >> 8);

	return;
}

void rc2_decrypt_chr(const unsigned short xkey[64],
					 unsigned char *plain,
					 const unsigned char *cipher)
{
	unsigned char src;
	int i;
	src=(*cipher);

	for(i=63;i>=0;i--)
	{
		if((i%16) == 4 || (i%16) == 5 | (i%16) == 14)
		{
			src += (xkey[i] & 255);
			src ^= ( xkey[i] >> 8 & 255 );
		}
		
		src = (src << 3 & 248) + (src >> 5 & 7);
		src ^= ( xkey[i] & 255 ); 
		src -= ( xkey[i] >> 8 & 255);
	}

	*plain = src;

	return;
}

int decrypt_rc2_array(unsigned char * buf,
					   const int buf_len,
					   char * key)
{
	unsigned short xkey[64];
	unsigned char in[9];
	unsigned char out[9];
	char *p;
	int i,j,k;
	int m;
	if (buf_len<0)
		return -1;
	if(rc2_keyschedule(xkey,(unsigned char *)key,strlen(key),0)<0)
	{
		printf("初始化密码表错误！\n");
		return -1;
	}
	j=buf_len/8;
	for (i=0;i<j;i++)
	{
		for(k=0;k<8;k++)
		{
			in[k]=buf[i*8+k];
		}	
		rc2_decrypt(xkey,out,in);
		for(k=0;k<8;k++)
		{
			buf[i*8+k]=out[k];
		}	
	}
	
	p=(char *)&buf[i*8];
	if(strlen(p)>0)
	{
		for(m=0;m<(buf_len-8*i);m++)
		{
			unsigned char chr_in,chr_out;
			chr_in=*(p+m);
			rc2_decrypt_chr(xkey,&chr_out,&chr_in);
			*(p+m)=chr_out;
		}
	}

	return 0;
}

int crypt_rc2_array(unsigned char * buf, const int buf_len,char * key)
{
	unsigned short xkey[64];
	unsigned char in[9];
	unsigned char out[9];
	char *p;
	int i,j,k;
	int m;
	if (buf_len<0)
		return -1;
	if(rc2_keyschedule( xkey,(unsigned char *)key,strlen(key),0)<0)
	{
		printf("初始化密码表错误！\n");
		return -1;
	}
	j=buf_len/8;
	for (i=0;i<j;i++)
	{
		for(k=0;k<8;k++)
		{
			in[k]=buf[i*8+k];
		}	
		rc2_encrypt(xkey,in,out);
		for(k=0;k<8;k++)
		{
			buf[i*8+k]=out[k];
		}	
	}
	
	p=(char *)&buf[i*8];
	if(strlen(p)>0)
	{
		for(m=0;m<(buf_len-8*i);m++)
		{
			unsigned char chr_in,chr_out;
			chr_in=*(p+m);
			rc2_encrypt_chr(xkey,&chr_in,&chr_out);
			*(p+m)=chr_out;
		}
	}

	return 0;
}

/***********************
 *函数： int decrypt(char *encrychr)
 *功能：封装了密钥的解密函数(用于数据库的用户和口令的解密)
 *2005-12-10 16:36 sunxh add 
 ***********************/
int decrypt2(char *encrychr)
 {
 	char srcbuf[256]; 	
	int i;
	char key[33];
	int len;
	char ctmp[3];
	
	memset(srcbuf,0,sizeof(srcbuf));	
	memset(key,0,sizeof(key));
	memset(ctmp,0,sizeof(ctmp));
	
	strcpy(key,"qwertyuiopasdfghjklzxcvbnm");
	 	
	len=strlen(encrychr);

	for(i=0;i<len/2;i++)
	{
		int tmp;
		memset(ctmp,0,sizeof(ctmp));
		memcpy(ctmp,&(encrychr[2*i]),2);
		sscanf(ctmp,"%2x",&tmp);
		srcbuf[i]=(char)tmp;
	}

	decrypt_rc2_array((unsigned char *)srcbuf,i,key);	 	
 	memset(encrychr,0,sizeof(encrychr));
 	sprintf(encrychr,srcbuf);
 	
 	return 1; 	
 }	
 
 
/***********************
*函数： int encrypt2(char *srcbuf)
*功能：封装了密钥的加密函数(用于数据库的用户和口令的加密)
*2005-12-10 16:36 sunxh add 
***********************/
int encrypt2(char* srcbuf)
 {
 	char key[33];
 	char encrychr[1024];
 	char ctmp[3];
 	int len;
 	int i;
 	
 	
 	memset(key,0,sizeof(key));
 	memset(ctmp,0,sizeof(ctmp));
 	memset(encrychr,0,sizeof(encrychr));
 	
 	strcpy(key,"qwertyuiopasdfghjklzxcvbnm");
 	
 	len=strlen(srcbuf);
	crypt_rc2_array((unsigned char *)srcbuf,len,key);

	for(i=0;i<len;i++)
	{
		int tmp;
		tmp=0;
		memcpy((void *)(&tmp),(void *)(&srcbuf[i]),1);
		memset(ctmp,0,sizeof(ctmp));
		sprintf(&(encrychr[2*i]),"%02x",srcbuf[i]&0xFF);
	}
	
	memset(srcbuf,'\0',sizeof(srcbuf));		
	sprintf(srcbuf,"%s",encrychr);
	
	return 1;
}

