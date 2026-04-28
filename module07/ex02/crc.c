#include "includes/main.h"

static uint16_t my_crc16_update(uint16_t __crc, uint8_t __data)
{
	uint8_t __tmp;
	uint16_t __ret;

	__asm__ __volatile__ (
		"eor %A0,%2" "\n\t"
		"mov %1,%A0" "\n\t"
		"swap %1" "\n\t"
		"eor %1,%A0" "\n\t"
		"mov __tmp_reg__,%1" "\n\t"
		"lsr %1" "\n\t"
		"lsr %1" "\n\t"
		"eor %1,__tmp_reg__" "\n\t"
		"mov __tmp_reg__,%1" "\n\t"
		"lsr %1" "\n\t"
		"eor %1,__tmp_reg__" "\n\t"
		"andi %1,0x07" "\n\t"
		"mov __tmp_reg__,%A0" "\n\t"
		"mov %A0,%B0" "\n\t"
		"lsr %1" "\n\t"
		"ror __tmp_reg__" "\n\t"
		"ror %1" "\n\t"
		"mov %B0,__tmp_reg__" "\n\t"
		"eor %A0,%1" "\n\t"
		"lsr __tmp_reg__" "\n\t"
		"ror %1" "\n\t"
		"eor %B0,__tmp_reg__" "\n\t"
		"eor %A0,%1"
		: "=r" (__ret), "=d" (__tmp)
		: "r" (__data), "0" (__crc)
		: "r0"
	);
	return __ret;
}


static void compute_crc_item(volatile uint16_t *computed_crc, uint16_t size, volatile void *storage)
{
	uint8_t		*ptr = (uint8_t *)storage;
	uint16_t	i = 0;

	while (i < size)
	{
		*computed_crc = my_crc16_update(*computed_crc, ptr[i]);
		i++;
	}
}


void compute_crc(volatile uint16_t *computed_crc, volatile uint32_t *node_id,
	volatile int16_t *prio, volatile char *tag)
{
	*computed_crc = 0xFFFF;

	compute_crc_item(computed_crc, sizeof(*node_id), node_id);
	compute_crc_item(computed_crc, sizeof(*prio), prio);
	compute_crc_item(computed_crc, 33, tag);
}
