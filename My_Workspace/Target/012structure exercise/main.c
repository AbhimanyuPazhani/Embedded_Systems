/*
 * main.c
 *
 *  Created on: Oct 15, 2025
 *      Author: ADMIN
 */


/* Write a program to decode a given 32bit packet information and print the values of different fields.
 create a structure with the member elements as packet field as shown below

 video 162*/

#include<stdio.h>
#include<stdint.h>

struct Packet
{

	uint8_t   crc;
	uint8_t   status;
	uint16_t  payload;
	uint8_t   bat;
	uint8_t   sensor;
	uint8_t   longAddr;
	uint8_t   shortAddr;
	uint8_t   addrMode;
};


int main(void)
{

	uint32_t packetValue;
	printf("Enter the 32bit packet value:");
	scanf("%x", &packetValue);

	struct Packet packet;

	packet.crc 			= (uint8_t) (packetValue & 0x3);
	packet.status 		= (uint8_t) ((packetValue >>2)&0x1);
	packet.payload 		= (uint16_t) ((packetValue >> 3) & 0xFFF);
	packet.bat 			= (uint8_t)	((packetValue >>15) & 0x0011);
	packet.sensor 		= (uint8_t) ((packetValue >> 18) & 0x7);
	packet.longAddr 	= (uint8_t) ((packetValue >> 21) & 0xFF);
	packet.shortAddr 	= (uint8_t) ((packetValue >> 29) & 0x1);
	packet.addrMode 	= (uint8_t) ((packetValue >> 31) & 0x1);


	printf("crc       : %#x\n", packet.crc);
	printf("status    : %#x\n", packet.status);
	printf("payload   : %#x\n", packet.payload);
	printf("bat   	  : %#x\n", packet.bat);
	printf("sensor    : %#x\n", packet.sensor);
	printf("longAddr  : %#x\n", packet.longAddr);
	printf("shortAddr : %#x\n", packet.shortAddr);
	printf("addrMode  : %#x\n", packet.addrMode);

	printf("The size of the struct is %u\n", sizeof(struct Packet));

	getchar();
	getchar();
	return 0;

}


/*   Output
 *
 * Enter the 32bit packet value:0x1234fff1
crc       : 0x1
status    : 0
payload   : 0xffe
bat       : 0x1
sensor    : 0x5
longAddr  : 0x91
shortAddr : 0
addrMode  : 0
The size of the struct is 10


 * Here we can see the struct consumes 10 bytes of address in the memory,
 * we can able to reduce the size of the struct by using bit fields in the program on the struct.
 *
 * */

 */
