/*
 * main.c
 *
 *  Created on: Feb 6, 2026
 *      Author: CITI
 */


#include<stdio.h>

int main (void)
{
	int a,r;
	printf("Enter the 4 digit number:");

	scanf("%d", &a);

	if (a<1000 || a>9999)
	{
		printf("It's not a 4 digit number");

	}
	else
	{
	r= ((a%10)*1000)  +  (((a/100)%10)*100)   + (a/100)*10 + (a/1000);
	    printf("%d", r);
	}

	getchar();
	getchar();
	}

//Output
//Enter the 4 digit number:1234
//4321
