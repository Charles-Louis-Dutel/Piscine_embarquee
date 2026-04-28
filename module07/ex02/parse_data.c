#include "includes/main.h"

static uint8_t parse_status_arg(void)
{
    ft_trim((char *)argument);
    if (argument[0] != '\0')
    {
        uart_printstr(STATUS_ARG_ERROR);
        return (0);
    }
    return (status_command());
}


static uint8_t parse_id_arg(void)
{
    uint8_t i = 0;

    ft_trim((char *)argument);
    if (argument[0] == '\0')
    {
        uart_printstr(ID_ARG_ERROR);
        return (0);
    }
    while (argument[i])
    {
        if (!ft_is_num(argument[i]))
        {
            uart_printstr(ID_ARG_ERROR);
            return (0);
        }
        i++;
    }
    return (set_id_command());
}


static uint8_t parse_prio_arg(void)
{
    uint8_t i = 0;

    ft_trim((char *)argument);
    if (argument[0] == '\0')
    {
        uart_printstr(PRIO_ARG_ERROR);
        return (0);
    }
    if (argument[0] == '-')
        i = 1;
    while (argument[i])
    {
        if (!ft_is_num(argument[i]))
        {
            uart_printstr(PRIO_ARG_ERROR);
            return (0);
        }
        i++;
    }
    return (set_priority_command());
}


static uint8_t parse_tag_arg(void)
{
    uint8_t len;
    uint8_t i;

    ft_trim((char *)argument);
    len = ft_strlen((const char *)argument);
    if (len > 34 || len < 3)
    {
        uart_printstr(TAG_ARG_ERROR);
        return (0);
    }
    if (argument[0] != '"' || argument[len - 1] != '"')
    {
        uart_printstr(TAG_ARG_ERROR_1);
        return (0);
    }

    i = 1;
    while (argument[i] && i < len - 1)
    {
        if (!ft_is_alphanum(argument[i]) && argument[i] != '-' && argument[i] != '_')
        {
            uart_printstr(TAG_ARG_ERROR_2);
            return (0);
        }
        i++;
    }
    return (set_tag_command());
}


static uint8_t parse_reset_arg(void)
{
    ft_trim((char *)argument);
    if (argument[0] != '\0')
    {
        uart_printstr(FACTORY_RESET_ARG_ERROR);
        return (0);
    }
    return (factory_reset_command());
}


static uint8_t parse_corrupted_demo_arg(void)
{
    ft_trim((char *)argument);
    if (argument[0] != '\0')
    {
        uart_printstr(WRITE_CORRUPTED_ARG_ERROR);
        return (0);
    }
    simulate_fail = 1;
    return (1);
}


static uint8_t all_fail_demo_arg(void)
{
    ft_trim((char *)argument);
    if (argument[0] != '\0')
    {
        uart_printstr(ALL_FAIL_ARG_ERROR);
        return (0);
    }
    simulate_all_fail = 1;
    return (1);
}


uint8_t  check_command(void)
{
    if (ft_strcomp(STATUS, (const char *)command))
        return (parse_status_arg());
    else if (ft_strcomp(SET_ID, (const char *)command))
        return (parse_id_arg());
    else if (ft_strcomp(SET_PRIO, (const char *)command))
        return (parse_prio_arg());
    else if (ft_strcomp(SET_TAG, (const char *)command))
        return (parse_tag_arg());
    else if (ft_strcomp(FACTORY_RESET, (const char *)command))
        return (parse_reset_arg());
    else if (ft_strcomp(WRITE_CORRUPTED_DEMO, (const char *)command))
        return (parse_corrupted_demo_arg());
    else if (ft_strcomp(ALL_FAIL_DEMO, (const char *)command))
        return (all_fail_demo_arg());
    uart_printstr(INVALID_COMMAND);
    return (0);
}