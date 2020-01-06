//
// Created by stefan on 05.01.20.
//

#include <iostream>
#include <cstring>
#include "epd_image.h"
#include "gui_paint.h"

epd_image::~epd_image() {
	delete [] data;
}

epd_image::epd_image(__uint16_t const width, __uint16_t const height, const epd_image::e_rotate rotate,
                     __uint16_t const color) {

	//this is for 2in9. Might be check if valid for others too
	array_size = ((width % 8 == 0)? (width / 8): (width / 8 + 1)) * height;
	data = new __uint8_t[array_size];
	std::memset(data, color, array_size);

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

	fprintf(stdout, "initialized image with: width: %i, height %i, array size: %i \n", this->width, this->height, this->array_size);
}

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
	if(addr >= array_size){
		std::cerr << "read out of bounds" << std::endl;
		return 0;
	}

	return data[addr];
}

void epd_image::set_data(__uint32_t const addr, __uint8_t const new_data) {
	if(addr >= array_size){
		std::cerr << "write out of bounds" << std::endl;
		return;
	}

	data[addr] = new_data;
}

__uint16_t epd_image::get_width() const {
	return width;
}

__uint16_t epd_image::get_height() const {
	return height;
}

void epd_image::set_mirroring(const epd_image::MIRROR_IMAGE new_mirror) {
	mirror = new_mirror;
}

void epd_image::set_scale(__uint8_t const new_scale) {
	if(new_scale == 2){
		scale = new_scale;
		width_byte = (width_memory % 8 == 0)? (width_memory / 8): (width_memory / 8 + 1);
	} else if (scale == 4){
		scale = new_scale;
		width_byte = (width_memory % 4 == 0)? (width_memory / 4): (width_memory / 4 + 1);
	}
}

void epd_image::set_rotate(const epd_image::e_rotate rotate) {
	this->rotation = rotate;
}
