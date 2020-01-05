//
// Created by stefan on 05.01.20.
//

#include <iostream>
#include "gui_paint.h"

void gui_paint::draw_line(__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const x_end, __uint16_t const y_end,
                     __uint16_t const color, const gui_paint::DOT_PIXEL line_width,
                     const gui_paint::LINE_STYLE line_style) {
	if (x_pos > display->get_width() || y_pos > display->get_height()
		|| x_end > display->get_width() || y_end > display->get_height()){
		std::cerr << "coordinates out of bounds" << std::endl;
		return;
	}

	__uint16_t Xpoint = x_pos;
	__uint16_t Ypoint = y_pos;

	int dx = (int)x_end - (int)x_pos >= 0 ? x_end - x_pos : x_pos - x_end;
	int dy = (int)y_end - (int)y_pos <= 0 ? y_end - y_pos : y_pos - y_end;

	// Increment direction, 1 is positive, -1 is counter;
	int XAddway = x_pos < x_end ? 1 : -1;
	int YAddway = y_pos < y_end ? 1 : -1;

	//Cumulative error
	int Esp = dx + dy;
	char Dotted_Len = 0;

	for (;;) {
		Dotted_Len++;
		//Painted dotted line, 2 point is really virtual
		if (line_style == LINE_STYLE_DOTTED && Dotted_Len % 3 == 0) {
			//Debug("LINE_DOTTED\r\n");
			draw_point(Xpoint, Ypoint, IMAGE_BACKGROUND, line_width, DOT_STYLE_DFT);
			Dotted_Len = 0;
		} else {
			draw_point(Xpoint, Ypoint, color, line_width, DOT_STYLE_DFT);
		}
		if (2 * Esp >= dy) {
			if (Xpoint == x_end)
				break;
			Esp += dy;
			Xpoint += XAddway;
		}
		if (2 * Esp <= dx) {
			if (Ypoint == y_end)
				break;
			Esp += dx;
			Ypoint += YAddway;
		}
	}
}

void gui_paint::draw_point(__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const color,
                           const gui_paint::DOT_PIXEL pixel_size, const gui_paint::DOT_STYLE pixel_style) {
	if (x_pos > display->get_width() || y_pos > display->get_width()){
		std::cerr << "coordinates out of bounds" << std::endl;
		return;
	}

	int16_t XDir_Num , YDir_Num;
	if (pixel_style == DOT_FILL_AROUND) {
		for (XDir_Num = 0; XDir_Num < 2 * pixel_size - 1; XDir_Num++) {
			for (YDir_Num = 0; YDir_Num < 2 * pixel_size - 1; YDir_Num++) {
				if(x_pos + XDir_Num - pixel_size < 0 || y_pos + YDir_Num - pixel_size < 0)
					break;
				set_pixel(x_pos + XDir_Num - pixel_size, y_pos + YDir_Num - pixel_size, color);
			}
		}
	} else {
		for (XDir_Num = 0; XDir_Num <  pixel_size; XDir_Num++) {
			for (YDir_Num = 0; YDir_Num <  pixel_size; YDir_Num++) {
				set_pixel(x_pos + XDir_Num - 1, y_pos + YDir_Num - 1, color);
			}
		}
	}
}

void gui_paint::set_pixel(__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const color) {
	if (x_pos > display->get_width() || y_pos > display->get_width()){
		std::cerr << "coordinates out of bounds" << std::endl;
		return;
	}

	__uint16_t x = 0, y = 0;
	switch (image->get_rotation()){
		case epd_image::e_rotate_0:
			x = x_pos;
			y = y_pos;
			break;
		case epd_image::e_rotate_90:
			x = image->get_width_memory() - y_pos - 1;
			y = x_pos;
			break;
		case epd_image::e_rotate_180:
			x = image->get_width_memory();
			y = image->get_height_memory();
			break;
		case epd_image::e_rotate_270:
			x = y_pos;
			y = image->get_height_memory() - x_pos - 1;
			break;
	}

	switch (image->get_mirror()){
		case epd_image::MIRROR_NONE:
			break;
		case epd_image::MIRROR_HORIZONTAL:
			x = image->get_width_memory() - x - 1;
			break;
		case epd_image::MIRROR_VERTICAL:
			y = image->get_height_memory() - y - 1;
			break;
		case epd_image::MIRROR_ORIGIN:
			x = image->get_width_memory() - x - 1;
			y = image->get_height_memory() - y - 1;
			break;
	}

	if (x > image->get_width_memory() || y > image->get_height_memory()){
		std::cerr << "coordinates out of bounds" << std::endl;
		return;
	}

	if(image->get_scale() == 2){
		__uint32_t addr = x / 8 + y * image->get_width_byte();
		__uint8_t rdata = image->get_data(addr);

		if(color == BLACK){
			image->set_data(addr,rdata & ~(0x80 >> (x % 8)));
		} else{
			image->set_data(addr,rdata | (0x80 >> (x % 8)));
		}
	} else if(image->get_scale() == 4){
		__uint32_t addr = x / 4 + y * image->get_width_byte();
		uint16_t set_color = color % 4;
		__uint8_t rdata = image->get_data(addr);

		rdata = rdata & (~(0xC0 >> ((x % 4)*2)));
		image->set_data(addr, rdata | ((set_color << 6) >> ((x % 4)*2)));
	}
}

