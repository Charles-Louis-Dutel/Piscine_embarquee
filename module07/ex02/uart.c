#include "includes/main.h"

void uart_init(unsigned int ubrr)
{
    UCSR0A |= (1 << U2X0);
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
    UBRR0 = ubrr;
}


unsigned char uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0)))
        ;
    
    return (UDR0);
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


void print_hex_value(uint8_t c)
{
    uint8_t low = c & 0b00001111;
    uint8_t high = (c & 0b11110000) >> 4;

    uart_tx(HEXA_MIN[high]);
    uart_tx(HEXA_MIN[low]);
}


void print_adress_hexa(uint16_t adress)
{
    uint8_t low_0_7 = adress & 0x0F;
    uint8_t high_0_7 = (adress >> 4) & 0x0F;
    uint8_t low_8_15 = (adress >> 8) & 0x0F;
    uint8_t high_8_15 = (adress >> 12) & 0x0F;

    uart_printstr("0000");
    uart_tx(HEXA_MIN[high_8_15]);
    uart_tx(HEXA_MIN[low_8_15]);
    uart_tx(HEXA_MIN[high_0_7]);
    uart_tx(HEXA_MIN[low_0_7]);
}


void ft_putnbr(int64_t n)
{
    if (n < 0)
    {

    }
    if (n >= 0 && n <= 9)
        uart_tx(n + '0');
    else
    {
        ft_putnbr(n / 10);
        ft_putnbr(n % 10);
    }
}