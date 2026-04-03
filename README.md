# SoPC System Design with Nios II/e on Cyclone V FPGA
This repository contains the development of a Microcontroller Introduction Laboratory (EE604P) from the National University of Engineering. The project focuses on designing and implementing a System on Programmable Chip (SoPC) using the Nios II/e soft-core processor on a DE1-SoC platform.

---

## 🛠️ Technical Specifications
* **Hardware:** Intel Cyclone V SoC FPGA (5CSEMA5F31C6).
* **Processor:** Nios II/e (Economy version) operating at **143 MHz**.
* **Clock Generation:** A **PLL (Phase-Locked Loop)** block generates the 143 MHz signal from a 50 MHz input.
* **Memory:** **External SDRAM** is utilized for program execution because C-compiled executables exceed the 4 KB on-chip memory capacity.
* **Development Tools:** * **Intel Quartus Prime & Platform Designer:** Used to define the hardware architecture.
    * **Nios II Software Build Tools for Eclipse:** Used for C language compilation and debugging.

---

## 🚀 Project Description
The primary goal was to migrate control logic previously implemented in Assembly to high-level **ANSI C**. The `lights.c` program interacts with 8 switches (SW7 to SW0) and seven-segment displays via **SN7447 BCD-to-7-segment decoders**.

### Operating Modes
The system supports five modes based on switch combinations:

| Mode | Switch (Control) | Display Pattern | Delay |
| :--- | :--- | :--- | :--- |
| **0** | Only SW0 or none | All displays off (FFFF) | N/A |
| **1** | SW1 ON | Cyclic timer from 01:59 to 00:00 | 0.2s |
| **2** | SW1 & SW3 ON | Left rotation of the pattern "12345678" | 1.0s |
| **3** | SW3 & SW5 ON | Right rotation of the pattern "87654321" | 1.0s |
| **4** | SW5 & SW7 ON | Blinking patterns "1234" and "5678" | 1.0s |

### State Persistence
A fundamental requirement is that dynamic patterns (timer and rotations) must **resume execution exactly where they left off** if the switch combination is changed and then returned to the previous state. This is achieved using **global static variables** (`static`) to store internal indices and counters.

---

## 📂 Code Structure
The `lights.c` source code includes:
* **I/O Management:** Use of `IORD` and `IOWR` macros to interface with `SWITCHES_BASE` and `LEDS_BASE`.
* **Wrapper Functions:** `delay_0_2s()` and `delay_ls()` which call `usleep()` with calculated microsecond values.
* **Selection Logic:** Bitwise masks (e.g., `sw & 0xFE`) ensure only relevant bits determine the operating mode, ignoring "don't care" positions.

```c
// Example of state persistence in lights.c
static alt_u8 estado_sw31 = 0; // Persistent index for left rotation
static alt_u16 minutos = 1;    // Persistent timer state
