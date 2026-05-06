/*
 * main.c
 *
 *  Created on: May 5, 2026
 *      Author: CITI
 */


#include <stdio.h>
void wait_for_input(void);

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

    wait_for_input();
}

void wait_for_input()
{
	printf("\n\nPress Enter for EXIT");
	while (getchar()!='\n');
	getchar();
}




//OUTPUT:
//4
//4
//5
//6
//7
//22
//
//
//Press Enter for EXIT
