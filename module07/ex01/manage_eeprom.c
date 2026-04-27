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


void print_eeprom_with_red(uint16_t adress, uint8_t octet_value)
{
    uint16_t        i = 0;
    uint8_t         octet = 0;
    uint8_t         c = 0;

    //uart_printstr("\r\n--- EEPROM DUMP ---\r\n");
    while (i < 1024)
    {
        c = read_eeprom(i);

        if (octet == 0)
        {
            print_adress_hexa(i);
            uart_tx(' ');
        }
        
        if (i == adress)
        {
            uart_tx(27);
            uart_printstr("[31m");
            print_hex_value(c);
            uart_tx(27);
            uart_printstr("[0m");
        }
        else
            print_hex_value(c);
        octet++;
        if (octet % 2 == 0)
            uart_tx(' ');
        if (octet == 16)
        {
            uart_printstr("\r\n");
            octet = 0;
        }
        i++;
    }
}


uint8_t check_octet_eeprom(void)
{
    uint8_t octet_eeprom = read_eeprom(adress_in_uint);

    // uart_printstr("Octet in eeprom : ");
    // ft_putnbr(octet_eeprom);
    // uart_printstr("\r\n");
    if (octet_eeprom == octet_in_uint)
        return (1);
    return (0);
}
