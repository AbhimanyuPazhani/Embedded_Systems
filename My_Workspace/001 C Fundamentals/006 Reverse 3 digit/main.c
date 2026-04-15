/*
 * main.c
 *
 *  Created on: Nov 12, 2025
 *      Author: ADMIN
 */


#include <stdio.h>

void wait_for_input(void);

int main() {
  int number ;
  int reversed = 0;
  printf("Enter the 3 digit number:");

  fflush (stdout);
  scanf("%d", &number);

  reversed = (((number % 100) % 10)* 100) + (((number % 100)/10)*10) + (number /100);  // Logic to reverse the number
  printf("Reversed = %d", reversed);
  wait_for_input();

  return 0;
}
void wait_for_input(void)
{
	printf("\nPress Enter to EXIT");
	while (getchar() != '\n');
	getchar();
}
