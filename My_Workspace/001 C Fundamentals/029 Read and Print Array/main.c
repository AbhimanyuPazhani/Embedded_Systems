/*
 * main.c
 *
 *  Created on: Apr 2, 2026
 *      Author: CITI
 */

#include <stdio.h>
#include <stdint.h>
void wait_for_input(void);
int main()
{
    int N, i;
    printf("Enter the size of the array:\n");
    scanf("%d", &N);

    int arr[N];
     printf("Enter the array elements %d\n", N);
    for(i=0; i<N; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("The array elements are:\n");
    for (i=0; i<N; i++)
    {
        printf("%d\n", arr[i]);
    }
    wait_for_input();

}

void wait_for_input()
{
	printf("\nPress Enter for EXIT");
	while (getchar() != '\n');
	getchar();
}
