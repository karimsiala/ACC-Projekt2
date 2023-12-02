#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 or 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <TFMPlus.h>        
#include <SoftwareSerial.h> 

SoftwareSerial mySerial(10, 11); // RX, TX
TFMPlus tfmP; 

void setup() {
    // Initialize the LCD
    lcd.init();
    lcd.backlight();

    Serial.begin(115200);
    delay(20);
    mySerial.begin(115200); 
    delay(20); 
    tfmP.begin(&mySerial); 

    Serial.println("Data-Frame rate: ");
  if (tfmP.sendCommand(SET_FRAME_RATE, FRAME_20)) {
    printf("%2uHz.\r\n", FRAME_20);
  } else tfmP.printReply();

  delay(500);

    // Display a message on the LCD
    lcd.setCursor(0,0);
    lcd.print("TFMini Plus Test");
}

int16_t tfDist = 0; 
int16_t tfFlux = 0; 
int16_t tfTemp = 0; 

void loop() {
    delay(50);

    if(tfmP.getData(tfDist, tfFlux, tfTemp)) {
        // Display data on LCD
        lcd.setCursor(0, 1);
        lcd.print("Dist: ");
        lcd.print(tfDist);
        lcd.print("cm");
    }
    else {
        tfmP.printFrame();
    }
}
