#include "includes/main.h"

volatile uint8_t count = 0;


int main()
{
    unsigned int    ubrr = (F_CPU / (8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    i2c_init();

    expander_pca955_write(CONFIG_PORT_0, (0xFF & ~(0b10000000)));
    expander_pca955_write(CONFIG_PORT_1, 0x00);
    
    expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b10000000)));
    expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(0b10100100)));
    
    while (1)
    {
        
    }
}