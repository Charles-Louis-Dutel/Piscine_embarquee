#include "includes/main.h"


void i2c_init(void)
{
    PORTC |= (1 << PC4) | (1 << PC5);

    TWSR = 0;
    //Formule pour calculer SCL frequency = F_CPU/(16+2(TWBR)*(Prescaler div)) (p.222)
    //Donc TWBR = (F_CPU/SCL-16)/(2*Prescaler)
    TWBR =  (F_CPU / SCL_FREQUENCY - 16) / (2 * PRESCALER);
}


void i2c_start(uint8_t mode)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)))
        ;
    
    if ((TWSR & 0xF8) != TWI_START)
        return (i2c_stop());
    
    if (mode == WRITE)
        TWDR =  PCA9555_ADDRESS_WRITE;
    else if (mode == READ)
        TWDR = PCA9555_ADDRESS_READ;
    
    TWCR = (1 << TWINT) | (1 << TWEN);
    
    while (!(TWCR & (1 << TWINT)))
        ;
    
    if (mode == WRITE)
    {
        if ((TWSR & 0xF8) != TWI_MT_SLA_ACK)
            return (i2c_stop());
    }
    else if (mode == READ)
    {
        if ((TWSR & 0xF8) != TWI_MR_SLA_ACK)
            return (i2c_stop());
    }
}


void i2c_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}


void i2c_write(uint8_t data)
{
    TWDR = data;

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 <<TWEA) ;

    while (!(TWCR & (1 << TWINT)))
        ;
    
    if ((TWSR & 0xF8) != TWI_MT_DATA_ACK)
        return (i2c_stop());
}


uint8_t i2c_read(void)
{
    //Master Receiver Mode (p.229)
    TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
    return (TWDR);
}
