/*
 * main.c
 *
 *  Created on: Feb 6, 2026
 *      Author: CITI
 */

#include <stdio.h>

int main()
{
	int a;
	printf("Enter any integer value:");

	scanf("%d", &a);

	if (a<0)
	{
		printf("\nIt is Negative number");
	}
	else if (a>0)
	{
		printf("\n It is Positive number");
	}

	else
	{
		printf("\nIt is Zero");
	}

	getchar();
	getchar();
}

//Output:
//Enter any integer value:2
//
// It is Positive number
