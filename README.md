# MX1508_ESP32 Library

A lightweight Arduino library for controlling MX1508 dual H-bridge motor drivers on ESP32 microcontrollers (tested on ESP32-C3).

## Features
- PWM speed control (8-bit resolution, 5 kHz default).
- Motor inversion support (runtime-configurable).
- Built-in robot movement functions (forward, turn, etc.).
- Serial command interface for easy testing.

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
