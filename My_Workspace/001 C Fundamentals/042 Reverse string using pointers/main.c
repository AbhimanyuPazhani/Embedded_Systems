/*
 * main.c
 *
 *  Created on: May 10, 2026
 *      Author: CITI
 */


#include <stdio.h>
#include<string.h>

void wait_for_input(void);

int main()
{
	char str[100];
	printf("Enter the string:");
	fgets(str, sizeof(str), stdin);

	str[strcspn(str, "\n")] = '\0';

	char *start= str;
	char *end = (str+strlen(str))-1;


	while (start<end)
	{
		char temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;

	}

	printf("\nReversed string: %s", str);
	wait_for_input();
}

void wait_for_input()
{
	printf("\nPress Enter for EXIT");

	while (getchar()!='\n');
getchar();

}


//
//OUTPUT:
//Enter the string:Abhimanyu
//
//Reversed string: uynamihbA
//Press Enter for EXIT
