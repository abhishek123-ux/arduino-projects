/*
 * Automatic Street Light Control
 *
 * Uses an LDR (light-dependent resistor) to sense ambient light and
 * switches the street light ON when it gets dark and OFF when it gets
 * bright. Two thresholds (hysteresis) stop the light from flickering
 * at dusk, and readings are averaged to ignore brief shadows or
 * headlights.
 *
 * Hardware (change the pins to match your circuit):
 *   LDR + 10k resistor voltage divider -> A0
 *     (5V -- LDR -- A0 -- 10k -- GND : brighter light = higher reading)
 *   Street light LED (with 220 ohm resistor) or relay module -> D9
 */

const int LDR_PIN   = A0;
const int LIGHT_PIN = 9;

const int DARK_THRESHOLD   = 300;  // below this -> it is dark, turn ON
const int BRIGHT_THRESHOLD = 450;  // above this -> it is bright, turn OFF
const int SAMPLES          = 10;   // readings averaged per decision

bool lightOn = false;

int readLightLevel() {
  long sum = 0;
  for (int i = 0; i < SAMPLES; i++) {
    sum += analogRead(LDR_PIN);
    delay(20);
  }
  return sum / SAMPLES;
}

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int level = readLightLevel();

  if (!lightOn && level < DARK_THRESHOLD) {
    lightOn = true;
    Serial.println("Dark detected  -> street light ON");
  } else if (lightOn && level > BRIGHT_THRESHOLD) {
    lightOn = false;
    Serial.println("Light detected -> street light OFF");
  }

  digitalWrite(LIGHT_PIN, lightOn ? HIGH : LOW);

  Serial.print("Light level: ");
  Serial.print(level);
  Serial.print("  |  Light: ");
  Serial.println(lightOn ? "ON" : "OFF");
  delay(500);
}
