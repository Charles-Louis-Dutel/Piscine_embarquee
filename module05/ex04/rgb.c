#include "includes/main.h"


void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    if (r == 0 && g == 0 && b == 0)
    {
        TCCR0A &= ~((1 << COM0A1) | (1 << COM0B1));
        TCCR2A &= ~(1 << COM2B1);
        PORTD &= ~((1 << PD3) | (1 << PD5) | (1 << PD6));
    }
    else
    {
        TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
        TCCR2A |= (1 << COM2B1);

        OCR0A = g;
        OCR0B = r;
        OCR2B = b;
    }
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