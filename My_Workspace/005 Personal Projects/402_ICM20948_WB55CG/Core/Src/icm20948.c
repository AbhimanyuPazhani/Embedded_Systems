/*
 * icm20948.c
 *
 *  Created on: May 21, 2026
 *      Author: CITI
 */


#include "icm20948.h"

/* Helper function to write a register */
static void ICM_WriteReg(SPI_HandleTypeDef *hspi, uint8_t reg, uint8_t val) {
    uint8_t tx_data[2];
    tx_data[0] = reg & 0x7F; // Write operation: MSB must be 0
    tx_data[1] = val;

    HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_RESET); // CS Low
    HAL_SPI_Transmit(hspi, tx_data, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_SET);   // CS High
}

/* Helper function to read a register */
static uint8_t ICM_ReadReg(SPI_HandleTypeDef *hspi, uint8_t reg) {
    uint8_t tx_data[2];
    uint8_t rx_data[2];

    tx_data[0] = reg | 0x80; // Read operation: MSB must be 1
    tx_data[1] = 0x00;       // Dummy byte

    HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(hspi, tx_data, rx_data, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_SET);

    return rx_data[1];
}

/* Initialize Sensor */
uint8_t ICM_Init(SPI_HandleTypeDef *hspi) {
    HAL_Delay(50); // Wait for sensor to power up

    // 1. Check WHO_AM_I
    uint8_t whoami = ICM_ReadReg(hspi, ICM_WHO_AM_I);
    if (whoami != ICM_EXPECTED_WHOAMI) {
        return 0; // Failure
    }

    // 2. Wake up sensor (Clear SLEEP bit in PWR_MGMT_1, set auto clock)
    ICM_WriteReg(hspi, ICM_PWR_MGMT_1, 0x01);
    HAL_Delay(50);

    return 1; // Success
}

/* Read all Accel and Gyro data (Burst read) */
void ICM_ReadData(SPI_HandleTypeDef *hspi, ICM20948_Data_t *data) {
    uint8_t tx_data[13] = {0};
    uint8_t rx_data[13] = {0};

    tx_data[0] = ICM_ACCEL_XOUT_H | 0x80; // Start reading from Accel X High

    HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(hspi, tx_data, rx_data, 13, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_SET);

    // Combine High and Low bytes
    data->accel_x = (int16_t)(rx_data[1] << 8 | rx_data[2]);
    data->accel_y = (int16_t)(rx_data[3] << 8 | rx_data[4]);
    data->accel_z = (int16_t)(rx_data[5] << 8 | rx_data[6]);

    data->gyro_x  = (int16_t)(rx_data[7] << 8 | rx_data[8]);
    data->gyro_y  = (int16_t)(rx_data[9] << 8 | rx_data[10]);
    data->gyro_z  = (int16_t)(rx_data[11] << 8 | rx_data[12]);
}
