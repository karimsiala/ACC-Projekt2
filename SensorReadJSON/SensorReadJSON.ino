#include <TFMPlus.h>  // Include TFMini Plus Library
#include <ArduinoJson.h>  // Include ArduinoJson Library

TFMPlus tfmP1, tfmP2, tfmP3;  // Create TFMini Plus objects for each sensor

void setupSensor(TFMPlus &sensor, HardwareSerial &port) {
  port.begin(115200);  // Initialize TFMPlus device serial port.
  delay(20);           // Give port time to initialize
  sensor.begin(&port); // Initialize device library object and pass device serial port to the object.
}

void readSensorData(TFMPlus &sensor, String sensorName) {
  int16_t tfDist = 0;  // Distance to object in centimeters
  int16_t tfFlux = 0;  // Strength or quality of return signal
  int16_t tfTemp = 0;  // Internal temperature of Lidar sensor chip

  StaticJsonDocument<200> jsonDoc;  // Create a JSON document

  if (sensor.getData(tfDist, tfFlux, tfTemp)) {
    jsonDoc["sensor"] = sensorName;
    jsonDoc["distance"] = tfDist;
    jsonDoc["flux"] = tfFlux;
    jsonDoc["temperature"] = tfTemp;
  } else {
    jsonDoc["sensor"] = sensorName;
    jsonDoc["error"] = "Data read failed";
  }

  serializeJson(jsonDoc, Serial);  // Serialize JSON to serial
  Serial.println();  // New line after JSON data
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
  readSensorData(tfmP1, "Sensor1");
  readSensorData(tfmP2, "Sensor2");
  readSensorData(tfmP3, "Sensor3");
}
