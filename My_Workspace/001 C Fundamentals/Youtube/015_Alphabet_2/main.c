/*
 * main.c
 *
 *  Created on: Jan 23, 2026
 *      Author: CITI
 */


#include <stdio.h>

int main() {
    int i,j,rows;

    printf("Enter the number of rows:");
    scanf("%d", &rows);

    for (i=rows; i>=1; i--)
    {
        for (j=1; j<=i; j++)
        {
            printf("%c",64+j);
        }
        printf("\n");
    }

    getchar();
    getchar();
}



//Output

//Enter the number of rows:6
//ABCDEF
//ABCDE
//ABCD
//ABC
//AB
//A
