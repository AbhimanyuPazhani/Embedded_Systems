/*
 * main.c
 *
 *  Created on: Jun 3, 2026
 *      Author: CITI
 */

#include <stdio.h>

void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}

// Comparison function for ascending order
int ascending(int a, int b)
{
    return a > b;
}

// Comparison function for descending order
int descending(int a, int b)
{
    return a < b;
}

// Generic Bubble Sort using function pointer
void bubbleSort(int arr[], int n, int (*compare)(int, int))
{
    int i, j, temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(compare(arr[j], arr[j + 1]))
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void display(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {5, 2, 9, 1, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Ascending order
    bubbleSort(arr, n, ascending);
    printf("Ascending: ");
    display(arr, n);

    // Descending order
    bubbleSort(arr, n, descending);
    printf("Descending: ");
    display(arr, n);

    wait_for_input ();
}

//
//OUTPUT:
//Ascending: 1 2 5 7 9
//Descending: 9 7 5 2 1
//
//Press enter to EXIT
