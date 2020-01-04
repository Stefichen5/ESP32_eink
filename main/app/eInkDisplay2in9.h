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
};


#endif //IMPORT_CMAKE_LIB_EINKDISPLAY2IN9_H
