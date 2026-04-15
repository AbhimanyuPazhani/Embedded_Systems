/*
 * main.c
 *
 *  Created on: 20-Jan-2026
 *      Author: CITI
 */


#include<stdio.h>


int main(void)
{
	int i,j,space,rows;

	printf("Enter the Number of rows:");
	scanf("%d", &rows);

	for (i=rows; i>=1; i--)
	{

		for(space =1; space<=(rows-i); space++)
		{
			printf(" ");

		}

		for(j=1; j<=(2*i-1); j++)
		{
			printf("*");
		}
		printf("\n");
	}
	getchar();
	getchar();
}


//output
//Enter the Number of rows:8
//***************
// *************
//  ***********
//   *********
//    *******
//     *****
//      ***
//       *
