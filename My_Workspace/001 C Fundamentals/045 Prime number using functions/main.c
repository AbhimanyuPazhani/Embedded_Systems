/*
 * main.c
 *
 *  Created on: May 13, 2026
 *      Author: CITI
 */

// Online C compiler to run C program online
#include <stdio.h>
int prime(int n);

void wait_for_input(void);


int main() {
    int num;
    printf("Enter the number:");
    scanf("%d", &num);

    if(prime(num))
    {
        printf("The Given %d is a prime number", num);
    }
    else
    {
        printf("The Given %d is not a prime number", num);
    }


    wait_for_input();
}

int prime(int n)
{
    int i;
    if (n<=1)
    {
        return 0;
    }

    for(i=2; i<n; i++)
    {
        if (n%i== 0)
        {
            return 0;
        }
    return 1;
    }
}

void wait_for_input(void)

	{
		printf("\n PRESS enter for EXIT");
		while(getchar()!= '\n');
		getchar();
	}
