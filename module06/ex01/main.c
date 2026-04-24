#include "includes/main.h"


void i2c_init(void)
{
    //On laisse les pin en input et on active les pull-up resistors
    PORTC |= (1 << PC4) | (1 << PC5);
    //Formule pour calculer SCL frequency = F_CPU/(16+2(TWBR)*(Prescaler div)) (p.222)
    //Donc TWBR = (F_CPU/SCL-16)/(2*Prescaler)
    TWSR = 0;
    TWBR =  (F_CPU/SCL_FREQUENCY-16)/(2*PRESCALER);
}


int main()
{
    unsigned int    ubrr = (F_CPU/(8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    i2c_init();

    while (1)
    {
        i2c_start(WRITE);
        _delay_ms(10);
        i2c_write(0xAC);
        i2c_write(0x33);
        i2c_write(0x00);
        i2c_stop();
        _delay_ms(80);
        i2c_start(READ);
        i2c_read();
        i2c_stop();
        _delay_ms(100);
    }
}