/*
 * main.c
 *
 *  Created on: Nov 11, 2025
 *      Author: ADMIN
 */
#include <stdio.h>


void wait_for_input (void);
int main()
{
	int num1, num2, num3;
	printf("Enter the num1, num2, num3 values:");
	fflush(stdout);
	scanf("%d %d %d",&num1, &num2, &num3);
	float average;
	average = ((num1)+ (num2)+ (num3))/3.0;
	printf("The average of num1, num2, num3 is : %.2f", average);
	wait_for_input();
	return 0;

}

void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}
