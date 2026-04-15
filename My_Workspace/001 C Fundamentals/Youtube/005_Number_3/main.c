/*
 * main.c
 *
 *  Created on: 15-Jan-2026
 *      Author: CITI
 */


#include<stdio.h>




int main()
{
	int i, j, rows;
	printf("Enter the rows:");
	scanf("%d", &rows);

	for(i=1; i<=rows; i++)
	{
		for (j=rows; j>=i; j--)
		{
			printf("%d", j);
		}
		printf("\n");
	}
	getchar();
	getchar();


}


//output
//Enter the rows:7
//7654321
//765432
//76543
//7654
//765
//76
//7
