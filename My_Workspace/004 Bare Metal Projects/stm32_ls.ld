ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM  (rwx): ORIGIN = 0x20000000, LENGTH = 128K
}

__max_heap_size = 0x400; /* A symbol declaration . not a variable !!! */
__max_stack_size = 0x200; /* A symbol declaration . not a variable !!! */

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text)
        *(.rodata) 
        _etext = .;
       /* end_of_text = .; store the updated location counter value in to a symbol  'end_of_test' */
    } > FLASH AT > FLASH 

    .data :
    {
        _sdata = .;
       /* start_of_data = 0x20000000; Assign a value to a symbol 'start_of_data'  */
        *(.data)
        _edata = .;
    } > SRAM AT > FLASH

    _sidata = LOADADDR(.data);

    .bss :
    {
        _sbss = .;
        *(.bss)
        _ebss = .;
    }> SRAM
}