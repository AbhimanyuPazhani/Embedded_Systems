/*
 * main.c
 *
 *  Created on: Sep 17, 2025
 *      Author: ADMIN
 */

#include <stdio.h>

int main (void)
{
	char num = 100;


	printf("The value of char is : %d", num);
	printf("\n The address of the num is  %p", &num);

	//Create a pointer variable and store the address of 'num'
	char* pAdress = &num;
	char value = *pAdress;
	printf("\n Read value is : %d", value);

	*pAdress = 65;
	printf("\n The value of num is %d", num);

//	while (getchar ()!= '\n')
//	{
//
//	}
//	getchar ();
	return 0;
}
