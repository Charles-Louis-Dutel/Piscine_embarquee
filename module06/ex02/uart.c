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


void print_hex_value(char c)
{
    uint8_t low = c & 0b00001111;
    uint8_t high = (c & 0b11110000) >> 4;

    uart_tx(HEXA[high]);
    uart_tx(HEXA[low]);
}


void ft_putnbr(int32_t n)
{
    if (n < 0)
    {
        uart_tx('-');
        n *= -1;
    }
    if (n >= 0 && n <= 9)
        uart_tx(n + '0');
    else
    {
        ft_putnbr(n / 10);
        ft_putnbr(n % 10);
    }
}


void print_decimal(volatile int32_t mean, uint8_t div)
{
    int32_t int_part = 0;
    int32_t decimal_part = 0;

    if (mean < 0)
    {
        uart_tx('-');
        mean = -mean;
    }

    int_part = mean / div;
    decimal_part = mean % div;

    ft_putnbr(int_part);
    uart_tx(',');

    if (decimal_part < 10 && div == 100)
        uart_tx('0');
    ft_putnbr(decimal_part);
}