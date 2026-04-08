/*
 * main.c
 *
 *  Created on: Apr 8, 2026
 *      Author: CITI
 */


#include <stdio.h>
void wait_for_input(void);
int main()
{
	char str[100];
	int i=0, len=0;
	printf("Enter a string:");

	fgets(str, sizeof(str), stdin);

	while (str[i] != '\0')
	{
		len++;
		i++;
	}
	printf("Length of the string: %d", len);
	wait_for_input();
}

void wait_for_input()
{
	printf("\nPress Enter for EXIT");
	while (getchar()!= '\n');
	getchar();
}


//Enter a string:Abhimanyu
//Length of the string: 10
//Press Enter for EXIT
