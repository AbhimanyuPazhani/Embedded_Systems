/*
 * main.c
 *
 *  Created on: 04-Jan-2026
 *      Author: CITI
 */


#include<stdio.h>
#include <stdint.h>

int main()
{
	int i,j, num;
	printf("Enter the number: ");
	scanf("%d", &num);
	for (i=0; i<num; i++)
	{
			for (j=0; j<=i;j++)
		{
			printf("*");


		}
			printf("\n");
	}
	getchar();
			getchar();
}
