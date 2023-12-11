#include <TFMPlus.h>  // Include TFMini Plus Library

TFMPlus tfmP1, tfmP2, tfmP3;  // Create TFMini Plus objects for each sensor

void setupSensor(TFMPlus &sensor, HardwareSerial &port) {
  port.begin(115200);  // Initialize TFMPLus device serial port.
  delay(20);           // Give port time to initalize
  sensor.begin(&port); // Initialize device library object and pass device serial port to the object.

  // Optional: Set frame rate or other configurations
  /*
  Serial.println("Data-Frame rate: ");
  if (sensor.sendCommand(SET_FRAME_RATE, FRAME_20)) {
    printf("%2uHz.\r\n", FRAME_20);
  } else sensor.printReply();
  */
}

void readSensorData(TFMPlus &sensor) {
  int16_t tfDist = 0;  // Distance to object in centimeters
  int16_t tfFlux = 0;  // Strength or quality of return signal
  int16_t tfTemp = 0;  // Internal temperature of Lidar sensor chip

  if (sensor.getData(tfDist, tfFlux, tfTemp)) {
    Serial.print("Dist: ");
    Serial.print(tfDist);
    Serial.println("cm");
    Serial.print("Flux: ");
    Serial.print(tfFlux);
    Serial.println();
    Serial.print("Temp: ");
    Serial.print(tfTemp);
    Serial.println("C");
    Serial.println();
  } else {
    sensor.printFrame(); // Display the error and HEX data
  }
}

void setup() {
  Serial.begin(115200); // Initialize terminal serial port
  delay(20);            // Give port time to initialize
  Serial.println("\r\nTFMPlus Library Example - Refactored\r\n");

  // Setup each sensor
  setupSensor(tfmP1, Serial1);
  setupSensor(tfmP2, Serial2);
  setupSensor(tfmP3, Serial3);
}

void loop() {
  delay(50); // Loop delay to match the 20Hz data frame rate

  // Read data from each sensor
  Serial.println("Sensor 1 Data:");
  readSensorData(tfmP1);

  Serial.println("Sensor 2 Data:");
  readSensorData(tfmP2);

  Serial.println("Sensor 3 Data:");
  readSensorData(tfmP3);
}
