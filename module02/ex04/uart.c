#include "includes/main.h"


void uart_init(uint16_t ubrr)
{
    UCSR0A |= (1 << U2X0);
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    UBRR0 = (unsigned char)ubrr;
}


uint8_t uart_rx(void)
{
    while (((UCSR0A & (1 << RXC0)) >> RXC0) != 1)
        ;
    return (UDR0);
}


void uart_tx(char c)
{
    while (((UCSR0A & (1 << UDRE0)) >> UDRE0) != 1)
        ;    
    UDR0 = c;
}


void uart_printstr(const char* str)
{
    while (*str != 0x00)
    {
        uart_tx(*str);
        str++;
    }
}