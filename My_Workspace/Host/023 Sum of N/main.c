/*
 * main.c
 *
 *  Created on: Feb 12, 2026
 *      Author: CITI
 */

#include <stdio.h>
void wait_for_input(void);

int main() {
    int N, i;
    int sum = 0;

    printf("Enter a positive integer: ");
    scanf("%d", &N);

    // Check if the number is positive
    if (N < 1) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    // Loop to calculate sum from 1 to N
    for (i = 1; i <= N; i++) {
        sum += i;
    }

    printf("Sum of natural numbers from 1 to %d is: %d\n", N, sum);

    wait_for_input();
}

void wait_for_input(void)
{
	printf("\nPress ENTER to EXIT");
	while (getchar ()!= '\n');

	getchar();


}


//Enter a positive integer: 7
//Sum of natural numbers from 1 to 7 is: 28
//
//Press ENTER to EXIT

