//
// Created by stefan on 05.01.20.
//

#ifndef WAVESHARE_EPD_GUI_PAINT_H
#define WAVESHARE_EPD_GUI_PAINT_H

#include <string>

#include "eInkDisplayBase.h"
#include "epd_image.h"

class gui_paint {
public:
	gui_paint(eInkDisplayBase * const display);
	~gui_paint();

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

	void set_pixel(__uint16_t const x_pos, __uint16_t const y_pos, __uint16_t const color);

	void draw_text(std::string const text,
			__uint16_t const x_pos, __uint16_t const y_pos,
			__uint16_t const color_foreground, __uint16_t const color_background);

	void draw_point(__uint16_t const x_pos, __uint16_t const y_pos,
			__uint16_t const color, DOT_PIXEL const pixel_size, DOT_STYLE const pixel_style);
	void draw_line(__uint16_t const x_pos, __uint16_t const y_pos,
			__uint16_t const x_end, __uint16_t const y_end,
			__uint16_t const color, DOT_PIXEL const line_width, LINE_STYLE const line_style);
	void draw_rectangle(__uint16_t const x_pos, __uint16_t const y_pos,
	                    __uint16_t const x_end, __uint16_t const y_end,
	                    __uint16_t const color, DOT_PIXEL const line_width, DRAW_FILL const draw_fill);
	void draw_circle(__uint16_t const x_center, __uint16_t const y_center,
						__uint16_t const radius, __uint16_t const color,
						DOT_PIXEL const line_width, DRAW_FILL const draw_fill);

	void fill(__uint16_t const color);
	void fill_window(__uint16_t const x_pos, __uint16_t const y_pos,
					__uint16_t const x_end, __uint16_t const y_end,
			__uint16_t const color);
private:
	eInkDisplayBase * display = nullptr;
	epd_image * image = nullptr;
};


#endif //WAVESHARE_EPD_GUI_PAINT_H
