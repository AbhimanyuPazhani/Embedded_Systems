/*
 * app.cpp
 *
 *  Created on: Jan 24, 2026
 *      Author: CITI
 */



#include "app.hpp"
#include "led.hpp"
#include "timer.hpp"

extern "C" {
#include "gpio.h"
#include "tim.h"
}

static uint8_t tickCount = 0;

void App_Run(void)
{
    LED_Init();
    Timer_Init();
    Timer_Start();

    while (1)
    {
        // Idle loop
        // All logic handled in timer interrupt
    }
}

void Timer_Callback()
{
    tickCount++;

    if (tickCount <= 3)
    {
        LED_On();
    }
    else
    {
        LED_Off();
    }

    if (tickCount >= 4)
    {
        tickCount = 0;
    }
}

