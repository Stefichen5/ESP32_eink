//
// Created by stefan on 05.01.20.
//

#include <iostream>
#include "epd_image.h"
#include "gui_paint.h"

epd_image::e_rotate epd_image::get_rotation() const {
	return rotation;
}

__uint16_t epd_image::get_width_memory() const {
	return width_memory;
}

__uint16_t epd_image::get_height_memory() const {
	return height_memory;
}

epd_image::MIRROR_IMAGE epd_image::get_mirror() const {
	return mirror;
}

__uint16_t epd_image::get_scale() const {
	return scale;
}

__uint16_t epd_image::get_width_byte() const {
	return width_byte;
}

__uint32_t epd_image::get_height_byte() const {
	return height_byte;
}

__uint8_t epd_image::get_data(__uint32_t const addr) const {
	//todo: implement
	return 0;
}

void epd_image::set_data(__uint32_t const addr, __uint8_t const data) {

}

epd_image::~epd_image() {
	delete [] data;
}

epd_image::epd_image(__uint16_t const width, __uint16_t const height, const epd_image::e_rotate rotate,
                     __uint16_t const color) {

	data = new __uint8_t[width*height];

	if(data == nullptr){
		std::cerr << "could not allocate memory" << std::endl;
		return;
	}

	width_memory = width;
	height_memory = height;
	this->color = color;
	this->scale = 2;

	width_byte = (width % 8 == 0)? (width / 8): (width / 8 + 1);
	height_byte = height;

	rotation = rotate;
	mirror = MIRROR_NONE;

	if (rotate == e_rotate_0 || rotate == e_rotate_180){
		this->width = width;
		this->height = height;
	} else{
		this->width = height;
		this->height = width;
	}
}
