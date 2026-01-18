/*
 * main.c
 *
 *  Created on: 17-Jan-2026
 *      Author: CITI
 */


#include<stdio.h>



int main (void)
{
	int i,j,rows;
	printf("Enter the number of rows:");
	scanf("%d", &rows);

	for (i=1; i<=rows; i++)
	{
		for (j=1; j<=i; j++)
		{
			printf("%d", i);
		}
		printf("\n");
	}

	getchar();
	getchar();
}


//Output
//Enter the number of rows:8
//1
//22
//333
//4444
//55555
//666666
//7777777
//88888888
