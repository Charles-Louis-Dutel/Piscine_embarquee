#include "includes/main.h"

static uint8_t write_block_eeprom(uint16_t address, uint16_t size, volatile void *storage)
{
    uint8_t     *ptr = (uint8_t *)storage;
    uint16_t    i = 0;
    uint8_t     readed_octet;

    if (simulate_fail == 1 || simulate_all_fail == 1)
    {
        simulate_fail = 0;
        return (FAIL);
    }
    while (i < size)
    {
        readed_octet = read_eeprom(address);
        if (readed_octet != ptr[i])
        {
            write_eeprom(address, ptr[i]);
            readed_octet = read_eeprom(address);
            if (readed_octet != ptr[i])
                return (FAIL);
        }
        i++;
        address++;
    }
    return (SUCCESS);
}


static void invalidate_old_slot(uint16_t address, uint16_t size)
{
    uint16_t    i = 0;
    uint8_t     readed_octet;

    while (i < size)
    {
        readed_octet = read_eeprom(address);
        if (readed_octet != 0x00)
        {
            write_eeprom(address, 0x00);
            readed_octet = read_eeprom(address);
            if (readed_octet != 0x00)
                return;
        }
        i++;
        address++;
    }
}


uint8_t save_config(void)
{
    uint8_t     old_slot = current_slot;
    uint8_t     slot = current_slot;
    uint8_t     number_of_slot_tried = 0; 
    uint16_t    current_slot_address = SLOT_1_ADDR + (slot - 1) * SLOT_SIZE;

    current_config.magic_number = MAGIC;
    if (write_block_eeprom(current_slot_address, sizeof(current_config), &current_config))
    {
        current_slot = slot;
        is_configured = 1;
        return (SUCCESS);
    }
    else
    {
        number_of_slot_tried++;
        uart_printstr("Corruption detected.\r\n");
        while (number_of_slot_tried < 4)
        {
            if (slot == SLOT_4)
                slot = SLOT_1;
            else
                slot++;
            uart_printstr("Relocating config to slot ");
            ft_putnbr(slot);
            uart_printstr("... ");
            current_slot_address = SLOT_1_ADDR + (slot - 1) * SLOT_SIZE;
            if (write_block_eeprom(current_slot_address, sizeof(current_config), &current_config))
            {
                uart_printstr("Success\r\nDone.\r\n");
                current_slot = slot;
                if (current_slot != old_slot)
                    invalidate_old_slot((SLOT_1_ADDR + (old_slot - 1) * SLOT_SIZE), sizeof(current_config.magic_number));
                is_configured = 1;
                return (SUCCESS);
            }
            else
            {
                uart_printstr("Fail\r\n");
                number_of_slot_tried++;
            }
        }
    }
    uart_printstr("CRITICAL EEPROM FAILURE.\r\n");
    return (FAIL);
}