#include "classic_controller.h"

#include "my_debug.h"


#define CLASSIC_CONTROLLER_ADDR 0x52 /* address of classic controller and nunchuck */

bool initializeClassicController(I2C_HandleTypeDef *i2c) {
	unsigned char initData[2] = { 0x40, 0x00 };
	HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(i2c, CLASSIC_CONTROLLER_ADDR << 1,
			initData, 2, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		debugPrintf("ret==%d", ret);
		return false;
	}

	return true;
}


bool readClassicControllerData(I2C_HandleTypeDef* i2c, uint16_t* buttonData) {
	unsigned char zeroData[1] = { 0x00 };
	HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(i2c, CLASSIC_CONTROLLER_ADDR << 1, zeroData, 1,
			HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		debugPrintf("ret2==%d", ret);
		return false;
	}

	HAL_Delay(2);

	// now receive controller data
	uint8_t buf[6];
	ret = HAL_I2C_Master_Receive(i2c, CLASSIC_CONTROLLER_ADDR << 1, buf, 6,
			HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		debugPrintf("ret3==%d", ret);
		return false;
	}

	// now decrypt data
	for (uint8_t i = 0; i < 6; ++i) {
		buf[i] = (buf[i] ^ 0x17) + 0x17; // decrypt data
	}


	*buttonData = buf[4] | (buf[5] << 8);


	return true;
}

bool isButtonPressed(ClassicButtons button, uint16_t buttons)
{
	return !(buttons & (1 << button));
}


