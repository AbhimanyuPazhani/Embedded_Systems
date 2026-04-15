/*
 * main.c
 *
 *  Created on: 12-Jan-2026
 *      Author: CITI
 */


#include <stdio.h>

int main()
{
	int i, j, rows;
	printf("Enter the number of rows:");
	scanf("%d", &rows);
	for (i=1; i<=rows; i++)
	{
		for (j=1; j<=i; j++)
		{
			printf("%d", j);
		}
		printf("\n");
	}
	getchar();
	getchar();
}
