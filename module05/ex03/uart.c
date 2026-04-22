#include "includes/main.h"

void uart_tx(char c)
{
    while (((UCSR0A & (1 << UDRE0)) >> UDRE0) != 1)
        ;
    UDR0 = c;
}


void uart_printstr(volatile char *str)
{
    while (*str)
    {
        uart_tx(*str);
        str++;
    }
}