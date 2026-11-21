/*
 * Blind Walking Aid
 *
 * Measures the distance to the nearest obstacle with an ultrasonic
 * sensor and warns the user with a buzzer. The closer the obstacle,
 * the faster the beeping. A vibration motor can be connected to the
 * same output pin (through a transistor) instead of, or along with,
 * the buzzer.
 *
 * Hardware (change the pins to match your circuit):
 *   Ultrasonic sensor (HC-SR04): TRIG -> D9, ECHO -> D10, VCC -> 5V, GND -> GND
 *   Buzzer / vibration motor     : D8
 */

const int TRIG_PIN   = 9;
const int ECHO_PIN   = 10;
const int BUZZER_PIN = 8;

const int WARN_DISTANCE_CM = 100;   // start warning below this distance
const int STOP_DISTANCE_CM = 25;    // continuous tone below this distance

long readDistanceCm() {
  // Send a 10 microsecond trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Echo pulse width = time for sound to go and come back.
  // Timeout of 30 ms (about 5 m) so the loop never gets stuck.
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;     // nothing in range

  // Speed of sound = 0.0343 cm/us, divide by 2 for the round trip
  return duration * 0.0343 / 2;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long distance = readDistanceCm();

  Serial.print("Distance: ");
  if (distance < 0) Serial.println("out of range");
  else { Serial.print(distance); Serial.println(" cm"); }

  if (distance > 0 && distance <= STOP_DISTANCE_CM) {
    digitalWrite(BUZZER_PIN, HIGH);           // very close: continuous alert
    delay(100);
  } else if (distance > 0 && distance <= WARN_DISTANCE_CM) {
    // Beep interval grows with distance: closer -> faster beeps
    int gap = map(distance, STOP_DISTANCE_CM, WARN_DISTANCE_CM, 80, 600);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(60);
    digitalWrite(BUZZER_PIN, LOW);
    delay(gap);
  } else {
    digitalWrite(BUZZER_PIN, LOW);            // path is clear
    delay(100);
  }
}
