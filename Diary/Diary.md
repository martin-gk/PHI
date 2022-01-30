### This document is just a loose list of my findings and issues as they come while working on the project

- Found out Arduino IOT Cloud does not support bluetooth boards. Kids thats why you carefully read the documentation first and don't just panic buy

  - there seems to be a workaround with IFTTT and the Adafruit Connect App

- Iphone seems to close BLE connection when locked. Hopefully it's just a scare. Need to check when I have actual code on my wearable. Again, read documentation first, cry later.

- Apparently I can't connect the vibration motors directly to the board. The board can be damaged. Why is electricity magic, and why can't I understand it?

  - "expensive" solution and complete overkill: [Haptic Motor Controller](https://www.adafruit.com/product/2305)
  - better solution [transistors](https://learn.adafruit.com/adafruit-arduino-lesson-13-dc-motors/transistors)
  - best solution have a board that comes with a vibrating motor

- There is plug-and-play and there is firmware updates. Wasted 3 hours and 2% hairs on a 10 min [fix](https://www.arduino.cc/en/Tutorial/WiFiNINA-FirmwareUpdater)

- Kids these day don't know how great they have it with autocomplete

- Compile error because your code is good but an imported library is not good is awful

- Sometimes you have to break your board in order to find out that what you have been looking for does not exist

- Compiling seconds are like hours in real time

- There is nothing like the helplessness of being unable to connect to your board

- shortcuts in your device communicator can ruin your life

- I hope its a shortcut

- Patience is a virtue you learn while waiting on your parts from china

- Comfort is not as important if you are afraid to loose your arm
