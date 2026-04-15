/*
 * main.c
 *
 *  Created on: Oct 3, 2025
 *      Author: ADMIN
 */

#include <stdio.h>
#include <stdint.h>

void wait_for_input(void)
{
    printf("\nPress Enter to exit...");
    while (getchar() != '\n');  // clear input buffer
    getchar();                  // wait for Enter
}

int main (void)
{

	int32_t start_num, end_num, even;
	printf("Enter the starting and ending numbers (Give space between 2 No's):");

	scanf("%d %d", &start_num, &end_num);
	even =0;
	while (start_num <= end_num)
	{
		if (!(start_num % 2)){
			printf("%4d\t", start_num);
			even++;
		}
		start_num ++;
	} //end of while loop
	printf("\n Total even numbers: %d\n", even);


	wait_for_input();
}
