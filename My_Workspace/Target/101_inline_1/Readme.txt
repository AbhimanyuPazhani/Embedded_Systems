# ARM Cortex-M Inline Assembly Example

## Description
This project demonstrates basic ARM Cortex-M assembly instructions
embedded inside C code using GCC inline assembly.

The program performs the following operations:
- Reads two 32-bit values from SRAM
- Adds the values using ARM registers
- Stores the result back into SRAM

This example is intended for learning **ARM Cortex-M3/M4 processor internals**
and is aligned with concepts taught in the *Embedded Systems Programming on
ARM Cortex-M3/M4* course by FastBit Academy.

---

## Target Hardware

- Development Board: Black Pill (STM32F411CEU6)
- MCU Core: ARM Cortex-M4
- Debugger: ST-Link V2
- Debug Interface: SWD
- IDE: STM32CubeIDE
- Toolchain: arm-none-eabi-gcc

The code was tested on a Black Pill STM32F411CEU6 board using ST-Link V2
for programming and debugging.

---

## Memory Usage

| Address       | Description            |
|--------------|------------------------|
| 0x20001000   | Operand 1 (SRAM)       |
| 0x20001004   | Operand 2 / Result     |

Both addresses fall within the internal SRAM region of the Cortex-M processor.

---

## Code Overview

The program uses inline ARM assembly instructions to:
- Load SRAM addresses into registers
- Read values from memory
- Perform addition using registers
- Store the result back to memory

Key ARM instructions used:
- `LDR`
- `ADD`
- `STR`

This highlights the **load–store architecture** of ARM Cortex-M processors.

---

## Key Concepts Demonstrated

- ARM Cortex-M register usage (R0, R1, R2)
- Inline assembly with GCC
- SRAM address space (0x20000000 region)
- Interaction between C code and assembly
- Basic debugging using memory view

---

## How to Test

1. Flash the code to the target using ST-Link V2.
2. Before execution, write test values to SRAM addresses:
   - `0x20001000`
   - `0x20001004`
3. Run the program.
4. Observe the result stored at `0x20001004` using the debugger memory view.

---

## Notes

- This project focuses on **processor-level understanding**, not HAL or
  peripheral programming.
- No RTOS or CMSIS abstraction is used.
- Intended purely for educational and learning purposes.
