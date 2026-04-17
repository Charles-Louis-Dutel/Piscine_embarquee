#include "includes/main.h"


int ft_strcmp(char *s1, char *s2)
{
    uint8_t i = 0;

    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    if (s1[i] != s2[i])
        return (0);
    return (1);
}

int ft_is_print(char c)
{
    if (c >= 32 && c <= 126)
        return (1);
    return (0);
}


void receive_username(char *username)
{
    uint8_t i = 0;
    char    c;
    while ((c = uart_rx()) && c != '\r')
    {
        if (i > 0 && c == 127)
        {
            uart_printstr("\b \b");
            i--;
        }
        else if (i < 20 && ft_is_print(c))
        {
            username[i] = c;
            uart_tx(c);
            i++;
        }
    }
    username[i] = '\0';
    uart_printstr("\r\n");
}


void receive_password(char *password)
{
    uint8_t i = 0;
    char    c;
    while ((c = uart_rx()) && c != '\r')
    {
        if (i > 0 && c == 127)
        {
            uart_printstr("\b \b");
            i--;
        }
        else if (i < 20 && ft_is_print(c))
        {
            password[i] = c;
            uart_tx('*');
            i++;
        }
    }
    password[i] = '\0';
    uart_printstr("\r\n");
}