#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define PRESCALER_DIV 64

#define PRESSED 1
#define UNPRESSED 0

void INT0_vect(void) __attribute__((signal));
void TIMER1_COMPA_vect(void) __attribute__((signal));

volatile uint8_t state = 0;

void INT0_vect(void)
{
    if (state == UNPRESSED)
        state = 1;
    else if (state == PRESSED)
        state = 0;
    //Desactive interrupt du bouton
    EIMSK = 0;
    //Remet le compteur a 0
    TCNT1 = 0;
    //Clear le flag du timer
    TIFR1 |= (1 << OCF1A);
    //Lance le timer
    TCCR1B |= (1 << CS10) | (1 << CS11);
}


void TIMER1_COMPA_vect(void)
{
    //Desactive le timer
    TCCR1B &= ~((1 << CS10) | (1 << CS11));

    if (state == PRESSED)
    {
        PORTB ^= (1 << PB0);
        //Active l'interrupt du bouton en mode rising edge
        EICRA = (1 << ISC00) | (1 << ISC01);
    }
    else if (state == UNPRESSED)
    {
        //Active l'interrupt du bouton en mode falling edge
        EICRA = (1 << ISC01);
    }
    
    //Clear le flag du bouton
    EIFR |= (1 << INTF0);
    //Active l'interrupt du bouton
    EIMSK = (1 << INT0);
}

void init_switch(void)
{
    PORTD = (1 << PD2);
}


void init_led(void)
{
    DDRB = (1 << PB0);
}


void init_timer(void)
{
    TCCR1B = (1 << WGM12);

    OCR1A = (F_CPU/PRESCALER_DIV) * 0.02 - 1;
}


void init_interrupt(void)
{
    //Permet de definir comment l'interrupt correspondant au bouton SW1 est
    //déclenchée, on le met en falling edge pour déclencher l'interrupt
    //quand le bouton est pressé.
    //ISC01 a 1 -> reg EICRA (p.80)
    EICRA = (1 << ISC01);
    //Permet d'activer l'interrupt correspondant au bouton SW1
    //INT0 a 1 -> reg EIMSK (p.81)
    EIMSK = (1 << INT0);

    //Active l'interrupt du timer
    TIMSK1 = (1 << OCIE1A);

    SREG |= (1 << SREG_I);
}

int main ()
{
    init_switch();
    init_led();
    init_timer();
    init_interrupt();

    while (1)
    {
    }
}