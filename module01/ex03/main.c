#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define PRESCALER 256
#define TICK_PER_SEC (F_CPU/PRESCALER)

#define MIN 10
#define MAX 100

int main ()
{
    volatile uint8_t state = 0;
    volatile uint8_t sw1_now, sw2_now = 0;
    volatile uint8_t sw1_prev, sw2_prev = 1;
    volatile uint8_t cycle_percentage = 1;

    DDRB |= (1 << PB1);
    DDRD |= (1 << PD2) | (1 << PD4);
    PORTD |= (1 << PD2) | (1 << PD4);

    TCCR1A |= (1 << WGM11) | (1 << COM1A1);
    TCCR1B |= (1 << CS12) | (1 << WGM12) | (1 << WGM13);

    OCR1A = (TICK_PER_SEC / 10) - 1;
    ICR1 = TICK_PER_SEC;

    while(1)
    {
        state = PIND;
        
        sw1_now = (state & (1 << PD2)) >> PD2;
        sw2_now = (state & (1 << PD4)) >> PD4;

        if (sw1_prev == 1 && sw1_now == 0)
        {
            if (cycle_percentage < 10)
                cycle_percentage++;
        }

        if (sw2_prev == 1 && sw2_now == 0)
        {
            if (cycle_percentage > 1)
                cycle_percentage --;
        }

        sw1_prev = sw1_now;
        sw2_prev = sw2_now;

        OCR1A = (TICK_PER_SEC / 10 * cycle_percentage) - 1;

        _delay_ms(20);
    }

    return (0);
}