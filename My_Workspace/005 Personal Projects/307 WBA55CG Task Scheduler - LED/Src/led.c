/*
 * led.c
 *
 *  Created on: Apr 21, 2026
 *      Author: CITI
 */


#include <stdint.h>
#include "led.h"

/* Base addresses (WBA series) */
#define RCC_BASE        0x58024400U
#define GPIOA_BASE      0x42020000U
#define GPIOB_BASE      0x42020400U

/* RCC register */
#define RCC_AHB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x4C))

/* GPIO registers */
#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile uint32_t*)(GPIOA_BASE + 0x14))

#define GPIOB_MODER     (*(volatile uint32_t*)(GPIOB_BASE + 0x00))
#define GPIOB_ODR       (*(volatile uint32_t*)(GPIOB_BASE + 0x14))

void led_init_all(void)
{
    /* Enable GPIOA and GPIOB clocks */
    RCC_AHB2ENR |= (1 << 0); // GPIOA
    RCC_AHB2ENR |= (1 << 1); // GPIOB

    /* Configure PA9 (Green LED) as output */
    GPIOA_MODER &= ~(3 << (9 * 2));
    GPIOA_MODER |=  (1 << (9 * 2));

    /* Configure PB4 (Blue LED) as output */
    GPIOB_MODER &= ~(3 << (4 * 2));
    GPIOB_MODER |=  (1 << (4 * 2));

    /* Configure PB8 (Red LED) as output */
    GPIOB_MODER &= ~(3 << (8 * 2));
    GPIOB_MODER |=  (1 << (8 * 2));

    /* Turn OFF all LEDs initially */
    led_off(LED_GREEN);
    led_off(LED_BLUE);
    led_off(LED_RED);
}

void led_on(uint8_t led)
{
    switch(led)
    {
        case LED_GREEN:
            GPIOA_ODR |= (1 << 9);
            break;

        case LED_BLUE:
            GPIOB_ODR |= (1 << 4);
            break;

        case LED_RED:
            GPIOB_ODR |= (1 << 8);
            break;
    }
}

void led_off(uint8_t led)
{
    switch(led)
    {
        case LED_GREEN:
            GPIOA_ODR &= ~(1 << 9);
            break;

        case LED_BLUE:
            GPIOB_ODR &= ~(1 << 4);
            break;

        case LED_RED:
            GPIOB_ODR &= ~(1 << 8);
            break;
    }
}
