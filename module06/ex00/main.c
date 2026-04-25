#include "includes/main.h"


void i2c_init(void)
{
    //On laisse les pin en input et on active les pull-up resistors
    PORTC |= (1 << PC4) | (1 << PC5);
    
    TWSR = 0;
    //Formule pour calculer SCL frequency = F_CPU/(16+2(TWBR)*(Prescaler div)) (p.222)
    //Donc TWBR = (F_CPU/SCL-16)/(2*Prescaler)
    TWBR =  (F_CPU/SCL_FREQUENCY-16)/(2*PRESCALER);
}


int main()
{
    unsigned int    ubrr = (F_CPU/(8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    i2c_init();

    i2c_start();
    i2c_stop();
    while (1)
    {
    }
}