/*
 * driver_led.h
 *
 *  Created on: Oct 17, 2024
 *      Author: matthew
 */

#ifndef SRC_DRIVER_LED_H_
#define SRC_DRIVER_LED_H_

// extern timers
extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch1;
extern DMA_HandleTypeDef hdma_tim1_ch3;

#define NUM_LEDS 30

// Changing the update speed
#define __CHANGE_TICK_SPEED(speed) /* timer7 speed = speed */

void led_send_hex(uint32_t colors[NUM_LEDS]);

#endif /* SRC_DRIVER_LED_H_ */
