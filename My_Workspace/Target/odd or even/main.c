/*
 * main.c
 *
 *  Created on: Sep 19, 2025
 *      Author: ADMIN
 */


#include<stdio.h>
#include<stdint.h>
void wait_for_input(void)
{
    printf("\nPress Enter to exit...");
    while (getchar() != '\n');  // clear input buffer
    getchar();                  // wait for Enter
}

int main (void)
{
	uint32_t number;
	printf("Enter the number:");
	scanf("%d", &number);

	if (number & 1)
	{
		printf("\nThe number is odd");

	}
	else
	{
		printf("\n The number is even");
	}
	wait_for_input();
}
