/**
 * @author Stefan Mayrhofer
 * @date 04.01.2019
 * @brief implementation of 2.9" display control, most parts ported directly from sample code by waveshare
 */

#ifndef IMPORT_CMAKE_LIB_CMD_EPD2IN7_H
#define IMPORT_CMAKE_LIB_CMD_EPD2IN7_H

#define PANEL_WIDTH 128
#define PANEL_HEIGHT 296

#define CMD_PANEL_SETTING                (__uint8_t) 0x00
#define PANEL_SETTING_ARG                (__uint8_t) 0x8F

#define CMD_DRIVER_OUTPUT_CONTROL        (__uint8_t) 0x01
#define DRIVER_OUTPUT_CONTROL_NR_OF_ARGS 3
static __uint8_t const driver_output_control_arg[DRIVER_OUTPUT_CONTROL_NR_OF_ARGS] = {39, 1 ,0};

//not documented
#define CMD_POWER_ON                     (__uint8_t) 0x04

#define CMD_BOOSTER_SOFT_START_CONTROL   (__uint8_t) 0x0C
#define BOOSTER_SOFT_START_CONTROL_NR_OF_ARGS 3
static __uint8_t const booster_soft_start_control_arg[BOOSTER_SOFT_START_CONTROL_NR_OF_ARGS] = {0xD7, 0xD6, 0x9D};

#define CMD_DEEP_SLEEP_MODE              (__uint8_t) 0x10
enum e_deep_sleep_mode_arg{
	e_deep_sleep_normal = 0,
	e_deep_sleep_deep = 1
};

#define CMD_DATA_ENTRY_MODE_SETTING      (__uint8_t) 0x11
enum e_data_entry_mode_arg{
	e_data_entry_dec_Y_dec_X = 0b00,
	e_data_entry_dec_Y_inc_X = 0b01,
	e_data_entry_inc_Y_dec_X = 0b10,
	e_data_entry_inc_Y_inc_X = 0b11
};

#define CMD_SWRESET                      (__uint8_t) 0x12
#define CMD_TEMPERATURE_SENSOR_CONTROL   (__uint8_t) 0x1A
#define CMD_MASTER_ACTIVATION            (__uint8_t) 0x20
#define CMD_DISPLAY_UPDATE_CONTROL_1     (__uint8_t) 0x21
#define CMD_DISPLAY_UPDATE_CONTROL_2     (__uint8_t) 0x22
#define CMD_WRITE_RAM                    (__uint8_t) 0x24

#define CMD_WRITE_VCOM                   (__uint8_t) 0x2C
#define WRITE_VCOM_ARG                   (__uint8_t) 0xA8

//not documented
#define CMD_PLL_CONTROL                  (__uint8_t) 0x30
#define PLL_CONTROL_ARG                  (__uint8_t) 0x39

#define CMD_WRITE_LUT                    (__uint8_t) 0x32

#define CMD_SET_DUMMY_LINE_PERIOD        (__uint8_t) 0x3A
#define SET_DUMMY_LINE_PERIOD_ARG        (__uint8_t) 0x1A

#define CMD_SET_GATE_LINE_WIDTH          (__uint8_t) 0x3B
#define SET_GATE_LINE_WIDTH_ARG          (__uint8_t) 0x08

#define CMD_BORDER_WAVEFORM_CONTROL      (__uint8_t) 0x3C
#define BORDER_WAVEFORM_CONTROL_FOLLOW_SOURCE ((__uint8_t) 0b1 << 7)
#define BORDER_WAVEFORM_CONTROL_VSS ((__uint8_t) 0b00 << 4)
#define BORDER_WAVEFORM_CONTROL_VSH ((__uint8_t) 0b01 << 4)
#define BORDER_WAVEFORM_CONTROL_VSL ((__uint8_t) 0b10 << 4)
#define BORDER_WAVEFORM_CONTROL_HIZ ((__uint8_t) 0b11 << 4)
#define BORDER_WAVEFORM_CONTROL_GSA_GSB ((__uint8_t) 0b00 << 0)
#define BORDER_WAVEFORM_CONTROL_GS0_GS1 ((__uint8_t) 0b01 << 0)


#define CMD_SET_RAM_X_ADDRESS            (__uint8_t) 0x44
#define CMD_SET_RAM_Y_ADDRESS            (__uint8_t) 0x45
#define CMD_SET_RAM_X_COUNTER            (__uint8_t) 0x4E
#define CMD_SET_RAM_Y_COUNTER            (__uint8_t) 0x4F

//not documented
#define CMD_VCOM_AND_DATA_INTERVAL_SETTING (__uint8_t) 0x50
#define VCOM_AND_DATA_INTERVAL_SETTING_ARG (__uint8_t) 0x77

//not documented
#define CMD_TCON_RESOLUTION                  (__uint8_t) 0x61
#define TCON_RESULITON_NR_OF_ARGS            3
__uint8_t const tcon_resolution_arg[TCON_RESULITON_NR_OF_ARGS] = {0x80, 0x01, 0x28};

//not documented
#define CMD_VCM_DC_SETTING_REGISTER      (__uint8_t) 0x82
#define VCM_DC_SETTING_REGISTER_ARG      (__uint8_t) 0x0A

#define CMD_NOP                          (__uint8_t) 0xFF

#define LUT_FULL_MONO_SIZE 30
static __uint8_t const lut_full_mono[LUT_FULL_MONO_SIZE] =
{
		0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22,
		0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88,
		0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51,
		0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

static __uint8_t lut_full_update[] = {
		0x50, 0xAA, 0x55, 0xAA, 0x11, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xFF, 0xFF, 0x1F, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



#endif //IMPORT_CMAKE_LIB_CMD_EPD2IN7_H
