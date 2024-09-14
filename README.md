# WS2812b LED Controller with STM32 NUCLEO-F303k8
This project focused on using STM32's CubeIDE and CubeMX in order to communicate with programmable LED lights (WS2812b). Data is sent using DMA with PWM to output data. Both hex and RGB color codes are options, and are sent as arrays of colors. This allows one color to correspond to one array index, correspond to one LED, making the code easily scalable. The LED Controller is abstracted into many easy-to-use functions, all of which start with fx_. Goals of this project were to create an easy-to-use, beginner friendly led-controller, which simultaneously served as a learning experience. The code can be refactored to work with any STM32 microcontroller, or even a different type of programmable LEDs, but requires an ability to comprehend data sheets and navigate clock configurations.

## Prerequisites

### You will need:
1. STM32CubeIDE
2. A STM32 Microcontroller (NUCLEO-F303k8 is what I used for this project)
3. A 3V3->5V level shifter (can be built on a breadboard or bought online)

### Important Notes
* In order to use this project, you will need STM32CubeIDE / CubeMX in order to run the program and communicate with an STM32 device. This software can be installed at the [STM32CubeIDE Installation Site](https://www.st.com/en/development-tools/stm32cubeide.html).

* I used an F303k8 microcontroller in order to output data, however any STM32 microcontroller will work, as long as there is an understanding in the math that goes behind the clock configurations. <em>If you choose not to use the F303K8, the IOC file will not be configured correctly.</em>

## Installation
### Hardware
STM32 runs on 3V3 logic, while according to the [WS2812b Datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf), the data input needs to be 5V. A solution to this is a level shifter. For my setup, I built a simple one on a breadboard. See the ```logic_level_shifter.asc``` schematic, which was made in LTspice. Level shifters can also be found for cheap online. 

WORK IN PROGRESS: The KiCad designs in the hardware folder are currently a work in progress. The plan is to create a PCB that mounts the F303k8, level shifter, and an on-off button / reset switch, as well as a header that the WS2812b lights can plug into.

<b>Useful note:</b> the F303K8, and other STM32 microcontrollers, has a +5V and a +3V3 power supply pin, which can be used to make the level shifter. This way, the level shifter can be built with just the microcontroller, an N-MOSFET, and two 1k resistors.

The F303K8 IOC file outlines that <b>PA9</b> is used to output PWM signals. Be sure that a connection is made to the right output port. The location of any port can be found on page 30 of the [F303k8 User Manual](https://www.st.com/resource/en/user_manual/dm00231744-stm32-nucleo-32-boards-mb1180-stmicroelectronics.pdf).
### Software
1. Ensure you have STM32CubeIDE set up and necessary hardware. See Prerequisites.
2. Run ```git clone <url>``` (The url can be found in the ```Code < >``` button at the top of the repo).
3. A folder named led-controller should have been created. Inside of it should be a folder WS2812B_Controller/. Open this with STM32CubeIDE.
4. Once inside STM32CubeIDE, WS2812B_Controller project may not show up. Navigate to File > Import > General > Existing Projects into Workspace.
5. Set the root directory to the WS2812B_Controller folder.
6. Click Finish. The project should now show up on the left hand side of the IDE.
7. Go to src/led_controller.h and change the NUM_LEDS to match your configuration.
8. Click the hammer button at the top to ensure that the console prints out "0 errors, 0 warnings."
9. Add your code. There is example / test code inside the main while loop that can be uncommented.
10. When ready, click the run button (green play button). A debug config page will show up, click "OK".
11. If you run into any issues, please add it to the issues section of the repo.

## License
Distributed under the MIT License. See the ```LICENSE.txt``` file for more information.

## Resources | Credits
* [WS2812b Datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf)
* [F303k8 User Manual](https://www.st.com/resource/en/user_manual/dm00231744-stm32-nucleo-32-boards-mb1180-stmicroelectronics.pdf)
* gitignore file refactored from the [gitignore repo](https://github.com/github/gitignore)
