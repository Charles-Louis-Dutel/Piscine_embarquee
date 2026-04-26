#include "includes/main.h"


uint8_t ft_is_print(unsigned char c)
{
    if (c >= 32 && c <= 126)
        return (1);
    return (0);
}


uint8_t ft_is_hexa(unsigned char c)
{
    uint8_t i = 0;

    while (HEXA_MIN[i])
    {
        if (c == HEXA_MIN[i])
            return (1);
        i++;
    }
    return (0);
}


uint8_t ft_strlen(const char *str)
{
    uint8_t i = 0;

    while (str[i])
        i++;
    return (i);
}


uint8_t hexa_to_ui(unsigned char c)
{
    uint8_t i = 0;

    while(HEXA_MIN[i])
    {
        if (c == HEXA_MIN[i])
            break;
        i++;
    }
    return (i);
}
