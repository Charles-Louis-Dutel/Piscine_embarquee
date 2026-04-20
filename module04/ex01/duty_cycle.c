#include "includes/main.h"

volatile uint8_t duty_cycle = 0;

void increment_duty_cycle(volatile uint8_t *phase)
{
    duty_cycle++;
    OCR1A = duty_cycle;
    if (duty_cycle == 255)
        *phase = 1;
}


void decrement_duty_cycle(volatile uint8_t *phase)
{
    duty_cycle--;
    OCR1A = duty_cycle;
    if (duty_cycle == 0)
        *phase = 0;
}