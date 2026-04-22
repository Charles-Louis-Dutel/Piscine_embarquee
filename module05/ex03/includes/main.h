#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
# define F_CPU 16000000
#endif

#define PRESCALER_DIV 64
#define UART_BAUDRATE 115200

#define THROW 0
#define KEEP 1

#define POT 0
#define LDR 1
#define NTC 2

#define HEXA "0123456789ABCDEF" 

void ADC_vect(void) __attribute__((signal));
void TIMER1_COMPA_vect(void) __attribute__((signal));

/*uart.c*/
void uart_tx(char c);
void uart_printstr(volatile char *str);


/*utils.c*/
void ft_putnbr(uint16_t n);
