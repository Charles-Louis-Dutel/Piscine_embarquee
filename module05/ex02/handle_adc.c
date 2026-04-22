#include "includes/main.h"

static volatile uint8_t adc_src = POT;
static volatile uint8_t data = THROW;
static volatile uint16_t data_pot = 0;
static volatile uint16_t data_ldr = 0;
static volatile uint16_t data_ntc = 0;


void get_data(uint8_t src)
{
    if (src == POT)
        data_pot = ADC;
    else if (src == LDR)
        data_ldr = ADC;
    else if (src == NTC)
        data_ntc = ADC;
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
    ft_putnbr(data_pot);
    uart_printstr(", ");
    ft_putnbr(data_ldr);
    uart_printstr(", ");
    ft_putnbr(data_ntc);
    uart_printstr("\r\n");
}