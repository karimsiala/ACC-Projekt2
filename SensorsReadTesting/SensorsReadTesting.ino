#include <TFMPlus.h>  // Include TFMini Plus Library

TFMPlus tfmP1, tfmP2, tfmP3;  // Create TFMini Plus objects for each sensor

const bool debugMode = false;  // Set to false for normal operation with sensors

void setupSensor(TFMPlus &sensor, HardwareSerial &port) {
  port.begin(115200);
  delay(20);
  sensor.begin(&port);
}

void readSensorDataAndPrint(TFMPlus &sensor, uint8_t sensorId) {
  int16_t tfDist;

  if (sensor.getData(tfDist)) {
    // Successfully read the distance
    Serial.print("Sensor ");
    Serial.print(sensorId);
    Serial.print(" Distance: ");
    Serial.println(tfDist);
  } else {
    // Error in reading distance
    Serial.print("Error reading sensor ");
    Serial.println(sensorId);
  }
}

void setup() {
  Serial.begin(115200);
  delay(20);

  pinMode(LED_BUILTIN, OUTPUT);  // Set LED as output for error indication

  // Initialize sensors
  setupSensor(tfmP1, Serial1);
  setupSensor(tfmP2, Serial2);
  setupSensor(tfmP3, Serial3);
}

void loop() {
  // Read sensor data and print to Serial Monitor
  readSensorDataAndPrint(tfmP1, 1);  // Sensor ID 1
  readSensorDataAndPrint(tfmP2, 2);  // Sensor ID 2
  readSensorDataAndPrint(tfmP3, 3);  // Sensor ID 3

  digitalWrite(LED_BUILTIN, LOW);  // Turn off error LED after reading
  delay(1000);  // Wait for a second before the next read cycle
}
