/*
 * main.c
 *
 *  Created on: Apr 27, 2026
 *      Author: CITI
 */


// Online C compiler to run C program online
#include <stdio.h>

int main() {

	void wait_for_input(void);
    int i=0, flag =1;
    char str1[100], str2[100];

    printf("Enter the string 1: ");
    scanf("%s", str1);

    printf("\nEnter the string 2: ");
    scanf("%s" , str2);

    while (str1[i] !='\0' || str2[i] !='\0')
    {
        if ( str1[i] != str2[i])
        {
            flag =0;
            break;
        }
        i++;
    }

        if (flag ==1)
        {
            printf("\nThe strings are equal");

        }
        else
        {
            printf("\n The strings are not equal");
        }


    wait_for_input();
}


void wait_for_input()
{
	printf("\nPress ENTER for EXIT");
	while (getchar()!= '\n');
	getchar();
}


//Output:
//Enter the string 1: Abhi
//
//Enter the string 2: Abhi
//
//The strings are equal
//Press ENTER for EXIT

