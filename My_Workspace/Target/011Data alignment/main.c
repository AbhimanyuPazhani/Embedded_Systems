/*
 * main.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ADMIN
 */


#include<stdio.h>
#include<stdint.h>

void wait_for_input(void)
{
    printf("\nPress Enter to exit...");
    while (getchar() != '\n');  // clear input buffer
    getchar();                  // wait for Enter
}

struct dataSet {

	char 	data1;
	int 	data2;
	char 	data3;
	short	data4;
};

int main (void)
{

	struct dataSet data;
	data.data1 = 0x11;
	data.data2 = 0xFFFFEEEE;
	data.data3 = 0x22;
	data.data4 = 0xABCD;

	uint8_t *ptr;
	ptr = (uint8_t*) &data; //struct dataset
	uint32_t totalSize = sizeof(struct dataSet);

	printf("Memory address       content \n");
	printf("==============================\n");

	for(uint32_t i =0; i<totalSize; i++)
	{
	printf("%p       ||        %X\n", ptr,*ptr);
	ptr++;
	}

	printf("Total memory consumed by this struct variable = %u\n", sizeof(struct dataSet));
	wait_for_input();


}
/*
Memory address       content
==============================
0061FF08       ||        11
0061FF09       ||        FF
0061FF0A       ||        61
0061FF0B       ||        0
0061FF0C       ||        EE
0061FF0D       ||        EE
0061FF0E       ||        FF
0061FF0F       ||        FF
0061FF10       ||        22
0061FF11       ||        19
0061FF12       ||        CD
0061FF13       ||        AB
Total memory consumed by this struct variable = 12


The above one is the output of the above program only 11, EE,EE,FF,22,CD,AB are the data which we provided others are padding ...
It sometimes print garbage values too that's what we see up there ...
In order to remove these padding for memory optimization we need to add attribute packed...
Which is a good for user not for the compiler ^v^...

*/

