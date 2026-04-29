#include "includes/main.h"

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


static void SPI_master_transmit(uint8_t data)
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


void full_SPI_frame(void)
{
    //START frame
    SPI_frame(0x00, 0x00, 0x00, 0x00);

    //D6
    SPI_frame(led_colors[0][0], led_colors[0][1], led_colors[0][2], led_colors[0][3]);

    //D7
    SPI_frame(led_colors[1][0], led_colors[1][1], led_colors[1][2], led_colors[1][3]);
    
    //D8
    SPI_frame(led_colors[2][0], led_colors[2][1], led_colors[2][2], led_colors[2][3]);

    //END frame
    SPI_frame(0xFF, 0xFF, 0xFF, 0xFF);
}


void full_SPI_frame_select(void)
{
    //START frame
    SPI_frame(0x00, 0x00, 0x00, 0x00);

    //D6
    SPI_frame(led_colors_select[0][0], led_colors_select[0][1], led_colors_select[0][2], led_colors_select[0][3]);

    //D7
    SPI_frame(led_colors_select[1][0], led_colors_select[1][1], led_colors_select[1][2], led_colors_select[1][3]);
    
    //D8
    SPI_frame(led_colors_select[2][0], led_colors_select[2][1], led_colors_select[2][2], led_colors_select[2][3]);

    //END frame
    SPI_frame(0xFF, 0xFF, 0xFF, 0xFF);
}