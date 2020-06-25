/*
 * my_debug.c
 *
 *  Created on: May 31, 2020
 */

#include "my_debug.h"

#include "stm32g0xx_hal.h"

void errorBlink() {
    for (;;) {
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET);
        HAL_Delay(50);
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_RESET);
        HAL_Delay(50);
    }
}

void debugPrint(const char *message) {
    volatile const char *tmp = message;
    (void) tmp;
}
