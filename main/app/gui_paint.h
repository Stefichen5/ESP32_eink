/**
 * @file gui_paint.h
 * @authors Waveshar electronics, Stefan Mayrhofer
 * @brief Most of the functionality was originally implemented by waveshare
 * I just modified it a little bit to suit my needs (C++, classes, ESP32)
 *
 * Copyright/Disclaimer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef WAVESHARE_EPD_GUI_PAINT_H
#define WAVESHARE_EPD_GUI_PAINT_H

#include <string>

#include "eInkDisplayBase.h"
#include "epd_image.h"
#include "Fonts/fonts.h"

class gui_paint {
public:
	gui_paint() = default;
	~gui_paint() = default;

	/**
	 * image color
	**/
	#define WHITE          0xFF
	#define BLACK          0x00
	#define RED            BLACK

	#define IMAGE_BACKGROUND    WHITE
	#define FONT_FOREGROUND     BLACK
	#define FONT_BACKGROUND     WHITE

	typedef enum {
		DOT_PIXEL_1X1  = 1,		// 1 x 1
		DOT_PIXEL_2X2  , 		// 2 X 2
		DOT_PIXEL_3X3  ,		// 3 X 3
		DOT_PIXEL_4X4  ,		// 4 X 4
		DOT_PIXEL_5X5  , 		// 5 X 5
		DOT_PIXEL_6X6  , 		// 6 X 6
		DOT_PIXEL_7X7  , 		// 7 X 7
		DOT_PIXEL_8X8  , 		// 8 X 8
	} DOT_PIXEL;
	#define DOT_PIXEL_DFT  DOT_PIXEL_1X1

	/**
	 * Point size fill style
	**/
	typedef enum {
		DOT_FILL_AROUND  = 1,		// dot pixel 1 x 1
		DOT_FILL_RIGHTUP,    		// dot pixel 2 X 2
	} DOT_STYLE;
	#define DOT_STYLE_DFT  DOT_FILL_AROUND

	/**
	 * Line style, solid or dashed
	**/
	typedef enum {
		LINE_STYLE_SOLID = 0,
		LINE_STYLE_DOTTED,
	} LINE_STYLE;

	/**
	 * Whether the graphic is filled
	**/
	typedef enum {
		DRAW_FILL_EMPTY = 0,
		DRAW_FILL_FULL,
	} DRAW_FILL;

	static void set_pixel( epd_image * const image,
			__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const color);

	static void draw_char(epd_image * const image,
			__uint16_t const x_pos, __uint16_t const y_pos, char const ch,
			sFONT* const font, __uint16_t const color_foreground,
			__uint16_t const color_background);
	static void draw_string(epd_image * const image,
			__uint16_t const x_pos, __uint16_t const y_pos,
	        std::string const text, sFONT * const font,
			__uint16_t const color_foreground, __uint16_t const color_background);

	static void draw_point(epd_image * const image,
			__uint16_t const x_pos, __uint16_t const y_pos,
			__uint16_t const color, DOT_PIXEL const pixel_size, DOT_STYLE const pixel_style);
	static void draw_line(epd_image * const image,
			__uint16_t const x_pos, __uint16_t const y_pos,
			__uint16_t const x_end, __uint16_t const y_end,
			__uint16_t const color, DOT_PIXEL const line_width, LINE_STYLE const line_style);
	static void draw_rectangle(epd_image * const image,
			__uint16_t const x_pos, __uint16_t const y_pos,
	                    __uint16_t const x_end, __uint16_t const y_end,
	                    __uint16_t const color, DOT_PIXEL const line_width, DRAW_FILL const draw_fill);
	static void draw_circle(epd_image * const image,
			__uint16_t const x_center, __uint16_t const y_center,
						__uint16_t const radius, __uint16_t const color,
						DOT_PIXEL const line_width, DRAW_FILL const draw_fill);

	static void fill(epd_image * const image, __uint16_t const color);
	static void fill_window(epd_image * const image,
			__uint16_t const x_pos, __uint16_t const y_pos,
			__uint16_t const x_end, __uint16_t const y_end,
			__uint16_t const color);
private:
};


#endif //WAVESHARE_EPD_GUI_PAINT_H
