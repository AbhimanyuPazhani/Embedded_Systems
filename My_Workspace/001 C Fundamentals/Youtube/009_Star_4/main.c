/*
 * main.c
 *
 *  Created on: 19-Jan-2026
 *      Author: CITI
 */



#include <stdio.h>

int main()

{
    int i,j, space,rows;
    printf("Enter the number of rows:");
    scanf("%d", &rows);
    for (i=1; i<=rows; i++)
    {
       for (space =1; space<= (rows -i); space++)
       {
           printf(" ");
       }
        for (j=1; j<=i; j++)
        {
            printf("* ");
        }
        printf("\n");
    }
    getchar();
    getchar();

    return 0;
}


//Output
//Enter the number of rows:6
//     *
//    * *
//   * * *
//  * * * *
// * * * * *
//* * * * * *
