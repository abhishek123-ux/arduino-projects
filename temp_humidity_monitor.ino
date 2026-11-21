/*
 * Temperature & Humidity Monitoring System
 *
 * Reads temperature and humidity from a DHT11 sensor every 2 seconds,
 * prints them on the Serial Monitor, and switches outputs when readings
 * cross set limits:
 *   - temperature above TEMP_LIMIT     -> fan/relay ON (D7)
 *   - humidity above HUMIDITY_LIMIT     -> warning LED ON (D6)
 *
 * Library: "DHT sensor library" by Adafruit
 *          (Arduino IDE -> Tools -> Manage Libraries -> search "DHT")
 *
 * Hardware (change the pins to match your circuit):
 *   DHT11 data -> D2 (with a 10k pull-up to 5V if using a bare sensor)
 *   Relay / fan driver -> D7
 *   LED (with 220 ohm resistor) -> D6
 */
#include <DHT.h>

#define DHT_PIN   2
#define DHT_TYPE  DHT11

const int FAN_PIN = 7;
const int LED_PIN = 6;

const float TEMP_LIMIT     = 30.0;  // degrees C
const float HUMIDITY_LIMIT = 70.0;  // percent
const float HYSTERESIS     = 1.0;   // avoids rapid ON/OFF switching near the limit

DHT dht(DHT_PIN, DHT_TYPE);
bool fanOn = false, ledOn = false;

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  Serial.println("Temperature & Humidity Monitor started");
}

void loop() {
  delay(2000);                       // DHT11 needs ~1 s between readings

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();   // Celsius

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11 - check wiring");
    return;
  }

  // Temperature control with hysteresis
  if (!fanOn && temperature > TEMP_LIMIT) fanOn = true;
  else if (fanOn && temperature < TEMP_LIMIT - HYSTERESIS) fanOn = false;

  // Humidity warning with hysteresis
  if (!ledOn && humidity > HUMIDITY_LIMIT) ledOn = true;
  else if (ledOn && humidity < HUMIDITY_LIMIT - HYSTERESIS) ledOn = false;

  digitalWrite(FAN_PIN, fanOn ? HIGH : LOW);
  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);

  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(" C  |  Humidity: ");
  Serial.print(humidity, 1);
  Serial.print(" %  |  Fan: ");
  Serial.print(fanOn ? "ON" : "OFF");
  Serial.print("  |  Humidity alert: ");
  Serial.println(ledOn ? "ON" : "OFF");
}
