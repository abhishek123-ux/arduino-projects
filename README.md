# Arduino Projects

Sensor-based embedded systems built on Arduino Uno.

| Project | Sensors / parts | What it does |
|---|---|---|
| [Blind Walking Aid](blind_walking_aid.ino) | Ultrasonic sensor, buzzer | Detects obstacles and beeps faster as they get closer |
| [Temperature & Humidity Monitor](temp_humidity_monitor.ino) | DHT11, relay, LED | Logs readings and switches a fan / warning LED when limits are crossed |
| [Automatic Street Light](street_light_automation.ino) | LDR, LED / relay | Turns the light on at dusk and off at dawn, with hysteresis to avoid flicker |
| [Joystick Servo Control](joystick_servo_control.ino) | Analog joystick, servo motors | Moves servos in real time to follow the joystick |

## How to run

1. Download the `.ino` file and open it in the Arduino IDE (it will offer to put it in a folder with the same name; click OK).
2. Install any library listed at the top of the sketch (**Tools → Manage Libraries**). Only the DHT project needs one: *DHT sensor library* by Adafruit.
3. Select **Board → Arduino Uno** and the right port, then upload.
4. Open the Serial Monitor at **9600 baud** to see live readings.

Pin numbers are listed at the top of each sketch.
