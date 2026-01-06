/*
 * main.c
 *
 *  Created on: Nov 12, 2025
 *      Author: ADMIN
 */


#include <stdio.h>


void wait_for_input (void);
int main()
{
	int num1, num2;
	int larger;
	printf("Enter the num1 and num2:");
	fflush(stdout);
	scanf("%d %d", &num1, &num2);

	larger = (num1>num2)? num1 : num2;
	printf("Larger Number = %d", larger);
//	if (num1 > num2)
//	{
//		printf("Larger Number = %d",num1);
//	}
//	else{
//		printf("Larger Number = %d", num2);
//	}
	wait_for_input();

}
void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}
