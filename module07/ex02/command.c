#include "includes/main.h"


void create_default_config(void)
{
    current_config.magic_number = MAGIC;
    current_config.node_id = 0;
    current_config.priority = 0;
    ft_copy_and_fill_0((char *)current_config.tag, "Unconfigured", 33);
    compute_crc(&current_config.crc, &current_config.node_id, &current_config.priority, current_config.tag);
}


uint8_t status_command(void)
{
    if (is_configured == 1)
    {
        uart_printstr("Node ID: ");
        ft_putnbr(current_config.node_id);
        uart_printstr("\r\nPriority: ");
        ft_putnbr(current_config.priority);
        uart_printstr("\r\nSlot: ");
        ft_putnbr(current_slot);
        uart_printstr("\r\nTag: ");
        uart_printstr((const char *)current_config.tag);
        uart_printstr("\r\n");
        
        return (1);
    }
    else if (corruption_detected == 1)
    {
        uart_printstr("CRITICAL: Data corruption detected!\r\n");
        return (1);
    }
    uart_printstr("Node unconfigured\r\n");
    return (1);
}


uint8_t set_id_command(void)
{
    if (!ft_atoi((const char *)argument, UINT32))
    {
        uart_printstr(ID_ARG_ERROR);
        return (0);
    }
    compute_crc(&current_config.crc, &current_config.node_id, &current_config.priority, current_config.tag);
    
    return (1);
}


uint8_t set_priority_command(void)
{
    if (!ft_atoi((const char *)argument, INT16))
    {
        uart_printstr(PRIO_ARG_ERROR);
        return (0);
    }
    compute_crc(&current_config.crc, &current_config.node_id, &current_config.priority, current_config.tag);

    return (1);
}


uint8_t set_tag_command(void)
{
    if (is_configured == 0)
        create_default_config();
    ft_copy_and_fill_0((char *)current_config.tag, (char *)argument, 33);
    compute_crc(&current_config.crc, &current_config.node_id, &current_config.priority, current_config.tag);

    return (1);
}