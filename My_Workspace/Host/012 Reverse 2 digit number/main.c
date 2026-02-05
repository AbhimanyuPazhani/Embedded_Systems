/*
 * main.c
 *
 *  Created on: Feb 4, 2026
 *      Author: CITI
 */

#include<stdio.h>

int main(void)
{
	int a;
	printf("Enter any 2 digit values: ");
	scanf("%d", &a);

	//Logic
	a=(((a%10)*10)+(a/10));
	printf("The value after reversing: %d ", a);

	getchar();
	getchar();
}
