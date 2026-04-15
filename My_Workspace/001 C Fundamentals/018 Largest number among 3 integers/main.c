/*
 * main.c
 *
 *  Created on: Feb 6, 2026
 *      Author: CITI
 */

#include <stdio.h>

int main()
{
    int a, b, c;

    printf("Enter the numbers a, b, c: ");
    scanf("%d %d %d", &a, &b, &c);

    if (a >= b && a >= c)
    {
        printf("\na is the biggest number");

        if (b >= c)
        {
            printf("\nb is the second biggest number");
            printf("\nc is the smallest number");
        }
        else
        {
            printf("\nc is the second biggest number");
            printf("\nb is the smallest number");
        }
    }
    else if (b >= a && b >= c)
    {
        printf("\nb is the biggest number");

        if (a >= c)
        {
            printf("\na is the second biggest number");
            printf("\nc is the smallest number");
        }
        else
        {
            printf("\nc is the second biggest number");
            printf("\na is the smallest number");
        }
    }
    else
    {
        printf("\nc is the biggest number");

        if (a >= b)
        {
            printf("\na is the second biggest number");
            printf("\nb is the smallest number");
        }
        else
        {
            printf("\nb is the second biggest number");
            printf("\na is the smallest number");
        }
    }

    getchar();
    getchar();
}



//output:
//Enter the numbers a, b, c: 0 5 1
//
//b is the biggest number
//c is the second biggest number
//a is the smallest number
