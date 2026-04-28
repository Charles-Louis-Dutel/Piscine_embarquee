#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


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


int main()
{
    SPI_master_init();

    while (1)
    {
        //START frame
        SPI_frame(0x00, 0x00, 0x00, 0x00);

        //D6
        SPI_frame(0xE1, 0x00, 0x00, 0xFF);

        //D7
        SPI_frame(0xE0, 0x00, 0x00, 0x00);
        
        //D8
        SPI_frame(0xE0, 0x00, 0x00, 0x00);

        //END frame
        SPI_frame(0xFF, 0xFF, 0xFF, 0xFF);
    }
}