#include <TFMPlus.h>  // Include TFMini Plus Library


TFMPlus tfmP;  // Create a TFMini Plus object

void setup() {
  Serial.begin(115200);                                           // Initialize terminal serial port
  delay(20);                                                      // Give port time to initialize
  Serial.println("\r\nTFMPlus Library Example - 10SEP2021\r\n");  // Say 'hello'

  Serial2.begin(115200);  // Initialize TFMPLus device serial port.
  delay(20);              // Give port time to initalize
  tfmP.begin(&Serial2);   // Initialize device library object and pass device serial port to the object.

/*
  Serial.println("Data-Frame rate: ");
  if (tfmP.sendCommand(SET_FRAME_RATE, FRAME_20)) {
    printf("%2uHz.\r\n", FRAME_20);
  } else tfmP.printReply();
*/
  delay(500);
}

// Initialize variables
int16_t tfDist = 0;  // Distance to object in centimeters
int16_t tfFlux = 0;  // Strength or quality of return signal
int16_t tfTemp = 0;  // Internal temperature of Lidar sensor chip

void loop() {

  delay(50);  // Loop delay to match the 20Hz data frame rate

  if (tfmP.getData(tfDist, tfFlux, tfTemp)) {  // Get data from the device
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
  } else {              // If the command fails...
    tfmP.printFrame();  // Display the error and HEX data
  }
}