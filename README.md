# fpga-embedded-system-project
Designed and implemented an embedded system on an FPGA (Intel Cyclone V SoC) using a Nios II soft-core processor.
## Architecture
- FPGA: Intel Cyclone V SoC (DE1-SoC)
- Processor: Nios II/e (soft-core)
- Memory: External SDRAM
- Clock: PLL (143 MHz)

## Key Concepts
- Memory-mapped I/O
- Real-time control systems
- State persistence using static variables
- Hardware-software co-design

## Functionality
- Switch-controlled system behavior
- Real-time pattern generation on 7-segment displays
- Timer-based and stateful pattern execution

## Security Perspective (IMPORTANT)
This system highlights potential research directions in embedded security:
- Memory-mapped I/O vulnerabilities
- Fault injection possibilities in timing logic
- Side-channel considerations in FPGA-based systems
