/*
 * led.c
 *
 *  Created on: May 2, 2026
 *      Author: CITI
 */


#include <stdint.h>
#include "led.h"

/* RCC AHB2 Enable Register */
#define RCC_AHB2ENR   (*(volatile uint32_t*)0x5800004C)

/* GPIOA Registers */
#define GPIOA_MODER   (*(volatile uint32_t*)0x48000000)
#define GPIOA_ODR     (*(volatile uint32_t*)0x48000014)

/* GPIOB Registers */
#define GPIOB_MODER   (*(volatile uint32_t*)0x48000400)
#define GPIOB_ODR     (*(volatile uint32_t*)0x48000414)

void led_init_all(void)
{
    /* 1. Enable GPIOA and GPIOB clock */
    RCC_AHB2ENR |= (1 << 0); // GPIOA
    RCC_AHB2ENR |= (1 << 1); // GPIOB
    //RCC_AHB2ENR |= (1 << 1); // GPIOB clock

    /* 2. Configure PA4 as output */
    GPIOA_MODER &= ~(3 << (2 * LED_GREEN)); // clear
    GPIOA_MODER |=  (1 << (2 * LED_GREEN)); // output mode

    /* 3. Configure PB0 and PB1 as output */
    GPIOB_MODER &= ~(3 << (2 * LED_BLUE));
    GPIOB_MODER |=  (1 << (2 * LED_BLUE));

    GPIOB_MODER &= ~(3 << (2 * LED_RED));
    GPIOB_MODER |=  (1 << (2 * LED_RED));

    /* Turn OFF all LEDs initially */
    GPIOA_ODR |= (1 << LED_BLUE);
    GPIOB_ODR |= (1 << LED_GREEN);
    GPIOB_ODR |= (1 << LED_RED);



}

void led_on(uint8_t led_no)
{
    if(led_no == LED_BLUE)
        GPIOA_ODR &= ~(1 << LED_BLUE);   // PA4
    else
        GPIOB_ODR &= ~(1 << led_no);     // PB0, PB1
}

void led_off(uint8_t led_no)
{
    if(led_no == LED_BLUE)
        GPIOA_ODR |= (1 << LED_BLUE);
    else
        GPIOB_ODR |= (1 << led_no);
}
