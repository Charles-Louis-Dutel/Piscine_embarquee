#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define RED [0xE1, 0x00, 0x00, 0xFF]

void SPI_master_init(void)
{
    //(p.172)
    /*Set MOSI and SCK output, all others input*/
    //PB3 -> MOSI
    //PB5 -> SCK
    //PB2 -> If SS is configured as an output, the pin is a general output
    //pin which does not affect the SPI system. Typically, the pin will be
    //driving the SS pin of the SPI Slave.
    DDRB = (1 << PB2) | (1 << PB3) | (1 << PB5);

    /*Enable SPI, Master, set clock rate fck/16*/
    //SPCR – SPI Control Register (p.176)
    //Activer le SPI
    //    SPE a 1 -> reg SPCR
    //Selectionner Master mode
    //    MSTR a 1 -> reg SPCR
    //Controle de la frequence SCK, fosc/16
    //    SPR0 a 1 -> reg SPCR
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}


void SPI_master_transmit(uint8_t data)
{
    /*Start transmission*/
    SPDR = data;

    /*Wait for transmission complete*/
    while (!(SPSR & (1 << SPIF)))
        ;
}


void SPI_frame(uint8_t brightness, uint8_t b, uint8_t g, uint8_t r)
{
    SPI_master_transmit(brightness);
    SPI_master_transmit(b);
    SPI_master_transmit(g);
    SPI_master_transmit(r);
}


void full_SPI_frame(uint8_t *colors)
{
    //START frame
    SPI_frame(0x00, 0x00, 0x00, 0x00);

    //D6
    SPI_frame(colors[0], colors[1], colors[2], colors[3]);

    //D7
    SPI_frame(0xE0, 0x00, 0x00, 0x00);
    
    //D8
    SPI_frame(0xE0, 0x00, 0x00, 0x00);

    //END frame
    SPI_frame(0xFF, 0xFF, 0xFF, 0xFF);
}


int main()
{
    uint8_t i = 0;
    uint8_t colors[7][4] = {
        {0xE1, 0x00, 0x00, 0xFF}, //RED
        {0xE1, 0x00, 0xFF, 0x00}, //GREEN
        {0xE1, 0xFF, 0x00, 0x00}, //BLUE
        {0xE1, 0x00, 0xFF, 0xFF}, //YELLOW
        {0xE1, 0xFF, 0xFF, 0x00}, //CYAN
        {0xE1, 0xFF, 0x00, 0xFF}, //MAGENTA
        {0xE1, 0xFF, 0xFF, 0xFF}, //WHITE
    };

    SPI_master_init();

    while (1)
    {
        full_SPI_frame(colors[i]);
        _delay_ms(1000);
        i++;
        if (i == 7)
            i = 0;
    }
}