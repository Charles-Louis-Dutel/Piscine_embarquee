MCU=atmega328p
CC=avr-gcc
OBJCOPY=avr-objcopy

SRC=main.c
OBJ=$(SRC:.c=.o)

F_CPU=16000000

CFLAGS=-mmcu=$(MCU) -Wall -Os -DF_CPU=$(F_CPU) -I$(AVR_LIBC_DIR)/include -nostdlib
TARGET=main

AVR_LIBC_DIR=/tmp/avr-libc

all: hex flash

# $(AVR_LIBC_DIR)/.CACHETAG:
# 	rm -rf $(AVR_LIBC_DIR)
# 	git clone --depth=1 https://github.com/avrdudes/avr-libc/ $(AVR_LIBC_DIR)
# 	cd $(AVR_LIBC_DIR) && ./bootstrap
# 	cd $(AVR_LIBC_DIR) && ./configure --build=`./config.guess` --host=avr
# 	cd $(AVR_LIBC_DIR) && make -j
# 	touch $(AVR_LIBC_DIR)/.CACHETAG

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

hex: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET).bin
	$(OBJCOPY) -O ihex $(TARGET).bin $(TARGET).hex

flash: hex
	avrdude -p $(MCU) -c arduino -P /dev/ttyUSB0 -b 115200  -U flash:w:$(TARGET).hex

clean:
	rm -f $(OBJ) $(TARGET).bin $(TARGET).hex

