#include "includes/main.h"

/*parsing*/
volatile unsigned char  data[65];
volatile unsigned char  command[65];
volatile unsigned char  argument[65];


/*config*/
volatile struct config  current_config;
volatile uint8_t        current_slot = 0;
volatile uint8_t        is_configured = 0;
volatile uint8_t        corruption_detected = 0;

int main ()
{
    unsigned int    ubrr = (F_CPU/(8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    load_config_from_eeprom();
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