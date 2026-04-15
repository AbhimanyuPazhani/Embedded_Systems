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
	int i,N, even_count =0, odd_count=0;
	printf("Enter the length of an array: ");
	scanf("%d", &N);

	int arr[N];
	for(i=0;i<N; i++)
	{
		printf("Enter the %d element: ",i);
		scanf("%d", &arr[i]);

	}

	for(i=0;i<N;i++)
	{
		if(arr[i]%2 == 0)
		{
			even_count++;
		}
		else
			odd_count++;
	}
	printf("The Even count is %d and Odd count is %d", even_count, odd_count);

	wait_for_input();
}


void wait_for_input()
{
	printf("\nPress Enter for EXIT");
	while(getchar()!= '\n');
	getchar();
}


//Enter the length of an array: 4
//Enter the 0 element: 3
//Enter the 1 element: 8
//Enter the 2 element: 9
//Enter the 3 element: 3
//The Even count is 1 and Odd count is 3
//Press Enter for EXIT
