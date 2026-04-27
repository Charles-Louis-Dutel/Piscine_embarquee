#include "includes/main.h"


volatile unsigned char  data[65];
volatile unsigned char  command[65];
volatile unsigned char  argument[65];


int main ()
{
    unsigned int    ubrr = (F_CPU/(8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    //eeprom_update_byte((uint8_t *)10, 'M');
    //print_eeprom();

    while (1)
    {


        uart_printstr("> ");
        receive_data();
        if (store_data())
        {

        }
        uart_printstr("\r\n");
    }
}