/*
 * classic_controller.h
 *
 *  Created on: May 31, 2020
 */

#ifndef SRC_CLASSIC_CONTROLLER_H_
#define SRC_CLASSIC_CONTROLLER_H_

#include "stm32f0xx_hal.h"

#include <stdbool.h>

typedef enum
{
	CLASSIC_BTN_rT     = 1,
	CLASSIC_BTN_start  = 2,
	CLASSIC_BTN_home   = 3,
	CLASSIC_BTN_select = 4,
	CLASSIC_BTN_lT     = 5,
	CLASSIC_BTN_down   = 6,
	CLASSIC_BTN_right  = 7,
	CLASSIC_BTN_up     = 8,
	CLASSIC_BTN_left   = 9,
	CLASSIC_BTN_rZ     = 10,
	CLASSIC_BTN_x      = 11,
	CLASSIC_BTN_a      = 12,
	CLASSIC_BTN_y      = 13,
	CLASSIC_BTN_b      = 14,
	CLASSIC_BTN_lZ     = 15,
} ClassicButtons;


bool initializeClassicController(I2C_HandleTypeDef* i2c);
bool readClassicControllerData(I2C_HandleTypeDef* i2c, uint16_t* buttonData);
bool isButtonPressed(ClassicButtons button, uint16_t buttons);

#endif /* SRC_CLASSIC_CONTROLLER_H_ */
