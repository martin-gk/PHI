// add libraries

#include "arduino_secrets.h"
#include "thingProperties.h"
#include <GxEPD.h>
#include <GxDEPG0150BN/GxDEPG0150BN.h> // specific display inside the GxEPD library
#include <GxIO/GxIO_SPI/GxIO_SPI.h>    // specific folder inside the GxEPD library
#include <GxIO/GxIO.h>                 // specific folder inside the GxEPD library
#include <U8g2_for_Adafruit_GFX.h>     // font library

// define pin outs
#define PIN_MOTOR 4
#define PIN_KEY GPIO_NUM_35
#define PWR_EN 5

#define SPI_SCK 14
#define SPI_DIN 13
#define EPD_CS 15
#define EPD_DC 2
#define SRAM_CS -1
#define EPD_RESET 17
#define EPD_BUSY 16



GxIO_Class io(SPI, /*CS*/ EPD_CS, /*DC=*/EPD_DC, /*RST=*/EPD_RESET); // mapping of the defined pins to the GxIO class
GxEPD_Class display(io, /*RST=*/EPD_RESET, /*BUSY=*/EPD_BUSY);       // mapping of the defined pins to the GxEPD class
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;                                     // renaming for easier use





void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  Serial.println("ESP32 EPD Simple Test");
  SPI.begin(SPI_SCK, -1, SPI_DIN, EPD_CS);
  pinMode(PIN_MOTOR, OUTPUT);
  pinMode(PWR_EN, OUTPUT);

  digitalWrite(PWR_EN, HIGH);


  display.init();
  u8g2Fonts.begin(display);

}


void loop() {
  ArduinoCloud.update();
  
  u8g2Fonts.setFontMode(1);                           // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);                      // left to right (this is default)
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);          // apply Adafruit GFX color black letters
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);          // apply Adafruit GFX color white background


  static int displayUpdater = 0;    /* static means that the variable will not be resetted every loop
                                       it saves its value */

  if (displayUpdater < 1) {         /* in order to save on energy consumption the display will only be updated every 5 minutes*/
    onMoistureChange();              // prepare info for display with the corresponding values 
    onLightChange();
    onTemperatureChange();
    display.update();                // update display
    displayUpdater = 100;            // reset counter for display updater
  }


  isThirsty();                      // is my plant thirsty
  isDying();                        // is my plant dying
  delay(3000);                      // delay the loop to only run every 3 seconds
  displayUpdater -= 1;              // decrease display counter

}


void isThirsty() {
  if (moisture < 15) return;        // if my moisture value is below 15 the plant is thirsty and the motor will not vibrate
  vibrateMotor();                   // if everything is ok the motor vibrates every 3 seconds 
}

void vibrateMotor() {
    digitalWrite(PIN_MOTOR, HIGH); // turn the motor on
    delay(100);
    digitalWrite(PIN_MOTOR, LOW);  // turn the motor off
}

void isDying() {                   // if the moisture levels are dangerous or the temperature is dangerous the motor will vibrate SOS in morse code
  if (temperature < 15 || temperature > 45 || moisture < 9 || moisture > 55) {
    vibrateSOS();
  }
}

void vibrateSOS() {
  for (int i = 0; i < 3; i++) { // three short bursts spelling the letter "S" in morse code
    digitalWrite(PIN_MOTOR, HIGH);
    delay(100);
    digitalWrite(PIN_MOTOR, LOW);
    delay(600);
  }
  for (int i = 0; i < 3; i++) { // three long bursts spelling the letter "O" in morse code
    digitalWrite(PIN_MOTOR, HIGH);
    delay(250);
    digitalWrite(PIN_MOTOR, LOW);
    delay(600);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(PIN_MOTOR, HIGH);
    delay(100);
    digitalWrite(PIN_MOTOR, LOW);
    delay(600);
  }
}


void onLightChange()  {
  String lightAsString = String(light);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);            // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  uint16_t x = display.width() / 2 + 55;              // define the x coordinate
  uint16_t y = display.height() / 2 + 70;             // define the y coordinate
  u8g2Fonts.setCursor(x, y);                          // start writing at this position
  u8g2Fonts.print(lightAsString);


  u8g2Fonts.setFont(u8g2_font_helvR10_tf);            
  x = display.width() / 2 + 45;
  y = display.height() / 2 + 90;
  u8g2Fonts.setCursor(x, y);                          
  u8g2Fonts.print("Light");
}


void onTemperatureChange()  {
  String tempAsString = String(temperature, 1);
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);            
  uint16_t x = 20;
  uint16_t y = display.height() / 2 + 70;
  u8g2Fonts.setCursor(x, y);                          
  u8g2Fonts.print(tempAsString + "°C");


  u8g2Fonts.setFont(u8g2_font_helvR10_tf);            
  x = display.width() / 2 - 80;
  y = display.height() / 2 + 90;
  u8g2Fonts.setCursor(x, y);                          
  u8g2Fonts.print("Temp");
}


void onMoistureChange()  {
  String moistureAsString = String (moisture);
  u8g2Fonts.setFont(u8g2_font_inb53_mf);            
  uint16_t x = display.width() / 2 - 65 ;
  uint16_t y = display.height() / 2;
  display.fillScreen(GxEPD_WHITE);
  u8g2Fonts.setCursor(x, y);                          
  u8g2Fonts.print(moistureAsString + "%");


  u8g2Fonts.setFont(u8g2_font_helvR14_tf);            
  x = display.width() / 2 - 35;
  y = display.height() / 2 + 25;
  u8g2Fonts.setCursor(x, y);                          
  u8g2Fonts.print("Moisture");
}


//void onHumidityChange()  {
  /* The humidity variable is not necessary for this code, but since it is available from the cloud
     it was included should it be needed in the future */
//}
