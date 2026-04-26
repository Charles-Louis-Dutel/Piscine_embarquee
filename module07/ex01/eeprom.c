#include "includes/main.h"

unsigned char read_eeprom(uint16_t adress)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
        ;

    /*Set up adress register*/
    EEAR = adress;

    /*Start eeprom read by writing EERE*/
    EECR |= (1 << EERE);

    return (EEDR);
}