/*
 * gameport.c
 *
 *  Created on: May 31, 2020
 */

#include "gameport.h"
#include "classic_controller.h"

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

#define MY_NOP asm volatile("nop")

typedef enum
{
	// 0 bit here
	// 1 bit here
	// 1 bit here
	// 1 bit here
	// 1 bit here
	// 1 bit here
	// 0 bit here
	GRAVIS_SELECT = 7,
	GRAVIS_START = 8,
	GRAVIS_R2 = 9,
	GRAVIS_BLUE = 10,
	// 0 bit here
	GRAVIS_L2 = 12,
	GRAVIS_GREEN = 13,
	GRAVIS_YELLOW = 14,
	GRAVIS_RED = 15,
	// 0 bit here
	GRAVIS_L1 = 17,
	GRAVIS_R1 = 18,
	GRAVIS_DOWN = 19,
	GRAVIS_UP = 20,
	// 0 bit here
	GRAVIS_RIGHT = 22,
	GRAVIS_LEFT = 23,
} GravisFrame;

//0	1	1	1	1	1
//0	Select	Start	R2	Blue
//0	L2	Green	Yellow	Red
//0	L1	R1	Down	Up
//0	Right	Left


void doStuff(uint16_t buttonData)
{

    uint32_t frame = 0b00000000000000000000000000111110; // bits to be sent.  Only 24bits are actually sent.

	#define SET_FRAME_BIT(classicButton, gravisButton) \
		frame |= (isButtonPressed(classicButton, buttonData) << gravisButton)

    SET_FRAME_BIT(CLASSIC_BTN_left, GRAVIS_LEFT);
    SET_FRAME_BIT(CLASSIC_BTN_right, GRAVIS_RIGHT);
    SET_FRAME_BIT(CLASSIC_BTN_up, GRAVIS_UP);
    SET_FRAME_BIT(CLASSIC_BTN_down, GRAVIS_DOWN);

    SET_FRAME_BIT(CLASSIC_BTN_select, GRAVIS_SELECT);
    SET_FRAME_BIT(CLASSIC_BTN_start, GRAVIS_START);

    SET_FRAME_BIT(CLASSIC_BTN_a, GRAVIS_RED);
    SET_FRAME_BIT(CLASSIC_BTN_b, GRAVIS_GREEN);
    SET_FRAME_BIT(CLASSIC_BTN_x, GRAVIS_YELLOW);
    SET_FRAME_BIT(CLASSIC_BTN_y, GRAVIS_BLUE);

    SET_FRAME_BIT(CLASSIC_BTN_lT, GRAVIS_L1);
	SET_FRAME_BIT(CLASSIC_BTN_lZ, GRAVIS_L2);
	SET_FRAME_BIT(CLASSIC_BTN_rT, GRAVIS_R1);
	SET_FRAME_BIT(CLASSIC_BTN_rZ, GRAVIS_R2);

    #define CLK_PIN GPIO_PIN_11
    #define DATA_PIN GPIO_PIN_12


    // now send actual button data
    for (int i = 0; i < 24; ++i)
    {
        HAL_GPIO_WritePin(GPIOA, CLK_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, DATA_PIN, (frame & 1)?GPIO_PIN_SET:GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, CLK_PIN, GPIO_PIN_RESET); // falling edge -> data is interpreted
        HAL_GPIO_WritePin(GPIOA, DATA_PIN, GPIO_PIN_RESET);
        frame >>= 1;
    }

}
