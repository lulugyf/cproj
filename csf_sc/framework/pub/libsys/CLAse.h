#pragma once


namespace NSPrime
{
	/*
	rijndael-alg-fst.h
	@version 3.0 (December 2000)
	Optimised ANSI C code for the Rijndael cipher (now AES)
	@author Vincent Rijmen <vincent.rijmen@esat.kuleuven.ac.be>
	@author Antoon Bosselaers <antoon.bosselaers@esat.kuleuven.ac.be>
	@author Paulo Barreto <paulo.barreto@terra.com.br>

	This code is hereby placed in the public domain.
	Modified by Peter Zaitsev to fit MySQL coding style.
	*/
#define AES_MAXKC	(256/32)
#define AES_MAXKB	(256/8)
#define AES_MAXNR	14

	int rijndaelKeySetupEnc(ub4 rk[/*4*(Nr + 1)*/], const ub1 cipherKey[],
		int keyBits);
	int rijndaelKeySetupDec(ub4 rk[/*4*(Nr + 1)*/], const ub1 cipherKey[],
		int keyBits);
	void rijndaelEncrypt(const ub4 rk[/*4*(Nr + 1)*/], int Nr,
		const ub1 pt[16], ub1 ct[16]);
	void rijndaelDecrypt(const ub4 rk[/*4*(Nr + 1)*/], int Nr,
		const ub1 ct[16], ub1 pt[16]);



	/****************************************************************************/

#define AES_KEY_LENGTH 128		/* Must be 128 192 or 256 */

	/*
	my_aes_encrypt	- Crypt buffer with AES encryption algorithm.
	source		- Pointer to data for encryption
	source_length		- size of encryption data
	dest			- buffer to place encrypted data (must be large enough)
	key			- Key to be used for encryption
	kel_length		- Length of the key. Will handle keys of any length

	returns  - size of encrypted data, or negative in case of error.
	*/

	int my_aes_encrypt(const char *source, int source_length, char *dest,
		const char *key, int key_length);

	/*
	my_aes_decrypt	- DeCrypt buffer with AES encryption algorithm.
	source		- Pointer to data for decryption
	source_length		- size of encrypted data
	dest			- buffer to place decrypted data (must be large enough)
	key			- Key to be used for decryption
	kel_length		- Length of the key. Will handle keys of any length

	returns  - size of original data, or negative in case of error.
	*/


	int my_aes_decrypt(const char *source, int source_length, char *dest,
		const char *key, int key_length);

	/*
	my_aes_get_size - get size of buffer which will be large enough for encrypted
	data
	source_length   -  length of data to be encrypted

	returns  - size of buffer required to store encrypted data
	*/

	int my_aes_get_size(int source_length);
}
