#include <avr/io.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define PRESCALER 256
#define TICK_PER_SEC (F_CPU/PRESCALER)

int main ()
{
    DDRB |= (1 << PB1);

    //Permet de de changer le comportement des pins correspondant selon le mode
    //que l'on veut utiliser, ici on veut le mode "Toggle OC1A/OC1B on Compare Match".
    //On doit avoir COM1A1 a 0 et COM1A0 a 1 qui permet de faire clignoter la led. (p.140)
    TCCR1A = (1 << COM1A0); //Toggle OC1A/OC1B on Compare Match (p.140).

    //Les bit WGM10 et 11 de TCCR1A et WGM12 et WGM13 de TCCR1B permettent de choisir le
    //mode d'operation du timer, ici on veut le mode "CTC = Clear Timer on Compare mode"
    //qui permet de reset le timer a 0 quand il y a un match de comparaison (p.132).
    //On doit mettre WGM12 a 1, WGM13, WGM11 et WGM10 a 0 (p.141).
    //On va aussi mettre un prescaler de 256 pour "ralentir" le timer et le faire
    //rentrer dans 16 bits en mettant CS12 a 1 et CS11 et CS10 a 0 (p.143)
    TCCR1B |= (1 << CS12) | (1 << WGM12);

    //On set le registre de comparaison a la valeur voulu pour obtenir un toggle toute
    //les 0.5s
    //16 000 000 / 256 = 62 500. 1 cycle = 62 500 tick, on divise par 2 pour 0.5s
    OCR1A = (TICK_PER_SEC / 2) - 1;

    while (1)
    {
    }

    return (0);
}