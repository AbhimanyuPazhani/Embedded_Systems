/*
 * main.c
 *
 *  Created on: May 15, 2026
 *      Author: CITI
 */

#include<stdio.h>

void wait_for_input(void);
int main()
{
	unsigned int x=1;
	char *ptr = (char*)&x;

	if (*ptr ==1)
	{
		printf("System is Little Endian\n");
	}
	else
		printf("System is Big Endian\n");
	wait_for_input();
}


void wait_for_input()
{
	printf("\nPress Enter for EXIT");

	while(getchar()!='\n');
	getchar();
}
