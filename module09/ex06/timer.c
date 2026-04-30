#include "includes/main.h"


void TIMER1_COMPA_vect(void)
{
    count++;
    if (count == 10000)
        count = 0;
}


void init_timer(void)
{
    OCR1A = (F_CPU / PRESCALER_DIV) - 1;
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12);
}