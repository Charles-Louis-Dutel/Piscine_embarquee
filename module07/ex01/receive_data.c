#include "includes/main.h"


void receive_data(void)
{
    uint8_t       i = 0;
    unsigned char c;

    while ((c = uart_rx()) && c != '\r')
    {
        if (i > 0 && c == 127)
        {
            uart_printstr("\b \b");
            i--;
        }
        else if (i < 11 && ft_is_print(c))
        {
            uart_tx((const char)c);
            data[i] = c;
            i++;
        }
    }
    data[i] = '\0';
    uart_printstr("\r\n");
}


uint8_t check_data(void)
{
    uint8_t i = 0;
    uint8_t space = 0;
    uint8_t len_after_space = 0;

    while (data[i])
    {
        if (!ft_is_hexa(data[i]) && data[i] != 32)
            return (0);
        
        if (i > 8 && space == 0)
            return (0);
        
        if (space >= 1)
            len_after_space++;

        if (data[i] == 32 && i == 0)
            return (0);
        else if (data[i] == 32)
            space++;

        i++;
    }
    if (space != 1 || len_after_space != 2)
        return (0);

    return (1);
}


void store_data(void)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t space = 0;

    while (data[i])
    {
        if (data[i] == 32)
        {
            space++;
            adress_to_write[i] = '\0';
        }

        if (space == 0 && data[i] != 32)
            adress_to_write[i] = data[i];
        
        if (space == 1 && data[i] != 32)
        {
            octet_to_write[j] = data[i];
            j++;
        }
        i++;
    }
    octet_to_write[j] = '\0';

    // uart_printstr("adress_to_write : ");
    // uart_printstr((const char *)adress_to_write);
    // uart_printstr("\toctet_to_write : ");
    // uart_printstr((const char *)octet_to_write);
    // uart_printstr("\r\n");
}


uint8_t convert_data(void)
{
    int8_t      i = 0;
    int8_t      len = ft_strlen((const char *)adress_to_write);
    uint8_t     bitshift = 0;
    uint16_t    temp = 0;

    octet_in_uint = 0;
    adress_in_uint = 0;
    i = len - 1;
    while (i >= 0)
    {
        if (i < len - 3 && adress_to_write[i] != '0')
        {
            uart_printstr("Address is invalid\r\n");
            return (0);
        }
        else if (i >= len - 3)
        {
            temp = hexa_to_ui(adress_to_write[i]);
            temp = temp << bitshift;
            bitshift += 4;
            adress_in_uint |= temp;
            if (adress_in_uint > 1023)
            {
                // ft_putnbr(adress_in_uint);
                // uart_printstr("\r\n");
                uart_printstr("Address is invalid\r\n");
                return (0);
            }
        }
        i--;
    }

    octet_in_uint = hexa_to_ui(octet_to_write[0]) << 4;
    octet_in_uint |= hexa_to_ui(octet_to_write[1]);
    
    return (1);
}