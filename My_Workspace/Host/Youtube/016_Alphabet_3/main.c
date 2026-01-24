/*
 * main.c
 *
 *  Created on: Jan 24, 2026
 *      Author: CITI
 */


#include<stdio.h>

int main()
{
	int i,j,rows;

	printf("Enter the number of rows:");
	scanf("%d", &rows);

	for (i=1; i<=rows; i++)
	{
		for (j=1; j<=i; j++)
		{
			printf("%c", 64+i);
		}
		printf("\n");
	}

	getchar();
	getchar();

}



//Output:
//
//Enter the number of rows:6
//A
//BB
//CCC
//DDDD
//EEEEE
//FFFFFF
