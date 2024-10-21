/*
 * driver_led.c
 *
 *  Created on: Oct 17, 2024
 *      Author: matthew
 */

#include "main.h"

#define BPL 24 // bits per led (3 bytes -> 24 bits)
#define RES_CODE 50

// ARR is 225
#define CODE1CCR 153
#define CODE0CCR 72

uint16_t led_data[NUM_LEDS * BPL + RES_CODE] = {0};

char state = 0;

void led_send_hex(uint32_t colors[NUM_LEDS]) {
	// fill led_data
	int data_idx = 0;
	for(int i = 0; i < NUM_LEDS; i++) {
		for(int j = BPL - 1; j >= 0; j--) {
			led_data[data_idx++] = colors[i] & (1 << j) ? CODE1CCR : CODE0CCR;
		}
	}
	HAL_TIMEx_PWMN_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t *) led_data, NUM_LEDS * BPL + RES_CODE);
}

void led_change_color(uint32_t color, char state) {
	uint32_t colors[NUM_LEDS] = {0}; // initialize to BLACK
	if(state) {
		for(int i = 0; i < NUM_LEDS; i++) {
			colors[i] = color;
		}
	}

	led_send_hex(colors);
}


// timer 7 update
void led_callback() {
	state = !state; // toggle state
}
