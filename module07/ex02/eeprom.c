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


void write_eeprom(uint16_t adress, uint8_t data)
{
    /*Wait for completion of previous write*/
    while (EECR & (1 << EEPE))
        ;
    
    /*Set up adress and data registers*/
    EEAR = adress;
    EEDR = data;

    /*Write logical one to EEMPE*/
    EECR |= (1 << EEMPE);

    /*Start eeprom write by setting EEPE*/
    EECR |= (1 << EEPE);
}