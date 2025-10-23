/*
 * main.c
 *
 *  Created on: Oct 16, 2025
 *      Author: ADMIN
 */


#include<stdio.h>
#include<stdint.h>

union address
{
	uint16_t shortAddr;
	uint32_t longAddr;
};

int main(void)
{
	union address Addr;
	Addr.shortAddr = 0xABCD;

	printf("Short address  : %#X\n", Addr.shortAddr);
	Addr.longAddr = 0xEEEECCCC;


	printf("Long address  : %#X\n", Addr.longAddr);

	getchar();
	getchar();
	return 0;
}
