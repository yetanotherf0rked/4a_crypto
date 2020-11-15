#include <stdio.h>
#include "des.c"

int main()
{
	unsigned char source[] = "azerty",
	     dest[256],
	     dest2[256];

	des_encipher(source,dest, (unsigned char*)"chabada");
	puts((char*)dest);
	des_decipher(dest, dest2, (unsigned char*)"chabada");
	puts((char*)dest2);
	exit(0);
}


