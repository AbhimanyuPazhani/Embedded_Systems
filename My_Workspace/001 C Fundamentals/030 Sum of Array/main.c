/*
 * main.c
 *
 *  Created on: Apr 2, 2026
 *      Author: CITI
 */
#include<stdio.h>

void wait_for_input(void);
int main()
{
	int i,N, sum =0;
	printf("Enter the length of the Array:");
	scanf("%d", &N);

	int arr[N];
	for (i=0;i<N;i++)
	{
		scanf("%d", &arr[i]);

	}

	for (i=0;i<N;i++)
	{
		sum += arr[i];
	}
	printf("The sum of the array is: %d", sum);
	wait_for_input();
}

void wait_for_input()
{
	printf("\nPress Enter for EXIT");

	while (getchar() != '\n');
	getchar();
}


//Enter the length of the Array:4
//1
//2
//3
//4
//The sum of the array is: 10
//Press Enter for EXIT
