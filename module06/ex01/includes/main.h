#include <avr/io.h>
#include <util/twi.h>

#ifndef F_CPU
# define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200
#define SCL_FREQUENCY 100000
#define PRESCALER 1

#define HEXA "0123456789ABCDEF"

#define START "A START condition has been transmitted"
#define REPEAT "A repeated START condition has been transmitted"
#define SLA_W_ACK "SLA+W has been transmitted; ACK has been received"
#define SLA_W_NACK "SLA+W has been transmitted; NOT ACK has been received"
#define DATA_ACK "Data byte has been transmitted; ACK has been received"
#define DATA_NACK "Data byte has been transmitted; NOT ACK has been received"
#define ARBITRATION "Arbitration lost in SLA+W or data bytes"

/*i2c_protocols.c*/
void i2c_start(void);
void i2c_stop(void);


/*uart.c*/
void uart_init(unsigned int ubrr);
void uart_tx(const char c);
void uart_printstr(const char *str);
void print_status(volatile uint8_t status);
