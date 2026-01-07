#include "MX1508_C3.h"

MX1508::MX1508(uint8_t pinIN1, uint8_t pinIN2,
               uint8_t resolutionBits,
               uint32_t freqHz)
: _pinIN1(pinIN1),
  _pinIN2(pinIN2),
  _resBits(resolutionBits),
  _freqHz(freqHz)
{
  if (_resBits < 1)  _resBits = 1;
  if (_resBits > 14) _resBits = 14;

  _maxPWM = (1u << _resBits) - 1u;

  // Configure pins as outputs
  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);

  // Attach PWM to pins (auto-assigns channels internally in core 3.x)
  bool ok1 = ledcAttach(_pinIN1, _freqHz, _resBits);
  bool ok2 = ledcAttach(_pinIN2, _freqHz, _resBits);

  if (!ok1 || !ok2) {
    Serial.println("Error: Failed to attach LEDC to pins!");
    // Fallback: set pins low
    digitalWrite(_pinIN1, LOW);
    digitalWrite(_pinIN2, LOW);
  }

  // Initialize to stop
  ledcWrite(_pinIN1, 0);
  ledcWrite(_pinIN2, 0);
}

void MX1508::motorStop() {
  ledcWrite(_pinIN1, 0);
  ledcWrite(_pinIN2, 0);
}

void MX1508::motorBrake() {
  ledcWrite(_pinIN1, _maxPWM);
  ledcWrite(_pinIN2, _maxPWM);
}

void MX1508::motorGo(uint16_t pwmVal) {
  if (pwmVal > _maxPWM) pwmVal = _maxPWM;
  ledcWrite(_pinIN1, pwmVal);
  ledcWrite(_pinIN2, 0);
}

void MX1508::motorRev(uint16_t pwmVal) {
  if (pwmVal > _maxPWM) pwmVal = _maxPWM;
  ledcWrite(_pinIN1, 0);
  ledcWrite(_pinIN2, pwmVal);
}