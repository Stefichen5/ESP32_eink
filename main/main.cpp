#include <iostream>
#include <app/eInkDisplay2in9.h>

#include "app/eInkDisplayBase.h"

extern "C" void app_main(void)
{
	std::cout << "Hello world" << std::endl;

	gpio_pin pin_dc(GPIO_NUM_27);
	gpio_pin pin_rst(GPIO_NUM_26);
	gpio_pin pin_busy(GPIO_NUM_25);

	spi_manager spi(GPIO_NUM_14, GPIO_NUM_13, GPIO_NUM_15, HSPI_HOST);

	eInkDisplay2in9 display(&spi, &pin_dc, &pin_busy, &pin_rst);
	display.clear();

	std::cout << "Done" << std::endl;
}