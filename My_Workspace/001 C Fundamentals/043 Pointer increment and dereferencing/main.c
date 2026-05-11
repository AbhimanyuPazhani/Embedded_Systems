/*
 * main.c
 *
 *  Created on: May 11, 2026
 *      Author: CITI
 */

// Online C compiler to run C program online
#include <stdio.h>
void wait_for_input(void);
int main() {
    int arr[] = {2,3,4,5,6,7};
    int *ptr;
    ptr = arr;
    printf("Size of array arr is: %d", sizeof(arr));
    int count = sizeof(arr)/sizeof(arr[0]);
    printf("\nSize of first element of arr is: %d", count);
    for (int i =0; i<count; i++)
    {
        printf("\n %d", *ptr);
        ptr++;
    }
    wait_for_input();
}

void wait_for_input()
{
    printf("\n Press ENTER for EXIT");
    while( getchar()!='\n');
    getchar();
}

//Output:
//Size of array arr is: 24
//Size of first element of arr is: 6
// 2
// 3
// 4
// 5
// 6
// 7
// Press ENTER for EXIT
