#include "includes/main.h"

volatile uint8_t state_sw1 = UNPRESSED;
volatile uint8_t state_sw2 = UNPRESSED;
volatile uint8_t active_switch = 0;

void init_switch(void)
{
    PORTD = (1 << PD2) | (1 << PD4);
}


void init_led(void)
{
    DDRB = (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
}


void init_timer(void)
{
    TCCR1B = (1 << WGM12);
    OCR1A = (F_CPU/PRESCALER_DIV) * 0.02 - 1;
}


void init_interrupt(void)
{
    //Active l'interrupt du bouton en mode falling edge
    //ISC01 a 1 -> reg EICRA (p.80)
    EICRA = (1 << ISC01);
    //activer l'interrupt correspondant au bouton SW1
    //INT0 a 1 -> reg EIMSK (p.81)
    EIMSK = (1 << INT0);

    //Active l'interrupt pin change interrupt 2 qui active les interrupts
    //sur PCINT16 a PCINT23
    //PCIE2 a 1 -> reg PCICR (p.82)
    PCICR = (1 << PCIE2);
    //Active l'interrupt du bouton SW2
    //PCINT20 a 1 -> reg PCMSK2 (p.83)
    PCMSK2 = (1 << PCINT20);

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