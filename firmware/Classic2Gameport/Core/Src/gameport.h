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
    AXIS_Y2,
} GameportAxis;

typedef enum
{
    POSITION_MIN,
    POSITION_MIDDLE,
    POSITION_MAX,
    POSITION_DISCONNECTED,
} GameportAxisPosition;

typedef struct
{
    bool button1;
    bool button2;
    bool button3;
    bool button4;
    GameportAxisPosition axisX1;
    GameportAxisPosition axisY1;
    GameportAxisPosition axisX2;
    GameportAxisPosition axisY2;
} GameportState;

bool setGameportAxis(GameportAxis axis, GameportAxisPosition position);

bool setGameportButton(int button, bool pressed);

void setGameport(GameportState* state);

// void doStuff(uint16_t buttonData);

#endif /* SRC_GAMEPORT_H_ */
