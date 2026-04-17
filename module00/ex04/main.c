#include <avr/io.h>
#include <util/delay.h>

int main ()
{
    uint8_t count = 0;
    uint8_t new_value = 0;
    uint8_t bit_3 = 0;
    uint8_t state = 0;
    uint8_t unpressed_sw1 = (1 << PD2);
    uint8_t unpressed_sw2 = (1 << PD4);

    PORTD |= (1 << PD2) | (1 << PD4);
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);

    while (1)
    {
        state = PIND & (1 << PD2);
        if (state != unpressed_sw1)
        {
            _delay_ms(20);
            state = PIND & (1 << PD2);
            if (state != unpressed_sw1)
            {
                count++;
                while (state != unpressed_sw1)
                {
                    state = PIND & (1 << PD2);
                    _delay_ms(20);
                }
            }
        }

        state = PIND & (1 << PD4);
        if (state != unpressed_sw2)
        {
            _delay_ms(20);
            state = PIND & (1 << PD4);
            if (state != unpressed_sw2)
            {
                count--;
                while (state != unpressed_sw2)
                {
                    state = PIND & (1 << PD4);
                    _delay_ms(20);
                }
            }
        }

        //Apres avoir checker si les boutons ont ete appuye ou non on passe a l'etape
        //allumer ou eteindre les leds, on remet les bits 0,1,2 et 4 a 0 dans un 1er temps.
        PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));
        
        new_value = 0;
        //On copie juste les bits 0,1 et 2 directement de la valeur de notre compteur
        new_value = count & 0b00000111;

        //Pour la valeur du bit 3 du compteur on doit l'isoler et la decaler au bit 4
        //pour la faire correspondre au bit de la led D4
        bit_3 = count & 0b00001000;
        bit_3 = bit_3 << 1;

        //On combine les bit 0,1,2 avec la valeur du bit 3 decale au bit 4
        new_value |= bit_3;

        //On passe les bit 0,1,2 et 4 de PORTB a la bonne valeur
        PORTB |= new_value;
    }
}