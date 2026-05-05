/*
 * main.c
 *
 *  Created on: May 5, 2026
 *      Author: CITI
 */


#include <stdio.h>

int main() {
    int n, sum = 0;

    // Input number of elements
    scanf("%d", &n);

    int arr[n];
    int *ptr = arr;

    // Input elements
    for(int i = 0; i < n; i++) {
        scanf("%d", ptr + i);   // using pointer arithmetic
    }

    // Calculate sum using pointer
    for(int i = 0; i < n; i++) {
        sum += *(ptr + i);      // dereferencing pointer
    }

    // Output result
    printf("%d\n", sum);

    return 0;
}
