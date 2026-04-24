#include "includes/main.h"

void uart_init(unsigned int ubrr)
{
    UCSR0A |= (1 << U2X0);
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
    UBRR0 = ubrr;
}


void uart_tx(const char c)
{
    while (((UCSR0A & (1 << UDRE0)) >> UDRE0) != 1)
        ;
    UDR0 = c;
}


void uart_printstr(const char *str)
{
    while(*str)
    {
        uart_tx(*str);
        str++;
    }
}


void print_status(volatile uint8_t status)
{
    uint8_t low = status & 0b00001111;
    uint8_t high = status >> 4;

    uart_printstr("0x");
    uart_tx(HEXA[high]);
    uart_tx(HEXA[low]);
    uart_printstr("\r\n");
}