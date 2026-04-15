/*
 * main.c
 *
 *  Created on: Nov 13, 2025
 *      Author: ADMIN
 */


#include <stdio.h>

void wait_for_input(void);

int main()
{
	float celsius, fahrenheit;
	printf("Enter the Celsius:");
	fflush(stdout);
	scanf("%f", &celsius);

	//formula for fahrenheit
	// fahrenheit = (celsius * 9/5) + 32;

	fahrenheit = (celsius * 9/5) + 32;
	printf("Fahrenheit = %.1f", fahrenheit);

	 wait_for_input();

	  return 0;
}
	void wait_for_input(void)
	{
		printf("\nPress Enter to EXIT");
		while (getchar() != '\n');
		getchar();
	}
