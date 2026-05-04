/*
 * main.c
 *
 *  Created on: May 4, 2026
 *      Author: CITI
 */


#include <stdio.h>
void swap (int *a, int *b)
	{
		int temp;
		temp = *a;
		*a=*b;
		*b=temp;
	}

void wait_for_input(void);

int main()
{
int x,y;
printf("Enter the value of X and Y:\n");
scanf ("%d %d", &x, &y);
swap(&x,&y);


printf("After swapping: x = %d and y = %d", x,y);
wait_for_input();

}

void wait_for_input()
{
	printf("\n\nPress Enter for EXIT");
	while (getchar()!='\n');
	getchar();
}


//OUTPUT:
//Enter the value of X and Y:
//2
//5
//After swapping: x = 5 and y = 2
//
//Press Enter for EXIT
