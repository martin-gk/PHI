#include "thingProperties.h" //include generated sketch by the Arduino cloud
#include <Arduino_MKRIoTCarrier.h> //include the MKR IoT Carrier library
MKRIoTCarrier carrier;

int moistPin = A5; // declare pin

String lightState;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  //Get Cloud Info/errors , 0 (only errors) up to 4
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  //Wait to get cloud connection to init the carrier
  while (ArduinoCloud.connected() != 1) {
    ArduinoCloud.update();
    delay(500);
  }

  delay(500);
  //update to true if you have the carrier in its case else use false
  CARRIER_CASE = true;
  carrier.begin();
  carrier.display.setRotation(0);
  delay(1500);
}

void loop() {
  //Update the Cloud
  ArduinoCloud.update();

  //read temperature and humidity
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();

  //read raw moisture value
  int raw_moisture = analogRead(moistPin);

  //map raw moisture to a scale of 0 - 100
  moisture = map(raw_moisture, 0, 1023, 100, 0);

  //read ambient light, the units for measurement are LUX
  while (!carrier.Light.colorAvailable()) {
    delay(5);
  }
  int none; //We are not interested in light color just light intensity
  carrier.Light.readColor(none, none, none, light);

  delay(100);

}