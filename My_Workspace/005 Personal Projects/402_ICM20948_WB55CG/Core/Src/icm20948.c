/*
 * icm20948.c
 *
 *  Created on: May 21, 2026
 *      Author: CITI
 */

/**
 * @file    icm20948.c
 * @brief   ICM-20948 9-DoF IMU Driver — SPI + HAL implementation
 *
 * Target:  STM32WB55CG (USB Dongle)
 * SPI:     SPI1  — PA5=SCK, PA6=MISO, PA7=MOSI
 * CS pin:  PB2   — renamed IMU_CS in CubeMX IOC
 * UART:    LPUART1 — PA2=TX, PA3=RX  (for printf debugging)
 *
 * SPI Mode:  CPOL=0, CPHA=0  (Mode 0)  — data latched on rising edge
 * Max clock: 7 MHz (ICM-20948 datasheet §3.6)
 *
 * Register banking:
 *   The ICM-20948 organises its registers into 4 banks.
 *   You MUST call ICM20948_SetBank(n) before any bank-n register access.
 *   REG_BANK_SEL lives at 0x7F in every bank.
 */

#include "icm20948.h"
#include <stdio.h>    /* for printf via UART */
#include <string.h>   /* for memset */

/* =========================================================
 *  SPI TIMEOUT (ms)
 * ========================================================= */
#define SPI_TIMEOUT_MS  100u

/* =========================================================
 *  Internal state
 * ========================================================= */
static uint8_t s_current_bank = 0xFF;  /* force a bank write on first use */

/* =========================================================
 *  SECTION 1 — Low-level SPI helpers
 * =========================================================
 *
 * SPI protocol for ICM-20948 (datasheet §6.5):
 *   WRITE: CS LOW → [reg addr | 0x00] [data byte] → CS HIGH
 *   READ:  CS LOW → [reg addr | 0x80] [dummy 0x00] → CS HIGH
 *            The sensor clocks out the register value in the dummy byte slot.
 *
 * Why manual CS (not hardware NSS)?
 *   Hardware NSS de-asserts between bytes in some HAL implementations.
 *   The ICM-20948 requires CS to stay LOW for the ENTIRE transaction.
 *   Manual control via GPIO guarantees correct timing.
 */

/**
 * @brief  Write a single byte to an ICM-20948 register.
 * @param  reg   Register address (7-bit, LSB of first byte)
 * @param  data  Byte to write
 */
void ICM20948_WriteReg(uint8_t reg, uint8_t data)
{
    uint8_t tx[2];
    tx[0] = (reg & 0x7F) | ICM_WRITE_FLAG;  /* bit7=0 → write */
    tx[1] = data;

    IMU_CS_LOW();                            /* assert chip select */
    HAL_SPI_Transmit(&hspi1, tx, 2, SPI_TIMEOUT_MS);
    IMU_CS_HIGH();                           /* de-assert chip select */
}

/**
 * @brief  Read a single byte from an ICM-20948 register.
 * @param  reg  Register address
 * @return      Register value
 */
uint8_t ICM20948_ReadReg(uint8_t reg)
{
    uint8_t tx[2], rx[2];
    tx[0] = (reg & 0x7F) | ICM_READ_FLAG;   /* bit7=1 → read */
    tx[1] = 0x00;                            /* dummy byte */

    IMU_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, SPI_TIMEOUT_MS);
    IMU_CS_HIGH();

    return rx[1];  /* rx[0] is garbage during address phase */
}

/**
 * @brief  Burst-read multiple consecutive registers.
 * @param  reg  Starting register address
 * @param  buf  Output buffer
 * @param  len  Number of bytes to read
 *
 * The ICM-20948 auto-increments the internal address pointer on
 * burst reads, so you can read 12 bytes of accel+gyro in one shot.
 */
void ICM20948_ReadRegs(uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t addr = (reg & 0x7F) | ICM_READ_FLAG;

    IMU_CS_LOW();
    HAL_SPI_Transmit(&hspi1, &addr, 1, SPI_TIMEOUT_MS);     /* send address */
    HAL_SPI_Receive (&hspi1, buf,   len, SPI_TIMEOUT_MS);   /* receive data */
    IMU_CS_HIGH();
}

