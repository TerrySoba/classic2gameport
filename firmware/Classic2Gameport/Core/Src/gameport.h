/*
 * gameport.h
 *
 *  Created on: May 31, 2020
 */

#ifndef SRC_GAMEPORT_H_
#define SRC_GAMEPORT_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    AXIS_X1,
    AXIS_Y1,
    AXIS_X2,
    AXIS_Y2,_
} GameportAxis;

typedef enum
{
    POSITION_MIN,
    POSITION_MIDDLE,
    POSITION_MAX,
    POSITION_DISCONNECTED,
} GameportAxisPosition;

bool setGameportAxis(GameportAxis axis, GameportAxisPosition position);

bool setGameportButton(int button, bool pressed);

void doStuff(uint16_t buttonData);

#endif /* SRC_GAMEPORT_H_ */
