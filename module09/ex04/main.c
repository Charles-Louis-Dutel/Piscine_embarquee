#include "includes/main.h"


void display_number(uint8_t n)
{
    switch (n)
    {
        case 0:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(ZERO)));
            break;
        case 1:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(ONE)));
            break;
        case 2:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(TWO)));
            break;
        case 3:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(THREE)));
            break;
        case 4:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(FOUR)));
            break;
        case 5:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(FIVE)));
            break;
        case 6:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(SIX)));
            break;
        case 7:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(SEVEN)));
            break;
        case 8:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(EIGHT)));
            break;
        case 9:
            expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(NINE)));
            break;
        default:
            ;
    }
}


int main()
{
    i2c_init();

    expander_pca955_write(CONFIG_PORT_0, (0xFF & ~(0b11000000)));
    expander_pca955_write(CONFIG_PORT_1, 0x00);
    
    
    while (1)
    {
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00000000)));

        expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(TWO)));
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b10000000)));
        _delay_ms(1);

        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00000000)));

        expander_pca955_write(OUTPUT_PORT_1, (0xFF & ~(FOUR)));
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b01000000)));
        _delay_ms(1);
    }
}