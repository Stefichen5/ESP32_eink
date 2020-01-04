//
// Created by stefan on 29.12.19.
//

#include <iostream>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "eInkDisplayBase.h"

eInkDisplayBase::eInkDisplayBase(spi_manager *const spiManager, gpio_pin *const pin_dc, gpio_pin *const pin_busy,
                                 gpio_pin *const pin_reset) {
	if (spiManager == nullptr || pin_dc == nullptr
		|| pin_busy == nullptr || pin_reset == nullptr){
		std::cerr << "Error - nullptr detected" << std::endl;
		return;
	}

	this->spi = spiManager;
	this->pin_dc = pin_dc;
	this->pin_busy = pin_busy;
	this->pin_reset = pin_reset;

	setup_pins();

	reset();
}

void eInkDisplayBase::setup_pins() {
	pin_dc->set_mode(GPIO_MODE_OUTPUT);
	pin_reset->set_mode(GPIO_MODE_OUTPUT);

	pin_busy->set_mode(GPIO_MODE_INPUT);
}

void eInkDisplayBase::send_command(__uint8_t const cmd) {
	pin_dc->set_state(gpio_pin::off);
	spi->send(&cmd, 1);
}

void eInkDisplayBase::send_data(__uint8_t const * const data, __uint8_t const len) {
	pin_dc->set_state(gpio_pin::on);
	spi->send(data, len);
}

void eInkDisplayBase::wait_until_idle() {
	while (pin_busy->get_state() == gpio_pin::on){
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

void eInkDisplayBase::send_cmd_n_arguments(__uint8_t const cmd, __uint8_t const * const args, __uint8_t const nr_of_args) {
	send_command(cmd);
	send_data(args, nr_of_args);
}

void eInkDisplayBase::set_lut(__uint8_t const cmd, __uint8_t const len, __uint8_t *const lut) {
	send_command(cmd);
	send_data(lut, len);
}

void eInkDisplayBase::reset() {
	pin_reset->set_state(gpio_pin::off);
	vTaskDelay(200 / portTICK_PERIOD_MS);
	pin_reset->set_state(gpio_pin::on);
	vTaskDelay(200 / portTICK_PERIOD_MS);
}

eInkDisplayBase::~eInkDisplayBase() {
	reset();
}

void eInkDisplayBase::send_cmd_1_argument(__uint8_t const cmd, __uint8_t const arg) {
	send_cmd_n_arguments(cmd, &arg, 1);
}
