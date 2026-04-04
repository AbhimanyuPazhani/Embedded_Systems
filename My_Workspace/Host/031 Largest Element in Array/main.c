/*
 * main.c
 *
 *  Created on: Apr 3, 2026
 *      Author: CITI
 */


#include<stdio.h>


void wait_for_input(void);

int main()
{
	int i,max,N;
	printf("Enter the Number of elements in an Array: ");
	scanf("%d", &N);

	int arr[N];

	for(i=0;i<N;i++)
	{
		printf("Enter the %d element: ", i);
		scanf("%d", &arr[i]);

	}

	max = arr[0];
	for(i=1; i<N;i++)
	{
		if(arr[i]>max)
		{
			max = arr[i];
		}
	}
	printf("The largest element in the array is : %d", max);


	 wait_for_input();
}

void wait_for_input()
{
	printf("\nPress Enter for EXIT");
	while (getchar() != '\n');
	getchar();
}

//Enter the Number of elements in an Array: 4
//Enter the 0 element: 1
//Enter the 1 element: 2
//Enter the 2 element: 3
//Enter the 3 element: 8
//The largest element in the array is : 8
//Press Enter for EXIT
