/*
 * led_controller.h
 *
 *  Created on: Aug 19, 2024
 *      Author: Matthew Briggs
 */

#ifndef SRC_LED_CONTROLLER_H_
#define SRC_LED_CONTROLLER_H_

// 24 bits = 3 bytes = 1 byte per color
#define DATA_SIZE 24

// Enter the number of LEDs on your LED strip here
#define NUM_LEDS 60

// compare may vary depending on clock speed (if using NUCLEO-F303k8, leave this as is)
#define CODE_1_COMPARE 51
#define CODE_0_COMPARE 26

// RST code must create a low signal for greater than 50us
#define RST_CODE_LENGTH 50

#define DEFAULT_SPEED 75

extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch2;
extern UART_HandleTypeDef huart2;

// reset function
void reset_led();

// startup function that utilizes fx_led_chaser
void startup_led();

// fx functions
void fx_change_color(uint8_t g, uint8_t r, uint8_t b);
void fx_led_chaser(uint8_t r, uint8_t g, uint8_t b);
void fx_build(uint8_t g, uint8_t r, uint8_t b);
void fx_build_inverted(uint8_t g, uint8_t r, uint8_t b);

// hex fx functions
void fx_change_color_hex_extended(uint32_t color, uint32_t length);
void fx_change_color_hex(uint32_t color);
void fx_led_chaser_hex_extended(uint32_t color, uint32_t update_speed_ms, uint32_t length);
void fx_led_chaser_hex(uint32_t color);
void fx_build_hex_extended(uint32_t color, uint32_t update_speed_ms);
void fx_build_hex(uint32_t color);
void fx_build_inverted_hex_extended(uint32_t color, uint32_t update_speed_ms);
void fx_build_inverted_hex(uint32_t color);


#endif /* SRC_LED_CONTROLLER_H_ */
