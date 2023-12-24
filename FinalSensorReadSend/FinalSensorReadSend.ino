#include <TFMPlus.h>  // Include TFMini Plus Library

// Create TFMini Plus objects for each sensor
TFMPlus tfmP1, tfmP2, tfmP3;

// Create a union to easily convert float to byte
typedef union {
  float number;
  uint8_t bytes[4];
} FLOATUNION_t;

// Create the variables you want to send
FLOATUNION_t distValue1, distValue2, distValue3;

void setup() {
  Serial.begin(115200); // Initialize serial
  pinMode(LED_BUILTIN, OUTPUT); // Set LED as output for error indication

  // Initialize sensors
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  tfmP1.begin(&Serial1);
  tfmP2.begin(&Serial2);
  tfmP3.begin(&Serial3);
}

void loop() {
  int16_t dist1, dist2, dist3;
  
  // Read distances from sensors
  if (tfmP1.getData(dist1)) {
    distValue1.number = dist1;
  } else {
    distValue1.number = -1.0; // Error value
  }
  
  if (tfmP2.getData(dist2)) {
    distValue2.number = dist2;
  } else {
    distValue2.number = -1.0; // Error value
  }
  
  if (tfmP3.getData(dist3)) {
    distValue3.number = dist3;
  } else {
    distValue3.number = -1.0; // Error value
  }
  
  // Print header
  Serial.write('A');
  
  // Print float data for each distance value
  for (int i=0; i<4; i++) {
    Serial.write(distValue1.bytes[i]);
  }
  for (int i=0; i<4; i++) {
    Serial.write(distValue2.bytes[i]);
  }
  for (int i=0; i<4; i++) {
    Serial.write(distValue3.bytes[i]);
  }
  
  // Print terminator
  Serial.print('\n');
  
  delay(50); // Delay to match the receive rate in Simulink
}
