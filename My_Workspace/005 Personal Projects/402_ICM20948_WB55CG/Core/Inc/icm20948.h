/*
 * icm20948.h
 *
 *  Created on: May 21, 2026
 *      Author: CITI
 */

#ifndef ICM20948_H_
#define ICM20948_H_

#include "main.h"
#define IMU_CS_Pin GPIO_PIN_2
#define IMU_CS_GPIO_Port GPIOB

/* ICM20948 Registers - Bank 0 */
#define ICM_WHO_AM_I         0x00
#define ICM_PWR_MGMT_1       0x06
#define ICM_ACCEL_XOUT_H     0x2D
#define ICM_GYRO_XOUT_H      0x33

#define ICM_EXPECTED_WHOAMI  0xEA

/* Struct to hold sensor data */
typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
} ICM20948_Data_t;

/* Function Prototypes */
uint8_t ICM_Init(SPI_HandleTypeDef *hspi);
void ICM_ReadData(SPI_HandleTypeDef *hspi, ICM20948_Data_t *data);

#endif /* ICM20948_H_ */
