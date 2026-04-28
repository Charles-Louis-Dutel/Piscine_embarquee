#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void ADC_vect(void) __attribute__((signal));


/*spi.c*/
void        SPI_master_init(void);
void        SPI_frame(uint8_t brightness, uint8_t b, uint8_t g, uint8_t r);
void        full_SPI_frame(volatile uint8_t *active_led);


/*adc.c*/
void        init_adc(void);
