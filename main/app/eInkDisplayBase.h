//
// Created by stefan on 29.12.19.
//

#ifndef IMPORT_CMAKE_LIB_EINKDISPLAYBASE_H
#define IMPORT_CMAKE_LIB_EINKDISPLAYBASE_H


#include <hw_interface/spi_manager.h>

class eInkDisplayBase {
public:
	eInkDisplayBase(spi_manager * const spiManager, gpio_pin * const pin_dc,
	                gpio_pin * const pin_busy, gpio_pin * const pin_reset);
	~eInkDisplayBase();

	void send_command(__uint8_t const cmd);
	void send_data(__uint8_t const data);
	void send_data(__uint8_t const * const data, __uint8_t const len);
	void wait_until_idle();
	void send_cmd_1_argument(__uint8_t const cmd, __uint8_t const arg);
	void send_cmd_n_arguments(__uint8_t const cmd, __uint8_t const *const args, __uint8_t const nr_of_args);
	void set_lut(__uint8_t const cmd, __uint8_t const len, __uint8_t * const lut);
	//void set_lut_bw();//todo
	void reset();

	virtual void clear() = 0;
	virtual __uint16_t get_width() const = 0;
	virtual __uint16_t get_height() const = 0;

private:
	spi_manager * spi           = nullptr;
	gpio_pin * pin_dc           = nullptr;
	gpio_pin * pin_busy         = nullptr;
	gpio_pin * pin_reset        = nullptr;

	void setup_pins();
};


#endif //IMPORT_CMAKE_LIB_EINKDISPLAYBASE_H
