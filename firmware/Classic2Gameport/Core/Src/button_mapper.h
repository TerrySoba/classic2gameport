#ifndef SRC_BUTTON_MAPPER_H_
#define SRC_BUTTON_MAPPER_H_

#include "classic_controller.h"
#include "gameport.h"

#include <stdint.h>


typedef enum
{
    MAP_TYPE_AXIS,
    MAP_TYPE_BUTTON,
    MAP_TYPE_END,
} MapType;

typedef struct 
{
    MapType type;
    bool force;             // if this is set to true, the map sill always be used regardles of button input
    uint16_t buttonMask1;   // mask to be applied to controller1
    uint16_t buttonMask2;   // mask to be applied to controller2
    GameportAxis axis;
    GameportAxisPosition position;
    int gameportButton;
} ButtonMap;

GameportState mapButtons(uint16_t controller1, uint16_t controller2, ButtonMap* buttonMap);


#endif
