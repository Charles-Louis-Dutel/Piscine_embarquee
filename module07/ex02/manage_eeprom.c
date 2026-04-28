#include "includes/main.h"

void print_eeprom(void)
{
    uint16_t        i = 0;
    uint8_t         octet = 0;
    uint8_t         c = 0;
    unsigned char   line[17];

    //uart_printstr("\r\n--- EEPROM DUMP ---\r\n");
    while (i < 1024)
    {
        c = read_eeprom(i);

        if (octet == 0)
        {
            print_adress_hexa(i);
            uart_tx(' ');
        }
        if (c >= 32 && c <= 126)
            line[octet] = c;
        else
            line[octet] = '.';
        print_hex_value(c);
        uart_tx(' ');
        octet++;
        if (octet == 16)
        {
            line[16] = '\0';
            uart_tx('|');
            uart_printstr((const char *)line);
            uart_printstr("|\r\n");
            octet = 0;
        }
        i++;
    }
}

