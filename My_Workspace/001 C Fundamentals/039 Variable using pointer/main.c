/*
 * main.c
 *
 *  Created on: May 3, 2026
 *      Author: CITI
 */

#include<stdio.h>
void wait_for_input(void);
int main()
{
	int var;
	int *ptr;
	printf("Enter the value: ");
	scanf("%d", &var);

	ptr = &var;
	printf("\nThe value of var: %d", var);
	printf("\nThe address of the var: %p", ptr);
	printf("\nThe value of var using pointer: %d", *ptr);
	wait_for_input();
}

void wait_for_input()
{
	printf("\nPress ENTER for EXIT");
	while (getchar()!='\n');
	getchar();
}


//Output:
//Enter the value: 6
//
//The value of var: 6
//The address of the var: 0061FF18
//The value of var using pointer: 6
//Press ENTER for EXIT
