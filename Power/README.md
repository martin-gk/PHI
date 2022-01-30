# Power

## Things to consider

- The wearable is run on 3.3V but can receive power from a source up to 5V.<br>
- Anything above and your board will be permanently damaged. <br>
- If your wearable does not receive enough power it will also not work.

## Possible power sources

Most of my information I gathered from the following website (link is in german)

- [Power ESP32 with battery](https://www.radioshuttle.de/media/tech-infos/esp32-mit-batteriebetrieb/)
  From that the solution that meets form, factor and our constraints mentioned above seems to be a LiPo battery. <br>
  This batteries are used in almost every wearable device that is in use nowadays. From mobile phones to e-cigarettes. <br>
  This is also a very cost inexpensive solution. <br>
  However there are also some drawbacks.

## Safety measures

LiPo batteries can become quite dangerous if they are not handled properly. <br>
If they overload or a cell gets damaged they can explode and cause a chemical fire. <br>
They should have safety circuitry built in but you never know the conditions they were made in. <br>
For that reason I have decided to use a power bank in my implementation of the project. <br>
It still uses a LiPo battery as a power source, but I have more faith in the manufacturing of a bigger brand than in my <br>
own soldering. Also the hard case around the cell feels more secure than having the naked battery directly on your skin.

## Connect the wearable to your battery

The LILYGO TTGO e-paper watch comes with a micro jst connector that ends in a red and black cable. <br>
To power the device you simply plug the jst connector into the female jst on your board. <br>
Now you need to connect this two wires onto your battery. <br>
If you decide to use a power bank like myself you will need to cut a USB cable and connect the black and red wires accordingly to <br> the wires attached to your board. <br>
Now you only need to plug the USB into your power bank and the wearable will be powered. <br>
Here is a picture of a cut USB cable, you only need the black and red wires, the other ones are data wires that can be cut short and ignored.
![USB](/img/CutUSB.png)
