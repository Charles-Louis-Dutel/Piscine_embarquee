#include "includes/main.h"


void expander_init()
{
    expander_pca955_write(POLARITY_PORT_0, 0x00);
    expander_pca955_write(POLARITY_PORT_1, 0x00);

    expander_pca955_write(OUTPUT_PORT_0, 0xFF);
    expander_pca955_write(OUTPUT_PORT_1, 0xFF);

    expander_pca955_write(CONFIG_PORT_0, (0xFF & ~(0b10000000)));
    expander_pca955_write(CONFIG_PORT_1, 0x00);
}


int main()
{
    i2c_init();
    expander_init();
    
    expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b10000000)));
    expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(0b10100100)));

    while (1)
    {
        
    }
}