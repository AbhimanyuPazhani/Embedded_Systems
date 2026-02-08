/*
 * main.c
 *
 *  Created on: Feb 8, 2026
 *      Author: CITI
 */


#include <stdio.h>


void wait_for_input (void);
int main() {
    int num;

    printf("Enter an integer: ");
    scanf("%d", &num);

    if (num % 5 == 0 && num % 11 == 0) {
        printf("The number is divisible by both 5 and 11");
    } else {
        printf("The number is not divisible by both 5 and 11");
    }

    wait_for_input ();


}
void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}
