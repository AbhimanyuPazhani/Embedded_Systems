//Perfect 👍 Abhimanyu — this is the **bare-metal interrupt-driven button program** from the FastBit course (which originally targets the **STM32F407 Discovery** board).
//
//Let’s now **adapt it for your STM32F722ZE Nucleo board**, where:
//
//* **User button** → **PC13**
//* **Blue LED** → **PB7**
//* Interrupt line for PC13 → **EXTI line 13**, handled by **EXTI15_10_IRQHandler()** (not EXTI0).
//
//We’ll rewrite everything accordingly, keeping the same register-level logic — just fixing base addresses and bit positions.
//
//---
//
//## 🧩 Full Working Code — Bare-Metal for STM32F722ZE Nucleo
//
//```c
/**
  ******************************************************************************
  * @file    main.c
  * @brief   Bare-metal EXTI interrupt test for NUCLEO-F722ZE
  ******************************************************************************
*/

#include <stdint.h>
#include <stdio.h>

// Global shared variables between main loop and ISR
volatile uint8_t g_button_pressed = 0;
uint32_t g_button_press_count = 0;

// Peripheral register addresses (from RM0431 Reference Manual)
volatile uint32_t *const pClkCtrlReg_AHB1  = (uint32_t*)(0x40023800 + 0x30); // RCC_AHB1ENR
volatile uint32_t *const pClkCtrlReg_APB2  = (uint32_t*)(0x40023800 + 0x44); // RCC_APB2ENR

volatile uint32_t *const pGPIOBModeReg     = (uint32_t*)(0x40020400 + 0x00); // GPIOB_MODER
volatile uint32_t *const pGPIOBOutReg      = (uint32_t*)(0x40020400 + 0x14); // GPIOB_ODR
volatile uint32_t *const pGPIOCModeReg     = (uint32_t*)(0x40020800 + 0x00); // GPIOC_MODER

volatile uint32_t *const pEXTIMaskReg      = (uint32_t*)(0x40013C00 + 0x00); // EXTI_IMR
volatile uint32_t *const pEXTIEdgeReg      = (uint32_t*)(0x40013C00 + 0x0C); // EXTI_FTSR (falling edge)
volatile uint32_t *const pEXTIPendReg      = (uint32_t*)(0x40013C00 + 0x14); // EXTI_PR

volatile uint32_t *const pSYSCFG_EXTICR4   = (uint32_t*)(0x40013800 + 0x14); // SYSCFG_EXTICR4
volatile uint32_t *const pNVIC_IRQEnReg    = (uint32_t*)0xE000E100;           // NVIC_ISER0

// Function prototypes
void button_init(void);
void EXTI15_10_IRQHandler(void);

int main(void)
{
    button_init();

    while (1)
    {
        // Disable interrupt mask temporarily
        *pEXTIMaskReg &= ~(1 << 13);

        if (g_button_pressed)
        {
            for (volatile uint32_t i = 0; i < 500000 / 2; i++); // debounce delay
            g_button_press_count++;

            // Toggle LED
            *pGPIOBOutReg ^= (1 << 7);

            g_button_pressed = 0;
        }

        // Re-enable interrupt mask
        *pEXTIMaskReg |= (1 << 13);
    }
}

// ------------------- Initialization -------------------
void button_init(void)
{
    // 1. Enable GPIOB (LED) and GPIOC (Button) clocks
    *pClkCtrlReg_AHB1 |= (1 << 1); // GPIOB
    *pClkCtrlReg_AHB1 |= (1 << 2); // GPIOC

    // 2. Enable SYSCFG clock on APB2 (for external interrupt line mapping)
    *pClkCtrlReg_APB2 |= (1 << 14);

    // 3. Configure PB7 as output
    *pGPIOBModeReg &= ~(3 << (7 * 2)); // clear bits
    *pGPIOBModeReg |=  (1 << (7 * 2)); // set as output

    // 4. Configure PC13 as input (default, but ensure bits are cleared)
    *pGPIOCModeReg &= ~(3 << (13 * 2));

    // 5. Map EXTI13 line to Port C in SYSCFG_EXTICR4
    *pSYSCFG_EXTICR4 &= ~(0xF << 4); // clear EXTI13 field
    *pSYSCFG_EXTICR4 |=  (0x2 << 4); // 0x2 = Port C

    // 6. Configure EXTI13 for falling edge trigger (button active-low)
    *pEXTIEdgeReg |= (1 << 13);

    // 7. Unmask interrupt line 13
    *pEXTIMaskReg |= (1 << 13);

    // 8. Enable IRQ in NVIC (EXTI15_10 line, position 40)
    volatile uint32_t *pNVIC_ISER1 = (uint32_t*)0xE000E104; // ISER1 handles IRQs 32–63
    *pNVIC_ISER1 |= (1 << (40 - 32)); // enable EXTI15_10_IRQn
}

// ------------------- ISR Handler -------------------
void EXTI15_10_IRQHandler(void)
{
    g_button_pressed = 1;             // Flag set
    *pEXTIPendReg |= (1 << 13);       // Clear pending bit (write 1 to clear)
}
//```
//
//---
//
//## 🧠 Explanation
//
//| Component              | Description                                          | Address               |
//| ---------------------- | ---------------------------------------------------- | --------------------- |
//| **User Button (PC13)** | Connected to EXTI line 13, triggered on falling edge | GPIOC, EXTI13         |
//| **Blue LED (PB7)**     | Output, toggled on each button press                 | GPIOB                 |
//| **SYSCFG_EXTICR4**     | Maps EXTI13 to Port C                                | `0x40013814`          |
//| **NVIC**               | EXTI15_10 IRQ enable via ISER1                       | `bit 8` (for line 40) |
//
//---
//
//## ✅ What Happens
//
//* When you **press USER button (B1)** → PC13 goes **low**.
//* EXTI line 13 detects falling edge → **calls `EXTI15_10_IRQHandler()`**.
//* ISR sets `g_button_pressed = 1`.
//* Main loop sees the flag → toggles PB7 LED and clears the flag.
//
//---
//
//## ⚡ Optimization Test
//
//Now you can:
//
//1. Change optimization flag in CubeIDE
//   → **Project → Properties → C/C++ Build → Settings → Tool Settings → Optimization**
//2. Try:
//
//   * **O0**: everything works (no optimization)
//   * **O2/O3**: without `volatile`, interrupt flag or GPIO reads may “disappear”
//   * Add `volatile` → always works
//
//You can also remove `volatile` from `g_button_pressed` and see it fail under `-O3`.
//That’s the same FastBit demo effect.
//
//---
//
//Would you like me to add an **LED ON while button held, OFF when released** version (instead of toggle-on-press)? It’s useful for understanding how EXTI and GPIO reads behave differently.
