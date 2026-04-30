#include "includes/main.h"


void ADC_vect(void)
{
    count = ADC;
}

void init_adc(void)
{
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADATE) | (1 << ADSC) | (1 << ADEN);
}