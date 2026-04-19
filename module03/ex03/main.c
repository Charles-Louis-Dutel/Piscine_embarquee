#include "includes/main.h"


#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define PREPSCALER_DIV 256
#define UART_BAUDRATE 115200

int main()
{
    unsigned int    ubrr = (F_CPU/(8 * UART_BAUDRATE)) - 1;
    char            color_code[8];

    uart_init(ubrr);
    init_rgb();

    while (1)
    {
        uart_printstr("Please enter a color in format #RRGGBB: ");
        receive_color(color_code);
        uart_printstr("\r\n");
        if (!check_color_code_validity(color_code))
            uart_printstr("Color format is invalide !\r\n");
        uart_printstr("\r\n");
        convert_hexa(color_code);
    }
}