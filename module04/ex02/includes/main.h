#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define PRESCALER_DIV 64

#define PRESSED 1
#define UNPRESSED 0

#define SWITCH_1 1
#define SWITCH_2 2

extern volatile uint8_t state_sw1;
extern volatile uint8_t state_sw2;
extern volatile uint8_t active_switch;

void INT0_vect(void) __attribute__((signal));
void PCINT2_vect(void) __attribute__((signal));
void TIMER1_COMPA_vect(void) __attribute__((signal));


/*handle_leds.c*/
void    increment_value(void);
void    decrement_value(void);
