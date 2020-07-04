#include "button_mapper.h"

#include "gameport.h"


GameportState mapButtons(uint16_t controller1, uint16_t controller2, ButtonMap* buttonMap)
{
	GameportState state =
    {
        false, false, false, false, // buttons
        POSITION_MIDDLE, POSITION_MIDDLE, POSITION_MIDDLE, POSITION_MIDDLE// axis
    };

    for (int i = 0;; ++i)
    {
        ButtonMap* map = &buttonMap[i];

        // check for end marker
        if (map->type == MAP_TYPE_END) break;

        // check if controller input matches mask
        if ((~controller1) & map->buttonMask1 ||
            (~controller2) & map->buttonMask2 ||
            map->force)
        {
            switch(map->type)
            {
                case MAP_TYPE_AXIS:
                    switch(map->axis)
                    {
                        case AXIS_X1:
                            state.axisX1 = map->position;
                            break;
                        case AXIS_Y1:
                            state.axisY1 = map->position;
                            break;
                        case AXIS_X2:
                            state.axisX2 = map->position;
                            break;
                        case AXIS_Y2:
                            state.axisY2 = map->position;
                            break;
                    }
                    break;
                case MAP_TYPE_BUTTON:
                    switch(map->gameportButton)
                    {
                        case 0: state.button1 = true; break;
                        case 1: state.button2 = true; break;
                        case 2: state.button3 = true; break;
                        case 3: state.button4 = true; break;
                    }
                    break;
                case MAP_TYPE_END:
                	// this is not supposed to happen...
                	break;
            }
        }
    }

	return state;
}
