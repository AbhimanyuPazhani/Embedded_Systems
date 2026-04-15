/*
 * main.c
 *
 *  Created on: Mar 4, 2026
 *      Author: CITI
 */


#include <stdio.h>

int main() {
    int N;

    printf("Enter a positive integer: ");
    scanf("%d", &N);

    printf("Even numbers between 1 and %d are:\n", N);

    for(int i = 1; i <= N; i++) {
        if(i % 2 == 0) {
            printf("%d ", i);
        }
    }


    getchar();
    getchar();
}


//OUTPUT:
//Enter a positive integer: 12
//Even numbers between 1 and 12 are:
//2 4 6 8 10 12
