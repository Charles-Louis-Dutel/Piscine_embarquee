#include "includes/main.h"

volatile uint8_t count = 0;

void expander_init()
{
    expander_pca955_write(POLARITY_PORT_0, 0x00);
    expander_pca955_write(POLARITY_PORT_1, 0x00);

    expander_pca955_write(OUTPUT_PORT_0, 0xFF);
    expander_pca955_write(OUTPUT_PORT_1, 0xFF);

    expander_pca955_write(CONFIG_PORT_0, 0b11110001);
    expander_pca955_write(CONFIG_PORT_1, 0xFF);
}

int main()
{
    i2c_init();
    expander_init();
    
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