#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200
#define SCL_FREQUENCY 100000
#define PRESCALER 1

#define WRITE 0
#define READ 1

/*PC9555 ADDRESS*/
#define PCA9555_ADDRESS_WRITE 0b01000000
#define PCA9555_ADDRESS_READ 0b01000001

/*TWI STATUS CODES*/
#define TWI_START 0x08
#define TWI_MT_SLA_ACK 0x18
#define TWI_MR_SLA_ACK 0x40
#define TWI_MT_DATA_ACK 0x28
#define TWI_MR_DATA_ACK 0x50

/*REGISTER*/
#define INPUT_PORT_0 0x00
#define INPUT_PORT_1 0x01
#define OUTPUT_PORT_0 0x02
#define OUTPUT_PORT_1 0x03
#define POLARITY_PORT_0 0x04
#define POLARITY_PORT_1 0x05
#define CONFIG_PORT_0 0x06
#define CONFIG_PORT_1 0x07

#define ZERO 0b11000000
#define ONE 0b11111001
#define TWO 0b10100100
#define THREE 0b10110000
#define FOUR 0b10011001
#define FIVE 0b10010010
#define SIX 0b10000010
#define SEVEN 0b11111000
#define EIGHT 0b10000000
#define NINE 0b10010000


/*i2c.c*/
void            i2c_init(void);
void            i2c_start(uint8_t mode);
void            i2c_stop(void);
void            i2c_write(uint8_t data);
uint8_t         i2c_read(void);


/*expander.c*/
void            expander_pca955_write(uint8_t command, uint8_t data);
uint8_t         expander_pca955_read(uint8_t reg_to_read);


/*uart.c*/
void            uart_init(unsigned int ubrr);
void            uart_tx(const char c);
void            uart_printstr(const char *str);
void            ft_putnbr(uint16_t n);
