# WS2812b LED Controller With STM32 Microcontroller
This project focused on using STM32's HAL in order to communicate with programmable LED lights. If you choose to use a different programmable LED, review with the data sheet in order to get accurate information on how data is to be sent. There is no gurantee that this project will work with an LED light that is not a WS2812b. The LED Controller is abstracted into many easy-to-use functions, all of which start with fx_ (typing in "fx_" then CTRL + SPACE will list all functions). This makes it easy to modify the current LED function, or implement higher levels of design, such as a state machine that allows for remote, bluetooth, ethernet, etc. to be used as a controller. 

## Prerequisites
In order to use this project, you will need STM32CubeIDE / CubeMX (they are a combined software now) in order to run the program and communicate with an STM32 device. This software can be installed at the [STM32CubeIDE Installation Site](https://www.st.com/en/development-tools/stm32cubeide.html).

I used a F303k8 microcontroller in order to output, however any STM32 microcontroller will work, as long as there is an understanding in the math that goes behind the clock configurations. A tutorial may be released at some point discussing the math and intuition behind how this project was made.

## Installation
Coming soon.

## License
Distributed under the MIT License. See the ```LICENSE.txt``` file for more information.
