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
    uint16_t    i = 0;
    int8_t      octet = 0;

    while (i < 1024)
    {
        print_hex_value(read_eeprom(i));
        uart_tx(' ');
        if (octet == 15)
        {
            uart_printstr("| |\r\n");
            octet = -1;
        }
        octet++;
        i++;
    }
}


int main ()
{
    unsigned int    ubrr = (F_CPU/(8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    print_eeprom();

    while (1)
    {
    }
}