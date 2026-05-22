# ICM-20948 on STM32WB55CG — Complete Mentor Guide

**Hardware:** STM32WB55CG USB Dongle + SparkFun ICM-20948 9DoF IMU  
**Tools:** STM32CubeIDE, ST-Link, UART TTL Converter

---

## STEP 1 — Verify Hardware Connections

### ✅ Your wiring is CORRECT

Let me confirm each wire and explain why it is correct:

| ICM-20948 Pin | STM32WB55 Pin | Why |
|---|---|---|
| GND | GND | Common ground — essential for any circuit |
| VIN | 3V3 | ICM-20948 VDD range: 1.71V–3.6V. 3.3V is safe |
| MOSI | PA7 (CN1 Pin 10) | SPI1 Master Out Slave In — data from MCU to sensor |
| MISO | PA6 (CN1 Pin 9) | SPI1 Master In Slave Out — data from sensor to MCU |
| SCK | PA5 (CN1 Pin 8) | SPI1 Serial Clock — driven by MCU (master) |
| NSS/CS | PB2 → IMU_CS | Chip Select — pulled LOW to select the sensor |

**UART connections:**
| TTL Converter | STM32WB55 | Why |
|---|---|---|
| TXD | PA3 (LPUART1_RX) | Converter transmits → MCU receives |
| RXD | PA2 (LPUART1_TX) | MCU transmits → Converter receives |

> ⚠️ **VDDIO WARNING:** The ICM-20948 datasheet specifies VDDIO = 1.71V–1.95V for its I/O supply. However, the SparkFun breakout board includes a voltage regulator and level shifter, which is why it can accept 3.3V logic. This is safe with the breakout board.

> ⚠️ **UART polarity:** TTL TXD → MCU RX (PA3). Never TXD→TXD — that is the most common wiring mistake. Think of it like a conversation: one person talks (TX) into the other's ear (RX).

**Common beginner mistakes to avoid:**
- Mixing up MOSI and MISO (the sensor will produce all-zero data)
- Forgetting a common GND between the dongle and TTL converter
- Connecting TXD→TXD instead of TXD→RXD
- CS pin left floating (sensor will never respond)

---

## STEP 2 — Create STM32CubeIDE Project

1. Open **STM32CubeIDE**.
2. Go to **File → New → STM32 Project**.
3. In the board selector, type `STM32WB55CG` in the search box.
4. Select **P-NUCLEO-WB55** (or the USB dongle variant) → **Next**.
5. Project name: `ICM20948_SPI` (no spaces).
6. Targeted language: **C**.
7. Click **Finish**.
8. When asked "Initialize all peripherals with their default mode?" → click **Yes**.

---

## STEP 3 — Configure IOC File (CubeMX Perspective)

When your project opens, you will see the `.ioc` file (the graphical pin configurator). This is called the **CubeMX** perspective inside STM32CubeIDE.

### Open the IOC file

Double-click the `.ioc` file in the Project Explorer on the left side.

### Rename PB2 as IMU_CS

1. Find the chip diagram in the center.
2. Click on pin **PB2**.
3. Select **GPIO_Output** from the dropdown.
4. Right-click **PB2** → **Enter User Label** → type `IMU_CS` → press Enter.

This is why the code uses `IMU_CS_GPIO_Port` and `IMU_CS_Pin` instead of `GPIOB` and `GPIO_PIN_2`. CubeMX generates these convenient macros from the label.

---

## STEP 4 — Configure SPI1

Still inside the IOC file:

1. On the left panel, click **Connectivity → SPI1**.
2. Set **Mode** to `Full-Duplex Master`.
3. **DO NOT enable Hardware NSS** — leave NSS as `Disable`.
   - Why? We are doing manual chip select via PB2 (IMU_CS). Manual CS ensures the CS line stays LOW for the entire SPI transaction. Hardware NSS can de-assert between bytes, which confuses the ICM-20948.
4. Under **Configuration → Parameter Settings**:
   - **Frame Format:** Motorola
   - **Data Size:** 8 Bits
   - **First Bit:** MSB First (ICM-20948 sends MSB first — datasheet §6.5)
   - **Prescaler:** Set so that **Baud Rate ≤ 7.0 MHz**
     - If your system clock is 64 MHz: prescaler 16 → 4 MHz ✓
     - If your system clock is 32 MHz: prescaler 8 → 4 MHz ✓
   - **CPOL:** Low (Clock idle state is LOW)
   - **CPHA:** 1 Edge (data captured on first/rising edge)
   - This gives **SPI Mode 0** — the mode required by ICM-20948 (datasheet §6.5: "Data is latched on the rising edge of SCLK")
   - **CRC Calculation:** Disabled
   - **NSS Signal Type:** Software

