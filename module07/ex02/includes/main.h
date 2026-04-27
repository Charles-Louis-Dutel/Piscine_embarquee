#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/crc16.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define UART_BAUDRATE 115200

#define HEXA "0123456789ABCDEF"
#define HEXA_MIN "0123456789abcdef"


/*CONFIG*/
#define SLOT_SIZE 64
#define SLOT_0_ADDR 0
#define SLOT_1_ADDR 64
#define SLOT_2_ADDR 128
#define SLOT_3_ADDR 192
#define MAGIC 0x42CACA07


/*ERROR MESSAGES*/
#define BAD_ENTRY "Bad entry, please try with this format: COMMAND ARGUMENT\r\n"
#define INVALID_COMMAND "Invalid command, try with : STATUS, SET_ID, SET_PRIO, SET_TAG, FACTORY_RESET\r\n"
#define STATUS_ARG_ERROR "STATUS doesn't need argument\r\n"
#define ID_ARG_ERROR "SET_ID argumment should only be numbers and should feet in uint32_t\r\n"
#define PRIO_ARG_ERROR "SET_PRIO argumment should only be numbers (negative number allowed with only \
one sign -) and should feet in int16_t\r\n"
#define TAG_ARG_ERROR "SET_TAG argument should be 32 charachters maximum and can't be empty\r\n"
#define TAG_ARG_ERROR_1 "SET_TAG argument should be between double quotes \"\"\r\n"
#define TAG_ARG_ERROR_2 "SET_TAG argument charachters should be alphanum, _ or -\r\n"
#define FACTORY_RESET_ARG_ERROR "FACTORY_RESET doesn't need argument\r\n"

/*COMMANDS*/
#define STATUS "STATUS"
#define SET_ID "SET_ID"
#define SET_PRIO "SET_PRIO"
#define SET_TAG "SET_TAG"
#define FACTORY_RESET "FACTORY_RESET"


struct config {
    uint32_t    magic_number; //4 octets
    uint32_t    node_id;      //4 octets
    int16_t     priority;     //2 octets
    char        tag[33];      //33 octets
    uint16_t    crc;          //2 octets
};                            //total 45 octets


/*Parsing*/
extern volatile unsigned char   data[65];
extern volatile unsigned char  command[65];
extern volatile unsigned char  argument[65];

/*Config*/
extern volatile uint8_t        current_slot;
extern volatile uint8_t        is_configured;
extern volatile uint8_t        corruption_detected;
extern volatile struct config  current_config;

/*uart.c*/
void            uart_init(unsigned int ubrr);
unsigned char   uart_rx(void);
void            uart_tx(const char c);
void            uart_printstr(const char *str);
void            print_hex_value(uint8_t c);
void            print_adress_hexa(uint16_t adress);
void            ft_putnbr(uint16_t n);


/*crc.*/
void            compute_crc(uint16_t *computed_crc, uint32_t *node_id, int16_t *prio, char *tag);


/*eeprom.c*/
unsigned char   read_eeprom(uint16_t address);
void            write_eeprom(uint16_t address, uint8_t data);
void            read_block_eeprom(uint16_t start_address, uint16_t size, void *storage);
void            load_config_from_eeprom(void);


/*receive_data.c*/
void            receive_data(void);
uint8_t         store_data(void);
uint8_t         convert_data(void);


/*parse_data.c*/
uint8_t         check_command(void);


/*utils.c*/
uint8_t         ft_is_print(unsigned char c);
uint8_t         ft_is_hexa(unsigned char c);
uint8_t         ft_strlen(const char *str);
uint8_t         hexa_to_ui(unsigned char c);
uint8_t         ft_strcomp(const char *s1, const char *s2);
uint8_t         ft_is_num(const char c);
uint8_t         ft_is_alphanum(const char c);
void            ft_trim(char *str);
void            ft_memcopy(void *to_copy, void *dest, uint16_t size);


/*manage_eeprom.c*/
void            print_eeprom(void);
void            print_eeprom_with_red(uint16_t adress, uint8_t octet_value);
uint8_t         check_octet_eeprom(void);


