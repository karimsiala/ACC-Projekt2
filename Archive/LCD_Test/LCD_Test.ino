#include <Wire.h>
#include "LCD03.h"
 
// Create new LCD03 instance
LCD03 lcd;
 
void setup() {
  // Initialise the LCD
  lcd.begin(20, 4);
 
  // Turn on the backlight
  lcd.backlight();
  
  // Write to the LCD
  lcd.print("Hello world");
 
  // Wait for 5 seconds
  delay(5000);
 
  // Clear the LCD
  lcd.clear();
}
 
void loop() {
  // Set the cursor to the top left
  lcd.home();
 
  // Print the uptime in millis
  lcd.print(millis());
}