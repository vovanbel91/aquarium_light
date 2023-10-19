simple_aquarium_light

Hello everyone. This is my first project on GitHub, so please don't judge too harshly.

Proper lighting is essential for the healthy growth of many plants in an aquarium. For instance, there are plants that react to the level of illumination, and if you suddenly expose them to bright light, they can get damaged. That's why it's necessary to gradually increase the brightness at a strictly defined time.

My friend had trouble controlling the lighting in his aquarium, and he proposed solving this problem, while also commercializing the project. However, after we devised the schematic, logic, wrote the software code, and created a working prototype, the project was abandoned due to a lack of time for implementation. The prototype uses an Arduino Nano microcontroller with the Atmega328P chip. The plan was to develop firmware and create a board for a fully commercial device, but the project came to a halt much sooner.

Since I was responsible for all the technical aspects, and I have all the schematics and code, I decided to make the project publicly available on my GitHub.

You will need:

Wires for connections.
An encoder with a push-button function.
128x32 OLED I2C Display.
Transistor assembly for PWM control (We used pre-made modules).
DS3231 Clock.
LED strips of the required colors and sizes.
Power supply.
How it works:

Upon powering on, a loading screen appears.

After loading, a screensaver is displayed, showing the current settings for different LED strips. It indicates the current mode (brightness transition or static illumination).

The program is designed in such a way that it doesn't matter what mode it operates in. The project is designed to provide illumination during the day at a specific brightness and remain off at night. Thus, there are two time intervals, t1 to t2 and t2 to t1. This is all the program needs. The brightness in both modes can be adjusted separately. When transitioning from one mode to another, the program gradually changes the brightness over 30 minutes.

After a click, Menu 1 appears. It displays the current time, and you can also select times for t1 and t2. The current time can be adjusted by turning the encoder.

After a long press, Menu 2 appears, where you can select the desired brightness for each LED strip by turning the encoder. To switch between LED strips, press the encoder once. To select the time interval during which the specified brightness will be adjusted, double-click the encoder.

! When you adjusting brightness, the selected LED strip will illuminate at the chosen brightness for visual evaluation. ! When the power is disconnected, the time will continue to progress correctly thanks to the DS3231 module. During this time, the LED strip brightness will smoothly increase from 0 to the brightness values corresponding to the current time to avoid damaging plants whose growth depends on light. ! All values are automatically stored in the non-volatile memory of the Arduino. After setting the desired parameter, wait for 5 seconds until the "Saved" message appears. This is done to conserve non-volatile memory resources.

In this project, I used some libraries from AlexGyver projects.
