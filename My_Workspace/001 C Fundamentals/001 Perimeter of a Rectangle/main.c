/*
 * main.c
 *
 *  Created on: Nov 7, 2025
 *      Author: ADMIN
 */

#include <stdio.h>

void wait_for_input (void);

int main() {
  int length, width;
  int perimeter;
  printf("Enter the Length and Width of the rectangle: ");

  fflush(stdout);

  scanf("%d  %d", &length, &width);
  perimeter = (2 * (length + width));   // Logic to calculate perimeter
  printf("Perimeter = %d", perimeter);


  wait_for_input();
  return 0;
}

void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}
