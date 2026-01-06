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
	int number;
	printf("Enter the Number:");
	fflush(stdout);
	scanf("%d", &number);

	if (number %2 == 0)
	{
		printf("Even");

	}
	else {
		printf("Odd");
	}
	wait_for_input();
}

void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}
