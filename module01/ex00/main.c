#include <avr/io.h>

int main ()
{
    volatile int i = 0;
    volatile int j = 0;

    DDRB |= (1 << PB1);

    while (1)
    {
        i = 0;
        while (i < 100)
        {
            j = 0;
            while (j < 7500)
            {
                j++;
            }
            i++;
        }
        PORTB ^= (1 << PB1);
    }

    return (0);
}