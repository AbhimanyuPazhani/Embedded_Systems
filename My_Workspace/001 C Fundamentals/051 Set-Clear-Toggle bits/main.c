/*
 * main.c
 *
 *  Created on: May 28, 2026
 *      Author: CITI
 */


#include <stdio.h>

 void wait_for_input (void);
int main() {
    int num, pos;

    // Input number and bit position
    printf("Enter an integer: ");
    scanf("%d", &num);

    printf("Enter bit position (0-based): ");
    scanf("%d", &pos);

    // Set the bit
    int setResult = num | (1 << pos);

    // Clear the bit
    int clearResult = num & ~(1 << pos);

    // Toggle the bit
    int toggleResult = num ^ (1 << pos);

    // Output results
    printf("\nOriginal Number : %d\n", num);
    printf("After Setting Bit   : %d\n", setResult);
    printf("After Clearing Bit  : %d\n", clearResult);
    printf("After Toggling Bit  : %d\n", toggleResult);

    wait_for_input();
     return 0;
 }

 void wait_for_input (void)
 {
 	printf("\nPress enter to EXIT");
 	while (getchar()!= '\n');
 	getchar();
 }

