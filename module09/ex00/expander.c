#include "includes/main.h"


void expander_pca955_write(uint8_t command, uint8_t data)
{
    i2c_start(WRITE);
    //Command byte
    i2c_write(command);
    //Data byte
    i2c_write(data);
    i2c_stop();
}