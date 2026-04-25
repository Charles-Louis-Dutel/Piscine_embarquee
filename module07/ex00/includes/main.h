#include <avr/io.h>
#include <avr/eeprom.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200

#define HEXA "0123456789ABCDEF"

/*uart.c*/
void uart_init(unsigned int ubrr);
void uart_tx(const char c);
void uart_printstr(const char *str);
void print_hex_value(char c);
