#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define PRESCALEUR_DIV 256

#define UART_BAUDRATE 115200

//***ACTIVER LES INTERRUPTIONS GLOBALE SANS sei()***
//7.7 Reset and Interrupt Handling
//Mettre a 1 le "Global Interrupt Enable" bit dans le "Status Register" (p.23)
//SREG – AVR Status Register -> I a 1 de SREG (p.20)


//7.7 Reset and Interrupt Handling (p.24)
//12.4 Interrupt Vectors in ATmega328 and ATmega328P (p.74)
//16.11.8 TIMSK1 – Timer/Counter1 Interrupt Mask Register (p.144)
//16.11.9 TIFR1 – Timer/Counter1 Interrupt Flag Register (p.145)


//Declaration qui permet de dire que TIMER1_COMPA_vect n'est pas une fonction normale,
//mais une routine d'interruption. Le nom correspond au vecteur defini dans le header AVR
//et qui correspond a l'interrupt Timer/Counter1 Compare Match A. Table 12-6, (p.74)
//L'attribut signal dit au compilateur de generer la fonction comme une ISR.
void TIMER1_COMPA_vect(void) __attribute__((signal));
void uart_printstr(const char* str);

volatile uint8_t count = 0;

void TIMER1_COMPA_vect(void)
{
    count++;
    if (count == 2)
    {
        uart_printstr("Hello World!\r\n");
        count = 0;
    }
}


void uart_tx(char c)
{
    while (((UCSR0A & (1 << UDRE0)) >> UDRE0) != 1)
        ;
    UDR0 = c;
}


void uart_printstr(const char* str)
{
    while (*str != 0x00)
    {
        uart_tx(*str);
        str++;
    }
}



void uart_init(uint16_t ubrr)
{
    UCSR0A |= (1 << U2X0);
    UCSR0B |= (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    UBRR0 = (unsigned char)ubrr;
}


void init_timer()
{
    //Mode CTC et prescaler 256
    TCCR1B = (1 << CS12) | (1 << WGM12);

    uint16_t tick_per_sec = (F_CPU/PRESCALEUR_DIV) - 1;
    OCR1A = tick_per_sec;

    //Active l'interrupt correspondant au Compare Match qui va declencher le Interrupt Vector
    //correspondant.
    //OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable -> OCIE1A a 1 de TIMSK1 (p.145)
    TIMSK1 |= (1 << OCIE1A);

    //Mettre a 1 le "Global Interrupt Enable" bit dans le "Status Register" (p.23)
    //SREG – AVR Status Register -> I a 1 de SREG (p.20)
    SREG |= (1 << SREG_I);
}


int main()
{
    uint16_t ubrr = (F_CPU / (8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    init_timer();

    while (1)
    {
    }
}

//Quand Timer1 atteint OCR1A :

// 1. le matériel détecte l’événement Compare Match A
// 2 .le flag matériel correspondant est posé
// 3 .si OCIE1A = 1 dans TIMSK1, l’interruption est considérée comme autorisée localement
// 4. si I = 1 dans SREG, elle est autorisée globalement
// 5. le CPU interrompt le flux normal
// 6. il sauvegarde l’adresse de retour
// 7. il saute à l’adresse du vecteur TIMER1_COMPA_vect
// 8. ta routine s’exécute
// 9. un RETI est fait à la fin
// 10. le CPU reprend là où il s’était arrêté