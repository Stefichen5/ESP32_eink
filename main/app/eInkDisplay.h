//
// Created by stefan on 29.12.19.
//

#ifndef IMPORT_CMAKE_LIB_EINKDISPLAY_H
#define IMPORT_CMAKE_LIB_EINKDISPLAY_H


#include <hw_interface/spi_manager.h>

class eInkDisplay {
public:
	eInkDisplay(spi_manager * const spiManager, gpio_pin * const pin_dc,
				gpio_pin * const pin_busy, gpio_pin * const pin_reset);
	~eInkDisplay() = default;

private:
	spi_manager * spiManager    = nullptr;
	gpio_pin * pin_dc           = nullptr;
	gpio_pin * pin_busy         = nullptr;
	gpio_pin * pin_reset        = nullptr;
};


#endif //IMPORT_CMAKE_LIB_EINKDISPLAY_H
