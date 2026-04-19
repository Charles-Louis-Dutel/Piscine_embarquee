#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//PORTD5 RED
//PORTD6 GREEN
//PORTD3 BLUE

//timer 0, led R(OC0B), led G(OC0A)
//timer 2, led B(OC2B)

void init_rgb()
{
    //reg DDRD (p.101)
    DDRD = (1 << DDD3) | (1 << DDD5) | (1 << DDD6);

    //timer0
    //reg TCCR0A (p.113)
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0B1) | (1 << COM0A1);
    //reg TCCR0B (p.116)
    TCCR0B |= (1 << CS02);

    //timer2
    //reg TCCR2A (p.162)
    TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1);
    //reg TCCR2B (p.165)
    TCCR2B |= (1 << CS21) | (1 << CS22);
}


void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0A = g;
    OCR0B = r;
    OCR2B = b;
}


void wheel(uint8_t pos)
{
    pos = 255 - pos;
    if (pos < 85)
    {
        set_rgb(255 - pos * 3, 0, pos * 3);
    }
    else if (pos < 170)
    {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    }
    else
    {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}


int main()
{
    uint8_t pos = 0;

    init_rgb();

    while (1)
    {
        wheel(pos);
        _delay_ms(100);
        pos++;
    }
}