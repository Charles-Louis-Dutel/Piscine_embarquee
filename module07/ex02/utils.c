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


uint8_t ft_strcomp(const char *s1, const char *s2)
{
    uint8_t i = 0;

    if (ft_strlen(s1) != ft_strlen(s2))
        return (0);
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}


uint8_t ft_is_num(const char c)
{
    if (!(c >= '0' && c <= '9'))
        return (0);
    return (1);
}


uint8_t ft_is_alphanum(const char c)
{
    if (!(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z'))
        return (0);
    return (1);
}


void ft_trim(char *str)
{
    int8_t len = ft_strlen(str) - 1;

    while (len >= 0 && str[len] == 32)
    {
        str[len] = '\0';
        len--;
    }
}


void  ft_memcopy(void *to_copy, void *dest, uint16_t size)
{
    uint8_t     *ptr_to_copy = (uint8_t *)to_copy;
    uint8_t     *ptr_dest = (uint8_t *)dest;
    uint16_t    i = 0;

    while (i < size)
    {
        ptr_dest[i] = ptr_to_copy[i];
        i++;
    }
}