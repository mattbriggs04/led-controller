# WS2812b LED Controller with STM32 Microcontroller
This project focused on using STM32's HAL in order to communicate with programmable LED lights. If you choose to use a different programmable LED, review with the data sheet in order to get accurate information on how data is to be sent. There is no gurantee that this project will work with an LED light that is not a WS2812b. The LED Controller is abstracted into many easy-to-use functions, all of which start with fx_ (typing in "fx_" then CTRL + SPACE will list all functions). This makes it easy to modify the current LED function, or implement higher levels of design, such as a state machine that allows for remote, bluetooth, ethernet, etc. to be used as a controller. 

## Prerequisites

### You will need:
1. STM32CubeIDE
2. A STM32 Microcontroller (NUCLEO-F303k8 will

### Descriptions
In order to use this project, you will need STM32CubeIDE / CubeMX (they are a combined software now) in order to run the program and communicate with an STM32 device. This software can be installed at the [STM32CubeIDE Installation Site](https://www.st.com/en/development-tools/stm32cubeide.html).

I used a F303k8 microcontroller in order to output, however any STM32 microcontroller will work, as long as there is an understanding in the math that goes behind the clock configurations. A tutorial may be released at some point discussing the math and intuition behind how this project was made.

## Installation
1. Ensure you have STM32CubeIDE set up. See Prerequisites.
2. Run ```git clone <url>``` (The url can be found in the ```Code < >``` button at the top of the repo).
3. A folder named led-controller should have been created. Inside of it should be a folder WS2812B_Controller/. Open this with STM32CubeIDE.
4. Once inside STM32CubeIDE, WS2812B_Controller project may not show up. Navigate to File > Import > General > Existing Projects into Workspace.
5. Set the root directory to the WS2812B_Controller folder.
6. Click Finish
7. Click the hammer button at the top to ensure that the console prints out "0 errors, 0 warnings."
8. Now, click the run button to run the program.

## License
Distributed under the MIT License. See the ```LICENSE.txt``` file for more information.
