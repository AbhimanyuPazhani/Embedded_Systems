/*
 * main.c
 *
 *  Created on: 09-Jan-2026
 *      Author: CITI
 */


#include <stdio.h>

int main()
{
	int i, j, n;
	printf("Enter the number:");
	scanf("%d", &n);

	for (i=1; i<=n; i++)
	{
		for (j=n;j>=i; j--)
		{
			printf("*");

		}
		printf("\n");
	}
	getchar();
	getchar();

}
