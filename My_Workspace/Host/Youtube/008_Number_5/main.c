/*
 * main.c
 *
 *  Created on: 18-Jan-2026
 *      Author: CITI
 */


#include <stdio.h>

int main (void)
{
	int i,j,num,rows;

	num =1;
	printf("Enter the rows:");
	scanf("%d", &rows);

	for (i=1; i<=rows; i++)
	{
		for (j=1; j<=i; j++)
		{
			printf(" %d", num);
			num++;
		}
		printf("\n");
	}
	getchar();
	getchar();
}


//output
//Enter the rows:8
// 1
// 2 3
// 4 5 6
// 7 8 9 10
// 11 12 13 14 15
// 16 17 18 19 20 21
// 22 23 24 25 26 27 28
// 29 30 31 32 33 34 35 36
