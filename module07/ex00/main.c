#include "includes/main.h"

//EEPROM Data Memory (p.29)
//Reading the EEPROM (p.35)(p.300)

unsigned char read_eeprom(uint16_t adress)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
        ;

    /*Set up adress register*/
    EEAR = adress;

    /*Start eeprom read by writing EERE*/
    EECR |= (1 << EERE);

    return (EEDR);
}


void print_eeprom(void)
{
    uint16_t        i = 0;
    uint8_t         octet = 0;
    uint8_t         c = 0;
    unsigned char   line[17];

    uart_printstr("\r\n--- EEPROM DUMP ---\r\n");
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


int main ()
{
    unsigned int    ubrr = (F_CPU/(8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    //eeprom_update_byte((uint8_t *)10, 'M');
    print_eeprom();

    while (1)
    {
    }
}