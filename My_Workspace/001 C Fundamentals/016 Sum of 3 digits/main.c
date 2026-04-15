/*
 * main.c
 *
 *  Created on: Feb 6, 2026
 *      Author: CITI
 */


#include <stdio.h>

int main()
{
	int a,b,c,d,e, x;
	printf("Enter the 3 digit number:");
	scanf("%d", &a);

	b= a%100;
	d= b/10;
	e= b%10;
	c=a/100;

	x=c+d+e;
	printf("\nThe sum of three digits: %d", x);

	getchar();
	getchar();


}


//
//Output:
//Enter the 3 digit number:123
//
//The sum of three digits: 6
