/*
 * main.c
 *
 *  Created on: Apr 7, 2026
 *      Author: CITI
 */


#include <stdio.h>


void wait_for_input (void);
int main()
{
	int i,temp, N;
	printf("Enter the Length of an Array:");
	scanf("%d", &N);

	int arr[N];
	for (i=0; i<N; i++)
	{
		printf("Enter the %d element: ", i);
		scanf("%d", &arr[i]);
	}

	printf("Before Reversing\n");
	for (i=0; i<N; i++)
	{
		printf("%d\n", arr[i]);
	}
	for(i=0; i<N/2; i++)
	{
		temp = arr[i];
		arr[i] = arr[N-i-1];
		arr[N-i-1] = temp;

	}
	printf("\nAfter Reversing\n");
		for (i=0; i<N; i++)
		{
			printf("%d\n", arr[i]);
		}
		wait_for_input();
}

void wait_for_input ()
{
	printf("Press Enter for EXIT");
	while ( getchar() != '\n');
	getchar();
}

//Enter the Length of an Array:4
//Enter the 0 element: 1
//Enter the 1 element: 3
//Enter the 2 element: 5
//Enter the 3 element: 7
//Before Reversing
//1
//3
//5
//7
//
//After Reversing
//7
//5
//3
//1
//Press Enter for EXIT
