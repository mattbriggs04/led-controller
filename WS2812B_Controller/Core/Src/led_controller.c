/*
 * led_controller.c
 *
 *  Created on: Aug 19, 2024
 *      Author: Matthew Briggs
 */
#include "main.h"
#include "led_controller.h"


// Helper functions
static uint32_t rgb_to_hex(uint8_t r, uint8_t g, uint8_t b) {
	return (r << 16) | (g << 8) | b;
}

static uint32_t grb_to_rgb(uint32_t color) {
	// Takes the red and green components of a GRB formatted color and swaps them, returning an RGB (or vice versa)
	return ((color & (0xff << 8)) << 8) | ((color & (0xff << 16)) >> 8)| (color & 0xff);
}

// RGB functions
void startup_led() {
	fx_led_chaser_hex_extended(0xffffff, 15, NUM_LEDS / 3);
	HAL_Delay(1);
	reset_led(); // turn LEDs off
}

// Creates a snake of LEDs that go along the LEDs
void fx_led_chaser(uint8_t r, uint8_t g, uint8_t b) {
	fx_led_chaser_hex(rgb_to_hex(r, g, b));
}

// Change color of all LEDs (at high NUM_LEDs (>30), color may change if 5V is only applied at one end).
void fx_change_color(uint8_t g, uint8_t r, uint8_t b) {
	fx_change_color_hex(rgb_to_hex(r, g, b));
}

// "builds" all LEDs on, one at a time at speed (in ms) from the start
void fx_build(uint8_t g, uint8_t r, uint8_t b) {
	fx_build_hex(rgb_to_hex(r, g, b));
}

// "builds" all LEDs on, starting from the last LED at speed (in ms)
void fx_build_inverted(uint8_t g, uint8_t r, uint8_t b) {
	fx_build_inverted_hex(rgb_to_hex(r, g, b));
}

// Hex functions
static void send_data_hex(uint32_t colors[NUM_LEDS]) {
	uint16_t pwm_data[DATA_SIZE * NUM_LEDS + RST_CODE_LENGTH] = {0};

	int running_idx = 0;
	for(int i = 0; i < NUM_LEDS; i++) { // For each color
		for(int j = DATA_SIZE - 1; j >= 0; j--) { // For every 24 bits in each color
			// If bit = 1, use CODE_1, else (bit = 0) use CODE_0
			pwm_data[running_idx] = (colors[i] & (1 << j)) ? CODE_1_COMPARE : CODE_0_COMPARE;
			running_idx++;
		}
	}

	// Note: the RESET portion of the data should already be 0 due to pwm_data initialization

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t*) pwm_data, DATA_SIZE * NUM_LEDS + RST_CODE_LENGTH);
}

// WS2812b lights will light up GRB rather than RGB
// this functions converts the users input (GRB) to be RGB on the lights

void reset_led() {
	uint32_t colors[NUM_LEDS] = {0};
	send_data_hex(colors);
	HAL_Delay(50);
}

void fx_change_color_hex_extended(uint32_t color, uint32_t length) {
	if(length <= NUM_LEDS) {
		color = grb_to_rgb(color);
		uint32_t colors[NUM_LEDS];
		for(int i = 0; i < NUM_LEDS; i++) {
			colors[i] = (i < length) ? color : 0x000000;
		}
		send_data_hex(colors);
	}
}
void fx_change_color_hex(uint32_t color) {
	fx_change_color_hex_extended(color, NUM_LEDS);
}

void fx_led_chaser_hex_extended(uint32_t color, uint32_t update_speed_ms, uint32_t length) {
	if(length <= NUM_LEDS) {
		color = grb_to_rgb(color);
		uint32_t colors[NUM_LEDS] = {0};
		for(int i = 0; i < NUM_LEDS; i++) {
			colors[i] = color;
			if(i >= length) {
				colors[i - length] = 0;
			}
			send_data_hex(colors);
			HAL_Delay(update_speed_ms);
		}
	}
}

void fx_led_chaser_hex(uint32_t color) {
	fx_led_chaser_hex_extended(color, 75, (NUM_LEDS > 10) ? 10 : NUM_LEDS);
}

void fx_build_hex_extended(uint32_t color, uint32_t update_speed_ms) {
	uint32_t colors[NUM_LEDS] = {0};
	for(int i = 0; i < NUM_LEDS; i++) {
		colors[i] = color;
		send_data_hex(colors);
		HAL_Delay(update_speed_ms);
	}
}

void fx_build_hex(uint32_t color) {
	fx_build_hex_extended(color, DEFAULT_SPEED);
}

void fx_build_inverted_hex_extended(uint32_t color, uint32_t update_speed_ms) {
	uint32_t colors[NUM_LEDS] = {0};
	for(int i = NUM_LEDS - 1; i >= 0; i--) {
		colors[i] = color;
		send_data_hex(colors);
		HAL_Delay(update_speed_ms);
	}
}

void fx_build_inverted_hex(uint32_t color) {
	fx_build_inverted_hex_extended(color, DEFAULT_SPEED);
}



