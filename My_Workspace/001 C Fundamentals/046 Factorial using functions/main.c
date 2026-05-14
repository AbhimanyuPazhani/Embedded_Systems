/*
 * main.c
 *
 *  Created on: May 14, 2026
 *      Author: CITI
 */


#include <stdio.h>
void wait_for_input(void);

int factorial(int n);
int main()
{
	int a;
	printf("Enter the Number: ");
	scanf("%d", &a);

	printf("\n The factorial is %d", factorial (a));
	wait_for_input();
}

int factorial(int n)
{
	int i;
	int ans = 1;
	for (i=2; i<=n; i++)
	{
		ans*=i;
	}
	return ans;
}


void wait_for_input()
{
	printf("\n Press ENTER for Exit");
	while (getchar()!='\n');
	getchar();
}


//OUTPUT:
//Enter the Number: 4
//
// The factorial is 24
// Press ENTER for Exit
