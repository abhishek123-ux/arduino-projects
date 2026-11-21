# Arduino Projects

Sensor-based embedded systems built on Arduino Uno.

| Project | Sensors / parts | What it does |
|---|---|---|
| [Blind Walking Aid](blind_walking_aid) | Ultrasonic sensor, buzzer | Detects obstacles and beeps faster as they get closer |
| [Temperature & Humidity Monitor](temp_humidity_monitor) | DHT11, relay, LED | Logs readings and switches a fan / warning LED when limits are crossed |
| [Automatic Street Light](street_light_automation) | LDR, LED / relay | Turns the light on at dusk and off at dawn, with hysteresis to avoid flicker |
| [Joystick Servo Control](joystick_servo_control) | Analog joystick, servo motors | Moves servos in real time to follow the joystick |

## How to run

1. Open the `.ino` file in the Arduino IDE (each sketch is in a folder with the same name, as the IDE expects).
2. Install any library listed at the top of the sketch (**Tools → Manage Libraries**). Only the DHT project needs one: *DHT sensor library* by Adafruit.
3. Select **Board → Arduino Uno** and the right port, then upload.
4. Open the Serial Monitor at **9600 baud** to see live readings.

Pin numbers are listed at the top of each sketch.

<!-- Add a photo or circuit diagram for each project, e.g. ![Blind walking aid](blind_walking_aid/photo.jpg) -->
