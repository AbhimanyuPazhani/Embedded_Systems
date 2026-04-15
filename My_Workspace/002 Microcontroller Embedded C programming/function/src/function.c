/*
 ============================================================================
 Name        : function.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdio.h>
void myfunction();
int main()
{
	myfunction(12,11,21);
	myfunction(10,10,-10);
	return 0;

}

void myfunction(int a, int b, int c)
{
	int sum;
	sum = a+b+c;
	printf("sum = %d\n", sum);
	printf("The sum of three is %d\n",a+b+c);
}
