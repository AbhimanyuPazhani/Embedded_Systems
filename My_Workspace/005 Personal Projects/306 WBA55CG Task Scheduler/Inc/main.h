/*
 * main.h
 *
 *  Created on: Apr 21, 2026
 *      Author: CITI
 */



#ifndef MAIN_H_
#define MAIN_H_

#define MAX_TASKS 4

/* Stack memory calculations */
#define SIZE_TASK_STACK     1024U
#define SIZE_SCHED_STACK    1024U

/* CRITICAL FIX: Added missing 0 to match STM32 SRAM address 0x20000000 */
#define SRAM_START          0x20000000U
#define SIZE_SRAM           (64 * 1024) //SRAM in the WBA55 is split into two parts so I just mentioned small amount of region in SRAM1 here, because this is enough for this task.
#define SRAM_END            ((SRAM_START) + (SIZE_SRAM))

/* Task stacks grow downwards from the end of SRAM */
#define T1_STACK_START      SRAM_END
#define T2_STACK_START      ((SRAM_END) - (1 * SIZE_TASK_STACK))
#define T3_STACK_START      ((SRAM_END) - (2 * SIZE_TASK_STACK))
#define T4_STACK_START      ((SRAM_END) - (3 * SIZE_TASK_STACK))
#define SCHED_STACK_START   ((SRAM_END) - (4 * SIZE_TASK_STACK))

#define TICK_HZ             1000U
#define HSI_CLOCK           16000000U
#define SYSTICK_TIM_CLK     HSI_CLOCK
#define DUMMY_XPSR          0x01000000U

#endif /* MAIN_H_ */