/* =========================================================
 *  SECTION 2 — Bank selection
 * =========================================================
 *
 * REG_BANK_SEL (0x7F) bits [5:4] select the active bank.
 *   0x00 → Bank 0    (WHO_AM_I, power, accel/gyro data)
 *   0x10 → Bank 1    (self-test, offset registers)
 *   0x20 → Bank 2    (gyro/accel configuration)
 *   0x30 → Bank 3    (I2C master — for magnetometer)
 */

/**
 * @brief  Switch to a register bank.
 * @param  bank  0, 1, 2, or 3
 *
 * Caches the last written bank to avoid redundant writes.
 * Always call this before accessing any register in a given bank.
 */
void ICM20948_SetBank(uint8_t bank)
{
    uint8_t val = (bank & 0x03) << 4;  /* bits [5:4] */
    if (val == s_current_bank) return;  /* already set — skip write */

    s_current_bank = val;
    ICM20948_WriteReg(ICM_REG_BANK_SEL, val);
}

/* =========================================================
 *  SECTION 3 — Magnetometer I2C master helpers
 * =========================================================
 *
 * The AK09916 magnetometer is a separate die inside the ICM-20948
 * package. It communicates over an internal I2C bus.
 *
 * When using SPI between the STM32 and ICM-20948, we CANNOT
 * use the bypass multiplexer (that only works with I2C host).
 * Instead we use the ICM-20948's built-in I2C master (Bank 3)
 * to read/write the AK09916 on our behalf.
 *
 * Method: I2C Slave 4 for single-byte reads/writes (simpler).
 */

/**
 * @brief  Write one byte to an AK09916 register via ICM I2C master.
 */
void ICM20948_MagWrite(uint8_t reg, uint8_t val)
{
    ICM20948_SetBank(3);
    ICM20948_WriteReg(ICM_B3_I2C_SLV4_ADDR, AK09916_I2C_ADDR);  /* addr, write=0 */
    ICM20948_WriteReg(ICM_B3_I2C_SLV4_REG,  reg);
    ICM20948_WriteReg(ICM_B3_I2C_SLV4_DO,   val);
    ICM20948_WriteReg(ICM_B3_I2C_SLV4_CTRL, 0x80); /* bit7=EN, single transaction */
    HAL_Delay(1);  /* let the I2C master complete */
}

/**
 * @brief  Read one byte from an AK09916 register via ICM I2C master.
 * @return Register value
 */
uint8_t ICM20948_MagRead(uint8_t reg)
{
    ICM20948_SetBank(3);
    ICM20948_WriteReg(ICM_B3_I2C_SLV4_ADDR, AK09916_I2C_ADDR | 0x80); /* bit7=1 → read */
    ICM20948_WriteReg(ICM_B3_I2C_SLV4_REG,  reg);
    ICM20948_WriteReg(ICM_B3_I2C_SLV4_CTRL, 0x80); /* EN */
    HAL_Delay(1);

    ICM20948_SetBank(3);
    return ICM20948_ReadReg(ICM_B3_I2C_SLV4_DI);  /* result is here */
}

/* =========================================================
 *  SECTION 4 — Magnetometer initialisation
 * ========================================================= */

/**
 * @brief  Initialise the AK09916 magnetometer via the ICM I2C master.
 *
 * Steps:
 *   1. Enable I2C master in the ICM (Bank 0 USER_CTRL)
 *   2. Configure I2C master clock (Bank 3)
 *   3. Soft-reset the AK09916
 *   4. Set AK09916 to continuous measurement 100 Hz
 *   5. Configure I2C Slave 0 to auto-read 8 bytes every sample
 *
 * @return ICM_OK on success, ICM_ERR if mag ID check fails
 */
