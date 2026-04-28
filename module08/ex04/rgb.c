#include "includes/main.h"


static void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    if (d6_wheel == 1)
    {
        led_colors[0][1] = b;
        led_colors[0][2] = g;
        led_colors[0][3] = r;
    }
    if (d7_wheel == 1)
    {
        led_colors[1][1] = b;
        led_colors[1][2] = g;
        led_colors[1][3] = r;
    }
    if (d8_wheel == 1)
    {
        led_colors[2][1] = b;
        led_colors[2][2] = g;
        led_colors[2][3] = r;
    }
    full_SPI_frame();
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