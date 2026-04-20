#include "includes/main.h"

void init_rgb(void)
{
    DDRD = (1 << DDD3) | (1 << DDD5) | (1 << DDD6);

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


uint8_t calculate_to_rgb(char x, char y)
{
    const char  hexa[17] = "0123456789ABCDEF";
    uint8_t     i = 0;
    uint8_t     rgb_value = 0;

    while (hexa[i])
    {
        if (x == hexa[i] || x == hexa[i] + 32)
        {
            rgb_value = i * 16;
            break;
        }
        i++;
    }
    i = 0;
    while (hexa[i])
    {
        if (y == hexa[i] || y == hexa[i] + 32)
        {
            rgb_value += i;
            break;
        }
        i++;
    }
    return (rgb_value);
}


void convert_hexa(const char *color_code)
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    r = calculate_to_rgb(color_code[1], color_code[2]);
    g = calculate_to_rgb(color_code[3], color_code[4]);
    b = calculate_to_rgb(color_code[5], color_code[6]);

    set_rgb(r, g, b);
}