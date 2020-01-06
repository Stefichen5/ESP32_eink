#include <iostream>
#include "gui_paint.h"

void gui_paint::draw_line(epd_image * const image,
		__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const x_end, __uint16_t const y_end,
        __uint16_t const color, const gui_paint::DOT_PIXEL line_width,
        const gui_paint::LINE_STYLE line_style) {
	if (x_pos > image->get_width() || y_pos > image->get_height()
		|| x_end > image->get_width() || y_end > image->get_height()){
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
			draw_point(image, Xpoint, Ypoint, IMAGE_BACKGROUND, line_width, DOT_STYLE_DFT);
			Dotted_Len = 0;
		} else {
			draw_point(image, Xpoint, Ypoint, color, line_width, DOT_STYLE_DFT);
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

void gui_paint::draw_point(epd_image * const image,
		__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const color,
        const gui_paint::DOT_PIXEL pixel_size, const gui_paint::DOT_STYLE pixel_style) {
	if (x_pos >= image->get_width() || y_pos >= image->get_height()){
		std::cerr << "coordinates out of bounds" << std::endl;
		return;
	}

	int16_t XDir_Num , YDir_Num;
	if (pixel_style == DOT_FILL_AROUND) {
		for (XDir_Num = 0; XDir_Num < 2 * pixel_size - 1; XDir_Num++) {
			for (YDir_Num = 0; YDir_Num < 2 * pixel_size - 1; YDir_Num++) {
				if(x_pos + XDir_Num - pixel_size < 0 || y_pos + YDir_Num - pixel_size < 0){
					break;
				}
				set_pixel(image,x_pos + XDir_Num - pixel_size, y_pos + YDir_Num - pixel_size, color);
			}
		}
	} else {
		for (XDir_Num = 0; XDir_Num <  pixel_size; XDir_Num++) {
			for (YDir_Num = 0; YDir_Num <  pixel_size; YDir_Num++) {
				set_pixel(image, x_pos + XDir_Num - 1, y_pos + YDir_Num - 1, color);
			}
		}
	}
}

void gui_paint::set_pixel(epd_image * const image,
		__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const color) {
	if (x_pos >= image->get_width() || y_pos >= image->get_height()){
		std::cerr << "coordinates out of bounds" << std::endl;
		return;
	}

	//fprintf(stdout, "setting pixel x: %i, y: %i\n", x_pos, y_pos);

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
			x = image->get_width_memory() - x_pos - 1;
			y = image->get_height_memory() - y_pos - 1;
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
		default:
			return;
	}

	if (x >= image->get_width_memory() || y >= image->get_height_memory()){
		fprintf(stderr, "coordinates x: %i, y: %i out of bounds", x, y);
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

void gui_paint::fill(epd_image * const image,
		__uint16_t const color) {
	fill_window(image, 0, 0, image->get_width()-1, image->get_height()-1, color);
}

void gui_paint::fill_window(epd_image * const image,
		__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const x_end, __uint16_t const y_end,
        __uint16_t const color) {

	fprintf(stdout, "fill until x: %i, y: %i\n", x_end, y_end);

	if(x_pos >= image->get_width() || x_end >= image->get_width()
		|| y_pos >= image->get_height() || y_end >= image->get_height()){
		return;
	}

	for (__uint16_t y = y_pos; y < y_end; y++){
		for (__uint16_t x = x_pos; x < x_end; x++){
			set_pixel(image, x, y, color);
		}
	}
}

void gui_paint::draw_circle(epd_image * const image,
		__uint16_t const x_center, __uint16_t const y_center, __uint16_t const radius,
        __uint16_t const color, const gui_paint::DOT_PIXEL line_width,
        const gui_paint::DRAW_FILL draw_fill) {
	if (x_center > image->get_width() || y_center > image->get_height()){
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
				draw_point(image, x_center + XCurrent, y_center + sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//1
				draw_point(image, x_center - XCurrent, y_center + sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//2
				draw_point(image, x_center - sCountY, y_center + XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//3
				draw_point(image, x_center - sCountY, y_center - XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//4
				draw_point(image, x_center - XCurrent, y_center - sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//5
				draw_point(image, x_center + XCurrent, y_center - sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//6
				draw_point(image, x_center + sCountY, y_center - XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//7
				draw_point(image, x_center + sCountY, y_center + XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
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
			draw_point(image, x_center + XCurrent, y_center + YCurrent, color, line_width, DOT_STYLE_DFT);//1
			draw_point(image, x_center - XCurrent, y_center + YCurrent, color, line_width, DOT_STYLE_DFT);//2
			draw_point(image, x_center - YCurrent, y_center + XCurrent, color, line_width, DOT_STYLE_DFT);//3
			draw_point(image, x_center - YCurrent, y_center - XCurrent, color, line_width, DOT_STYLE_DFT);//4
			draw_point(image, x_center - XCurrent, y_center - YCurrent, color, line_width, DOT_STYLE_DFT);//5
			draw_point(image, x_center + XCurrent, y_center - YCurrent, color, line_width, DOT_STYLE_DFT);//6
			draw_point(image, x_center + YCurrent, y_center - XCurrent, color, line_width, DOT_STYLE_DFT);//7
			draw_point(image, x_center + YCurrent, y_center + XCurrent, color, line_width, DOT_STYLE_DFT);//0

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

void gui_paint::draw_rectangle(epd_image * const image,
		__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const x_end,
        __uint16_t const y_end, __uint16_t const color, const gui_paint::DOT_PIXEL line_width,
        const gui_paint::DRAW_FILL draw_fill) {
	if (x_pos > image->get_width() || y_pos > image->get_height()){
		std::cerr << "coordinates out of bounds" << std::endl;
		return;
	}

	if (draw_fill) {
		__uint16_t Ypoint;
		for(Ypoint = y_pos; Ypoint < y_end; Ypoint++) {
			draw_line(image, x_pos, Ypoint, x_end, Ypoint, color , line_width, LINE_STYLE_SOLID);
		}
	} else {
		draw_line(image, x_pos, y_pos, x_end, y_pos, color, line_width, LINE_STYLE_SOLID);
		draw_line(image, x_pos, y_pos, x_pos, y_end, color, line_width, LINE_STYLE_SOLID);
		draw_line(image, x_end, y_end, x_end, y_pos, color, line_width, LINE_STYLE_SOLID);
		draw_line(image, x_end, y_end, x_pos, y_end, color, line_width, LINE_STYLE_SOLID);
	}
}


void gui_paint::draw_string(epd_image * const image,
		__uint16_t const x_pos, __uint16_t const y_pos, std::string const text, sFONT *const font,
        __uint16_t const color_foreground, __uint16_t const color_background) {
	__uint16_t Xpoint = x_pos;
	__uint16_t  Ypoint = y_pos;

	if (x_pos > image->get_width() || y_pos > image->get_height()) {
		std::cerr << "Paint_DrawString_EN Input exceeds the normal display range" << std::endl;
		return;
	}

	auto text_c_str = text.c_str();
	char const * pString = text_c_str;

	while (* pString != '\0') {
		//if X direction filled , reposition to(Xstart,Ypoint),Ypoint is Y direction plus the Height of the character
		if ((Xpoint + font->Width ) > image->get_width() ) {
			Xpoint = x_pos;
			Ypoint += font->Height;
		}

		// If the Y direction is full, reposition to(Xstart, Ystart)
		if ((Ypoint  + font->Height ) > image->get_height() ) {
			Xpoint = x_pos;
			Ypoint = y_pos;
		}
		draw_char(image, Xpoint, Ypoint, * pString, font, color_foreground, color_background);

		//The next character of the address
		pString ++;

		//The next word of the abscissa increases the font of the broadband
		Xpoint += font->Width;
	}
}

void gui_paint::draw_char(epd_image * const image,
		__uint16_t const x_pos, __uint16_t const y_pos, char const ch, sFONT *const font,
        __uint16_t const color_foreground, __uint16_t const color_background) {
	__uint16_t Page = 0, Column = 0;

	if (x_pos > image->get_width() || y_pos > image->get_height()) {
		std::cerr << "Paint_DrawChar Input exceeds the normal display range" << std::endl;
		return;
	}

	uint32_t Char_Offset = (ch - ' ') * font->Height * (font->Width / 8 + (font->Width % 8 ? 1 : 0));
	const unsigned char *ptr = &font->table[Char_Offset];

	for (Page = 0; Page < font->Height; Page ++ ) {
		for (Column = 0; Column < font->Width; Column ++ ) {

			//To determine whether the font background color and screen background color is consistent
			if (FONT_BACKGROUND == color_background) { //this process is to speed up the scan
				if (*ptr & (0x80 >> (Column % 8)))
					set_pixel(image, x_pos + Column, y_pos + Page, color_foreground);
				// Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
			} else {
				if (*ptr & (0x80 >> (Column % 8))) {
					set_pixel(image, x_pos + Column, y_pos + Page, color_foreground);
					// Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
				} else {
					set_pixel(image, x_pos + Column, y_pos + Page, color_background);
					// Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
				}
			}
			//One pixel is 8 bits
			if (Column % 8 == 7){
				ptr++;
			}
		}// Write a line
		if (font->Width % 8 != 0){
			ptr++;
		}
	}
}
