#include <stdint.h>

/* Memory */
#define SRAM_START  0x20000000U
#define SRAM_SIZE   (128 * 1024)
#define SRAM_END    (SRAM_START + SRAM_SIZE)
#define STACK_START SRAM_END

/* Linker symbols */
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _la_data;

/* Prototype */
int main(void);
void __libc_init_array(void);

/* Handlers */
void Reset_Handler(void);
void Default_Handler(void);

/* Cortex handlers */
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

/* IRQ (only few shown, rest default handled automatically) */
void WWDG_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void)__attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler(void)__attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));

/* Vector Table */
uint32_t vectors[] __attribute__((section(".isr_vector"))) =
{
    STACK_START,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    (uint32_t)MemManage_Handler,
    (uint32_t)BusFault_Handler,
    (uint32_t)UsageFault_Handler,
    0,0,0,0,
    (uint32_t)SVC_Handler,
    (uint32_t)DebugMon_Handler,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,

    /* IRQs (keep minimal for now) */
    (uint32_t)WWDG_IRQHandler,
    (uint32_t)PVD_IRQHandler,
    (uint32_t)TAMP_STAMP_IRQHandler,
    (uint32_t)RTC_WKUP_IRQHandler,
    (uint32_t)RCC_IRQHandler,
    (uint32_t)EXTI0_IRQHandler,
    (uint32_t)DMA1_Stream0_IRQHandler,
    (uint32_t)USART1_IRQHandler,
};

/* Default Handler */
void Default_Handler(void)
{
    while(1);
}

/* Reset Handler */
void Reset_Handler(void)
{
    /* Copy .data */
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pSrc = (uint8_t*)&_la_data;
    uint8_t *pDst = (uint8_t*)&_sdata;

    for(uint32_t i=0; i<size; i++)
        *pDst++ = *pSrc++;

    /* Clear .bss */
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;

    for(uint32_t i=0; i<size; i++)
        *pDst++ = 0;
    __libc_init_array();

    main();
}