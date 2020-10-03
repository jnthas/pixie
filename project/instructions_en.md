
# Pixie 

## Intro

Pixie was a project developed with the intention of making the plants we have at home more interactive, since for most people one of the challenges of having a plant at home is to know how to take care of it, how often we water, when and how much sun is enough, etc. While sensors work to obtain plant data, a LED display, purposely pixelated (hence the name Pixie), displays basic expressions that indicate the state of the plant, such as joy while it is being watered or sadness if the temperature is too high, indicating that it should be taken to a cooler place. To make the experience even more interesting, other sensors such as presence, touch and luminosity have been added, translating into other expressions that make it seem that you now have a virtual pet to take care of.

The project has several parameters where it is possible to customize the limits and needs of each case, considering the diversity of plants as well as sensors of different brands. As we know, there are plants that need more sun or water while others can live with fewer resources, such as cacti for example, in cases like this, having parameters is a must have. Throughout this article, I will present the operation and an overview about how to build a Pixie using a little knowledge of electronics, components easily found in the market and a 3d printed case.

Although it's a fully functional project, there are possibilities of customization and improvements that will be presented at the end of the article. I will be glad to answer any question about the project here in the comments or directly to my email or Twitter account.


## Components & Tools

All components are easily found in specialized stores or websites.

- 1 MCU ESP32 (ESP8266 can be used or even an Arduino Nano if you do not want to send data over the internet)
  - I’ve used this model for the project
- 1 LDR 5mm GL5528
- 1 PIR element D203S or similar (it is the same sensor used in SR501 or SR505 modules)
- 1 DHT11 Temperature sensor
- 1 Soil moisture sensor
   - Prefer using capacitive soil sensor instead of resistive, this video explains well why https://www.youtube.com/watch?v=udmJyncDvw0
- 1 Led Matrix 8x8 with integrated MAX7219
 - I've used this model https://aliexpress.com/item/32801376173.html, but it can be any similar
   - I used this model, but it could be any similar
- 1 Resistor 4.7 kΩ 1/4w
- 1 Resistor 47 kΩ 1/4w
- 1 Resistor 10 kΩ 1/4w

Others

- 3d Printer
- Soldering Iron
- Cutting Pliers
- Wires for circuit connection
- USB cable for power supply

## Circuit

![Circuit](/project/pixie_bb.png)

The circuit can be seen in the image above using a breadboard, but to be placed in the case, connections must be soldered directly to take up less space. The question of space used was an important point of the project, I tried to reduce as much as possible the area that Pixie would occupy. Although the case has become small, it is still possible to reduce further, especially by developing an exclusive PCB for this purpose.

Presence detection was done using only one PIR element instead of a complete module such as SR501 or SR505, since the integrated timer and the wide actuation range exceeding five meters were not required. Using only the PIR element the sensitivity decreased and the presence detection is done via software. More details of the connection can be seen here. https://sites.google.com/a/gr0b.com/0_o/updates/pyroelectricinfraredsensorspirthermograph

Another recurring issue in electronic projects is the battery, there were some possibilities for this project like a 9v battery or a rechargeable one. Although it was more practical, an extra space was going to be needed in the case and I ended up leaving the USB output of the MCU exposed so that the user decides how the power supply will be and making it easier to upload the sketch.


## 3D Design and Printing

Along with the circuit, a case to accommodate the Pixie components was developed and printed on an Ender 3 Pro using PLA. The STL files were included here.
Some concepts were present during the design of this case:

- Since the plant pot is normally on a table, the display has been placed slightly tilted in order not to lose the viewing area
- Designed to avoid the use of printing supports
- Encourages the exchange of parts for other colors in order to make the product more personalized, interchangeable and fitting design
- The temperature sensor with opening for external environment to enable a more correct reading
- Considering the different pot sizes, the installation of Pixie in the plant can be done in two way
- Through a rod fixed to the earth; or
 - Using a strap that wraps around the plant pot
 - Points of improvement

Although functional, there are some points in the design that must be modified, such as the size of the walls that have been defined in order to avoid loss of material and speed up printing during prototyping by 1mm.

The fittings need to be improved by applying the design patterns in 3d printing, probably it will be necessary to adjust the size of the stick and stand fitting in order to snap the pieces correctly.


## Code
![Code]("/project/Pixie - Main Blocks.png")

As a programmer, I can say that it was the most fun part of working, thinking about how to structure and organize the code, took a few hours of planning and the result was quite satisfactory. The fact that most sensors use an analog input generated a separate treatment of the code in order to try to obtain a more accurate reading trying to ignore false positives as much as possible. The diagram above was created with the main blocks of code and it illustrates the core functionality, for more details I recommend taking a look at the code at https://github.com/jnthas/pixie.

There are several points open to modification that allow you to customize Pixie as you wish. Among them I can highlight:

- Sensor reading frequency
- Timeout of expressions
- Max and min temperature, lighting and ground limits as well as the threshold of sensors
- Display light intensity of each expression
- Time between frames of each expression
- The animations are separated from the code allowing you to modify them if you wish

### Triggers

It was necessary to implement a way to detect when an action was happening in real time based on the last readings. This was necessary in three known cases, watering, presence and touch, these events should be triggered as soon as a considerable variation of the sensor is detected and for this a different implementation was used. An example of this is the presence sensor, as only the PIR element was used in the analog input, the values read variates often and a logic was necessary to declare that there is presence or not while the temperature sensor, in turn, has a very low variation and just the standard reading of its values is enough to adjust the behavior of the Pixie.

## Project Next Steps

- Become a IoT device and start sending data to a platform via MQTT
- An App for customization of parameters and maybe the expressions
- Make the touch work by touching the plant. I found a great example of Touche-like project on Instructables
- Include a battery
- Design a PCB
- Print the complete vase not only the case of the Pixie
- Include a piezo in the project to play sounds accordingly the expressions
- Extend the Pixie's “memory” with historical data (too long without detecting presence could generate a sad expression)
- UV sensor to detect a Sun exposure more accurate
