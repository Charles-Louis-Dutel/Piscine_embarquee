#include "includes/main.h"

void i2c_start(uint8_t mode)
{
    // if (mode == WRITE)
    //     uart_printstr("Write mode\r\n");
    // else
    //     uart_printstr("Read mode\r\n");
    //(p.225)
    //1. Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    //2. Wait for TWINT Flag set. This indicates that the START condition has been transmitted
    while (!(TWCR & (1 << TWINT)))
        ;
    
    //3. Check value of TWI Status Register. Mask prescaler bits.
    if ((TWSR & 0xF8) != TW_START && (TWSR & 0xF8) != TW_REP_START)
    {
        print_status((TWSR & 0xF8));
        return (i2c_stop());
    }
    //Load SLA_W/R into TWDR Register. Clear TWINT bit in TWCR to start transmission
    //of address
    if (mode == WRITE)
        TWDR = (0x38 << 1) | 0;
    else if (mode == READ)
        TWDR = (0x38 << 1) | 1;
    TWCR = (1 << TWINT) | (1 << TWEN);

    //4. Wait for TWINT Flag set. This indicates that the SLA+W/R has been transmitted,
    //and ACK/NACK has been received.
    while (!(TWCR & (1 << TWINT)))
        ;
    
    //5. Check value of TWI Status Register. Mask prescaler bits. If status different
    //from MT_SLA_ACK go to ERROR
    if (mode == WRITE)
    {
        if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
        {
            print_status((TWSR & 0xF8));
            return(i2c_stop());
        }
    }
    else if (mode == READ)
    {
        if ((TWSR & 0xF8) != TW_MR_SLA_ACK)
        {
            print_status((TWSR & 0xF8));
            return(i2c_stop());
        }
    }
}


void i2c_stop(void)
{
    //7. Transmit STOP condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}


void i2c_write(unsigned char data)
{
    //(p.225)
    //5. Load DATA into TWDR Register. Clear TWINT bit in TWCR to
    //start transmission of data
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);

    //6. Wait for TWINT Flag set. This indicates that the DATA has been
    //transmitted, and ACK/NACK has been received.
    while (!(TWCR & (1 << TWINT)))
        ;
    
    //7. Check value of TWI Status Register. Mask prescaler bits. If status different
    //from MT_DATA_ACK go to ERROR
    if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
    {
        print_status((TWSR & 0xF8));
        return(i2c_stop());
    }
}


void i2c_read(void)
{
    //Master Receiver Mode (p.229)
    uint8_t i = 0;

    while (i < 6)
    {
        TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
        while (!(TWCR & (1 << TWINT)))
            ;
        print_hex_value(TWDR);
        uart_tx(' ');
        i++;
    }
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
            ;
    print_hex_value(TWDR);
    uart_printstr("\r\n");
}