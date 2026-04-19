#include "includes/main.h"


uint8_t ft_isprint(const char c)
{
    if (c >= 32 && c <= 126)
        return (1);
    return (0);
}

uint8_t ft_is_hexa(const char c)
{
    const char  hexa[23] = "0123456789abcdefABCDEF";
    uint8_t     i = 0;

    while (hexa[i])
    {
        if (c == hexa[i])
            return (1);
        i++;
    }
    return (0);
}