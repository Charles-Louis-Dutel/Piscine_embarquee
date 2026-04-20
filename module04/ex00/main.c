#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void INT0_vect(void) __attribute__((signal));

volatile uint8_t interrupt_flag = 0;

void INT0_vect(void)
{
    interrupt_flag = 1;
}


void init_switch(void)
{
    PORTD = (1 << PD2);
}


void init_led(void)
{
    DDRB = (1 << PB0);
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

    SREG |= (1 << SREG_I);
}

int main ()
{
    init_switch();
    init_led();
    init_interrupt();

    while (1)
    {
        if (interrupt_flag == 1)
        {
            //Desactive l'interrupt
            EIMSK &= ~(1 << INT0);
            //debounce
            _delay_ms(200);
            PORTB ^= (1 << PB0);
            interrupt_flag = 0;
            //Clear le flag d'interrupt
            EIFR |= (1 << INTF0);
            //Réactive l'interrupt
            EIMSK |= (1 << INT0);
        }
    }
}