/*
 * main.c
 *
 *  Created on: Nov 12, 2025
 *      Author: ADMIN
 */

#include <stdio.h>

void wait_for_input (void);

int main()
{
	int number, factorial = 1;
	printf("Enter the Number:");
	fflush(stdout);
	scanf("%d", &number);

	for (; number >0; number --)
	{
		factorial *= number;
	}

	printf("Factorial = %d", factorial);
	wait_for_input();
}

void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}
