#include <avr/io.h>
#include <util/delay.h>


int main ()
{
    uint8_t value = 0;
    DDRB |= (1 << PB0);

    //DDD2 est a 0, donc le pin est en input. On met le bit a 1 pour activer le
    //"pull-up resistor" ce qui permet d'eviter une valeur flotante qui est un etat inconnu
    //ou meme un court circuit potentiel.
    //https://learn.sparkfun.com/tutorials/pull-up-resistors/all
    PORTD |= (1 << PD2); 

    while (1)
    {
        //PINx = Port Input Pins (p.84)
        //Permet de lire la valeur du pin
        //Si la value combine des bits == 0, le bouton est presse, on allume la led,
        //sinon on l'eteint
        value = PIND & (1 << PD2);
        _delay_ms(20);
        if (value == 0)
            PORTB |= (1 << PB0);
        else
            PORTB &= ~(1 << PB0);
    }

    return (0);
}