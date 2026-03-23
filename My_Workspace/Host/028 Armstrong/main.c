/*
 * main.c
 *
 *  Created on: Mar 23, 2026
 *      Author: CITI
 */


#include <stdio.h>

int main() {
    int num = 153, original, remainder, result = 0;
    int n = 0, temp, i, power;

    original = num;
    temp = num;

    // Count number of digits
    while (temp != 0) {
        temp /= 10;
        n++;
    }

    temp = num;

    // Calculate Armstrong sum
    while (temp != 0) {
        remainder = temp % 10;

        power = 1;
        for (i = 0; i < n; i++) {
            power *= remainder;
        }

        result += power;
        temp /= 10;

        getchar();
    }

    // Check result
    if (result == original)
        printf("Armstrong number");
    else
        printf("Not an Armstrong number");

   getchar();
   getchar();
}


//Output
//153
//Armstrong number
