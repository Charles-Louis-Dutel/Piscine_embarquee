#include "includes/main.h"

//EEPROM Data Memory (p.29)
//Reading the EEPROM (p.35)(p.300)

volatile unsigned char  data[12];
volatile unsigned char  adress_to_write[9];
volatile unsigned char  octet_to_write[3];
volatile uint8_t        octet_in_uint;
volatile uint16_t       adress_in_uint;


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
                // uart_printstr("adress : ");
                // ft_putnbr(adress_in_uint);
                // uart_printstr("\toctet : ");
                // ft_putnbr(octet_in_uint);
                // uart_printstr("\r\n");

                if (!check_octet_eeprom())
                {
                    // uart_printstr("Octet different, on va le changer\r\n");
                    write_eeprom(adress_in_uint, octet_in_uint);
                    print_eeprom_with_red(adress_in_uint, octet_in_uint);
                }
            }
        }
        uart_printstr("\r\n");
    }
}