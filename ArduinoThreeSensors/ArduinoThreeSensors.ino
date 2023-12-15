#include <TFMPlus.h>  // Include TFMini Plus Library

TFMPlus tfmP;  // Create a TFMini Plus object

void setup() {
  Serial.begin(115200); // Initialize terminal serial port
  delay(20);            // Give port time to initialize

  Serial1.begin(115200); // Initialize TFMini Plus device serial port
  delay(20);             // Give port time to initialize
  tfmP.begin(&Serial1);  // Pass hardware serial port to TFMini Plus object
  delay(500);
}

void loop() {
  int16_t tfDist = 0;    // Distance to object in centimeters
  int16_t tfFlux = 0;    // Strength or quality of return signal
  int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
  
  delay(50); // Loop delay to match the 20Hz data frame rate

  if (tfmP.getData(tfDist, tfFlux, tfTemp)) {  // Get data from the device
    // Send data in binary format
    Serial.wirte(sensorID);
    Serial.write((uint8_t*)&tfDist, sizeof(tfDist));
    Serial.write((uint8_t*)&tfFlux, sizeof(tfFlux));
    Serial.write((uint8_t*)&tfTemp, sizeof(tfTemp));
  } else {
    // Send error code if reading fails
    int16_t errorCode = -1; // Example error code
    Serial.write((uint8_t*)&errorCode, sizeof(errorCode));
    Serial.write((uint8_t*)&errorCode, sizeof(errorCode));
    Serial.write((uint8_t*)&errorCode, sizeof(errorCode));
  }
}
