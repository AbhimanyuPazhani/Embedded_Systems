/*
 * main.c
 *
 *  Created on: Feb 10, 2026
 *      Author: CITI
 */


// Online C compiler to run C program online
#include <stdio.h>


void wait_for_input(void);

int main() {
    int units;
    float Bill;
    printf("Enter the number of units:");
    scanf("%d", &units);

    if (units<=100)
    {
        Bill = (units *0);

    }
    else if(units<=200)
    {
        Bill = ((units - 100) * 1.5);
    }
    else if(units <= 300)
    {
        Bill = (100 * 1.5 )+((units - 200) * 2.5);
    }
    else
    {
        Bill = (100 * 1.5)+(100 * 2.5)+((units - 300)*4);
    }

    printf("The Electricity bill: %.2f", Bill);

    wait_for_input();

}

void wait_for_input(void)
{
	printf("\nPress ENTER to EXIT");
	while (getchar ()!= '\n');

	getchar();


}
