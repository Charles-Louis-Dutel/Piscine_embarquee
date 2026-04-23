#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void ADC_vect(void) __attribute__((signal));

/*rgb.c*/
void wheel(uint8_t pos);
