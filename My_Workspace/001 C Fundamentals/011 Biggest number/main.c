/*
 * main.c
 *
 *  Created on: Feb 4, 2026
 *      Author: CITI
 */


#include <stdio.h>

int main(void)
{
    int a, b;

    printf("Enter the values of A and B: ");
    scanf("%d %d", &a, &b);

    if (a > b)
    {
        printf("A is the biggest number");
    }
    else if (a < b)
    {
        printf("B is the biggest number");
    }
    else
    {
        printf("A and B are equal");
    }

    getchar();
    getchar();
}


//Output:
//Enter the values of A and B: 1 2
//B is the biggest number
