/*
 * Joystick to Servo Control
 *
 * Reads the X and Y axes of an analog joystick and moves two servo
 * motors to match, in real time (pan/tilt). Pressing the joystick
 * button centres both servos.
 *
 * Library: Servo (built into the Arduino IDE)
 *
 * Hardware (change the pins to match your circuit):
 *   Joystick VRx -> A0, VRy -> A1, SW -> D2, +5V -> 5V, GND -> GND
 *   Servo X signal -> D9, Servo Y signal -> D10
 *   (Power servos from a separate 5V supply if they jitter; join the grounds.)
 *
 * If you used only one servo, remove the Y-axis lines.
 */
#include <Servo.h>

const int JOY_X_PIN  = A0;
const int JOY_Y_PIN  = A1;
const int JOY_SW_PIN = 2;
const int SERVO_X_PIN = 9;
const int SERVO_Y_PIN = 10;

const int DEADZONE = 20;     // ignore small movements around the centre (512)
const float SMOOTHING = 0.3; // 0..1, lower = smoother but slower response

Servo servoX, servoY;
float angleX = 90, angleY = 90;

int readAxis(int pin) {
  int value = analogRead(pin);              // 0..1023, centre ~512
  if (abs(value - 512) < DEADZONE) value = 512;
  return map(value, 0, 1023, 0, 180);       // convert to servo angle
}

void setup() {
  pinMode(JOY_SW_PIN, INPUT_PULLUP);        // button reads LOW when pressed
  servoX.attach(SERVO_X_PIN);
  servoY.attach(SERVO_Y_PIN);
  servoX.write(90);
  servoY.write(90);
  Serial.begin(9600);
}

void loop() {
  int targetX, targetY;

  if (digitalRead(JOY_SW_PIN) == LOW) {
    targetX = 90;                           // button pressed: centre
    targetY = 90;
  } else {
    targetX = readAxis(JOY_X_PIN);
    targetY = readAxis(JOY_Y_PIN);
  }

  // Move gradually towards the target to reduce jitter
  angleX += SMOOTHING * (targetX - angleX);
  angleY += SMOOTHING * (targetY - angleY);

  servoX.write((int)angleX);
  servoY.write((int)angleY);

  Serial.print("X angle: ");
  Serial.print((int)angleX);
  Serial.print("  |  Y angle: ");
  Serial.println((int)angleY);
  delay(15);                                // servos update about every 15-20 ms
}
