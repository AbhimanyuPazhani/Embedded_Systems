/*
 * main.c
 *
 *  Created on: Sep 19, 2025
 *      Author: ADMIN
 *
 *
 */

//#include <stdio.h>
//
//int main(void) {
//    int num;
//    printf("Enter a number: ");
//    scanf("%d", &num);
//    printf("You typed: %d\n", num);
//    return 0;
//}

#include<stdio.h>
#include<stdint.h>

#include "wait.h"


int main (void)

{
	int income, tax;
	printf("Enter the Annual income of the employee:");
	scanf("%d",&income);

	if (income <= 9525)
	{
		printf("\nTax percentage is 0");
		tax = income;
		printf("\nIncome = %d", income);
	}
	else if ( income > 9525 && income <= 38700)
	{
		printf("\n Tax percentage is 12");
		tax = income * 0.12;
		printf("\n Tax is %d", tax);
	}
	else if (income > 38700 && income <=82500)
	{
		printf("\n Tax percentage is 22");
		tax = income * 0.22;
		printf("\n Tax is %d", tax);
	}
	else
	{
		printf("\n Tax percentage is 32 + 1000");
		tax = (income * 0.32)+1000;
		printf("\n Tax is %d", tax);
	}
//	return 0;
	wait_for_input();

//	while (getchar() != '\n')
//	{
//
//	}
//	getchar ();
}

