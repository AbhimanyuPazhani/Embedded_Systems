/*
 * main.c
 *
 *  Created on: Sep 16, 2025
 *      Author: ADMIN
 */

#include <stdio.h>

int main (void)
{
	char c1,c2,c3,c4,c5,c6;
	printf("Enter the 6 character:");
	scanf ("%c %c %c %c %c %c",&c1,&c2,&c3,&c4,&c5,&c6 );

	printf("\n ASCII codes: %u.%u,%u,%u,%u,%u", c1,c2,c3,c4,c5,c6);
	printf("\nPress any key to exit the window");
	while (getchar ()!= '\n')
	{
			//just read the input
	}
	getchar();
}
