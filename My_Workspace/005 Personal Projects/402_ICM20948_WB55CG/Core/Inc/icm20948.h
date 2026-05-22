/*
 * icm20948.h
 *
 *  Created on: May 21, 2026
 *      Author: CITI
 */

/**
 * @file    icm20948.h
 * @brief   ICM-20948 9-DoF IMU Driver for STM32WB55 using SPI + HAL
 *
 * Hardware: SparkFun ICM-20948 breakout board
 * Interface: SPI1, Mode 0 (CPOL=0, CPHA=0)
 * CS Pin: PB2, labelled IMU_CS in IOC/CubeMX
 *
 * WHO_AM_I expected value: 0xEA
 *
 * IMPORTANT — Bank switching:
 *   The ICM-20948 uses 4 register banks (Bank 0–3).
 *   REG_BANK_SEL (address 0x7F) exists in ALL banks.
 *   Always switch to the correct bank before accessing a register.
 *   This driver provides ICM20948_SetBank() for that purpose.
 */

#ifndef ICM20948_H
#define ICM20948_H

#include "main.h"      /* Brings in CubeMX pin definitions and the HAL */
#include <stdint.h>
#include <stdbool.h>

/* =========================================================
 *  Hardware handle — set this to your SPI handle name
 * ========================================================= */
extern SPI_HandleTypeDef hspi1;   /* Defined in main.c / spi.c */

/* =========================================================
 *  Chip-Select macro — uses your IOC-renamed pin IMU_CS
 * ========================================================= */
#define IMU_CS_LOW()   HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_RESET)
#define IMU_CS_HIGH()  HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, GPIO_PIN_SET)

/* =========================================================
 *  SPI register-address format (datasheet §6.5)
 *    Bit 7 = 1  → READ
 *    Bit 7 = 0  → WRITE
 * ========================================================= */
#define ICM_READ_FLAG   0x80u
#define ICM_WRITE_FLAG  0x00u

/* =========================================================
 *  WHO_AM_I
 * ========================================================= */
#define ICM20948_WHO_AM_I_VAL   0xEA   /* Expected fixed value */

/* =========================================================
 *  REG_BANK_SEL  — address 0x7F in ALL banks
 * ========================================================= */
#define ICM_REG_BANK_SEL        0x7F
#define ICM_BANK_0              (0 << 4)
#define ICM_BANK_1              (1 << 4)
#define ICM_BANK_2              (2 << 4)
#define ICM_BANK_3              (3 << 4)

/* =========================================================
 *  BANK 0 Registers
 * ========================================================= */
#define ICM_B0_WHO_AM_I         0x00
#define ICM_B0_USER_CTRL        0x03
#define ICM_B0_PWR_MGMT_1       0x06
#define ICM_B0_PWR_MGMT_2       0x07
#define ICM_B0_INT_PIN_CFG      0x0F
#define ICM_B0_ACCEL_XOUT_H     0x2D
#define ICM_B0_ACCEL_XOUT_L     0x2E
#define ICM_B0_ACCEL_YOUT_H     0x2F
#define ICM_B0_ACCEL_YOUT_L     0x30
#define ICM_B0_ACCEL_ZOUT_H     0x31
#define ICM_B0_ACCEL_ZOUT_L     0x32
#define ICM_B0_GYRO_XOUT_H      0x33
#define ICM_B0_GYRO_XOUT_L      0x34
#define ICM_B0_GYRO_YOUT_H      0x35
#define ICM_B0_GYRO_YOUT_L      0x36
#define ICM_B0_GYRO_ZOUT_H      0x37
#define ICM_B0_GYRO_ZOUT_L      0x38
#define ICM_B0_TEMP_OUT_H       0x39
#define ICM_B0_TEMP_OUT_L       0x3A
/* External sensor data — magnetometer data lands here when I2C master mode is used */
#define ICM_B0_EXT_SLV_SENS_DATA_00  0x3B

/* =========================================================
 *  BANK 2 Registers (gyro/accel config)
 * ========================================================= */
#define ICM_B2_GYRO_SMPLRT_DIV  0x00
#define ICM_B2_GYRO_CONFIG_1    0x01
#define ICM_B2_ACCEL_SMPLRT_DIV_1 0x10
#define ICM_B2_ACCEL_SMPLRT_DIV_2 0x11
#define ICM_B2_ACCEL_CONFIG     0x14

/* =========================================================
 *  BANK 3 Registers (I2C master — used to reach magnetometer)
 * ========================================================= */
#define ICM_B3_I2C_MST_CTRL     0x01
#define ICM_B3_I2C_SLV0_ADDR    0x03
#define ICM_B3_I2C_SLV0_REG     0x04
#define ICM_B3_I2C_SLV0_CTRL    0x05
#define ICM_B3_I2C_SLV4_ADDR    0x13
#define ICM_B3_I2C_SLV4_REG     0x14
#define ICM_B3_I2C_SLV4_CTRL    0x15
#define ICM_B3_I2C_SLV4_DO      0x16
#define ICM_B3_I2C_SLV4_DI      0x17

