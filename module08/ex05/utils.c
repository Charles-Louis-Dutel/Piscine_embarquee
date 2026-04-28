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
        if (c == HEXA_MIN[i] || c == HEXA[i])
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
        if (c == HEXA_MIN[i] || c == HEXA[i])
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


void ft_trim(char *str)
{
    int8_t len = ft_strlen(str) - 1;

    while (len >= 0 && str[len] == 32)
    {
        str[len] = '\0';
        len--;
    }
}


void ft_copy_and_fill_0(char *dest, char *to_copy, uint8_t size)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t len_to_copy = ft_strlen(to_copy);

    while (i < len_to_copy)
    {
        if (to_copy[i] != '"')
        {
            dest[j] = to_copy[i];
            j++;
        }
        i++;
    }
    while (j < size)
    {
        dest[j] = '\0';
        j++;
    }
}