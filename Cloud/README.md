# Cloud

## First Steps

The Arduino IoT Cloud is a service that is provided by Arduino. <br>
It features a free and a paid version. For the scope of this project the free version is enough <br>
but a registration is still necessary.

## Connect your hardware to the cloud

I will never be able to write a better step by step guide as Arduino themselves so please enjoy the wonderfully <br>
created tutorial by Arduino. <br>

- [Getting started with the Arduino IoT cloud](https://docs.arduino.cc/cloud/iot-cloud/tutorials/iot-cloud-getting-started)

When you have reached step 5 you will need to create the following variables

- humidity: float; Read and Write
- light: int; Read and Write
- temperature: float; Read and Write
- moisture: int; Read and Write

Once you have connected one device to the cloud you will want to sync the variables to the second device. <br>
This step is documented [here](https://docs.arduino.cc/cloud/iot-cloud/tutorials/device-to-device) in step 5.<br>
The tutorial features an explanation for arduino boards as well as for third party boards like the ESP32 for our wearable. <br>
Once you have completed all the steps the cloud will have generated a thingProperties.h sketch that your hardware needs in order to <br> communicate with the cloud. Exemplary sketches can be found in the directories inside this directory. <br>
The cloud will also generate a arduino_secrets.h file with your network login data. This is not included in this documentation.
