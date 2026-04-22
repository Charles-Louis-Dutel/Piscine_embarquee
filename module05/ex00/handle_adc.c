#include "includes/main.h"

void TIMER1_COMPB_vect(void)
{
    uint8_t val = ADCL;
    uart_tx(ADCH);
}