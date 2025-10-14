/*
 * main.c
 *
 *  Created on: Oct 9, 2025
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


struct carModel
{
	uint32_t carNumber;
	uint32_t carPrice;
	uint16_t carMaxSpeed;
	float carWeight;
};

int main (void)
{
	struct carModel carBMW = {2021, 15000, 220, 1330};

	struct carModel carFord = {4031, 35000, 160, 1900.96};

	struct carModel carHonda = {.carWeight=204, .carNumber = 3031, .carPrice =18000, .carMaxSpeed = 300};

	printf("The car details of BMW\n");
	printf("carNumber = %u\n", carBMW.carNumber);
	printf("carWeight = %f\n", carBMW .carWeight);
	printf("carPrice = %u\n", carBMW.carPrice);
	printf("carMaxSpeed = %u\n", carBMW.carMaxSpeed);

	wait_for_input();

	return 0;


}
