/* Name: main.c
 * Project: classic2gameport, a Wii Classic Controller to PC Gameport adapter
 * Author: Torsten Stremlau <torsten@stremlau.de>
 * Creation Date: 2020-05-14
 */

#define TW_SCL 100000 // TWI frequency in Hz

#include "twi_speed.h"

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include "bit_tools.h"
#include "twi_func.h"

#include <stdint.h>
#include <stdbool.h>

#define SLAVE_ADDR 0x52     /* address of classic controller and nunchuck */


typedef struct {
    uint8_t   buttons[2];
} report_t;


uint8_t rawData[6];

static report_t report;

/* I2C initialization */
void myI2CInit(void) {
    twi_init(); // this is a macro from "twi_speed.h"
}

// initialize Wii controller
unsigned char myWiiInit(void) {
    unsigned char buf[2] = {0x40, 0x00};

    return twi_send_data(SLAVE_ADDR, buf, 2);
}


unsigned char fillReportWithWii(void) {
    unsigned char buf[6];

    /* send 0x00 to the controller to tell it we want data! */
    buf[0] = 0x00;
    
    if (!twi_send_data(SLAVE_ADDR, buf, 1)) {
        goto fend;
    }

    _delay_ms(2);

    // ------ now get 6 bytes of data
    if (!(twi_receive_data(SLAVE_ADDR, buf, 6))) {
        goto fend;
    }

    for (uint8_t i = 0; i < 6; ++i) {
        rawData[i] = (buf[i] ^ 0x17) + 0x17; // decrypt data
    }

    // split out buttons
    #define BTN_rT      GET_BIT(~rawData[4], 1)
    #define BTN_start   GET_BIT(~rawData[4], 2)
    #define BTN_home    GET_BIT(~rawData[4], 3)
    #define BTN_select  GET_BIT(~rawData[4], 4)
    #define BTN_lT      GET_BIT(~rawData[4], 5)
    #define BTN_down    GET_BIT(~rawData[4], 6)
    #define BTN_right   GET_BIT(~rawData[4], 7)
    #define BTN_up      GET_BIT(~rawData[5], 0)
    #define BTN_left    GET_BIT(~rawData[5], 1)
    #define BTN_rZ      GET_BIT(~rawData[5], 2)
    #define BTN_x       GET_BIT(~rawData[5], 3)
    #define BTN_a       GET_BIT(~rawData[5], 4)
    #define BTN_y       GET_BIT(~rawData[5], 5)
    #define BTN_b       GET_BIT(~rawData[5], 6)
    #define BTN_lZ      GET_BIT(~rawData[5], 7)

        // button mappings (button 0..15)
    #define BUTTON_X              0
    #define BUTTON_A              1
    #define BUTTON_B              2
    #define BUTTON_Y              3
    #define BUTTON_START          4
    #define BUTTON_SELECT         5
    #define BUTTON_HOME           6
    #define BUTTON_RIGHT_TRIGGER  7
    #define BUTTON_LEFT_TRIGGER   8
    #define BUTTON_RIGHT_Z        9
    #define BUTTON_LEFT_Z        10
    #define BUTTON_UP            11
    #define BUTTON_DOWN          12
    #define BUTTON_LEFT          13
    #define BUTTON_RIGHT         14
    #define NO_BUTTON            15

    #define SET_BUTTON(BUTTON, SOURCE) SET_BIT_VALUE(report.buttons[BUTTON/8],BUTTON%8,SOURCE)

    SET_BUTTON(BUTTON_X, BTN_x);
    SET_BUTTON(BUTTON_A, BTN_a);
    SET_BUTTON(BUTTON_B, BTN_b);
    SET_BUTTON(BUTTON_Y, BTN_y);
    SET_BUTTON(BUTTON_START, BTN_start);
    SET_BUTTON(BUTTON_SELECT, BTN_select);
    SET_BUTTON(BUTTON_HOME, BTN_home);
    SET_BUTTON(BUTTON_RIGHT_TRIGGER, BTN_rT);
    SET_BUTTON(BUTTON_LEFT_TRIGGER, BTN_lT);
    SET_BUTTON(BUTTON_RIGHT_Z, BTN_rZ);
    SET_BUTTON(BUTTON_LEFT_Z, BTN_lZ);
    SET_BUTTON(BUTTON_UP, BTN_up);
    SET_BUTTON(BUTTON_DOWN, BTN_down);
    SET_BUTTON(BUTTON_LEFT, BTN_left);
    SET_BUTTON(BUTTON_RIGHT, BTN_right);
    SET_BUTTON(NO_BUTTON, 0);
    
    return 1;

fend:
    _delay_us(20);
    twi_stop();
    return 0;
}


/* This function sets up stuff */
void myInit(void)
{
    _delay_ms(300);
    myI2CInit();
    _delay_ms(120);
    myWiiInit();
    _delay_ms(1);
    fillReportWithWii();
}


void setGameportButton(uint8_t button, bool pressed)
{
    if (pressed)
    {
        // make pin an output and set to low
        CLR_BIT(PORTC, button);
        SET_BIT(DDRC, button);
    } else {
        // make pin an input (high impedance) and set to high (pull up)
        CLR_BIT(DDRC, button);
        SET_BIT(PORTC, button);
    }
}




typedef enum 
{
    AXIS_X_1 = 0,
    AXIS_Y_1 = 2,
    AXIS_X_2 = 4,
    AXIS_Y_2 = 6,
} Axis;

typedef enum
{
    POS_MIN,
    POS_NEUTRAL,
    POS_MAX,
} Position;


