/*
 * gameport.c
 *
 *  Created on: May 31, 2020
 */

#include "gameport.h"

#include "stm32f0xx_hal.h"

bool setGameportAxis(GameportAxis axis, GameportAxisPosition position)
{
	switch(axis)
	{
	case AXIS_X1:
		switch(position)
		{
		case POSITION_DISCONNECTED:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
			break;
		case POSITION_MAX:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
			break;
		case POSITION_MIDDLE:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
			break;
		case POSITION_MIN:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
			break;
		}
		break;
	case AXIS_Y1:
		switch(position)
		{
		case POSITION_DISCONNECTED:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			break;
		case POSITION_MAX:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			break;
		case POSITION_MIDDLE:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			break;
		case POSITION_MIN:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
			break;
		}
		break;
	}

	return true;
}


void setGpioModeToInput(GPIO_TypeDef* GPIOx, uint32_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // digital Input
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void setGpioModeToOutput(GPIO_TypeDef* GPIOx, uint32_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // digital Output
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOx, pin, GPIO_PIN_RESET);
}

bool setGameportButton(int button, bool pressed)
{
	switch(button)
	{
	case 0:
		if (pressed) setGpioModeToOutput(GPIOA, GPIO_PIN_8);
		else setGpioModeToInput(GPIOA, GPIO_PIN_8);
		break;
	case 1:
		if (pressed) setGpioModeToOutput(GPIOA, GPIO_PIN_9);
		else setGpioModeToInput(GPIOA, GPIO_PIN_9);
		break;
	case 2:
		if (pressed) setGpioModeToOutput(GPIOA, GPIO_PIN_10);
		else setGpioModeToInput(GPIOA, GPIO_PIN_10);
		break;
	case 3:
		if (pressed) setGpioModeToOutput(GPIOA, GPIO_PIN_15);
		else setGpioModeToInput(GPIOA, GPIO_PIN_15);
		break;
	}
	return true;
}


