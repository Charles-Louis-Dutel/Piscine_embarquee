#include "includes/main.h"


void init_leds(void)
{
    DDRB = (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
    DDRD = (1 << PD3) | (1 << PD5) | (1 << PD6);
}

void init_interrupt(void)
{
    //Activer l'interrupt ADC
    //ADIE a 1 -> reg ADCSRA (p.258)
    ADCSRA |= (1 << ADIE);

    SREG |= (1 << SREG_I);
}


void init_adc(void)
{
    ADMUX = (1 << ADLAR) | (1 << REFS0);
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADATE) | (1 << ADSC) | (1 << ADEN);
}


void init_rgb(void)
{
    OCR0A = 0;
    OCR0B = 0;
    OCR2B = 0;

    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B |= (1 << CS02);
    TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1);
    TCCR2B |= (1 << CS21) | (1 << CS22);
}


int main()
{
    init_leds();
    init_interrupt();
    init_adc();
    init_rgb();


    while (1)
    {
    }
}