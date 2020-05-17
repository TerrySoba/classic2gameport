#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include "bit_tools.h"

int main(void)
{
    cli();
    wdt_disable();

    // make PORTC_0 (LED) an output pin
    SET_BIT(DDRB, 0);


    CLR_BIT(DDRC, 0);
    CLR_BIT(DDRC, 1);
    CLR_BIT(DDRC, 2);
    CLR_BIT(DDRC, 3);
    CLR_BIT(PORTC, 0);
    CLR_BIT(PORTC, 1);
    CLR_BIT(PORTC, 2);
    CLR_BIT(PORTC, 3);


    SET_BIT(DDRD, 0);
    SET_BIT(DDRD, 1);
    SET_BIT(DDRD, 2);
    SET_BIT(DDRD, 3);

    for (;;)
    {
        SET_BIT(PORTB, 0);


        // R = 0 ohm
        SET_BIT(PORTD, 0);
        CLR_BIT(PORTD, 1);

        SET_BIT(PORTD, 2);
        CLR_BIT(PORTD, 3);



        SET_BIT(DDRC, 0);
        CLR_BIT(DDRC, 1);
        CLR_BIT(DDRC, 2);
        CLR_BIT(DDRC, 3);



        _delay_ms(500);
        CLR_BIT(PORTB, 0);

        // R = 50k ohm
        CLR_BIT(PORTD, 0);
        SET_BIT(PORTD, 1);

        CLR_BIT(PORTD, 2);
        SET_BIT(PORTD, 3);


        CLR_BIT(DDRC, 0);
        SET_BIT(DDRC, 1);
        CLR_BIT(DDRC, 2);
        CLR_BIT(DDRC, 3);


        _delay_ms(500);


        // R = 50k ohm
        SET_BIT(PORTD, 0);
        SET_BIT(PORTD, 1);

        SET_BIT(PORTD, 2);
        SET_BIT(PORTD, 3);


        CLR_BIT(DDRC, 0);
        CLR_BIT(DDRC, 1);
        SET_BIT(DDRC, 2);
        CLR_BIT(DDRC, 3);


        _delay_ms(500);


        CLR_BIT(DDRC, 0);
        CLR_BIT(DDRC, 1);
        CLR_BIT(DDRC, 2);
        SET_BIT(DDRC, 3);

        _delay_ms(500);

    }
}
