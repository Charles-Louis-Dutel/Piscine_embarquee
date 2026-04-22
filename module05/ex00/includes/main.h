#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
# define F_CPU 16000000
#endif

#define PRESCALER_DIV 64
#define UART_BAUDRATE 115200

void TIMER1_COMPB_vect(void) __attribute__((signal));

/*uart.c*/
void uart_tx(char c);
