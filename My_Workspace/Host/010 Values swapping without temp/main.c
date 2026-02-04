/*
 * main.c
 *
 *  Created on: Feb 3, 2026
 *      Author: CITI
 */


//#include <stdio.h>
//
//int main()
//{
//	int a,b;
//	printf("Enter the values of a and b:");
//	scanf("%d\n %d", &a, &b);
//	printf("Before swapping\n");
//	printf("a=%d and b=%d\n", a,b);
//	a=a+b;
//	b=a-b;
//	a=a-b;
//	printf("After swapping\n");
//	printf("a=%d and b=%d\n", a,b);
//
//	getchar();
//	getchar();
//}


#include <stdio.h>

int main()
{
	int a,b;
	printf("Enter the values of a and b:");
	scanf("%d\n %d", &a, &b);
	printf("Before swapping\n");
	printf("a=%d and b=%d\n", a,b);
	a=a^b;
	b=a^b;
	a=a^b;
	printf("After swapping\n");
	printf("a=%d and b=%d\n", a,b);

	getchar();
	getchar();
}



//Output:
//Enter the values of a and b:6
//9
//Before swapping
//a=6 and b=9
//After swapping
//a=9 and b=6
