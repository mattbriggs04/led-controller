/*
 * led_controller.h
 *
 *  Created on: Aug 19, 2024
 *      Author: matthew
 */

#ifndef SRC_LED_CONTROLLER_H_
#define SRC_LED_CONTROLLER_H_

#define DATA_SIZE 24
#define NUM_LEDS 60
#define CODE_1_COMPARE 51
#define CODE_0_COMPARE 26
#define RST_CODE_LENGTH 50

extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch2;
extern UART_HandleTypeDef huart2;

void reset_led();
void startup_led();
void fx_led_chaser(int g, int r, int b, int speed);

#endif /* SRC_LED_CONTROLLER_H_ */
