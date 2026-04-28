#include "includes/main.h"


void receive_data(void)
{
    uint8_t       i = 0;
    unsigned char c;

    while ((c = uart_rx()) && c != '\r')
    {
        if (i > 0 && c == 127)
        {
            uart_printstr("\b \b");
            i--;
        }
        else if (i < 12 && ft_is_print(c))
        {
            uart_tx((const char)c);
            data[i] = c;
            i++;
        }
    }
    data[i] = '\0';
    ft_trim((char *)data);
    uart_printstr("\r\n");
}


uint8_t check_data(void)
{
    uint8_t i = 1;

    if (ft_strlen((const char *)data) != 9 && !ft_strcomp((const char *)data, "#FULLRAINBOW"))
    {
        uart_printstr(FORMAT_ERROR);
        return (0);
    }
    if (ft_strcomp((const char *)data, "#FULLRAINBOW"))
        return (1);
    
    if (data[0] != '#')
    {
        uart_printstr(FORMAT_ERROR);
        return (0);
    }
    while (data[i])
    {
        if ((i < 7 && !ft_is_hexa(data[i])) || (i == 7 && data[i] != 'D') || (i == 8 &&
            (data[i] != '6' && data[i] != '7' && data[i] != '8')))
        {
            uart_printstr(FORMAT_ERROR);
            return (0);
        }
        i++;
    }    
    return (1);
}


void convert_data(void)
{
    TIMSK1 &= ~(1 << OCIE0A);
    uint8_t led = data[8] - '0';
    uint8_t red = hexa_to_ui(data[1]) * 16 + hexa_to_ui(data[2]);
    uint8_t green = hexa_to_ui(data[3]) * 16 + hexa_to_ui(data[4]);
    uint8_t blue = hexa_to_ui(data[5]) * 16 + hexa_to_ui(data[6]);

    // uart_printstr("red: ");
    // ft_putnbr(red);
    // uart_printstr("\r\ngreen: ");
    // ft_putnbr(green);
    // uart_printstr("\r\nblue: ");
    // ft_putnbr(blue);
    // uart_printstr("\r\n");
    if (led == 6)
    {
        d6_wheel = 0;
        led_colors[D6][1] = blue;
        led_colors[D6][2] = green;
        led_colors[D6][3] = red;
    }
    else if (led == 7)
    {
        d7_wheel = 0;
        led_colors[D7][1] = blue;
        led_colors[D7][2] = green;
        led_colors[D7][3] = red;
    }
    else if (led == 8)
    {
        d8_wheel = 0;
        led_colors[D8][1] = blue;
        led_colors[D8][2] = green;
        led_colors[D8][3] = red;
    }
    if (d6_wheel == 0 && d7_wheel == 0 && d8_wheel == 0)
        desactivate_timer();
}