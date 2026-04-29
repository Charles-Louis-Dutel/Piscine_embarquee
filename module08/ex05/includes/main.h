#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
 #define F_CPU 16000000
#endif

#define PRESCALER_DIV 64
#define UART_BAUDRATE 115200

#define HEXA "0123456789ABCDEF"
#define HEXA_MIN "0123456789abcdef"

/*SWITCHES*/
#define PRESSED 1
#define UNPRESSED 0

#define SWITCH_1 1
#define SWITCH_2 2

/*LEDS*/
#define D6 0
#define D7 1
#define D8 2

#define BLUE 1
#define GREEN 2
#define RED 3

extern volatile uint8_t state_sw1;
extern volatile uint8_t state_sw2;
extern volatile uint8_t active_switch;
extern volatile uint8_t active_color;
extern volatile uint8_t old_color_value;
extern volatile uint8_t active_led;
extern volatile uint8_t led_colors[3][4];
extern volatile uint8_t led_colors_select[3][4];

void ADC_vect(void) __attribute__((signal));
void INT0_vect(void) __attribute__((signal));
void PCINT2_vect(void) __attribute__((signal));
void TIMER1_COMPA_vect(void) __attribute__((signal));


/*spi.c*/
void            SPI_master_init(void);
void            SPI_frame(uint8_t brightness, uint8_t b, uint8_t g, uint8_t r);
void            full_SPI_frame(void);
void            full_SPI_frame_select(void);


/*receive_data.c*/
void            receive_data(void);
uint8_t         check_data(void);
void            convert_data(void);


/*utils.c*/
uint8_t         ft_is_print(unsigned char c);
uint8_t         ft_is_hexa(unsigned char c);
uint8_t         ft_strlen(const char *str);
void            ft_trim(char *str);
uint8_t         ft_strcomp(const char *s1, const char *s2);
uint8_t         hexa_to_ui(unsigned char c);
void            ft_copy_table(uint8_t mode);

/*timer.c*/
void            init_timer1(void);
void            activate_timer(void);
void            desactivate_timer(void);


/*handle_switches.c*/
void            init_switch(void);


/*adc.c*/
void            init_adc(void);


