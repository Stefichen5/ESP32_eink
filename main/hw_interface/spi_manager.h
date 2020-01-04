//
// Created by stefan on 29.12.19.
//

#ifndef IMPORT_CMAKE_LIB_SPI_MANAGER_H
#define IMPORT_CMAKE_LIB_SPI_MANAGER_H


#include <driver/spi_master.h>
#include "gpio_pin.h"

class spi_manager {
public:
	spi_manager();
	~spi_manager();

	/**
	 * Send
	 * @param data Pointer to array of data to transmit
	 * @param length Length of data to transmit (bytes)
	 * @return Transfer successful
	 */
	bool send(char * const data, __uint32_t const length);
private:
	spi_device_handle_t spi;
	spi_bus_config_t bus_cfg = {0};
	spi_device_interface_config_t devcfg = {0};
};


#endif //IMPORT_CMAKE_LIB_SPI_MANAGER_H
