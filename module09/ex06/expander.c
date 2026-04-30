#include "includes/main.h"


void expander_pca955_write(uint8_t command, uint8_t data)
{
    i2c_start(WRITE);
    //Command byte
    i2c_write(command);
    //Data byte
    i2c_write(data);
    i2c_stop();
    _delay_us(10);
}


uint8_t expander_pca955_read(uint8_t reg_to_read)
{
    uint8_t data;

    i2c_start(WRITE);
    i2c_write(reg_to_read);
    i2c_stop();
    _delay_us(10);
    
    i2c_start(READ);
    //Data byte
    data = i2c_read();
    i2c_stop();
    _delay_us(10);

    return (data);
}