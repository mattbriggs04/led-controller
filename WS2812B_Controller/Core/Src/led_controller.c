/*
 * led_controller.c
 *
 *  Created on: Aug 19, 2024
 *      Author: matthew
 */
#include "main.h"
#include "led_controller.h"

static void check_color_bounds(int* green, int* red, int* blue) {
	if(*green > 255) *green = 255;
	else if (*green < 0) *green = 0;

	if(*red > 255) *red = 255;
	else if (*red < 0) *red = 0;

	if(*blue > 255) *blue = 255;
	else if (*blue < 0) *blue = 0;
}

static void set_color(int green, int red, int blue, int led_idx, int led_colors[NUM_LEDS][3]) {
	// Verify all color values are between 0 and 255 and led_num is in bounds
	check_color_bounds(&green, &red, &blue);
	if (led_idx > NUM_LEDS - 1) {
		led_idx = NUM_LEDS - 1;
	}

	led_colors[led_idx][0] = green;
	led_colors[led_idx][1] = red;
	led_colors[led_idx][2] = blue;
}

static void send_data(int led_colors[NUM_LEDS][3]) {
	uint16_t pwm_data[(DATA_SIZE * NUM_LEDS) + RST_CODE_LENGTH];
	// each color is 3 bytes = 24 bits (Green byte | Red byte | Blue byte for WS2812b)
	uint32_t color = 0;
	int running_idx = 0; // accumulating index to continually add to pwm_data

	for(int j = 0; j < NUM_LEDS; j++) {
		// create GRB color from each byte of led_colors
		color = (led_colors[j][0] << 16) | (led_colors[j][1] << 8) | (led_colors[j][2]);

		// Put a code 1 into pwm stream if bit = 1, and code 0 if bit = 0
		for(int i = DATA_SIZE - 1; i >= 0; i--) {
			if(color & (1 << i)) {
				pwm_data[running_idx] = CODE_1_COMPARE;
			}
			else {
				pwm_data[running_idx] = CODE_0_COMPARE;
			}
			running_idx++;
		}
	}

	// Ensure the reset code is implemented -> should go low for > 50us
	for(int i = 0; i < RST_CODE_LENGTH; i++) {
		pwm_data[running_idx] = 0;
		running_idx++;
	}

	// Start the DMA
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t*) pwm_data, DATA_SIZE * NUM_LEDS + RST_CODE_LENGTH);
}

void startup_led() {
	fx_led_chaser(255, 255, 255, 15);
	HAL_Delay(1);
	reset_led(); // turn LEDs off
}

// Effects functions

// Creates a snake of LEDs that go forward and back along the LEDs
void fx_led_chaser(int g, int r, int b, int speed) {
	int led_colors[NUM_LEDS][3] = {0};


	for(int i = 0; i < NUM_LEDS; i++) {
		set_color(g, r, b, i, led_colors);
		if(i >= 10) {
			set_color(0, 0, 0, i - 10, led_colors);
		}
		send_data(led_colors);
		HAL_Delay(speed);
	}
	for(int i = NUM_LEDS - 10; i >= 0; i--) {
		set_color(g, r, b, i, led_colors);
		if(i < NUM_LEDS - 10) {
			set_color(0, 0, 0, i + 10, led_colors);
		}
		send_data(led_colors);
		HAL_Delay(speed);
	}
}

// Change color of all LEDs
void fx_change_color(int g, int r, int b) {
	int led_colors[NUM_LEDS][3] = {0};
	for(int i = 0; i < NUM_LEDS; i++) {
		set_color(g, r, b, i, led_colors);
	}
	send_data(led_colors);
}

// "builds" all LEDs on, one at a time at speed (in ms) from the start
void fx_build(int g, int r, int b, int speed) {
	int led_colors[NUM_LEDS][3] = {0};

	for(int i = 0; i < NUM_LEDS; i++) {
		set_color(g, r, b, i, led_colors);
		send_data(led_colors);
		HAL_Delay(speed);
	}
}

// "builds" all LEDs on, starting from the last LED at speed (in ms)
void fx_build_inverted(int g, int r, int b, int speed) {
	int led_colors[NUM_LEDS][3] = {0};

	for(int i = NUM_LEDS - 1; i >= 0; i--) {
		set_color(g, r, b, i, led_colors);
		send_data(led_colors);
		HAL_Delay(speed);
	}
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

static uint32_t grb_to_rgb(uint32_t color) {
	return ((color & (0xff << 8)) << 8) | ((color & (0xff << 16)) >> 8)| (color & 0xff);
}

void reset_led() {
	uint32_t colors[NUM_LEDS] = {0};
	send_data_hex(colors);
	HAL_Delay(50);
}

void fx_change_color_hex(uint32_t color) {
	color = grb_to_rgb(color);
	uint32_t colors[NUM_LEDS];
	for(int i = 0; i < NUM_LEDS; i++) {
		colors[i] = color;
	}
	send_data_hex(colors);
}

void fx_led_chaser_hex(uint32_t color) {
	color = grb_to_rgb(color);
	uint32_t colors[NUM_LEDS] = {0};
	for(int i = 0; i < NUM_LEDS; i++) {
		colors[i] = color;
		if(i >= 10) {
			colors[i - 10] = 0;
		}
		send_data_hex(colors);
		HAL_Delay(50);
	}
}


