#include <iostream>
#include <cstring>
#include <app/eInkDisplay2in9.h>

#include "app/eInkDisplayBase.h"

extern "C" void app_main(void)
{
	std::cout << "Hello world" << std::endl;
	char hello[] = "Hello World";

	gpio_pin pin_dc(GPIO_NUM_27);
	gpio_pin pin_rst(GPIO_NUM_26);
	gpio_pin pin_busy(GPIO_NUM_25);

	spi_manager spi(GPIO_NUM_14, GPIO_NUM_13, GPIO_NUM_15, HSPI_HOST);
	//spi.send((__uint8_t*)hello, strlen(hello));

	eInkDisplay2in9 display(&spi, &pin_dc, &pin_busy, &pin_rst);

//	spi_manager manager;
/*


	pin_dc.set_mode(GPIO_MODE_OUTPUT);
	pin_rst.set_mode(GPIO_MODE_OUTPUT);
	pin_busy.set_mode(GPIO_MODE_INPUT);

	eInkDisplayBase display(&manager, &pin_dc, &pin_busy, &pin_rst);
 */

	std::cout << "Done" << std::endl;
}