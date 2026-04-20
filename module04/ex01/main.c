#include "includes/main.h"


volatile uint8_t phase = 0;

void TIMER0_COMPA_vect(void) __attribute__((signal));


void TIMER0_COMPA_vect(void)
{
    if (phase == 0)
        increment_duty_cycle(&phase);
    else
        decrement_duty_cycle(&phase);
}


void init_led(void)
{
    DDRB = (1 << PB1);
}


void init_timer0(void)
{
    //On utilise le mode CTC sur le Timer0 pour générer l'interrupt
    //TCCR0A (p.113)
    TCCR0A = (1 << WGM01);
    //TCCR0B (p.116)
    TCCR0B = (1 << CS02);

    //On active l'interrupt pour le Compare Match A
    //TIMSK0 (p.118)
    TIMSK0 |= (1 << OCIE0A);
    
    //On va faire varier le duty cycle du Timer1 de 0 à 255 puis de 255 à 0 en 1s
    //On va donc calibrer le Timer0 pour envoyer 510 interruptions
    //1s/510 = 1.96ms -> 2ms
    //Pour déclencher une interruption toutes les 2ms
    //Pour pouvoir le faire tenir dans OCR0A:
    //(16 000 000/256) * 0.002 = 125
    OCR0A = ((F_CPU/PRESCALER_DIV) * 0.002) - 1;
}


void init_timer1()
{
    //Mode Fast PWM 8-bit, TOP correspond à 255, OCR1A = duty cycle
    //TCCR1A (p.140)
    TCCR1A = (1 << WGM10) | (1 << COM1A1);
    //Prescaler de 8 pour avoir une fréquence élevé : 16 000 000/(8*256) = 7 812 Hz
    //TCCR1B (p.142)
    TCCR1B = (1 << CS11) | (1 << WGM12);

    OCR1A = 0;
}


void init_interrupt(void)
{
    SREG |= (1 << SREG_I);
}

int main()
{
    init_led();
    init_timer0();
    init_timer1();
    init_interrupt();

    while (1)
    {

    }
}