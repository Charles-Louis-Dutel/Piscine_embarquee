#include "includes/main.h"

//EEPROM Data Memory (p.29)
//Reading the EEPROM (p.35)(p.300)

volatile unsigned char  data[12];
volatile unsigned char  adress_to_write[9];
volatile unsigned char  octet_to_write[3];
volatile uint8_t        octet_in_uint;
volatile uint16_t       adress_in_uint;

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
    //print_eeprom();

    while (1)
    {
        octet_in_uint = 0;
        adress_in_uint = 0;

        uart_printstr("> ");
        receive_data();
        if(!check_data())
            uart_printstr(BAD_ENTRY);
        else
        {
            store_data();
            if (convert_data())
            {
                uart_printstr("adress : ");
                ft_putnbr(adress_in_uint);
                uart_printstr("\toctet : ");
                ft_putnbr(octet_in_uint);
                uart_printstr("\r\n");
            }
        }
        uart_printstr("\r\n");
    }
}