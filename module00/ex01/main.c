#include <avr/io.h>

int main ()
{
    //DDRx = Data Direction Register (p.84)
    //Permet de definir la direction du pin. Si le bit est a 1, fonctionne
    //en output, si le bit est a 0, fonctionne en input. (p.85)
    //On passe le bit 0 de DDRB a 1. (p.100)
    DDRB |= (1 << PB0);

    //PORTx = Data Register (p.84)
    //Si le pin est en output, si le bit est a 1 la broche du port est a l'etat haut,
    //si le bit est a 0 la broche du port est a l'etat bas. (p.85)
    //On passe le bit 0 de PORTB a 1. (p.100)
    PORTB |= (1 << PB0);

    while(1)
    {
    }

    return (0);
}