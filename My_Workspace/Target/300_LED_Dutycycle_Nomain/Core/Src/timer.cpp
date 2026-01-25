/*
 * timer.cpp
 *
 *  Created on: Jan 24, 2026
 *      Author: CITI
 */

#include "timer.hpp"
#include "stm32f4xx_hal.h"

extern "C" TIM_HandleTypeDef htim2;

void Timer_Init()
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 16000 - 1;   // 1 ms tick
    htim2.Init.Period = 125 - 1;        // 125 ms
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;

    HAL_TIM_Base_Init(&htim2);
    HAL_TIM_Base_Start_IT(&htim2);
}

void Timer_Start()
{
    HAL_TIM_Base_Start_IT(&htim2);
}

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        Timer_Callback();
    }
}



