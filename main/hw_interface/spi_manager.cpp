//
// Created by stefan on 29.12.19.
//

#include <iostream>
#include <cstring>
#include "spi_manager.h"

spi_manager::spi_manager(gpio_num_t const mosi, gpio_num_t const sclk,
                         gpio_num_t const csel, spi_host_device_t const host_device) {
	this->mosi = mosi;
	this->sclk = sclk;
	this->csel = csel;

	std::memset(&bus_cfg, 0, sizeof(bus_cfg));
	std::memset(&devcfg, 0, sizeof(devcfg));

	bus_cfg.mosi_io_num = this->mosi;
	bus_cfg.sclk_io_num = this->sclk;
	bus_cfg.miso_io_num = -1;

	bus_cfg.quadhd_io_num = -1;
	bus_cfg.quadwp_io_num = -1;

	bus_cfg.max_transfer_sz =  16*320*2+8;

	auto retval = spi_bus_initialize(host_device, &bus_cfg, 1);
	if (retval != ESP_OK){
		std::cerr << "Error initializing SPI bus" << std::endl;
		return;
	}

	devcfg.clock_speed_hz = SPI_MASTER_FREQ_8M;
	devcfg.mode = 0;
	devcfg.queue_size = 8;

	devcfg.spics_io_num = this->csel;

	retval = spi_bus_add_device(host_device, &devcfg, &spi);
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

bool spi_manager::send(__uint8_t const * const data, __uint32_t const length) {
	spi_transaction_t transaction;

	std::memset(&transaction, 0, sizeof(transaction));

	transaction.length = length*8;
	transaction.tx_buffer = data;

	return (spi_device_polling_transmit(spi, &transaction) == ESP_OK);
}
