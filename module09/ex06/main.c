#include "includes/main.h"

volatile uint16_t   count = 0;

void init_interrupt(void)
{
    TIMSK1 |= (1 << OCIE1A);

    SREG = (1 << SREG_I);
}

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
    unsigned int    ubrr = (F_CPU / (8 * UART_BAUDRATE)) - 1;

    uart_init(ubrr);
    i2c_init();
    init_interrupt();
    

    expander_pca955_write(CONFIG_PORT_0, (0xFF & ~(0b11110000)));
    expander_pca955_write(CONFIG_PORT_1, 0x00);
    
    init_timer();
    while (1)
    {
        
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00000000)));

        //digit 1
        display_number(count % 10);
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b10000000)));
        _delay_ms(1);

        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00000000)));

        //digit 2
        display_number((count / 10) % 10);
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b01000000)));
       _delay_ms(1);

        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00000000)));

        //digit 3
        display_number((count / 100) % 10);
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00100000)));
        _delay_us(1);

        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00000000)));

        //digit 4
        display_number((count / 1000) % 10);
        expander_pca955_write(OUTPUT_PORT_0, (0xFF & ~(0b00010000)));
        _delay_us(1);
    }
}