> **SPI Mode cheat sheet:**
> - CPOL=0, CPHA=0 → Mode 0 → ICK idles LOW, sample on rising edge ✓

---

## STEP 5 — Configure GPIO

The IMU_CS pin (PB2) needs to be configured as a push-pull output:

1. Click on **PB2** in the pin diagram.
2. Confirm it is set to **GPIO_Output**.
3. On the left panel, go to **System Core → GPIO**.
4. Click on **PB2** in the GPIO table.
5. Set:
   - **GPIO output level:** High (CS starts HIGH = de-asserted = sensor not selected)
   - **GPIO mode:** Output Push Pull
   - **GPIO Pull-up/Pull-down:** No pull-up and no pull-down
   - **Maximum output speed:** High
   - **User Label:** `IMU_CS` (should already be set)

> **Why start CS HIGH?**  
> CS is active LOW. HIGH means the sensor is NOT selected. If CS were LOW at power-up, the sensor would be confused before initialisation even begins.

---

## STEP 6 — Configure LPUART1

1. On the left panel, click **Connectivity → LPUART1**.
2. Set **Mode** to `Asynchronous`.
3. Under **Configuration → Parameter Settings**:
   - **Baud Rate:** 115200 bps
   - **Word Length:** 8 Bits
   - **Parity:** None
   - **Stop Bits:** 1
   - **Data Direction:** Receive and Transmit
   - **Over Sampling:** 16 Samples
4. Confirm PA2 = LPUART1_TX and PA3 = LPUART1_RX (shown on pin diagram).

> **Why 115200?** It is the universally supported "fast" baud rate for terminal software. Fast enough for continuous sensor output, slow enough to be reliable without hardware flow control.

> **Common UART mistakes:**
> - Wrong baud rate on terminal → garbled text
> - TXD→TXD wiring → no data
> - No common GND between dongle and converter → floating signals

---

## STEP 7 — Configure Clock

1. Click the **Clock Configuration** tab at the top of the IOC editor.
2. Select **HSE** (external crystal) or **HSI** (internal oscillator) as your clock source.
3. Ensure **HCLK** is set to at least **32 MHz** (64 MHz recommended for full performance).
4. The tool will auto-calculate prescalers. If there is a conflict, click **Resolve Clock Issues**.
5. Verify the SPI clock is ≤ 7 MHz (check the SPI clock display).

---

## STEP 8 — Generate Code

1. Click **Project → Generate Code** (or press Alt+K).
2. Wait for the code generator to run.
3. When asked "Do you want to open the C/C++ perspective?" → click **Yes**.

CubeMX will create:
```
Core/
  Src/
    main.c          ← Your application code goes here
    spi.c           ← SPI1 HAL initialisation
    gpio.c          ← GPIO initialisation (includes IMU_CS)
    usart.c         ← LPUART1 initialisation
  Inc/
    main.h
    spi.h
    gpio.h
```

---

## STEP 9 — Paste Header File

1. In the **Project Explorer**, right-click on `Core/Inc/`.
2. Select **New → File**.
3. Filename: `icm20948.h`
4. Click **Finish**.
5. Paste the entire contents of the provided `icm20948.h` file.
6. Save with **Ctrl+S**.

**What this file does:**
- Defines all register addresses (so you never use magic numbers)
- Defines sensitivity constants for unit conversion
- Declares all public API functions so `main.c` can call them
- Defines the `ICM_Data` struct that holds all sensor readings

---

## STEP 10 — Paste Source File

1. Right-click on `Core/Src/`.
2. Select **New → File**.
3. Filename: `icm20948.c`
4. Click **Finish**.
5. Paste the entire contents of the provided `icm20948.c` file.
6. Save with **Ctrl+S**.

**Key functions explained:**

| Function | What it does |
|---|---|
| `ICM20948_WriteReg()` | Pulls CS low, sends address+data, pulls CS high |
| `ICM20948_ReadReg()` | Pulls CS low, sends address with READ bit set, receives 1 byte, CS high |
| `ICM20948_ReadRegs()` | Burst read — sends address, receives N bytes in one CS LOW cycle |
| `ICM20948_SetBank()` | Writes to REG_BANK_SEL (0x7F) to switch register banks |
| `ICM20948_Init()` | Full power-on sequence: reset, wake, configure, verify WHO_AM_I |
| `ICM20948_ReadAll()` | Reads all sensors and converts to physical units in one call |

