//
// Created by stefan on 29.12.19.
//

#ifndef IMPORT_CMAKE_LIB_SPI_MANAGER_H
#define IMPORT_CMAKE_LIB_SPI_MANAGER_H


#include <driver/spi_master.h>
#include "gpio_pin.h"

class spi_manager {
public:
	spi_manager(gpio_num_t const mosi, gpio_num_t const sclk,
			gpio_num_t const csel, spi_host_device_t const host_device);
	~spi_manager();

	/**
	 * Send
	 * @param data Pointer to array of data to transmit
	 * @param length Length of data to transmit (bytes)
	 * @return Transfer successful
	 */
	bool send(__uint8_t const * const data, __uint32_t const length);
private:
	spi_device_handle_t spi;
	spi_bus_config_t bus_cfg;
	spi_device_interface_config_t devcfg;
	gpio_num_t mosi, sclk, csel;
};


#endif //IMPORT_CMAKE_LIB_SPI_MANAGER_H
