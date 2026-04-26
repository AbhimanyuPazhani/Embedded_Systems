/*
 * led.c
 *
 *  Created on: Apr 21, 2026
 *      Author: CITI
 */


#include <stdint.h>
#include "led.h"

/* Base addresses (WBA series) */
#define RCC_BASE        0x46020C00U
#define GPIOA_BASE      0x42020000U
#define GPIOB_BASE      0x42020400U

/* RCC register - STM32WBA GPIOs are on AHB2 (Offset 0x4C) */
#define RCC_AHB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x4C))

/* GPIO registers */
#define GPIOA_BSRR      (*(volatile uint32_t*)(GPIOA_BASE + 0x18))
#define GPIOB_BSRR      (*(volatile uint32_t*)(GPIOB_BASE + 0x18))

#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOB_MODER     (*(volatile uint32_t*)(GPIOB_BASE + 0x00))

/* Push Pull */
#define GPIOA_OTYPER    (*(volatile uint32_t*)(GPIOA_BASE + 0x04))
#define GPIOB_OTYPER    (*(volatile uint32_t*)(GPIOB_BASE + 0x04))

void led_init_all(void)
{
    /* 1. Enable GPIOA and GPIOB clocks on the correct AHB2 bus */
    RCC_AHB2ENR |= (1 << 0); // GPIOA
    RCC_AHB2ENR |= (1 << 1); // GPIOB

    /* Small delay for clock stabilization */
    for(volatile int i=0; i<1000; i++);

    /* Configure Push-pull */
    GPIOA_OTYPER &= ~(1 << 9);
    GPIOB_OTYPER &= ~(1 << 4);
    GPIOB_OTYPER &= ~(1 << 8);

    /* Configure PA9 (Green) as Output */
    GPIOA_MODER &= ~(3 << (9 * 2));
    GPIOA_MODER |=  (1 << (9 * 2));

    /* Configure PB4 (Blue) as Output */
    GPIOB_MODER &= ~(3 << (4 * 2));
    GPIOB_MODER |=  (1 << (4 * 2));

    /* Configure PB8 (Red) as Output */
    GPIOB_MODER &= ~(3 << (8 * 2));
    GPIOB_MODER |=  (1 << (8 * 2));

    /* Turn OFF all LEDs initially */
    led_off(LED_GREEN);
    led_off(LED_BLUE);
    led_off(LED_RED);
}

void led_on(uint8_t led)
{
    /* 2. Nucleo LEDs are Active High. We must SET the bottom 16 bits */
    switch(led)
    {
        case LED_GREEN:
            GPIOA_BSRR = (1 << 9); // SET (HIGH)
            break;
        case LED_BLUE:
            GPIOB_BSRR = (1 << 4); // SET (HIGH)
            break;
        case LED_RED:
            GPIOB_BSRR = (1 << 8); // SET (HIGH)
            break;
    }
}

void led_off(uint8_t led)
{
    /* 2. Nucleo LEDs are Active High. We must RESET using the top 16 bits */
    switch(led)
    {
        case LED_GREEN:
            GPIOA_BSRR = (1 << (9 + 16)); // RESET (LOW)
            break;
        case LED_BLUE:
            GPIOB_BSRR = (1 << (4 + 16)); // RESET (LOW)
            break;
        case LED_RED:
            GPIOB_BSRR = (1 << (8 + 16)); // RESET (LOW)
            break;
    }
}