void setAxis(Axis axis, Position pos)
{
    switch(pos)
    {
        case POS_MIN:
            SET_BIT(PORTD, 0 + axis);
            CLR_BIT(PORTD, 1 + axis);
            break;
        case POS_NEUTRAL:
            CLR_BIT(PORTD, 0 + axis);
            SET_BIT(PORTD, 1 + axis);
            break;
        case POS_MAX:
            SET_BIT(PORTD, 0 + axis);
            SET_BIT(PORTD, 1 + axis);
            break;
    }
}

#define buttonPressed(button, buffer) ((buffer.buttons[button/8] & (1 << (button%8))) != 0)


typedef enum
{
    UNINITIALIZED,
    NORMAL_MODE,
    JUMP_RUN_MODE,
    NES_MODE,
} AdapterMode;


/**
 * This function takes the global variable report
 * and sets the gameport output accordingly.
 */
void setGameport(AdapterMode mode)
{
    bool jump = false;

    if (mode == JUMP_RUN_MODE)
    {
        setGameportButton(0, buttonPressed(BUTTON_Y, report));
        setGameportButton(1, buttonPressed(BUTTON_A, report));
        jump = buttonPressed(BUTTON_B, report);
    }
    else if (mode == NES_MODE)
    {
        setGameportButton(0, buttonPressed(BUTTON_A, report));
        setGameportButton(1, buttonPressed(BUTTON_B, report));
        setGameportButton(2, buttonPressed(BUTTON_START, report));
        setGameportButton(3, buttonPressed(BUTTON_SELECT, report));
    }
    else
    {
        setGameportButton(0, buttonPressed(BUTTON_B, report));
        setGameportButton(1, buttonPressed(BUTTON_Y, report));
        setGameportButton(2, buttonPressed(BUTTON_A, report));
        setGameportButton(3, buttonPressed(BUTTON_X, report));
    }


    if (buttonPressed(BUTTON_LEFT, report))
    {
        setAxis(AXIS_X_1, POS_MIN);
    }
    else if (buttonPressed(BUTTON_RIGHT, report))
    {
        setAxis(AXIS_X_1, POS_MAX);
    }
    else
    {
        setAxis(AXIS_X_1, POS_NEUTRAL);
    }

    if (buttonPressed(BUTTON_UP, report) || jump)
    {
        setAxis(AXIS_Y_1, POS_MIN);
    }
    else if (buttonPressed(BUTTON_DOWN, report))
    {
        setAxis(AXIS_Y_1, POS_MAX);
    }
    else
    {
        setAxis(AXIS_Y_1, POS_NEUTRAL);
    }
    
}


void setupGameport()
{
    // set buttons to off position
    CLR_BIT(DDRC, 0);
    CLR_BIT(DDRC, 1);
    CLR_BIT(DDRC, 2);
    CLR_BIT(DDRC, 3);
    CLR_BIT(PORTC, 0);
    CLR_BIT(PORTC, 1);
    CLR_BIT(PORTC, 2);
    CLR_BIT(PORTC, 3);

    // set gameport axes to neutral
    SET_BIT(DDRD, 0);
    SET_BIT(DDRD, 1);
    SET_BIT(DDRD, 2);
    SET_BIT(DDRD, 3);
    SET_BIT(DDRD, 4);
    SET_BIT(DDRD, 5);
    SET_BIT(DDRD, 6);
    SET_BIT(DDRD, 7);
    setAxis(AXIS_X_1, POS_NEUTRAL);
    setAxis(AXIS_Y_1, POS_NEUTRAL);
    setAxis(AXIS_X_2, POS_MAX);
    setAxis(AXIS_Y_2, POS_MAX);
}


int main(void)
{
    AdapterMode adapterMode = NORMAL_MODE;
    AdapterMode lastAdapterMode = UNINITIALIZED;

start:
    cli();
    wdt_disable();
    /* Even if you don't use the watchdog, turn it off here. On newer devices,
     * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
     */


    report.buttons[0] = 0;
    report.buttons[1] = 0;

    // make PORTB_0 (LED) an output pin
    SET_BIT(DDRB, 0);

    for (int i = 0; i < 5; ++i)
    {
        SET_BIT(PORTB, 0);
        _delay_ms(25);
        CLR_BIT(PORTB, 0);
        _delay_ms(25);
    }

    sei();

    myInit();
    setupGameport();

    for(;;){                /* main event loop */
        wdt_reset();

        // check if mode has changed, if it did change then reset ports
        if (adapterMode != lastAdapterMode)
        {
            setupGameport();
        }
        lastAdapterMode = adapterMode;

        fillReportWithWii();
        setGameport(adapterMode);
        
        if (buttonPressed(BUTTON_SELECT, report) && buttonPressed(BUTTON_UP, report))
        {
            adapterMode = JUMP_RUN_MODE;
        }

        if (buttonPressed(BUTTON_SELECT, report) && buttonPressed(BUTTON_DOWN, report))
        {
            adapterMode = NORMAL_MODE;
        }

        if (buttonPressed(BUTTON_SELECT, report) && buttonPressed(BUTTON_RIGHT, report))
        {
            adapterMode = NES_MODE;
        }

        /* If the gamepad starts feeding us 0xff, we have to restart to recover */
        if ((rawData[0] == 0xff) && (rawData[1] == 0xff) && (rawData[2] == 0xff) && (rawData[3] == 0xff) && (rawData[4] == 0xff) && (rawData[5] == 0xff)) {
            goto start;
        }
    }
    return 0;
}
