/*
 * main.c
 *
 *  Created on: Feb 11, 2026
 *      Author: CITI
 */


#include <stdio.h>


void wait_for_input(void);
int main() {

    int i,n;
    printf("Enter the n input:");
    scanf("%d", &n);

    for (i=0; i<=n; i++)
    {
        printf("%d\n",i);

    }

    wait_for_input();
}

void wait_for_input(void)
{
	printf("\nPress ENTER to EXIT");
	while (getchar ()!= '\n');

	getchar();


}
