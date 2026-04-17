#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200

#define USERNAME "admin"
#define PASSWORD "Password123"


/*uart.c*/
void        uart_init(uint16_t ubrr);
uint8_t     uart_rx(void);
void        uart_tx(char c);
void        uart_printstr(const char* str);


/*utils.c*/
int         ft_strcmp(char *s1, char *s2);
void        receive_username(char *username);
void        receive_password(char *password);
