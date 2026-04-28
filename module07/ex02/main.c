#include "includes/main.h"

/*parsing*/
volatile unsigned char  data[65];
volatile unsigned char  command[65];
volatile unsigned char  argument[65];


/*config*/
volatile struct config  current_config;
volatile uint8_t        current_slot = SLOT_1;
volatile uint8_t        is_configured = 0;
volatile uint8_t        corruption_detected = 0;
volatile uint8_t        simulate_fail = 0;
volatile uint8_t        simulate_all_fail = 0;

int main ()
{
    unsigned int    ubrr = (F_CPU/(8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    load_config_from_eeprom();

    while (1)
    {


        uart_printstr("> ");
        receive_data();
        if (store_data())
        {
            if (ft_strcomp(SET_ID, (const char *)command) || ft_strcomp(SET_PRIO, (const char *)command) ||
                ft_strcomp(SET_TAG, (const char *)command))
            {
                save_config();
                //print_eeprom();
            }
        }
        uart_printstr("\r\n");
    }
}