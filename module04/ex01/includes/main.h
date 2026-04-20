#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
# define F_CPU
#endif

#define PRESCALER_DIV 256

/*duty_cycle.c*/
void    increment_duty_cycle(volatile uint8_t *phase);
void    decrement_duty_cycle(volatile uint8_t *phase);
