#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200

//CTRL A + K sortir de screen

//Baud rate : Le débit en bauds définit le nombre de changements d'état du
//signal transmis par seconde dans un canal de communication.
//Dans les systèmes embarqués et les capteurs inertiels, le débit en bauds fait
//généralement référence à la vitesse d'échange de bits de données sur une ligne série

void uart_init (uint16_t ubrr)
{
    //Activer le mode Double speed -> U2Xn a 1 reg UCSRnA (p.180/200)
    //On va mettre en mode "Asynchronous Double Speed" car on va interagir avec le pc sans
    //utiliser de clock externe. Le double speed permet de limiter le % d'erreur pour le
    //calcul de la valeur que l'on va inserer dans UBRRn
    UCSR0A |= (1 << U2X0);

    //Transmitter Enable -> TXENn a 1 reg UCSRnB (p.202)
    //Permet d'activer le transmetteur USART
    UCSR0B |= (1 << TXEN0);

    //Asynchronous Mode -> Table 20-8, UMSELn1/0 a 0 reg UCSRnC (p.202)
    //Parity Mode disabled -> Table 20-9, UPMn1/0 a 0 reg UCSRnC (P.203) 
    //Stop Bit 1-bit -> Table 20-10, USBSn a 0 reg UCSRnC (p.203)
    //Character size 8 bit -> Table 20-11, UCSZn2 a 0 reg UCSRnB, UCSZn1/0 a 1 reg UCSRnC (p.203)
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    //UBRRnL doit être calculé en fonction de UART_BAUDRATE et F_CPU
    UBRR0 = (unsigned char) ubrr;
}


void uart_tx(char c)
{
    //On check le flag qui permet d'indiquer que le buffer UDR0 est pret a recevoir de la data (p.200)
    while (((UCSR0A & (1 << UDRE0)) >> UDRE0) != 1)
        ;
    //On ecrit la data dans le buffer, le transmetteur est active donc le transmetteur va load
    //la data dans le "Transmit Shift Register" puis la data sera envoye via le pin TxD0 (p.200)
    UDR0 = c;
}


int main ()
{
    uint16_t ubrr = (F_CPU/(8*UART_BAUDRATE)) - 1;

    uart_init(ubrr);

    while (1)
    {
        uart_tx('Z');
        _delay_ms(1000);
    }
}