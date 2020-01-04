#include <iostream>
#include <cstring>

#include "app/eInkDisplay.h"

extern "C" void app_main(void)
{
	std::cout << "Hello world" << std::endl;
	char hello[] = "Hello World";

	spi_manager spi;
	spi.send(hello, strlen(hello));

//	gpio_pin pin_mosi(GPIO_NUM_23);
//	gpio_pin pin_clk(GPIO_NUM_18);
//	gpio_pin pin_cs(GPIO_NUM_5);

//	spi_manager manager;
/*
	gpio_pin pin_dc(GPIO_NUM_4);
	gpio_pin pin_rst(GPIO_NUM_2);
	gpio_pin pin_busy(GPIO_NUM_15);

	pin_dc.set_mode(GPIO_MODE_OUTPUT);
	pin_rst.set_mode(GPIO_MODE_OUTPUT);
	pin_busy.set_mode(GPIO_MODE_INPUT);

	eInkDisplay display(&manager, &pin_dc, &pin_busy, &pin_rst);
 */

	std::cout << "Done" << std::endl;
}