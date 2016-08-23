#pragma once

namespace NSPrime
{
/*
 This is the header file for code which implements the Secure
 Hashing Algorithm 1 as defined in FIPS PUB 180-1 published
 April 17, 1995.

 Many of the variable names in this code, especially the
 single character names, were used because those were the names
 used in the publication.

 Please read the file sha1.c for more information.

 Modified 2002 by Peter Zaitsev to better follow MySQL standards
*/


enum sha_result_codes
{
  SHA_SUCCESS = 0,
  SHA_NULL,		/* Null pointer parameter */
  SHA_INPUT_TOO_LONG,	/* input data too long */
  SHA_STATE_ERROR	/* called Input after Result */
};

#define SHA1_HASH_SIZE 20 /* Hash size in bytes */

/*
  This structure will hold context information for the SHA-1
  hashing operation
*/

typedef struct SHA1_CONTEXT
{
  ulonglong  Length;		/* Message length in bits      */
  ub4 Intermediate_Hash[SHA1_HASH_SIZE/4]; /* Message Digest  */
  int Computed;			/* Is the digest computed?	   */
  int Corrupted;		/* Is the message digest corrupted? */
  sb2 Message_Block_Index;	/* Index into message block array   */
  ub1 Message_Block[64];	/* 512-bit message blocks      */
} SHA1_CONTEXT;

/*
  Function Prototypes
*/

int sha1_reset( SHA1_CONTEXT* );
int sha1_input( SHA1_CONTEXT*, const ub1 *, unsigned int );
int sha1_result( SHA1_CONTEXT* , ub1 Message_Digest[SHA1_HASH_SIZE] );
}
