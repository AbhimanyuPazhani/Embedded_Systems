/*
 * main.c
 *
 *  Created on: May 31, 2026
 *      Author: CITI
 */

#include<stdio.h>

int countsetbits(unsigned int num)
{
	int count =0;

	while(num)
	{
		count+=(num&1);
		num >>= 1;
	}

	return count;
}
void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}

int main()
{
	unsigned int num;
	printf("Enter the number:");
	scanf("%d", &num);

	printf("\nSet bits = %d", countsetbits(num));
	wait_for_input ();
}
