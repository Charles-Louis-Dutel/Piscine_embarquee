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
