# Embedded Systems Projects and Learning Repository

This repository contains my hands-on work, experiments, and mini-projects in embedded systems development using STM32 microcontrollers. The content is primarily based on structured learning from FastBit Academy courses, along with my own implementations and explorations.

---
## Learning Progression

```text
001 C Fundamentals
        │
        ▼
002 Microcontroller Embedded C Programming
        │
        ▼
003 Embedded Systems Programming on ARM Cortex-M3/M4
        │
        ▼
004 Bare Metal Projects
        │
        ▼
005 Personal Projects
        │
        ▼
BLE Stack

---

## Development Platforms

* STM32F722ZE Nucleo Board
* STM32F411CEU6 BlackPill Board

---

## What This Repository Includes

### 1. Embedded Systems Programming (Beginner Level)

* GPIO programming
* Peripheral interfacing
* Basic driver development
* Register-level programming

### 2. ARM Cortex-M3/M4 Programming

* Processor architecture understanding
* Thread mode vs Handler mode
* Privileged vs Unprivileged Access
* MSP (Main Stack Pointer) and PSP (Process Stack Pointer)
* Exception handling (SysTick, PendSV, Fault handlers)
* Stack management and context switching

### 3. Mini Projects and Implementations

#### Simple Task Scheduler (RTOS Concept)

* Implemented a basic round-robin scheduler with multiple tasks
* Manual task stack initialization in SRAM
* Context switching using PSP
* SysTick-based time slicing
* Understanding of how RTOS works internally

---

## Key Learning Outcomes

* Strong understanding of ARM Cortex-M internal working
* Practical experience with low-level register programming
* Deep understanding of task scheduling and context switching
* Ability to design embedded systems without relying on high-level libraries
* Hands-on debugging using ST-Link

---

## Tools and Environment

* STM32CubeIDE
* ST-Link V2 Debugger
* Embedded C Programming
* ARM Cortex-M Architecture

---

## Future Work

* Bare-metal embedded systems development (FastBit Academy course)
* Advanced driver development
* RTOS-based application development
* Sensor interfacing and real-time applications

---

## Note

This repository is focused on learning and understanding core embedded concepts through practical implementation. Each module reflects my progression in mastering low-level embedded system design.
