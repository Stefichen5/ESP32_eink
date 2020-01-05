//
// Created by stefan on 05.01.20.
//

#ifndef WAVESHARE_EPD_EPD_IMAGE_H
#define WAVESHARE_EPD_EPD_IMAGE_H


#include <stdint.h>

class epd_image {
public:
	enum e_rotate{
		e_rotate_0      =   0,
		e_rotate_90     =   90,
		e_rotate_180    =   180,
		e_rotate_270    =   270
	};

	typedef enum {
		MIRROR_NONE  = 0x00,
		MIRROR_HORIZONTAL = 0x01,
		MIRROR_VERTICAL = 0x02,
		MIRROR_ORIGIN = 0x03,
	} MIRROR_IMAGE;
	#define MIRROR_IMAGE_DFT MIRROR_NONE

	epd_image(__uint16_t const width, __uint16_t const height,
			e_rotate const rotate, __uint16_t const color);
	~epd_image();

	e_rotate get_rotation() const;
	__uint16_t get_width_memory() const;
	__uint16_t get_height_memory() const;
	MIRROR_IMAGE get_mirror() const;
	__uint16_t get_scale() const;
	__uint16_t get_width_byte() const;
	__uint32_t get_height_byte() const;
	__uint16_t get_width() const;
	__uint16_t get_height() const;
	__uint8_t get_data(__uint32_t const addr) const;

	void set_data(__uint32_t  const addr, __uint8_t const data);
	void set_scale(__uint8_t const scale);
	void set_mirroring(MIRROR_IMAGE const mirror);
	void set_rotate(e_rotate const rotate);
private:
	e_rotate rotation = e_rotate_0;
	__uint16_t width_memory = 0;
	__uint16_t height_memory = 0;
	MIRROR_IMAGE mirror = MIRROR_IMAGE_DFT;
	__uint16_t scale = 2;
	__uint16_t width_byte = 0;
	__uint16_t height_byte = 0;
	__uint16_t color = 0;
	__uint8_t * data = nullptr;
	__uint16_t width = 0;
	__uint16_t height = 0;
};


#endif //WAVESHARE_EPD_EPD_IMAGE_H
