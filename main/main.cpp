#include <iostream>
#include <app/eInkDisplay2in9.h>
#include <app/gui_paint.h>

#include "app/eInkDisplayBase.h"

extern "C" void app_main(void)
{
	std::cout << "Hello world" << std::endl;

	gpio_pin pin_dc(GPIO_NUM_27);
	gpio_pin pin_rst(GPIO_NUM_26);
	gpio_pin pin_busy(GPIO_NUM_25);

	spi_manager spi(GPIO_NUM_14, GPIO_NUM_13, GPIO_NUM_15, HSPI_HOST);

	eInkDisplay2in9 display(&spi, &pin_dc, &pin_busy, &pin_rst);
	std::cout << "clear display" << std::endl;
	//display.clear();

	std::cout << "start painting" << std::endl;
	gui_paint paint(display.get_width(), display.get_height());
	epd_image image(display.get_height(), display.get_width(), epd_image::e_rotate_90, WHITE);
	paint.draw_string(&image, 0,0,"hello world", &Font12, BLACK, WHITE);
	//paint.fill(&image, WHITE);
	//paint.draw_circle(&image, 50, 50, 20, BLACK, gui_paint::DOT_PIXEL_8X8, gui_paint::DRAW_FILL_FULL);

	std::cout << "draw image" << std::endl;
	//display.draw_image(&image);
	display.draw_image(&image);
	std::cout << "Done" << std::endl;
}