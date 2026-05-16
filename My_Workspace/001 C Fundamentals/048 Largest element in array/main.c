/*
 * main.c
 *
 *  Created on: May 16, 2026
 *      Author: CITI
 */


#include<stdio.h>


int function (int arr[], int num);
void wait_for_input(void);

int main()
{
	int arr[100], i,num,largest;

	printf("Enter the number of elements in an array\n");
	scanf("%d", &num);
	printf("Enter the number of component in an array\n");
	for(i=0; i<num;i++)
	{
		scanf("\n%d", &arr[i]);
	}
	largest = function(arr, num);

	printf("The largest element is: %d\n", largest);
	wait_for_input();
}

int function (int arr[], int num)
{
	int i,largest;
	largest = arr[0];

	for(i=0; i<num; i++)
	{
	if (arr[i]>largest)
	{
	largest = arr[i];
	}
	}
	return largest;
}

void wait_for_input(void)
{
	printf("Press ENTER for Exit\n");
	while(getchar()!='\n');
	getchar();

}

//OUTPUT:
//Enter the number of elements in an array
//5
//Enter the number of component in an array
//56
//32
//31
//44
//23
//The largest element is: 56
//Press ENTER for Exit