ICM_Status ICM20948_InitMagnetometer(void)
{
    /* Step 1 — enable ICM I2C master */
    ICM20948_SetBank(0);
    uint8_t user_ctrl = ICM20948_ReadReg(ICM_B0_USER_CTRL);
    user_ctrl |= ICM_I2C_MST_EN;
    ICM20948_WriteReg(ICM_B0_USER_CTRL, user_ctrl);
    HAL_Delay(10);

    /* Step 2 — set I2C master clock ~345 kHz (safe for AK09916) */
    ICM20948_SetBank(3);
    ICM20948_WriteReg(ICM_B3_I2C_MST_CTRL, 0x07);  /* I2C_MST_CLK=7 */
    HAL_Delay(10);

    /* Step 3 — soft-reset the AK09916 */
    ICM20948_MagWrite(AK09916_CNTL3, 0x01);  /* SRST bit */
    HAL_Delay(10);

    /* Step 4 — verify magnetometer ID */
    uint8_t mag_id = ICM20948_MagRead(AK09916_WIA);
    if (mag_id != 0x09) {
        printf("[ICM] AK09916 ID mismatch: got 0x%02X, expected 0x09\r\n", mag_id);
        return ICM_ERR;
    }
    printf("[ICM] AK09916 magnetometer found (ID=0x09)\r\n");

    /* Step 5 — set continuous measurement 100 Hz */
    ICM20948_MagWrite(AK09916_CNTL2, AK09916_MODE_CONT_100HZ);
    HAL_Delay(10);

    /*
     * Step 6 — configure I2C Slave 0 to automatically read 8 bytes
     * (ST1 + HXL + HXH + HYL + HYH + HZL + HZH + ST2) every sample.
     * These bytes land in EXT_SLV_SENS_DATA_00..07 (Bank 0).
     */
    ICM20948_SetBank(3);
    ICM20948_WriteReg(ICM_B3_I2C_SLV0_ADDR, AK09916_I2C_ADDR | 0x80); /* read */
    ICM20948_WriteReg(ICM_B3_I2C_SLV0_REG,  AK09916_ST1);             /* start reg */
    ICM20948_WriteReg(ICM_B3_I2C_SLV0_CTRL, 0x88);  /* EN | read 8 bytes */

    return ICM_OK;
}

/* =========================================================
 *  SECTION 5 — Main initialisation
 * ========================================================= */

/**
 * @brief  Full ICM-20948 initialisation sequence.
 *
 * Order matters:
 *   1. CS HIGH (idle state)
 *   2. Wait for power-on (>11 ms per datasheet §A.C. table)
 *   3. Software reset → device wakes clean
 *   4. Disable sleep mode, select auto clock
 *   5. Disable I2C slave (SPI-only mode)
 *   6. Configure gyroscope (Bank 2)
 *   7. Configure accelerometer (Bank 2)
 *   8. Verify WHO_AM_I
 *   9. Init magnetometer
 *
 * @return ICM_OK on success, ICM_ERR on WHO_AM_I mismatch
 */
ICM_Status ICM20948_Init(void)
{
    /* Ensure CS starts HIGH (de-asserted) */
    IMU_CS_HIGH();
    HAL_Delay(20);  /* wait for sensor power-on */

    /* --- Software reset --- */
    ICM20948_SetBank(0);
    ICM20948_WriteReg(ICM_B0_PWR_MGMT_1, ICM_DEVICE_RESET);
    HAL_Delay(100);  /* datasheet says 100 ms after reset */

    /*
     * --- Wake from sleep, select auto clock (CLKSEL=1) ---
     * Reset value of PWR_MGMT_1 is 0x41 (SLEEP=1, CLKSEL=1).
     * Writing 0x01 clears SLEEP while keeping CLKSEL=1.
     */
    ICM20948_WriteReg(ICM_B0_PWR_MGMT_1, ICM_CLKSEL_AUTO);
    HAL_Delay(30);

    /*
     * --- Disable I2C slave interface, lock to SPI only ---
     * USER_CTRL bit 4 (I2C_IF_DIS) prevents the sensor from
     * accidentally reverting to I2C mode. This is recommended
     * when using SPI (datasheet §6.1 NOTE).
     */
    ICM20948_WriteReg(ICM_B0_USER_CTRL, ICM_I2C_IF_DIS);

    /* --- Enable all accelerometer and gyroscope axes --- */
    ICM20948_WriteReg(ICM_B0_PWR_MGMT_2, 0x00);  /* 0x00 = all sensors ON */

    /* -------------------------------------------------------
     * Gyroscope configuration (Bank 2)
     *   GYRO_CONFIG_1:
     *     bits [5:3] GYRO_DLPFCFG = 000 → 196.6 Hz BW
     *     bits [2:1] GYRO_FS_SEL  = 00  → ±250 dps
     *     bit  [0]   GYRO_FCHOICE = 1   → enable DLPF
     *   Value: 0b00000001 = 0x01
     * ------------------------------------------------------- */
    ICM20948_SetBank(2);
    ICM20948_WriteReg(ICM_B2_GYRO_CONFIG_1, 0x01);

    /* Gyro sample rate divider: ODR = 1125 / (1 + DIV) Hz
     * DIV=0 → 1125 Hz (maximum, fine for our use) */
    ICM20948_WriteReg(ICM_B2_GYRO_SMPLRT_DIV, 0x00);

    /* -------------------------------------------------------
     * Accelerometer configuration (Bank 2)
     *   ACCEL_CONFIG:
     *     bits [5:3] ACCEL_DLPFCFG = 000 → 246.0 Hz BW
     *     bits [2:1] ACCEL_FS_SEL  = 00  → ±2g
     *     bit  [0]   ACCEL_FCHOICE = 1   → enable DLPF
     *   Value: 0x01
     * ------------------------------------------------------- */
    ICM20948_WriteReg(ICM_B2_ACCEL_CONFIG, 0x01);

    /* Accel sample rate: 1125 / (1 + 0) = 1125 Hz */
    ICM20948_WriteReg(ICM_B2_ACCEL_SMPLRT_DIV_1, 0x00);
    ICM20948_WriteReg(ICM_B2_ACCEL_SMPLRT_DIV_2, 0x00);

    /* -------------------------------------------------------
     * WHO_AM_I verification (Bank 0)
     * ------------------------------------------------------- */
    ICM20948_SetBank(0);
    uint8_t id = ICM20948_ReadReg(ICM_B0_WHO_AM_I);
    if (id != ICM20948_WHO_AM_I_VAL) {
        printf("[ICM] ERROR: WHO_AM_I = 0x%02X, expected 0x%02X\r\n",
               id, ICM20948_WHO_AM_I_VAL);
        printf("[ICM] Check wiring: MOSI/MISO/SCK/CS and 3V3/GND\r\n");
        return ICM_ERR;
    }
    printf("[ICM] WHO_AM_I = 0x%02X ✓  ICM-20948 detected!\r\n", id);

    /* -------------------------------------------------------
     * Magnetometer initialisation
     * ------------------------------------------------------- */
    ICM_Status mag_status = ICM20948_InitMagnetometer();
    if (mag_status != ICM_OK) {
        printf("[ICM] WARNING: Magnetometer init failed. Continuing without mag.\r\n");
    }

    /* Return to Bank 0 — this is the "home" bank for data reads */
    ICM20948_SetBank(0);

    printf("[ICM] Initialisation complete!\r\n");
    return ICM_OK;
}

