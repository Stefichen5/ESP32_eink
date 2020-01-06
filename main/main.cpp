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
	gui_paint paint;
	epd_image image(display.get_width(), display.get_height(), epd_image::e_rotate_90, WHITE);

	std::cout << "draw point" << std::endl;
	paint.draw_point(&image, 100, 120, BLACK, gui_paint::DOT_PIXEL_2X2, gui_paint::DOT_FILL_AROUND);

	std::cout << "draw string" << std::endl;
	paint.draw_string(&image, 0,0,"hello world", &Font24, BLACK, WHITE);
	//paint.fill(&image, BLACK);

	std::cout << "draw line" << std::endl;
	paint.draw_line(&image, 50, 50, 100, 50, BLACK, gui_paint::DOT_PIXEL_1X1, gui_paint::LINE_STYLE_SOLID);
	//paint.draw_line(&image, 50, 50, 50, 100, BLACK, gui_paint::DOT_PIXEL_1X1, gui_paint::LINE_STYLE_SOLID);

	std::cout << "draw circle" << std::endl;
	paint.draw_circle(&image, 200, 50, 20, BLACK, gui_paint::DOT_PIXEL_8X8, gui_paint::DRAW_FILL_FULL);

	std::cout << "draw image" << std::endl;
	display.draw_image(&image);

	display.activate_deep_sleep();

	std::cout << "Done" << std::endl;
}