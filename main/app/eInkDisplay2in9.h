//
// Created by stefan on 04.01.20.
//

#ifndef IMPORT_CMAKE_LIB_EINKDISPLAY2IN9_H
#define IMPORT_CMAKE_LIB_EINKDISPLAY2IN9_H


#include "eInkDisplayBase.h"
#include "app/cmd_epd2in9.h"

class eInkDisplay2in9 : eInkDisplayBase {
public:
	eInkDisplay2in9(spi_manager *const spiManager, gpio_pin *const pin_dc, gpio_pin *const pin_busy,
	                gpio_pin *const pin_reset);

	void set_window(__uint16_t const x_start, __uint16_t const y_start, __uint16_t x_end, __uint16_t y_end);
	void set_cursor(__uint16_t const x_start, __uint16_t const y_start);
	void turn_on_display();
	void clear() override;
	void fill(__uint8_t const value);

	virtual __uint16_t get_width() const;
	virtual __uint16_t get_height() const;
};


#endif //IMPORT_CMAKE_LIB_EINKDISPLAY2IN9_H
