/*
 * tmp117.h
 *
 *  Created on: May 9, 2026
 *      Author: CITI
 */


#ifndef TMP117_H
#define TMP117_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define TMP117_I2C_ADDR_GND    0x48
#define TMP117_I2C_ADDR_VDD    0x49
#define TMP117_I2C_ADDR_SDA    0x4A
#define TMP117_I2C_ADDR_SCL    0x4B

#define TMP117_REG_TEMP_RESULT 0x00
#define TMP117_REG_CONFIG      0x01
#define TMP117_REG_DEVICE_ID   0x0F

#define TMP117_DEVICE_ID_VAL   0x0117

#define TMP117_CFG_DATA_READY  (1u << 13)
#define TMP117_CFG_MOD_CC      (0u << 10)
#define TMP117_CFG_MOD_OS      (3u << 10)  /**< One-shot mode */
#define TMP117_CFG_AVG_8       (1u << 5)
#define TMP117_CFG_CONV_1S     (4u << 7)
#define TMP117_CFG_SOFT_RESET  (1u << 1)

#define TMP117_RESOLUTION      0.0078125f
#define TMP117_MAX_RETRIES     3

typedef enum {
    TMP117_OK = 0,
    TMP117_ERR_I2C,
    TMP117_ERR_DEVICE_ID,
    TMP117_ERR_TIMEOUT,
    TMP117_ERR_SELF_TEST
} TMP117_Status_t;

typedef struct {
    void    *i2c_handle;
    uint8_t  addr;
    bool     initialized;
} TMP117_Handle_t;

TMP117_Status_t TMP117_Init(TMP117_Handle_t *dev);
TMP117_Status_t TMP117_Read(TMP117_Handle_t *dev, float *temp);

#ifdef __cplusplus
}
#endif
#endif /* TMP117_H */
