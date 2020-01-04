//
// Created by stefan on 29.12.19.
//

#include "eInkDisplay.h"

eInkDisplay::eInkDisplay(spi_manager *const spiManager, gpio_pin *const pin_dc, gpio_pin *const pin_busy,
                         gpio_pin *const pin_reset) {
	this->spiManager = spiManager;
	this->pin_dc = pin_dc;
	this->pin_busy = pin_busy;
	this->pin_reset = pin_reset;
}
