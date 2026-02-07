/*
 * main.c
 *
 *  Created on: Feb 6, 2026
 *      Author: CITI
 */


#include <stdio.h>

int main()
{
	int a,b,c,d;

	printf("Enter the 2 digit number:");
	scanf("%d", &a);
	b = a%10;
	c = a/10;
	d = b+c;
	printf("\nThe sum of two digits: %d", d);

	getchar();
	getchar();
}



//Output:
//Enter the 2 digit number:78
//
//The sum of two digits: 15
