/*
 * main.c
 *
 *  Created on: May 31, 2026
 *      Author: CITI
 */

#include<stdio.h>

void wait_for_input (void)
{
	printf("\nPress enter to EXIT");
	while (getchar()!= '\n');
	getchar();
}

#if count
int countsetbits(unsigned int num)
{
	int count =0;

	while(num)
	{
		count+=(num&1);
		num >>= 1;
	}

	return count;
}


int main()
{
	unsigned int num;
	printf("Enter the number:");
	scanf("%d", &num);

	printf("\nSet bits = %d", countsetbits(num));
	wait_for_input ();
}

#endif

//Method 2: Brian Kernighan's Algorithm

int countSetBits(unsigned int num)
{
    int count = 0;

    while(num)
    {
        num = num & (num - 1);
        count++;
    }

    return count;
}

int main()
{
	unsigned int num;
	printf("Enter the number:");
	scanf("%d", &num);

    printf("Number of set bits = %d\n", countSetBits(num));

    wait_for_input ();
}
