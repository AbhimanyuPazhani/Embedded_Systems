/*
 * main.c
 *
 *  Created on: Feb 9, 2026
 *      Author: CITI
 */


#include <stdio.h>

void wait_for_input (void);

int main()
{
	int year;
	printf("Enter the year:");
	scanf("%d", &year);

	if(( year %4 ==0 && year %100 !=0) || (year % 400 == 0))
		{
		printf("It is a leap year");
		}

	 else {
	        printf("%d is not a leap year.\n", year);
	    }

	wait_for_input ();


}

void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}
