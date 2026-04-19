#include "includes/main.h"

void init_rgb(void)
{
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B |= (1 << CS02);
    TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1);
    TCCR2B |= (1 << CS21) | (1 << CS22);
}


void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0A = g;
    OCR0B = r;
    OCR2B = b;
}


void convert_hexa(const char *color_code)
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t i = 1;

    while (color_code[i])
    {
        if (i == 1)
            r = color_code[i] << 4;
        else if (i == 2)
            r = color_code[i] << 0;
        else if (i == 3)
            g = color_code[i] << 4;
        else if (i == 4)
            g = color_code[i] << 0;
        else if (i == 5)
            b = color_code[i] << 4;
        else if (i == 6)
            b = color_code[i] << 0;
        i++;
    }
    set_rgb(r, g, b);
}