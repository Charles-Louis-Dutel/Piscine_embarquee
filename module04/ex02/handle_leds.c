#include "includes/main.h"

static volatile uint8_t value = 0;


void change_leds_state(void)
{
    PORTB =
    (((value >> 0) & 1) << PB0) |
    (((value >> 1) & 1) << PB1) |
    (((value >> 2) & 1) << PB2) |
    (((value >> 3) & 1) << PB4);
}


void increment_value(void)
{
    value++;
    change_leds_state();
}


void decrement_value(void)
{
    value--;
    change_leds_state();
}
