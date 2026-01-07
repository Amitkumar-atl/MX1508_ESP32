#include "MX1508_C3.h"

/* ========== PINS ========== */
#define L_IN1 2
#define L_IN2 1
#define R_IN1 4
#define R_IN2 3

#define LEFT_MOTOR_INVERTED  1
#define RIGHT_MOTOR_INVERTED 1

// Auto‑channel, 8‑bit, 5 kHz
MX1508 leftMotor(L_IN1, L_IN2);
MX1508 rightMotor(R_IN1, R_IN2);

/* ========== LOW LEVEL ========== */
void leftForward(uint8_t s) {
#if LEFT_MOTOR_INVERTED
  leftMotor.motorRev(s);
#else
  leftMotor.motorGo(s);
#endif
}

void leftBackward(uint8_t s) {
#if LEFT_MOTOR_INVERTED
  leftMotor.motorGo(s);
#else
  leftMotor.motorRev(s);
#endif
}

void rightForward(uint8_t s) {
#if RIGHT_MOTOR_INVERTED
  rightMotor.motorRev(s);
#else
  rightMotor.motorGo(s);
#endif
}

void rightBackward(uint8_t s) {
#if RIGHT_MOTOR_INVERTED
  rightMotor.motorGo(s);
#else
  rightMotor.motorRev(s);
#endif
}

/* ========== ROBOT MOVES ========== */
void forward(uint8_t s) {
  leftForward(s);
  rightForward(s);
}

void backward(uint8_t s) {
  leftBackward(s);
  rightBackward(s);
}

void leftTurn(uint8_t s) {
  leftMotor.motorStop();    // pivot turn
  rightForward(s);
}

void rightTurn(uint8_t s) {
  rightMotor.motorStop();   // pivot turn
  leftForward(s);
}

void stopRobot() {
  leftMotor.motorStop();
  rightMotor.motorStop();
}

void brakeRobot() {
  leftMotor.motorBrake();
  rightMotor.motorBrake();
}

/* ========== COMMAND HANDLER ========== */
void handleCommand(String cmd) {
  cmd.trim();
  cmd.toUpperCase();

  int speed = 180;
  int sp = cmd.indexOf(' ');
  if (sp > 0) {
    String speedStr = cmd.substring(sp + 1);
    if (speedStr.length() > 0 && isDigit(speedStr.charAt(0))) {
      speed = constrain(speedStr.toInt(), 0, 255);
    } else {
      Serial.println("Error: Invalid speed value");
      return;
    }
    cmd = cmd.substring(0, sp);
  }

  if (cmd == "F") forward(speed);
  else if (cmd == "B") backward(speed);
  else if (cmd == "L") leftTurn(speed);
  else if (cmd == "R") rightTurn(speed);
  else if (cmd == "S") stopRobot();
  else if (cmd == "BRAKE") brakeRobot();
  else {
    Serial.println("Error: Unknown command");
    return;
  }

  Serial.println("CMD OK: " + cmd + " S:" + String(speed));
}

/* ========== SETUP & LOOP ========== */
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32-C3 ROBOT CMD READY");
  Serial.println("Commands: F/B/L/R/S/BRAKE [speed]");
  Serial.println("e.g. F 200");
}

void loop() {
  if (Serial.available()) {
    handleCommand(Serial.readStringUntil('\n'));
  }
}