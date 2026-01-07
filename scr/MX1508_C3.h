#pragma once
#include <Arduino.h>

// Simple, safe MX1508 wrapper for ESP32-C3
class MX1508 {
  public:
    // Auto channel assignment, 8-bit @ 5 kHz by default
    MX1508(uint8_t pinIN1, uint8_t pinIN2,
           uint8_t resolutionBits = 8,
           uint32_t freqHz = 5000);

    // Direction + speed
    void motorGo(uint16_t pwmVal);   // 0..maxPWM
    void motorRev(uint16_t pwmVal);  // 0..maxPWM

    // Stops
    void motorStop();   // both low, free run
    void motorBrake();  // both high, active brake
    void stopMotor() { motorStop(); }   // backward compatible

    // Helpers
    uint16_t maxPWM() const { return _maxPWM; }

  private:
    uint8_t  _pinIN1;
    uint8_t  _pinIN2;
    uint8_t  _resBits;
    uint32_t _freqHz;
    uint16_t _maxPWM;
};