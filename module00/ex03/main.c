#include <avr/io.h>
#include <util/delay.h>

int main ()
{
    uint8_t state = 0;
    uint8_t unpressed_state = (1 << PD2);

    DDRB |= (1 << PB0);
    PORTD |= (1 << PD2);

    while (1)
    {

        state = PIND & (1 << PD2);
        //On check la valeur du pin correspondant au bouton, pour voir si il est
        //presse ou non.
        if (state != unpressed_state)
        {
            //Si il est presse on met un delai de 20ms pour eviter les rebonds
            //et on recheck la valeur du pin
            _delay_ms(20);
            state = PIND & (1 << PD2);
            if (state != unpressed_state)
            {
                //Si le bouton est presse on change l'etat de la led
                PORTB ^= (1 << PB0);
                while (state != unpressed_state)
                {
                    //On check l'etat du bouton tant qu'il n'a pas change
                    _delay_ms(20);
                    state = PIND & (1 << PD2);
                }
            }
        }
    }

    return (0);
}