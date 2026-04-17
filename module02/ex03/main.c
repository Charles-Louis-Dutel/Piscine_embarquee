#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200

void USART_RX_vect(void) __attribute__((signal));
void uart_tx(char c);

void USART_RX_vect(void)
{
    //Lorsque le bit RXCn de UCSRnA passe a 1, le vecteur correspondant a l'interrupt
    //USART Rx Complete est appele.
    uart_tx(UDR0);
}

void invert_case(char *c)
{
    if (*c >= 'A' && *c <= 'Z')
        *c += 32;
    else if (*c >= 'a' && *c <= 'z')
        *c -= 32;
}

void uart_tx(char c)
{
    while (((UCSR0A & (1 << UDRE0)) >> UDRE0) != 1)
        ;
    invert_case(&c);
    
    UDR0 = c;
}


void uart_init(uint16_t ubrr)
{
    UCSR0A |= (1 << U2X0);

    //RXCIEn: RX Complete Interrupt Enable -> RXCIEn a 1 reg UCSRnB
    //Active une interrupt sur le flag RXCn (p.201)
    //Le bit RXCn de UCSRnA passe a 1 lorsqu'il y a de la data dans le buffer de reception UDR0
    //et mit a 0 lorsque le buffer est vide. (p.200)
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    UBRR0 = (unsigned char)ubrr;
}


int main()
{
    uint16_t ubrr = (F_CPU / (8 * UART_BAUDRATE)) - 1;
    
    SREG |= (1 << SREG_I);
    uart_init(ubrr);

    while (1)
    {
    }
} 