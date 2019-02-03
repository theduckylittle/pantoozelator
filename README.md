# Loppet Foundation Pantoozelator

Code, libraries, and documentation for the Loppet's paint-marking robot.

![Image of robot](https://github.com/theduckylittle/pantoozelator/blob/master/robot-2019.jpg?raw=true)

## Basic operating theory

The hall effect sensor counts the number of passing spokes (10) in order to
determine the distance traveled by the wheel (15" diameter).  This is used to
calculated when approximately 20 feet has passed. Every 50-marks the robot
will switch from "red" markings to using "blue" marking.

## Wiring

 * Blue with Black Stripe: 12V+ for washer motors
 * Orange: 12V+
 * Black: Ground / 12V-
 * Red: "Red pump" ground
 * Blue: "Blue pump" ground
 * Wrapped wires: hall effect sensor

  * Small blue - ground
  * Black - Power
  * Tan - Signal

## Replacement part numbers

 * [Arduino Uno Rev 3](https://store.arduino.cc/usa/arduino-uno-rev3)
 * [Sainsmart 2-Channel Relay Module](https://www.amazon.com/SainSmart-101-70-100-2-Channel-Relay-Module/dp/B0057OC6D8/ref=asc_df_B0057OC6D8/?tag=hyprod-20&linkCode=df0&hvadid=309818716690&hvpos=1o1&hvnetw=g&hvrand=4196290691658680630&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9019498&hvtargid=pla-441324329911&psc=1)
 * [AdaFruit  ST7735R Display](https://www.adafruit.com/product/358)