void gui_paint::fill(__uint16_t const color) {
	fill_window(0, 0, image->get_width_byte(), image->get_height_memory(), color);
}

void gui_paint::fill_window(__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const x_end, __uint16_t const y_end,
                       __uint16_t const color) {
	__uint16_t x = 0, y = 0;

	for (y = y_pos; y < y_end; y++){
		for (x = x_pos; x < x_end; x++){
			set_pixel(x, y, color);
		}
	}
}

void gui_paint::draw_circle(__uint16_t const x_center, __uint16_t const y_center, __uint16_t const radius,
                            __uint16_t const color, const gui_paint::DOT_PIXEL line_width,
                            const gui_paint::DRAW_FILL draw_fill) {
	if (x_center > display->get_width() || y_center > display->get_width()){
		std::cerr << "coordinates out of bounds" << std::endl;
		return;
	}

	//Draw a circle from(0, R) as a starting point
	int16_t XCurrent, YCurrent;
	XCurrent = 0;
	YCurrent = radius;

	//Cumulative error,judge the next point of the logo
	int16_t Esp = 3 - (radius << 1 );

	int16_t sCountY;
	if (draw_fill == DRAW_FILL_FULL) {
		while (XCurrent <= YCurrent ) { //Realistic circles
			for (sCountY = XCurrent; sCountY <= YCurrent; sCountY ++ ) {
				draw_point(x_center + XCurrent, y_center + sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//1
				draw_point(x_center - XCurrent, y_center + sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//2
				draw_point(x_center - sCountY, y_center + XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//3
				draw_point(x_center - sCountY, y_center - XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//4
				draw_point(x_center - XCurrent, y_center - sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//5
				draw_point(x_center + XCurrent, y_center - sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//6
				draw_point(x_center + sCountY, y_center - XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//7
				draw_point(x_center + sCountY, y_center + XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
			}
			if (Esp < 0 )
				Esp += 4 * XCurrent + 6;
			else {
				Esp += 10 + 4 * (XCurrent - YCurrent );
				YCurrent --;
			}
			XCurrent ++;
		}
	} else { //Draw a hollow circle
		while (XCurrent <= YCurrent ) {
			draw_point(x_center + XCurrent, y_center + YCurrent, color, line_width, DOT_STYLE_DFT);//1
			draw_point(x_center - XCurrent, y_center + YCurrent, color, line_width, DOT_STYLE_DFT);//2
			draw_point(x_center - YCurrent, y_center + XCurrent, color, line_width, DOT_STYLE_DFT);//3
			draw_point(x_center - YCurrent, y_center - XCurrent, color, line_width, DOT_STYLE_DFT);//4
			draw_point(x_center - XCurrent, y_center - YCurrent, color, line_width, DOT_STYLE_DFT);//5
			draw_point(x_center + XCurrent, y_center - YCurrent, color, line_width, DOT_STYLE_DFT);//6
			draw_point(x_center + YCurrent, y_center - XCurrent, color, line_width, DOT_STYLE_DFT);//7
			draw_point(x_center + YCurrent, y_center + XCurrent, color, line_width, DOT_STYLE_DFT);//0

			if (Esp < 0 )
				Esp += 4 * XCurrent + 6;
			else {
				Esp += 10 + 4 * (XCurrent - YCurrent );
				YCurrent --;
			}
			XCurrent ++;
		}
	}
}

void gui_paint::draw_rectangle(__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const x_end,
                               __uint16_t const y_end, __uint16_t const color, const gui_paint::DOT_PIXEL line_width,
                               const gui_paint::DRAW_FILL draw_fill) {
	if (x_pos > display->get_width() || y_pos > display->get_width()){
		std::cerr << "coordinates out of bounds" << std::endl;
		return;
	}

	if (draw_fill) {
		__uint16_t Ypoint;
		for(Ypoint = y_pos; Ypoint < y_end; Ypoint++) {
			draw_line(x_pos, Ypoint, x_end, Ypoint, color , line_width, LINE_STYLE_SOLID);
		}
	} else {
		draw_line(x_pos, y_pos, x_end, y_pos, color, line_width, LINE_STYLE_SOLID);
		draw_line(x_pos, y_pos, x_pos, y_end, color, line_width, LINE_STYLE_SOLID);
		draw_line(x_end, y_end, x_end, y_pos, color, line_width, LINE_STYLE_SOLID);
		draw_line(x_end, y_end, x_pos, y_end, color, line_width, LINE_STYLE_SOLID);
	}
}

gui_paint::~gui_paint() {
	delete image;
}

gui_paint::gui_paint(eInkDisplayBase *const display) {
	if(display == nullptr){
		std::cerr << "display is nullptr" << std::endl;
		return;
	}

	this->display = display;

	image = new epd_image(display->get_width(), display->get_height(), epd_image::e_rotate_0, BLACK);
	if (image == nullptr){
		std::cerr << "image is nullptr" << std::endl;
		return;
	}
}
