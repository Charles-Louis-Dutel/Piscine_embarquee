#include "includes/main.h"

volatile uint8_t count = 0;


int main()
{
    unsigned int    ubrr = (F_CPU / (8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    i2c_init();

    expander_pca955_write(CONFIG_PORT_0, (0xFF & ~(0b00001110)));
    while (1)
    {
        if ((expander_pca955_read(INPUT_PORT_0) & 0x01) == 0)
        {
            _delay_ms(20);
            while ((expander_pca955_read(INPUT_PORT_0) & 0x01) == 0)
                ;
            count++;
        }
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & (~(count) << 1)));
    }
}