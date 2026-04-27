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
        else if (i < 64 && ft_is_print(c))
        {
            uart_tx((const char)c);
            data[i] = c;
            i++;
        }
    }
    data[i] = '\0';
    uart_printstr("\r\n");
}


uint8_t store_data(void)
{
    uint8_t i = 0;
    uint8_t j = 0;

    while (data[i] && data[i] == 32)
        i++;
    
    while (data[i] && data[i] != 32)
    {
        command[j] = data[i];
        j++;
        i++;
    }
    command[j] = '\0';

    while (data[i] && data[i] == 32)
        i++;

    j = 0;
    while (data[i])
    {
        argument[j] = data[i];
        i++;
        j++;
    }
    argument[j] = '\0';

    return (check_command());
}


// uint8_t convert_data(void)
// {
//     int8_t      i = 0;
//     int8_t      len = ft_strlen((const char *)adress_to_write);
//     uint8_t     bitshift = 0;
//     uint16_t    temp = 0;

//     octet_in_uint = 0;
//     adress_in_uint = 0;
//     i = len - 1;
//     while (i >= 0)
//     {
//         if (i < len - 3 && adress_to_write[i] != '0')
//         {
//             uart_printstr("Address is invalid\r\n");
//             return (0);
//         }
//         else if (i >= len - 3)
//         {
//             temp = hexa_to_ui(adress_to_write[i]);
//             temp = temp << bitshift;
//             bitshift += 4;
//             adress_in_uint |= temp;
//             if (adress_in_uint > 1023)
//             {
//                 // ft_putnbr(adress_in_uint);
//                 // uart_printstr("\r\n");
//                 uart_printstr("Address is invalid\r\n");
//                 return (0);
//             }
//         }
//         i--;
//     }

//     octet_in_uint = hexa_to_ui(octet_to_write[0]) << 4;
//     octet_in_uint |= hexa_to_ui(octet_to_write[1]);
    
//     return (1);
// }