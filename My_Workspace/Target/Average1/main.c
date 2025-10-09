/*
 * main.c
 *
 *  Created on: Sep 13, 2025
 *      Author: ADMIN
 */

// Problems may occur in the Ecllipse console: When you run this program the console does not print anything instead it shows blank, due to BUFFER
#include <stdio.h>
int main (void)
{
	float num1, num2, num3;
	float average;
	printf("Enter the first number:");
	fflush(stdout);
		scanf("%f", &num1);
	printf("\nEnter the first number:");
	fflush(stdout);
		scanf("%f", &num2);
	printf("\nEnter the first number:");
	fflush(stdout);
		scanf("%f", &num3);

	average = (num1 + num2 + num3)/3;
	printf("\nThe average of the numbers is %f", average);
	while (getchar ()!='\n')
	{

	}
getchar ();
}


