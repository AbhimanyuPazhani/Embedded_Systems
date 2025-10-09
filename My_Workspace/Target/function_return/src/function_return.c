/*
 ============================================================================
 Name        : function_return.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include "math.h"

//int myfunction();
//
//int main()
//{
//
//	int retvalue;
//	retvalue = myfunction(12,12,12);
//	printf("The return value is %d", retvalue);
//	return 0;
//}
//
//int myfunction(int a, int b, int c)
//{
//	int sum;
//	sum = a+b+c;
//	return sum;
//}

int main (void)
{
	printf("Addition: %d\n", math_add(0x0fff1111, 0x0fff1111));
	printf("Subtraction: %d\n", math_sub(0x0fff1111, 0x0fff1111));
	printf("Multiplication: %I64d\n", math_mul(5, 5));
	printf("Division: %f\n", math_div(2, 1));

	return 0;
}