/**
 * @brief  Read and return the WHO_AM_I register value.
 */
uint8_t ICM20948_WhoAmI(void)
{
    ICM20948_SetBank(0);
    return ICM20948_ReadReg(ICM_B0_WHO_AM_I);
}

/* =========================================================
 *  SECTION 6 — Sensor data reads
 * =========================================================
 *
 * All data registers are in Bank 0 and can be burst-read.
 * ACCEL output starts at 0x2D, GYRO at 0x33 — they are
 * contiguous, so we can read all 12 bytes in one transaction.
 *
 * Data format: 16-bit signed, big-endian (HIGH byte first).
 * Combine: value = (HIGH << 8) | LOW
 */

/**
 * @brief  Read raw accelerometer values.
 */
void ICM20948_ReadAccelRaw(ICM_RawData *out)
{
    uint8_t buf[6];
    ICM20948_SetBank(0);
    ICM20948_ReadRegs(ICM_B0_ACCEL_XOUT_H, buf, 6);

    out->x = (int16_t)((buf[0] << 8) | buf[1]);
    out->y = (int16_t)((buf[2] << 8) | buf[3]);
    out->z = (int16_t)((buf[4] << 8) | buf[5]);
}

/**
 * @brief  Read raw gyroscope values.
 */
void ICM20948_ReadGyroRaw(ICM_RawData *out)
{
    uint8_t buf[6];
    ICM20948_SetBank(0);
    ICM20948_ReadRegs(ICM_B0_GYRO_XOUT_H, buf, 6);

    out->x = (int16_t)((buf[0] << 8) | buf[1]);
    out->y = (int16_t)((buf[2] << 8) | buf[3]);
    out->z = (int16_t)((buf[4] << 8) | buf[5]);
}

/**
 * @brief  Read raw magnetometer values from EXT_SLV_SENS_DATA registers.
 *
 * The ICM I2C master auto-reads AK09916 data and stores it starting
 * at EXT_SLV_SENS_DATA_00 (0x3B). Layout:
 *   [0] ST1    [1,2] HXL,HXH    [3,4] HYL,HYH
 *   [5,6] HZL,HZH    [7] ST2
 *
 * AK09916 data is LITTLE-ENDIAN (LOW byte first, unlike accel/gyro).
 *
 * @return true if data was ready, false if DRDY bit was not set
 */
