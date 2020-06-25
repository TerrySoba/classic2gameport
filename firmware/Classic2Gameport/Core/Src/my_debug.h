/*
 * my_debug.h
 *
 *  Created on: May 31, 2020
 */

#ifndef SRC_MY_DEBUG_H_
#define SRC_MY_DEBUG_H_


void errorBlink();
void debugPrint(const char *message);


#define debugPrintf(message, ...)

/*
#define debugPrintf(message, ...) \
    { \
        char buffer[20]; \
        snprintf(buffer, 20, message, __VA_ARGS__); \
        debugPrint(buffer);\
    }
*/

#endif /* SRC_MY_DEBUG_H_ */
