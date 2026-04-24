/*
 * led.h
 *
 *  Created on: Apr 21, 2026
 *      Author: CITI
 */


#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define LED_GREEN   0   // PA9
#define LED_BLUE    1   // PB4
#define LED_RED     2   // PB8

void led_init_all(void);
void led_on(uint8_t led);
void led_off(uint8_t led);

#endif