---

## STEP 11 — Modify main.c

Open `Core/Src/main.c`. You will add code in specific marked sections that CubeMX creates for you. **Only add code between the `USER CODE BEGIN` and `USER CODE END` markers** — otherwise CubeMX will erase your code next time you regenerate.

### 11a — Add includes (near the top of main.c)

Find the section that says:
```c
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
```

Add:
```c
/* USER CODE BEGIN Includes */
#include "icm20948.h"
#include <stdio.h>
/* USER CODE END Includes */
```

### 11b — Add the printf redirect (for UART output)

Find:
```c
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
```

Add the following. This function intercepts every `printf()` call and sends it out through LPUART1:

```c
/* USER CODE BEGIN 0 */

/**
 * Redirect printf to LPUART1.
 * With this, every printf("...") call sends text to your serial terminal.
 */
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&hlpuart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

/* USER CODE END 0 */
```

> **Why this works:** The C standard library's `printf` calls `__io_putchar` for each character. By overriding it, we redirect all output to UART. This is called "retargeting" the C library.

### 11c — Declare variables (inside main, before the while loop)

Find the `/* USER CODE BEGIN 1 */` section inside the `main()` function:

```c
/* USER CODE BEGIN 1 */
ICM_Data   sensor_data;   /* All sensor readings go here */
uint8_t    who_am_i;      /* For verifying the sensor ID */
/* USER CODE END 1 */
```

### 11d — Initialise the sensor (after all HAL_Init calls, before the while loop)

Find `/* USER CODE BEGIN 2 */`:

```c
/* USER CODE BEGIN 2 */

printf("\r\n===== ICM-20948 SPI Driver =====\r\n");
printf("Initialising sensor...\r\n");

/* Verify WHO_AM_I */
who_am_i = ICM20948_WhoAmI();
printf("WHO_AM_I = 0x%02X (expected 0xEA)\r\n", who_am_i);

/* Full initialisation */
if (ICM20948_Init() != ICM_OK) {
    printf("FATAL: Sensor init failed! Check wiring.\r\n");
    while (1); /* halt */
}

printf("Starting sensor loop...\r\n\r\n");

/* USER CODE END 2 */
```

### 11e — Continuous sensor reading loop (inside while(1))

Find `/* USER CODE BEGIN 3 */` (this is inside the `while (1)` loop):

```c
/* USER CODE BEGIN 3 */

/* Read all sensors at once */
ICM20948_ReadAll(&sensor_data);

/* Print accelerometer */
printf("ACCEL: X=%.3f  Y=%.3f  Z=%.3f  [g]\r\n",
       sensor_data.accel_g.x,
       sensor_data.accel_g.y,
       sensor_data.accel_g.z);

/* Print gyroscope */
printf("GYRO:  X=%.2f  Y=%.2f  Z=%.2f  [dps]\r\n",
       sensor_data.gyro_dps.x,
       sensor_data.gyro_dps.y,
       sensor_data.gyro_dps.z);

/* Print magnetometer */
printf("MAG:   X=%.2f  Y=%.2f  Z=%.2f  [uT]\r\n",
       sensor_data.mag_uT.x,
       sensor_data.mag_uT.y,
       sensor_data.mag_uT.z);

/* Print temperature */
printf("TEMP:  %.2f C\r\n", sensor_data.temp_C);

printf("---\r\n");
HAL_Delay(100);  /* 10 Hz output rate — adjust as needed */

/* USER CODE END 3 */
```

---

## STEP 12 — Build and Flash

### Build

1. Click **Project → Build All** (or press **Ctrl+B**).
2. Watch the Console panel at the bottom. You want to see:
   ```
   Build Finished. 0 errors, 0 warnings.
   ```
3. If you see errors, the most common causes are:
   - Missing `#include "icm20948.h"` in main.c
   - `hspi1` not declared — add `extern SPI_HandleTypeDef hspi1;` at the top of icm20948.h *(already done in the provided file)*
   - `hlpuart1` not declared — add `extern UART_HandleTypeDef hlpuart1;` to main.c if needed

### Flash

