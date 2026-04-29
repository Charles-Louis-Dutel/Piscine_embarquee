#include "includes/main.h"


void init_interrupt(void)
{
    ADCSRA |= (1 << ADIE);

    SREG |= (1 << SREG_I);
}


int main()
{
    SPI_master_init();
    init_adc();
    init_interrupt();

    while (1)
    {
    }
}