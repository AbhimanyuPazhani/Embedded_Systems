/*
 * main.c
 *
 *  Created on: 22-Jan-2026
 *      Author: CITI
 */


#include <stdio.h>

int main() {
    int i,j, rows;

    printf("Enter the number of rows:");
    scanf("%d", &rows);
    for (i=1; i<=rows; i++)
    {
        for (j=1; j<=i; j++)
        {
            printf("%c", 64+j);
        }
        printf("\n");
    }

    getchar();
    getchar();
}



//Note :
//
//Capital Letters (A–Z)
//
//Starting point: A = 65 (decimal) = 0x41 (hex)
//
//Ending point: Z = 90 (decimal) = 0x5A (hex)
//
//Output
//Enter the number of rows:8
//A
//AB
//ABC
//ABCD
//ABCDE
//ABCDEF
//ABCDEFG
//ABCDEFGH
