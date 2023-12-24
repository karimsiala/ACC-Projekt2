void setup() {
  // Start the serial communication with the baud rate to match the Simulink configuration
  Serial.begin(115200);
  delay(20); // Give the serial port some time to become ready
}

void loop() {
  // Mock data for three sensors
  uint8_t sensorIDs[3] = {1, 2, 3};        // Sensor IDs for each of the three sensors
  int16_t distances[3] = {123, 456, 789};  // Example distances for each sensor

  for (int i = 0; i < 3; i++) {
    // Send the sensor ID
    Serial.write(sensorIDs[i]);

    // Send the distance as two bytes
    Serial.write((uint8_t*)&distances[i], sizeof(distances[i]));

    // Send the terminator (carriage return)
    Serial.write('\r');

    // Wait a bit before sending the next sensor data to avoid overwhelming the serial buffer
    delay(10);
  }

  // Wait a bit longer before starting the next cycle of data transmission
  delay(50);
}
