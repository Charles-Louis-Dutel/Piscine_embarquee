#include "includes/main.h"


void receive_color(char *color_code)
{
    uint8_t i = 0;
    char    c;

    while((c = uart_rx()) && c != '\r')
    {
        if (i > 0 && c == 127)
        {
            uart_printstr("\b \b");
            i--;
        }
        else if (i < 7 && ft_isprint(c))
        {
            uart_tx(c);
            color_code[i] = c;
            i++;
        }
    }
    color_code[i] = '\0';
}

uint8_t check_color_code_validity(const char *color_code)
{
    uint8_t i = 0;

    while (color_code[i])
    {
        if (i == 0 && color_code[i] != '#')
            return (0);
        else if (i > 0 && !ft_is_hexa(color_code[i]))
            return (0);
        i++;
    }
    return (1);
}