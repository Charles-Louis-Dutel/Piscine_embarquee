#include "includes/main.h"

volatile uint8_t active_led[4][3] = {
        {0xE0, 0xE0, 0xE0}, //No led
        {0xE1, 0xE0, 0xE0}, //D6
        {0xE1, 0xE1, 0xE0}, //D6 + D7
        {0xE1, 0xE1, 0xE1}  //D6 + D7 + D8
    };


void ADC_vect(void)
{
    uint8_t value = ADCH;

    if (value < 85)
        full_SPI_frame(active_led[0]);
    else if (value >= 85 && value < 170)
        full_SPI_frame(active_led[1]);
    else if (value >= 170 && value < 255)
        full_SPI_frame(active_led[2]);
    else if (value == 255)
        full_SPI_frame(active_led[3]);

}


void init_adc(void)
{
    ADMUX = (1 << ADLAR) | (1 << REFS0);
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADATE) |
            (1 << ADSC) | (1 << ADEN);
    ADCSRB = 0;
}
