#include "includes/main.h"

static volatile uint16_t data_intern = 0;


void ADC_vect(void)
{
    data_intern = (ADC - 324.31) / 1.22;
}


void TIMER1_COMPA_vect(void)
{
    ft_putnbr(data_intern);
    uart_printstr("\r\n");
}