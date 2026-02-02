/*
 * main.c
 *
 *  Created on: Jan 31, 2026
 *      Author: CITI
 */

#include <stdio.h>

int main()
{
	int x,y;
	printf("Enter the 2 digit number:");
	scanf("%d",&x);

	y=x/10;
	printf("The tens position number is: %d", y);
	getchar();
	getchar();
}
