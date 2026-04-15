#include "stm32f4xx.h"

extern uint32_t SystemCoreClock;

namespace CustomLED {

class LED {
public:
    static void Init() {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
        GPIOC->MODER = (GPIOC->MODER & ~(0x3U << 26)) | (0x1U << 26);
        GPIOC->OTYPER &= ~(1U << 13);
        GPIOC->OSPEEDR &= ~(0x3U << 26);
        GPIOC->PUPDR &= ~(0x3U << 26);
    }

    static void On() {
        GPIOC->BSRR = (1U << (13 + 16));
    }

    static void Off() {
        GPIOC->BSRR = (1U << 13);
    }
};

}

volatile uint32_t msTicks = 0;

extern "C" void SysTick_Handler(void) {
    msTicks++;
}

void Delay_ms(uint32_t ms) {
    uint32_t start = msTicks;
    while ((msTicks - start) < ms) {}
}

int main(void)
{
    SysTick_Config(SystemCoreClock / 1000U);

    CustomLED::LED::Init();

    while (1) {
        CustomLED::LED::On();
        Delay_ms(375);
        CustomLED::LED::Off();
        Delay_ms(125);
    }
}
