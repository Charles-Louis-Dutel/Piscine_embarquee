MCU=atmega328p
CC=avr-gcc
OBJCOPY=avr-objcopy

SRC=main.c spi.c utils.c timer.c adc.c handle_switches.c
OBJ=$(SRC:.c=.o)

F_CPU=16000000

CFLAGS=-mmcu=$(MCU) -Wall -Os -DF_CPU=$(F_CPU)
TARGET=main


all: hex flash

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

hex: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET).bin
	$(OBJCOPY) -O ihex $(TARGET).bin $(TARGET).hex

flash: hex
	avrdude -p $(MCU) -c arduino -P /dev/ttyUSB0 -b 115200  -U flash:w:$(TARGET).hex

clean:
	rm -f $(OBJ) $(TARGET).bin $(TARGET).hex