/* =========================================================
 *  Magnetometer (AK09916) — accessed via ICM I2C master
 * ========================================================= */
#define AK09916_I2C_ADDR        0x0C   /* 7-bit address */
#define AK09916_WIA             0x01   /* Device ID register; expected 0x09 */
#define AK09916_ST1             0x10   /* Status 1 — bit 0 = DRDY */
#define AK09916_HXL             0x11   /* Measurement data start */
#define AK09916_ST2             0x18   /* Status 2 — must be read to release data */
#define AK09916_CNTL2           0x31   /* Control 2 — measurement mode */
#define AK09916_CNTL3           0x32   /* Control 3 — soft reset */

/* Magnetometer measurement modes for CNTL2 */
#define AK09916_MODE_POWER_DOWN     0x00
#define AK09916_MODE_SINGLE         0x01
#define AK09916_MODE_CONT_10HZ      0x02
#define AK09916_MODE_CONT_20HZ      0x04
#define AK09916_MODE_CONT_50HZ      0x06
#define AK09916_MODE_CONT_100HZ     0x08

/* =========================================================
 *  PWR_MGMT_1 bit fields
 * ========================================================= */
#define ICM_DEVICE_RESET        0x80   /* Bit 7 — software reset */
#define ICM_SLEEP_BIT           0x40   /* Bit 6 — sleep mode */
#define ICM_CLKSEL_AUTO         0x01   /* CLKSEL=1 → best available clock */

/* =========================================================
 *  USER_CTRL bit fields
 * ========================================================= */
#define ICM_I2C_IF_DIS          0x10   /* Bit 4 — disable I2C slave, force SPI */
#define ICM_I2C_MST_EN          0x20   /* Bit 5 — enable I2C master */

/* =========================================================
 *  Sensitivity scale factors (from datasheet tables)
 * ========================================================= */
/* Gyroscope — GYRO_FS_SEL=0 → ±250 dps */
#define GYRO_SENS_250DPS        131.0f   /* LSB/dps */
/* Accelerometer — ACCEL_FS_SEL=0 → ±2g */
#define ACCEL_SENS_2G           16384.0f /* LSB/g */
/* Magnetometer */
#define MAG_SENS_UT_PER_LSB     0.15f    /* µT/LSB */

/* =========================================================
 *  Return codes
 * ========================================================= */
typedef enum {
    ICM_OK  = 0,
    ICM_ERR = 1
} ICM_Status;

/* =========================================================
 *  Data structures
 * ========================================================= */

/** Raw 16-bit sensor readings */
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} ICM_RawData;

/** Converted float readings */
typedef struct {
    float x;   /* Physical units depend on sensor type */
    float y;
    float z;
} ICM_FloatData;

/** Full sensor dataset (populated by ICM20948_ReadAll) */
typedef struct {
    ICM_RawData   accel_raw;   /* Raw ADC counts */
    ICM_RawData   gyro_raw;
    ICM_RawData   mag_raw;     /* Raw ADC counts (Little-Endian from AK09916) */

    ICM_FloatData accel_g;     /* Acceleration in g */
    ICM_FloatData gyro_dps;    /* Angular rate in degrees/second */
    ICM_FloatData mag_uT;      /* Magnetic field in µT */

    float temp_C;              /* Die temperature in °C */
} ICM_Data;

/* =========================================================
 *  Public API
 * ========================================================= */

/** Low-level SPI helpers */
void     ICM20948_WriteReg(uint8_t reg, uint8_t data);
uint8_t  ICM20948_ReadReg(uint8_t reg);
void     ICM20948_ReadRegs(uint8_t reg, uint8_t *buf, uint16_t len);

/** Bank selection — MUST be called before any register access */
void     ICM20948_SetBank(uint8_t bank);

/** Initialization */
ICM_Status ICM20948_Init(void);
uint8_t    ICM20948_WhoAmI(void);

/** Sensor reads */
void ICM20948_ReadAccelRaw(ICM_RawData *out);
void ICM20948_ReadGyroRaw(ICM_RawData *out);
bool ICM20948_ReadMagRaw(ICM_RawData *out);   /* returns false if not ready */

/** Converted reads */
void ICM20948_GetAccel_g(ICM_FloatData *out);
void ICM20948_GetGyro_dps(ICM_FloatData *out);
bool ICM20948_GetMag_uT(ICM_FloatData *out);

/** Read everything at once (convenience wrapper) */
void ICM20948_ReadAll(ICM_Data *data);

/** Magnetometer-specific (AK09916 accessed via I2C master) */
ICM_Status ICM20948_InitMagnetometer(void);
void       ICM20948_MagWrite(uint8_t reg, uint8_t val);
uint8_t    ICM20948_MagRead(uint8_t reg);

/** Temperature */
float ICM20948_ReadTemp_C(void);

#endif /* ICM20948_H */
