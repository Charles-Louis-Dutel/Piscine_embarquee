#include "includes/main.h"

void i2c_start(void)
{
    //(p.225)
    //1. Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    //2. Wait for TWINT Flag set. This indicates that the START condition has been transmitted
    while (!(TWCR & (1 << TWINT)))
        ;
    
    //3. Check value of TWI Status Register. Mask prescaler bits. If status different
    //from START go to ERROR
    //START 0x08 00001000
    //      0xF8 11111000
    if ((TWSR & 0xF8) != TW_START)
    {
        print_status((TWSR & 0xF8));
        return (i2c_stop());
    }
    else
        print_status((TWSR & 0xF8));
    //Load SLA_W into TWDR Register. Clear TWINT bit in TWCR to start transmission
    //of address
    //SLA+W = AHT20 adress -> 0x38 | 0
    TWDR = (0x38 << 1) | 0;
    TWCR = (1 << TWINT) | (1 << TWEN);

    //4. Wait for TWINT Flag set. This indicates that the SLA+W has been transmitted,
    //and ACK/NACK has been received.
    while (!(TWCR & (1 << TWINT)))
        ;
    
    //5. Check value of TWI Status Register. Mask prescaler bits. If status different
    //from MT_SLA_ACK go to ERROR
    if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
    {
        print_status((TWSR & 0xF8));
        return(i2c_stop());
    }
    else
        print_status((TWSR & 0xF8));
}


void i2c_stop(void)
{
    //7. Transmit STOP condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}