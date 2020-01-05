#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "eInkDisplay2in9.h"

eInkDisplay2in9::eInkDisplay2in9(spi_manager *const spiManager, gpio_pin *const pin_dc, gpio_pin *const pin_busy,
                                 gpio_pin *const pin_reset) : eInkDisplayBase(spiManager, pin_dc, pin_busy, pin_reset) {
	reset();
	send_cmd_n_arguments(CMD_DRIVER_OUTPUT_CONTROL, driver_output_control_arg, DRIVER_OUTPUT_CONTROL_NR_OF_ARGS);
	send_cmd_n_arguments(CMD_BOOSTER_SOFT_START_CONTROL, booster_soft_start_control_arg, BOOSTER_SOFT_START_CONTROL_NR_OF_ARGS);
	send_cmd_1_argument(CMD_WRITE_VCOM, WRITE_VCOM_ARG);
	send_cmd_1_argument(CMD_SET_DUMMY_LINE_PERIOD, SET_DUMMY_LINE_PERIOD_ARG);
	send_cmd_1_argument(CMD_SET_GATE_LINE_WIDTH, SET_GATE_LINE_WIDTH_ARG);
	send_cmd_1_argument(CMD_DATA_ENTRY_MODE_SETTING, e_data_entry_inc_Y_inc_X);

	__uint8_t ram_x_arg[] = {0, 15};
	send_cmd_n_arguments(CMD_SET_RAM_X_ADDRESS, ram_x_arg, 2);
	__uint8_t ram_y_arg[] = {0, 0, 45, 1};
	send_cmd_n_arguments(CMD_SET_RAM_Y_ADDRESS, ram_y_arg, 4);

	send_cmd_1_argument(CMD_SET_RAM_X_COUNTER, 0);
	ram_y_arg[0] = 0;
	ram_y_arg[1] = 0;
	send_cmd_n_arguments(CMD_SET_RAM_Y_COUNTER, ram_y_arg, 2);

	set_lut(CMD_WRITE_LUT, LUT_FULL_MONO_SIZE, (__uint8_t *)lut_full_mono);

	send_command(CMD_WRITE_RAM);
	vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void eInkDisplay2in9::clear() {
	fill(0xFF);
	fill(0x00);
	fill(0xFF);
}

void eInkDisplay2in9::set_window(__uint16_t const x_start, __uint16_t const y_start, __uint16_t x_end, __uint16_t y_end) {
	send_command(CMD_SET_RAM_X_ADDRESS);
	send_data((x_start >> 3) & 0xFF);
	send_data((x_end >> 3) & 0xFF);

	send_command(CMD_SET_RAM_Y_ADDRESS);
	send_data(y_start & 0xFF);
	send_data((y_start >> 8) & 0xFF);

	send_data(y_end & 0xFF);
	send_data((y_end >> 8) & 0xFF);
}

void eInkDisplay2in9::set_cursor(__uint16_t const x_start, __uint16_t const y_start) {
	send_command(CMD_SET_RAM_X_COUNTER);
	send_data((x_start >> 3) & 0xFF);

	send_command(CMD_SET_RAM_Y_COUNTER);
	send_data(y_start & 0xFF);
	send_data((y_start >> 8) & 0xFF);

}

void eInkDisplay2in9::turn_on_display() {
	send_command(CMD_DISPLAY_UPDATE_CONTROL_2);
	send_data(0xC4);
	send_command(CMD_MASTER_ACTIVATION);
	send_command(CMD_NOP);
	wait_until_idle();
}

void eInkDisplay2in9::fill(__uint8_t const value) {
	__uint16_t width = (PANEL_WIDTH % 8 == 0) ? (PANEL_WIDTH / 8): (PANEL_WIDTH / 8 + 1);
	__uint16_t height = PANEL_HEIGHT;

	set_window(0, 0, PANEL_WIDTH, PANEL_HEIGHT);
	for(__uint16_t y = 0; y < height; y++){
		set_cursor(0, y);
		send_command(CMD_WRITE_RAM);
		for(__uint16_t x = 0; x < width; x++){
			send_data(value);
		}
	}

	turn_on_display();
}

__uint16_t eInkDisplay2in9::get_width() const {
	return PANEL_WIDTH;
}

__uint16_t eInkDisplay2in9::get_height() const {
	return PANEL_HEIGHT;
}
