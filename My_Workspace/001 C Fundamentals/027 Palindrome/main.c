/*
 * main.c
 *
 *  Created on: Mar 12, 2026
 *      Author: CITI
 */


#include <stdio.h>


void wait_for_input(void);
int main()
{
	int a,r=0;
	printf("Enter the 4 digit number:");

	scanf("%d", &a);

	if (a<1000 || a>9999)
	{
		printf("It's not a 4 digit number");

	}
	else
	{
		r = (((a%10)*1000))  + (((a/100)%10)*100)  + (((a/10)%10)*10) + (a/1000);

		if (a==r)
			{
				printf("It is a Palindrome");

			}
			else
			{
				printf("It is Not a Palindrome");
			}
	}
	wait_for_input();


}

void wait_for_input()
{
	printf("\nPress ENTER to EXIT");

	while (getchar()!='\n');
	getchar();
}



//Output:
//Enter the 4 digit number:1551
//It is a Palindrome
//Press ENTER to EXIT
