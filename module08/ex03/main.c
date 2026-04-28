#include "includes/main.h"


void init_interrupt(void)
{
    ADCSRA |= (1 << ADIE);

    SREG |= (1 << SREG_I);
}


int main()
{
    uint8_t i = 0;
    uint8_t active_led[4][3] = {
        {0xE0, 0xE0, 0xE0}, //No led
        {0xE1, 0xE0, 0xE0}, //D6
        {0xE0, 0xE1, 0xE0}, //D7
        {0xE0, 0xE0, 0xE1}  //D8
    };

    SPI_master_init();
    init_adc();
    init_interrupt();

    while (1)
    {
    }
}