/*
 * tmp117.c
 *
 *  Created on: May 9, 2026
 *      Author: CITI
 */




#include "tmp117.h"

/* ───────────── Platform I2C Abstraction ───────────── */
/* These are implemented in main.c using STM32 HAL */
extern int TMP117_Platform_I2C_Write(void *handle, uint8_t addr, uint8_t reg, const uint8_t *data, uint16_t len);
extern int TMP117_Platform_I2C_Read(void *handle, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len);
extern void TMP117_Platform_Delay(uint32_t ms);

/* ───────────── Internal Helpers ───────────── */

static TMP117_Status_t tmp117_write_reg16(TMP117_Handle_t *dev, uint8_t reg, uint16_t val)
{
    uint8_t buf[2] = { (uint8_t)(val >> 8), (uint8_t)(val & 0xFF) };
    for (uint8_t attempt = 0; attempt < TMP117_MAX_RETRIES; attempt++) {
        if (TMP117_Platform_I2C_Write(dev->i2c_handle, dev->addr, reg, buf, 2) == 0) {
            return TMP117_OK;
        }
        TMP117_Platform_Delay(2);
    }
    return TMP117_ERR_I2C;
}

static TMP117_Status_t tmp117_read_reg16(TMP117_Handle_t *dev, uint8_t reg, uint16_t *val)
{
    uint8_t buf[2];
    for (uint8_t attempt = 0; attempt < TMP117_MAX_RETRIES; attempt++) {
        if (TMP117_Platform_I2C_Read(dev->i2c_handle, dev->addr, reg, buf, 2) == 0) {
            *val = (uint16_t)(buf[0] << 8 | buf[1]);
            return TMP117_OK;
        }
        TMP117_Platform_Delay(2);
    }
    return TMP117_ERR_I2C;
}

/* ───────────── Public API ───────────── */

TMP117_Status_t TMP117_Init(TMP117_Handle_t *dev)
{
    if (!dev || !dev->i2c_handle) return TMP117_ERR_I2C;

    /* Soft reset the sensor */
    TMP117_Status_t st = tmp117_write_reg16(dev, TMP117_REG_CONFIG, TMP117_CFG_SOFT_RESET);
    if (st != TMP117_OK) return st;
    TMP117_Platform_Delay(5);

    /* Verify Device ID */
    uint16_t dev_id = 0;
    st = tmp117_read_reg16(dev, TMP117_REG_DEVICE_ID, &dev_id);
    if (st != TMP117_OK) return st;
    if (dev_id != TMP117_DEVICE_ID_VAL) return TMP117_ERR_DEVICE_ID;

    /* --- CONTINUOUS MODE CHANGE --- */
    /* Tell the sensor to run continuously, average 8 samples, and output every 1 second */
    st = tmp117_write_reg16(dev, TMP117_REG_CONFIG,
                            TMP117_CFG_MOD_CC | TMP117_CFG_AVG_8 | TMP117_CFG_CONV_1S);
    if (st != TMP117_OK) return st;

    dev->initialized = true;
    return TMP117_OK;
}

TMP117_Status_t TMP117_Read(TMP117_Handle_t *dev, float *temp)
{
    if (!dev || !dev->initialized || !temp) return TMP117_ERR_I2C;

    /* --- CONTINUOUS MODE CHANGE --- */
    /* * No trigger commands, no waiting for DATA_READY.
     * The sensor is updating this register in the background.
     * We just read whatever the latest value is.
     */
    uint16_t raw = 0;
    TMP117_Status_t st = tmp117_read_reg16(dev, TMP117_REG_TEMP_RESULT, &raw);
    if (st != TMP117_OK) return st;

    /* Convert to Celsius */
    int16_t raw_signed = (int16_t)raw;
    *temp = (float)raw_signed * TMP117_RESOLUTION;

    return TMP117_OK;
}
