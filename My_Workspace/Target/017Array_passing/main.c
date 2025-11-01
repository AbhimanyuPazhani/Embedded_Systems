/*
 * main.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ADMIN
 */


#include <stdint.h>
#include<stdio.h>

void array_display(uint8_t const *const pArray, uint32_t nItems);

int main (void)
{
	uint8_t someData[10] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,};
	for (uint32_t i =0; i<10; i++)
	{
		someData [i] = 0x33;

	}
	uint32_t nItems = sizeof(someData)/sizeof(uint8_t); //There is 10 items so 10 divided by one is equal to 10. nItems =10;
array_display(someData,nItems); //function that sends data outside the forever loop
return 0;
}

//Display function
//Note: Display function do not modify the data or address of the array so we use const keyword.

void array_display(uint8_t const *const pArray, uint32_t nItems) //function that prints the array using passing an array from main to function
{
	//lets display the contents of the received array
	for(uint32_t i=0; i<nItems; i++)
	{
		printf("%x\t", *(pArray+i)); //instead printf("%x\t", *pArray[i]);

		//How to passing a second element of the array to the function?
		//Let say i want to pass the third element of the array,
		//array_display(someData+3,nItems-2);  that +3 only sends from the 3rd element and decrement nItems because of the unbound error.



	}
	getchar();


}
