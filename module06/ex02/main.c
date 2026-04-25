#include "includes/main.h"

volatile uint32_t    humidity_data = 0;
volatile uint32_t    temperature_data = 0;
volatile uint32_t    humidity_mean = 0;
volatile int32_t     temperature_mean = 0;

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
    uint8_t         i = 0;

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
        convert_data();
        i++;
        if (i == 3)
        {
            uart_printstr("Temperature: ");
            print_decimal(temperature_mean / 3, 100);
            //ft_putnbr(temperature_mean / 3);
            uart_printstr(".C, Humidity: ");
            print_decimal(humidity_mean / 3, 10);
            uart_printstr("%\r\n");
            temperature_mean = 0;
            humidity_mean = 0;
            i = 0; 
        }
        i2c_stop();
        _delay_ms(100);
    }
}