/*
 * main.c
 *
 *  Created on: Sep 18, 2025
 *      Author: ADMIN
 */

#include <stdio.h>
#include <stdint.h>

long long int g_data = 0xFFFEABCD11112345;

int main (void)
{

	char* pAddress1;
//har *pAddress1;   //Both the above and this one is same dont confuse with this...

	pAddress1 =(char*)&g_data;

	printf("The value of the pointer %p is : %x\n", pAddress1, *pAddress1); //1 byte of data just 45 is printing at the end due to char data type

	int* pAddress2;
	pAddress2 = (int*) &g_data;
	printf("The value of the pointer %p is : %x\n", pAddress2, *pAddress2); //4 bye is printing at the console because of int data type 11112345


 return 0;

}
