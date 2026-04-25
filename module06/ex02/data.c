#include "includes/main.h"

void extract_data(uint8_t i)
{
    uint32_t    temp = 0;

    temp = TWDR;
    if (i == 0)
    {
        temp = temp << 12;
        humidity_data |= temp;
    }
    else if (i == 1)
    {
        temp = temp << 4;
        humidity_data |= temp;
    }
    else if (i == 2)
    {
        humidity_data |= ((temp >> 4) & 0x0F);
        temp = (temp & 0x0F) << 16;
        temperature_data |= temp;
    }
    else if (i == 3)
    {
        temp = temp << 8;
        temperature_data |= temp;
    }
    else if (i == 4)
    {
        temperature_data |= temp;
    }
}


void convert_data(void)
{
    uint32_t humidity = 0;
    int32_t temperature = 0;
    uint32_t div = (1UL << 20);

    //RH[%] = (Srh / 2^20) * 100%
    //humidity = (humidity_data * 100) / div;
    humidity = (humidity_data * 1000) / div;
    humidity_mean += humidity;
    
    //T[℃] = (St / 2^20) * 200 - 50
    //temperature = ((int32_t)temperature_data * 200) / div - 50;
    temperature = (((int64_t)temperature_data * 20000) / div) - 5000;
    temperature_mean += temperature; 
}