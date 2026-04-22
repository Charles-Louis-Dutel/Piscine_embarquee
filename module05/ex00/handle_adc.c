#include "includes/main.h"

void ADC_vect(void)
{
    uint8_t value = ADCL;
    value = ADCH;

    uint8_t less_significant_bits = value & (0b00001111);
    uint8_t most_significant_bits = value >> 4;

    char    x = HEXA[most_significant_bits];
    char    y = HEXA[less_significant_bits];

    uart_tx(x);
    uart_tx(y);
    uart_tx('\r');
    uart_tx('\n');
}