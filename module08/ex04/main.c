#include "includes/main.h"

volatile uint8_t    d6_wheel = 0;
volatile uint8_t    d7_wheel = 0;
volatile uint8_t    d8_wheel = 0;
volatile char       data[13];
volatile uint8_t    led_colors[3][4] = {
        {0xE1, 0x00, 0x00, 0x00}, //D6
        {0xE1, 0x00, 0x00, 0x00}, //D7
        {0xE1, 0x00, 0x00, 0x00}, //D8
    };

void init_interrupt(void)
{
    TIMSK1 |= (1 << OCIE1A);

    SREG |= (1 << SREG_I);
}


int main()
{
    unsigned int    ubrr = (F_CPU / (8 * UART_BAUDRATE)) - 1;
    

    SPI_master_init();
    uart_init(ubrr);
    init_timer1();
    init_interrupt();

    while (1)
    {
        uart_printstr("Please enter a color in #RRGGBBDX format: ");
        receive_data();
        if (check_data())
        {
            if (ft_strcomp((char *)data, "#FULLRAINBOW"))
            {
                d6_wheel = 1;
                d7_wheel = 1;
                d8_wheel = 1;
                activate_timer();
            }
            else
            {
                convert_data();
                full_SPI_frame();
                TIMSK1 |= (1 << OCIE0A);
            }
            uart_printstr("\r\n");
        }
    }
}