#include "includes/main.h"


volatile uint8_t count = 0;


void TIMER1_COMPA_vect(void)
{
    //Desactive le timer
    TCCR1B &= ~((1 << CS10) | (1 << CS11));

    if (active_switch == SWITCH_1 && state_sw1 == PRESSED)
    {
        ft_copy_table(0);
        full_SPI_frame();
        active_color++;
        if (active_color == 4)
            active_color = BLUE;
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
        ft_copy_table(1);
        full_SPI_frame();
        active_led++;
        if (active_led == 4)
            active_led = D6;
    }
    
    //Clear le flag des boutons
    EIFR |= (1 << INTF0);
    PCIFR |= (1 << PCIF2);
    //Active l'interrupt des boutons
    EIMSK = (1 << INT0);
    PCICR = (1 << PCIE2);
}


void init_timer1(void)
{
    TCCR1B |= (1 << WGM12);

    OCR1A = (F_CPU / PRESCALER_DIV) * 0.02 - 1;
}
