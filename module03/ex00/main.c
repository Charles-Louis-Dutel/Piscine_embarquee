#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//PORTD5 RED
//PORTD6 GREEN
//PORTD3 BLUE

int main()
{
    DDRD = (1 << PORTD3) | (1 << PORTD5) | (1 << PORTD6);

    while (1)
    {
        PORTD = (1 << PORTD5);
        _delay_ms(1000);
        PORTD = (1 << PORTD6);
        _delay_ms(1000);
        PORTD = (1 << PORTD3);
        _delay_ms(1000);
    }
}