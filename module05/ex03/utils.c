#include "includes/main.h"


void ft_putnbr(uint16_t n)
{
    if (n >= 0 && n <= 9)
        return (uart_tx(n + 48));
    else
    {
        ft_putnbr(n / 10);
        ft_putnbr(n % 10);
    }
}