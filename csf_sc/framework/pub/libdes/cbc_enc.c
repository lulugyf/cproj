/* cbc_enc.c */
/* Copyright (C) 1993 Eric Young - see README for more details */
#include "des_locl.h"

int AscToBcd(const char* src, unsigned char *dest, int srcLen)
{
	int i;

	memset(dest, 0, sizeof(dest));
	for (i=0; i < srcLen; i +=2)
	{
		dest[i / 2] = ((src[i] - 'A') << 4) + (src[i + 1] - 'A');
	}
	dest[srcLen / 2] = 0;
	return 0;
}

int BcdToAsc(unsigned char* src, char *dest, int srcLen)
{
	int i;

	for (i=0; i < srcLen; i ++)
	{
		dest[i * 2] = 'A' + (src[i] >> 4);
		dest[i * 2 + 1] = 'A' + (src[i] & 0x0F);
	}
	dest[srcLen * 2] = 0;
	return 0;
}

/*
 * flags: 1加密 0解密
 */
void spublicEnDePasswd(const char *src, char *dest, char *key, int flags)
{
	register int i;
	des_key_schedule ks;
	unsigned char iv[8];
	int l,rem;
	des_cblock kk;
	unsigned char src1[MAXENDELEN + 1];
	unsigned char dest1[MAXENDELEN + 1];

	des_string_to_key(key,(C_Block *)kk);

	des_set_key((C_Block *)kk,ks);
	memset(iv,0,sizeof(iv));

	l=1;
	rem=0;
	if (flags)
	{
		strcpy((char*)src1, src);
		l=strlen((char*)src1);
		if (l < 0)
		{
			return;
		}

		rem=l%8;
		srand(time(NULL));
		for (i=8-rem; i>0; i--)	src1[l++]='\0';

		des_cbc_encrypt(
			(des_cblock *)src1,(des_cblock *)dest1,
			(long)l,ks,(des_cblock *)iv,DES_ENCRYPT);
		if (l >= 8) bcopy(&(dest1[l-8]),iv,8);
		BcdToAsc(dest1, dest, l);
	}
	else
	{
		l=strlen(src);
		AscToBcd(src, src1, l);
		l = l/2;
		if (l < 0)
		{
			return ;
		}
		des_cbc_encrypt(
			(des_cblock *)src1,(des_cblock *)dest,
			(long)l,ks,(des_cblock *)iv,DES_DECRYPT);
	}
	return ;
}


int des_cbc_encrypt(des_cblock * input,des_cblock * output,long length,des_key_schedule schedule,des_cblock * ivec,int encrypt)
{
	register unsigned long tin0,tin1;
	register unsigned long tout0,tout1,xor0,xor1;
	register unsigned char *in,*out;
	register long l=length;
	unsigned long tout[2],tin[2];
	unsigned char *iv;

	in=(unsigned char *)input;
	out=(unsigned char *)output;
	iv=(unsigned char *)ivec;

	if (encrypt)
		{
		c2l(iv,tout0);
		c2l(iv,tout1);
		for (; l>0; l-=8)
			{
			if (l >= 8)
				{
				c2l(in,tin0);
				c2l(in,tin1);
				}
			else
				c2ln(in,tin0,tin1,l);
			tin0^=tout0;
			tin1^=tout1;
			tin[0]=tin0;
			tin[1]=tin1;
			des_encrypt((unsigned long *)tin,(unsigned long *)tout,
				schedule,encrypt);
			tout0=tout[0];
			tout1=tout[1];
			l2c(tout0,out);
			l2c(tout1,out);
			}
		}
	else
		{
		c2l(iv,xor0);
		c2l(iv,xor1);
		for (; l>0; l-=8)
			{
			c2l(in,tin0);
			c2l(in,tin1);
			tin[0]=tin0;
			tin[1]=tin1;
			des_encrypt((unsigned long *)tin,(unsigned long *)tout,
				schedule,encrypt);
			tout0=tout[0]^xor0;
			tout1=tout[1]^xor1;
			if (l >= 8)
				{
				l2c(tout0,out);
				l2c(tout1,out);
				}
			else
				l2cn(tout0,tout1,out,l);
			xor0=tin0;
			xor1=tin1;
			}
		}
	tin0=tin1=tout0=tout1=xor0=xor1=0;
	tin[0]=tin[1]=tout[0]=tout[1]=0;
	return(0);
	}


/*
 * 加密
 * 返回的字符串需要在外部free
 */
char * pubEncrypt(const char *src, const int inlen, int *outlen, char *key)
{
	register int i;
	des_key_schedule ks;
	unsigned char iv[8];
	int l,rem;
	des_cblock kk;
	unsigned char *src1;
	unsigned char *dest1;
	char *dest;

	des_string_to_key(key,(C_Block *)kk);
	des_set_key((C_Block *)kk,ks);
	memset(iv,0,sizeof(iv));
	
	if(inlen % 8 > 0)
		l = inlen + (8-inlen%8);
	else
		l = inlen;

	src1 = (unsigned char *)malloc(l);
	if(src1 == NULL) return NULL;
	dest1 = (unsigned char *)malloc(l);
	if(dest1 == NULL) { free(src1); return NULL; }
	
	memset(src1+(l-8), 0, 8);
	memcpy(src1, src, inlen);

	srand(time(NULL));

	des_cbc_encrypt(
			(des_cblock *)src1,(des_cblock *)dest1,
			(long)l, ks, (des_cblock *)iv, DES_ENCRYPT);
	
	dest = (char *)malloc(l*2+1);
	if(dest == NULL){
		free(src1);
		free(dest1);
		return NULL;
	}
	BcdToAsc(dest1, dest, l);
	free(src1);
	free(dest1);
	*outlen = l*2;
	
	return dest;
}


/*
 * 解密
 */
char * pubDecrypt(const char *src, int inlen, int *outlen, char *key)
{
	register int i;
	des_key_schedule ks;
	unsigned char iv[8];
	int l,rem;
	des_cblock kk;
	unsigned char *src1;
	unsigned char *dest;

	des_string_to_key(key,(C_Block *)kk);
	des_set_key((C_Block *)kk,ks);
	memset(iv,0,sizeof(iv));

	if(inlen % 16 > 0)
		return NULL; //长度不对
	l=inlen;
	src1 = (char *)malloc(l/2);
	if(src1 == NULL) return NULL;
	AscToBcd(src, src1, l);

	l = l/2;
	dest = (char *)malloc(l+1);
	if(dest == NULL){ free(src1); return NULL; }
	dest[l] = 0;
	des_cbc_encrypt(
		(des_cblock *)src1,(des_cblock *)dest,
		(long)l,ks,(des_cblock *)iv, DES_DECRYPT);
	*outlen = l;
	return dest;
}