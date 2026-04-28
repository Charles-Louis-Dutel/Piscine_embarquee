#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define PRESCALER_DIV 256
#define UART_BAUDRATE 115200

/*PARSE*/
#define HEXA "0123456789ABCDEF"
#define HEXA_MIN "0123456789abcdef"

/*LEDS*/
#define D6 0
#define D7 1
#define D8 2

/*ERROR*/
#define FORMAT_ERROR "Bad format, please try #RRGGBBDX in hexa or #FULLRAINBOW\r\n\r\n"

extern volatile uint8_t    d6_wheel;
extern volatile uint8_t    d7_wheel;
extern volatile uint8_t    d8_wheel;
extern volatile char    data[13];
extern volatile uint8_t led_colors[3][4];

void ADC_vect(void) __attribute__((signal));
void TIMER1_COMPA_vect(void) __attribute__((signal));


/*spi.c*/
void            SPI_master_init(void);
void            SPI_frame(uint8_t brightness, uint8_t b, uint8_t g, uint8_t r);
void            full_SPI_frame(void);


/*uart.c*/
void            uart_init(unsigned int ubrr);
unsigned char   uart_rx(void);
void            uart_tx(const char c);
void            uart_printstr(const char *str);
void            print_hex_value(uint8_t c);
void            ft_putnbr(int64_t n);


/*receive_data.c*/
void            receive_data(void);
uint8_t         check_data(void);
void            convert_data(void);


/*utils.c*/
uint8_t         ft_is_print(unsigned char c);
uint8_t         ft_is_hexa(unsigned char c);
uint8_t         ft_strlen(const char *str);
void            ft_trim(char *str);
uint8_t         ft_strcomp(const char *s1, const char *s2);
uint8_t         hexa_to_ui(unsigned char c);


/*timer.c*/
void            init_timer1(void);
void            activate_timer(void);
void            desactivate_timer(void);


/*rgb.c*/
void            wheel(uint8_t pos);
