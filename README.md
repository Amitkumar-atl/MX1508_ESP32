# MX1508_ESP32 Library

A lightweight Arduino library for controlling MX1508 dual H-bridge motor drivers on ESP32 microcontrollers (tested on ESP32-C3).

## Features
- PWM speed control (8-bit resolution, 5 kHz default).
- Motor inversion support (runtime-configurable).
- Built-in robot movement functions (forward, turn, etc.).
- Serial command interface for easy testing.
  
## Hardware Connections
The MX1508 is a dual H-bridge module for controlling two DC motors. Connect it to your ESP32 as follows (adjust pins as needed in your code):

MX1508 Module Pins:

- IN1/IN2: Control inputs for Motor 1 (left motor in robot setups).
- IN3/IN4: Control inputs for Motor 2 (right motor in robot setups).
- VCC: Connect to 3.3V-5V (ESP32's 3.3V recommended for logic).
- GND: Connect to ESP32 GND.
- Motor Outputs: OUT1/OUT2 for Motor 1, OUT3/OUT4 for Motor 2. Connect your DC motors here.
- Power Supply: For motors, use a separate battery (e.g., 6-12V) connected to VM and GND on the MX1508. Do not power motors directly from ESP32 to avoid damage.
- ESP32 Connections Example (for a 2-wheel robot):

- ESP32 GPIO 2 → MX1508 IN1 (Left Motor IN1)
- ESP32 GPIO 1 → MX1508 IN2 (Left Motor IN2)
- ESP32 GPIO 4 → MX1508 IN3 (Right Motor IN1)
- ESP32 GPIO 3 → MX1508 IN4 (Right Motor IN2)
- Ensure no conflicts with UART pins (e.g., GPIO 1/3 are TX/RX; use alternatives if serial is needed).
Note: Verify your MX1508 module's pinout (some variants may differ). Test motor direction and use setInverted() if needed. Use a multimeter to confirm connections and avoid short circuits.

## Installation
- Via Arduino Library Manager: Search for "MX1508_ESP32".
- Manual: Download the ZIP from [GitHub Releases](https://github.com/Amitkumar-atl/MX1508_ESP32/releases), extract to `~/Arduino/libraries/`, and restart Arduino IDE.

## Usage
See the `examples/RobotControl` sketch for a full example.

## API Reference
- `MX1508(pinIN1, pinIN2, resBits=8, freqHz=5000)`: Constructor.
- `setInverted(bool invert)`: Set motor direction inversion.
- `motorGo(speed)`, `motorRev(speed)`: Drive forward/reverse.
- `motorStop()`, `motorBrake()`: Stop modes.

## License
MIT License. See LICENSE file.

## Contributing
Pull requests welcome! Test on your ESP32 variant.
