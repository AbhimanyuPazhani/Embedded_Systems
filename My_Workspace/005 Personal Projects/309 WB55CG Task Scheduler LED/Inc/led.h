/*
 * led.h
 *
 *  Created on: May 2, 2026
 *      Author: CITI
 */

#ifndef LED_H_
#define LED_H_

#include <stdint.h>

/* Correct mapping */
#define LED_BLUE   4   // PA4
#define LED_GREEN  0   // PB0
#define LED_RED    1   // PB1

void led_init_all(void);
void led_on(uint8_t led_no);
void led_off(uint8_t led_no);

#endif
