#include "includes/main.h"

void INT0_vect(void)
{
    active_switch = SWITCH_1;
    if (state_sw1 == UNPRESSED)
        state_sw1 = 1;
    else if (state_sw1 == PRESSED)
        state_sw1 = 0;
    //Desactive interrupt des boutons
    EIMSK = 0;
    PCICR = 0;
    //Remet le compteur a 0
    TCNT1 = 0;
    //Clear le flag du timer
    TIFR1 |= (1 << OCF1A);
    //Lance le timer
    TCCR1B |= (1 << CS10) | (1 << CS11);
}


void PCINT2_vect(void)
{
    active_switch = SWITCH_2;
    if (state_sw2 == UNPRESSED)
        state_sw2 = 1;
    else if (state_sw2 == PRESSED)
        state_sw2 = 0;
    //Desactive interrupt des boutons
    EIMSK = 0;
    PCICR = 0;
    //Remet le compteur a 0
    TCNT1 = 0;
    //Clear le flag du timer
    TIFR1 |= (1 << OCF1A);
    //Lance le timer
    TCCR1B |= (1 << CS10) | (1 << CS11);
}