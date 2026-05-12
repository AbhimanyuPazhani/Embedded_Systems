/*
 * main.c
 *
 *  Created on: May 12, 2026
 *      Author: CITI
 */


#include <stdio.h>

void wait_for_input();

int func(int x, int y)
{
    return x + y;
}

int main()
{
    int a, b, sum;

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    sum = func(a, b);

    printf("The sum is %d", sum);
wait_for_input();
    return 0;
}

void wait_for_input(void)
{
	printf("\nPress Enter to EXIT");
	while (getchar() != '\n');
	getchar();
}

//Output:
//
//Enter two integers: 10 20
//The sum is 30
//Press Enter to EXIT
