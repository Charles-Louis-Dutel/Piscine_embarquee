#include "includes/main.h"


void expander_init()
{
    expander_pca955_write(POLARITY_PORT_0, 0x00);
    expander_pca955_write(POLARITY_PORT_1, 0x00);

    expander_pca955_write(OUTPUT_PORT_0, 0xFF);
    expander_pca955_write(OUTPUT_PORT_1, 0xFF);

    expander_pca955_write(CONFIG_PORT_0, (0xFF & ~(0b00001000)));
    expander_pca955_write(CONFIG_PORT_1, 0xFF);
}


int main()
{
    i2c_init();
    expander_init();

    while (1)
    {
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00001000)));
        _delay_ms(500);
        expander_pca955_write(OUTPUT_PORT_0, 0xFF);
        _delay_ms(500);
    }
}