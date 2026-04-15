/*
 * math.c
 *
 *  Created on: Aug 30, 2025
 *      Author: ADMIN
 */


int math_add(int a, int b);
int math_sub(int a, int b);
long long int math_mul(int a, int b);
float math_div(int a, int b);

int math_add(int a, int b)
{
	return a+b;
}
int math_sub(int a, int b)
{
	return a-b;
}
long long int math_mul(int a, int b)
{
	return (long long int)a*b; //Use type cast for better results (This one is explicit casting)
}
float math_div(int a, int b)
{
	return a/b;
}
