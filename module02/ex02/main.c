#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
# define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200

//20.7.1 Receiving Frames with 5 to 8 Data Bits (p.189)
void uart_tx(char c)
{
    while (((UCSR0A & (1 << UDRE0)) >> UDRE0) != 1)
        ;
    UDR0 = c;
}

void uart_rx(void)
{
    while (((UCSR0A & (1 << RXC0)) >> RXC0) != 1)
        ;
    uart_tx(UDR0);
}

void uart_init(uint16_t ubrr)
{
    UCSR0A |= (1 << U2X0);
    //Receiver Enable -> RXENn a 1 reg UCSRnB (p.202)
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    UBRR0 = (unsigned char) ubrr;
}

int main()
{
    uint16_t ubrr = (F_CPU / (8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);

    while (1)
    {
        uart_rx();
    }
}