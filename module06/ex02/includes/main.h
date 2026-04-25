#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#ifndef F_CPU
# define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200
#define SCL_FREQUENCY 100000
#define PRESCALER 1

#define WRITE 0
#define READ 1

#define HEXA "0123456789ABCDEF"

#define START "A START condition has been transmitted"
#define REPEAT "A repeated START condition has been transmitted"
#define SLA_W_ACK "SLA+W has been transmitted; ACK has been received"
#define SLA_W_NACK "SLA+W has been transmitted; NOT ACK has been received"
#define DATA_ACK "Data byte has been transmitted; ACK has been received"
#define DATA_NACK "Data byte has been transmitted; NOT ACK has been received"
#define ARBITRATION "Arbitration lost in SLA+W or data bytes"


extern volatile uint32_t    humidity_data;
extern volatile uint32_t    temperature_data;
extern volatile uint32_t    humidity_mean;
extern volatile int32_t     temperature_mean;

/*i2c_protocols.c*/
void    i2c_start(uint8_t mode);
void    i2c_stop(void);
void    i2c_write(unsigned char data);
void    i2c_read(void);


/*uart.c*/
void    uart_init(unsigned int ubrr);
void    uart_tx(const char c);
void    uart_printstr(const char *str);
void    print_status(volatile uint8_t status);
void    print_hex_value(char c);
void    ft_putnbr(int32_t n);
void    print_decimal(volatile int32_t mean, uint8_t div);



/*data.c*/
void    extract_data(uint8_t i);
void    convert_data(void);

