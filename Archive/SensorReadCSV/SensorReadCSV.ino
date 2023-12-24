#include <TFMPlus.h>  // Include TFMini Plus Library

TFMPlus tfmP1, tfmP2, tfmP3;  // Create TFMini Plus objects for each sensor

// Define start and end markers
const uint8_t startMarker = 0xFF;
const uint8_t endMarker = 0xFE;

void setupSensor(TFMPlus &sensor, HardwareSerial &port) {
  port.begin(115200);  // Initialize TFMPlus device serial port.
  delay(20);           // Give port time to initialize
  sensor.begin(&port); // Initialize device library object and pass device serial port to the object.
}

void sendSensorDataBinary(TFMPlus &sensor, uint8_t sensorId) {
  int16_t tfDist = 0;  // Distance to object in centimeters
  int16_t tfFlux = 0;  // Strength or quality of return signal
  int16_t tfTemp = 0;  // Internal temperature of Lidar sensor chip

  if (sensor.getData(tfDist, tfFlux, tfTemp)) {
    Serial.write(startMarker);
    Serial.write(sensorId);
    Serial.write((uint8_t*)&tfDist, sizeof(tfDist));
    Serial.write((uint8_t*)&tfFlux, sizeof(tfFlux));
    Serial.write((uint8_t*)&tfTemp, sizeof(tfTemp));
    Serial.write(endMarker);
  } else {
    // Send error packet
    Serial.write(startMarker);
    Serial.write(sensorId);
    tfDist = -1; // Error code for distance
    tfFlux = -1; // Error code for flux
    tfTemp = -1; // Error code for temperature
    Serial.write((uint8_t*)&tfDist, sizeof(tfDist));
    Serial.write((uint8_t*)&tfFlux, sizeof(tfFlux));
    Serial.write((uint8_t*)&tfTemp, sizeof(tfTemp));
    Serial.write(endMarker);
  }
}

void setup() {
  Serial.begin(115200); // Initialize terminal serial port
  delay(20);            // Give port time to initialize
  setupSensor(tfmP1, Serial1);
  setupSensor(tfmP2, Serial2);
  setupSensor(tfmP3, Serial3);
}

void loop() {
  delay(50); // Loop delay to match the 20Hz data frame rate
  sendSensorDataBinary(tfmP1, 1); // Sensor ID 1
  sendSensorDataBinary(tfmP2, 2); // Sensor ID 2
  sendSensorDataBinary(tfmP3, 3); // Sensor ID 3
}
