#include <avr/io.h>
#include "btn_utils.h"

uint8_t btn_mem[1];

void btn_read()
{
	btn_mem[0]= PINB & 0b111;
}