1. Connect your ST-Link to the dongle via SWCLK, SWDIO, GND, 3V3.
2. Click the **Run** button (green play arrow) OR go to **Run → Run**.
3. If prompted, select **ST-LINK (OpenOCD)** as the debug probe.
4. The IDE will flash the firmware and reset the board.

---

## STEP 13 — Open Live Expressions

Live Expressions let you watch variables update in real time while debugging without stopping the program.

### Start a debug session

1. Click the **Debug** button (bug icon) instead of Run.
2. Click **Switch** if asked about perspectives.
3. The program will pause at `main()`.
4. Click the green **Resume** button (F8) to let it run.

### Add Live Expressions

1. In the top menu, click **Window → Show View → Live Expressions**.
2. Click **Add new expression** (the + button).
3. Add each of these:

```
sensor_data.accel_g.x
sensor_data.accel_g.y
sensor_data.accel_g.z
sensor_data.gyro_dps.x
sensor_data.gyro_dps.y
sensor_data.gyro_dps.z
sensor_data.mag_uT.x
sensor_data.mag_uT.y
sensor_data.mag_uT.z
sensor_data.temp_C
who_am_i
```

4. The values will update continuously as the program runs.

> **Tip:** Tilt the sensor and watch `accel_g.z` change from approximately +1.0g (flat) to near 0g (tilted 90°). That is gravity!

### Using breakpoints

1. Click in the grey margin left of a line number in `main.c` to set a breakpoint (red dot appears).
2. When the debugger hits the breakpoint, execution pauses.
3. Hover your mouse over any variable to see its current value in a tooltip.
4. Press **F8** to resume.

---

## STEP 14 — Read UART Output

### Open a serial terminal

**Windows:** Use PuTTY, Tera Term, or the built-in terminal in STM32CubeIDE.  
**Linux/Mac:** Use `screen /dev/ttyUSB0 115200` or minicom.

### Settings
- **Port:** The COM port of your TTL converter (check Device Manager on Windows)
- **Baud rate:** 115200
- **Data bits:** 8
- **Parity:** None
- **Stop bits:** 1
- **Flow control:** None

### Expected output (sensor flat on table)

```
===== ICM-20948 SPI Driver =====
Initialising sensor...
WHO_AM_I = 0xEA (expected 0xEA)
[ICM] WHO_AM_I = 0xEA ✓  ICM-20948 detected!
[ICM] AK09916 magnetometer found (ID=0x09)
[ICM] Initialisation complete!
Starting sensor loop...

ACCEL: X=0.012  Y=-0.008  Z=1.003  [g]
GYRO:  X=0.15   Y=-0.08   Z=0.12   [dps]
MAG:   X=12.45  Y=-8.23   Z=32.10  [uT]
TEMP:  28.4 C
---
ACCEL: X=0.011  Y=-0.007  Z=1.002  [g]
...
```

**What successful communication looks like:**
- WHO_AM_I = 0xEA exactly
- Accel Z ≈ +1.0g when flat (gravity!)
- Accel X, Y ≈ 0g when flat
- Gyro ≈ 0 dps when stationary (small noise is normal)
- Temperature ≈ room temperature

**What failed communication looks like:**
- WHO_AM_I = 0x00 → no data at all → check MISO, GND, power
- WHO_AM_I = 0xFF → MISO stuck high → check CS, SPI mode
- WHO_AM_I = 0xAA or random → SPI clock too fast, or CPOL/CPHA wrong
- All sensor values = 0 → sensor in sleep mode → check init sequence

---

## STEP 15 — Troubleshooting

### Problem: WHO_AM_I returns 0x00 or 0xFF

**Cause:** SPI communication is completely failing.  
**Steps:**
1. Check physical wiring — are MOSI/MISO/SCK/CS all connected?
2. Check GND — is there a common ground?
3. Check 3V3 power — is the sensor powered?
4. Verify SPI1 is enabled in CubeMX and the correct pins are shown.
5. Try reducing SPI prescaler (lower clock speed).
6. Use an oscilloscope or logic analyser on SCK — do you see clock pulses when the sensor is accessed?

### Problem: WHO_AM_I returns wrong value (not 0xEA)

**Cause:** SPI communication is happening but data is corrupted.  
**Steps:**
1. Check SPI mode — must be CPOL=0, CPHA=0 (Mode 0).
2. Check that MOSI and MISO are not swapped.
3. Verify SPI clock is ≤ 7 MHz.
4. Check that CS goes LOW before the transaction and HIGH after.