bool ICM20948_ReadMagRaw(ICM_RawData *out)
{
    uint8_t buf[8];
    ICM20948_SetBank(0);
    ICM20948_ReadRegs(ICM_B0_EXT_SLV_SENS_DATA_00, buf, 8);

    if (!(buf[0] & 0x01)) {  /* ST1 bit0 = DRDY */
        return false;  /* data not ready yet */
    }

    /* Little-endian combine: LOW then HIGH */
    out->x = (int16_t)((buf[2] << 8) | buf[1]);  /* HXH:HXL */
    out->y = (int16_t)((buf[4] << 8) | buf[3]);  /* HYH:HYL */
    out->z = (int16_t)((buf[6] << 8) | buf[5]);  /* HZH:HZL */

    /* buf[7] = ST2 — reading it releases the AK09916 data lock */
    /* (Already captured in buf[7], nothing more needed here) */

    return true;
}

/* =========================================================
 *  SECTION 7 — Converted (physical unit) reads
 * ========================================================= */

/**
 * @brief  Get accelerometer in g (gravity units).
 */
void ICM20948_GetAccel_g(ICM_FloatData *out)
{
    ICM_RawData raw;
    ICM20948_ReadAccelRaw(&raw);
    out->x = (float)raw.x / ACCEL_SENS_2G;
    out->y = (float)raw.y / ACCEL_SENS_2G;
    out->z = (float)raw.z / ACCEL_SENS_2G;
}

/**
 * @brief  Get gyroscope in degrees/second.
 */
void ICM20948_GetGyro_dps(ICM_FloatData *out)
{
    ICM_RawData raw;
    ICM20948_ReadGyroRaw(&raw);
    out->x = (float)raw.x / GYRO_SENS_250DPS;
    out->y = (float)raw.y / GYRO_SENS_250DPS;
    out->z = (float)raw.z / GYRO_SENS_250DPS;
}

/**
 * @brief  Get magnetometer in µT.
 * @return true if data was ready, false otherwise
 */
bool ICM20948_GetMag_uT(ICM_FloatData *out)
{
    ICM_RawData raw;
    if (!ICM20948_ReadMagRaw(&raw)) return false;
    out->x = (float)raw.x * MAG_SENS_UT_PER_LSB;
    out->y = (float)raw.y * MAG_SENS_UT_PER_LSB;
    out->z = (float)raw.z * MAG_SENS_UT_PER_LSB;
    return true;
}

/**
 * @brief  Read die temperature in degrees Celsius.
 *
 * Formula from datasheet §8.31:
 *   TEMP_degC = ((TEMP_OUT - RoomTemp_Offset) / Temp_Sensitivity) + 21
 *   Where RoomTemp_Offset = 0, Temp_Sensitivity = 333.87 LSB/°C
 */
float ICM20948_ReadTemp_C(void)
{
    uint8_t buf[2];
    ICM20948_SetBank(0);
    ICM20948_ReadRegs(ICM_B0_TEMP_OUT_H, buf, 2);

    int16_t raw_temp = (int16_t)((buf[0] << 8) | buf[1]);
    return ((float)raw_temp / 333.87f) + 21.0f;
}

/**
 * @brief  Read all sensors in one call. Populates all fields in ICM_Data.
 */
void ICM20948_ReadAll(ICM_Data *data)
{
    /* Accel */
    ICM20948_ReadAccelRaw(&data->accel_raw);
    data->accel_g.x = (float)data->accel_raw.x / ACCEL_SENS_2G;
    data->accel_g.y = (float)data->accel_raw.y / ACCEL_SENS_2G;
    data->accel_g.z = (float)data->accel_raw.z / ACCEL_SENS_2G;

    /* Gyro */
    ICM20948_ReadGyroRaw(&data->gyro_raw);
    data->gyro_dps.x = (float)data->gyro_raw.x / GYRO_SENS_250DPS;
    data->gyro_dps.y = (float)data->gyro_raw.y / GYRO_SENS_250DPS;
    data->gyro_dps.z = (float)data->gyro_raw.z / GYRO_SENS_250DPS;

    /* Magnetometer (non-blocking) */
    ICM_FloatData mag;
    if (ICM20948_GetMag_uT(&mag)) {
        data->mag_uT = mag;
    }

    /* Temperature */
    data->temp_C = ICM20948_ReadTemp_C();
}
