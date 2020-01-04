//
// Created by stefan on 29.12.19.
//

#include <iostream>
#include <cstring>
#include "spi_manager.h"

spi_manager::spi_manager() {
	bus_cfg.mosi_io_num = GPIO_NUM_14;
	bus_cfg.sclk_io_num = GPIO_NUM_13;
	bus_cfg.miso_io_num = -1;

	bus_cfg.quadhd_io_num = -1;
	bus_cfg.quadwp_io_num = -1;

	bus_cfg.max_transfer_sz =  16*320*2+8;

	auto retval = spi_bus_initialize(HSPI_HOST, &bus_cfg, 1);
	if (retval != ESP_OK){
		std::cerr << "Error initializing SPI bus" << std::endl;
		return;
	}

	devcfg.clock_speed_hz = 1*1000*1000;
	devcfg.mode = 0;
	devcfg.queue_size = 8;

	devcfg.spics_io_num = GPIO_NUM_15;

	retval = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
	if (retval != ESP_OK){
		std::cerr << "Error adding device" << std::endl;
		return;
	}

	std::cout << "initialisation done" << std::endl;
}

spi_manager::~spi_manager() {
	spi_bus_remove_device(spi);
	spi_device_release_bus(spi);
}

bool spi_manager::send(char *const data, __uint32_t const length) {
	spi_transaction_t transaction = {0};

	transaction.length = length*8;
	transaction.tx_buffer = data;

	std::cout << "sending " << transaction.length/8 << " bytes" << std::endl;
	return (spi_device_polling_transmit(spi, &transaction) == ESP_OK);
}
