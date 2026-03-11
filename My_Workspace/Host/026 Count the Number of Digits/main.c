/*
 * main.c
 *
 *  Created on: Mar 11, 2026
 *      Author: CITI
 */


#include <stdio.h>


void wait_for_input(void);
int main ()
{
	int i,n;
	printf("Enter the integer: ");
	scanf("%d", &n);

	for (i=1; i<n; i++)
	{
		n=n/10;

	}
	printf("The number of digits is : %d", i);
	wait_for_input();

}

void wait_for_input()
{
	printf("\nPress ENTER to EXIT\n");
	while (getchar()!='\n');
getchar();


}

//
//Output:
//Enter the integer: 123456
//The number of digits is : 6
//Press ENTER to EXIT
