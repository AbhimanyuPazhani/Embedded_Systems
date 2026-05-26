/*
 * main.c
 *
 *  Created on: May 26, 2026
 *      Author: CITI
 */


#include <stdio.h>


void wait_for_input (void);
int main() {
    int num;

    // Input
    printf("Enter an integer: ");
    scanf("%d", &num);

    // Check even or odd using bitwise AND
    if (num & 1)
        printf("%d is Odd.\n", num);
    else
        printf("%d is Even.\n", num);
    wait_for_input();
    return 0;
}

void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}
