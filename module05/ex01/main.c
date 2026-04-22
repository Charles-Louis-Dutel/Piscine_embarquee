#include "includes/main.h"


void init_uart(unsigned int ubrr)
{
    UCSR0A |= (1 << U2X0);
    UCSR0B |= (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
    UBRR0 = ubrr;
}


void init_interrupt(void)
{
    //Active interrupt Output Compare B Match
    TIMSK1 = (1 << OCIE1A);

    //Activer l'interrupt ADC
    //ADIE a 1 -> reg ADCSRA (p.258)
    ADCSRA |= (1 << ADIE);

    SREG |= (1 << SREG_I);
}


void init_adc(void)
{
    //AVCC with external capacitor at AREF pin : REFS0 a 1 -> reg ADMUX (p.257)
        //ADLAR a 1 -> reg ADMUX ??
    //Selectionner quel input analogique est connecte a ADC, ADC_POT -> ADC0
        //MUX0/3 a 0 -> reg ADMUX
    ADMUX = (1 << ADLAR) | (1 << REFS0);

    //Activer ADC
        //ADEN a 1 -> reg ADCSRA (p.258)
    //Commencer la conversion
        //ADSC a 1 -> reg ADCSRA
    //Activer l'auto trigger ADC
        //ADATE a 1 -> reg ADCSRA (p.258)
    //Activer l'interrupt ADC
        //ADIE a 1 -> reg ADCSRA (p.258)
    //Activer le presacler ADC pour ralentir l'horloge car CPU = 16MHz or ADC doit etre a
    //une valeur entre 50kHz et 200kHz (p.249)
    //16 000 000/128 = 125 000 = 125kHz
        //ADPS0/1/2 a 1 -> reg ADCSRA (p.258)
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADATE) | (1 << ADSC) | (1 << ADEN);
}


void init_timer(void)
{
    OCR1A = (F_CPU/PRESCALER_DIV) * 0.02 - 1;
 
    TCCR1B = (1 << CS10) | (1 << CS11) | (1 << WGM12);
}


int main ()
{
    unsigned int ubrr = F_CPU/(8*UART_BAUDRATE) - 1;

    init_uart(ubrr);
    init_interrupt();
    init_adc();
    init_timer();

    while (1)
    {
    }
}