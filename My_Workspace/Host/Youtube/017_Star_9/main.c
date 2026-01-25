/*
 * main.c
 *
 *  Created on: Jan 25, 2026
 *      Author: CITI
 */


#include<stdio.h>

int main()
{
	int i,j,rows;
	printf("Enter the number of rows:");
	scanf("%d",&rows);

	for (i=1; i<=rows; i++)
	{
		for (j=1; j<=rows; j++)
		{
			if(i==1 ||i==rows || j==1 || j==rows)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}

		}
		printf("\n");
	}
	getchar();
	getchar();
}



//Output:
//Enter the number of rows:6
//******
//*    *
//*    *
//*    *
//*    *
//******
