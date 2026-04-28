#include "includes/main.h"

volatile uint8_t    active_switch = 0;
volatile uint8_t    active_color = BLUE;
volatile uint8_t    old_color_value = 0;
volatile uint8_t    active_led = D6;
volatile uint8_t    state_sw1 = UNPRESSED;
volatile uint8_t    state_sw2 = UNPRESSED;
volatile uint8_t    led_colors[3][4] = {
        {0xE1, 0x00, 0x00, 0x00}, //D6
        {0xE1, 0x00, 0x00, 0x00}, //D7
        {0xE1, 0x00, 0x00, 0x00}, //D8
    };

void init_interrupt(void)
{
    ADCSRA |= (1 << ADIE);
    TIMSK1 |= (1 << OCIE1A);
    EICRA = (1 << ISC00) | (1 << ISC01);
    EIMSK = (1 << INT0);
    PCICR = (1 << PCIE2);
    PCMSK2 = (1 << PCINT20);

    SREG |= (1 << SREG_I);
}


int main()
{
    unsigned int ubrr = (F_CPU / (8 * UART_BAUDRATE)) - 1;

    SPI_master_init();
    uart_init(ubrr);
    init_adc();
    init_switch();
    init_timer1();
    init_interrupt();
    uart_printstr("BLUE\r\n\r\n");

    while (1)
    {

    }
}