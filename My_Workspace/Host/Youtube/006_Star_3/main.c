/*
 * main.c
 *
 *  Created on: 16-Jan-2026
 *      Author: CITI
 */


#include<stdio.h>


int main(void)
{
	int i,j,rows;
	printf("Enter the number of rows:");
	scanf("%d", &rows);

	for (i=1; i<=rows; i++)
	{
		for (j=1; j<=rows; j++)
		{
			if(i+j<=rows)
			{
				printf(" ");
			}
			else{printf("*");}
		}
		printf("\n");
	}

	getchar();
	getchar();

}



//output:
//Enter the number of rows:8
//       *
//      **
//     ***
//    ****
//   *****
//  ******
// *******
//********
