//
// Created by stefan on 29.12.19.
//

#ifndef IMPORT_CMAKE_LIB_GPIO_PIN_H
#define IMPORT_CMAKE_LIB_GPIO_PIN_H


class gpio_pin {
public:
	typedef __uint8_t t_pin_nr
	enum gpio_pin_mode{
		pin_out,
		pin_in,
		pin_float
	};

	enum gpio_pin_state{
		off = 0,
		on = 1
	};

	gpio_pin(t_pin_nr const pin);
	~gpio_pin();

private:
	t_pin_nr pinNr = 0;
};


#endif //IMPORT_CMAKE_LIB_GPIO_PIN_H
