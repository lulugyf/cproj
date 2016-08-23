#include "csf_util_CSFDes.h"

#include <stdio.h>
#include <stdlib.h>

extern "C" {
	char * pubEncrypt(const char *src, const int inlen, int *outlen, char *key);
	char * pubDecrypt(const char *src, const int inlen, int *outlen, char *key);
}

JNIEXPORT jbyteArray JNICALL Java_csf_util_CSFDes_encrypt
  (JNIEnv *env, jclass obj, jbyteArray src, jbyteArray key)
{
	int inlen = (int)env->GetArrayLength(src);
	char * src1 = (char *)env->GetByteArrayElements(src, 0);
	char *key1 = (char *)env->GetByteArrayElements(key, 0);
	int keylen = (int)env->GetArrayLength(key);
	
	src1[ inlen ] = 0;
	key1[ keylen ] = 0;
	//printf("in===[%s] key[%s]\n", src1, key1);
	
	int outlen;
	char *out = pubEncrypt(src1, inlen, &outlen, key1);
	if(out == NULL)
		return NULL;
		
	jbyteArray bArray = env->NewByteArray( outlen );
	env->SetByteArrayRegion(bArray, 0, outlen, (jbyte *)out);
	free(out);
	return bArray;
}

/*
 * Class:     csf_util_CSFDes
 * Method:    decrypt
 * Signature: ([B[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_csf_util_CSFDes_decrypt
  (JNIEnv *env, jclass obj, jbyteArray src, jbyteArray key)
{
	int inlen = (int)env->GetArrayLength(src);
	char * src1 = (char *)env->GetByteArrayElements(src, 0);
	char *key1 = (char *)env->GetByteArrayElements(key, 0);
	int keylen = (int)env->GetArrayLength(key);
	
	src1[ inlen ] = 0;
	key1[ keylen ] = 0;
	//printf("in===[%s] key[%s]\n", src1, key1);
	
	int outlen;
	char *out = pubDecrypt(src1, inlen, &outlen, key1);
	if(out == NULL)
		return NULL;
		
	jbyteArray bArray = env->NewByteArray( outlen );
	env->SetByteArrayRegion(bArray, 0, outlen, (jbyte *)out);
	//printf("===[%s]\n", out);
	free(out);
	return bArray;	  
}
