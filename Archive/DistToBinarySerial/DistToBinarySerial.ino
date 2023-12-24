#include <TFMPlus.h>  // Include TFMini Plus Library

TFMPlus tfmP1, tfmP2, tfmP3;  // Create TFMini Plus objects for each sensor

const bool debugMode = true;  // Set to true for debugging without sensors


void setupSensor(TFMPlus &sensor, HardwareSerial &port) {
  if (!debugMode) {
    port.begin(115200);
    delay(20);
    sensor.begin(&port);
  }
}

void sendSensorDistanceBinary(TFMPlus &sensor, uint8_t sensorId) {
  int16_t tfDist;

  // Attempt to get data from the sensor
  if (!debugMode && sensor.getData(tfDist)) {
    // Successfully read distance from sensor
  } else {
    // In case of failure or if in debug mode, simulate a distance
    tfDist = (debugMode) ? random(50, 200) : -1;
    digitalWrite(LED_BUILTIN, (tfDist == -1) ? HIGH : LOW);  // Indicate error with LED if -1
  }

  // Send sensor ID
  Serial.write(sensorId);

  // Send the distance as two bytes in little-endian format
  Serial.write(lowByte(tfDist));  // Send low byte first
  Serial.write(highByte(tfDist)); // Send high byte second

  // Send terminator
  Serial.write('\r'); // Carriage return as terminator
}


void setup() {
  Serial.begin(115200);
  delay(20);

  pinMode(LED_BUILTIN, OUTPUT);  // Set LED as output for error indication

  setupSensor(tfmP1, Serial1);
  setupSensor(tfmP2, Serial2);
  setupSensor(tfmP3, Serial3);
}

void loop() {
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 50) {
    lastTime = millis();

    sendSensorDistanceBinary(tfmP1, 1);  // Sensor ID 1
    sendSensorDistanceBinary(tfmP2, 2);  // Sensor ID 2
    sendSensorDistanceBinary(tfmP3, 3);  // Sensor ID 3

    digitalWrite(LED_BUILTIN, LOW);  // Reset error indication LED
  }
}
