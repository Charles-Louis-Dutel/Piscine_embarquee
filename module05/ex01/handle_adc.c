#include "includes/main.h"

static volatile uint8_t adc_src = POT;
static volatile uint8_t data = THROW;
static volatile char to_print[13] = "xx, yy, zz\r\n";

void get_data(uint8_t src)
{
    uint8_t value = ADCL;
    value = ADCH;

    uint8_t less_significant_bits = value & (0b00001111);
    uint8_t most_significant_bits = value >> 4;

    if (src == POT)
    {
        to_print[0] = HEXA[most_significant_bits];
        to_print[1] = HEXA[less_significant_bits];
    }
    else if (src == LDR)
    {
        to_print[4] = HEXA[most_significant_bits];
        to_print[5] = HEXA[less_significant_bits];
    }
    else if (src == NTC)
    {
        to_print[8] = HEXA[most_significant_bits];
        to_print[9] = HEXA[less_significant_bits];
    }
}


void ADC_vect(void)
{
    if (data == THROW)
    {
        data = KEEP;
        return;
    }
    if (adc_src == POT)
    {
        get_data(POT);
        ADMUX |= (1 << MUX0);
        ADMUX &= ~((1 << MUX1) | (1 << MUX2) | (1 << MUX3));
        adc_src = LDR;
    }
    else if (adc_src == LDR)
    {
        get_data(LDR);
        ADMUX |= (1 << MUX1);
        ADMUX &= ~((1 << MUX0) | (1 << MUX2) | (1 << MUX3));
        adc_src = NTC; 
    }
    else if (adc_src == NTC)
    {
        get_data(NTC);
        ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3));
        adc_src = POT;
    }
    data = THROW;
}


void TIMER1_COMPA_vect(void)
{
    
    uart_printstr(to_print);
}