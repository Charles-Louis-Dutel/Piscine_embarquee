#include "includes/main.h"

uint8_t check_validity(char *username, char *password)
{
    if (!ft_strcmp(USERNAME, username) || !ft_strcmp(PASSWORD, password))
        return (uart_printstr("Bad combinaison username/password\r\n\r\n"), 0);
    uart_printstr("Hello ");
    uart_printstr(username);
    uart_printstr("!\r\nShall we play a game?\r\n");
    return (1);
}

int main()
{
    uint16_t    ubrr = (F_CPU / (8 * UART_BAUDRATE)) - 1;
    uint8_t     validity= 0;
    uint8_t     rgb = 1;
    uint8_t     on = 1;
    char        username[21];
    char        password[21];

    
    DDRB = (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
    DDRD = (1 << PD3) | (1 << PD5) | (1 << PD6);

    uart_init(ubrr);

    while (1)
    {
        if (validity == 0)
        {
            uart_printstr("Enter your login:\r\n");
            uart_printstr("\tusername: ");
            receive_username(username);
            uart_printstr("\tpassword: ");
            receive_password(password);
            validity = check_validity(username, password);
        }
        else
        {
            PORTB ^= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
            if (on == 0)
            {
                PORTD = 0;
                on = 1;
            }
            else if (rgb == 1 && on == 1)
            {
                PORTD = (1 << PD5);
                rgb = 2;
                on = 0;
            }
            else if (rgb == 2 && on == 1)
            {
                PORTD = (1 << PD6);
                rgb = 3;
                on = 0;
            }
            else if (rgb == 3 && on == 1)
            {
                PORTD = (1 << PD3);
                rgb = 1;
                on = 0;
            }
            _delay_ms(500);
        }
    }
} 