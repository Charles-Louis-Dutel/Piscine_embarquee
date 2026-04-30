#include "includes/main.h"

int main()
{
    i2c_init();

    expander_pca955_write(CONFIG_PORT_0, (0xFF & ~(0b00001000)));
    while (1)
    {
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00001000)));
        _delay_ms(500);
        expander_pca955_write(OUTPUT_PORT_0, 0xFF);
        _delay_ms(500);
    }
}