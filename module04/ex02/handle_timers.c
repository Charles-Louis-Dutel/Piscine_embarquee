#include "includes/main.h"



void TIMER1_COMPA_vect(void)
{
    //Desactive le timer
    TCCR1B &= ~((1 << CS10) | (1 << CS11));

    if (active_switch == SWITCH_1 && state_sw1 == PRESSED)
    {
        increment_value();
        //Active l'interrupt du bouton en mode rising edge
        EICRA = (1 << ISC00) | (1 << ISC01);
    }
    else if (active_switch == SWITCH_1 && state_sw1 == UNPRESSED)
    {
        //Active l'interrupt du bouton en mode falling edge
        EICRA = (1 << ISC01);
    }
    else if (active_switch == SWITCH_2 && state_sw2 == PRESSED)
    {
        decrement_value();
    }
    
    //Clear le flag des boutons
    EIFR |= (1 << INTF0);
    PCIFR |= (1 << PCIF2);
    //Active l'interrupt des boutons
    EIMSK = (1 << INT0);
    PCICR = (1 << PCIE2);
}