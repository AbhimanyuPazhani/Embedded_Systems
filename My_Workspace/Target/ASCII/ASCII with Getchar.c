/*
 * ASCII with Getchar.c
 *
 *  Created on: Sep 16, 2025
 *      Author: ADMIN
 */

#include <stdio.h>

int main(void)
{
	char c1,c2,c3,c4,c5,c6;
	printf("Enter the characters:\n");

	c1 = getchar();
	getchar();

	c2 = getchar();
	getchar();

	c3 = getchar();
	getchar();

	c4 = getchar();
	getchar();

	c5 = getchar();
	getchar();

	c6 = getchar();
	getchar();

	printf("The Equivalent ASCIIs are %u %u %u %u %u %u", c1,c2,c3,c4,c5,c6);

	while (getchar() != '\n')
	{
		//Just read the buffer nothing
	}
	getchar();



}
