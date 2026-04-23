#include "includes/main.h"


void handle_leds(uint8_t adc_value)
{
    if (adc_value < 64)
        PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));
    else if (adc_value >= 64 && adc_value < 128)
        PORTB = (1 << PB0);
    if (adc_value >= 128 && adc_value < 192)
        PORTB = (1 << PB0) | (1 << PB1);
    if (adc_value >= 192 && adc_value < 255)
        PORTB = (1 << PB0) | (1 << PB1) | (1 << PB2);
    if (adc_value == 255)
        PORTB = (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
}


void ADC_vect(void)
{
    uint8_t adc_value = ADCL;
    adc_value = ADCH;

    wheel(adc_value);
    handle_leds(adc_value);
}