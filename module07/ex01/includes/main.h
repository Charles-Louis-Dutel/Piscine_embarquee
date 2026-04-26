#include <avr/io.h>
#include <avr/eeprom.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200

#define HEXA "0123456789ABCDEF"
#define HEXA_MIN "0123456789abcdef"
#define BAD_ENTRY "Bad entry, please try with this format: adress_in_hexa_min(1 to 8 char) \
space octet_in_hexa(2 char)\r\n"


extern volatile unsigned char   data[12];
extern volatile unsigned char   adress_to_write[9];
extern volatile unsigned char   octet_to_write[3];
extern volatile uint8_t         octet_in_uint;
extern volatile uint16_t        adress_in_uint;

/*uart.c*/
void            uart_init(unsigned int ubrr);
unsigned char   uart_rx(void);
void            uart_tx(const char c);
void            uart_printstr(const char *str);
void            print_hex_value(uint8_t c);
void            print_adress_hexa(uint16_t adress);
void            ft_putnbr(uint16_t n);


/*eeprom.c*/
unsigned char   read_eeprom(uint16_t adress);


/*receive_data.c*/
void            receive_data(void);
uint8_t         check_data(void);
void            store_data(void);
uint8_t         convert_data(void);


/*utils.c*/
uint8_t         ft_is_print(unsigned char c);
uint8_t         ft_is_hexa(unsigned char c);
uint8_t         ft_strlen(const char *str);
uint8_t         hexa_to_ui(unsigned char c);


