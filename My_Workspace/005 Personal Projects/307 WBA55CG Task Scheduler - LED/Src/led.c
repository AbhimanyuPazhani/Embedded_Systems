/*
 * led.c
 *
 *  Created on: Apr 21, 2026
 *      Author: CITI
 */


#include <stdint.h>
#include "led.h"

/* Base addresses (WBA series) */
#define RCC_BASE 		0x46020C00U // From the RM0493 User manual
//#define RCC_BASE        0x58024400U This is for STM32F407x Disc Board AHB1 Address
#define GPIOA_BASE      0x42020000U
#define GPIOB_BASE      0x42020400U

/* RCC register */
//#define RCC_AHB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x4C))
#define RCC_AHB4ENR		 (*(volatile uint32_t*)(RCC_BASE + 0xE0))

/* GPIO registers */
#define GPIOA_BSRR 		(*(volatile uint32_t*)(GPIOA_BASE + 0x18))


#define GPIOB_BSRR 		(*(volatile uint32_t*)(GPIOB_BASE + 0x18))

#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
//#define GPIOA_ODR       (*(volatile uint32_t*)(GPIOA_BASE + 0x14))
//
#define GPIOB_MODER     (*(volatile uint32_t*)(GPIOB_BASE + 0x00))
//#define GPIOB_ODR       (*(volatile uint32_t*)(GPIOB_BASE + 0x14))

/* Push Pull */
#define GPIOA_OTYPER (*(volatile uint32_t*)(GPIOA_BASE + 0x04))
#define GPIOB_OTYPER (*(volatile uint32_t*)(GPIOB_BASE + 0x04))

void led_init_all(void)
{
    /* Enable GPIOA and GPIOB clocks FIRST */
	RCC_AHB4ENR |= (1 << 0); // GPIOA
	RCC_AHB4ENR |= (1 << 1); // GPIOB

    /* Small delay (important for clock stabilization) */
    for(volatile int i=0; i<1000; i++);

    /* Push-pull */
    GPIOA_OTYPER &= ~(1 << 9);
    GPIOB_OTYPER &= ~(1 << 4);
    GPIOB_OTYPER &= ~(1 << 8);

    /* Configure PA9 */
    GPIOA_MODER &= ~(3 << (9 * 2));
    GPIOA_MODER |=  (1 << (9 * 2));

    /* Configure PB4 */
    GPIOB_MODER &= ~(3 << (4 * 2));
    GPIOB_MODER |=  (1 << (4 * 2));

    /* Configure PB8 */
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
           GPIOA_BSRR = (1 << (9 + 16)); // RESET (LOW)

            break;

        case LED_BLUE:
            GPIOB_BSRR = (1 << (4 + 16));
            break;

        case LED_RED:
            GPIOB_BSRR = (1 << (8 + 16));
            break;
    }
}

void led_off(uint8_t led)
{
    switch(led)
    {
        case LED_GREEN:
            GPIOA_BSRR = (1 << 9); // SET (HIGH)
            break;

        case LED_BLUE:
            GPIOB_BSRR = (1 << 4);
            break;

        case LED_RED:
            GPIOB_BSRR = (1 << 8);
            break;
    }
}
