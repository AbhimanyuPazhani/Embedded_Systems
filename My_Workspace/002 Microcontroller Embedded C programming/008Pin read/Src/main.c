#include <stdint.h>

int main(void)
{
    // Define pointers to RCC, GPIOB (LED), and GPIOC (Button)
    volatile uint32_t *const pClkCtrlReg   = (uint32_t*)0x40023830; // RCC_AHB1ENR
    volatile uint32_t *const pPortBModeReg = (uint32_t*)0x40020400; // GPIOB_MODER
    volatile uint32_t *const pPortBOutReg  = (uint32_t*)0x40020414; // GPIOB_ODR

    volatile uint32_t *const pPortCModeReg = (uint32_t*)0x40020800; // GPIOC_MODER
    volatile uint32_t *const pPortCInReg   = (uint32_t*)0x40020810; // GPIOC_IDR

    // 1. Enable clock for GPIOB and GPIOC
    *pClkCtrlReg |= (1 << 1); // Enable GPIOB clock
    *pClkCtrlReg |= (1 << 2); // Enable GPIOC clock

    // 2. Set PB7 as output (14:15 bits -> 01)
    *pPortBModeReg &= ~(3 << (7 * 2)); // Clear bits
    *pPortBModeReg |=  (1 << (7 * 2)); // Set as output mode

    // 3. Set PC13 as input (26:27 bits -> 00)
    *pPortCModeReg &= ~(3 << (13 * 2)); // Already input by default, but clear anyway

    // 4. Simple loop to turn LED ON when button pressed (PC13 LOW)
    while (1)
    {
        uint32_t buttonState = (*pPortCInReg >> 13) & 0x1; // Read bit 13

        if (buttonState == 0) // Active low button pressed
        {
            *pPortBOutReg |= (1 << 7);  // Turn ON LED
        }
        else
        {
            *pPortBOutReg &= ~(1 << 7); // Turn OFF LED
        }
    }
}
