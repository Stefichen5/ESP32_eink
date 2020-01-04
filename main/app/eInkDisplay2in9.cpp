//
// Created by stefan on 04.01.20.
//

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
