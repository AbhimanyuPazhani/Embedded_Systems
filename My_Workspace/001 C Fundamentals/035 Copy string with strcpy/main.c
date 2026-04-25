/*
 * main.c
 *
 *  Created on: Apr 25, 2026
 *      Author: CITI
 */


#include<stdio.h>
void wait_for_input(void);

int main()
{
	char Source[100], Destination[100];
	int i=0;

	printf("Enter the string:");
	scanf("%s", Source);

	while (Source[i] != '\0')
	{

		Destination [i] = Source [i];
		i++;

	}

	Destination[i] = '\0';

	printf("\nCopied String: %s", Destination);
	wait_for_input();

}

void wait_for_input()
{
	printf("\nPress ENTER to EXIT");

	while (getchar() != '\n');
	getchar();
}

//
//Output:
//Enter the string:Abhimanyu
//
//Copied String: Abhimanyu
//Press ENTER to EXIT
