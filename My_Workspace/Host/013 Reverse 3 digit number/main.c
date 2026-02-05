/*
 * main.c
 *
 *  Created on: Feb 5, 2026
 *      Author: CITI
 */


#include<stdio.h>

int main (void)
{
	int a,r;
	printf("Enter the 3 digit number:");

	scanf("%d", &a);

	if (a<100 || a>999)
	{
		printf("It's not a 3 digit number");

	}
	else
	{
	r= ((a%10)*100)  +  (((a/10)%10)*10)   + (a/100);
	    printf("%d", r);
	}

	getchar();
	getchar();
	}


//Output
//Enter the 3 digit number:345
//543