### Problem: Sensor values are always exactly zero

**Cause:** Sensor is in sleep mode, or data registers are being read before init.  
**Steps:**
1. Confirm `ICM20948_Init()` returned `ICM_OK`.
2. Confirm you called `ICM20948_WriteReg(ICM_B0_PWR_MGMT_1, 0x01)` to wake the sensor.
3. Add `HAL_Delay(100)` after the reset, before reading.

### Problem: Sensor values jump around erratically

**Cause:** Electrical noise, loose connections, or CS glitches.  
**Steps:**
1. Check all connections are firm.
2. Add 100nF bypass capacitors between VCC and GND near the sensor.
3. Shorten wires if possible.

### Problem: No UART output at all

**Cause:** Wrong COM port, wrong baud rate, or TX/RX swapped.  
**Steps:**
1. Verify TTL TXD → MCU PA3 (LPUART1_RX), not PA2.
2. Confirm baud rate is 115200 in both CubeMX and your terminal.
3. Check that LPUART1 is enabled and PA2/PA3 are shown as LPUART1_TX/RX in CubeMX.
4. Confirm `__io_putchar` is correctly redirecting to `hlpuart1`.

### Problem: Magnetometer returns zeros or doesn't initialise

**Cause:** I2C master not configured, or AK09916 not reset properly.  
**Steps:**
1. Confirm `ICM_I2C_MST_EN` is set in USER_CTRL.
2. Add a 50ms delay after enabling I2C master.
3. Soft-reset the AK09916 via CNTL3.
4. Check that I2C Slave 0 is configured to auto-read from address 0x3B.

### Problem: Sensor init fails after repeated power cycles

**Cause:** Sensor still in sleep from previous run, SCLK/nCS state at power-up.  
**Steps:**
1. Always write `ICM_DEVICE_RESET` (0x80) to PWR_MGMT_1 first, then wait 100ms.
2. Pull CS HIGH in the GPIO init (set initial output level to HIGH in CubeMX).

---

## Project Folder Structure

```
ICM20948_SPI/
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   ├── icm20948.h      ← ADD THIS FILE HERE
│   │   ├── spi.h
│   │   ├── usart.h
│   │   └── gpio.h
│   └── Src/
│       ├── main.c          ← MODIFY THIS FILE
│       ├── icm20948.c      ← ADD THIS FILE HERE
│       ├── spi.c
│       ├── usart.c
│       └── gpio.c
├── Drivers/
│   └── STM32WBxx_HAL_Driver/   ← Auto-generated, do not modify
└── ICM20948_SPI.ioc             ← CubeMX config file
```

---

## SPI Transaction Timing Reference

```
CS   ──┐     ┌──────────────────────────────┐     ┌──
       └─────┘                              └─────┘
              ↑ IMU_CS_LOW()              ↑ IMU_CS_HIGH()

SCK  ────┬─┬─┬─┬─┬─┬─┬─┬──────────────────────────────
         ↑ Data latched here (rising edge = CPOL=0, CPHA=0)

MOSI ────[  REG ADDR | 0x80  ][   DUMMY 0x00   ]────
MISO ────[  don't care       ][  REGISTER DATA  ]────
```

**Read transaction:** Send (reg | 0x80), receive 1 dummy byte then 1 data byte.  
**Write transaction:** Send (reg | 0x00) then the data byte.

---

## Sensitivity Reference

| Sensor | Full-Scale Range | Sensitivity | Units |
|---|---|---|---|
| Accelerometer | ±2g | 16384 LSB/g | Divide raw by 16384 to get g |
| Gyroscope | ±250 dps | 131 LSB/dps | Divide raw by 131 to get dps |
| Magnetometer | ±4900 µT | 0.15 µT/LSB | Multiply raw by 0.15 to get µT |

---

## Quick Reference: Register Banks

| Bank | Key Registers |
|---|---|
| Bank 0 | WHO_AM_I, PWR_MGMT, USER_CTRL, all data output registers |
| Bank 1 | Self-test registers, accelerometer offset registers |
| Bank 2 | GYRO_CONFIG, ACCEL_CONFIG, sample rate dividers |
| Bank 3 | I2C master control (for magnetometer access) |

**To switch banks:** Write to register 0x7F (REG_BANK_SEL) in any bank.  
`bits [5:4]` = bank number: 0x00=Bank0, 0x10=Bank1, 0x20=Bank2, 0x30=Bank3.
