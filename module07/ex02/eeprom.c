#include "includes/main.h"

unsigned char read_eeprom(uint16_t address)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
        ;

    /*Set up adress register*/
    EEAR = address;

    /*Start eeprom read by writing EERE*/
    EECR |= (1 << EERE);

    return (EEDR);
}


void write_eeprom(uint16_t address, uint8_t data)
{
    /*Wait for completion of previous write*/
    while (EECR & (1 << EEPE))
        ;
    
    /*Set up adress and data registers*/
    EEAR = address;
    EEDR = data;

    /*Write logical one to EEMPE*/
    EECR |= (1 << EEMPE);

    /*Start eeprom write by setting EEPE*/
    EECR |= (1 << EEPE);
}


void read_block_eeprom(uint16_t start_address, uint16_t size, void *storage)
{
    uint8_t     *ptr = (uint8_t *)storage;
    uint16_t    i = 0;

    while (i < size)
    {
        ptr[i] = read_eeprom(start_address);
        start_address++;
        i++;
    }
}


void load_config_from_eeprom(void)
{
    uint8_t     slot = SLOT_1;
    uint16_t    address;
    uint32_t    magic;
    uint32_t    node_id;
    int16_t     prio;
    char        tag[33];
    uint16_t    crc;
    uint16_t    computed_crc;


    while (slot <= 4)
    {
        address = SLOT_1_ADDR + (slot - 1) * SLOT_SIZE;
        computed_crc = 0xFFFF;
        read_block_eeprom(address, sizeof(magic), &magic);
        if (magic == MAGIC)
        {
            address += sizeof(magic);
            read_block_eeprom(address, sizeof(node_id), &node_id);
            address += sizeof(node_id);
            read_block_eeprom(address, sizeof(prio), &prio);
            address += sizeof(prio);
            read_block_eeprom(address, sizeof(tag), tag);
            address += sizeof(tag);
            read_block_eeprom(address, sizeof(crc), &crc);

            compute_crc(&computed_crc, &node_id, &prio, tag);
            if (crc == computed_crc)
            {
                current_config.magic_number = magic;
                current_config.node_id = node_id;
                current_config.priority = prio;
                ft_memcopy(tag, (char *)current_config.tag, sizeof(tag));
                current_config.crc = crc;
                current_slot = slot;
                is_configured = 1;
                return;
            }
            corruption_detected = 1;
        }
        slot++;
    }
    is_configured = 0;
}