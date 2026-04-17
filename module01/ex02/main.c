#include <avr/io.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define PRESCALER 256
#define TICK_PER_SEC (F_CPU/PRESCALER)

int main ()
{
    DDRB |= (1 << PB1);

    //On va utiliser le Mode Fast PVM (Pulse Width Modulation) pour pouvoir mettre en
    //place un rapport cyclique.
    //Le mode permet de compter a partir de BOTTOM jusqu'a TOP puis restart a partir de
    //BOTTOM. (p.132)
    //On prend le mode ou on set ICR1 en TOP ce qui permet d'utiliser OCR1 pour definir
    //le temps du rapport cyclique. (p.133)
    //On va utiliser le "non inverting Compare Output mode" qui va permettre d'eteindre la
    //led lorsque la valeur de TCNT1 et OCR1A seront identique. (p.132)

    //Table 16.2 -> COM1A1 a 1 et COM1A0 a 0 pour utiliser le mode ou OC1a est clear au
    //compare match et sert apres de BOTTOM (p.140)
    //Table 16.4, ligne 14 -> set WGM11/12/13 a 1 pour le mode Fast PVM avec ICR1 en TOP (p.142)
    //Table 16.5 -> CS12 a 1, CS11/10 a 0 pour prescaleur a 256.
    TCCR1A |= (1 << WGM11) | (1 << COM1A1);
    TCCR1B |= (1 << CS12) | (1 << WGM12) | (1 << WGM13);

    //ICR1 TOP vaut 1 cycle, OCR1A 10% du cycle
    OCR1A = (TICK_PER_SEC / 10) - 1;
    ICR1 = TICK_PER_SEC - 1;

    while (1)
    {
    }

    return (0);
}