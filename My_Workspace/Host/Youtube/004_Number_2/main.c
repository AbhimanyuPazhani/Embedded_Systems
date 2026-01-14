/*
 * main.c
 *
 *  Created on: 14-Jan-2026
 *      Author: CITI
 */


#include<stdio.h>

int main()
{
	int i,j,rows;
	printf("Enter the rows:");
	scanf("%d", &rows);

	for (i = rows; i>=1; i--)
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
