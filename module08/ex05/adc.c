#include "includes/main.h"


void ADC_vect(void)
{
    uint8_t value = ADCH;

    led_colors[active_led][active_color] = value;
    full_SPI_frame();
}


void init_adc(void)
{
    ADMUX = (1 << ADLAR) | (1 << REFS0);
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADATE) |
            (1 << ADSC) | (1 << ADEN);
    ADCSRB = 0;
}
