#include "includes/main.h"


volatile uint8_t count = 0;


void TIMER1_COMPA_vect(void)
{
    wheel(count);
    count++;
    if (count == 256)
        count = 0;
}


void init_timer1(void)
{
    TCCR1B |= (1 << WGM12);

    OCR1A = (F_CPU / PRESCALER_DIV) * 0.01 - 1;
}


void activate_timer(void)
{
    TCCR1B |= (1 << CS12);
}


void desactivate_timer(void)
{
    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
}
