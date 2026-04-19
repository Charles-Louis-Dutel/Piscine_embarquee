#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/*uart.c*/
void    uart_init(unsigned int ubrr);
void    uart_tx(const char c);
void    uart_printstr(const char *str);
char    uart_rx(void);


/*receiving_data.c*/
void    receive_color(char *color_code);
uint8_t check_color_code_validity(const char *color_code);


/*utils.c*/
uint8_t ft_isprint(const char c);
uint8_t ft_is_hexa(const char c);


/*rgb.c*/
void init_rgb(void);
void convert_hexa(const char *color_code);
