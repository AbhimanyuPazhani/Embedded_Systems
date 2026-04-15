/*
 * main.c
 *
 *  Created on: Mar 6, 2026
 *      Author: CITI
 */
// Online C compiler to run C program online
#include <stdio.h>


void wait_for_input();
int main() {
    int i,j,mul;
    printf("Enter the number:");
    scanf("%d", &j);

    for (i=0;i<=10; i++)
    {
        mul = j*i;
        printf("%d * %d = %d\n", j,i, mul);

    }

    wait_for_input();
}

void wait_for_input()
{
	printf("\n Press Enter to EXIT");
	while (getchar()!='\n');
	getchar();
}



//Output:
//Enter the number:5
//5 * 0 = 0
//5 * 1 = 5
//5 * 2 = 10
//5 * 3 = 15
//5 * 4 = 20
//5 * 5 = 25
//5 * 6 = 30
//5 * 7 = 35
//5 * 8 = 40
//5 * 9 = 45
//5 * 10 = 50
//
// Press Enter to EXIT
